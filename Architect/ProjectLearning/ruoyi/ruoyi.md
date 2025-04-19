## 视频教程

https://www.bilibili.com/video/BV1zm4y1A7yQ?p=7&vd_source=d258f4a5ee4d4e3cef59553156ef7d92

https://www.bilibili.com/video/BV1HT4y1d7oA/?spm_id_from=333.788.recommend_more_video.1&vd_source=d258f4a5ee4d4e3cef59553156ef7d92

https://www.bilibili.com/video/BV1684y1X7tK/?spm_id_from=333.788.recommend_more_video.9&vd_source=d258f4a5ee4d4e3cef59553156ef7d92

https://xie.infoq.cn/article/7669d33662b9f91ff9248c808

ruoyi报名修改工具：https://gitee.com/lpf_project/common-tools

## JWT

https://mp.weixin.qq.com/s/U-GsQNiVE6CHE9gIzH2Zmg

## 前端调试

1. 在需要调试的后端部分插入 “debugger”

2. 前端vue项目配置：

![image-20231127165101636](https://s2.loli.net/2023/11/27/Y2rPtWbAn7S6MuQ.png)

3. 然后浏览器点击F12，点击`sources`标签

## 解决跨域问题

双管齐下

- 前端：vue反向代理

  `vue.config.js`

  ![image-20231127222859688](https://s2.loli.net/2023/11/27/FtgCyphVP9S8o5G.png)

- 后端：CORS。配置过滤器，添加响应头

  `ResourceConfig.java`

  ![image-20231127223100638](https://s2.loli.net/2023/11/27/l9PXQWEMaJHVNpc.png)

  

## ruoyi权限管理

没有使用spring security自带的权限管理，而是自己实现了一下

包含有：菜单权限，目录权限，按钮权限

如何与spring security发生关系？

用户在此处定义了权限：`*:*:*`字符串形式

```java
//SecurityConfig：其中LoginUser实现了UserDetails接口
public UserDetails createLoginUser(SysUser user)
{
    //需要注意最后一个参数，这里去数据库查询了权限！！！也就是查询登录人的权限【包括页面权限和按钮权限】
    return new LoginUser(user.getUserId(), user.getDeptId(), user, permissionService.getMenuPermission(user));
}
```



菜单权限【前端】：通过数据库去拉取菜单路由列表，在前端显示出来【不赘述】

按钮权限【前端】：按钮是否显示，无权限的不显示，依靠自主实现的属性 `v-hasPermi`

![图片](https://s2.loli.net/2023/11/27/L7Hn9QplT4geP2q.png)

接口权限【后端】：`@PreAuthorize`注解

```java
/*
  * 获取岗位列表
*/
@PreAuthorize("@ss.hasPermi('system:post:list')")
@GetMapping("/list")
public TableDataInfo list(SysPost post)
{
    startPage();
    List<SysPost> list = postService.selectPostList(post);
    return getDataTable(list);
}
```

`@PreAuthorize`注解是Spring Security提供的，参数是一个表达式，如果返回true，则执行方法，否则不执行

`@ss.hasPermi()`是自己定义的bean里面的一个方法，用来进行权限判断，本质是比较已认证的用户的权限集（在认证时设置，见上文）中是否有当前权限



## 分页后端实现

使用pagehelper进行分页，pagehelp内部引入了mybatis

![image-20231128134407359](https://s2.loli.net/2023/11/28/JVD3pL61HkN2YXj.png)

pagehelper的分页方法：[官网](https://pagehelper.github.io/docs/howtouse/)

```java
//获取第1页，10条内容，默认查询总数count
// ry用的就是下面这种。
PageHelper.startPage(1, 10);
Mapper的sql查询
```

ry的集成：

需要分页的`Controller`都会继承`BaseController`；

![image-20231128161649767](https://s2.loli.net/2023/11/28/Ef5w7ZAnU9abSm8.png)

点进去可见：

![image-20231128161718083](https://s2.loli.net/2023/11/28/7VnYgbSsXw46CKI.png)

再点进去可以看到，默认取第一页，每页10条记录，升序，配置了参数合理化

![image-20231128161818748](https://s2.loli.net/2023/11/28/4kxb9I6lhYCwsUX.png)