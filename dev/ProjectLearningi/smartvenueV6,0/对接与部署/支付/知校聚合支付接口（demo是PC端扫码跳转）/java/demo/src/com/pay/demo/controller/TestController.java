package com.pay.demo.controller;

import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import java.util.UUID;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;

import net.sf.json.JSONObject;

@Controller
@RequestMapping("/order")
public class TestController {
	//查询接口
	String query_url = "http://wx.weiweixiao.net/pay_api/order_query";

	//创建订单接口
	String create_url = "http://wx.weiweixiao.net/pay_api/order_create";

	//取消订单接口
	String cancel_url = "http://wx.weiweixiao.net/pay_api/order_cancel";

	//订单退款接口
	String order_refund = "http://wx.weiweixiao.net/pay_api/order_refund";
	
	//创建订单成功回调地址
	String return_url = "https://notify.zhizhixao.com/return.html";
	
	//通知处理接口
	String notify_url = "127.0.0.1:8080/demo/order/notify";
	
	//本地查询订单解耦
	String localQuery = "http://127.0.0.1:8080/demo/order/selectOrderQuery.do";

	String aes_key = "AD42F6697B035B7580E4FEF93BE20B4D";

	String id = "partner1";

	String sign_key = "weiweixiao";

	public String getId() {
		return id;
	}

	public String getAesKey() {
		return aes_key;
	}

	public String getSignKey() {
		return sign_key;
	}


	public static Map<String, Boolean> notice = new HashMap<String, Boolean>();

	
	/**
	 * 创建订单
	 * @param request
	 * @param response
	 */
	@RequestMapping(value = "/orderCreate", method = RequestMethod.POST)
	@ResponseBody
	public void orderCreate(HttpServletRequest request, HttpServletResponse response) {
		response.setHeader("Content-type", "text/html;charset=UTF-8");
		String out_no = request.getParameter("order_id");
		if (out_no == null || out_no.equals("")) {
			out_no = UUID.randomUUID().toString().replaceAll("-", "");
		}
		aesPost d = new aesPost();
		String pathUrl = "";
		JSONObject jsn = new JSONObject();
		//订单描述
		jsn.put("body", "订单创建测试");
		//商户订单号
		jsn.put("out_trade_no", out_no);
		//订单金额
		jsn.put("total_fee", "1");
		//订单成功后返回地址
		jsn.put("return_url", return_url);
		//订单后台通知接口地址
		jsn.put("notify_url", notify_url);
		pathUrl = create_url;
		jsn = d.CreateConnection(pathUrl, jsn);
		try {
			response.getWriter().write(jsn.toString());
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	/**
	 * 查询订单
	 * @param request
	 * @param response
	 */
	@RequestMapping(value = "/selectOrderQuery", method = RequestMethod.GET)
	@ResponseBody
	public JSONObject selectOrderQuery(HttpServletRequest request, HttpServletResponse response) {
		response.setHeader("Content-type", "text/html;charset=UTF-8");
		String out_no = request.getParameter("order_id");
		aesPost d = new aesPost();
		String pathUrl = "";
		JSONObject jsn = new JSONObject();
		//商户订单号
		jsn.put("out_trade_no", out_no);
		pathUrl = query_url;
		jsn = d.CreateConnection(pathUrl, jsn);
		JSONObject jo = new JSONObject();
		jo = jsn.getJSONObject("ret_content");
		System.out.println("查询订单结果！！！");
		//商户订单号
		System.out.println("商户订单号 :" + jo.getString("out_trade_no"));
		//订单号
		System.out.println("订单号 : "+ jo.getString("order_id"));
		//支付状态
		System.out.println("支付状态 : " +jo.getString("status"));
		return jsn;
	}
	
	/**
	 * 取消订单
	 * @param request
	 * @param response
	 */
	@RequestMapping(value = "/orderRemove", method = RequestMethod.GET)
	@ResponseBody
	public void orderRemove(HttpServletRequest request, HttpServletResponse response) {
		response.setHeader("Content-type", "text/html;charset=UTF-8");
		String out_no = request.getParameter("order_id");
		aesPost d = new aesPost();
		String pathUrl = "";
		JSONObject jsn = new JSONObject();
		//商户订单号
		jsn.put("out_trade_no", out_no);
		pathUrl = cancel_url;
		jsn = d.CreateConnection(pathUrl, jsn);
		JSONObject jo = new JSONObject();
		jo = jsn.getJSONObject("ret_content");
		
		System.out.println("取消订单结果");
		//商户订单号
		System.out.println("商户订单号 :"+jo.getString("out_trade_no"));
		//订单号
		System.out.println("订单号 :" + jo.getString("order_id"));
		
	}
	
	/**
	 * 订单通知
	 * @param request
	 * @param response
	 */
	@RequestMapping(value = "/notify", method = RequestMethod.POST)
	@ResponseBody
	public String orderNotices(HttpServletRequest request, HttpServletResponse response) {
		response.setContentType("text/html;charset=utf-8");
		String params = request.getParameter("param");
		String signs = request.getParameter("sign");
		String signF = id+params+sign_key;
		signF = aesPost.getMD5(signF);
		signF = signF.toLowerCase();
		if(signF.equals(signs)){//校验请求
			//String out_no = request.getParameter("order_id");
			JSONObject jsb = new JSONObject();
			aesPost aep = new aesPost();
			params = aep.aesDecode(params);
			jsb = JSONObject.fromObject(params);
			//商户订单号 
			String out_no = jsb.getString("out_trade_no");
			//订单号 
			String order_id = jsb.getString("order_id");
			SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			//支付成功时间
			String time_end = df.format(new Date());
			//用户uid
			String uid = jsb.getString("uid");
			
			//处理业务逻辑
			
			System.out.println("商户订单号 ：" + order_id);
			System.out.println("订单号 ：" + out_no);
			System.out.println("支付成功时间 ：" + time_end);
			System.out.println("用户uid ：" + uid);
			return "success";
		}
		return null;
	}
	
	/**
	 * 退款
	 * 
	 * @param request
	 * @param response
	 */
	@RequestMapping(value = "/orderRefund", method = RequestMethod.GET)
	@ResponseBody
	public void orderRefund(HttpServletRequest request, HttpServletResponse response) {
		response.setHeader("Content-type", "text/html;charset=UTF-8");
		String out_no = request.getParameter("order_id");
		String refund_fee = "1";//request.getParameter("refund_fee");
		aesPost d = new aesPost();
		String pathUrl = "";
		JSONObject jsn = new JSONObject();
		//商户订单号
		jsn.put("out_trade_no", out_no);
		//退款金额
		jsn.put("refund_fee", refund_fee);
		pathUrl = order_refund;
		jsn = d.CreateConnection(pathUrl, jsn);
		JSONObject jo = new JSONObject();
		  
		jo = jsn.getJSONObject("ret_content");
		System.out.println("退款结果");
		//商户订单号
		System.out.println("商户订单号 :"+jo.getString("out_trade_no"));
		//订单号
		System.out.println("订单号 :" + jo.getString("order_id"));
		
		//业务处理
	}
}
