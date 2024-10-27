package cn.lntd.venues.module.business.util.dataImport.dal.domain;

import com.baomidou.mybatisplus.annotation.KeySequence;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.*;

@TableName("prd_undergraduate_major")
@KeySequence("prd_undergraduate_major_seq") // 用于 Oracle、PostgreSQL、Kingbase、DB2、H2 数据库的主键自增。如果是 MySQL 等数据库，可不写。
@Data
@ToString(callSuper = true)
@Builder
@NoArgsConstructor
@AllArgsConstructor
public class PrdUndergraduateMajorDO {
    /**
     * 专业编码
     */
    @TableField("ZYBM")
    private String zybm;

    /**
     * 专业名称
     */
    @TableField("ZYMC")
    private String zymc;

    /**
     * 院系编码
     */
    @TableField("YXBM")
    private String yxbm;
}
