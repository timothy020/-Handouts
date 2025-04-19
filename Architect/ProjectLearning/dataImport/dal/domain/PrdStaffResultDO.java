package cn.lntd.venues.module.business.util.dataImport.dal.domain;

import cn.lntd.venues.framework.mybatis.core.dataobject.BaseDO;
import com.baomidou.mybatisplus.annotation.KeySequence;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.*;

@TableName("prd_staff_result")
@KeySequence("prd_staff_result_seq") // 用于 Oracle、PostgreSQL、Kingbase、DB2、H2 数据库的主键自增。如果是 MySQL 等数据库，可不写。
@Data
@ToString(callSuper = true)
@Builder
@NoArgsConstructor
@AllArgsConstructor
public class PrdStaffResultDO {
    /**
     * 工号
     */
    @TableField("GH")
    private String gh;

    /**
     * 姓名
     */
    @TableField("XM")
    private String xm;

    /**
     * 所在单位编码
     */
    @TableField("SZDWBM")
    private String szdwbm;

    /**
     * 物理卡号
     */
    @TableField("WLKH")
    private String wlkh;

    /**
     * 卡序列号
     */
    @TableField("KXLH")
    private String kxlh;

    /**
     * 单位名称
     */
    @TableField("DWMC")
    private String dwmc;

    /**
     * 隶属单位编码
     */
    @TableField("LSDWBM")
    private String lsdwbm;
}
