TODO：**把busi-biz模块重新在父工程的pom中加回去**



## 前置

### 启动

http://localhost:48080/  "msg": "账号未登录"

接口文档地址： http://localhost:48080/doc.html#/home



### 项目结构

> TD：为什么可以这么做

![image-20240103145433257](https://s2.loli.net/2024/01/03/P4SNfkyoeZawC3z.png)



例子： system-Notice controller service vo/eo

**MapStruct:实现对象与对象之间的转换** : 本质是代码生成，生成在biz的convert目录下



package:

- api: 模块调用， pom引入api包， 诸如api的bean
- biz：实现（业务相关）

api包的结构：
![](https://s2.loli.net/2024/01/03/aSPK9NiU8JRcL2n.png)

api包定义接口，实现还是在biz的api目录；和controller类似，只不过controller对客户端暴露，api对其他模块暴露。

[biz包的结构](https://doc.iocoder.cn/project-intro/#_3-yudao-module-xxx)

整体架构：

![image-20240103153013348](https://s2.loli.net/2024/01/03/bpqMYk6XrIf5AdS.png)



### 添加功能与模块

[新功能](https://doc.iocoder.cn/new-feature/)：

可以通过代码生成功能生成的代码，来学习如何写crud。

可以做初始化，如果需要修改，建议还是手动修改。

[新模块](https://doc.iocoder.cn/module-new/)：

如果在swagger文档里没看到新模块的controller

注意添加到serverApplication的扫描包



## 登录

![image-20240103162005574](https://s2.loli.net/2024/01/03/TdMXP8DQp9n7zKm.png)

SpringSecurity：做如权限，过滤等全局控制

OAth2：实现登录，方便一些



登录方式： 账号密码验证码，手机，第三方

Controller跳过登录过程： `@PermitAll`



有开启验证码，参会传递code和uuid

![image-20240103163416943](https://s2.loli.net/2024/01/03/f4ymWhpMQl9KuGO.png)

> 问题：什么是参数校验



**为什么短信验证码不存在redis，而是存在数据库：**

为了方便实现限制操作：每天，每小时，每个ip能发多少条短信



**user_type是为了复用表结构**：用户user和会员member



**生成令牌：**

- OAuth2的设计：提高一定的安全性
  - `system_oauth2_access_token`：访问令牌，短过期时间
  - `system_oauth2_refresh_token`：刷新令牌，长过期时间

![image-20240103171503549](https://s2.loli.net/2024/01/03/dEkx38zR4u1rBoq.png)



**校验令牌：**

`cn.lntd.venues.framework.security.core.filter.TokenAuthenticationFilter`

用oauth2生成token（accesstoken和freshtoken）

accsstoken包含如下内容：

![image-20240104135157729](https://s2.loli.net/2024/01/04/7deNnvEPQ2CJuxp.png)

校验用户类型，防止拿到token直接访问后台

去查redis，没有还会查数据库（误删，驱逐策略）

![image-20240103171440087](https://s2.loli.net/2024/01/03/PTFKQCwNXVSYIrh.png)



**刷新令牌**

访问令牌过期或泄漏了，调用刷新令牌接口。

生成新的访问令牌和刷新令牌（特殊的“登录”），成功则用户继续操作，失败则返回登录页。

前端如何感知访问令牌过期：返回401；过期时发出的操作怎么办：先存然后callback

![image-20240103171859768](https://s2.loli.net/2024/01/03/GMbWuLCwVtiA6aY.png)



> OAuth2在整个过程中的作用是什么



**mock登录：**

`security:cone:filter:TokenAuthenticationFileter`:doFilterInternal和mockLoginUser

![image-20240103174054860](https://s2.loli.net/2024/01/03/osqXf57FtpzlIcU.png)



判断一个url是否需要认证：

![image-20240103175334696](https://s2.loli.net/2024/01/03/1aRdyQlqL5TjpsM.png)



**登出：注意复用枚举/常量就好**

![image-20240103165300291](https://s2.loli.net/2024/01/03/9lV4nALBKerwxsj.png)





## 功能权限

实现： `permmsion`包

![image-20240103181252696](https://s2.loli.net/2024/01/03/seBFwduSbiyXoMf.png)







*RBAC(Role-Based Aceess Control)*

![image-20240103181451793](https://s2.loli.net/2024/01/03/vdTDpoFiJ2LPMB8.png)

*ABAC(Attribute-Based Access Control)* ：本项目没有使用



**菜单[权限]：**

表结构设计

`menue_type`： 1目录，2菜单，3操作权限

![image-20240103182134890](https://s2.loli.net/2024/01/03/mSrqATKokEG73sH.png)



![image-20240103182925227](https://s2.loli.net/2024/01/03/n6xMQBN7vH5Z3aO.png)



实现：

- 后端：注解 `@PreAuthorize(@ss.hasPermission("system:user:list")`

调用`system:api:permmsion:PermissionApiImpl`:*hasAnyPermissions*

如何获取到用户的角色和角色对应的权限呢

（缓存中`@Cacheable(value = RedisKeyConstants.PERMISSION_MENU_ID_LIST, key = "#permission")`，见下文）

> ruoyi是从SpringSecurity的安全上下文中取出来的，因为已经把权限集成到SpringSecurity中了

@hasPermission @hasAnyPermission @hasRole @hasAnyRoles

- 前端：标签 `v-hasPermi`



创建：

`system:permission:MenuController`:*initLocalCache+@PostConstruct*，初始化缓存【内存】

菜单会缓存到本地，然后菜单变更的时候，会刷新缓存并发送MQ通知，见*createMenu*



**角色：**

表结构： `system_role`，type角色类型（内置，自定义）， code角色标识（@PreAuthorize(“@ss.hasRole(”super_admin”)）



**角色赋予权限**：

关联表，`system_role_menu`表-`RoleMenuDO`实体

- `list-role-menus` 获得角色拥有的菜单编号
- `assigin-role-menu` 赋予角色菜单

依然有缓存



**设定用户的角色：**

同上

`list-user-roles` 和 `assigin-user-role`



**动态菜单与按钮权限**

类ruoyi

![image-20240103210832012](https://s2.loli.net/2024/01/03/6zwa2myOYUPs4CZ.png)



> 哪些url无需认证？

## 数据权限

1. 能重写sql，具备添加where条件的能力
2. 可以根据规则生成where条件，实现扩展

![image-20240203131314447](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240203131314447.png)



![image-20240115121632916](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240115121632916.png)



## 多租户

开关：

- 后端：`yudao.server.tenant.enable=false`
- 前端：`VUE_APP_TENANT_ENABLE = false`

不需要多租户的功能：

- 数据表不添加tenant_id字段
- 配置application.yml中`ignore-tables`与`ignore-urls`
- 全局功能时可能会用到： `@TenantIgnore`，见APO与Utils小节



核心问题：

![image-20240115122652613](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240115122652613.png)

### DB层封装

**可以视为一种特殊的数据权限【只能看到自己租户的数据】**

选用的租户方案：共享数据表（√）， 分库分表（×）

需要使用tenant_id，DAO继承`TenantBaseDO`

如何在sql中插入tenant_id：mp的多租户插件：

- 创建Interceptor

![image-20240115124102019](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240115124102019.png)

- 添加到Interceptor chain

![image-20240115124240532](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240115124240532.png)





### Redis封装

类似于DB的共享数据库： Redis Key标识 `user:1024` -> `user:1:1024`

![image-20240115132234220](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240115132234220.png)



![image-20240115132401978](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240115132401978.png)



![image-20240115132514506](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240115132514506.png)



### Web与Security封装

`TenantContextHolder`：租户上下文Holder

- `TENANT_ID`：租户编号
- `IGNORE`：是否忽略租户



**Web：**

`cn/lntd/venues/framework/tenant/core/web/TenantContextWebFilter.java`

前端输入租户名，调用 `get-id-by-name`，得到租户id

放入请求头中

后端Filter解析该请求头，将tenant_id放入`TenantContextHolder`上下文中



**Security：**

`cn/lntd/venues/framework/tenant/core/security/TenantSecurityWebFilter.java`

1. 登陆的用户，校验是否有权限访问该租户，避免越权问题。

2. 如果请求未带租户编号，检查是否是忽略的url，如果不是，则不予访问
3. 检查租户是否合法，例如禁用，过期



配置：`cn/lntd/venues/framework/tenant/config/LntdvenuesTenantAutoConfiguration.java`



### Job层

[添加Job示例：](https://doc.iocoder.cn/job/#_2-3-%E9%85%8D%E7%BD%AE%E4%BB%BB%E5%8A%A1)

- 编写执行函数： `cn/lntd/venues/module/system/job/DemoJob.java`
- 系统中添加crond



多租户执行： `@TenantJob`

原理：AOP。

对于有该注解注解的定时方法，获取系统租户id，对于每一个租户，开一个线程执行该定时任务

![image-20240115153633665](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240115153633665.png)

注册为Bean

![image-20240115153825289](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240115153825289.png)



### MQ与Async

TenantContextHolder只在一个线程中可以获取，无法跨线程

**MQ：**

- 线程一发送消息，线程二收到消息时，不知道线程一的租户id
- 把tenant_id埋在消息里，作为消息的一部分发出去，接收方解析

![image-20240115154550498](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240115154550498.png)



`cn/lntd/venues/framework/tenant/core/mq/rabbitmq/TenantRabbitMQMessagePostProcessor.java`



**Async:**

异步线程池，问题同上：异步场景，ThreadLocal丢失

线程是基于阿里的TTL线程： `import com.alibaba.ttl.TransmittableThreadLocal;`

1. TenantContextHolder使用TransmittableThreadLocal `cn/lntd/venues/framework/tenant/core/context/TenantContextHolder.java`
2. 包装执行器，将Runnable包装成TtlRunnable `cn/lntd/venues/framework/quartz/config/LntdvenuesAsyncAutoConfiguration.java`



### AOP与TenantUtils

**AOP:**

有些场景下，需要忽略租户，处理所有租户的逻辑，主要是一些全局功能：如个定时任务，读取所有数据，进行处理。

- 实现注解`@TenantIgnore`：`cn/lntd/venues/framework/tenant/core/aop/TenantIgnoreAspect.java`

- 注册到Springboot： `cn/lntd/venues/framework/tenant/config/LntdvenuesTenantAutoConfiguration.java`

  ```java
  @Bean
  public TenantIgnoreAspect tenantIgnoreAspect() {
      return new TenantIgnoreAspect();
  }
  ```



**TenantUtils：**

实现了`execute`方法：使用指定的租户，执行相关逻辑

`cn/lntd/venues/framework/tenant/core/util/TenantUtils.java`



### 租户业务

![image-20240116011740223](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240116011740223.png)

新建租户：

- 往`system_tenant`表中添加租户信息
  - 关联租户套餐id
  - 创建并关联该租户下的管理员用户
  - 创建该租户对应的角色
  - 关联管理员用户与租户角色
  - 将套餐权限信息同步到租户角色权限信息[system_role_menu]

更新租户信息：套餐权限`system_tenant_package`同步到角色权限

- 创建租户时同步
- 更新租户套餐时同步
  - 角色本身是租户管理员，直接改变权限
  - 角色本身不是租户管理员，原有的权限与租户套餐权限取交集

![image-20240116012134430](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240116012134430.png)



`void handleTenantInfo(TenantInfoHandler handler)函数`：

传一个handler，用当前租户id执行。

```java
@Override
    public void handleTenantInfo(TenantInfoHandler handler) {
        // 如果禁用，则不执行逻辑
        if (isTenantDisable()) {
            return;
        }
        // 获得租户
        TenantDO tenant = getTenant(TenantContextHolder.getRequiredTenantId());
        // 执行处理器
        handler.handle(tenant);
    }
```

![image-20240116012553955](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240116012553955.png)



## Web组件

### 统一前缀与响应

基于分包添加前缀

`cn/lntd/venues/framework/web/config/LntdvenuesWebAutoConfiguration.java`

![image-20240116013704602](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240116013704602.png)

配置：

![image-20240116013719755](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240116013719755.png)





全局响应格式：`cn/lntd/venues/framework/common/pojo/CommonResult.java`



### 全局异常处理

`cn/lntd/venues/framework/web/core/handler/GlobalExceptionHandler.java`



`@ControllerAdvice`+`@ExceptionHandler`：将异常转化为对应的 CommmonResult

兜底的Exception处理：记录异常日志， infra_error_log表

处理日志中的异常： 基础设施-API日志-错误日志



处理的都是MVC异常，对于Filter产生的异常，直接定义一个全量的Exception处理：`allExceptionHandler`



### 全局错误码

1. 系统级别： `cn/lntd/venues/framework/common/exception/enums/GlobalErrorCodeConstants.java`

2. 业务级别：

   - 规范：![image-20240116102723765](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240116102723765.png)

   - 具体定义：`cn/lntd/venues/module/system/enums/ErrorCodeConstants.java`



如何统一加载与更新：`cn/lntd/venues/framework/errorcode/core`

- generator：加载`application.yml`配置类，写入到system服务[system_error_code表]

  ![image-20240116120833463](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240116120833463.png)

  

- loader：每隔60s拉取一次错误码信息，查看是否需要更新；把错误码写入MESSAGE全局变量，供`ServiceExceptionUtil`使用



错误码线上管理：系统管理-错误码管理



**MVC框架一般响应流程：**

正常返回则调用 `success(Object)`

出错则直接抛异常，异常会被全局异常捕获，转化为统一响应：

- `throw exception(ErrorCode)`：ErrorCode对象无需填充参数

- `throw exception(AUTH_LOGIN_CAPTCHA_CODE_ERROR, response.getRepMsg());` ：ErrorCode对象需要填充参数

  ![image-20240116105022763](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240116105022763.png)

  {}是占位符

  ![image-20240116105030460](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240116105030460.png)

**MVC框架一般请求流程：**

- 确定请求类型： VO，`@RequestBody`
- 参数校验： 类上`@Validated`；参数上`@Valid`(Bean)，`@NotNull`；`@AssertTrue`校验与自定义注解



### 全局序列化与反序列化

`cn/lntd/venues/framework/jackson/config/LntdvenuesJacksonAutoConfiguration.java`

![image-20240302140835406](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240302140835406.png)





## Tricks

mysql没有数组类型，把Set进行Jason化，例子：用户信息表的岗位编号字段
![image-20240103162606808](https://s2.loli.net/2024/01/03/wZ2jLX1hodePuU6.png)

> 问题：如何实现数据库数据的Json解析



配置无需携带租户编号 `application.yml` urls,tables

![image-20240106110537793](https://s2.loli.net/2024/01/06/Rvn6VTIDjxsW8S4.png)

从请求中解析出tenant_id

![image-20240106125404873](https://s2.loli.net/2024/01/06/MukpUKYsgWHBheG.png)



对象类型转换：

![img](https://s2.loli.net/2024/01/10/GP4dve7jDMZgH3z.jpg)

