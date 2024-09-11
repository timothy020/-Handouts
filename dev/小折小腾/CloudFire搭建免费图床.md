[TOC]

## CloudFire对象存储

### 创建bucket

**打开[CloudFire](https://dash.cloudflare.com/16a880f30f641c6170ab972bbf9e7f03)官网并注册账号，点击R2存储。**

![image-20240909194038848](https://my-pic.miaops.sbs/2024/09/image-20240909194038848.png)



**创建图床bucket**



地区可以选择亚洲（APAC）或者北美洲西部（ENAM），根据需求选其他区域也可以，但 Cloudflare 并不保证一定会分配到所指定的区域。



![image-20240909194418371](https://my-pic.miaops.sbs/2024/09/image-20240909194418371.png)

### 配置域名

**打开 R2.dev 子域，得到图片公网地址**

![image-20240909195751892](https://my-pic.miaops.sbs/2024/09/image-20240909195751892.png)

![image-20240909195807881](https://my-pic.miaops.sbs/2024/09/image-20240909195807881.png)



**自定义域名（可选）**



可以添加自己的域名，比如我有一个域名为`miaops.sbs`，那么可以把自定义域设置为`test-pic.miaops.sbs`



输入域名

![image-20240909200036264](https://my-pic.miaops.sbs/2024/09/image-20240909200036264.png)

![image-20240909200058822](https://my-pic.miaops.sbs/2024/09/image-20240909200058822.png)



点击“连接域”

![image-20240909200151388](https://my-pic.miaops.sbs/2024/09/image-20240909200151388.png)



成功后等待一段时间，可以看到设置成功的域名，之后可以用这个域名访问图片

![image-20240909200308109](https://my-pic.miaops.sbs/2024/09/image-20240909200308109.png)

![image-20240909200317609](https://my-pic.miaops.sbs/2024/09/image-20240909200317609.png)

### 配置 Bucket 访问 API

进入API tokens管理界面，创建API token。权限选择允许读和写，应用到特定的bucket。

![image-20240911122411627](https://my-pic.miaops.sbs/2024/09/image-20240911122411627.png)

**创建后页面上会显示``Access Key ID` ，`Secret Access Key` 等信息，先不要关闭页面，把相关信息做好记录，因为之后不会再显示。**

## PicGO配置

打开插件市场，下载S3对象存储插件。

![image-20240911122301036](https://my-pic.miaops.sbs/2024/09/image-20240911122301036.png)



把配置信息填写到插件页面，其余信息默认即可。



如果设置了自定义域名，则填写上去。



最后点击，“设为默认图床”即可。

![image-20240911122253766](https://my-pic.miaops.sbs/2024/09/image-20240911122253766.png)



接下来就可以用PicGo愉快地上传图片啦~。

比如把一张截图黏贴到typora中，就会自动上传到cloudFire，链接为设置的自定义域名+插件中设置的文件路径，我的设置是`{year}/{month}/{fileName}.{extName}`。

所以路径为`(https://自定义域名/2024/09/image-20240911122253766.png)`。

如果没有设置自定义域名，域名就是cloudFire分配的网址，名称较长，但不影响使用。



