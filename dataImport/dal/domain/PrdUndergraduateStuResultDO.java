package cn.lntd.venues.module.business.util.dataImport.dal.domain;

import com.baomidou.mybatisplus.annotation.KeySequence;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.*;

@TableName("prd_undergraduate_stu_result")
@KeySequence("prd_undergraduate_stu_result_seq") // 用于 Oracle、PostgreSQL、Kingbase、DB2、H2 数据库的主键自增。如果是 MySQL 等数据库，可不写。
@ToString(callSuper = true)
@NoArgsConstructor
public class PrdUndergraduateStuResultDO extends PrdStuResultBaseDO{
    @TableField("BJBM")
    private String bjbm;

    @TableField("BJMC")
    private String bjmc;

    public PrdUndergraduateStuResultDO(String xh, String xm, String yxbm, String zybm, String wlkh, String kxlh, String dwmc, String lsdwbm, String zymc, String bjbm, String bjmc) {
        super(xh, xm, yxbm, zybm, wlkh, kxlh, dwmc, lsdwbm, zymc);
        this.bjbm = bjbm;
        this.bjmc = bjmc;
    }
}
