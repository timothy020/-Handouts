## Tomcat

### 基础

Tomcat是什么；是服务器软件，是在靶场中发射子弹的枪。



一个可以发布到tomcat/webapp中的目录结构。

- static
  - js: `.js`
  - img: `.png` `.jpg`
  - css: `.css`
- page: `.html`
- WEB-INF（受保护的资源目录）
  - classes：字节码根路径
  - lib：依赖jar包存放路径
  - web.xml：项目的配置文件

| static和page是属于视图相关的文件，可以随意编排。



部署项目的两种方式

1. 直接扔到webapps

2. 放到其他目录，在\Tomcat 10.1\conf\Catalina\localhost添加配置

   如果部署的项目文件夹为app，则添加如下配置 `app.xml`

   ```xml
   <Context path="/app" docBase="D:\myWebApp\app" />
   # path为应用上下文路径，即为url的路径，一般与项目文件名保持一致
   # docBase为应用的地址
   ```



要访问tomcat原有的管理项目，需要先设置tomcat密码。

在/cnf/tomcat-users.xml文件中添加如下代码：

```xml
<role rolename="admin-gui"/>
<role rolename="admin-script"/>
<role rolename="manager-gui"/>
<role rolename="manager-script"/>
<role rolename="manager-jmx"/>
<role rolename="manager-status"/>
<user username="admin" password="admin" roles="manager-gui,manager-script,manager-jmx,manager-status,admin-script,admin-gui"/>
```

访问http://localhost:8080/manager/html，输入admin/admin

![image-20240905225545691](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240905225545691.png)



### idea开发javaweb工程

![image-20240905230416952](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240905230416952.png)

1. **建立Tomcat和idea关联**

   ![image-20240905231010999](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240905231010999.png)

2. **使用idea创建javaweb工程，在web工程中开发代码**

   首先配置JDK，模块，引用的库，Artifacts

   ![image-20240906135016605](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240906135016605.png)

3. **使用idea将工程构建成一个可以发布的app**

   当缺少WEB目录时，可以通过下面的方式添加

   ![image-20240906134403872](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240906134403872.png)

4. **使用idea将构建好的app部署到tomcat中启动运行**

   ![image-20240906135139569](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240906135139569.png)

   ![image-20240906135229823](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240906135229823.png)



### idea运行javaweb工程的原理

| 疑问：为什么在idea中运行javaweb工程后，在对应的tomcat的workapp目录下并没有应用文件？

idea为了避免污染硬盘中的tomcat目录，没有直接把应用文件放到workapp中，而是根据需要部署的web应用，创建了一套配置文件，让tomcat根据那个配置文件进行运行。

![image-20240906140645140](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240906140645140.png)

![image-20240906140750343](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240906140750343.png)

继续打开 `conf/Catalina/localhost`中的 `demo_war_exploded.xml`，有下面的代码，配置了web应用的上下文路径和项目文件位置

```xml
<Context path="/demo_war_exploded" docBase="C:\Users\Timothy\Documents\WeChat Files\wxid_b7e193fz08w512\FileStorage\File\2024-09\知校聚合支付接口（demo是PC端扫码跳转）\java\demo\out\artifacts\demo_war_exploded" />
```





