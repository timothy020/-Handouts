package com.example.httpscript;

import cn.hutool.http.HttpUtil;
import cn.hutool.json.JSONUtil;
import com.example.httpscript.resp.*;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.springframework.stereotype.Service;
import org.springframework.web.util.UriComponentsBuilder;

import java.io.FileWriter;
import java.io.IOException;
import java.net.URI;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@Service
public class HttpApiServiceImpl implements HttpService {

    private final ObjectMapper objectMapper;

    private final String tokenUrl = "https://hcsoxj.cdutcm.edu.cn/open_api/authentication/get_access_token";
    private final String key = "20240614200018015250858452008963019";
    private final String secret = "2f2c48e21340e2873d7e5612eb00674a6574b97e";
    private final String cardUrl = "https://hcsoxj.cdutcm.edu.cn/open_api/customization/tyktyktzhxxb/full";
    private final String staffUrl = "https://hcsoxj.cdutcm.edu.cn/open_api/customization/tgxjgjzgjbxx/full";
    private final String underStuUrl = "https://hcsoxj.cdutcm.edu.cn/open_api/customization/tgxxsbzksjbxx/full";
    private final String postStuUrl = "https://hcsoxj.cdutcm.edu.cn/open_api/customization/tgxxsyjsxsjbxx/full";
    private final String deptUrl = "https://hcsoxj.cdutcm.edu.cn/open_api/customization/tgxxxyxsdwxx/full";
    private final String underStuMajorUrl = "https://hcsoxj.cdutcm.edu.cn/open_api/customization/tgxjxbzkszyjbxx/full";
    private final String underStuClassUrl = "https://hcsoxj.cdutcm.edu.cn/open_api/customization/tgxxsbzksbjjbxx/full";
    private final String postStuMajorUrl = "https://hcsoxj.cdutcm.edu.cn/open_api/customization/tgxjxyjszyxx/full";

    public HttpApiServiceImpl() {
        this.objectMapper = new ObjectMapper();
    }

    /**
     * 获得一卡通信息
     */
    @Override
    public void getCardInfo() {
        // 获取token
        String token = getToken();

        List<CardResp.Result.Data> allData = new ArrayList<>();
        int currentPage = 1;
        int maxPage;

        do {
            CardResp response = getResult(token, cardUrl, currentPage, CardResp.class);

            if (response != null && response.getResult() != null) {
                CardResp.Result result = response.getResult();
                allData.addAll(result.getData());
                maxPage = result.getMaxPage();
                currentPage++;
            } else {
                break;
            }
        } while (currentPage <= maxPage);

        writeCardDataToFile(allData, "./card.txt");
        System.out.println("一卡通信息获取完毕，数据总量："+allData.size());
    }

    /**
     * 获得教职工信息
     */
    @Override
    public void getStaffInfo() {
        // 获取token
        String token = getToken();

        List<StaffResp.Result.Data> allData = new ArrayList<>();
        int currentPage = 1;
        int maxPage;

        do {
            StaffResp response = getResult(token, staffUrl, currentPage, StaffResp.class);

            if (response != null && response.getResult() != null) {
                StaffResp.Result result = response.getResult();
                allData.addAll(result.getData());
                maxPage = result.getMaxPage();
                currentPage++;
            } else {
                break;
            }
        } while (currentPage <= maxPage);

        writeCardDataToFile(allData, "./staff.txt");
        System.out.println("教职工信息获取完毕，数据总量："+allData.size());
    }

    /**
     * 本科生信息
     */
    @Override
    public void getUnderStuInfo() {
        // 获取token
        String token = getToken();

        List<UnderStuResp.Result.Data> allData = new ArrayList<>();
        int currentPage = 1;
        int maxPage;

        do {
            UnderStuResp response = getResult(token, underStuUrl, currentPage, UnderStuResp.class);

            if (response != null && response.getResult() != null) {
                UnderStuResp.Result result = response.getResult();
                allData.addAll(result.getData());
                maxPage = result.getMaxPage();
                currentPage++;
            } else {
                break;
            }
        } while (currentPage <= maxPage);

        writeCardDataToFile(allData, "./underStu.txt");
        System.out.println("本科生信息获取完毕，数据总量："+allData.size());
    }

    /**
     * 研究生信息
     */
    @Override
    public void getPostStuInfo() {
        // 获取token
        String token = getToken();

        List<PostStuResp.Result.Data> allData = new ArrayList<>();
        int currentPage = 1;
        int maxPage;

        do {
            PostStuResp response = getResult(token, postStuUrl, currentPage, PostStuResp.class);

            if (response != null && response.getResult() != null) {
                PostStuResp.Result result = response.getResult();
                allData.addAll(result.getData());
                maxPage = result.getMaxPage();
                currentPage++;
            } else {
                break;
            }
        } while (currentPage <= maxPage);

        writeCardDataToFile(allData, "./postStu.txt");
        System.out.println("研究生信息获取完毕，数据总量："+allData.size());
    }

