package cn.lntd.venues.module.business.util.dataImport.controller;


import cn.lntd.venues.framework.common.pojo.CommonResult;
import cn.lntd.venues.module.business.admin.activityCancellation.service.ActivityCancellationService;
import cn.lntd.venues.module.business.admin.activityCancellation.vo.ActivityCancellationSaveReqVO;
import cn.lntd.venues.module.business.constant.RestApiConstant;
import cn.lntd.venues.module.business.util.dataImport.service.DataImportService;
import com.fasterxml.jackson.core.JsonProcessingException;
import io.swagger.v3.oas.annotations.Operation;
import io.swagger.v3.oas.annotations.tags.Tag;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import javax.annotation.security.PermitAll;
import javax.validation.Valid;

import static cn.lntd.venues.framework.common.pojo.CommonResult.success;

@Tag(name = "管理后台 - 数据导入")
@RestController
@RequestMapping(RestApiConstant.REST_TOB_PATH_PREFIX+"/data-import")
@Validated
public class DataImportController {
    @Resource
    private DataImportService dataImportService;

    /**
     * ================ 成都中医药大学开放数据导入 ================
     */
    @GetMapping("undergraduate-to-members")
    @Operation(summary = "本科生信息导入会员表")
    @PermitAll
    public CommonResult<Boolean> importUndergraduateStuInfoToMembers() {
        dataImportService.undergraduateStu2Members();
        return success(true);
    }


    @GetMapping("postgraduate-to-members")
    @Operation(summary = "研究生信息导入会员表")
    @PermitAll
    public CommonResult<Boolean> importPostgraduateStuInfoToMembers() {
        dataImportService.postgraduateStu2Members();
        return success(true);
    }

    @GetMapping("staff-to-members")
    @Operation(summary = "教职工信息导入会员表")
    @PermitAll
    public CommonResult<Boolean> importStaffInfoToMembers() {
        dataImportService.staff2Members();
        return success(true);
    }

    @GetMapping("import-department")
    @Operation(summary = "导入部门表")
    @PermitAll
    public CommonResult<Boolean> importDeptInfo() {
        dataImportService.importDeptInfo();
        return success(true);
    }
}
