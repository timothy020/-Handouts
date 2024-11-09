package com.atguigu.servlet;

import jakarta.servlet.RequestDispatcher;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;

@WebServlet("/servletA")
public class ServletA extends HttpServlet {
    @Override
    protected void service(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        System.out.println("ServletA执行了");
        // 请求转发给ServletB
        // 1.获得请求转发器
        RequestDispatcher requestDispatcher = req.getRequestDispatcher("servletB");
        // 2.做出转发动作
        requestDispatcher.forward(req, resp);

        // 也可以转发给视图资源
        req.getRequestDispatcher("a.html").forward(req, resp);

        // 转发到 WEB-INF 目录下的资源，访问WEB-INF下受保护资源的唯一访问方式
        req.getRequestDispatcher("WEB_INF/b.html").forward(req, resp);

    }
}
