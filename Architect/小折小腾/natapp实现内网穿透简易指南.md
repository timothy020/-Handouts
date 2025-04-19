## NATAPP是什么

NATAPP是一个十分容易上手的内网穿透工具，可以把本机的ip和端口映射到公网，将本机暴露在公网中供他人访问。

这在进行一些回调接口的本地测试（如支付宝微信支付的回调接口）时十分好用，同时也可以用来搭建服务器私服，和朋友一起畅快联机。

NETAPP提供了两条免费隧道供注册用户使用，也有其他套餐，按需选取即可。

![image-20240911125246657](https://my-pic.miaops.sbs/2024/09/image-20240911125246657.png)



## 快速入门

### 购买隧道

进入[NATAPP官网](https://natapp.cn/)，点击右上角免费注册，进行注册并登录。![image-20240911125457819](https://my-pic.miaops.sbs/2024/09/image-20240911125457819.png)



进入主界面后，点击”购买隧道“，选择”免费隧道“。

![image-20240911125557521](https://my-pic.miaops.sbs/2024/09/image-20240911125557521.png)



选择需要的隧道协议，映射的本地端口，然后直接点击“免费购买”即可。

![image-20240911125727468](https://my-pic.miaops.sbs/2024/09/image-20240911125727468.png)



购买隧道后，在”我的隧道“中，可以查看购买的隧道的相关信息。

![image-20240911125834558](https://my-pic.miaops.sbs/2024/09/image-20240911125834558.png)





### 安装客户端

仅仅购买了隧道还不够，需要安装客户端才可以实现内网穿透。

进入[客户端下载页面](https://natapp.cn/#download)，选择相应的版本进行下载，此处以windows为例。【该页面也可以查看官方教程】

![image-20240911130201537](https://my-pic.miaops.sbs/2024/09/image-20240911130201537.png)



下载并解压之后，可以发现有一个`config.ini`和`natapp.exe`文件。

![image-20240911130256666](https://my-pic.miaops.sbs/2024/09/image-20240911130256666.png)

用记事本打开`config.ini`文件，在authtoken出输入自己隧道token即可。

![image-20240911130530678](https://my-pic.miaops.sbs/2024/09/image-20240911130530678.png)

最后点击`natapp.exe`，即可实现内网穿透。如下图，把` http://3upmcv.natappfree.cc`映射到了本机的80端口，此时访问`http://3upmcv.natappfree.cc`就等于访问本机的80端口。

![image-20240911130835405](https://my-pic.miaops.sbs/2024/09/image-20240911130835405.png)



如果后续需要修改映射的端口，在“我的隧道”界面点击“配置“即可。

![image-20240911131011117](https://my-pic.miaops.sbs/2024/09/image-20240911131011117.png)

![image-20240911131023764](https://my-pic.miaops.sbs/2024/09/image-20240911131023764.png)