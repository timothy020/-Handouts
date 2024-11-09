using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;



namespace xxtea_experiment
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            textBox1.Text = "0105020000110000000A000007D9B1ED17080916353317081916353303921001921002921003";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int k=0,EnStrLen=0,nIntCount=0,nRemaind=0;
            string NeedEnCryptStr;
            NeedEnCryptStr = textBox1.Text;
            EnStrLen = NeedEnCryptStr.Length;
            nIntCount = EnStrLen/8;
            nRemaind = EnStrLen%8;
            if(nRemaind!=0)
            {
                nIntCount++;
            }
            string[] r = SplitByLen(NeedEnCryptStr, 8);
            UInt32[] V = new UInt32[20];
            UInt32[] Vout = new UInt32[20];
            k=0;
            foreach (string s in r)
            {
                Console.WriteLine("{0}", s);
                V[k++] = (UInt32)Convert.ToInt32(s, 16);
            }
            UInt32[] keyC = { 0x00852953, 0x00543210, 0x00852953,0x00543210 };
            Vout = EncryptCai(V, keyC, nIntCount);

            string result="";
            for(k=0;k<nIntCount;k++)
                result = result + V[k].ToString("X").PadLeft(8, '0'); ;

            string OldText=textBox2.Text;

            textBox2.Text = OldText+result;
            



        }

        public static string[] SplitByLen(string str, int separatorCharNum)
        {
            if (string.IsNullOrEmpty(str) || str.Length <= separatorCharNum)
            {
                return new string[] { str };
            }
            string tempStr = str;
            List<string> strList = new List<string>();
            int iMax = Convert.ToInt32(Math.Ceiling(str.Length / (separatorCharNum * 1.0)));//获取循环次数  
            for (int i = 1; i <= iMax; i++)
            {
                string currMsg = tempStr.Substring(0, tempStr.Length > separatorCharNum ? separatorCharNum : tempStr.Length);
                strList.Add(currMsg);
                if (tempStr.Length > separatorCharNum)
                {
                    tempStr = tempStr.Substring(separatorCharNum, tempStr.Length - separatorCharNum);
                }
            }
            return strList.ToArray();
            //throw new NotImplementedException();
        }
        public static UInt32[] EncryptCai(UInt32[] v, UInt32[] k, Int32 n)
        {

            UInt32 z = v[n - 1], y = v[0], delta = 0x9E3779B9, sum = 0, e;
            Int32 p, q = 6 + 52 / n;
            while (q-- > 0)
            {
                sum = unchecked(sum + delta);
                e = sum >> 2 & 3;
                for (p = 0; p < n - 1; p++)
                {
                    y = v[p + 1];
                    z = unchecked(v[p] += (z >> 5 ^ y << 2) + (y >> 3 ^ z << 4) ^ (sum ^ y) + (k[p & 3 ^ e] ^ z));
                }
                y = v[0];
                z = unchecked(v[n - 1] += (z >> 5 ^ y << 2) + (y >> 3 ^ z << 4) ^ (sum ^ y) + (k[p & 3 ^ e] ^ z));
            }
            return v;
        }

        private void label16_Click(object sender, EventArgs e)
        {

        }

        private void textBox11_TextChanged(object sender, EventArgs e)
        {

        }
        //生成需要加密的字符串
        private void button2_Click(object sender, EventArgs e)
        {
	        //string StrTmp,QRTmp[,StrTmp2[10];
            string[] QRTmp = new string[6];
            string[] StrTmp2 = new string[10];
            string   StrTmp;
	        //1用户数据 nB
            textBox3.Text.Trim();
	        QRTmp[0]=textBox3.Text;

	        //2二维码关联的卡号 4B
            //得到关联卡号十进制字符，先转换成整形，再转为16进制字符串
            int value = Convert.ToInt32(textBox6.Text.Trim());
            QRTmp[1] = String.Format("{0:X8}", value);
            if(QRTmp[1].Length!=8)
            {
                 MessageBox.Show("关联卡号输入有误"+QRTmp[1]);
            }
            //是否启用明码
            int m_bNoEncrypt=0;
            if ((checkBox1.Checked))
                m_bNoEncrypt = 1;
            else
                m_bNoEncrypt = 0;
            	
	        //4.管理字节4字节  8B
	        //时段限制1B
	        if(checkBox2.Checked)
	        {
		        StrTmp2[0] = "01";
	        }else{
		        StrTmp2[0] = "00";
	        }
	        //次数限制1B
	        int nQR_Count=0;            
            nQR_Count = Convert.ToInt32(textBox7.Text.Trim());
	        if((nQR_Count<0)||(nQR_Count>255))
	        {
                MessageBox.Show("次数不对，次数值范围0-255");
		        return;
	        }
            StrTmp2[1] = String.Format("{0:X2}", nQR_Count);



	        //开门方式1B
            int QR_OpenType=2;
            if (radioButton1.Checked == true)
            {
                StrTmp2[2] = "00";
                QR_OpenType=0;
            }
            else  if (radioButton2.Checked == true)
            {
                StrTmp2[2] = "01";
                QR_OpenType=1;
            }
            else  if (radioButton3.Checked == true)
            {
                StrTmp2[2] = "02";
                QR_OpenType=2;
            }
            else  if (radioButton4.Checked == true)
            {
                StrTmp2[2] = "03";
                QR_OpenType=3;
            }
	        //开门时长 2B
	        int nQR_Delay=0;            
            nQR_Count = Convert.ToInt32(textBox8.Text.Trim());
	        if((nQR_Delay<0)||(nQR_Count>65535))
	        {
                MessageBox.Show("开门时长不对(0-65535)");
		        return;
	        }
            StrTmp2[3] = String.Format("{0:X4}", nQR_Count);

	        //保留字节3B
	        StrTmp2[4]="000000";
	        QRTmp[3] =StrTmp2[0]+StrTmp2[1]+StrTmp2[2]+StrTmp2[3]+StrTmp2[4];//8B

	        //5、开始日期和结束日期

            string startdatestr, enddatestr, startdatestr1, enddatestr1;

            DateTime date = DateTime.Parse(dateTimePicker1.Text);
            string years = String.Format("{0:D4}", date.Year);
            string months   = String.Format("{0:D2}", date.Month);
            string days = String.Format("{0:D2}", date.Day);
            string hours = String.Format("{0:D2}", date.Hour);
            string minute = String.Format("{0:D2}", date.Minute);
            string second = String.Format("{0:D2}", date.Second);

            startdatestr1 = years + months + days + hours + minute + second;

            DateTime dateEnd = DateTime.Parse(dateTimePicker1.Text);
            years = String.Format("{0:D4}", dateEnd.Year);
            months   = String.Format("{0:D2}", dateEnd.Month);
            days = String.Format("{0:D2}", dateEnd.Day);
            hours = String.Format("{0:D2}", dateEnd.Hour);
            minute = String.Format("{0:D2}", dateEnd.Minute);
            second = String.Format("{0:D2}", dateEnd.Second);
            enddatestr1 = years + months + days + hours + minute + second;
            startdatestr=startdatestr1.Remove(0,2);
            enddatestr=enddatestr1.Remove(0,2);
	        QRTmp[4] = startdatestr+enddatestr;

	        //6.项目编号和楼栋编号或可开设备的MAC低四位地址
	        if(QR_OpenType==1)//项目编号+房间编号组合
	        {
		        //楼栋数量
	            int nTemp=0;            
                nTemp = Convert.ToInt32(textBox10.Text.Trim());
                StrTmp2[1] = String.Format("{0:X2}", nTemp);
		        //项目编号
                StrTmp = textBox9.Text.Trim();
		        if(StrTmp.Length!=8)
		        {
                    MessageBox.Show("项目编号不对，长度8位(如：41590501)");
			        return;
		        }
		        StrTmp2[1]=StrTmp;

		        //房间组合
                nTemp=0;
		        StrTmp2[2]="";
                if (checkBox3.Checked == true)
                {
                    StrTmp = textBox12.Text.Trim();
		            if(StrTmp.Length!=8)
		            {
                        MessageBox.Show("楼栋房间编号不对，长度8位(如：03010201 3栋1单元2层1室)");
			            return;
		            }
                    StrTmp2[2]+=StrTmp;
                }
                if (checkBox4.Checked == true)
                {
                    StrTmp = textBox12.Text.Trim();
		            if(StrTmp.Length!=8)
		            {
                        MessageBox.Show("楼栋房间编号不对，长度8位(如：03010201 3栋1单元2层1室)");
			            return;
		            }
                    StrTmp2[2]+=StrTmp;
                }
                if (checkBox5.Checked == true)
                {
                    StrTmp = textBox12.Text.Trim();
		            if(StrTmp.Length!=8)
		            {
                        MessageBox.Show("楼栋房间编号不对，长度8位(如：03010201 3栋1单元2层1室)");
			            return;
		            }
                    StrTmp2[2]+=StrTmp;
                }
		        QRTmp[5] = StrTmp2[0]+StrTmp2[1]+StrTmp2[2];
	
	        }
	        else if(QR_OpenType==2)//MAC地址组合
	        {
		        //MAC数量
	            int nTemp=0;            
                nTemp = Convert.ToInt32(textBox11.Text.Trim());
                StrTmp2[0] = String.Format("{0:X2}", nTemp);

		        //MAC组合
		        StrTmp2[1]="";
                if (checkBox6.Checked == true)
                {
                    StrTmp = textBox17.Text.Trim();
		            if(StrTmp.Length!=6)
		            {
                        MessageBox.Show("MAC地址不对，取设备MAC地址后6位(如：MAC:008139921016==>921016)");
			            return;
		            }
                    StrTmp2[1]+=StrTmp;
                }
                if (checkBox7.Checked == true)
                {
                    StrTmp = textBox16.Text.Trim();
		            if(StrTmp.Length!=6)
		            {
                        MessageBox.Show("MAC地址不对，取设备MAC地址后6位(如：MAC:008139921016==>921016)");
			            return;
		            }
                    StrTmp2[1]+=StrTmp;
                }
                if (checkBox8.Checked == true)
                {
                    StrTmp = textBox15.Text.Trim();
		            if(StrTmp.Length!=6)
		            {
                        MessageBox.Show("MAC地址不对，取设备MAC地址后6位(如：MAC:008139921016==>921016)");
			            return;
		            }
                    StrTmp2[1]+=StrTmp;
                }
		        QRTmp[5] = StrTmp2[0]+StrTmp2[1];	
	        }

            //3.加密参数 6B
            //计算加密字符长度
            string encryptionQRStr;//需要加密的字符串
            encryptionQRStr = QRTmp[3] + QRTmp[4] + QRTmp[5];
            if (encryptionQRStr.Length > 500)
            {
                MessageBox.Show("加密字符长度过长");
                return;
            }
            if (m_bNoEncrypt==1)
            {
                StrTmp2[0] = String.Format("{0:X2}", encryptionQRStr.Length);
                StrTmp2[2] = "00000000";
                QRTmp[2] = StrTmp2[0] + StrTmp2[2];
            }
            else
            {
                //加密字符长度,8个字符长度为1个整形长度
                int nLength = encryptionQRStr.Length / 8;
                if ((encryptionQRStr.Length % 8) != 0)
                    nLength++;
                StrTmp2[0] = String.Format("{0:X2}", nLength);
                //余数
                StrTmp2[1] = String.Format("{0:X2}", (encryptionQRStr.Length% 8)/2);

                //二维码加密秘钥
                StrTmp2[2] = textBox4.Text.Trim();

                QRTmp[2] = StrTmp2[0] + StrTmp2[1] + StrTmp2[2];
            }

            string AllQRStr;//所有二维码字符串
            string QRPreStr = QRTmp[0] + "|" + QRTmp[1] + QRTmp[2];

            AllQRStr = QRTmp[0] + "|" + QRTmp[1] + QRTmp[2] + encryptionQRStr;

            textBox18.Text = AllQRStr;
            textBox1.Text  = encryptionQRStr;
            textBox2.Text  = QRPreStr;




        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
        
        }
 
    }
}
