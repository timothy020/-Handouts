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



**部署项目的两种方式**

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

![image-20240905225545691](https://my-pic.miaops.sbs/2024/09/image-20240905225545691.png)



### idea开发javaweb工程

![image-20240905230416952](https://my-pic.miaops.sbs/2024/09/image-20240905230416952.png)

1. **建立Tomcat和idea关联**

   ![image-20240905231010999](https://my-pic.miaops.sbs/2024/09/image-20240905231010999.png)

2. **使用idea创建javaweb工程，在web工程中开发代码**

   首先配置JDK，模块，引用的库，Artifacts

   ![image-20240906135016605](https://my-pic.miaops.sbs/2024/09/image-20240906135016605.png)

3. **如果使用了Servlet，模块中需要添加Tomcat依赖**

   ![image-20240918100754679](https://my-pic.miaops.sbs/2024/09/image-20240918100754679.png)

4. **使用idea将工程构建成一个可以发布的app**

   当缺少WEB目录时，可以通过下面的方式添加

   ![image-20240906134403872](https://my-pic.miaops.sbs/2024/09/image-20240906134403872.png)

5. **使用idea将构建好的app部署到tomcat中启动运行**

   ![image-20240906135139569](https://my-pic.miaops.sbs/2024/09/image-20240906135139569.png)

   ![image-20240906135229823](https://my-pic.miaops.sbs/2024/09/image-20240906135229823.png)



### idea运行javaweb工程的原理

| 疑问：为什么在idea中运行javaweb工程后，在对应的tomcat的workapp目录下并没有应用文件？

idea为了避免污染硬盘中的tomcat目录，没有直接把应用文件放到workapp中，而是根据需要部署的web应用，创建了一套配置文件，让tomcat根据那个配置文件进行运行。

![image-20240906140645140](https://my-pic.miaops.sbs/2024/09/image-20240906140645140.png)

![image-20240906140750343](https://my-pic.miaops.sbs/2024/09/image-20240906140750343.png)

继续打开 `conf/Catalina/localhost`中的 `demo_war_exploded.xml`，有下面的代码，配置了web应用的上下文路径和项目文件位置

```xml
<Context path="/demo_war_exploded" docBase="C:\Users\Timothy\Documents\WeChat Files\wxid_b7e193fz08w512\FileStorage\File\2024-09\知校聚合支付接口（demo是PC端扫码跳转）\java\demo\out\artifacts\demo_war_exploded" />
```





## Servlet

### Servlet简介

**Servlet是什么？**

静态资源与动态资源：预先生成好的资源；服务器接受用户请求参数，动态生成的资源。

![image-20240918093912234](https://my-pic.miaops.sbs/2024/09/image-20240918093912234.png)

Servlet：能够处理客户请求并做出响应的一套Java技术标准，即**Java代码生成动态资源的标准**。

> Servlet运行在服务端，所以只能在Web项目中开发，且在Tomcat这样的服务容器中运行。



**Servlet运行流程？**

![image-20240918094923041](https://my-pic.miaops.sbs/2024/09/image-20240918094923041.png)



用户请求 -> Tomcat -> Servlet -> Java类（Controller，Service，Mapper，DAO）



### Servlet开发流程

**基本流程**

1. 创建javaweb项目，同时将tomcat作为项目依赖

2.  重写service方法，service(HttpServletRequest req, HttpServletResponse resp)，定义业务处理代码

   ```java
   public class UserServlet extends HttpServlet {
       @Override
       protected void service(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
           // 1.获取请求参数，只要是kv形式（无论在请求头还是请求体），都可以通过getParameter方法获取
           String username = req.getParameter("username");
   
           // 2.执行业务代码
           String info = "Yes";
           if("atguigu".equals(username)) {
               info = "No";
           }
   
           // 3.响应数据
           resp.setContentType("text/html");   // 设置响应头
           PrintWriter writer = resp.getWriter();
           writer.write(info);
       }
   }
   ```

3. 在web.xml中，配置Servlet的访问路径【可以直接用注解`@WebServlet("/userName")`替换】

   ![image-20240918112150995](https://my-pic.miaops.sbs/2024/09/image-20240918112150995.png)

   

**注意事项：**

1. 如何导入`servlet-api`依赖

- 通过在Web资源目录下新建lib文件夹，把依赖放进去
- 通过Project Settings-Modules-Dependency指定

![image-20240918112753870](https://my-pic.miaops.sbs/2024/09/image-20240918112753870.png)

`Tomcat 10.1`自动导入了`jsp-api`和`servlet-api`依赖

![image-20240918113011074](https://my-pic.miaops.sbs/2024/09/image-20240918113011074.png)

> Tomcat 10.1在哪里配置的？见“idea开发javaweb工程”中的第一步配置。

*两种方式有什么区别？*

区别在于是否会把依赖存放在打好的war包中。lib方式会把servlet依赖放到war包，另一种方式由于scope是`provided`，表示只会在编码时导入，不会放到war包。

*如果不放到war包，程序怎么用`servlet-api`呢？*

tomcat中部署的所有war包共享当前tomcat的lib库中的依赖。【所以自己导入后反而有可能由于冲突报错】

![image-20240918113527443](https://my-pic.miaops.sbs/2024/09/image-20240918113527443.png)

2. 怎么指定响应头的`Content-type`字段。

- 对于静态资源，tomcat的`web.xml`维护了请求的静态文件的扩展名与响应头`Content-type`字段的对应关系。比如请求的是`xxx.html`文件，则`Content-type`为text/html

  ![image-20240918113926905](https://my-pic.miaops.sbs/2024/09/image-20240918113926905.png)

- 对Servlet，默认的`Content-type`是html，如果数据需要作为其他类型解析，则要手动设置。具体设置的类型可以参考`web.xml`



### Servlet生命周期

| 生命周期           | 执行者  | 时机                                           |
| ------------------ | ------- | ---------------------------------------------- |
| 实例化             | 构造器  | 第一次请求/服务启动<br />【`load-on-startup`】 |
| 初始化             | init    | 构造完毕                                       |
| 接受请求，处理请求 | service | 每次请求                                       |
| 销毁               | destory | 关闭服务                                       |

**Servlet在Tomcat中是单例的，所以不建议在其中修改变量值。**



### DefaultServlet

Tomcat中提供了一个`DefaultServlet`用来返回静态资源。

当所有Servlet都无法匹配到路径时，`DefaultServlet`会接手，将其视为请求静态资源，然后把对应文件的内容放到请求体，并填充请求头的`Content-type`字段，进行返回。

配置文件：`web.xml`

![image-20240918123901239](https://my-pic.miaops.sbs/2024/09/image-20240918123901239.png)

![image-20240918124020933](https://my-pic.miaops.sbs/2024/09/image-20240918124020933.png)