## 快捷键：

- 重写接口方法：`ctrl o`

- 环绕方法 `ctrl alt t`

  ![image-20231205203021316](https://s2.loli.net/2023/12/05/kKhmelosPuCSWIU.png)



## 登录校验流程：[黑马javawebP167 5.34]

![image-20231205165821026](https://s2.loli.net/2023/12/05/jmk5qGVuXaisd6T.png)





Filter与Interceptor区别：

- Filter是在servlet层，拦截所有资源
- Interceptor是在spring层，只拦截进入spring的资源

![image-20231205203003469](https://s2.loli.net/2023/12/05/ClTq1tFpKLQVRyN.png)



## AOP相关

![image-20231205202945247](https://s2.loli.net/2023/12/05/omgSNUFJDVeAhvf.png)

![image-20231205212830198](https://s2.loli.net/2023/12/05/gWEVdJpUz6FOvNr.png)



## 自定义starter

定义Bean：

- 本项目：`Controller` `Service` `Component`

- 第三方：在配置类中写`@Bean`

- 扫描：

  - `@ComponentScen` 

  - `@import()`:三种形式，常用实现selector的方式 || 很多框架的 `@Enablexxx`本质就是import

    - 导入普通类：`@Import(TokenParser.class)`

    - 导入配置类：`@Import(HeaderConfig.class)`

    - 导入ImportSelector接口实现类：

      ![image-20231206121313735](https://s2.loli.net/2023/12/06/jIQRVF3DqxXy4M9.png)

  - 框架写自动配置文件：

    ![image-20231206121035541](https://s2.loli.net/2023/12/06/txD5qMhaRsp6UZG.png)

![image-20231206120358659](https://s2.loli.net/2023/12/06/h5W7DjFHT2IQXNM.png)





## HttpClient

![image-20231209213801737](https://s2.loli.net/2023/12/09/jZbmJQ3ouv71eWR.png)

> 具体代码： `sky-take-out`-test目录-`HttpClientTest`

示例代码：

```java
package com.sky.test;

import com.alibaba.fastjson.JSONObject;
import lombok.extern.slf4j.Slf4j;
import org.apache.http.HttpEntity;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;

import java.io.IOException;
import java.io.UnsupportedEncodingException;

@SpringBootTest
@Slf4j
public class HttpClientTest {
    /**
     * 测试通过HttpClient发送Get请求
     */
    @Test
    public void testHttpClientGet() throws IOException {
        //创建HttpClient对象
        CloseableHttpClient httpClient = HttpClients.createDefault();

        //创建请求对象
        HttpGet httpGet = new HttpGet("http://localhost:8080/user/shop/status");

        //发送请求
        CloseableHttpResponse response = httpClient.execute(httpGet);

        //解析返回结果
        int statusCode = response.getStatusLine().getStatusCode();
        System.out.println("服务端返回的状态码："+statusCode);

        HttpEntity entity = response.getEntity();
        String body = EntityUtils.toString(entity);
        System.out.println("服务端返回的数据为："+body);

        //关闭资源
        response.close();
        httpClient.close();
    }

    /**
     * 测试通过HttpClient发送Post请求
     */
    @Test
    public void testHttpClientPost() throws IOException {
        //创建HttpClient对象
        CloseableHttpClient httpClient = HttpClients.createDefault();

        //创建请求对象
        HttpPost httpPost = new HttpPost("http://localhost:8080/admin/employee/login");

        //FastJson构建Json对象
        JSONObject jsonObject = new JSONObject();
        jsonObject.put("username", "admin");
        jsonObject.put("password", "123456");

        StringEntity entity = new StringEntity(jsonObject.toString());
        //指定请求的编码方法
        entity.setContentEncoding("utf-8");
        //数据格式：Json
        entity.setContentType("application/json");
        httpPost.setEntity(entity);

        //发送请求,并且接收响应结果
        CloseableHttpResponse response = httpClient.execute(httpPost);

        //解析返回结果
        int statusCode = response.getStatusLine().getStatusCode();
        System.out.println("服务端返回的状态码："+statusCode);
        HttpEntity entity1 = response.getEntity();
        String body = EntityUtils.toString(entity1);
        System.out.println("服务端返回的数据为："+body);

        //关闭资源
        response.close();
        httpClient.close();
    }
}
```



封装好的工具类：`HttpClientUtils`

```java
package com.sky.utils;

import com.alibaba.fastjson.JSONObject;
import org.apache.http.NameValuePair;
import org.apache.http.client.config.RequestConfig;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.client.utils.URIBuilder;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.util.EntityUtils;

import java.io.IOException;
import java.net.URI;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 * Http工具类
 */
public class HttpClientUtil {

    static final  int TIMEOUT_MSEC = 5 * 1000;

    /**
     * 发送GET方式请求
     * @param url
     * @param paramMap
     * @return
     */
    public static String doGet(String url,Map<String,String> paramMap){
        // 创建Httpclient对象
        CloseableHttpClient httpClient = HttpClients.createDefault();

        String result = "";
        CloseableHttpResponse response = null;

        try{
            URIBuilder builder = new URIBuilder(url);
            if(paramMap != null){
                for (String key : paramMap.keySet()) {
                    builder.addParameter(key,paramMap.get(key));
                }
            }
            URI uri = builder.build();

            //创建GET请求
            HttpGet httpGet = new HttpGet(uri);

            //发送请求
            response = httpClient.execute(httpGet);

            //判断响应状态
            if(response.getStatusLine().getStatusCode() == 200){
                result = EntityUtils.toString(response.getEntity(),"UTF-8");
            }
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            try {
                response.close();
                httpClient.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        return result;
    }

    /**
     * 发送POST方式请求
     * @param url
     * @param paramMap
     * @return
     * @throws IOException
     */
    public static String doPost(String url, Map<String, String> paramMap) throws IOException {
        // 创建Httpclient对象
        CloseableHttpClient httpClient = HttpClients.createDefault();
        CloseableHttpResponse response = null;
        String resultString = "";

        try {
            // 创建Http Post请求
            HttpPost httpPost = new HttpPost(url);

            // 创建参数列表
            if (paramMap != null) {
                List<NameValuePair> paramList = new ArrayList();
                for (Map.Entry<String, String> param : paramMap.entrySet()) {
                    paramList.add(new BasicNameValuePair(param.getKey(), param.getValue()));
                }
                // 模拟表单
                UrlEncodedFormEntity entity = new UrlEncodedFormEntity(paramList);
                httpPost.setEntity(entity);
            }

            httpPost.setConfig(builderRequestConfig());

            // 执行http请求
            response = httpClient.execute(httpPost);

            resultString = EntityUtils.toString(response.getEntity(), "UTF-8");
        } catch (Exception e) {
            throw e;
        } finally {
            try {
                response.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        return resultString;
    }

    /**
     * 发送POST方式请求
     * @param url
     * @param paramMap
     * @return
     * @throws IOException
     */
    public static String doPost4Json(String url, Map<String, String> paramMap) throws IOException {
        // 创建Httpclient对象
        CloseableHttpClient httpClient = HttpClients.createDefault();
        CloseableHttpResponse response = null;
        String resultString = "";

        try {
            // 创建Http Post请求
            HttpPost httpPost = new HttpPost(url);

            if (paramMap != null) {
                //构造json格式数据
                JSONObject jsonObject = new JSONObject();
                for (Map.Entry<String, String> param : paramMap.entrySet()) {
                    jsonObject.put(param.getKey(),param.getValue());
                }
                StringEntity entity = new StringEntity(jsonObject.toString(),"utf-8");
                //设置请求编码
                entity.setContentEncoding("utf-8");
                //设置数据类型
                entity.setContentType("application/json");
                httpPost.setEntity(entity);
            }

            httpPost.setConfig(builderRequestConfig());

            // 执行http请求
            response = httpClient.execute(httpPost);

            resultString = EntityUtils.toString(response.getEntity(), "UTF-8");
        } catch (Exception e) {
            throw e;
        } finally {
            try {
                response.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        return resultString;
    }
    private static RequestConfig builderRequestConfig() {
        return RequestConfig.custom()
                .setConnectTimeout(TIMEOUT_MSEC)
                .setConnectionRequestTimeout(TIMEOUT_MSEC)
                .setSocketTimeout(TIMEOUT_MSEC).build();
    }

}
```



## 关于JSON

### Jackson

springboot默认用Jackson解析

前端日期校验

`@Jackson(pattern="")`

### FastJson：json与对象转换

[菜鸟教程](https://www.runoob.com/w3cnote/fastjson-intro.html)

[博客教程](https://www.cnblogs.com/dmego/p/9033080.html)

[官方文档](https://www.w3cschool.cn/fastjson/fastjson-intro.html)



对象转换器`com/sky/json/JacksonObjectMapper.java`

使用的是FastJson包

```java
//FastJson构建Json对象
JSONObject jsonObject = new JSONObject();
jsonObject.put("username", "admin");
jsonObject.put("password", "123456");

StringEntity entity = new StringEntity(jsonObject.toString());

//解析JSON对象
String json = HttpClientUtil.doGet(WX_LOGIN, map);

JSONObject jsonObject = JSON.parseObject(json);
String openid = jsonObject.getString("openid");

//构建map，转JSON字符串
Map map = new HashMap();
map.put("type", 1);
map.put("orderId", ordersDB); //1表示来单提醒 2表示客户催单
map.put("content","订单号："+outTradeNo);

String json = JSON.toJSONString(map);
webSocketServer.sendToAllClient(json);
```

`JSONObject`：json对象

`JSONArray`:json数组

[示例博客](https://blog.csdn.net/tangerr/article/details/76217924)





### ObjectMapper:发json，简单解析json

https://kucw.github.io/blog/2020/6/java-jackson/

```java
@Test
    public void testJson() throws JsonProcessingException {
        ObjectMapper objectMapper = new ObjectMapper();
        List<String> list = new ArrayList<String>(Arrays.asList("张三","2023-11-2:13:40","2024-1-12:15:30"));
        //对象转json
        String json = objectMapper.writeValueAsString(list);
        System.out.println(json);
        //json转对象
        List j_list = objectMapper.readValue(json, List.class);
        j_list.forEach(System.out::println);
    }
```

![image-20240118121523118](https://raw.githubusercontent.com/timothy020/pic/main/img/JS3eZEFpOoCbLdw.png)

支持Java8时间类型：

```java
@Test
    public void testJson() throws JsonProcessingException {
        ObjectMapper objectMapper = new ObjectMapper();
        objectMapper.registerModule(new JavaTimeModule());

        ShiftInfo shiftInfo = new ShiftInfo("user1",
                LocalTime.of(13,0,10),
                LocalTime.of(15,0,10));
        String json = objectMapper.writeValueAsString(shiftInfo);
        //Object->json
        System.out.println(json);
        //json->Object
        System.out.println(objectMapper.readValue(json, ShiftInfo.class));
    }
```



### 前端日期校验

`@DateTimeformate()`

![image-20240302152632526](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240302152632526.png)



## Tricks

### 对象复制

1. **BeanUtils对象复制**

[hutool包](https://apidoc.gitee.com/loolly/hutool/cn/hutool/core/bean/BeanUtil.html)

- toBean
- copyProperties

2. **Mpstruct对象复制**

[官网](https://mapstruct.org/)



### 日期

1. **校验日期格式`@DateTimeFormat`**

```java
@Schema(description = "营业端-现场开单 获取交互信息时使用的VO")
@Data
@ToString(callSuper = true)
public class PriceListInteractReqVO implements Serializable {
    @Schema(description = "场区id", example = "1")
    @NotNull(message = "场区id不能为空")
    private Long zoneId;

    @Schema(description = "会员等级", example = "1")
    @NotNull(message = "会员等级不能为空")
    private Integer memberGrade;

    @Schema(description = "日期", example = "2024-2-16")
    @NotNull(message = "日期不能为空")
    @DateTimeFormat(pattern = FORMAT_YEAR_MONTH_DAY)
    private LocalDate date;
}
```





## 关于Redis

> 具体代码： `sky-take-out`-test目录-`SpringDataRedisTest`



## 关于SpringCache

![image-20231210173205578](https://s2.loli.net/2023/12/10/8gMla6eAfyENsVi.png)

![](https://s2.loli.net/2023/12/10/KVLdzwgsNQkPZ5G.png)

> 具体代码： `cloud-demo`-`srpingcache-demo`里面的controller的注解

## PageHelper在Service层的使用

`OrderServiceImpl`：

```java
/***
 * 获取历史订单信息
 * @param pageNum
 * @param pageSize
 * @param status
 * @return PageResult
 */
@Override
public PageResult pageQueryByUser(Integer pageNum, Integer pageSize, Integer status) {
    // 设置分页
    PageHelper.startPage(pageNum, pageSize);

    OrdersDTO ordersDTO = new OrdersDTO();
    ordersDTO.setUserId(BaseContext.getCurrentId());
    ordersDTO.setStatus(status);

    // 分页条件查询
    Page<Orders> page = orderMapper.pageQuery(ordersDTO);

    List<OrderVO> list = new ArrayList<>();
    // 查询出订单明细，并封装入OrderVO进行响应
    if(page != null && page.getTotal() > 0) {
        for(Orders orders : page) {
            // 查询订单明细
            List<OrderDetail> orderDetails = orderDetailMapper.getByOrderId(orders.getId());

            OrderVO orderVO = new OrderVO();
            BeanUtils.copyProperties(orders, orderVO);
            orderVO.setOrderDetailList(orderDetails);

            list.add(orderVO);
        }
    }

    return new PageResult(page.getTotal(), list);

}

/**
 * 封装分页查询结果
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class PageResult implements Serializable {

    private long total; //总记录数

    private List records; //当前页数据集合

}
/*--------------------------*/

/*条件查询请求体*/
public class OrdersPageQueryDTO implements Serializable {

    private int page;
    private int pageSize;
    private String number;
    private  String phone;
    private Integer status;
    
    @DateTimeFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private LocalDateTime beginTime;

    @DateTimeFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private LocalDateTime endTime;
    private Long userId;

}

```

一般思路：`PageQueryDTO`—pageHelper—`PageResult`



## 微信支付

![image-20231213151433975](https://s2.loli.net/2023/12/13/IG3dpXeqmsSBUWo.png)

## 流式操作与批操作

1. 对List中的所有元素进行Map-Reduce操作，收集为List

`OrderServiceImpl`：

```java
/**
 * 再来一单
 * @param id
 */
@Override
public void repetition(Long id) {
    // 查询当前用户id
    Long userId = BaseContext.getCurrentId();

    // 根据订单id查询当前订单详情
    List<OrderDetail> orderDetails = orderDetailMapper.getByOrderId(id);

    // 将订单详情对象转换为购物车对象
    List<ShoppingCart> shoppingCartList = orderDetails.stream().map(x -> {
        ShoppingCart shoppingCart = new ShoppingCart();

        // 将原订单详情里面的菜品信息重新复制到购物车对象中
        BeanUtils.copyProperties(x, shoppingCart, "id");
        shoppingCart.setUserId(userId);
        shoppingCart.setCreateTime(LocalDateTime.now());

        return shoppingCart;
    }).collect(Collectors.toList());

    //将购物车对象批量添加到数据库
    shoppingCartMapper.insertBatch(shoppingCartList);
}

```

![image-20231214192822470](https://s2.loli.net/2023/12/14/6vHPFdk4LX5KGRZ.png)

`ReportServiceImpl`：

```java
/**
 * 获取销量前十的商品
 * @param begin
 * @param end
 * @return
 */
@Override
public SalesTop10ReportVO getSalesTop10(LocalDate begin, LocalDate end) {
    LocalDateTime beginTime = LocalDateTime.of(begin, LocalTime.MIN);
    LocalDateTime endTime   = LocalDateTime.of(end, LocalTime.MAX);
    List<GoodsSalesDTO> salesTop10 = orderMapper.getSalesTop10(beginTime, endTime);

    List<String> names = 				salesTop10.stream().map(GoodsSalesDTO::getName).collect(Collectors.toList());
    List<Integer> numbers = salesTop10.stream().map(GoodsSalesDTO::getNumber).collect(Collectors.toList());
    
    String nameList = StringUtils.join(names, ",");
    String numberList = StringUtils.join(numbers, ",");

    //封装返回结果数据
    return SalesTop10ReportVO.builder()
            .nameList(nameList)
            .numberList(numberList)
            .build();
}
```



2. Stream流式操作统计List总和

```java
//计算时间区间内的订单总数量
Integer totalOrderCount = totalOrderList.stream().reduce(Integer::sum).get();

//计算时间区间内的有效订单总数量
Integer validOrderCount = validOrderList.stream().reduce(Integer::sum).get();
```



groupby与类型转换:

![img](https://raw.githubusercontent.com/timothy020/pic/main/img/202207162055560.png)

```java
@Override
    public List<BookingRuleConfigAllRulesRespVO> getAllRulesWithoutContent() {
        List<BookingRuleConfigDO> bookingRuleConfigDOS = bookingRuleConfigMapper.selectList(null);
        //流式操作
        //第一次map-reduce，根据type分类: List<BookingRuleConfigDO>  => (type, List<BookingRuleConfigAllRulesRespVO>)
        //第二次map-reduce，类型转换:     (type, List<BookingRuleConfigAllRulesRespVO>) => (type, List<SimpleRuleItems>)
        Map<Integer, List<SimpleRuleItem>> collect = bookingRuleConfigDOS.stream().
                collect(Collectors.groupingBy(BookingRuleConfigDO::getType,
                        Collectors.mapping(bookingRuleConfigDO -> SimpleRuleItem.builder()
                                    .id(bookingRuleConfigDO.getId())
                                    .name(bookingRuleConfigDO.getName())
                                    .build(),
                                Collectors.toList())));
        //构造返回结果
         List<BookingRuleConfigAllRulesRespVO> result = new ArrayList<>();
         collect.forEach((type, rules) ->{
             result.add(new BookingRuleConfigAllRulesRespVO(type, rules));
         });
         return result;
    }
```



3. 搜集List中的字段到一个map

```java
Map<Long, String> fieldIdNameMap = 	
  svFieldInfoPage.getList().stream()
    .collect(Collectors.toMap(SvFieldInfoDO::getId,SvFieldInfoDO::getName));
Map<Long, List<PriceListDO>> fieldIdSessionInfoMap = priceListDOS.stream()
    .collect(Collectors.groupingBy(PriceListDO::getFieldId, Collectors.toList()));
List<SessionInfoRespVO> result = new ArrayList<>();
fieldIdSessionInfoMap.forEach((id, priceListDOList) -> {
    List<SessionInfo> sessionInfos = SiteBillingConvert.INSTANCE.convert(priceListDOList);
    IdNameVO idNameVO = IdNameVO.builder()
        .Id(id)
        .name(fieldIdNameMap.get(id))
        .build();
    result.add(SessionInfoRespVO.builder()
               .fieldIdName(idNameVO)
               .sessionInfos(sessionInfos)
               .build());
});
```



4. Integer List 转 逗号分隔的字符串 【stream+joining】

```java
@Mapper
public interface FieldLockConvert {
    FieldLockConvert INSTANCE = Mappers.getMapper(FieldLockConvert.class);

    default FieldLockDO convert(FieldLockSaveReqVO fieldLockSaveReqVO) {
        FieldLockDO fieldLockDO = BeanUtils.copyPorperties(fieldLockSaveReqVO, FieldLockDO.class, "lockIdList");
        String lockIdListStr = fieldLockSaveReqVO.getLockIdList().stream()
                .map(Object::toString)
                .collect(Collectors.joining(","));
        fieldLockDO.setLockIdList(lockIdListStr);
        return fieldLockDO;
    }
}
```





## Spring Task

cron表达式：https://cron.qqe2.com/

![image-20231214130811250](https://s2.loli.net/2023/12/14/bSKFMvCDzxHJ28N.png)



![image-20231214131045210](https://s2.loli.net/2023/12/14/WUwBPKe9H31LsTj.png)

```java
package com.sky.task;

import lombok.extern.slf4j.Slf4j;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;

import java.util.Date;

@Component
@Slf4j
public class MyTask {

    /**
     * 定时任务，每5s触发一次
     */
    @Scheduled(cron = "0/5 * * * * ?")
    public void excuteTask() {
        log.info("定时任务开始执行： {}", new Date());
    }
}
```



## WebSocket

![image-20231214140857577](https://s2.loli.net/2023/12/14/r9wL5qjx4intBSU.png)

![image-20231214141224668](https://s2.loli.net/2023/12/14/DWS6FZgn3TwRdL2.png)

测试代码写在 `WebSocketTask`，定时发送消息，查看是否能收到

业务代码写在 `OrderServiceImpl-payment`，调用**webSocketServer.sendToAllClient(json);**发送消息





![image-20231214145952240](https://s2.loli.net/2023/12/14/rPRoZY2q5AkTM7s.png)

 



![image-20231214150043158](https://s2.loli.net/2023/12/14/pHIW5yN2QGzKrt6.png)



![image-20231214150801812](https://s2.loli.net/2023/12/14/BPHoq9ShQu4Kxr3.png)





## 前端数据可视化 Apache Echarts 

官网：https://echarts.apache.org/en/index.html

![image-20231214151804086](https://s2.loli.net/2023/12/14/HWNr48xmeo9nqQD.png)

> 总结：本质是数据
> 使用Echats，重点在于研究当前图表所需的数据格式。通常是需要后端提供符合格式要求的动态数据，然后响应给前端来展示图表。

关键点：

- 前端需要的数据格式： 

  ```java
  public class TurnoverReportVO implements Serializable {
  
      //日期，以逗号分隔，例如：2022-10-01,2022-10-02,2022-10-03
      private String dateList;
      
      //营业额，以逗号分隔，例如：406.0,1520.0,75.0
      private String turnoverList;
  }
  ```

- 日期的递增操作： `localDate.plusDays(1)`
- List转为“,”分隔的字符串： `SpringUtils.join(list, separator)`

```java
//ReportServiceImpl
/**
 * 统计指定时间区间内的营业额数据
 * @param begin
 * @param end
 * @return
 */
@Override
public TurnoverReportVO getTurnoverStatistics(LocalDate begin, LocalDate end) {
    //当前集合用于存放从begin到end范围内的每天的日期
    List<LocalDate> dateList = new ArrayList<>();

    dateList.add(begin);
    while(!begin.equals(end)) {
        //日期计算：计算指定日期的后一天的日期
        begin = begin.plusDays(1);
        dateList.add(begin);
    }

    //存放每天的营业额
    List<Double> turnoverList = new ArrayList<>();
    for(LocalDate date : dateList){
        //查询date日期对应的营业额数据，营业额是指：状态为“已完成”的订单金额合计
        LocalDateTime beginTime = LocalDateTime.of(date, LocalTime.MIN);
        LocalDateTime endTime = LocalDateTime.of(date, LocalTime.MAX);

        //select sum(amount) from orders where order_time > beginTime and order_time < endTime and status = 5
        //之所以计算beginTime和endTime是因为order_time的类型是LocalDateTime，而不是LocalDate
        Map map = new HashMap();
        map.put("begin", beginTime);
        map.put("end", endTime);
        map.put("status", Orders.COMPLETED);
        Double turnover = orderMapper.sumByMap(map);
        turnover = (turnover == null ? 0.0 : turnover);
        turnoverList.add(turnover);
    }

    //StringUtils.join : convert List item to String separated by ","
    String dateListString = StringUtils.join(dateList, ",");
    String turnoverListString = StringUtils.join(turnoverList, ",");

    return TurnoverReportVO.builder()
            .dateList(dateListString)
            .turnoverList(turnoverListString)
            .build();
}
```



## 操作Excel表格，Apache POI

![image-20231215091304880](https://s2.loli.net/2023/12/15/MVsTgOrXz4Nedfa.png)

入门案例：

Excel-Sheet-Row-Cell

```java
package com.sky.test;

import org.apache.poi.xssf.usermodel.XSSFRow;
import org.apache.poi.xssf.usermodel.XSSFSheet;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;

/**
 * 使用POI操作Excel文件
 */
public class POITest {

    /**
     * 通过POI创建Excel文件并行写入内容
     */
    public static void write() throws Exception {
        //在内存中创建一个Excel文件
        XSSFWorkbook excel = new XSSFWorkbook();
        //在Excel中创建一个sheet页
        XSSFSheet sheet = excel.createSheet();
        //在sheet中创建行对象，下标从0开始
        XSSFRow row = sheet.createRow(1);
        //创建单元格并写入内容
        row.createCell(1).setCellValue("姓名");
        row.createCell(2).setCellValue("城市");

        //创建一个新行
        row = sheet.createRow(2);
        row.createCell(1).setCellValue("张三");
        row.createCell(2).setCellValue("北京");

        row = sheet.createRow(3);
        row.createCell(1).setCellValue("李四");
        row.createCell(2).setCellValue("南京");

        //通过输出流，将内存中的Excel文件写入到磁盘
        FileOutputStream out = new FileOutputStream(new File("E:\\info.xlsx"));
        excel.write(out);

        //关闭资源
        out.close();
        excel.close();
    }

    /**
     * 通过POI读取Excel文件的内容
     * @throws Exception
     */
    public static void read() throws Exception {
        FileInputStream in = new FileInputStream(new File("E:\\info.xlsx"));
        //读取磁盘上已经存在的Excel文件
        XSSFWorkbook excel = new XSSFWorkbook(in);
        //读取Excel文件中的第一个sheet页
        XSSFSheet sheet = excel.getSheetAt(0);

        //获取sheet页中最后一行的行号
        int lastRowNum = sheet.getLastRowNum();

        for(int i = 1; i <= lastRowNum; i++){
            //获得某一行
            XSSFRow row = sheet.getRow(i);
            //获得单元格对象
            String cellValue1 = row.getCell(1).getStringCellValue();
            String cellValue2 = row.getCell(2).getStringCellValue();
            System.out.println(cellValue1 + " " + cellValue2);
        }

        //关闭资源
        in.close();
        excel.close();
    }

    public static void main(String[] args) throws Exception {
        write();
        read();
    }

}
```