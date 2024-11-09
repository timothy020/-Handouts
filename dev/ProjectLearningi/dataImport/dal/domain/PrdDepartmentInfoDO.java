package cn.lntd.venues.module.business.util.dataImport.dal.domain;

import com.baomidou.mybatisplus.annotation.KeySequence;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.*;

@TableName("prd_department_info")
@KeySequence("prd_department_info_seq") // 用于 Oracle、PostgreSQL、Kingbase、DB2、H2 数据库的主键自增。如果是 MySQL 等数据库，可不写。
@Data
@ToString(callSuper = true)
@Builder
@NoArgsConstructor
@AllArgsConstructor
public class PrdDepartmentInfoDO {
    @TableField("DWBM")
    private String dwbm;

    @TableField("SJSX")
    private String sjsx;

    @TableField("LSDWBM")
    private String lsdwbm;

    @TableField("DWMC")
    private String dwmc;
}
