package cn.lntd.venues.module.business.util.dataImport.service;

import cn.hutool.core.util.IdUtil;
import cn.lntd.venues.module.business.admin.whiteList.dal.domain.WhitelistInfoDO;
import cn.lntd.venues.module.business.constant.MemberGrade;
import cn.lntd.venues.module.business.user.member.dal.domain.MembersDO;
import cn.lntd.venues.module.business.user.member.service.MembersService;
import cn.lntd.venues.module.business.util.dataImport.dal.domain.*;
import cn.lntd.venues.module.business.util.dataImport.dal.mapper.*;
import cn.lntd.venues.module.system.controller.admin.dept.vo.dept.DeptListReqVO;
import cn.lntd.venues.module.system.dal.dataobject.dept.DeptDO;
import cn.lntd.venues.module.system.service.dept.DeptService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.validation.annotation.Validated;

import javax.annotation.Resource;
import java.util.*;
import java.util.stream.Collectors;

@Service
@Validated
@Slf4j
public class DataImportServiceImpl implements DataImportService{
    @Resource
    private MembersService membersService;
    @Resource
    private DeptService deptService;
    @Resource
    private PrdStaffResultMapper prdStaffResultMapper;
    @Resource
    private PrdUndergraduateStuResultMapper prdUndergraduateStuResultMapper;
    @Resource
    private PrdPostgraduateStuResultMapper prdPostgraduateStuResultMapper;
    @Resource
    private PrdDepartmentInfoMapper prdDepartmentInfoMapper;
    @Resource
    private PrdUndergraduateMajorMapper prdUndergraduateMajorMapper;
    @Resource
    private PrdPostgraduateMajorMapper prdPostgraduateMajorMapper;

    @Override
    @Transactional
    public void undergraduateStu2Members() {
        log.info("开始导入本科生信息到会员表");
        Map<String, List<DeptDO>> deptCode2DOListMap = buildDeptCode2DOListMap();
        List<PrdUndergraduateStuResultDO> prdUndergraduateStuResultDOS = prdUndergraduateStuResultMapper.selectList();

        // 插入会员表
        List<MembersDO> membersDOS = buildMemberDOListByStuResultDO(prdUndergraduateStuResultDOS, deptCode2DOListMap);
        membersService.insertBatch(membersDOS);

        // 插入白名单
//        List<WhitelistInfoDO> whitelistInfoDOS = buildWhiteListInfoDOS(membersDOS);
//        whitelistInfoService.insertBatch(whitelistInfoDOS);
        log.info("结束导入本科生信息到会员表，插入数量：" + membersDOS.size());
    }

    @Override
    @Transactional
    public void postgraduateStu2Members() {
        log.info("开始导入研究生信息到会员表");
        Map<String, List<DeptDO>> deptCode2DOListMap = buildDeptCode2DOListMap();
        List<PrdPostgraduateStuResultDO> prdPostgraduateStuResultDOS = prdPostgraduateStuResultMapper.selectList();

        // 插入会员表
        List<MembersDO> membersDOS = buildMemberDOListByStuResultDO(prdPostgraduateStuResultDOS, deptCode2DOListMap);
        membersService.insertBatch(membersDOS);

        // 插入白名单
//        List<WhitelistInfoDO> whitelistInfoDOS = buildWhiteListInfoDOS(membersDOS);
//        whitelistInfoService.insertBatch(whitelistInfoDOS);
        log.info("结束导入研究生信息到会员表，插入数量：" + membersDOS.size());
    }

    @Override
    @Transactional
    public void staff2Members() {
        log.info("开始导入教职工信息到会员表");
        Map<String, List<DeptDO>> deptCode2DOListMap = buildDeptCode2DOListMap();
        List<PrdStaffResultDO> prdStaffResultDOS = prdStaffResultMapper.selectList();
        List<MembersDO> membersDOS = new ArrayList<>();

        // 插入会员表
        for(PrdStaffResultDO staffResultDO : prdStaffResultDOS){
            MembersDO membersDO = new MembersDO();
            membersDO.setId(IdUtil.getSnowflakeNextId());
            membersDO.setCode(staffResultDO.getGh());
            membersDO.setName(staffResultDO.getXm());
            membersDO.setCardNumber(staffResultDO.getWlkh());
            membersDO.setGrade(MemberGrade.STAFF.getCode());

            String szdwbm = staffResultDO.getSzdwbm();
            Long deptIdByCode = getDeptIdByCode(deptCode2DOListMap, szdwbm);
            membersDO.setDeptId(deptIdByCode);

            membersDOS.add(membersDO);
        }

        membersService.insertBatch(membersDOS);

//        // 插入白名单
//        List<WhitelistInfoDO> whitelistInfoDOS = buildWhiteListInfoDOS(membersDOS)
//        whitelistInfoService.insertBatch(whitelistInfoDOS);

        log.info("结束导入教职工信息到会员表，插入数量：" + membersDOS.size());
    }

