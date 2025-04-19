## 错误描述

用户端点击“绑定”时抛出如下错误：

![image-20240707154634267](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240707154634267.png)

![ea61ceeab6d50d5c977a9b109df3219](https://raw.githubusercontent.com/timothy020/pic/main/img/ea61ceeab6d50d5c977a9b109df3219.png)



## 错误定位

点击“绑定”时，先后调用了三个接口（具体流程参考[微信官方文档](https://developers.weixin.qq.com/doc/offiaccount/OA_Web_Apps/Wechat_webpage_authorization.html#0))：

| 调用者         | 接口                                                | 接口位置 | 作用               |
| -------------- | --------------------------------------------------- | -------- | ------------------ |
| 前端           | https://open.weixin.qq.com/connect/oauth2/authorize | 微信平台 | 获取code           |
| 前端           | bind()                                              | 后端     | 绑定用户           |
| 后端bind()接口 | https://api.weixin.qq.com/sns/oauth2/access_token   | 微信平台 | 通过code获取openId |

点击F12，发现前端还没有调用bind()接口，就已经报错，说明是调用“获取code”的接口报错。

![image-20240707155501230](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240707155501230.png)

以测试环境为例，“获取code”接口的完整的GET请求如下：

```java
https://open.weixin.qq.com/connect/oauth2/authorize?appid=wx28c67ddf65bbed9d&redirect_uri=https://cs.sxlntd.cn:80/%23/pages/mine/bind/index&response_type=code&scope=snsapi_base&state=123#wechat_redirect
```



在微信环境中进行上述GET请求，就能复现出错误。

![image-20240707162848253](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240707162848253.png)

![image-20240707162924327](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240707162924327.png)

## 错误原因

“获取code”接口需要一个参数redirect_uri【uri：Uniform Resource Identifie，url：Uniform Resource Locator是uri的一种具体形式】作为回调地址。

前端实现中，redirect_uri是动态获取的，为当前页面的url地址，即绑定页面的url：

- 开发环境：https://www.sxlntd.cn:20080/#/pages/mine/bind/index
- 测试环境：https://cs.sxlntd.cn:80/#/pages/mine/index

后台配置的域名已经与 redirect_uri一致，然而依然报错。

![image-20240707155850622](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240707155850622.png)



后经查证发现，是微信的回调地址（无论是网页授权回调redirect_uri还是支付回调notify_url）都不支持携带端口。

> 参考微信社区中的回答：
>
> - 授权回调：[回答1](https://developers.weixin.qq.com/community/develop/doc/0006aa68efcff8d028cd3f98f56400)，[回答2](https://developers.weixin.qq.com/community/develop/doc/00024c52758140fb12a19149161800)
> - 支付回调：[回答](https://developers.weixin.qq.com/community/develop/doc/000c8c543bc32040c6ee20f4152800)



目前的两个redirect_uri都是携带端口号的，要不携带端口号，比较简便的方式就是前端部署时使用默认端口

- 测试环境-https-443
- 开发环境-http-80



这样在获取当前页面的时候，得到的url为：

- 开发环境：https://www.sxlntd.cn/#/pages/mine/bind/index
- 测试环境：http://cs.sxlntd.cn/#/pages/mine/index

就不会出现上述问题，而且前端本身部署在默认端口上，可以跳转回对应页面。



修改redirect_uri后，开发环境和测试环境的GET请求变为：

```java
//开发环境：
https://open.weixin.qq.com/connect/oauth2/authorize?appid=wx28c67ddf65bbed9d&redirect_uri=http://www.sxlntd.cn/%23/pages/mine/bind/index&response_type=code&scope=snsapi_base&state=123#wechat_redirect
//测试环境
https://open.weixin.qq.com/connect/oauth2/authorize?appid=wx28c67ddf65bbed9d&redirect_uri=https://cs.sxlntd.cn/%23/pages/mine/bind/index&response_type=code&scope=snsapi_base&state=123#wechat_redirect
```

在微信环境中请求，可以发现不再报redirect_uri不一致的错误（因为没有修改配置，会报其他错误）。

![image-20240707164526546](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240707164526546.png)



> 为什么之前没有出现这个问题？
>
> 原先开发环境和测试环境的用户端地址为 https://cs.sxlntd.cn/#/ 和 https://www.sxlntd.cn/#/，两个域名对应两个不同ip，都采用https，默认端口443，所以redirect_uri不会携带端口号。



## 错误解决

由于开发环境和测试环境现在处于同一个服务器上，两个域名对应同一个ip，所以不能都使用https并使用默认端口443。



测试环境使用https，开发环境使用http。



**配置修改：**

需要达到的效果：

- 测试环境用户端可以通过 https://cs.sxlntd.cn 访问
- 开发环境用户端可以通过 http://www.sxlntd.cn 访问

可供参考的步骤：

1. 测试环境用户端：修改dockerFile的端口映射 443->443
2. 开发环境用户端：修改nginx配置为http，把前端项目部署到80端口；修改dockerFile的端口映射 80->80



前端无需修改，因为都是通过nginx解析 /gateway路径 然后反向代理到后端。

