package com.pay.demo.controller;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.net.URL;
import java.net.URLConnection;
import java.net.URLEncoder;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

import org.apache.commons.codec.binary.Base64;

import net.sf.json.JSONObject;

public class aesPost {

	public static aesPost aep = new aesPost();
	Map<String, String> mapParam = new HashMap<String, String>();
    TestController testController = new TestController();
    
    /**
     * 校验sign
     */
    public boolean checkSign(JSONObject flag){
    	Integer ret_code = flag.getInt("ret_code");
    	String ret_content = flag.getString("ret_content");
    	String signKey = testController.getSignKey();
		String str = ret_code+ret_content+signKey;
		String sign = aesPost.getMD5(str);
		String signFlag = flag.getString("sign").toLowerCase();
		StringBuffer bf = new StringBuffer();
		for (int i = 0; i < sign.length(); i++) {
			char a = sign.charAt(i); // 根据下标取字符
			String as = (new Character(a)).toString();// 通过包装类把字符转成字符串类型
			bf.append(as.toLowerCase());
		}
		sign = bf.toString();
		if(sign.equals(signFlag)){
			return true;
		}
		return false;
    }
    
	/**
	 * 发送post请求
	 */
	public static String sendPost(String url, Map<String, String> paramMap) {
		PrintWriter out = null;
		BufferedReader in = null;
		String result = "";
		try {
			URL realUrl = new URL(url);
			// 打开和URL之间的连接
			URLConnection conn = realUrl.openConnection();
			// 设置通用的请求属性
			conn.setRequestProperty("accept", "*/*");
			conn.setRequestProperty("connection", "Keep-Alive");
			conn.setRequestProperty("user-agent", "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1;SV1)");
			conn.setRequestProperty("Charset", "UTF-8");
			// 发送POST请求必须设置如下两行
			conn.setDoOutput(true);
			conn.setDoInput(true);
			// 获取URLConnection对象对应的输出流
			out = new PrintWriter(conn.getOutputStream());
			// 设置请求属性
			String param = "";
			if (paramMap != null && paramMap.size() > 0) {
				Iterator<String> ite = paramMap.keySet().iterator(); 
				while (ite.hasNext()) {
					String key = ite.next();// key
					String value = paramMap.get(key);
					param += key + "=" + value + "&";
				}
				param = param.substring(0, param.length() - 1);
			}
			// 发送请求参数
			out.print(param);
			// flush输出流的缓冲
			out.flush();
			// 定义BufferedReader输入流来读取URL的响应
			in = new BufferedReader(new InputStreamReader(conn.getInputStream()));
			String line;
			while ((line = in.readLine()) != null) {
				result += line;
			}
		} catch (Exception e) {
			System.err.println("发送 POST 请求出现异常！" + e);
			e.printStackTrace();
		}
		// 使用finally块来关闭输出流、输入流
		finally {
			try {
				if (out != null) {
					out.close();
				}
				if (in != null) {
					in.close();
				}
			} catch (IOException ex) {
				ex.printStackTrace();
			}
		}
		return result;
	}