    private List<MembersDO> buildMemberDOListByStuResultDO(List<? extends PrdStuResultBaseDO> prdStuResultBaseDOS,
                                                           Map<String, List<DeptDO>> deptCode2DOListMap) {
        List<MembersDO> membersDOS = new ArrayList<>();

        for(PrdStuResultBaseDO prdStuResultBaseDO : prdStuResultBaseDOS){
            MembersDO membersDO = new MembersDO();
            membersDO.setId(IdUtil.getSnowflakeNextId());
            membersDO.setCode(prdStuResultBaseDO.getXh());
            membersDO.setName(prdStuResultBaseDO.getXm());
            membersDO.setCardNumber(prdStuResultBaseDO.getWlkh());
            membersDO.setGrade(MemberGrade.STUDENT.getCode());

            String yxbm = prdStuResultBaseDO.getYxbm();
            Long deptId= getDeptIdByCode(deptCode2DOListMap, yxbm);
//            membersDO.setDeptId(deptId);

            String majorCode = prdStuResultBaseDO.getZybm();

            Long majorId = getMajorIdByCode(deptCode2DOListMap, deptId, majorCode);
            // 专业编码作为部门编码
            membersDO.setDeptId(majorId);

            membersDOS.add(membersDO);
//             TODO：班级编码
//            String classCode = prdStuResultBaseDO.getBjbm();
        }
        return membersDOS;
    }

    private List<WhitelistInfoDO> buildWhiteListInfoDOS(List<MembersDO> membersDOS) {
        List<WhitelistInfoDO> result = new ArrayList<>();
        for(MembersDO membersDO : membersDOS) {
            WhitelistInfoDO whitelistInfoDO = new WhitelistInfoDO();
            whitelistInfoDO.setCustomId(membersDO.getId());
            whitelistInfoDO.setCustomName(membersDO.getName());
            whitelistInfoDO.setMemberGrade(membersDO.getGrade());
            whitelistInfoDO.setDeptId(membersDO.getDeptId());

            result.add(whitelistInfoDO);
        }

        return result;
    }

    private Long getMajorIdByCode(Map<String, List<DeptDO>> deptCode2DOListMap, Long deptId,  String majorCode) {
        List<DeptDO> majorList = deptCode2DOListMap.get(majorCode);
        if(majorList == null || majorList.isEmpty()) {
            System.err.println("专业id不存在, 专业编码: " + majorCode);
            return null;
        }
        if(majorList.size() == 1) {
            return majorList.get(0).getId();
        }else {
            Optional<DeptDO> first = majorList.stream().filter(major -> major.getParentId().equals(deptId)).findFirst();
            return  first.get().getId();
        }
    }

    private Long getDeptIdByCode(Map<String, List<DeptDO>> deptCode2DOListMap, String yxbm) {
        List<DeptDO> deptDOS = deptCode2DOListMap.get(yxbm);

        if(deptDOS == null || deptDOS.isEmpty()) {
            System.err.println("部门id不存在，院系编码: " + yxbm);
            return null;
        } else if(deptDOS.size() > 1) {
            System.err.println("存在多个部门id，院系编码: " + yxbm);
            return null;
        }

        return deptDOS.get(0).getId();
    }

    private Map<String, List<DeptDO>> buildDeptCode2DOListMap() {
        Map<String, List<DeptDO>> deptCode2DOListMap = new HashMap<>();
        List<DeptDO> deptList = deptService.getDeptList(new DeptListReqVO());
        for (DeptDO deptDO : deptList) {
            String deptCode = deptDO.getDeptCode();
            if (deptCode2DOListMap.containsKey(deptCode)) {
                deptCode2DOListMap.get(deptCode).add(deptDO);
            } else {
                List<DeptDO> values = new ArrayList<>();
                values.add(deptDO);
                deptCode2DOListMap.put(deptCode, values);
            }
        }
        return deptCode2DOListMap;
    }

