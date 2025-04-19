package cn.lntd.venues.module.business.util.dataImport.dal.domain;

import com.baomidou.mybatisplus.annotation.TableField;
import lombok.*;

@Data
@ToString(callSuper = true)
@NoArgsConstructor
@AllArgsConstructor
public class PrdStuResultBaseDO {
    @TableField("XH")
    private String xh;

    @TableField("XM")
    private String xm;

    @TableField("YXBM")
    private String yxbm;

    @TableField("ZYBM")
    private String zybm;

    @TableField("WLKH")
    private String wlkh;

    @TableField("KXLH")
    private String kxlh;

    @TableField("DWMC")
    private String dwmc;

    @TableField("LSDWBM")
    private String lsdwbm;

    @TableField("ZYMC")
    private String zymc;
}
