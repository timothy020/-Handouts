package com.atguigu.servlet;

import jakarta.servlet.Servlet;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.io.PrintWriter;

/**
 * Servlet开发流程
 * 1. 创建javaweb项目，同时将tomcat作为项目依赖
 * 2. 重写service方法，service(HttpServletRequest req, HttpServletResponse resp)
 * 3. 在service方法中，定义业务处理代码
 * 4. 在web.xml中，配置Servlet的访问路径
 */

@WebServlet("/userName")
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