    @Override
    @Transactional
    public void importDeptInfo(){
        log.info("开始导入部门和专业表");
        // 1. 获取部门和专业信息
        List<PrdDepartmentInfoDO> prdDepartmentInfoDOS = prdDepartmentInfoMapper.selectList();
        List<PrdUndergraduateMajorDO> prdUndergraduateMajorDOS = prdUndergraduateMajorMapper.selectList();
        List<PrdPostgraduateMajorDO> prdPostgraduateMajorDOS = prdPostgraduateMajorMapper.selectList();

        // 2.构建数据
        // 2.1 创建一个map，存储部门的父机构编码（因为数据表只有parentId而没有parentCode字段）
        Map<Long, String> deptId2ParentCode = new HashMap<>();

        // 2.2插入部门表
        List<DeptDO> deptDOS = new ArrayList<>();
        for(PrdDepartmentInfoDO prdDepartmentInfoDO : prdDepartmentInfoDOS) {
            DeptDO deptDO = new DeptDO();
            deptDO.setId(IdUtil.getSnowflakeNextId());
            deptDO.setDeptCode(prdDepartmentInfoDO.getDwbm());
            deptDO.setSort(Integer.parseInt(prdDepartmentInfoDO.getSjsx()));
            deptDO.setName(prdDepartmentInfoDO.getDwmc());
            deptDO.setStatus(0);
            deptDO.setType(1); //1-部门，2-本科专业，3-研究生专业

            // 暂存隶属单位编码
            String lsdwbm = prdDepartmentInfoDO.getLsdwbm();
            if(lsdwbm.equals(".")) { //没有父机构
                deptId2ParentCode.put(deptDO.getId(), ".");
            } else {
                deptId2ParentCode.put(deptDO.getId(), lsdwbm);
            }

            deptDOS.add(deptDO);
        }
        // 2.3插入专业表
        for (PrdUndergraduateMajorDO prdUndergraduateMajorDO : prdUndergraduateMajorDOS) {
            DeptDO deptDO = new DeptDO();
            deptDO.setId(IdUtil.getSnowflakeNextId());
            deptDO.setDeptCode(prdUndergraduateMajorDO.getZybm());
            deptDO.setSort(0);
            deptDO.setName(prdUndergraduateMajorDO.getZymc());
            deptDO.setStatus(0);
            deptDO.setType(2); //1-部门，2-本科专业，3-研究生专业

            deptId2ParentCode.put(deptDO.getId(), prdUndergraduateMajorDO.getYxbm());

            deptDOS.add(deptDO);
        }
        for (PrdPostgraduateMajorDO prdPostgraduateMajorDO : prdPostgraduateMajorDOS) {
            DeptDO deptDO = new DeptDO();
            deptDO.setId(IdUtil.getSnowflakeNextId());
            deptDO.setDeptCode(prdPostgraduateMajorDO.getZybm());
            deptDO.setSort(0);
            deptDO.setName(prdPostgraduateMajorDO.getZymc());
            deptDO.setStatus(0);
            deptDO.setType(3); //1-部门，2-本科专业，3-研究生专业

            deptId2ParentCode.put(deptDO.getId(), prdPostgraduateMajorDO.getYxbm());

            deptDOS.add(deptDO);
        }

        Map<String, Long> deptCode2IdMap = new HashMap<>();

        // 3.更新parentId字段
        // 3.1 构造编码和id的映射
        // 【研究生专业存在专业编码deptCode相同但是院系编码parentCode不同的情况
        //   会导致deptCode2Id有duplicate key
        //   但是由于专业编码不可能作为parentCode，所以直接忽略duplicate key，任意保留一个，不报错即可】
        deptCode2IdMap = deptDOS.stream().collect(Collectors.toMap(DeptDO::getDeptCode, DeptDO::getId, (existingValue, newValue) -> existingValue));

        // 3.2 更新
        for (DeptDO deptDO : deptDOS) {
            Long id = deptDO.getId();
            // 找到deptDO的parentCode
            String parentCode = deptId2ParentCode.get(id);
            if(parentCode == null) {
                System.out.println("parentCode为null，deptDO为："+ deptDO);
                continue;
            }
            // 根据parentCode找到parentId
            if(parentCode.equals(".")) {
                deptDO.setParentId(0L);
            } else {
                Long parentId = deptCode2IdMap.get(parentCode);
                deptDO.setParentId(parentId);
            }
        }

        // 4.插入数据
        deptService.insertBatch(deptDOS);

        log.info("结束导入部门和专业表");
    }


}