    /**
     * 院系信息
     */
    @Override
    public void getDeptInfo() {
        // 获取token
        String token = getToken();

        List<DeptResp.Result.Data> allData = new ArrayList<>();
        int currentPage = 1;
        int maxPage;

        do {
            DeptResp response = getResult(token, deptUrl, currentPage, DeptResp.class);

            if (response != null && response.getResult() != null) {
                DeptResp.Result result = response.getResult();
                allData.addAll(result.getData());
                maxPage = result.getMaxPage();
                currentPage++;
            } else {
                break;
            }
        } while (currentPage <= maxPage);

        writeCardDataToFile(allData, "./deptInfo.txt");
        System.out.println("院系信息获取完毕，数据总量："+allData.size());
    }

    /**
     * 本科生专业信息
     */
    @Override
    public void getUnderStuMajor() {
        // 获取token
        String token = getToken();

        List<UnderStuMajorResp.Result.Data> allData = new ArrayList<>();
        int currentPage = 1;
        int maxPage;

        do {
            UnderStuMajorResp response = getResult(token, underStuMajorUrl, currentPage, UnderStuMajorResp.class);

            if (response != null && response.getResult() != null) {
                UnderStuMajorResp.Result result = response.getResult();
                allData.addAll(result.getData());
                maxPage = result.getMaxPage();
                currentPage++;
            } else {
                break;
            }
        } while (currentPage <= maxPage);

        writeCardDataToFile(allData, "./underStuMajor.txt");
        System.out.println("本科生专业信息获取完毕，数据总量："+allData.size());
    }

    /**
     * 本科生班级信息
     */
    @Override
    public void getUnderStuClass() {
        // 获取token
        String token = getToken();

        List<UnderStuClassResp.Result.Data> allData = new ArrayList<>();
        int currentPage = 1;
        int maxPage;

        do {
            UnderStuClassResp response = getResult(token, underStuClassUrl, currentPage, UnderStuClassResp.class);

            if (response != null && response.getResult() != null) {
                UnderStuClassResp.Result result = response.getResult();
                allData.addAll(result.getData());
                maxPage = result.getMaxPage();
                currentPage++;
            } else {
                break;
            }
        } while (currentPage <= maxPage);

        writeCardDataToFile(allData, "./underStuClass.txt");
        System.out.println("本科生班级信息获取完毕，数据总量："+allData.size());
    }

    /**
     * 研究生专业信息
     */
    @Override
    public void getPostStuMajor() {
        // 获取token
        String token = getToken();

        List<PostStuMajorResp.Result.Data> allData = new ArrayList<>();
        int currentPage = 1;
        int maxPage;

        do {
            PostStuMajorResp response = getResult(token, postStuMajorUrl, currentPage, PostStuMajorResp.class);

            if (response != null && response.getResult() != null) {
                PostStuMajorResp.Result result = response.getResult();
                allData.addAll(result.getData());
                maxPage = result.getMaxPage();
                currentPage++;
            } else {
                break;
            }
        } while (currentPage <= maxPage);

        writeCardDataToFile(allData, "./postStuMajor.txt");
        System.out.println("研究生专业信息获取完毕，数据总量："+allData.size());
    }


    private <T> T getResult(String token, String queryUrl, int currentPage, Class<T> respClass) {
        Map<String, Object> paramMap = new HashMap<>();
        paramMap.put("access_token", token);
        paramMap.put("page", currentPage);
        paramMap.put("per_page", 1000);
        String resp = HttpUtil.get(queryUrl, paramMap);
        return JSONUtil.toBean(resp, respClass);
    }

    private String getToken() {
        Map<String, Object> paramMap = new HashMap<>();
        paramMap.put("key", key);
        paramMap.put("secret", secret);
        String resp = HttpUtil.get(tokenUrl, paramMap);
        TokenResp tokenResp = JSONUtil.toBean(resp, TokenResp.class);
        return tokenResp.getResult().getAccess_token();
    }


    private URI buildURI(String baseUrl, String token, int perPage, int currentPage) {
        return UriComponentsBuilder.fromHttpUrl(baseUrl)
                .queryParam("access_token", token)
                .queryParam("page", currentPage)
                .queryParam("per_page", perPage)
                .build()
                .toUri();
    }

    private <T> void writeCardDataToFile(List<T> data, String outputFilePath) {
        try (FileWriter writer = new FileWriter(outputFilePath)) {
            objectMapper.writeValue(writer, data);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
