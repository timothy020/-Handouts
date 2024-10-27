package com.example.httpscript;

import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;

@SpringBootApplication
public class Application {

    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
        System.out.println("运行结束");
    }

    @Bean
    CommandLineRunner run(HttpApiServiceImpl httpApiServiceImpl) {
        return args -> {
            httpApiServiceImpl.getCardInfo();
            httpApiServiceImpl.getStaffInfo();
            httpApiServiceImpl.getUnderStuInfo();
            httpApiServiceImpl.getPostStuInfo();
            httpApiServiceImpl.getDeptInfo();
            httpApiServiceImpl.getUnderStuMajor();
            httpApiServiceImpl.getUnderStuClass();
            httpApiServiceImpl.getPostStuMajor();
        };
    }
}
