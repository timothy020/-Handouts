## 验证码

后端： `ruoyi-admin:web:controller:common:CaptchaController`

- 收到前端验证码请求，生成一个表达式和uuid

- 把表达式的答案，记录在redis里，名称为`captcha_codes:uuid`，有效期2min

  ![image-20231215141129745](https://s2.loli.net/2023/12/15/nZiruw7tm2kIDj6.png)

- 把表达式转换为图片，连同uuid，发送给前端

- 登录验证时，把前端发送过来的答案和uuid，与redis里的正确答案比较，一致则验证通过

  ![image-20231215141312851](https://s2.loli.net/2023/12/15/a8wZV6vsDyfBxtL.png)



前端：

- 初始化时调用方法获取验证码和cookie

`login.vue`：

![image-20231215140213856](https://s2.loli.net/2023/12/15/5vLWaJzslkQwVbK.png)

![image-20231215140240886](https://s2.loli.net/2023/12/15/Lzs7CvO8MiP1maZ.png)

- 前端对axios请求的封装： `utils.request.js`

  ![image-20231215141716775](https://s2.loli.net/2023/12/15/7VA6BE8aGiSKHY2.png)

baseURL，配置在**.env.development**中，这就解释了为什么请求中会带有 */dev-api*前缀

![image-20231215141806559](https://s2.loli.net/2023/12/15/NM4EAuS9RK175kL.png)

![image-20231215141901786](https://s2.loli.net/2023/12/15/GhzxVIBRkYWcEbN.png)

- 前端反向代理解决跨域

`vue.config.js`：路径重写 

> http://localhost:81/dev-api/captchaImage -> http://localhost:81/captchaImage 
>
> -> http://localhost:8080/captchaImage

[详细文档](https://cli.vuejs.org/config/#devserver-proxy)

![image-20231215142742436](https://s2.loli.net/2023/12/15/VePx2ZpAFoQRl7g.png)



## 登录

前端：

- 组件绑定**handlerlogin**，内部调用actions的**Login**，再异步调用**login**，内部调用`request.js`封装的`request`，发送axios请求
- 再经过前文所说的反向代理，到达后端controller

![image-20231215144059139](https://s2.loli.net/2023/12/15/1Ne7kzL6aKFUhIo.png)

![image-20231215144039431](https://s2.loli.net/2023/12/15/AHFGd6nXlwKCYUT.png)

![image-20231215144323686](https://s2.loli.net/2023/12/15/VHEFMiobDzL8OCf.png)

后端：

`ruoyi-admin:SysLoginController`中的**@PostMapping("/login")** 

-> `ruoyi-framework:service:SysLoginService`中的**login**

![image-20231215151849515](https://s2.loli.net/2023/12/15/6BTh9IyFzjERMsC.png)

![image-20231215144948531](https://s2.loli.net/2023/12/17/wHqzu4nD1JoT87b.png)

- 校验验证码： **validateCaptcha**

- 校验用户名和密码： Spring Security

- 生成token: **tokenService.createToken**

  ![image-20231215150806676](https://s2.loli.net/2023/12/15/KFBJq9TLU4sHyoi.png)

  - **refreshToken**：把用户信息存入redis：键为*login_token:uuid*， 有效期30min

    ![image-20231215151447445](https://s2.loli.net/2023/12/15/UaJ3g7Ib4siFNTq.png)

    ![image-20231215151536688](https://s2.loli.net/2023/12/15/31cJqQEFmYRaupH.png)

  - **createToken(claims)**：生成JWT令牌，JWT内保存的是uuid，返回给前端。

    ![image-20231215151807725](https://s2.loli.net/2023/12/15/MQn3fmVoXAkILRP.png)

- 前端在回调函数中把token保存到**Cookie**中。之后前端在请求时只需从cookie里取出token，后端根据token解析出uuid，再根据uuid从redis里找到登录信息，即可完成校验。

  ![image-20231215152455508](https://s2.loli.net/2023/12/15/wkLYqdus5iSrcK4.png)

- 记录日志

  - `AsyncManager` 异步任务管理器，结合线程池，异步记录日志。登录信息日志sys_logininfor
  - `recordLoginInfo`：改变用户登录状态sys_user



## 前端如何携带token，后端如何解析token？

前端：

`request.js`把axios请求封装为`request`，同时设置了拦截器。

每次发送请求的时候，都会从headers中取*isToken*字段，查看该方法是否需要携带token。

- 如果需要携带token（默认需要token），就在请求中设置请求参数 *Authorization*，并带上token

![image-20231215153349155](https://s2.loli.net/2023/12/15/5avXfqzhADF6eZS.png)

![image-20231215153722121](https://s2.loli.net/2023/12/15/7dA1xFhQ42gG6Xl.png)

- `login.js`中登录，注册以及获取验证码的方法的headers里的 *isToken*字段都设置为了 false，这就是为什么**登录和注册的时候不需要验证token**

![image-20231215153910792](https://s2.loli.net/2023/12/15/lesiF198pmkIqta.png)



后端：

`ruoyi-framework:config:SecurityConfig`内添加了JWT过滤器

![image-20231215155804139](https://s2.loli.net/2023/12/15/dpPr6n2fwvN7sMI.png)

具体定义在`ruoyi-framework:security:filter:JwtAuthenticationTokenFilter`

- 对于没有`Authorization`字段的请求，直接放行
- 对于有`Authorizatoin`字段的请求，校验token是否合法，合法则从redis中取出用户信息，然后刷新token过期时间，校验用户名与密码与权限验证[结合Spring Security实现]

![image-20231215160553797](https://s2.loli.net/2023/12/15/frdWtVQqvIybgLB.png)



## ruoyi权限管理

![hnBho.png](https://i0.imgs.ovh/2024/01/15/hnBho.png)

若依的权限管理底层是基于Spring Security进行的

关于Spring Security，可以参考 [这篇博客](https://zhuanlan.zhihu.com/p/342755411?utm_medium=social&utm_oi=1343915562263547904)



### 在何时获取权限？登陆时

其实在登录时就已经获取到了。

`ruoyi-framework:web:service:SysLoginService`

![image-20231215171134798](https://s2.loli.net/2023/12/15/JTkC9qp6HANFDjU.png)

![image-20231215202744027](https://s2.loli.net/2023/12/15/YfpRHmKzuMilPE3.png)

![image-20231215202808704](https://s2.loli.net/2023/12/15/fAI9yh7ENLeiKGj.png)

![image-20231215202832905](https://s2.loli.net/2023/12/15/cmvCy3lBGEikTzU.png)

一路跟下去，其实就是sql查表

![image-20231215202848673](https://s2.loli.net/2023/12/15/fxRGEVohJ8g2INM.png)

把这个sql放到navicat里面执行一下【用ry用户效果更明显】：

![image-20231215203045286](https://s2.loli.net/2023/12/15/6XKzUMyN9BvR4Iu.png)

> 关联查询了 sys_menu 和 sys_role_menu
> 其他和权限管理有关的数据表： sys_user sys_role sys_user_role sys_role_dept

得到的就是权限字符串：

![image-20231215203107554](https://s2.loli.net/2023/12/15/8dKiTWPkoavALzg.png)

保存到了redis里：

![image-20231215203251605](https://s2.loli.net/2023/12/15/WPxj53U6fYMgZwl.png)



### 后端如何进行权限校验？@PreAuthorize

`@PreAuthorize`是Spring Security提供的一个注解，用于在方法执行前验证权限

开启方式： `ruoyi-framework:config:SecurityConfig`中的`@EnableGlobalMethodSecurity`注解

![image-20231215203854601](https://s2.loli.net/2023/12/15/nd6QH1hNKBRUgkw.png)

注解的具体说明可以参考： [这篇博客](https://blog.csdn.net/chihaihai/article/details/104678864)

`@PreAuthorize`的value值写SpEL表达式，并且返回值为true则可以执行方法，返回值为false则表示不能执行方法。

SpEL表达式可以通过“@”来引用bean。

```java
@PreAuthorize("@ss.hasPermi('system:user:list')")
```

`ss`这个bean定义在`ruoyi-framework:web:service:PermissionService`

内部其实就是判断调用方法的权限字符串是否在该登录用户的权限集里面【权限集保存在SpringSecuriy的安全上下文中，也暂存到了redis中】

![image-20231215204620056](https://s2.loli.net/2023/12/15/uT1DJSRbU4VFnfh.png)

如果是超级管理员 \*:\*:\* 则直接放行，否则进行上述所说的判断

![image-20231215204845249](https://s2.loli.net/2023/12/15/p9K6oAOPawin7xJ.png)



测试：把`ruoyi-admin:web:system:SysUserController`内的**/list**请求路径的权限改为：

```java
@PreAuthorize("@ss.hasPermi('system:user:list1')")
@PreAuthorize("@ss.hasPermi('system:user:*')")
```

![image-20231215205549321](https://s2.loli.net/2023/12/15/KNDlagrH26jfzn4.png)

都会触发报错：

![image-20231215205805293](https://s2.loli.net/2023/12/15/1XFYdv7TWkNBnlZ.png)



### 权限管理在前端的体现

#### 根据角色权限获取菜单

前端在调用为**login**方法登录后，会立即调用 **getInfo**获取用户信息 和 **getRouters** 获取该登录用户对应的动态菜单项

![image-20231215211235780](https://s2.loli.net/2023/12/15/eZagGtckfUrLw3n.png)

**这两个请求是在哪里发出的？全局路由配置`permmison.js`**

每次发出请求前都会判断是否获取过用户信息和菜单，如果没有，就会调用 **getInfo**和**getRouters**去获取。

获取完以后会进行Vuex全局存储，以便后续查询。【继续追踪GetInfo即可，不在赘述】

![image-20231215211359666](https://s2.loli.net/2023/12/15/MBCoziGqXPWxT2Y.png)

后端controller:

![image-20231215212408839](https://s2.loli.net/2023/12/15/vL8M4TZpBcJfHul.png)

**permissoinService.getMenuPermission**在登录时获取权限处已经提到过，此处调用的是同一个方法，之前调用的结果存到了redis里，此处的调用结果返回给了前端，存储到Vuex中。

![image-20231215213623219](https://s2.loli.net/2023/12/15/GpJLcN1ET7iZ59q.png)

后端controller:

![image-20231215213019055](https://s2.loli.net/2023/12/15/nemRl8p6sQEFhBw.png)

内部的核心逻辑是：关联查询权限与菜单表，然后根据返回结果递归构建层级菜单

把底层sql放到navicat里面执行，结果如下：

![image-20231215213237358](https://s2.loli.net/2023/12/15/GxcYNpB1gQkZa4T.png)

根据 *menu_id*和*parent_id*明确层级关系，递归构建出层级菜单

![image-20231215213343687](https://s2.loli.net/2023/12/15/dvQJnVKR9uClzp5.png)

![image-20231215213726041](https://s2.loli.net/2023/12/15/ZCGlpBDA8NQW9M1.png)



#### 根据权限显示按钮

ry用户只会显示自己部门的相关信息，且由于ry用户具有用户管理的增删改查与导入导出的权限，所以这些按钮才会显示否则不会显示。

前端是如何根据用户权限动态控制这些组件的显示呢？

![image-20231215213840909](https://s2.loli.net/2023/12/15/cpEaem9TkP1BgvC.png)

>  若依自定义了一个标签`v-hasPermi`来依照权限控制组件显示

`views:system:user:index.vue`中：

![image-20231215214245376](https://s2.loli.net/2023/12/15/SJ2gpPQzfwo1xBU.png)

比如用户管理中的“新增”按钮，就需要 “system:user:add” 权限，有则显示该按钮，无则不显示



自定义的组件又是在哪里定义和导入的呢？

在 **directives**目录中定义，在**main.js**中导入：

![image-20231215214803948](https://s2.loli.net/2023/12/15/b8AS9W6HUXTxsY2.png) 

从上面可以发现，自定义指令是以插件的形式包装的，Vue.use方法会自动执行插件的install方法：

![image-20231215214833871](https://s2.loli.net/2023/12/15/iBcDV4uTahP5IpF.png)

可以看出，对象里面只有一个方法inserted，也就是在被绑定元素插入父节点时调用，这里正好可以判断有没有权限.

**有就插入，没有就直接移除dom即可。**

![image-20231215220514547](https://s2.loli.net/2023/12/15/iOueg5LwpajHVbq.png)



### 使用@Anonymous绕过权限管理

`@Anonymous`是ruoyi自定义的一个注解，可以定义的方法上，也可以定义在Controller类上，加上注解后，可以直接绕过权限管理，直接请求到后台方法

```java
/**
 * 匿名访问不鉴权注解
 * 
 * @author ruoyi
 */
@Target({ ElementType.METHOD, ElementType.TYPE })
@Retention(RetentionPolicy.RUNTIME)
@Documented
public @interface Anonymous
{
}
```



![image-20231215223402936](https://s2.loli.net/2023/12/15/EyZlT7jQnNevUuA.png)

直接访问：

![image-20231215223754147](https://s2.loli.net/2023/12/15/RM2EdAzU9p8eb7W.png)

前端反向代理访问【前端端口为81】：

![image-20231215223806153](https://s2.loli.net/2023/12/15/WJK3CMQ6xDlvTse.png)

如果不加注解，显示认证失败，无法访问：

![image-20231215223654852](https://s2.loli.net/2023/12/15/19VBIr4ifOyCgsA.png)





如何实现的？`ruoyi-framework:config:properties:PermitAllUrlProperties`

- 获取所有RequestMapping的Bean，检查类或方法上有没有 `@Anonymous`注解
- 如果有，加入到urls数组中，`SecurityConfig`类会把urls数组中的url设置为**permitAll()**，即允许访问

![image-20231215225102464](https://s2.loli.net/2023/12/15/csjZVkwRXTmrCJv.png)

![image-20231215225518015](https://s2.loli.net/2023/12/15/hfkKImXnW1eLwUj.png)



## ruoyi数据权限

AOP切入，和日志一样

![image-20240115095608246](https://s2.loli.net/2024/01/15/3ortLjfBm94dAGz.png)

本质是在sql语句中拼接一句类似与 `and u.userid = 1`这样的条件

- 条件存放在哪里：BaseEntity类中的params成员

- params在哪里构建的？ AOP中，切点是注解`@DataScope`
- 在哪里添加param：xml映射文件中

![image-20240115104553460](https://s2.loli.net/2024/01/15/WzA3vliPE1I9nYd.png)



如何自己添加数据权限： [参考](https://mp.weixin.qq.com/s/RW4IKz0jMZWLDema2LNgrg)

- 代码生成
- 在xml映射文件中添加 `left join`进行关联，where中添加上 `${params.dataScope}$`
- Service层添加注解 `@DataScope(...)`







查本部门及其子部门：

`find_in_set（x,array)`：判读x是否在array里面，在返回索引（1开始），不在返回0.

![image-20240115101539682](https://s2.loli.net/2024/01/15/5nFUZycdPKHox4w.png)

递归关系在数据表中体现：

![image-20240115101716434](https://s2.loli.net/2024/01/15/1IzxUK3SXOW7ehq.png)





需要有数据权限：

- 实体类必须继承基本实体 `BaseEntity`
- 需要再Service层写注解： `@DataScope(deptAlias = "d", userAlias = "u")`





## Tricks

### 后端实现分页

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

![image-20231128161818748](https://s2.loli.net/2023/12/15/qy6jn8xVAJsPSdD.png)

前端请求参数： `pageNum`与`pageSize`

![image-20231215232303821](https://s2.loli.net/2023/12/15/gBNod8ht3HFpQJ5.png)

如果Controller只是一些简单的sql，直接调用startPage()即可分页

![image-20231215232720854](https://s2.loli.net/2023/12/15/DWu49f6lHOYNUoM.png)

> `BaseController`中还提供了其他基础方法，详情见 `ruoyi-common:core:controller:BaseController`



### 添加新模块

新建模块，导入 `ruoyi-common`，内部就包含springboot，web等依赖

![image-20231216130918624](https://s2.loli.net/2023/12/16/irHn8qw2Xbce3VN.png)

`ruoyi-admin`导入自定义模块

![image-20231216130946914](https://s2.loli.net/2023/12/16/mCz9sIBpaN3UVYo.png)

新模块的Controller写在`com.ruoyi`包下，启动`ruoyi-admin`即可访问到自定义的Controller

![image-20231216131111825](https://s2.loli.net/2023/12/16/N5rlJ3hA7m1VgHd.png)



### 代码生成

ruuoyi提供代码生成模块，可以根据提供的数据表[单表，树表，主子表]，自动生成前后端增删改查的代码。

下面演示单表的自动生成：

先导入示例sql创建数据表：

```java

CREATE TABLE `ry-vue`.`testSingle`  (
  `id` bigint NOT NULL AUTO_INCREMENT COMMENT '编号',
  `username` varchar(255) NULL COMMENT '用户名',
  `pwd` varchar(255) NULL COMMENT '密码',
  `sex` char(1) NULL COMMENT '性别',
  `telephone` varchar(255) NULL COMMENT '电话',
  `email` varchar(255) NULL COMMENT '邮箱',
  `brithday` date NULL COMMENT '生日',
  `avatar` varchar(255) NULL COMMENT '头像',
  `description` longblob NULL COMMENT '描述',
  `del_flag` char(1) NULL COMMENT '逻辑删除标志',
  `status` char(1) NULL COMMENT '状态',
  `create_by` varchar(255) NULL COMMENT '创建者',
  `create_time` datetime NULL COMMENT '创建时间',
  `update_by` varchar(255) NULL COMMENT '更新者',
  `update_time` datetime NULL COMMENT '更新时间',
  `remark` varchar(500) NULL COMMENT '备注',
  PRIMARY KEY (`id`)
);
```

点开代码生成，导入数据表，设置相关的信息

![image-20231216142958883](https://s2.loli.net/2023/12/16/WcpExh6mKvjn8e5.png)

![image-20231216140350442](https://s2.loli.net/2023/12/16/Y1Dm4XAUgs8KEoV.png)

![image-20231216143005465](https://s2.loli.net/2023/12/16/tGmMFCYvoSX8W6L.png)

之后点击生成代码，即可下载生成的代码的压缩包。

![image-20231216143152080](https://s2.loli.net/2023/12/16/zQhGrjwSy5O9n7Y.png)

sql代码执行后的结果：`sys_menu`

![image-20231216145028120](https://s2.loli.net/2023/12/16/4aOtKS7RPkp3QcH.png)

把所有代码导入到项目后，即可正常进行增删改查：

- 可以在**系统管理-菜单管理**，给刚添加的菜单项的图标；

- 生成代码时，生成信息下选择的上级菜单是**系统工具**，所以是该菜单的子菜单

![image-20231216143242332](https://s2.loli.net/2023/12/16/wb1O2ZsxmoBYGDC.png)

![image-20231216150447532](https://s2.loli.net/2023/12/16/1bnlh5CHBPUAXk2.png)

*树表和主子表的流程大体相同，不再赘述。*

> 代码生成模块的代码或许在很多时候不符合我们的使用预期，但是可以帮助我们明确如何往ruoyi系统里添加一个菜单功能：
>
> **写好前后端代码，然后把相关菜单信息填入sys_menu表中**

此时刚添加的菜单只能admin用户访问，如何让ry用户也能访问？ 

设置ry用户的菜单权限： `sys_role_menu`

添加这三行，就给ry用户【用户id为2，见`sys_user`】，添加了该菜单项的查询和新增功能。【结合`sys_menu`表来看】

![image-20231216145816919](https://s2.loli.net/2023/12/16/Zv8yNz4JcgjP1Ih.png)

**Test:testsingle:add**权限也有，截图没截上

![image-20231216150117452](https://s2.loli.net/2023/12/16/mewM8GqlRI2rCTx.png)



**测试单表生成**菜单可以正常显示，且ry用户只具备list与add权限。修改，删除和导出按钮都不显示，具体解析见上文“ruoyi权限管理”。

![image-20231216150227931](https://s2.loli.net/2023/12/16/6nXFoKhbwT21DR9.png)





### 验证码开关

前台修改：

![image-20231216151333400](https://s2.loli.net/2023/12/16/W4py2Rq5nPjg7SJ.png)



后台修改：`sys_config`

![image-20231216151509568](https://s2.loli.net/2023/12/16/6blSmPCe2s9Lfzo.png)

![image-20231216151520204](https://s2.loli.net/2023/12/16/qQi91S6yVEg8Z3j.png)



