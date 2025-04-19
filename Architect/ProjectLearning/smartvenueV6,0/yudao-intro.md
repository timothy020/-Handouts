## 说明

本文档主要是对项目结构以及与开发流程中的相关问题进行简要描述，如果需要了解其他具体内容，可参考下列文档：

1. [芋道开放文档](https://doc.iocoder.cn/intro/)
2. [需求文档](https://sfspgrzi0t.feishu.cn/docx/WRFGd65Y0oFOAPxfokzc9dJcnMh)

2. [概要设计V2.0](https://sfspgrzi0t.feishu.cn/docx/UkcXdVKAyo12Clxy1klc2l1rnXe)
3. [数据库与接口设计文档](https://sfspgrzi0t.feishu.cn/docx/Ws06dqGAaoVwuuxRe5SceiIlnjd)



## 开发流程与工具

| 开发流程         | 相关文档与工具                                               | 备注                                  |
| ---------------- | ------------------------------------------------------------ | ------------------------------------- |
| 明确需求         | 需求文档、原型图                                             |                                       |
| 设计表结构与接口 | 需求文档、数据库与接口文档                                   | 建表申请，表名lntdvenues_sv_xxx       |
| 开发             | 概要设计V2.0、数据库与接口文档、git                          | git pull-git commit-git pull-git push |
| 自测             | [API Fox](https://doc.iocoder.cn/api-doc/)/PostMan/[Knife4j](http://60.204.188.168:48081/doc.html#/home) |                                       |
| 写接口文档       | 数据库与接口文档                                             | 描述接口的设计，传参，返回值          |
| 联调             | CICD                                                         | 沟通时间                              |
| 测试             | 禅道                                                         | 提交测试单                            |
| 修改bug          | 禅道                                                         |                                       |



## 项目结构

![image-20240320184644764](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240320184644764.png)



### 框架结构

信息来源：[芋道开发文档](https://doc.iocoder.cn/project-intro/)

| **Maven Module**          | **作用**                     |
| :------------------------ | :--------------------------- |
| `lntdvenues-dependencies` | Maven 依赖版本管理           |
| `lntdvenues-framework`    | Java 框架拓展                |
| `lntdvenues-module-xxx`   | XXX 功能的 Module 模块       |
| `lntdvenues-server`       | 管理后台 + 用户 App 的服务端 |



1. **lntdvenues-dependencies**

该模块是一个 Maven Bom，只有一个`pom` 文件，定义项目中所有 Maven 依赖的版本号，解决依赖冲突问题。

2. **lntdvenues-framework**

该模块是 `ruoyi-vue-pro` 项目的框架封装，其下的每个 Maven Module 都是一个组件，分成两种类型：

- 技术组件：技术相关的组件封装，例如说 MyBatis、Redis 等等。

| Maven Module                                 | 作用                                                         |
| -------------------------------------------- | :----------------------------------------------------------- |
| `lntdvenues-common`                          | 定义基础pojo类、枚举、工具类等                               |
| `lntdvenues-spring-boot-starter-web`         | Web封装，提供全局异常、访问日志等                            |
| `lntdvenues-spring-boot-starter-websocket`   | WebSocket封装，提供Token认证、WebSocket 集群广播、Message 监听 |
| `lntdvenues-spring-boot-starter-security`    | 认证授权，基于Spring Security实现                            |
| `lntdvenues-spring-boot-starter-mybatis`     | 数据库操作，基于 MyBatis Plus 实现                           |
| `lntdvenues-spring-boot-starter-redis`       | 缓存操作，基于Spring Data Redis + Redisson 实现              |
| `lntdvenues-spring-boot-starter-mq`          | 消息队列，基于Redis 实现，支持集群消费和广播消费             |
| `lntdvenues-spring-boot-starter-job`         | 定时任务，基于Quartz 实现，支持集群模式                      |
| `lntdvenues-spring-boot-starter-flowable`    | 工作流，基于Flowable 实现                                    |
| `lntdvenues-spring-boot-starter-protection`  | 服务保障，提供幂等、分布式锁、限流、熔断等功能               |
| `lntdvenues-spring-boot-starter-file`        | 文件客户端，支持将文件存储到 S3（MinIO、阿里云、腾讯云、七牛云）、本地、FTP、SFTP、数据库等 |
| `lntdvenues-spring-boot-starter-excel`       | Excel 导入导出，基于 EasyExcel 实现                          |
| `lntdvenues-spring-boot-starter-monitor`     | 服务监控，提供链路追踪、日志服务、指标收集等功能             |
| `lntdvenues-spring-boot-starter-captcha`     | 验证码Captcha，提供滑块验证码                                |
| `lntdvenues-spring-boot-starter-test`        | 单元测试，基于 Junit + Mockito 实现                          |
| `lntdvenues-spring-boot-starter-banner`      | 控制台Banner，启动打印各种提示                               |
| `lntdvenues-spring-boot-starter-desensitize` | 脱敏组件：支持 JSON 返回数据时，将邮箱、手机等字段进行脱敏   |

- 业务组件：业务相关的组件封装，例如说数据字典、操作日志等等。如果是业务组件，名字会包含`biz`关键字。

| Maven Module                                          | 作用                                       |
| :---------------------------------------------------- | :----------------------------------------- |
| `lntdvenues-spring-boot-starter-biz-tenant`           | SaaS 多租户                                |
| `lntdvenues-spring-boot-starter-biz-data-permissionn` | 数据权限                                   |
| `lntdvenues-spring-boot-starter-biz-dict`             | 数据字典                                   |
| `lntdvenues-spring-boot-starter-biz-operatelog`       | 操作日志                                   |
| `lntdvenues-spring-boot-starter-biz-pay`              | 支付客户端，对接微信支付、支付宝等支付平台 |
| `lntdvenues-spring-boot-starter-biz-sms`              | 短信客户端，对接阿里云、腾讯云等短信服务   |
| `lntdvenues-spring-boot-starter-biz-error-code`       | 全局错误码                                 |
| `lntdvenues-spring-boot-starter-biz-ip`               | 地区&IP库                                  |

每个组件，包含两部分：

1. `core` 包：组件的核心封装，拓展相关的功能。
2. `config` 包：组件的 Spring Boot 自动配置。

![img](https://raw.githubusercontent.com/timothy020/pic/main/img/asynccode)

3. **lntdvenues-module-xxx**

该模块是 XXX 功能的 Module 模块，目前内置了 8 个模块。

| 项目                       | 说明       | 是否必须 |
| :------------------------- | :--------- | :------- |
| `lntdvenues-module-system` | 系统功能   | √        |
| `lntdvenues-module-infra`  | 基础设施   | √        |
| `lntdvenues-module-member` | 会员中心   | x        |
| `lntdvenues-module-bpm`    | 工作流程   | x        |
| `lntdvenues-module-pay`    | 支付系统   | x        |
| `lntdvenues-module-report` | 大屏报表   | x        |
| `lntdvenues-module-mall`   | 商城系统   | x        |
| `lntdvenues-module-mp`     | 微信公众号 | x        |

每个模块包含两个 Maven Module，分别是：

| Maven Module                | 作用                     |
| :-------------------------- | :----------------------- |
| `lntdvenues-module-xxx-api` | 提供给其它模块的 API定义 |
| `lntdvenues-module-xxx-biz` | 模块的功能的具体实现     |

> **疑问：为什么设计** **`yudao-module-xxx-api`** **模块呢？**
>
> 1. 明确需要提供给其它模块的 API 定义，方便未来迁移微服务架构。
> 2. **模块之间可能会存在相互引用**的情况，虽然说从系统设计上要尽量避免，但是有时在快速迭代的情况下，可能会出现。此时，通过只引用对方模块的 API 子模块，解决相互引用导致 Maven 无法打包的问题。

![image-20240320183516588](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240320183516588.png)

API模块有哪些内容

| 所在包  | 类                    | 作用                                |
| :------ | :-------------------- | :---------------------------------- |
| `api`   | Api 接口              | 提供给其它模块的 API 接口           |
| `api`   | DTO 类                | Api 接口的入参 ReqDTO、出参 RespDTO |
| `enums` | Enum 类               | 字段的枚举                          |
| `enums` | DictTypeConstants 类  | 数据字典的枚举                      |
| `enums` | ErrorCodeConstants 类 | 错误码的枚举                        |



4. y**udao-server**

该模块是后端 Server 的主项目，通过引入需要 `yudao-module-xxx` 业务模块，从而实现提供 RESTful API 给 `yudao-ui-admin-vue3`、`yudao-mall-uniapp` 等前端项目。

本质上来说，它就是个空壳（容器）。如下图所示：

![image-20240320184137546](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240320184137546.png)



### 业务模块结构

详见 [概要设计说明书V2.0的6.3部分](https://sfspgrzi0t.feishu.cn/docx/UkcXdVKAyo12Clxy1klc2l1rnXe)



## 开发相关组件使用

**用户系统与权限管理：**

- `@PreAuthorize("@ss.hasPermission(权限字符串)")`
- `@PermitAll`不进行权限校验
- 获取当前登录用户：`AdminUserRespDTO user = adminUserApi.getUser(SecurityFrameworkUtils.getLoginUserId());`
- 详细了解的话可阅读下列文档：芋道开发文档(用户体系，数据权限，功能权限)，概要设计文档(登录系统设计)，[若依权限系统解读](https://sfspgrzi0t.feishu.cn/docx/Wg9vdXgE8oC4wHxUQ5fcNAUOnkc)(yudao脱胎于ruoyi，二者权限管理有相似之处)



**参数校验：**

[开发文档](https://doc.iocoder.cn/validator/#_1-%E5%8F%82%E6%95%B0%E6%A0%A1%E9%AA%8C%E6%B3%A8%E8%A7%A3)

1. 接口参数类`*ReqVO`上添加 `@Valid`注解

   ![image-20240320193834435](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240320193834435.png)

2. 在参数类内添加校验注解

   - `@NotNull`：不能为null
   - `@NotEmpty`：不能为空
   - `@Length(max,min)`：被注释的字符串的大小必须在指定的范围内
   - ![image-20240320193906976](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240320193906976.png)





**异常处理与错误码：**

[开发文档](https://doc.iocoder.cn/exception/#_1-%E7%BB%9F%E4%B8%80%E5%93%8D%E5%BA%94)

异常处理流程：

1. 业务内使用`throw exception(Errocode)`抛出异常

2. 该异常会被全局处理异常处理器捕获
3. ErrorCode中的异常信息会发送到前端作为响应

相关类：

- `ErrorCode`类：cn/lntd/venues/framework/common/exception/ErrorCode.java

  - 系统ErrorCode类：cn/lntd/venues/framework/common/exception/enums/GlobalErrorCodeConstants.java

  - 业务中的ErrorCode类：cn/lntd/venues/module/business/constant/ErrorCodeConstants.java

    随着业务功能逐渐添加

- `exception`方法： cn/lntd/venues/framework/common/exception/util/ServiceExceptionUtil.java

- 全局异常处理器：cn/lntd/venues/framework/web/core/handler/GlobalExceptionHandler.java



**工具类：**

[开发文档](https://doc.iocoder.cn/util/)

1. Hutool

   `IdUtil.getSnowflakeNextId()`：生成一个主键id（由于多租户需求，数据库主键不能设置为自增，需要自己用该函数设置id字段，然后在插入数据库）

2. 对象转换

   - 简单的对象转换：`BeanUtils.toBean()`

   - 自定义类型转换，转换List等容器类型：[MapStruct](https://mapstruct.org/documentation/installation/)

     例子：cn/lntd/venues/module/business/admin/bookingrule/convert/PeriodConfigConvert.java



## 基础CRUD演示

1. 建表

   - id为Not NULL，非自增

   - 添加六个基本字段，其中`tenant-id`是为了实现多租户，见[文档](https://doc.iocoder.cn/saas-tenant/)

     这些字段不需要自己维护，框架中的MybatisPlus插件会在CRUD时自动维护，添加上即可

     ![image-20240320202705803](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240320202705803.png)



2. 代码生成

3. 建包

4. cpoy，添加错误码

5. 润色

   - 修改前缀

   - 去掉不需要的方法

   - 修改接口路径，统一格式

6. 接口自测：带上两个header

   ![image-20240320203048206](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240320203048206.png)



