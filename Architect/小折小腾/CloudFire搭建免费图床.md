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



## 使用WebP Cloud图片优化（可选）

[WebP Cloud](https://webp.se/)简单来说这是一个类 CDN 的图片代理 SaaS 服务，可以把图片转换为webp/avif格式，所见图像体积，加快网页中图片的加载速度。

> 本人没有采用，因为返回的图片可能是webp，也可能是avif，而avif在typora中无法正常预览。

![image-20241113145548355](https://my-pic.miaops.sbs/2024/11/image-20241113145548355.png)

配置方式如下：

注册账号并登陆，创建代理。源站地址为picGO中设置的自定义域名；如果没配置自定义域名则填写 R2 提供的 `xxx.r2.dev` 格式的域名。

![image-20241113150126991](https://my-pic.miaops.sbs/2024/11/image-20241113150126991.png)

创建成功后可以得到一个代理地址，将代理地址设置到picGo的自定义域名中即可。

![image-20241113150300249](https://my-pic.miaops.sbs/2024/11/image-20241113150300249.png)

![image-20241113150350255](https://my-pic.miaops.sbs/2024/11/image-20241113150350255.png)

免费用户每天有 3000 Free Quota，即能够代理 2000 次图片访问请求，并提供 100M 的图片缓存，对于一般用户来说完全够用。

如超过了 Quota，访问则会被 302 转发到源站图片地址，不经 WebP Cloud 服务压缩，但依然可用；超过 100M 的缓存则会按照 LRU 算法清理，所以依然能够保障一些高频请求的图片能够有较好的访问体验。



参考链接：[从零开始搭建你的免费图床系统 （Cloudflare R2 + WebP Cloud + PicGo](https://sspai.com/post/90170)
