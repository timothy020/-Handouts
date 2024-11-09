![image-20231212211807345](https://s2.loli.net/2023/12/12/i2X1YAMZCBgKkDR.png)

```text
com.ruoyi     
├── common            // 工具类
│       └── annotation                    // 自定义注解
│       └── config                        // 全局配置
│       └── constant                      // 通用常量
│       └── core                          // 核心控制
│       └── enums                         // 通用枚举
│       └── exception                     // 通用异常
│       └── filter                        // servlet过滤器
│       └── utils                         // 通用类处理
│       └── xss                           // XSS过滤处理
├── framework         // 框架核心
│       └── aspectj                       // 注解实现
│       └── config                        // 系统配置
│       └── datasource                    // 数据权限
│       └── interceptor                   // 拦截器
│       └── manager                       // 异步处理
│       └── security                      // 集成spring security进行权限控制
│       └── web                           // 验证码与登录验证授权相关服务
├── ruoyi-generator   // 代码生成（不用可移除）
├── ruoyi-quartz      // 定时任务（不用可移除）
├── ruoyi-system      // 系统代码
├── ruoyi-admin       // 后台服务
├── ruoyi-xxxxxx      // 其他模块
```



common：工具类

| 目录       | 功能                                                         |
| ---------- | ------------------------------------------------------------ |
| annotation | 自定义注解<br />1.@Anonyoums：匿名访问不鉴权注解<br />2.@DataScope：数据权限过滤注解<br />3.@DataSource：自定义多数据源切换注解<br />4.@Excel：自定义导出Excel数据注解<br />5.@Excels：Excel注解集<br />6.@Log：自定义操作日志记录注解。使用方式`@Log(title = "定时任务", businessType = BusinessType.EXPORT)`<br />7.@RateLimiter：限流注解<br />8.@RepeatSubmit：自定义注解防止表单重复提交 |
| config     | 全局配置<br />name：项目名称；version：版本；copyrightYear：版权年份；demoEnabled：实例演示开关；<br />profile：上传路径；addressEnabled：获取地址开关；captchaType：验证码类型 |
| constant   | 通用常量<br />1.CacheConsatns：缓存的key 常量，记录在redis中的缓存字段的名字<br />2.Constants：通用常量信息，如字符集，www主域，通用成功/失败标识等，令牌，用户权限，定时任务白名单<br />3.GenConstans：代码生成通用常量，如表类型名称，编码字段，数据库数据类型名称，前端控件名称<br />4.HttpStatus：返回状态码，如请求成功，资源已被移除，重定向，未授权<br />5.ScheduleConstants：任务调度通用常量，如执行目标key，立即触发执行，触发一次执行，执行状态码<br />6.UserConstants：用户常量信息，如用户和部门状态的状态码，字典状态码，菜单类型和组件标识，用户名密码长度限制<br /> |
| core       | 核心控制<br />1.controller：该目录下定义了`BaseController`，是若依中其他`Controller`的基类，进行web层通用数据处理，包括字符串转Date类型，设置PageHelper分页参数，设置请求排序，返回各类响应信息，获取用户缓存，获取当前请求的登录用户id和部门id<br />2.domain：该目录下定义实体类<br />model:登录鉴权相关：用户登录，注册实体对象，登录用户身份权限对象<br />entity:基本实体类：用户，部门，菜单，角色，字典数据<br />其他：Ajax请求封装，Entity基类，响应信息主体,Treeselect树结构实体类<br />3.page：该目录下定义分页相关结构。分页请求参数PageDomain，分页后响应的结果TableDataInfo，分页后表格数据处理TableSupport<br />4.RedisCache：redis工具类，封装RedisTemplate，用来操作redis<br />5.text：该目录下定义处理字符相关操作。字符集处理对象，类型转换器，字符串格式化 |
| enums      | 通用枚举<br />1.BusinessStatus：操作状态。成功，失败<br />2.BUsinessType：业务操作类型。增删改查，导入，清空等<br />3.DataSourceType：数据源类型。主库，从库<br />4.HttpMethod：http请求方法<br />5.LimitType：限流类型。全局，根据Ip<br />6.OpentorType：操作人类别。后台，手机端，其他<br />7.UserStatus：用户状态。正常，停用，删除 |
| exception  | 通用异常<br />1.BaseExceptoin：基础异常，是其他自定义异常的基类。包含字段：所属模块module，错误码：code，错误码对应参数args，错误消息defaultMessage<br />2.file：该目录下定义文件操作相关异常。文件名长度，文件大小，文件上传错误，后缀无效<br />3.job：该目录下定义计划策略异常TaskException。<br />4.user：该目录下定义用户相关异常。黑名单ip，验证码错误，用户不存在，用户密码错误，错误最大次数<br />5.DemoModeException：演示模式异常<br />6.GlobalException：全局异常<br />7.ServiceException：业务异常<br />8.UtilException：工具类异常 |
| filter     | Servelet过滤器<br />1.PropertyPreExcludedFilter：排除JSON敏感属性<br />2.RepeatbleFilter：Repeatable 过滤器<br />3.RepeatedlyRequestWrapper：构建可重复读取inputStream的request<br />4.XssFilter：防止XSS攻击的过滤器<br />5.XssHttpServletRequestWrapper：XSS过滤处理 |
| utils      | 通用类处理：<br />1.bean：bean工具类。Bean属性复制BeanUtils，属性验证BeanValidators<br />2.file：文件工具类。文件类型FileTypeUtils，文件上传UploadUtils，图片工具Imageutils，媒体类型工具MimeTypeUtils<br />3.html：html相关工具类。转义与反转义EscapeUtil，去除Xss漏洞HTMLFilter<br />4.http：http工具类封装。通用http工具类HttpHelper，发送http请求：HttpUtils<br />5.ip：ip地址处理相关工具类。根据Ip获取地址AddressUtils，获取ip，IpUtils<br />6.poi：excel表格处理工具类。数据格式处理适配器ExcelHandlerAdapter，Excel相关处理ExcelUtil<br />7.reflect：反射工具类ReflectUtils。提供调用getter/setter方法, 访问私有变量, 调用私有方法, 获取泛型类型Class, 被AOP过的真实类等工具函数<br />8.sign：签名认证工具类。Base64，Md5Utils<br />9.spring：spring工具类 方便在非spring管理环境中获取bean。<br />10.sql:sql操作工具类SqlUtil<br />11.uuid：通用唯一识别码工具类。UUID：生成uuid；IdUtils：获取uuid；Seq：生成序列；<br />12.其他：安全服务工具类SecurityUtils[获取用户，部门id，检验密码，认证授权等]，分页工具类PageUtils，错误信息处理工具类ExceptionUtil，处理并记录日志工具类LogUtils，时间工具类DateUtils…… |
| xss        | XSS过滤处理<br />1.Xss：自定义xss校验注解<br />2.XssValidator：自定义xss校验注解实现 |

framework：框架核心

| 目录        | 功能                                                         |
| ----------- | ------------------------------------------------------------ |
| aspectj     | 注解实现，AOP相关<br />1.DataScopeAspect：数据过滤处理<br />2.DataSourceAspect：多数据源处理<br />3.LogAspect：操作日志记录处理<br />4.RateLimiterAspect：限流处理 |
| config      | 系统配置<br />1.DruidProperties：druid基础配置<br />2.DruidConfig：druid 配置多数据源<br />3.PermitAllUrlProperties：设置@Anonymous注解允许匿名访问的url<br />4.CaptchaConfig：验证码配置<br />5.FastJson2JsonRedisSerializer：Redis使用FastJson序列化<br />6.FilterConfig：Filter配置<br />7.MyBatisConfig：Mybatis支持*匹配扫描包<br />8.RedisConfig：redis配置<br />9.ResourcesConfig：通用配置<br />10.SecurityConfig：spring security配置<br />11.ServerConfig：服务器相关配置<br />12.ThreadPoolConfig：线程池配置 |
| datasource  | 多数据源<br />1.DynamicDataSource：动态数据源<br />2.DynamicDataSourceContextHolder：动态数据源切换 |
| interceptor | 拦截器<br />RepeatSubmitInterceptor：防止重复提交拦截器      |
| manager     | 异步任务管理器<br />1.AsyncFactory：异步工厂（产生任务用）<br />2.AsyncManager：异步任务管理器<br />3.ShutdownManager：确保应用退出时能关闭后台线程 |
| security    | 集成SpringSecurity权限控制<br />1.context：该目录下定义SpringSecurity中ContextHolder对象，用来进行身份校验与权限管理。AuthenticationContextHolder管理身份验证信息；PermissionContextHolder管理权限信息<br />2.filter：该目录下定义往SpringSecurity过滤器链中添加的过滤器。token过滤器 验证token有效性JwtAuthenticationTokenFilter<br />3.handle：该目录下定义自定义的异常处理器。认证失败处理类 返回未授权AuthenticationEntryPointImpl，退出处理onLogoutSuccess |
| web         | 验证码与登录验证授权相关服务<br />1.server：该目录下定义服务器相关信息。<br />2.exception：该目录下定义登录授权与http请求相关的全局异常处理器<br />3.service：该目录下定义token验证与登录授权相关的服务<br />TokenService：token验证处理<br />UserDetailsServiceImpl：用户验证处理<br />SysRegisterService：注册校验方法<br />SysLoginService：登录校验方法<br />SysPermissionService：用户权限处理<br />PermissionService：若依自定义的权限处理方法，使用字符串 \*:\*:\* |

ruoyi-quartz：定时任务

| 目录       | 功能                                                         |
| ---------- | ------------------------------------------------------------ |
| config     | `ScheduleConfig`：定时任务配置【源码中被注释掉了，未使用】<br />说明如下：单机部署建议删除此类和qrtz数据库表，默认走内存会最高效 |
| domain     | 实体类：<br />1.`SysJob`：定时任务类，关联sys_job数据库表，用于前后端通信<br />2.`SysJobLog`：定时任务日志类，关联sys_job_log数据库表，用于前后端通信 |
| controller | Controller类：<br />1.`SysJobController`：定时任务控制类，请求路径/monitor/job<br />[GET]/list：询定时任务列表<br />[GET]/{jobId}：获取定时任务详细信息<br />[POST]/：新增定时任务<br />[PUT]/：修改定时任务<br />[PUT]/changeStatus：定时任务状态修改<br />[POST]/export：导出定时任务列表<br />[PUT]/run：定时任务立即执行一次<br />[DELETE]/{jobIds}：删除定时任务<br />2.`SysJobLogController`：定时任务日志控制类，请求路径/monitor/jobLog<br />[GET]/list：查询定时任务调度日志列表<br />[POST]/export：导出定时任务调度日志列表<br />[GET]/{jobLogId}：根据调度编号获取详细信息<br />[DELETE]/{jobLogIds}：删除定时任务调度日志<br />[DELETE]/clean：清空定时任务调度日志<br /> |
| service    | Service类：<br />1.`ISysJobService`：定时任务调度Service类<br />selectJobList：获取quartz调度器的计划任务<br />selectJobById：通过调度任务ID查询调度信息<br />pauseJob：暂停任务<br />resumeJob：恢复任务<br />deleteJob：删除任务，所对应的trigger也将被删除<br />deleteJobByIds：批量删除调度信息<br />changeStatus：任务调度状态修改<br />run：立即运行任务<br />insertJob：新增任务<br />updateJob：更新任务<br />2.`ISysJobLogService`：定时任务调度日志信息信息<br />selectJobLogList：获取quartz调度器日志的计划任务<br />selectJobLogById：通过调度任务日志ID查询调度信息<br />addJobLog：新增任务日志<br />deleteJobLogByIds：批量删除调度日志信息<br />deleteJobLogById：删除任务日志<br />cleanJobLog：清空任务日志 |
| mapper     | Mapper类：<br />1.`SysJobMapper`：定时任务Mapper类<br />selectJobList：查询调度任务日志集合<br />selectJobAll：查询所有调度任务<br />selectJobById：通过调度ID查询调度任务信息<br />deleteJobById：通过调度ID删除调度任务信息<br />deleteJobByIds：批量删除调度任务信息<br />updateJob：修改调度任务信息<br />insertJob：新增调度任务信息<br />2.`SysJobLogMapper`：定时任务日志Mapper类<br />selectJobLogList：获取quartz调度器日志的计划任务<br />selectJobLogAll：查询所有调度任务日志<br />selectJobLogById：通过调度任务日志ID查询调度信息<br />insertJobLog：新增任务日志<br />deleteJobLogByIds：批量删除调度日志信息<br />deleteJobLogById：删除任务日志<br />cleanJobLog：清空任务日志<br /> |
| utils      | 定时任务调度工具类：<br />1.`AbstractQuartzJob`：抽象quartz调用，实现quartz的`Job`接口，重写excute方法<br />2.`CronUtils`：cron表达式工具类。判断cron表达式的有效性；根据给定的Cron表达式返回下一个执行时间<br />3.`JobInvokeUtil`：任务执行工具类。执行方法；调用任务方法；获取bean方法；获取method方法参数相关列表等<br />4.`QuartzDisallowConcurrentExecution`：定时任务处理（禁止并发执行）<br />5.`QuartzJobExecution`：定时任务处理（允许并发执行）<br />6.`whiteList`：检查包名是否为白名单配置 |
| task       | 该目录下存放定时任务的执行方法                               |

添加自定义定时任务相关说明：

![](https://s2.loli.net/2023/12/13/a7bZzRBnOQLDkGt.png)

1. 将要执行的方法放在task目录下

2. Cron表达式需要合法

3. 调用方法要求：

   不允许'rmi'调用
   不允许'ldap(s)'调用
   不允许'http(s)'调用
   不允许存在违规字符
   执行方法的包需要在白名单内

4. 调用方法的调用方式：通过Bean`BeanName.MethodName(args)`调用或者Class类调用`ClassName.MethodName(args)`

违规字符定义于 `com.ruoyi.common.constant.Constants`中的JOB_ERROR_STR字符串数组

白名单定义于 `com.ruoyi.common.constant.Constants`中的JOB_WHITELIST_STR字符串数组





ruoyi剖析：

- common下面的模块都有什么用？为什么common下面会有annotation,config这些模块，哪里用到它们
- common下面的模块是如何组织的？如果我要往common里面加模块，哪些模块可以加进去
- 其他模块的作用是什么？generator，quartz具体怎么用，可以在quartz里面添加自己的代码吗
- 如何添加自己的模块？ admin模块的作用是什么，一定需要它来关联自定义的服务吗



接口设计：

![Snipaste_2023-12-12_20-46-32](https://s2.loli.net/2023/12/12/MtnloDLFxsVHBUm.png)

- 理解业务：需求说明，概要说明对照着看

- 接口编写规范：参考杨伟老师以前写过的，自己查查写接口要注意什么

- 思维通路：产品-价格-出售-服务-核销