	/**
	 * aes加密
	 * 
	 * @param param
	 * @return
	 */
	public String aesEncode(String param) {
		String encodingAesKey = testController.getAesKey();
		String replyMsg = param;
		Cipher cipher;
		try {
			cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
			SecretKeySpec keySpec = new SecretKeySpec(encodingAesKey.getBytes(), "AES");
			IvParameterSpec iv = new IvParameterSpec(encodingAesKey.getBytes(), 0, 16);
			cipher.init(Cipher.ENCRYPT_MODE, keySpec, iv);

			// 加密
			byte[] encrypted = cipher.doFinal(replyMsg.getBytes("utf-8"));
			// 使用BASE64对加密后的字符串进行编码
			String base64Encrypted = new Base64().encodeToString(encrypted);
			return base64Encrypted;
		} catch (NoSuchAlgorithmException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;
	}

	/**
	 * aes解密
	 */
	public String aesDecode(String param) {
		byte[] bs = new Base64().decode(param);
		Cipher cipher;
		String ret = "";
		try {
			cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
			String encodingAesKey = testController.getAesKey();
			SecretKeySpec keySpec = new SecretKeySpec(encodingAesKey.getBytes(), "AES");
			IvParameterSpec iv = new IvParameterSpec(encodingAesKey.getBytes(), 0, 16);
			cipher.init(Cipher.DECRYPT_MODE, keySpec, iv);
			bs = cipher.doFinal(bs);
			ret = new String(bs, "utf8");
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (NoSuchAlgorithmException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (NoSuchPaddingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InvalidKeyException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InvalidAlgorithmParameterException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalBlockSizeException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (BadPaddingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return ret;
	}

	/**
	 * 生成md5
	 * 
	 * @param message
	 * @return
	 */
	public static String getMD5(String message) {
		String md5str = "";
		try {
			// 1 创建一个提供信息摘要算法的对象，初始化为md5算法对象
			MessageDigest md = MessageDigest.getInstance("MD5");

			// 2 将消息变成byte数组
			byte[] input = message.getBytes();

			// 3 计算后获得字节数组,这就是那128位了
			byte[] buff = md.digest(input);

			// 4 把数组每一字节（一个字节占八位）换成16进制连成md5字符串
			md5str = bytesToHex(buff);

		} catch (Exception e) {
			e.printStackTrace();
		}
		return md5str;
	}

	/**
	 * 二进制转十六进制
	 * 
	 * @param bytes
	 * @return
	 */
	public static String bytesToHex(byte[] bytes) {
		StringBuffer md5str = new StringBuffer();
		// 把数组每一字节换成16进制连成md5字符串
		int digital;
		for (int i = 0; i < bytes.length; i++) {
			digital = bytes[i];

			if (digital < 0) {
				digital += 256;
			}
			if (digital < 16) {
				md5str.append("0");
			}
			md5str.append(Integer.toHexString(digital));
		}
		return md5str.toString().toUpperCase();
	}

	/**
	 * 创建请求数据
	 * 
	 * @throws NoSuchAlgorithmException
	 * @throws NoSuchPaddingException
	 * @throws InvalidAlgorithmParameterException
	 * @throws InvalidKeyException
	 * @throws BadPaddingException
	 * @throws IllegalBlockSizeException
	 */
	public JSONObject CreateConnection(String url, JSONObject jsn) {
		mapParam.put("id", testController.getId());
		String param = jsn.toString();
		param = aep.aesEncode(param);
		String str = testController.getId() + param + testController.getSignKey();
		try {
			String sign = aesPost.getMD5(str);
			StringBuffer bf = new StringBuffer();
			for (int i = 0; i < sign.length(); i++) {
				char a = sign.charAt(i); // 根据下标取字符
				String as = (new Character(a)).toString();// 通过包装类把字符转成字符串类型
				bf.append(as.toLowerCase());
			}
			sign = bf.toString();
			param = URLEncoder.encode(param, "utf-8");
			mapParam.put("param", param);
			mapParam.put("sign", sign);
			String result = aesPost.sendPost(url, mapParam);
			JSONObject jsonObject = new JSONObject();
			jsonObject = JSONObject.fromObject(result);
			String ret_content = (String) jsonObject.get("ret_content");
			ret_content = aep.aesDecode(ret_content);
			if (jsonObject.get("ret_code").equals(0) && aep.checkSign(jsonObject)) {
				jsonObject.put("param", ret_content);
				JSONObject jsb = JSONObject.fromObject(ret_content);
				if (jsb.get("url") != null) {
					jsonObject.put("url_image", jsb.get("url"));
				}
				jsonObject.put("ret_content", jsb);
			} else {
				jsonObject.put("ret_content", ret_content);
				jsonObject.put("ret_code", -1);
			}
			return jsonObject;
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;
	}

}
