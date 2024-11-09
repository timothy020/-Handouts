package com.example.httpscript;

public interface HttpService {
    /**
     * 获得一卡通信息
     */
    public void getCardInfo();

    /**
     * 获得教职工信息
     */
    public void getStaffInfo();

    /**
     * 本科生信息
     */
    public void getUnderStuInfo();

    /**
     * 研究生信息
     */
    public void getPostStuInfo();

    /**
     * 院系信息
     */
    public void getDeptInfo();

    /**
     * 本科生专业信息
     */
    public void getUnderStuMajor();

    /**
     * 本科生班级信息
     */
    public void getUnderStuClass();

    /**
     * 研究生专业信息
     */
    public void getPostStuMajor();


}
