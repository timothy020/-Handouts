package cn.lntd.venues.module.business.util.dataImport.service;

import cn.lntd.venues.framework.common.pojo.CommonResult;

import java.io.IOException;

public interface DataImportService {
    /**
     * 导入本科生信息
     */
    void undergraduateStu2Members();

    /**
     * 导入研究生信息
     */
    void postgraduateStu2Members();

    /**
     * 导入教职工信息
     */
    void staff2Members();

    /**
     * 导入部门信息
     */
    void importDeptInfo();

}
