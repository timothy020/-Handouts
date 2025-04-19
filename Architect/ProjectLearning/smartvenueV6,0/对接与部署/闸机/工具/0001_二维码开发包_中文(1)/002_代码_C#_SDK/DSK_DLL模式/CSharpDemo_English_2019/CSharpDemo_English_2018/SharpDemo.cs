
#define ENGLISH 

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Threading;

namespace CSharpDemo
{

    public partial class SharpDemo : Form
    {
        //public NET_CARD;
        private string szLocalIP = "192.168.1.189";

        private string szLocalPort = "18887";


        private string DeviceIP = "192.168.1.15";
        private string DevicePort = "9998";
        private string DeviceMask = "255.255.255.0";
        private string DeviceGate = "192.168.1.1";
        private string DeviceMAC = "008139000015";


        //public byte[] DeviceIP = new byte[4];
        public byte[] ReMACBuffer = new byte[6];
        //public byte[] ReMACBuffer = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; 
        //public byte[] szLocalIP = new byte[4];



        private int nLocalPort = 18887;
        private int nDevicePort = 9998;
        private int WaitTimout = 3000;
        private int nRet = 0;
        private int nReaderNo =0x0F;
        private byte nReaderRight = 0xF0;
        private byte nCardPassword = 0x00;
        private string strTmp1;
        private string strTmp2;
        private uint uCardIDID=0;
        private string StartCardIDStr;
        private string StartCardIDStr2;
        private uint nTypeforDownloadCard=0;        
        
                


        string[] NationArray = new string[]{"汉","蒙古","回","藏","维吾尔","苗","彝","壮","布依","朝鲜","满","侗","瑶","白","土家",
		        "哈尼","哈萨克","傣","黎","傈僳","佤","畲","高山","拉祜","水","东乡","纳西","景颇","柯尔克孜","土",
		        "达斡尔","仫佬","羌","布朗","撒拉","毛南","仡佬","锡伯","阿昌","普米","塔吉克","怒","乌孜别克","俄罗斯","鄂温克",
		        "德昂","保安","裕固","京","塔塔尔","独龙","鄂伦春","赫哲","门巴","珞巴","基诺" };

        #region << Event name EventString[100]>>
#if ENGLISH
        public string[] EventString = new string[]{
     "Normal punching card", "Remote opening", "Dual verification", "Password to open the door", "duress code to open the door",
     "Customize Input to open the door", "Primary Card to open the door", "Manual Button to open the door", "the door is normally closed", "Customize 1 Alarm", 
     "Customize 2 Alarm", "Customize 3 Alarm", "Customize 4 Alarm", "No Permission Time Zone", "Invalid Password", 
     "Invalid Dual Verification", "No permission to open the door", "No Punching the Primary Card", "illegal card", "punching the card by double-card",
     "Door Sensor Alarm", "Duress Alarm", "the correct multi-card combination", "the overdue card", "the false multi-door interlocking condition",
     "all along open door", "remote closing", "urgent opening", "urgent closing", "the door is closed urgently", 
     "all along close door", "recover door status","3 card punching","4 card punching","5 card punching",
     "3 card invalid","4 card invalid","5 card invalid","3 card open","4 card open",
     "5 card open","1 Confirm open","2 Confirm open","3 Confirm open","4 Confirm open",
     "5 Confirm open","repeat punching","card experit","Remote confirm open","",
     "","","","","",
     "","","","","",
     "","","","","",
     "","","","","",
     "","","","","",
     "","","","","",
     "","","","","",
     "","","","","",
     "","","","","",
     "","","","",""
    };
#else
        public string[] EventString = new string[]
     {
	     "刷卡开门",		"远程开门",		"双卡开门",			"密码开门",		"胁迫码开门",
	     "输入开门",		"首卡开门",		"开门按扭开门",		"此门已被常闭",	"非法闯入",
	     "进入刷卡",		"离开刷卡",		"人员已离开",		"人员已进入",	"密码无效",
	     "双卡无效",	    "紧急开门",		"未刷首卡",			"卡片非法",		"双卡刷卡",
	     "门开超时报警",	"胁迫报警",	    "多卡组合正确",		"此卡已过期",	"互锁条件限制",
	     "门常开",			"远程关门",		"门强制打开",		"紧急关门",		"门被紧急关闭",
	     "门常闭",			"恢复门到常态",	"三卡刷卡",			"四卡刷卡",		"五卡刷卡",
	     "三卡无效",		"四卡无效",		"五卡无效",			"三卡开门",		"四卡开门",
	     "五卡开门",		"单卡确认开门",	"双卡确认开门",		"三卡确认开门",	"四卡确认开门",	
	     "五卡确认开门",	"多卡重复刷卡", "此卡已过期",		"远程确认开门",	"保留",
	     "系统正常",		"系统满员",		"系统超员",			"保留",			"保留",
	     "双开恢复正常",	"双闭恢复正常",	"手控盒双开",		"手控盒双闭",	"手控盒开门",
	     "手控盒复位",		"锁舌故障",		"锁故障恢复正常",	"此卡为删除卡",	"旋钮或钥匙开门",
	     "请求对讲",		"验证自动加卡",	"重复进入",			"重复外出",		"保留",
	     "保留","保留","保留","保留","保留",
	     "保留","保留","保留","保留","保留",
	     "保留","保留","保留","保留","保留",
	     "保留","保留","保留","保留","保留"
    };

#endif
        #endregion

        public string[] m_sStrOutputInfo = new string[60];
        public string[] m_sCommandState = new string[15];

        private NET_CARD.NET_CARD_TIME m_struDeviceTime;

        private NET_CARD._PBroadcastSearchCallback m_fSerachData = null;
        private NET_CARD._PProcessCallback   m_fRealtimeData = null;
        private NET_CARD._PProcessCallbackEx m_fRealtimeExData = null;



        public SharpDemo()
        {
            InitializeComponent();



            InitNetSDK();
            //DeviceIP = "192.168.1.15";

            for (int i = 0; i < 6; i++)
            {
                ReMACBuffer[i] = 0x0;
            }
            DoorNoCheckBox1.Checked = true;
            DoorNoCheckBox2.Checked = true;
            DoorNoCheckBox3.Checked = true;
            DoorNoCheckBox4.Checked = true;
            #region << Message:m_sStrOutputInfo and status:m_sCommandState>>

#if ENGLISH

    m_sStrOutputInfo[0]="the successful operation";
	m_sStrOutputInfo[1]="The operation failed!";
	m_sStrOutputInfo[2]="Online";
	m_sStrOutputInfo[3]="Offline";
	m_sStrOutputInfo[4]="Delete?";
	m_sStrOutputInfo[5]="IP address is invalid, please re-enter";
	m_sStrOutputInfo[6]="changed successfully!";
	m_sStrOutputInfo[7]="Modification fails!";
	m_sStrOutputInfo[8]="Delete successfully!";
	m_sStrOutputInfo[9]="Delete fails!";
	m_sStrOutputInfo[10]="No Network Card!";
	m_sStrOutputInfo[11]="DLL initialization network parameters";

	m_sStrOutputInfo[12]="Device Search";
	m_sStrOutputInfo[13]="Setting network parameter";
	m_sStrOutputInfo[14]="online detect";
	m_sStrOutputInfo[15]="Read time";
	m_sStrOutputInfo[16]="Settimg time";
	m_sStrOutputInfo[17]="Read version";
	m_sStrOutputInfo[18]="device init";
	m_sStrOutputInfo[19]="set server IP and port";
	m_sStrOutputInfo[20]="start real moniter";
	m_sStrOutputInfo[21]="stop real moniter";
	m_sStrOutputInfo[22]="remote open door";
	m_sStrOutputInfo[23]="remote close door";
	m_sStrOutputInfo[24]="setting interlock";
	m_sStrOutputInfo[25]="setting lock delay";
	m_sStrOutputInfo[26]="Enable Door Overtime Alarm";
	m_sStrOutputInfo[27]="setting alarm out delay";
	m_sStrOutputInfo[28]="The password should contain 4 digits (from 0 to 9) ";
	m_sStrOutputInfo[29]="Setting Magnetic out  and Threat out delay";
	m_sStrOutputInfo[30]="Setting Threat password";
	m_sStrOutputInfo[31]="login a card";
	m_sStrOutputInfo[32]="Clear all card";
	m_sStrOutputInfo[33]="PWD open Door";
	m_sStrOutputInfo[34]="Get Card Info.";
	m_sStrOutputInfo[35]="Batch download cards";

	m_sStrOutputInfo[36]="Voice Function";

    m_sStrOutputInfo[37]="distant open door";
    m_sStrOutputInfo[38]="recovery door status";
    m_sStrOutputInfo[39]="set lock delay";
    m_sStrOutputInfo[40]="set lock type";
    m_sStrOutputInfo[41]="Alarm out delay";


	m_sCommandState[0]="Successful command";
	m_sCommandState[1]="Illegal command";
	m_sCommandState[2]="Illegal parameters";
	m_sCommandState[3]="Now the sorting of the download card information cannot be allowed. Please try again after cleaning the space";
	m_sCommandState[4]="Unknown command";
	m_sCommandState[5]="Unauthorized!";
	m_sCommandState[6]="Equipment trouble";
	m_sCommandState[7]="The failed command operation";
	m_sCommandState[8]="The unsuccessful acceptance of the command";
	m_sCommandState[9]="The insufficient storage space for the controller";
	m_sCommandState[10]="No record in the controller";
	m_sCommandState[11]="The card information or starting operation doesn't exist in the controller ";
	m_sCommandState[12]="All the records in the controller have been read";

#else
            m_sStrOutputInfo[0] = "操作成功!";
            m_sStrOutputInfo[1] = "操作失败!";
            m_sStrOutputInfo[2] = "在线";
            m_sStrOutputInfo[3] = "离线";
            m_sStrOutputInfo[4] = "确定删除吗?";
            m_sStrOutputInfo[5] = "IP地址无效,请重新输入";
            m_sStrOutputInfo[6] = "修改成功!";
            m_sStrOutputInfo[7] = "修改失败!";
            m_sStrOutputInfo[8] = "删除成功!";
            m_sStrOutputInfo[9] = "删除失败!";
            m_sStrOutputInfo[10] = "系统无网卡!";
            m_sStrOutputInfo[11] = "初始化DLL网络参数";

            m_sStrOutputInfo[12] = "设备搜索";
            m_sStrOutputInfo[13] = "设备网络参数";
            m_sStrOutputInfo[14] = "设备在线检测";
            m_sStrOutputInfo[15] = "读取时间";
            m_sStrOutputInfo[16] = "设置时间";
            m_sStrOutputInfo[17] = "读取版本";
            m_sStrOutputInfo[18] = "设备初始化";
            m_sStrOutputInfo[19] = "设置上传服务器与端口号";
            m_sStrOutputInfo[20] = "开启实时监控";
            m_sStrOutputInfo[21] = "停止实时监控";
            m_sStrOutputInfo[22] = "远程开门";
            m_sStrOutputInfo[23] = "远程关门";
            m_sStrOutputInfo[24] = "设置互锁";
            m_sStrOutputInfo[25] = "设置锁延时";
            m_sStrOutputInfo[26] = "启动门开超时报警";
            m_sStrOutputInfo[27] = "设置报警输入延时";
            m_sStrOutputInfo[28] = " 密码为4位数字(0-9) ";
            m_sStrOutputInfo[29] = "设置门磁与胁迫输出延时";
            m_sStrOutputInfo[30] = "设置胁迫开门密码";

            m_sStrOutputInfo[31] = "下载单张卡";
            m_sStrOutputInfo[32] = "清除所有卡";

            m_sStrOutputInfo[33] = "设置密码直接开门";

            m_sStrOutputInfo[34] = "获取单张卡信息";

            m_sStrOutputInfo[35] = "批量下载卡";

            m_sStrOutputInfo[36] = "语音指令";

            m_sStrOutputInfo[37] = "门常开";
            m_sStrOutputInfo[38] = "恢复门状态";
            m_sStrOutputInfo[39] = "设置锁延时";
            m_sStrOutputInfo[40] = "设置锁类型";
            m_sStrOutputInfo[41] = "设置报警输出延时";




            m_sCommandState[0] = "命令成功";
            m_sCommandState[1] = "命令无效";
            m_sCommandState[2] = "参数无效";
            m_sCommandState[3] = "现在不能排序下载卡信息，请清空后重试";
            m_sCommandState[4] = "未知命令";
            m_sCommandState[5] = "没有权限";
            m_sCommandState[6] = "设备损坏";
            m_sCommandState[7] = "命令操作失败";
            m_sCommandState[8] = "命令接受不成功";
            m_sCommandState[9] = "控制器存储空间不足";
            m_sCommandState[10] = "控制器内无记录";
            m_sCommandState[11] = "控制器内无该卡信息或没有启动相关操作";
            m_sCommandState[12] = "控制器内记录已读完";

#endif
            #endregion


        }

        public delegate void ProcessDelegate(string a);

        public void DisplayInfoforRecieve(string a)
        {
            if (m_wndList1.Lines.GetUpperBound(0) + 1 > 500)
            {
                m_wndList1.Text = "";
            }
            string str1 = m_wndList1.Text + a;
            m_wndList1.Text = str1;

            this.m_wndList1.Select(this.m_wndList1.TextLength, 0);//光标定位到文本最后
            this.m_wndList1.ScrollToCaret();//滚动到光标处
            return;        
        }
        public void mem_copy(byte[] dst, int dst_offst, byte[] src, int src_offst, int len)
        {
            for (int i = 0; i < len; i++)
            {
                dst[dst_offst++] = src[src_offst++];
            }

        }
        public int SendCommandtoDevice(string SendCommandStr)
        {
	        int i=0;
	        int nLength=0;
	        string strSend,tempStr,tempDataStr;
	        string strText,strTextLength;
            strSend = "";
	        SendCommandStr.Trim();	        
	        nLength = SendCommandStr.Length;
	        for(i=0;i<nLength;i++)
	        {
		        tempStr=SendCommandStr.Substring(i,1);
		        if(tempStr!=" ")
		        {
			        strSend +=tempStr;
		        }
	        }
            strTextLength= (String.Format("{0:X}", strSend.Length/2+8)).PadLeft(4,'0');
            strText="02"+strTextLength+"FFFFFFFFFFFF11"+strSend+"FF03";

	        string strtt="";
	        string strTextCai="";
	        int nLen = strText.Length;
	        for(int kk=0;kk<nLen/2;kk++)
	        {
		        strtt=strText.Substring(2*kk,2);
		        if(kk==(nLen/2-1))
			        strTextCai =strTextCai+strtt;
		        else
			        strTextCai =strTextCai+strtt+" ";
	        }
	        //m_cCommAll.SetWindowText(strTextCai);


	        int   m_iOK;
            byte[] byData    = new byte[1500];
            byte[] RevData    = new byte[1500];
	        for(int kk=0;kk<nLen/2;kk++)
	        {
		        strtt=strText.Substring(2*kk,2);
                byData[kk] = Convert.ToByte(strtt, 16);
	        }           
	        nRet = NET_CARD.NET_CARD_SendCommandToDevice(NET_CARD.DEVICE_NET_ACCESS,DeviceIP,nDevicePort,ref byData[0],nLen/2,ref RevData[0],ref nLength);           
	        if(nRet==1)
	        {
		        tempDataStr="";
                tempStr = string.Empty;
                for (i = 0; i < nLength; i++)//逐字节变为16进制字符
                {
                    tempStr += (Convert.ToString(RevData[i], 16)).PadLeft(2,'0');
                }
		        //string strText,strTextCai;
		        nLen = tempStr.Length;
                strText = tempStr;
		        for(int kk=0;kk<nLen/2;kk++)
		        {
                    strtt = strText.Substring(2 * kk, 2);
			        if(kk==(nLen/2-1))
                        strTextCai = strTextCai + strtt;
			        else
                        strTextCai = strTextCai + strtt + " ";
		        }


                tempDataStr = tempStr.Substring(24, 2);
                m_iOK = Convert.ToByte(tempDataStr, 16);
		        if((m_iOK>=0)&&(m_iOK<=12))
		        {
                    tempDataStr = m_sCommandState[m_iOK];
		        }
		        else if(tempDataStr=="FF")
		        {
			        tempDataStr ="Command error or unsupport";
		        }
                ProcessDelegate showProcess = new ProcessDelegate(DisplayInfoforRecieve);
                m_wndList1.Invoke(showProcess, "\r\ncommand state:" + tempDataStr + "\r\n");


		        if(tempStr.Length>=30)
			        tempDataStr = tempStr.Substring(26,tempStr.Length-26-4);

                 m_wndList1.Invoke(showProcess, "Command Return:" + tempStr + "\r\n");
                 m_wndList1.Invoke(showProcess, "Command Data:" + tempDataStr + "\r\n");



		        strTextCai="";
		        nLen = tempDataStr.Length;
		        strText = tempDataStr;
		        for(int kk=0;kk<nLen/2;kk++)
		        {
			        strtt=strText.Substring(2*kk,2);
			        if(kk==(nLen/2-1))
				        strTextCai =strTextCai+strtt;
			        else
				        strTextCai =strTextCai+strtt+" ";
		        }
                m_wndList1.Invoke(showProcess, "Command Data(Add space):" + strTextCai + "\r\n");


		        return   m_iOK;

	        }
	        else
	        {
                ProcessDelegate showProcess = new ProcessDelegate(DisplayInfoforRecieve);
                m_wndList1.Invoke(showProcess, "Error" + nRet.ToString());
		        return -1;
	        }

        }

        public int GetRealtimeDataProcess(ref NET_CARD.NET_CARD_RECORDINFO pRecordInfo, IntPtr pReturnIP ,ref int nIPLength, IntPtr pReturnMAC)
        {
            int nRecord_EventNum =0;
            int nRecord_DoorNum =0;
            string sRecord_CardID, sDateTimeStr, sIPstr, sMACstr, m_sInOrOut;
            string[] Record_Time  = new string[6];
            byte[] ReturnMAC    = new byte[6];
            string[] m_sMAC = new string[6];
            UInt32   nCardID = 0;


            //Get device IP
            sIPstr = Marshal.PtrToStringAnsi(pReturnIP);
            //Get device MAC
            Marshal.Copy(pReturnMAC, ReturnMAC, 0, 6);

            sMACstr = "";
            for (int kk = 0; kk < 6; kk++)
            {
                m_sMAC[kk] = ReturnMAC[kk].ToString("X2");
                sMACstr += m_sMAC[kk];
            }
            //sMACstr =System.Text.Encoding.Default.GetString(ReturnMAC);
            //Get Event's cardID 
            nCardID = pRecordInfo.Record_CardID[2];
            nCardID = nCardID <<8;
            nCardID = nCardID | pRecordInfo.Record_CardID[3];

            sRecord_CardID = pRecordInfo.Record_CardID[0].ToString("D3");
            sRecord_CardID += pRecordInfo.Record_CardID[1].ToString("D3");
            sRecord_CardID += nCardID.ToString("D5");
            //Get Event's Time
            for(int kk=0;kk<6;kk++)
            {
                Record_Time[kk] = pRecordInfo.Record_Time[kk].ToString("X2");
            }
            Record_Time[0] ="20"+Record_Time[0];
            sDateTimeStr =Record_Time[0]+"-"+ Record_Time[1]+"-"+Record_Time[2]+" "+Record_Time[3]+":"+Record_Time[4]+":"+Record_Time[5];
            //Get Event's number
            nRecord_EventNum = pRecordInfo.Record_EventNum;
            //Get Event's reader No.
            nRecord_DoorNum  = pRecordInfo.Record_DoorNum & 0x07;

            m_sInOrOut = "IN";
            if (nRecord_DoorNum >= 4)
            {
                m_sInOrOut = "OUT";
                nRecord_DoorNum = nRecord_DoorNum - 4;
            }


            if (sRecord_CardID == "25525565535")
            {
                string AllDoorStatus, SwitchNametmp;
                int nDoorStatue = pRecordInfo.Record_DoorNum & 0x0f;
                AllDoorStatus = SwitchNametmp = "";
                for (int ii = 0; ii < 4; ii++)
                {
                    int m_iDoor;
                    m_iDoor = (nDoorStatue & (1 << ii));
                    if (m_iDoor>0)
                    {
                        SwitchNametmp = string.Format("{0:D} open ", ii+1 );
                    }
                    else
                    {
                        SwitchNametmp = string.Format("{0:D} close ", ii + 1);
                    }
                    AllDoorStatus += SwitchNametmp;
                }
                sDateTimeStr += "\r\n";
                sDateTimeStr += "Door sensor:"+AllDoorStatus +"\r\n"; ;
                ProcessDelegate showProcess = new ProcessDelegate(DisplayInfoforRecieve);
                m_wndList1.Invoke(showProcess, sDateTimeStr);
            }
            else
            {

                string strTmp1, tmpStr;
                strTmp1 = tmpStr = "";
                strTmp1 += "Gather Time:" + sDateTimeStr + "\r\n";
                strTmp1 += "Card Series:" + sRecord_CardID + "\r\n";
                tmpStr = sIPstr;
                strTmp1 += "IP:" + tmpStr + "\r\n";
                strTmp1 += "Reader No.:" + nRecord_DoorNum.ToString() + "\r\n";
                strTmp1 += "Event ID:" + nRecord_EventNum.ToString() + "\r\n";
                strTmp1 += "Event Name:" + EventString[nRecord_EventNum] + "\r\n";
                strTmp1 += "Event Time:" + sDateTimeStr + "\r\n";
                strTmp1 += "Device MAC:" + sMACstr + "\r\n";
                strTmp1 += "IN  or OUT:" + m_sInOrOut + "\r\n";
                strTmp1 += "\r\n";


                ProcessDelegate showProcess = new ProcessDelegate(DisplayInfoforRecieve);
                m_wndList1.Invoke(showProcess, strTmp1);
            }
           
            return 0;
        }
        private static string byteToHexStr(byte[] bytes, int length)
        {
            string returnStr = "";
            if (bytes != null)
            {
                for (int i = 0; i < length; i++)
                {
                    returnStr += bytes[i].ToString("X2");
                }
            }
            return returnStr;
        }
        // QR code and  2rd ID reader 
        public int GetRealtimeDataProcessEx(IntPtr pData, ref int DataLength, int nType, IntPtr  pReturnIP, ref int ReturnIPLen, IntPtr pReturnMAC, IntPtr pIDBuffer, ref int ReturnIDBufferLen, int IDReaderNo)
        {                       
            string   sIPstr, sMACstr,QRString;//m_sInOrOut
            string[] Record_Time  = new string[6];
            byte[] ReturnMAC    = new byte[6];
            string[] m_sMAC = new string[6];

            byte[] RecvData    = new byte[1500];
            byte[] QRData = new byte[200];

            int  nReturnIDBufLen =0;
            int  nRetDataLen = 0;
            
            nRetDataLen = DataLength;

            //Get device IP
            sIPstr = Marshal.PtrToStringAnsi(pReturnIP);
            //Get device MAC
            Marshal.Copy(pReturnMAC, ReturnMAC, 0, 6);
            sMACstr = "";
            for (int kk = 0; kk < 6; kk++)
            {
                m_sMAC[kk] = ReturnMAC[kk].ToString("X2");
                sMACstr += m_sMAC[kk];
            }
	        if(nType==2)//QR Data  二维码或条码数据
	        {
		        if(nRetDataLen<1200)
		        {                    
                    int nDataLength=nRetDataLen-14-2;
                    byte[] QRDataTmp = new byte[nDataLength];
                    Marshal.Copy(pData, RecvData, 0, nRetDataLen);
                    mem_copy(QRDataTmp, 0, RecvData, 14, nDataLength);
                    QRString = System.Text.Encoding.Default.GetString(QRDataTmp);
                    QRString = "QR Data:"+QRString+"\r\n";
                    ProcessDelegate showProcess = new ProcessDelegate(DisplayInfoforRecieve);
                    m_wndList1.Invoke(showProcess, QRString);
		        }
	        }
	        else if(nType==3)//其它设备发送过来的数据
	        {
                byte[] DataTmpIP = new byte[ReturnIPLen];
                byte[] DataTmp = new byte[nRetDataLen];
                byte[] data = new byte[200];
                Marshal.Copy(pData, DataTmp, 0, nRetDataLen);


                if ((DataTmp[10] == 0x45) && (DataTmp[11] == 0x11))//历史记录信息
                {
                    string tmpStr, tmpStrIP,tmpStr2, strTmp1;

                    Marshal.Copy(pReturnIP, DataTmpIP, 0,ReturnIPLen);

                    tmpStrIP = tmpStr = System.Text.Encoding.Default.GetString(DataTmpIP);

                    strTmp1 = "Device IP:" + tmpStr + "\r\n";
                    ProcessDelegate showProcess = new ProcessDelegate(DisplayInfoforRecieve);
                    m_wndList1.Invoke(showProcess, strTmp1);

                    tmpStr = "NO.   Reader    CardSeries        Time          EventID    EventName\r\n";

                    m_wndList1.Invoke(showProcess, tmpStr);

                    int nEventCunt = DataTmp[13];
                    string strCardRecord;
                    string strDateRecord;
                    string m_sEventStr;

                    int m_iEvent = 0;
                    strTmp1 = "";
                    for (int i = 0; i < nEventCunt; i++)
                    {
                        Buffer.BlockCopy(DataTmp, 14 + i * 17, data, 0, 17);
                        strCardRecord = data[0].ToString("X2") + data[1].ToString("X2") + data[2].ToString("X2") + data[3].ToString("X2");
                        strDateRecord = "20" + data[4].ToString("X2") + data[5].ToString("X2") + data[6].ToString("X2") + data[7].ToString("X2") + data[8].ToString("X2") + data[9].ToString("X2");

                        m_iEvent = data[10];
                        if (m_iEvent < 100)
                            m_sEventStr = EventString[m_iEvent];
                        else
                            m_sEventStr = "Unknow Event";
                        int nReader = data[16] & 0x07;

                        tmpStr = (i + 1).ToString("D2") + "\t" + nReader.ToString("D2");
                        tmpStr2 = m_iEvent.ToString();
                        strTmp1 += tmpStr + "\t" + strCardRecord + "\t" + strDateRecord + "\t" + tmpStr2 + "\t"+m_sEventStr + "\r\n";
                    }
                    m_wndList1.Invoke(showProcess, strTmp1);

                    int nRet = 0;
                    nRet = NET_CARD.NET_CARD_EventConfirm(NET_CARD.DEVICE_NET_ACCESS, tmpStrIP, nDevicePort, ref ReMACBuffer[0]);
                    if (nRet == 0)
                    {
                        m_wndList1.Invoke(showProcess, "Confirming the histroy record is " + m_sStrOutputInfo[0] + "\r\n");
                    }
                    else
                    {
                        string m_sReturnError;
                        m_sReturnError= nRet.ToString();
                        m_wndList1.Invoke(showProcess, m_sStrOutputInfo[42] + m_sStrOutputInfo[0] + m_sReturnError+"\r\n");
                    }

                }			
		    }
	        else if(nType==4)//4508心跳信息  heart infomation
	        {
                byte[] DataTmpIP = new byte[ReturnIPLen];
                byte[] DataTmp = new byte[nRetDataLen];
                byte[] data = new byte[200];
                Marshal.Copy(pData, DataTmp, 0, nRetDataLen);
		        //02003D00813922602011451800
		        //C0A8010F008139226020C0A80101FFFFFF00270E31313032444C3830304D325356352E362E30351804251922540202000001B003
                if ((DataTmp[10] == 0x45) && (DataTmp[11] == 0x18))//heart infomation
                {
                    //string tmpStr, tmpStr2, strTmp1;
                    //int nDevicePort;
                    //string strTmp2;
                    //string m_sIP, m_sMAC, m_sGate, m_sMask, m_sPort, m_sVersion, m_sDoorNum;

                }
			
		     }
            else if(nType==1)//2rd ID data //二代身份证数据
	        {
		        if(ReturnIDBufferLen!=0)
			        nReturnIDBufLen = ReturnIDBufferLen;
		        else
			        nReturnIDBufLen =0;

		        if(ReturnIDBufferLen==38862)//图片已正确解码
		        {
                    string picfileNamestr;
                    picfileNamestr = Application.StartupPath + "\\EmployeePic.BMP";

                    byte[] photo = new byte[ReturnIDBufferLen];
                    Marshal.Copy(pIDBuffer, photo, 0, ReturnIDBufferLen);

                    FileStream fs = new FileStream(picfileNamestr, FileMode.Create, FileAccess.Write);
                    fs.Write(photo, 0, photo.Length);
                    fs.Flush();
                    fs.Close();

                    //pictureBox1.Image = Image.FromFile(picfileNamestr);
                    //Bitmap bmp = new System.Drawing.Bitmap(pictureBox1.Image);
                    //pictureBox1.Image.Dispose();

		        }
		        //显示身份证的信息
                NET_CARD.NET_CARD_IDCARDINFO IDCardInfo;
                IDCardInfo = (NET_CARD.NET_CARD_IDCARDINFO)Marshal.PtrToStructure(pData, typeof(NET_CARD.NET_CARD_IDCARDINFO));
                string strTmp1, strTmpStr;
                strTmp1 = strTmpStr = "";
               
                strTmpStr = System.Text.Encoding.Default.GetString(IDCardInfo.IDCard_Name);
                strTmpStr = strTmpStr.Trim("\0".ToCharArray());
                strTmp1 += "\r\n姓名:" + strTmpStr + "\r\n";

                if (IDCardInfo.IDCard_Sex != 0x31)
                    strTmpStr = "女";
                else
                    strTmpStr = "男";
                strTmp1 += "性别:" + strTmpStr + "\r\n";

                int nNation;
                nNation = IDCardInfo.IDCard_National - 0x30;//atoi(IDCardInfo.IDCard_National);
                if ((nNation >= 0) && (nNation <= 55))
                {
                    strTmp1 += "民族:" + NationArray[nNation] + "\r\n";
                }
                else
                {
                    strTmp1 += "民族:汉\r\n";
                }

                strTmpStr = System.Text.Encoding.Default.GetString(IDCardInfo.IDCard_Birthday);
                strTmpStr = strTmpStr.Trim("\0".ToCharArray());
                strTmp1 += "出生年月:" + strTmpStr + "\r\n";

                strTmpStr = System.Text.Encoding.Default.GetString(IDCardInfo.IDCard_Address);
                strTmpStr = strTmpStr.Trim("\0".ToCharArray());
                strTmp1 += "住址:" + strTmpStr + "\r\n";

                strTmpStr = System.Text.Encoding.Default.GetString(IDCardInfo.IDCard_IDNumber);
                strTmpStr = strTmpStr.Trim("\0".ToCharArray());
                strTmp1 += "身份证号码:" + strTmpStr + "\r\n";

                strTmpStr = System.Text.Encoding.Default.GetString(IDCardInfo.IDCard_Issuing);
                strTmpStr = strTmpStr.Trim("\0".ToCharArray());
                strTmp1 += "签发机关:" + strTmpStr + "\r\n";


                strTmpStr = System.Text.Encoding.Default.GetString(IDCardInfo.IDCard_Validity_StartDate);
                strTmpStr = strTmpStr.Trim("\0".ToCharArray());

                strTmp1 += "开始有效期:" + strTmpStr + "\r\n";

                strTmpStr = System.Text.Encoding.Default.GetString(IDCardInfo.IDCard_Validity_EndDate);
                strTmpStr = strTmpStr.Trim("\0".ToCharArray());
                strTmp1 += "截止有效期:" + strTmpStr + "\r\n";


                strTmpStr = IDReaderNo.ToString();
                strTmp1 += "读头号:"+strTmpStr + "\r\n";

                ProcessDelegate showProcess = new ProcessDelegate(DisplayInfoforRecieve);
                m_wndList1.Invoke(showProcess, strTmp1);

	        }

	        else 
	        {
		        //显示条码信息或其它信息
		        if(nRetDataLen<1200)
		        {
                    byte[] QRDataTmp = new byte[nRetDataLen];
                    Marshal.Copy(pData, QRDataTmp, 0, nRetDataLen);                    

                    QRString = byteToHexStr(QRDataTmp, nRetDataLen);

                    QRString = "Return Data:" + QRString + "\r\n";

                    ProcessDelegate showProcess = new ProcessDelegate(DisplayInfoforRecieve);
                    m_wndList1.Invoke(showProcess, QRString);

                    if((QRDataTmp[10]==0x55)&&(QRDataTmp[11]==0x25))//刷卡实时上传
                    {
                        string strCardRecord16;
                        string strCardRecord10;
                        string m_sEventStr;
                        int m_iEvent = QRDataTmp[12];//事件号
                        if (m_iEvent < 100)
                            m_sEventStr = EventString[m_iEvent];//事件名称
                        else
                            m_sEventStr = "Unknow Event";
                        int nReaderNo = QRDataTmp[13];//读头号1或2，//进出定义：一般软件定义1为进，2为出，人为定义
                        //卡号，用16进制表示
                        strCardRecord16 = QRDataTmp[14].ToString("X2") + QRDataTmp[15].ToString("X2") + QRDataTmp[16].ToString("X2") + QRDataTmp[17].ToString("X2");
                        UInt32 nCardRecord10 = 0;
                        nCardRecord10 = QRDataTmp[14];
                        nCardRecord10 <<=8;
                        nCardRecord10 = nCardRecord10 | QRDataTmp[15];
                        nCardRecord10 <<= 8;
                        nCardRecord10 = nCardRecord10 | QRDataTmp[16];
                        nCardRecord10 <<= 8;
                        nCardRecord10 = nCardRecord10 | QRDataTmp[17];

                        strCardRecord10 = nCardRecord10.ToString("D10");

                        strTmp1 = "\r\n刷卡实时记录：读头号:" + nReaderNo.ToString();
                        strTmp1 += " 十六进制卡号:" + strCardRecord16 ;
                        strTmp1 += " 十进制10位卡号:" + strCardRecord10;
                        strTmp1 += " 刷卡事件号:" + m_iEvent.ToString();
                        strTmp1 += " 刷卡事件:" + m_sEventStr + "\r\n\r\n";

                        m_wndList1.Invoke(showProcess, strTmp1);
  
                    }
			        
		        }

	        }

	        return 0;

        }
        public int GetBroadcastSerachProcess(ref NET_CARD.NET_CARD_DEVICENETPARA pNetParameter, IntPtr pReturnIP ,ref int nIPLength, IntPtr pReturnMAC)
        {
            //int 
            string sTmp,sIPstr, sMACstr, sGatestr, sMaskstr, sPortstr, sVersionstr, sDoorNumstr;
            sIPstr = sMACstr = sGatestr = sMaskstr = sPortstr = sVersionstr = sDoorNumstr = "";
            string[] m_sIP   = new string[4];
            string[] m_sMAC  = new string[6];
            string[] m_sGate = new string[4];
            string[] m_sMask = new string[4];
            string[] m_sPort = new string[2];
            string[] m_sVersion = new string[16];

            for(int kk=0;kk<4;kk++)
            {
                m_sIP[kk] = pNetParameter.m_sNetIP[kk].ToString("D0");
            }
            sTmp = "IP Address:";
            sIPstr = m_sIP[0] + "." + m_sIP[1] + "." + m_sIP[2] + "." + m_sIP[3];
            sIPstr = sTmp+sIPstr+"\r\n";

            sTmp = "MAC:";
            for(int kk=0;kk<6;kk++)
            {
                m_sMAC[kk] = pNetParameter.m_sNetMAC[kk].ToString("X2");
                sMACstr +=m_sMAC[kk];
            }
            sMACstr =sTmp + sMACstr+ "\r\n";

            sTmp = "Gate:";
            for(int kk=0;kk<4;kk++)
            {
                m_sGate[kk] = pNetParameter.m_sNetGate[kk].ToString("D0");
            }
            sGatestr = m_sGate[0] + "." + m_sGate[1] + "." + m_sGate[2] + "." + m_sGate[3];
            sGatestr =sTmp + sGatestr + "\r\n";

            sTmp = "Mask:";
            for(int kk=0;kk<4;kk++)
            {
                m_sMask[kk] = pNetParameter.m_sNetMask[kk].ToString("D0");
            }
            sMaskstr = m_sMask[0] + "." + m_sMask[1] + "." + m_sMask[2] + "." + m_sMask[3];
            sMaskstr =sTmp+ sMaskstr+ "\r\n";

            sTmp = "Version:";
            sVersionstr = System.Text.Encoding.Default.GetString(pNetParameter.m_sVersion);
            sVersionstr = sVersionstr.Replace("\0", "");
            sVersionstr =sTmp+sVersionstr+"\r\n";

            sTmp = "DoorNum:";
            sDoorNumstr = (pNetParameter.m_nDoorNum & 0x07).ToString("X");

            sDoorNumstr =sTmp+sDoorNumstr+ "\r\n";

            int Port = 0;
            Port = pNetParameter.m_nNetPort[0];
            Port = Port << 8;
            Port = Port | pNetParameter.m_nNetPort[1];

            sTmp = "Port:";
            sPortstr = Port.ToString("D2");
            sPortstr =sTmp + sPortstr+" \r\n";

            
            ProcessDelegate showProcess = new ProcessDelegate(DisplayInfoforRecieve);
            m_wndList1.Invoke(showProcess, sIPstr + sMACstr + sGatestr + sMaskstr + sPortstr + sVersionstr + sDoorNumstr);

           // DisplayInfoforRecieve(sIPstr + sMACstr + sGatestr + sMaskstr + sPortstr + sVersionstr + sDoorNumstr );
            return 0;
        }


  
        private void InitNetSDK()
        {
            string ErrorStr;
            int ret;
            // szLocalIP = "192.168.1.158";
            nLocalPort = 18887;

            szLocalIP = Cfg.GetConfig("LocalIP", "192.168.1.189");
            szLocalPort = Cfg.GetConfig("LocalPort", "18887");
            nLocalPort = int.Parse(szLocalPort);


            List<string> color;
            color = GetHostIPAddress();
            System.String[] IPstr = { };  //color.Count
            IPstr = color.ToArray();

            int nLocalDex = 0;
            for (int kk = 0; kk < IPstr.Count(); kk++)
            {
                comBoxLocalIP.Items.Add(IPstr[kk]);
                if (szLocalIP == IPstr[kk])
                {
                    nLocalDex = kk;
                }
            }
            comBoxLocalIP.SelectedIndex = nLocalDex;
            szLocalIP = comBoxLocalIP.SelectedItem.ToString();
            InterLockComBox.SelectedIndex = 0;


            szLocalIP="0.0.0.0";
            WaitTimout = 3000;
            ret = NET_CARD.NET_CARD_InitEx(szLocalIP, nLocalPort, WaitTimout);
            if (ret != 0)
            {
                ErrorStr = "NET_CARD_InitEx error!";
                MessageBox.Show(ErrorStr);
                //return;
            }
            //Get local IP list;

            DeviceIP = Cfg.GetConfig("DeviceIP", "192.168.1.15");
            DevicePort = Cfg.GetConfig("DevicePort", "9998");
            DeviceMask = Cfg.GetConfig("DeviceMask", "255.255.255.0");
            DeviceGate = Cfg.GetConfig("DeviceGate", "192.168.1.1");
            DeviceMAC = Cfg.GetConfig("DeviceMAC", "00813900015");


            nDevicePort = int.Parse(DevicePort);
            textBox1.Text = DeviceIP;
            textBox2.Text = DevicePort;
            textBox3.Text = DeviceMask;
            textBox4.Text = DeviceGate;
            textBox5.Text = DeviceMAC;

            //设置设备搜索回调函数
            //Set a callback function for Broadcast  Search all devices
            m_fSerachData = new NET_CARD._PBroadcastSearchCallback(GetBroadcastSerachProcess);
            NET_CARD.NET_CARD_BroadcastSerachDevice(m_fSerachData);
             //设置记录获取回调函数
             //Set a callback function for  Get records
             m_fRealtimeData = new NET_CARD._PProcessCallback(GetRealtimeDataProcess);
             NET_CARD.NET_CARD_RealTimeDataCallback(m_fRealtimeData);
             
             //设置二维码或身份证信息回调函数
             //set QRcode or ID card information callback function
             m_fRealtimeExData = new NET_CARD._PProcessCallbackEx(GetRealtimeDataProcessEx);
             NET_CARD.NET_CARD_RealTimeDataCallbackEx(m_fRealtimeExData);

           
        }
        private List<string> GetHostIPAddress()
        {
            List<string> lstIPAddress = new List<string>();
            IPHostEntry IpEntry = Dns.GetHostEntry(Dns.GetHostName());
            foreach (IPAddress ipa in IpEntry.AddressList)
            {
                if (ipa.AddressFamily == AddressFamily.InterNetwork)
                    lstIPAddress.Add(ipa.ToString());
            }
            return lstIPAddress; // result: 192.168.1.17 ......
        }

        private void AddStringtoList(string OperatStatus, string EventExplain, string ErrorInfo)
        {
            int nItemCount = 0;
            this.m_wndOutputList.BeginUpdate();
            nItemCount = m_wndOutputList.Items.Count + 1;
            ListViewItem list = new ListViewItem();
            list.Text = nItemCount.ToString();//序号
            list.SubItems.Add(DateTime.Now.ToString());//时间
            list.SubItems.Add(OperatStatus);
            list.SubItems.Add(EventExplain);
            list.SubItems.Add(ErrorInfo);
            m_wndOutputList.Items.Add(list);
            this.m_wndOutputList.EndUpdate();
            this.m_wndOutputList.EnsureVisible(nItemCount - 1);

            return;
        }

        //onlineDetect
        private void btnOnlineDetect_Click(object sender, EventArgs e)
        {
            string ErrorStr;
            Int32 nSize = Marshal.SizeOf(m_struDeviceTime);
            IntPtr ptrDeviceTime = Marshal.AllocHGlobal(nSize);
            Marshal.StructureToPtr(m_struDeviceTime, ptrDeviceTime, false);

            nRet = NET_CARD.NET_CARD_DetectDeviceOnline(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, ref ReMACBuffer[0], ptrDeviceTime);

            if (nRet == 0)
            {
                ErrorStr = "Successful";
                // MessageBox.Show(ErrorStr);
                AddStringtoList(m_sStrOutputInfo[0], m_sStrOutputInfo[14], ErrorStr);
            }
            else
            {
                //写入输出LIST
                ErrorStr = nRet.ToString();
                MessageBox.Show(ErrorStr);
                AddStringtoList(m_sStrOutputInfo[1], m_sStrOutputInfo[14], ErrorStr);
            }

        }

        private void btnReadVersion_Click(object sender, EventArgs e)
        {
            string ErrorStr;
            byte[] DevVersion = new byte[16];

            nRet = NET_CARD.NET_CARD_ReadDeviceVersion(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, ref ReMACBuffer[0], ref DevVersion[0]);
            if (nRet == 0)
            {
                string DevVersionStr = System.Text.Encoding.Default.GetString(DevVersion);
                AddStringtoList(m_sStrOutputInfo[0], m_sStrOutputInfo[17], DevVersionStr);
            }
            else
            {
                ErrorStr = nRet.ToString();
                MessageBox.Show(ErrorStr);
            }

        }

        private void btnDeviceSearch_Click(object sender, EventArgs e)
        {
            int nRemotePort = 0;
            CSharpEditforIP fEditforIP = new CSharpEditforIP();
            fEditforIP.ShowDialog();
            try
            {
                if (fEditforIP.blnOKEnter == true)
                {
                    nRemotePort = int.Parse(fEditforIP.editPortstr);// int.TryParse(fEditforIP.editPortstr, out nRemotePort);

                    nRet = NET_CARD.NET_CARD_BroadCastSearchDevice(NET_CARD.DEVICE_NET_ACCESS, fEditforIP.editIPstr, nRemotePort);
                    if (nRet > 0)
                    {
                        //CString OperatTimeStr,EventExplainStr,m_sReturnError;
                        string strtmp = m_sStrOutputInfo[12] + m_sStrOutputInfo[0];
                        AddStringtoList(m_sStrOutputInfo[0], strtmp, m_sStrOutputInfo[0]);
                    }
                    else
                    {
                        AddStringtoList(m_sStrOutputInfo[1], m_sStrOutputInfo[12] + m_sStrOutputInfo[1], nRet.ToString());
                    }
                }
            }
            catch
            {

            }
        }
        private void btnReadTime_Click(object sender, EventArgs e)
        {
            string ErrorStr, DeviceTimeStr;
            Int32 nSize = Marshal.SizeOf(m_struDeviceTime);
            IntPtr ptrDeviceTime = Marshal.AllocHGlobal(nSize);
            Marshal.StructureToPtr(m_struDeviceTime, ptrDeviceTime, false);

            nRet = NET_CARD.NET_CARD_DetectDeviceOnline(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, ref ReMACBuffer[0], ptrDeviceTime);
            if (nRet == 0)
            {
                m_struDeviceTime = (NET_CARD.NET_CARD_TIME)Marshal.PtrToStructure(ptrDeviceTime, typeof(NET_CARD.NET_CARD_TIME));
                DeviceTimeStr = "20" + m_struDeviceTime.wYear.ToString("X2") + "-" + m_struDeviceTime.byMonth.ToString("X2") + "-" + m_struDeviceTime.byDay.ToString("X2") + " " + m_struDeviceTime.byHour.ToString("X2")
                                + ":" + m_struDeviceTime.byMinute.ToString("X2") + ":" + m_struDeviceTime.bySecond.ToString("X2");
                AddStringtoList(m_sStrOutputInfo[0], m_sStrOutputInfo[15], DeviceTimeStr);
                //MessageBox.Show(DeviceTimeStr);
            }
            else
            {
                //写入输出LIST
                ErrorStr = nRet.ToString();
                AddStringtoList(m_sStrOutputInfo[1], m_sStrOutputInfo[14], ErrorStr);
            }

        }
        public static string ConvertToHex(string str, bool reverse)
        {
            byte[] arrByte = System.Text.Encoding.Default.GetBytes(str);
            StringBuilder sb = new StringBuilder();
            if (reverse)
                Array.Reverse(arrByte);
            foreach (byte b in arrByte)
                sb.AppendFormat("{0:x2}", b);
            return sb.ToString();
        }

        private void btnSetTime_Click(object sender, EventArgs e)
        {


            NET_CARD.NET_CARD_TIME struDeviceTime = new NET_CARD.NET_CARD_TIME();
            string strnew = DateTime.Now.ToString();//2014-10-10 10:10:01

            string strTmp = strnew.Substring(2, 2);
            //byte kk = Convert.ToByte(strTmp, 16);
            struDeviceTime.wYear =  Convert.ToByte(strTmp, 16);

            strTmp = strnew.Substring(5, 2);
            struDeviceTime.byMonth = Convert.ToByte(strTmp, 16);
            strTmp = strnew.Substring(8, 2);
            struDeviceTime.byDay = Convert.ToByte(strTmp, 16);
            strTmp = strnew.Substring(11, 2);
            struDeviceTime.byHour = Convert.ToByte(strTmp, 16);
            strTmp = strnew.Substring(14, 2);
            struDeviceTime.byMinute = Convert.ToByte(strTmp, 16);
            strTmp = strnew.Substring(17, 2);
            struDeviceTime.bySecond = Convert.ToByte(strTmp, 16);

            nRet = NET_CARD.NET_CARD_SetDeviceTime(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, ref  struDeviceTime, ref ReMACBuffer[0]);

            if (nRet == 0)
            {
                string strtmp = m_sStrOutputInfo[16] + m_sStrOutputInfo[0];
                AddStringtoList(m_sStrOutputInfo[0], strtmp, m_sStrOutputInfo[0]);
            }
            else
            {
                AddStringtoList(m_sStrOutputInfo[1], m_sStrOutputInfo[12] + m_sStrOutputInfo[1], nRet.ToString());
            }

        }
        //remote open door
        private void button1_Click(object sender, EventArgs e)
        {
            string ErrorStr;
            Int32 nSize = Marshal.SizeOf(m_struDeviceTime);
            IntPtr ptrDeviceTime = Marshal.AllocHGlobal(nSize);
            Marshal.StructureToPtr(m_struDeviceTime, ptrDeviceTime, false);

            nRet = NET_CARD.NET_CARD_RemoteOpen(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, 1, ref ReMACBuffer[0]);

            if (nRet == 0)
            {
                ErrorStr = "Successful";

                AddStringtoList(m_sStrOutputInfo[0], m_sStrOutputInfo[22], ErrorStr);
            }
            else
            {
                //写入输出LIST
                ErrorStr = nRet.ToString();
                MessageBox.Show(ErrorStr);
                AddStringtoList(m_sStrOutputInfo[1], m_sStrOutputInfo[14], ErrorStr);
            }
        }

        private void comBoxLocalIP_SelectedIndexChanged(object sender, EventArgs e)
        {
            szLocalIP = comBoxLocalIP.SelectedItem.ToString();

        }
        //GetAllServerPARM  获取所有服务器参数
        private void btnGetServerPara_Click(object sender, EventArgs e)
        {
            string m_sReturnError;
            byte[] RetChar = new byte[30];
            int nRetLen = 0;
            int nPos = 0;
            int nPort = 0;
            string strTmpStr, strTmp1;
            strTmp1 = strTmpStr = "";

            nRet = NET_CARD.NET_CARD_Get_ALLServerIPandPort(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, ref RetChar[0], ref nRetLen, ref ReMACBuffer[0]);
            if (nRetLen == 18)
            {
                nPort = 0x00;
                nPort |= RetChar[4];
                nPort <<= 8;
                nPort |= RetChar[5];
                nPos = 0;
                strTmpStr = "\r\nTCP server IP:" + RetChar[nPos].ToString("D") + "." + RetChar[nPos + 1].ToString("D") + "." + RetChar[nPos + 2].ToString("D") + "." + RetChar[nPos + 3].ToString("D") + " Port:" + nPort.ToString();// string.Format("TCP server IP:{0:D3}.{1:D3}.{2:D3}.{3:D3}, Port={4,D3}", RetChar[nPos], RetChar[nPos + 1], RetChar[nPos + 2], RetChar[nPos + 3], nPort);
                strTmp1 += strTmpStr + "\r\n";
                nPos = 6;
                strTmpStr = "QR UDP Server IP:" + RetChar[nPos].ToString("D") + "." + RetChar[nPos + 1].ToString("D") + "." + RetChar[nPos + 2].ToString("D") + "." + RetChar[nPos + 3].ToString("D") + " Port:" + nPort.ToString();// string.Format("TCP server IP:{0:D3}.{1:D3}.{2:D3}.{3:D3}, Port={4,D3}", RetChar[nPos], RetChar[nPos + 1], RetChar[nPos + 2], RetChar[nPos + 3], nPort);
                strTmp1 += strTmpStr + "\r\n";
                nPos = 12;
                strTmpStr = "Record UDP server IP:" + RetChar[nPos].ToString("D") + "." + RetChar[nPos + 1].ToString("D") + "." + RetChar[nPos + 2].ToString("D") + "." + RetChar[nPos + 3].ToString("D") + " Port:" + nPort.ToString();// string.Format("TCP server IP:{0:D3}.{1:D3}.{2:D3}.{3:D3}, Port={4,D3}", RetChar[nPos], RetChar[nPos + 1], RetChar[nPos + 2], RetChar[nPos + 3], nPort);
                strTmp1 += strTmpStr + "\r\n";
                DisplayInfoforRecieve(strTmp1);

            }
            else
            {
                m_sReturnError = string.Format("{0:d}", nRet);
                AddStringtoList(m_sStrOutputInfo[1], m_sStrOutputInfo[17], m_sReturnError);
            }
        }
        //  SetUDPServer    设置UDP服务器 
        private void btnSetUDPServer_Click(object sender, EventArgs e)
        {
            int nServerPort = 18887;
            byte[] byteServerIp = new byte[4];
            string ServerIPstr;
            ServerIPstr = textBox10.Text.ToString();

            string[] strIPv4 = new string[4];
            strIPv4 = ServerIPstr.Split('.');
            if (strIPv4.Length != 4)
                return;
            for (int kk = 0; kk < 4; kk++)
            {
                byteServerIp[kk] = Convert.ToByte(strIPv4[kk]);
            }
            nServerPort = int.Parse(textBox11.Text.ToString());


            nRet = NET_CARD.NET_CARD_Set_RecordUpLoad_UDPIPAndPort(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, byteServerIp, nServerPort, ref ReMACBuffer[0]);

            if (nRet == 0)
            {
                string strtmp = "set udp server ip and port " + m_sStrOutputInfo[0];
                AddStringtoList(m_sStrOutputInfo[0], strtmp, m_sStrOutputInfo[0]);
            }
            else
            {
                AddStringtoList(m_sStrOutputInfo[1], "set udp server ip and port " + m_sStrOutputInfo[1], nRet.ToString());
            }
        }
        //  SetTCPServer   设置TCP服务器
        private void btnSetTCPServer_Click(object sender, EventArgs e)
        {
            int nServerPort = 18887;
            byte[] byteServerIp = new byte[4];
            string ServerIPstr;
            ServerIPstr = textBox9.Text.ToString();

            string[] strIPv4 = new string[4];
            strIPv4 = ServerIPstr.Split('.');
            if (strIPv4.Length != 4)
                return;
            for (int kk = 0; kk < 4; kk++)
            {
                byteServerIp[kk] = Convert.ToByte(strIPv4[kk]);
            }
            nServerPort = int.Parse(textBox12.Text.ToString());


            nRet = NET_CARD.NET_CARD_Set_QR_ServerTCPIPAndPort(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, byteServerIp, nServerPort, ref ReMACBuffer[0]);

            if (nRet == 0)
            {
                string strtmp = "set QR udp server ip and port " + m_sStrOutputInfo[0];
                AddStringtoList(m_sStrOutputInfo[0], strtmp, m_sStrOutputInfo[0]);
            }
            else
            {
                AddStringtoList(m_sStrOutputInfo[1], "set QR udp server ip and port " + m_sStrOutputInfo[1], nRet.ToString());
            }
        }
        // SetSPUDPServer  set QR server IP and port 设置二维码与身份证上传的 UDP专用服务器
        private void btnSetSPUDPServer_Click(object sender, EventArgs e)
        {
            int nServerPort = 18887;
            byte[] byteServerIp = new byte[4];
            string ServerIPstr;
            ServerIPstr = textBox8.Text.ToString();

            string[] strIPv4 = new string[4];
            strIPv4 = ServerIPstr.Split('.');
            if (strIPv4.Length != 4)
                return;
            for (int kk = 0; kk < 4; kk++)
            {
                byteServerIp[kk] = Convert.ToByte(strIPv4[kk]);
            }
            nServerPort = int.Parse(textBox13.Text.ToString());


            nRet = NET_CARD.NET_CARD_Set_QR_ServerUDPIPAndPort(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, byteServerIp, nServerPort, ref ReMACBuffer[0]);

            if (nRet == 0)
            {
                string strtmp = "set QR udp server ip and port " + m_sStrOutputInfo[0];
                AddStringtoList(m_sStrOutputInfo[0], strtmp, m_sStrOutputInfo[0]);
            }
            else
            {
                AddStringtoList(m_sStrOutputInfo[1], "set QR udp server ip and port " + m_sStrOutputInfo[1], nRet.ToString());
            }
        }
        //Start monitor
        private void button2_Click(object sender, EventArgs e)
        {

            nRet = NET_CARD.NET_CARD_EnableRealTimeMonitor(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, ref ReMACBuffer[0]);
            if (nRet == 0)
            {

                AddStringtoList(m_sStrOutputInfo[0], m_sStrOutputInfo[20], m_sStrOutputInfo[0]);
            }
            else
            {
                AddStringtoList(m_sStrOutputInfo[1], m_sStrOutputInfo[20] + m_sStrOutputInfo[1], nRet.ToString());
            }

        }
        //Stop monitor
        private void button3_Click(object sender, EventArgs e)
        {
            nRet = NET_CARD.NET_CARD_DisbleRealTimeMonitor(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, ref ReMACBuffer[0]);
            if (nRet == 0)
            {

                AddStringtoList(m_sStrOutputInfo[0], m_sStrOutputInfo[21], m_sStrOutputInfo[0]);
            }
            else
            {
                AddStringtoList(m_sStrOutputInfo[1], m_sStrOutputInfo[21] + m_sStrOutputInfo[1], nRet.ToString());
            }
        }

        private void btnReadNetPARM_Click(object sender, EventArgs e)
        {

            //CEditforModifyNetwork fEditforNet = new CEditforModifyNetwork();
            CEditforModifyNetwork fEditforNet = new CEditforModifyNetwork(DeviceIP, DevicePort, DeviceMask, DeviceGate, DeviceMAC);

            fEditforNet.ShowDialog();
            try
            {
                if (fEditforNet.blnOKEnter == true)
                {
   
                    NET_CARD.NET_CARD_DEVICENETPARA NetParameter = new NET_CARD.NET_CARD_DEVICENETPARA();
                    byte[] sNewIP = new byte[4];
                    byte[] sNewPort = new byte[2];
                    byte[] sNewGate = new byte[4];
                    byte[] sNewMask = new byte[4];
                    byte[] sNewMac = new byte[6];
                    byte[] sOldMac = new byte[6];
                    int nRet = 0;
                    int nNewPort=9998;

                    sNewIP[0] = Convert.ToByte(fEditforNet.arrayIP[0]);
                    sNewIP[1] = Convert.ToByte(fEditforNet.arrayIP[1]);
                    sNewIP[2] = Convert.ToByte(fEditforNet.arrayIP[2]);
                    sNewIP[3] = Convert.ToByte(fEditforNet.arrayIP[3]);
                    NetParameter.m_sNetIP = sNewIP;

                    nNewPort = int.Parse(fEditforNet.editPortstr);
                    sNewPort[0] = (byte)((nNewPort>>8) &0x00ff);
                    sNewPort[1] = (byte)(nNewPort &0x00ff);
                    NetParameter.m_nNetPort = sNewPort;

                    sNewMask[0] = Convert.ToByte(fEditforNet.arrayMask[0]);
                    sNewMask[1] = Convert.ToByte(fEditforNet.arrayMask[1]);
                    sNewMask[2] = Convert.ToByte(fEditforNet.arrayMask[2]);
                    sNewMask[3] = Convert.ToByte(fEditforNet.arrayMask[3]);
                    NetParameter.m_sNetMask = sNewMask;

                    sNewGate[0] = Convert.ToByte(fEditforNet.arrayGate[0]);
                    sNewGate[1] = Convert.ToByte(fEditforNet.arrayGate[1]);
                    sNewGate[2] = Convert.ToByte(fEditforNet.arrayGate[2]);
                    sNewGate[3] = Convert.ToByte(fEditforNet.arrayGate[3]);
                    NetParameter.m_sNetGate = sNewGate;

                    for (int i = 0; i < 6; i++)
                    {
                        sNewMac[i] = Convert.ToByte(fEditforNet.arrayMAC[i], 16); 
                    }
                    NetParameter.m_sNetMAC = sNewMac;

                    for (int i = 0; i < 6; i++)
                    {
                        sOldMac[i] = Convert.ToByte(fEditforNet.arrayOldMAC[i], 16);
                    }
/*
                    sNewMac[0] = Convert.ToByte(fEditforNet.editMACstr.Substring(0, 2));
                    sNewMac[1] = Convert.ToByte(fEditforNet.editMACstr.Substring(2, 2));
                    sNewMac[2] = Convert.ToByte(fEditforNet.editMACstr.Substring(4, 2));
                    sNewMac[3] = Convert.ToByte(fEditforNet.editMACstr.Substring(6, 2));
                    sNewMac[4] = Convert.ToByte(fEditforNet.editMACstr.Substring(8, 2));
                    sNewMac[5] = Convert.ToByte(fEditforNet.editMACstr.Substring(10, 2));
*/
                    nRet = NET_CARD.NET_CARD_SetNetWorkParameter(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, sOldMac, ref NetParameter, ref ReMACBuffer[0]);
                    if (nRet == 0)
                    {
                        //写入输出LIST
                        AddStringtoList(m_sStrOutputInfo[0], m_sStrOutputInfo[13], m_sStrOutputInfo[0]);
                    }
                    else
                    {
                        AddStringtoList(m_sStrOutputInfo[1], m_sStrOutputInfo[13] + m_sStrOutputInfo[1], nRet.ToString());
                    }

                }
            }
            catch
            {

            }
        }

        private void btnDeviceInit_Click(object sender, EventArgs e)
        {

             
            DeviceIP = textBox1.Text.Trim();
            DevicePort = textBox2.Text.Trim();
            DeviceMask = textBox3.Text.Trim();
            DeviceGate = textBox4.Text.Trim();
            DeviceMAC = textBox5.Text.Trim();

            Cfg.SetConfig("DeviceIP", DeviceIP);
            Cfg.SetConfig("DevicePort", DevicePort);
            Cfg.SetConfig("DeviceMask", DeviceMask);
            Cfg.SetConfig("DeviceGate", DeviceGate);
            Cfg.SetConfig("DeviceMAC", DeviceMAC);

            Cfg.SetConfig("LocalIP", szLocalIP);
            Cfg.SetConfig("LocalPort", szLocalPort);

            MessageBox.Show(m_sStrOutputInfo[0]);
        }
        /// <summary>
        ///door operation and door parameters
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void DoorNoCheckBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (DoorNoCheckBox1.Checked)
            {
                nReaderNo |= 0x01;
            }
            else
            {
                nReaderNo &= 0x0E;
            }
        }

        private void DoorNoCheckBox2_CheckedChanged(object sender, EventArgs e)
        {
            if ((DoorNoCheckBox2.Checked))
            {
                nReaderNo |= 0x02;
            }
            else
            {
                nReaderNo &= 0x0D;
            }
        }

        private void DoorNoCheckBox3_CheckedChanged(object sender, EventArgs e)
        {
            if ((DoorNoCheckBox3.Checked))
            {
                nReaderNo |= 0x04;
            }
            else
            {
                nReaderNo &= 0x0B;
            }
        }

        private void DoorNoCheckBox4_CheckedChanged(object sender, EventArgs e)
        {
            if ((DoorNoCheckBox4.Checked))
            {
                nReaderNo |= 0x08;
            }
            else
            {
                nReaderNo &= 0x07;
            }
        }
        //remote open door
        private void button4_Click(object sender, EventArgs e)
        {
            //nReaderNo=1 (0001)	open door1
            //nReaderNo=2 (0010)	open door2
            //nReaderNo=3 (0011)	open door1,door2
            //nReaderNo=4 (0100)	open door3
            //nReaderNo=5 (0101)	open door1,door3
            //nReaderNo=6 (0110)	open door2,door3
            //nReaderNo=7 (0111)	open door1,door2,door3
            //nReaderNo=8 (1000)	open door4
            //nReaderNo=9 (1001)	open door1,door4
            //nReaderNo=10 (1010)	open door2,door4
            //nReaderNo=11 (1011)	open door1,door2,door4
            //nReaderNo=12 (1100)	open door3,door4
            //nReaderNo=13 (1101)	open door1,door3,door4
            //nReaderNo=14 (1110)	open door2,door3,door4
            //nReaderNo=15 (1111)	open door1,door2,door3,door4
            string ErrorStr;
            nRet = NET_CARD.NET_CARD_RemoteOpen(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, nReaderNo, ref ReMACBuffer[0]);
            if (nRet == 0)
            {
                ErrorStr = "Successful";

                AddStringtoList(m_sStrOutputInfo[0], m_sStrOutputInfo[22], ErrorStr);
            }
            else
            {
                //写入输出LIST
                ErrorStr = nRet.ToString();
                MessageBox.Show(ErrorStr);
                AddStringtoList(m_sStrOutputInfo[1], m_sStrOutputInfo[22], ErrorStr);
            }

        }
        //remote close door
        private void button5_Click(object sender, EventArgs e)
        {
            string ErrorStr;
            nRet = NET_CARD.NET_CARD_RemoteClose(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, nReaderNo, ref ReMACBuffer[0]);
            if (nRet == 0)
            {
                ErrorStr = "Successful";

                AddStringtoList(m_sStrOutputInfo[0], m_sStrOutputInfo[22], ErrorStr);
            }
            else
            {
                //写入输出LIST
                ErrorStr = nRet.ToString();
                MessageBox.Show(ErrorStr);
                AddStringtoList(m_sStrOutputInfo[1], m_sStrOutputInfo[23], ErrorStr);
            }
        }
        //door always on门常开
        private void button6_Click(object sender, EventArgs e)
        {
            string ErrorStr;
            nRet = NET_CARD.NET_CARD_AlwayOpen(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, nReaderNo, ref ReMACBuffer[0]);
            if (nRet == 0)
            {
                ErrorStr = "Successful";

                AddStringtoList(m_sStrOutputInfo[0], m_sStrOutputInfo[37], ErrorStr);
            }
            else
            {
                //写入输出LIST
                ErrorStr = nRet.ToString();
                MessageBox.Show(ErrorStr);
                AddStringtoList(m_sStrOutputInfo[1], m_sStrOutputInfo[37], ErrorStr);
            }
        }
        //Recovery door State 恢复门状态
        private void button7_Click(object sender, EventArgs e)
        {            
            string ErrorStr;
            nRet = NET_CARD.NET_CARD_RecoveryState(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, nReaderNo, ref ReMACBuffer[0]);
            if (nRet == 0)
            {
                ErrorStr = "Successful";

                AddStringtoList(m_sStrOutputInfo[0], m_sStrOutputInfo[38], ErrorStr);
            }
            else
            {
                //写入输出LIST
                ErrorStr = nRet.ToString();
                MessageBox.Show(ErrorStr);
                AddStringtoList(m_sStrOutputInfo[1], m_sStrOutputInfo[38], ErrorStr);
            }
        }
        // InterLock    设置互锁
        private void button8_Click(object sender, EventArgs e)
        {
            string ErrorStr;
            string m_sMuxLock;
            byte[] MuxLock = new byte[4];


	        int m_iMuxLock=InterLockComBox.SelectedIndex;
	        m_sMuxLock="00000000";
	        switch(m_iMuxLock)
	        {
		        case 0: m_sMuxLock="00000000";break;
		        case 1: m_sMuxLock="01010000";break;
		        case 2: m_sMuxLock="01000100";break;
		        case 3: m_sMuxLock="01000001";break;
		        case 4: m_sMuxLock="00010100";break;
		        case 5: m_sMuxLock="00010001";break;
		        case 6: m_sMuxLock="00000101";break;
		        case 7: m_sMuxLock="01010100";break;
		        case 8: m_sMuxLock="01010001";break;
		        case 9: m_sMuxLock="01000101";break;
		        case 10: m_sMuxLock="00010101";break;
		        case 11: m_sMuxLock="01010101";break;
	        }
            MuxLock[0] = byte.Parse(m_sMuxLock.Substring(0,2));
            MuxLock[1] = byte.Parse(m_sMuxLock.Substring(2,2));
            MuxLock[2] = byte.Parse(m_sMuxLock.Substring(4,2));
            MuxLock[3] = byte.Parse(m_sMuxLock.Substring(6,2));

            nRet = NET_CARD.NET_CARD_SetInterLock(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, ref MuxLock[0], ref ReMACBuffer[0]);
            if (nRet == 0)
            {
                ErrorStr = "Successful";

                AddStringtoList(m_sStrOutputInfo[0], m_sStrOutputInfo[38], ErrorStr);
            }
            else
            {
                //写入输出LIST
                ErrorStr = nRet.ToString();
                MessageBox.Show(ErrorStr);
                AddStringtoList(m_sStrOutputInfo[1], m_sStrOutputInfo[38], ErrorStr);
            }


        }

        //Overtime Alarm启动门超时报警
        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            string ErrorStr;
            int nAlarm;
            if ((OvertimeAlarmcheckBox1.Checked))
                nAlarm = nReaderNo;
            else
                nAlarm = 0;

            nRet = NET_CARD.NET_CARD_EnableTimeOutAlarm(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, nAlarm, ref ReMACBuffer[0]);
            if (nRet == 0)
            {
                ErrorStr = "Successful";

                AddStringtoList(m_sStrOutputInfo[0], m_sStrOutputInfo[26], ErrorStr);
            }
            else
            {
                //写入输出LIST
                ErrorStr = nRet.ToString();
                MessageBox.Show(ErrorStr);
                AddStringtoList(m_sStrOutputInfo[1], m_sStrOutputInfo[26], ErrorStr);
            }
	
        }
        //DoorDelay    设置锁延时
        private void button9_Click(object sender, EventArgs e)
        {
            string ErrorStr;
            byte m_nLockDelay = 0;
            m_nLockDelay = byte.Parse(textBox14.Text.ToString());

            NET_CARD.NET_CARD_OPEN_DELAY DoorDelay = new NET_CARD.NET_CARD_OPEN_DELAY();
            DoorDelay.Door01DelayTime = m_nLockDelay;//lock 1 delay
            DoorDelay.Door02DelayTime = m_nLockDelay;//lock 2 delay
            DoorDelay.Door03DelayTime = m_nLockDelay;//lock 3 delay
            DoorDelay.Door04DelayTime = m_nLockDelay;//lock 4 delay
            nRet = NET_CARD.NET_CARD_SetOpenDelayTime(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, ref DoorDelay, ref ReMACBuffer[0]);
            if (nRet == 0)
            {
                ErrorStr = "Successful";

                AddStringtoList(m_sStrOutputInfo[0], m_sStrOutputInfo[39], ErrorStr);
            }
            else
            {
                //写入输出LIST
                ErrorStr = nRet.ToString();
                MessageBox.Show(ErrorStr);
                AddStringtoList(m_sStrOutputInfo[1], m_sStrOutputInfo[39], ErrorStr);
            }

 

        }
        //LockType    设置锁类型
        private void button10_Click(object sender, EventArgs e)
        {
            string ErrorStr;
            byte nLockType;
            if (radioButton2.Checked == true)
                nLockType = (byte)nReaderNo;
            else
                nLockType = (byte)(nReaderNo ^ 0xff);

            nRet = NET_CARD.NET_CARD_SetLockType(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, nLockType, ref ReMACBuffer[0]);
            if (nRet == 0)
            {
                ErrorStr = "Successful";

                AddStringtoList(m_sStrOutputInfo[0], m_sStrOutputInfo[40], ErrorStr);
            }
            else
            {
                //写入输出LIST
                ErrorStr = nRet.ToString();
                MessageBox.Show(ErrorStr);
                AddStringtoList(m_sStrOutputInfo[1], m_sStrOutputInfo[40], ErrorStr);
            }
        }
        //Alarm Delay 报警输出延时
        private void button11_Click(object sender, EventArgs e)
        {
            string ErrorStr;
            byte m_nAlarmOutDelay1 = 0;
            byte m_nAlarmOutDelay2 = 0;
            byte m_nAlarmOutDelay3 = 0;
            byte m_nAlarmOutDelay4 = 0;

            m_nAlarmOutDelay1 = byte.Parse(textBox15.Text.ToString());
            m_nAlarmOutDelay2 = byte.Parse(textBox16.Text.ToString());
            m_nAlarmOutDelay3 = byte.Parse(textBox17.Text.ToString());
            m_nAlarmOutDelay4 = byte.Parse(textBox18.Text.ToString());


            NET_CARD.NET_CARD_ALARM_DELAY AlarmDelay = new NET_CARD.NET_CARD_ALARM_DELAY();
            AlarmDelay.Alarm01DelayTime = m_nAlarmOutDelay1;
            AlarmDelay.Alarm02DelayTime = m_nAlarmOutDelay2;
            AlarmDelay.Alarm03DelayTime = m_nAlarmOutDelay3;
            AlarmDelay.Alarm04DelayTime = m_nAlarmOutDelay4;
            nRet = NET_CARD.NET_CARD_SetAlarmDelayTime(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, ref AlarmDelay, ref ReMACBuffer[0]);
            if (nRet == 0)
            {
                ErrorStr = "Successful";

                AddStringtoList(m_sStrOutputInfo[0], m_sStrOutputInfo[41], ErrorStr);
            }
            else
            {
                //写入输出LIST
                ErrorStr = nRet.ToString();
                MessageBox.Show(ErrorStr);
                AddStringtoList(m_sStrOutputInfo[1], m_sStrOutputInfo[41], ErrorStr);
            }
        }
        //PasswordOpen 密码开门 
        private void button12_Click(object sender, EventArgs e)
        {
            string ErrorStr;
            byte[] Password = new byte[10];

            textBox19.Text.Trim();
            textBox20.Text.Trim();
            textBox21.Text.Trim();
            textBox22.Text.Trim();
            if((textBox19.Text.Length!=4)||(textBox20.Text.Length!=4)||(textBox21.Text.Length!=4)||(textBox22.Text.Length!=4))
            {
                MessageBox.Show(m_sStrOutputInfo[28]);
		        return;
            }
            Password[0] = byte.Parse(textBox19.Text.Substring(0,2));
            Password[1] = byte.Parse(textBox19.Text.Substring(2,2));
            Password[2] = byte.Parse(textBox20.Text.Substring(0,2));
            Password[3] = byte.Parse(textBox20.Text.Substring(2,2));
            Password[4] = byte.Parse(textBox21.Text.Substring(0,2));
            Password[5] = byte.Parse(textBox21.Text.Substring(2,2));
            Password[6] = byte.Parse(textBox22.Text.Substring(0,2));
            Password[7] = byte.Parse(textBox22.Text.Substring(2,2));

            NET_CARD.NET_CARD_DOORPASSWORD DoorPassword = new NET_CARD.NET_CARD_DOORPASSWORD();

	        //door1 4 password
	        DoorPassword.Door01Password1[0]=Password[0];
	        DoorPassword.Door01Password1[1]=Password[1];
	        DoorPassword.Door01Password2[0]=Password[2];
	        DoorPassword.Door01Password2[1]=Password[3];
	        DoorPassword.Door01Password3[0]=Password[4];
	        DoorPassword.Door01Password3[1]=Password[5];
	        DoorPassword.Door01Password4[0]=Password[6];
	        DoorPassword.Door01Password4[1]=Password[7];
	        //door2 4 password
	        DoorPassword.Door02Password1[0]=Password[0];
	        DoorPassword.Door02Password1[1]=Password[1];
	        DoorPassword.Door02Password2[0]=Password[2];
	        DoorPassword.Door02Password2[1]=Password[3];
	        DoorPassword.Door02Password3[0]=Password[4];
	        DoorPassword.Door02Password3[1]=Password[5];
	        DoorPassword.Door02Password4[0]=Password[6];
	        DoorPassword.Door02Password4[1]=Password[7];
	        //door3 4 password
	        DoorPassword.Door03Password1[0]=Password[0];
	        DoorPassword.Door03Password1[1]=Password[1];
	        DoorPassword.Door03Password2[0]=Password[2];
	        DoorPassword.Door03Password2[1]=Password[3];
	        DoorPassword.Door03Password3[0]=Password[4];
	        DoorPassword.Door03Password3[1]=Password[5];
	        DoorPassword.Door03Password4[0]=Password[6];
	        DoorPassword.Door03Password4[1]=Password[7];
	        //door4 4 password
	        DoorPassword.Door04Password1[0]=Password[0];
	        DoorPassword.Door04Password1[1]=Password[1];
	        DoorPassword.Door04Password2[0]=Password[2];
	        DoorPassword.Door04Password2[1]=Password[3];
	        DoorPassword.Door04Password3[0]=Password[4];
	        DoorPassword.Door04Password3[1]=Password[5];
	        DoorPassword.Door04Password4[0]=Password[6];
	        DoorPassword.Door04Password4[1]=Password[7];

            nRet = NET_CARD.NET_CARD_SetDoorPassWord(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, ref DoorPassword, ref ReMACBuffer[0]);
            if (nRet == 0)
            {
                ErrorStr = "Successful";

                AddStringtoList(m_sStrOutputInfo[0], m_sStrOutputInfo[41], ErrorStr);
            }
            else
            {
                //写入输出LIST
                ErrorStr = nRet.ToString();
                MessageBox.Show(ErrorStr);
                AddStringtoList(m_sStrOutputInfo[1], m_sStrOutputInfo[41], ErrorStr);
            }

        }

        private void button13_Click(object sender, EventArgs e)
        {
            string ErrorStr;
            byte m_nDruessDelay = 0;
            m_nDruessDelay = byte.Parse(textBox23.Text.ToString());

            NET_CARD.NET_CARD_LIGHT_DELAY Light_Delay = new NET_CARD.NET_CARD_LIGHT_DELAY();
            Light_Delay.LightOpenDelayTime  = 30; //Magnetometer Out Delay
            Light_Delay.DruessDelayTime     = m_nDruessDelay;
            nRet = NET_CARD.NET_CARD_SetDuressAlarmDelayTime(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, ref Light_Delay, ref ReMACBuffer[0]);
            if (nRet == 0)
            {
                ErrorStr = "Successful";
                AddStringtoList(m_sStrOutputInfo[0], m_sStrOutputInfo[29], ErrorStr);
            }
            else
            {
                //写入输出LIST
                ErrorStr = nRet.ToString();
                MessageBox.Show(ErrorStr);
                AddStringtoList(m_sStrOutputInfo[1], m_sStrOutputInfo[29], ErrorStr);
            }

        }

        private void button14_Click(object sender, EventArgs e)
        {
            string ErrorStr;
            byte[] Password = new byte[2];

            textBox24.Text.Trim();
            if (textBox24.Text.Length != 4)
            {
                MessageBox.Show(m_sStrOutputInfo[28]);
                return;
            }
            Password[0] = byte.Parse(textBox24.Text.Substring(0, 2));
            Password[1] = byte.Parse(textBox24.Text.Substring(2, 2));

            NET_CARD.NET_CARD_DOORDURESSWORD DruessPassword = new NET_CARD.NET_CARD_DOORDURESSWORD();

            //door 1
            DruessPassword.Door01Password[0] = Password[0];
            DruessPassword.Door01Password[1] = Password[1];
            //door 2
            DruessPassword.Door02Password[0] = Password[0];
            DruessPassword.Door02Password[1] = Password[1];
            //door 3
            DruessPassword.Door03Password[0] = Password[0];
            DruessPassword.Door03Password[1] = Password[1];
            //door 4
            DruessPassword.Door04Password[0] = Password[0];
            DruessPassword.Door04Password[1] = Password[1];

            nRet = NET_CARD.NET_CARD_SetDoorDuressPassWord(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, ref DruessPassword, ref ReMACBuffer[0]);
            if (nRet == 0)
            {
                ErrorStr = "Successful";

                AddStringtoList(m_sStrOutputInfo[0], m_sStrOutputInfo[30], ErrorStr);
            }
            else
            {
                //写入输出LIST
                ErrorStr = nRet.ToString();
                MessageBox.Show(ErrorStr);
                AddStringtoList(m_sStrOutputInfo[1], m_sStrOutputInfo[30], ErrorStr);
            }
        }
        //Get Status 获取状态
        private void button15_Click(object sender, EventArgs e)
        {
            string ErrorStr;
            String DoorCiStr;
            String OpenBtnStr;
            String InputStr;
            NET_CARD.NET_CARD_DOORSTATUS DoorStatus = new NET_CARD.NET_CARD_DOORSTATUS();

            nRet = NET_CARD.NET_CARD_GetRunStatus(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, ref DoorStatus, ref ReMACBuffer[0]);
            if (nRet == 0)
            {
                checkBox2.Checked = true;
                checkBox3.Checked = true;
                checkBox4.Checked = true;
                checkBox5.Checked = true;

                if ((DoorStatus.m_iDoorCi & 0x01)==0x01)
                {
                    DoorCiStr = " Door: Open";
                }
                else
                {
                    DoorCiStr = " Door: Close";
                    checkBox2.Checked = false;
                }
                if ((DoorStatus.m_iDoorCi & 0x02)==0x01)
                {
                    DoorCiStr += " Open";
                }
                else
                {
                    DoorCiStr += " Close";
                    checkBox3.Checked = false;
                }
                if ((DoorStatus.m_iDoorCi & 0x04)==0x01)
                {
                    DoorCiStr += " Open";
                }
                else
                {
                    DoorCiStr += " Close";
                    checkBox4.Checked = false;
                }
                if ((DoorStatus.m_iDoorCi & 0x08)==0x01)
                {
                    DoorCiStr += " Open";
                }
                else
                {
                    DoorCiStr += " Close";
                    checkBox5.Checked = false;
                }


                if ((DoorStatus.m_iDoorCi & 0x01)==0x01)
                {
                    OpenBtnStr = " BTN: Open";
                }
                else
                {
                    OpenBtnStr = " BTN: Close";
                }
                if ((DoorStatus.m_iDoorCi & 0x02)==0x01)
                {
                    OpenBtnStr += " Open";
                }
                else
                {
                    OpenBtnStr += " Close";
                }
                if ((DoorStatus.m_iDoorCi & 0x04)==0x01)
                {
                    OpenBtnStr += " Open";
                }
                else
                {
                    OpenBtnStr += " Close";
                }
                if ((DoorStatus.m_iDoorCi & 0x08)==0x01)
                {
                    OpenBtnStr += " Open";
                }
                else
                {
                    OpenBtnStr += " Close";
                }

                
                if ((DoorStatus.m_iDoorCi & 0x01)==0x01)
                    InputStr = " Input: Open";
                else
                    InputStr = " Input: Close";
                if ((DoorStatus.m_iDoorCi & 0x02)==0x01)
                    InputStr += " Open";
                else
                    InputStr += " Close";
                if ((DoorStatus.m_iDoorCi & 0x04)==0x01)
                    InputStr += " Open";
                else
                    InputStr += " Close";
                if ((DoorStatus.m_iDoorCi & 0x08)==0x01)
                    InputStr += " Open";
                else
                    InputStr += " Close";

                String HistoryRecordStr;
                HistoryRecordStr="HistoryRecord Num."+ DoorStatus.m_iDisOnlineCardNums.ToString();
                String RealRecordStr;
                RealRecordStr="RealRecord Num.="+DoorStatus.m_iRealCardNums.ToString();

                String TempCardNumStr;
                TempCardNumStr="TempCard Num.="+DoorStatus.m_iCardNumTemp.ToString();
                String SortCardNumStr;
                SortCardNumStr="SortCard Num.="+DoorStatus.m_iCardNumSort.ToString();

                String OutPutStr;
                OutPutStr = DoorCiStr + "\r\n";
                OutPutStr += OpenBtnStr + "\r\n";
                OutPutStr += InputStr + "\r\n";
                OutPutStr += HistoryRecordStr + "\r\n";
                OutPutStr += RealRecordStr + "\r\n";
                OutPutStr += TempCardNumStr + "\r\n";
                OutPutStr += SortCardNumStr + "\r\n";

                DisplayInfoforRecieve(OutPutStr);

            }
            else
            {
                //写入输出LIST
                ErrorStr = nRet.ToString();
                MessageBox.Show(ErrorStr);
                AddStringtoList(m_sStrOutputInfo[1], m_sStrOutputInfo[30], ErrorStr);
            }
        }

        private void button16_Click(object sender, EventArgs e)
        {
            string ErrorStr;
	        int  VoiceLength=0;

            byte[] VoiceTmp = new byte[40];
            textBox25.Text.Trim();
	        if(textBox25.Text.Length<2)
	        {                
#if ENGLISH
		        MessageBox.Show("Please Input Audio Code");
#else
		        MessageBox.Show("请输入语音代码");
#endif
		        return;
	        }
            VoiceLength = textBox25.Text.Length/2;
	        for(int kk=0;kk<(textBox25.Text.Length/2);kk++)
	        {
                VoiceTmp[kk] = byte.Parse(textBox25.Text.Substring(kk*2, 2));
	        }             

	        int nbOpenDoor=0;//是否开门
	        int nReaderNo=1;//开哪个门
            nRet = NET_CARD.NET_CARD_VoiceAndOpen(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, VoiceTmp, VoiceLength,nbOpenDoor,nReaderNo,ref ReMACBuffer[0]);

            if (nRet == 0)
            {
                ErrorStr = "Successful";

                AddStringtoList(m_sStrOutputInfo[0], m_sStrOutputInfo[36], ErrorStr);
            }
            else
            {
                //写入输出LIST
                ErrorStr = nRet.ToString();
                MessageBox.Show(ErrorStr);
                AddStringtoList(m_sStrOutputInfo[1], m_sStrOutputInfo[36], ErrorStr);
            }
        }

        private void button17_Click(object sender, EventArgs e)
        {
            string ErrorStr;
            int VoiceLength = 0;

            byte[] VoiceTmp = new byte[40];
            textBox25.Text.Trim();
            if (textBox25.Text.Length < 2)
            {
#if ENGLISH
		        MessageBox.Show("Please Input Audio Code");
#else
                MessageBox.Show("请输入语音代码");
#endif
                return;
            }
            VoiceLength = textBox25.Text.Length / 2;
            for (int kk = 0; kk < (textBox25.Text.Length / 2); kk++)
            {
                VoiceTmp[kk] = byte.Parse(textBox25.Text.Substring(kk * 2, 2));
            }

            int nbOpenDoor = 1;//开门
            int nReaderNo = 1;//门1
            nRet = NET_CARD.NET_CARD_VoiceAndOpen(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, VoiceTmp, VoiceLength, nbOpenDoor, nReaderNo, ref ReMACBuffer[0]);

            if (nRet == 0)
            {
                ErrorStr = "Successful";

                AddStringtoList(m_sStrOutputInfo[0], m_sStrOutputInfo[36], ErrorStr);
            }
            else
            {
                //写入输出LIST
                ErrorStr = nRet.ToString();
                MessageBox.Show(ErrorStr);
                AddStringtoList(m_sStrOutputInfo[1], m_sStrOutputInfo[36], ErrorStr);
            }
        }

        private void button18_Click(object sender, EventArgs e)
        {
            string ErrorStr;
            int nRecordCount=0;
            byte m_nDruessDelay = 0;
            m_nDruessDelay = byte.Parse(textBox23.Text.ToString());

            NET_CARD.NET_CARD_RECORDINFO[] RecordInfo = new NET_CARD.NET_CARD_RECORDINFO[80];

            nRet = NET_CARD.NET_CARD_GetHistroyRecord(NET_CARD.DEVICE_NET_ACCESS, DeviceIP, nDevicePort, 80,ref nRecordCount, ref RecordInfo[0], ref ReMACBuffer[0]);
            if (nRet == 0)
            {
                ErrorStr = "Successful";
                AddStringtoList(m_sStrOutputInfo[0], m_sStrOutputInfo[29], ErrorStr);
            }
            else
            {
                //写入输出LIST
                ErrorStr = nRet.ToString();
                MessageBox.Show(ErrorStr);
                AddStringtoList(m_sStrOutputInfo[1], m_sStrOutputInfo[29], ErrorStr);
            }

  
        }

        private void m_wndOutputList_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void checkBox8_CheckedChanged(object sender, EventArgs e)
        {
	        if(checkBox8.Checked)
	        {
                nReaderRight ^= (0x01<<0);
	        }else{
		        
                nReaderRight |=0x01;
	        }
        }

        private void checkBox7_CheckedChanged(object sender, EventArgs e)
        {
            if ((checkBox7.Checked))
            {
                nReaderRight ^= (0x01 << 1);

            }
            else
            {
                nReaderRight |= 0x02;                
            }
        }

        private void radioButton4_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton4.Checked == true)
                nCardPassword = 0;
            else
                nCardPassword = 1;
        }

        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton3.Checked == true)
                nCardPassword = 1;
            else
                nCardPassword = 0;
        }

        private void button19_Click(object sender, EventArgs e)
        {
	        //1)Get all cards Series
            string CardIDStr, TmpStr, CardIDTmpStr;
	        string Card_PasswordStr,Card_DateStr;

	        byte Card_CardStatus=0;
	        byte Card_WeekProgram=0;

	       // int nMaxCardNum=1000;
	        //byte  CardStatus=0;
	        //Get First CardNum
            textBox26.Text.Trim();//得到卡号，卡号是8位16进制
	        if(textBox26.Text.Length!=8)
		        return;

            CardIDStr = textBox26.Text;
            CardIDTmpStr = CardIDStr;
            //ulong uCardID =0;
           // uCardID = Convert.ToUInt64(CardIDStr);
            uint uCardID = 0;

            uCardID = (uint)(Convert.ToInt32(textBox26.Text,16));


 
	        //////////////////////////////////////////////////////卡状态组合 下 组成一个字节
	        //最高二位是卡或卡+密码的模式
            if(nCardPassword==0)
	        {
	           Card_CardStatus = 0x00;//卡00，   CardStatus最高二位 第7，6位
	        }
	        else
	        {
	           Card_CardStatus = 0xC0;//卡+密码  CardStatus最高二位 第7，6位   1100,0000 门1门2都是卡+密码
	        }
            //是否能过门1门2的权限
            Card_CardStatus = (byte)((byte)Card_CardStatus & (nReaderRight << 4)); //第5，4位，是否能过门1门2的权限
	        //3，2位保留，最低二位是卡状态，1，0为卡状态
            if (checkBox6.Checked)
                Card_CardStatus = (byte)(Card_CardStatus & 0xf0);//最低二位为00，第3，4位保留，定为00;
	        else
                Card_CardStatus = (byte)(Card_CardStatus & 0xf2);//最低二位为02，启用了有效期
	        //////////////////////////////////////////////////////卡状态组合 上

	        //密码 2B
            Card_PasswordStr ="1234";
            textBox29.Text.Trim();
	        if(textBox29.Text.Length!=4)
		        return;
            Card_PasswordStr = textBox29.Text.Trim();
            
            //4.截止有效期(年月日 3B)  //注：如0x180915,年只最后2位，如2018只取18，去掉20
	        Card_DateStr="FFFFFF";
	        if ((checkBox6.Checked))
	        {
                textBox27.Text.Trim();
	            if(textBox27.Text.Length!=6)
		            return;
                Card_DateStr = textBox27.Text.Trim();
	        }
	        //////////////////////////////////////////////////////////周编程 1B
	        Card_WeekProgram =0x00;

            CardIDStr += (String.Format("{0:X}", Card_CardStatus)).PadLeft(2, '0'); 
	        CardIDStr+=Card_PasswordStr;
	        CardIDStr+=Card_DateStr;

            TmpStr = (String.Format("{0:X}", Card_WeekProgram)).PadLeft(2, '0');
            CardIDStr += TmpStr;

	        nRet = SendCommandtoDevice("4200FF"+CardIDStr);
	        if(nRet==0)
	        {
                strTmp2 = " Single card download OK, CardSeries="+CardIDTmpStr;
		        strTmp1 = strTmp2+"\r\n";

                //ProcessDelegate showProcess = new ProcessDelegate(DisplayInfoforRecieve);
                //m_wndList1.Invoke(showProcess, strTmp1);

		        DisplayInfoforRecieve(strTmp1);
                if (checkBox1.Checked)
		        {
			        uCardID++;
                    textBox26.Text = (uCardID.ToString("X")).PadLeft(8,'0');
		        }

	        }
        }

        private void checkBox6_CheckedChanged(object sender, EventArgs e)
        {
        
        }

        private void button20_Click(object sender, EventArgs e)
        {
            //1)Get all cards Series
            string CardIDStr, TmpStr, CardIDTmpStr;
            string Card_PasswordStr, Card_DateStr;

            byte Card_CardStatus = 0;
            byte Card_WeekProgram = 0;

            // int nMaxCardNum=1000;
            //byte  CardStatus=0;
            //Get First CardNum
            textBox26.Text.Trim();//得到卡号，卡号是8位16进制
            if (textBox26.Text.Length != 8)
                return;

            CardIDStr = textBox26.Text;
            CardIDTmpStr = CardIDStr;
            //ulong uCardID =0;
            // uCardID = Convert.ToUInt64(CardIDStr);
            uint uCardID = 0;

            uCardID = (uint)(Convert.ToInt32(textBox26.Text, 16));



            //////////////////////////////////////////////////////卡状态组合 下 组成一个字节
            //最高二位是卡或卡+密码的模式
            if (nCardPassword == 0)
            {
                Card_CardStatus = 0x00;//卡00，   CardStatus最高二位 第7，6位
            }
            else
            {
                Card_CardStatus = 0xC0;//卡+密码  CardStatus最高二位 第7，6位   1100,0000 门1门2都是卡+密码
            }
            //是否能过门1门2的权限
            Card_CardStatus = (byte)((byte)Card_CardStatus & (nReaderRight << 4)); //第5，4位，是否能过门1门2的权限
            //3，2位保留，最低二位是卡状态，1，0为卡状态

            Card_CardStatus = (byte)(Card_CardStatus & 0x03);//03 Card Status deleted 
            //////////////////////////////////////////////////////卡状态组合 上

            //密码 2B
            Card_PasswordStr = "1234";
            textBox29.Text.Trim();
            if (textBox29.Text.Length != 4)
                return;
            Card_PasswordStr = textBox29.Text.Trim();

            //4.截止有效期(年月日 3B)  //注：如0x180915,年只最后2位，如2018只取18，去掉20
            Card_DateStr = "FFFFFF";
            if ((checkBox6.Checked))
            {
                textBox27.Text.Trim();
                if (textBox27.Text.Length != 6)
                    return;
                Card_DateStr = textBox27.Text.Trim();
            }
            //////////////////////////////////////////////////////////周编程 1B
            Card_WeekProgram = 0x00;

            CardIDStr += (String.Format("{0:X}", Card_CardStatus)).PadLeft(2, '0');
            CardIDStr += Card_PasswordStr;
            CardIDStr += Card_DateStr;

            TmpStr = (String.Format("{0:X}", Card_WeekProgram)).PadLeft(2, '0');
            CardIDStr += TmpStr;

            nRet = SendCommandtoDevice("4200FF" + CardIDStr);
            if (nRet == 0)
            {
                strTmp2 = " Single card download OK, CardSeries=" + CardIDTmpStr;
                strTmp1 = strTmp2 + "\r\n";

                //ProcessDelegate showProcess = new ProcessDelegate(DisplayInfoforRecieve);
                //m_wndList1.Invoke(showProcess, strTmp1);

                DisplayInfoforRecieve(strTmp1);
                if (checkBox1.Checked)
                {
                    uCardID++;
                    textBox26.Text = (uCardID.ToString("X")).PadLeft(8, '0');
                }

            }

        }

        private void button21_Click(object sender, EventArgs e)
        {
            //1)Get all cards Series
            string CardIDStr;

            //Get First CardNum
            textBox26.Text.Trim();//得到卡号，卡号是8位16进制
            if (textBox26.Text.Length != 8)
                return;

            CardIDStr = textBox26.Text;

            uint uCardID = 0;

            uCardID = (uint)(Convert.ToInt32(textBox26.Text, 16));



            nRet = SendCommandtoDevice("4300FF" + CardIDStr);
            if (nRet == 0)
            {
                strTmp2 = " Query Card OK, CardSeries=" + CardIDStr;
                strTmp1 = strTmp2 + "\r\n";

                DisplayInfoforRecieve(strTmp1);
                if (checkBox1.Checked)
                {
                    uCardID++;
                    textBox26.Text = (uCardID.ToString("X")).PadLeft(8, '0');
                }

            }
        }

        public void ThreadFunc()
        {
            int nRet = 0;
            int nMaxCardNum = 1000;

            nMaxCardNum = Convert.ToInt32(textBox28.Text);

            //1)Get all cards Series
            string m_sTempStr, strTmp2;

            string m_sReturnError, CardIDStr;

            m_sTempStr = StartCardIDStr;

            string AllCardInfoStr = "";


            if (nTypeforDownloadCard == 0)
            {
                for (int kk = 0; kk < nMaxCardNum; kk++)
                {
                    CardIDStr = uCardIDID.ToString("X8");
                    AllCardInfoStr = (CardIDStr + StartCardIDStr2);
                    uCardIDID++;

                    nRet = SendCommandtoDevice("4200FF" + AllCardInfoStr);
                    if (nRet == 0)
                    {
                        strTmp2 = " Single Download Package " + (kk + 1).ToString()+"\r\n";
                        ProcessDelegate showProcess = new ProcessDelegate(DisplayInfoforRecieve);
                        m_wndList1.Invoke(showProcess, strTmp2);

                    }
                    else
                    {
                        if ((nRet > 0) && (nRet < 13))
                            m_sReturnError = m_sCommandState[nRet].ToString();
                        else
                            m_sReturnError = nRet.ToString();
                        ProcessDelegate showProcess = new ProcessDelegate(DisplayInfoforRecieve);
                        m_wndList1.Invoke(showProcess, m_sReturnError);
                        return;
                    }
                }
            }
            else if (nTypeforDownloadCard == 1)
            {

                for (int ii = 0; ii < nMaxCardNum; ii++)
                {
                    CardIDStr = uCardIDID.ToString("X8");
                    uCardIDID++;
                    nRet = SendCommandtoDevice("4300FF" + CardIDStr);
                    if (nRet == 0)
                    {
                        strTmp2 = " Query successful " + (ii + 1).ToString();
                        ProcessDelegate showProcess = new ProcessDelegate(DisplayInfoforRecieve);
                        m_wndList1.Invoke(showProcess, CardIDStr + strTmp2);
                    }
                    else
                    {
                        if ((nRet > 0) && (nRet < 13))
                            m_sReturnError = m_sCommandState[nRet].ToString();
                        else
                            m_sReturnError = nRet.ToString();
                        ProcessDelegate showProcess = new ProcessDelegate(DisplayInfoforRecieve);
                        m_wndList1.Invoke(showProcess, m_sReturnError);
                        return;
                    }
                }

            }
            else if (nTypeforDownloadCard == 2)
            {


                int PackCardNum = 96;//96;
                int ii = 0;
                for (ii = 0; ii < nMaxCardNum / PackCardNum; ii++)
                {
                    AllCardInfoStr = "";
                    for (int kk = 0; kk < PackCardNum; kk++)
                    {
                        CardIDStr = uCardIDID.ToString("X8");
                        AllCardInfoStr += (CardIDStr + StartCardIDStr2);
                        uCardIDID++;
                    }

                    // m_sTempStr.Format("%04X%02X",ii*PackCardNum,PackCardNum);
                    m_sTempStr = (ii * PackCardNum).ToString("X4") + PackCardNum.ToString("X2");
                    nRet = SendCommandtoDevice("4203FF" + m_sTempStr + AllCardInfoStr);
                    if (nRet == 0)
                    {
                        strTmp2 = " Card No of packs=" + (ii * PackCardNum).ToString() + " Batch Download Package" + (ii + 1).ToString() + "\r\n";
                        ProcessDelegate showProcess = new ProcessDelegate(DisplayInfoforRecieve);
                        m_wndList1.Invoke(showProcess, strTmp2);
                    }
                    else
                    {
                        if ((nRet > 0) && (nRet < 13))
                            m_sReturnError = m_sCommandState[nRet].ToString();
                        else
                            m_sReturnError = nRet.ToString();
                        ProcessDelegate showProcess = new ProcessDelegate(DisplayInfoforRecieve);
                        m_wndList1.Invoke(showProcess, m_sReturnError);
                        return;
                    }
                }
                int nRestcards = nMaxCardNum % PackCardNum;

                AllCardInfoStr = "";
                if (nRestcards > 0)
                {
                    for (int kk = 0; kk < nRestcards; kk++)
                    {
                        CardIDStr = uCardIDID.ToString("X8");
                        AllCardInfoStr += (CardIDStr + StartCardIDStr2);
                        uCardIDID++;
                    }
                    //m_sTempStr.Format("%04X%02X",ii*PackCardNum,nRestcards);
                    m_sTempStr = (ii * PackCardNum).ToString("X4") + nRestcards.ToString("X2");
                    nRet = SendCommandtoDevice("4203FF" + m_sTempStr + AllCardInfoStr);
                    if (nRet == 0)
                    {
                        strTmp2 = " Download the last package in batch,，Number of Cards =" + nRestcards.ToString() + "Downloaded in total Cards=" + (ii * PackCardNum + nRestcards).ToString() + "\r\n";
                        ProcessDelegate showProcess = new ProcessDelegate(DisplayInfoforRecieve);
                        m_wndList1.Invoke(showProcess, strTmp2);

                    }
                    else
                    {
                        if ((nRet > 0) && (nRet < 13))
                            m_sReturnError = m_sCommandState[nRet].ToString();
                        else
                            m_sReturnError = nRet.ToString();
                        ProcessDelegate showProcess = new ProcessDelegate(DisplayInfoforRecieve);
                        m_wndList1.Invoke(showProcess, m_sReturnError);
                        return;
                    }
                }

            }
            return;
        }

        private void button24_Click(object sender, EventArgs e)
        {

	        nRet=SendCommandtoDevice("4202FF02");
	        if(nRet==0)
	        {
		        strTmp2=" Clear sorting area card successfully\r\n";
                DisplayInfoforRecieve(strTmp2);
	        }

	        //1)Get all cards Series
            string CardIDStr, TmpStr, CardIDTmpStr;
	        string Card_PasswordStr,Card_DateStr;

	        byte Card_CardStatus=0;
	        byte Card_WeekProgram=0;

	       // int nMaxCardNum=1000;
	        //byte  CardStatus=0;
	        //Get First CardNum
            textBox26.Text.Trim();//得到卡号，卡号是8位16进制
	        if(textBox26.Text.Length!=8)
		        return;

            CardIDStr = textBox26.Text;
            CardIDTmpStr = CardIDStr;
            //ulong uCardID =0;
           // uCardID = Convert.ToUInt64(CardIDStr);
            uint uCardID = 0;

            uCardID = (uint)(Convert.ToInt32(textBox26.Text,16));

	        //////////////////////////////////////////////////////卡状态组合 下 组成一个字节
	        //最高二位是卡或卡+密码的模式
            if(nCardPassword==0)
	        {
	           Card_CardStatus = 0x00;//卡00，   CardStatus最高二位 第7，6位
	        }
	        else
	        {
	           Card_CardStatus = 0xC0;//卡+密码  CardStatus最高二位 第7，6位   1100,0000 门1门2都是卡+密码
	        }
            //是否能过门1门2的权限
            Card_CardStatus = (byte)((byte)Card_CardStatus & (nReaderRight << 4)); //第5，4位，是否能过门1门2的权限
	        //3，2位保留，最低二位是卡状态，1，0为卡状态
            if (checkBox6.Checked)
                Card_CardStatus = (byte)(Card_CardStatus & 0xf0);//最低二位为00，第3，4位保留，定为00;
	        else
                Card_CardStatus = (byte)(Card_CardStatus & 0xf2);//最低二位为02，启用了有效期
	        //////////////////////////////////////////////////////卡状态组合 上

	        //密码 2B
            Card_PasswordStr ="1234";
            textBox29.Text.Trim();
	        if(textBox29.Text.Length!=4)
		        return;
            Card_PasswordStr = textBox29.Text.Trim();
            
            //4.截止有效期(年月日 3B)  //注：如0x180915,年只最后2位，如2018只取18，去掉20
	        Card_DateStr="FFFFFF";
	        if ((checkBox6.Checked))
	        {
                textBox27.Text.Trim();
	            if(textBox27.Text.Length!=6)
		            return;
                Card_DateStr = textBox27.Text.Trim();
	        }
	        //////////////////////////////////////////////////////////周编程 1B
	        Card_WeekProgram =0x00;
            StartCardIDStr = CardIDStr;
            StartCardIDStr2="";
            StartCardIDStr2 += (String.Format("{0:X}", Card_CardStatus)).PadLeft(2, '0'); 
	        StartCardIDStr2+=Card_PasswordStr;
	        StartCardIDStr2+=Card_DateStr;

            TmpStr = (String.Format("{0:X}", Card_WeekProgram)).PadLeft(2, '0');
            StartCardIDStr2 += TmpStr;

	        uCardIDID=uCardID;
	        nTypeforDownloadCard=2;

             Thread parameterThread = new Thread(new ThreadStart(ThreadFunc));
             parameterThread.Name = "ParameterThread";
             parameterThread.IsBackground = true; 
             parameterThread.Start();  


        }


        private void button23_Click(object sender, EventArgs e)
        {
            //1)Get all cards Series
            string CardIDStr, TmpStr, CardIDTmpStr;
            string Card_PasswordStr, Card_DateStr;

            byte Card_CardStatus = 0;
            byte Card_WeekProgram = 0;

            // int nMaxCardNum=1000;
            //byte  CardStatus=0;
            //Get First CardNum
            textBox26.Text.Trim();//得到卡号，卡号是8位16进制
            if (textBox26.Text.Length != 8)
                return;

            CardIDStr = textBox26.Text;
            CardIDTmpStr = CardIDStr;
            //ulong uCardID =0;
            // uCardID = Convert.ToUInt64(CardIDStr);
            uint uCardID = 0;

            uCardID = (uint)(Convert.ToInt32(textBox26.Text, 16));

            //////////////////////////////////////////////////////卡状态组合 下 组成一个字节
            //最高二位是卡或卡+密码的模式
            if (nCardPassword == 0)
            {
                Card_CardStatus = 0x00;//卡00，   CardStatus最高二位 第7，6位
            }
            else
            {
                Card_CardStatus = 0xC0;//卡+密码  CardStatus最高二位 第7，6位   1100,0000 门1门2都是卡+密码
            }
            //是否能过门1门2的权限
            Card_CardStatus = (byte)((byte)Card_CardStatus & (nReaderRight << 4)); //第5，4位，是否能过门1门2的权限
            //3，2位保留，最低二位是卡状态，1，0为卡状态
            if (checkBox6.Checked)
                Card_CardStatus = (byte)(Card_CardStatus & 0xf0);//最低二位为00，第3，4位保留，定为00;
            else
                Card_CardStatus = (byte)(Card_CardStatus & 0xf2);//最低二位为02，启用了有效期
            //////////////////////////////////////////////////////卡状态组合 上

            //密码 2B
            Card_PasswordStr = "1234";
            textBox29.Text.Trim();
            if (textBox29.Text.Length != 4)
                return;
            Card_PasswordStr = textBox29.Text.Trim();

            //4.截止有效期(年月日 3B)  //注：如0x180915,年只最后2位，如2018只取18，去掉20
            Card_DateStr = "FFFFFF";
            if ((checkBox6.Checked))
            {
                textBox27.Text.Trim();
                if (textBox27.Text.Length != 6)
                    return;
                Card_DateStr = textBox27.Text.Trim();
            }
            //////////////////////////////////////////////////////////周编程 1B
            Card_WeekProgram = 0x00;
            StartCardIDStr = CardIDStr;
            StartCardIDStr2 = "";
            StartCardIDStr2 += (String.Format("{0:X}", Card_CardStatus)).PadLeft(2, '0');
            StartCardIDStr2 += Card_PasswordStr;
            StartCardIDStr2 += Card_DateStr;

            TmpStr = (String.Format("{0:X}", Card_WeekProgram)).PadLeft(2, '0');
            StartCardIDStr2 += TmpStr;

            uCardIDID = uCardID;
            nTypeforDownloadCard = 0;

            Thread parameterThread = new Thread(new ThreadStart(ThreadFunc));
            parameterThread.Name = "ParameterThread";
            parameterThread.IsBackground = true;
            parameterThread.Start();  
        }

        private void button22_Click(object sender, EventArgs e)
        {
            //1)Get all cards Series
            string CardIDStr;

            //Get First CardNum
            textBox26.Text.Trim();//得到卡号，卡号是8位16进制
            if (textBox26.Text.Length != 8)
                return;

            CardIDStr = textBox26.Text;

            uint uCardID = 0;

            uCardID = (uint)(Convert.ToInt32(textBox26.Text, 16));

            uCardIDID = uCardID;
            nTypeforDownloadCard = 1;

            Thread parameterThread = new Thread(new ThreadStart(ThreadFunc));
            parameterThread.Name = "ParameterThread";
            parameterThread.IsBackground = true;
            parameterThread.Start(); 


        }

        private void button27_Click(object sender, EventArgs e)
        {
            nRet = SendCommandtoDevice("4202FF02");
            if (nRet == 0)
            {
                strTmp2 = " Clear Sort Aear Card OK\r\n" ;
                DisplayInfoforRecieve(strTmp2);
            }
        }

        private void button26_Click(object sender, EventArgs e)
        {
            nRet = SendCommandtoDevice("4202FF01");
            if (nRet == 0)
            {
                strTmp2 = " Clear Temp. Aear Card OK\r\n";
                DisplayInfoforRecieve(strTmp2);
            }
        }

        private void button25_Click(object sender, EventArgs e)
        {
            nRet = SendCommandtoDevice("4202FF00");
            if (nRet == 0)
            {
                strTmp2 = " Clear All Card OK\r\n";
                DisplayInfoforRecieve(strTmp2);
            }
        }

        private static byte[] HexToByte(string hexString)//字串符转换成16进制byte[]
        {
            byte[] returnBytes = new byte[hexString.Length / 2];
            for (int i = 0; i < returnBytes.Length; i++)
                returnBytes[i] = Convert.ToByte(hexString.Substring(i * 2, 2), 16);
            return returnBytes;
        }//返回的结果就是16进制的byte[]

        [System.Runtime.InteropServices.DllImportAttribute("UnPack.dll")]
        private static extern int Unpack(byte[] wlt,byte[] bmp);

        private void button28_Click(object sender, EventArgs e)
        {
            byte[] wlt = new byte[1024];
            byte[] bmp = new byte[38862];
            //unsigned char	*bmp = new unsigned char[38862];//解码后bmp数据待存入的数组
            string strUcs2="574C66007E00320000FF851A5151513E710DD564F365D06FCCCA955A2B809CAA2212C0A4EB90DC70ECEE317E3C83A982E67F1A370A4C0F4FEB77EF39F38447E2140F3CAAA5F7C0C5A10926050D378E35BF6CDEAD81C1FEEE11AED95251515A3E9C607B71AF2F541D5B084BD2866D52CE9E45164F0C7E9AA71269A363AB9AA9CEAA4E8EE4C2A3C93C93D274916F928B85924FC7513DFC845E3FF9333DD11A7E690A22A931D606CB15286649E2C3A32DA54CECE3232B2BD943281FEFB83827C9F172FD0A6F9E9BC7FAA83749B95C634252B9E38DB80CC04737E1E6DC9FB5067B2265F610D4CA708B6E5FC8BE54A6A8D1494049BEFC50071E8FF4A53DD8C12781C5A418D298979DBEC699C601DF33B5C3FA68CDD1451858522DE2BC60B2300AF74B6B46881AB09B49627D490FC9D65E4FA29C0028C04A554037F2736F0CCAD3AE51B91272CA6E02DADB2E9E8CE9B53BD17A06F80B04B61A7274C4F2F13B1DFDF85A54DA1BD5AAE6F58305FEB00778B7D06F14D54E03EB4A782CCB67F45623ED2FE58FB64885BF27D4EF472B5F0C0332642102E669598E8B330B8C2C5221AFE5239B0C753C9B2120636E7B971A0866EEAE51A8AA2050537BD7DCB2C863BB3A09C6ED1B2F2CDB41277914EA71DC3FF5F087A2B0F1E3954C4F6B926A5D507AF6B50375D42FCDA9B6A77B7C350F864FA5F6807534D57200430C6FBFA7FFC8952AFB23C2D9432C13633DB4B61DEE58C28234F5B856E2A5ABC9068C2FB864E2830A3EA68AFBAC94BB968F08485B406B67EE8917DDA4ABB70F62D8C02770A0741E2B17148CCDA1C905DEB20472E5FFAAF41DF37CF39F26E244748361D40F09CEDF1A12F90EA6A312C961AD426F035D2B2BCC187B2AD2FB3D53ADD9DF6C25658A91787D8E4F0448D36C914F27A00A72B79E97F5D75FDBF2DB5A84863321C530AB4864630284CD249FB5D256DA8ADAD9791721074536B7BF1334BAC2928782C116E84BD5ABB0B4B205954EC33619DE5DC8F1359E43CF0EE368DFB3C43A5CA7535F46BDAA0F8E1323D869CA8C901A8E53206F1AB85FC6B1196E7E28500376F87374516C47E4B68AD68B339D2F1456B4F3D5EB116B8710EC54BC7B695FD4883210CDE2859FD65CC147AE51B61239B8641ADDE23362E3053B504DAD17BFB8BF6BD65CF6978ACE5EF7D875DFA7578D24058B2C02772FC1F41393E2321245E62B615081BF9FF0EC80FB7B8DBF355A3E09326C938293AA9CFEA2AE5140559EBA992821D784DCA082C4FC8C54904DC296DD1BE87ED5CAAA7043E713BA76BEEE6901546A4B522970011BBED049C95E330F5670610E1DCCD34D6D0BBBEE766371DE5A3E8B124F1C953E907B12D13248D416E698714675986D5A0B76A34E20BB824D12737676745A883BB168EAC31632B54AE62A500C06666C4AB1D67A63262EF307007AA9294F556BF462";
            wlt = HexToByte(strUcs2);
           // wlt =System.Text.Encoding.Default.GetBytes(strUcs2);
            int ret = Unpack(wlt, bmp);

            if (ret == 1)
            {
                string path = "test.bmp";
                //创建一个文件流
                FileStream fs = new FileStream(path, FileMode.Create);
                //将byte数组写入文件中
                fs.Write(bmp, 0, bmp.Length);
                //所有流类型都要关闭流，否则会出现内存泄露问题
                fs.Close();
            }

            //MessageBox.Show(ret.ToString());



//574C66007E00320000FF851A5151513E710DD564F365D06FCCCA955A2B809CAA2212C0A4EB90DC70ECEE317E3C83A982E67F1A370A4C0F4FEB77EF39F38447E2140F3CAAA5F7C0C5A10926050D378E35BF6CDEAD81C1FEEE11AED95251515A3E9C607B71AF2F541D5B084BD2866D52CE9E45164F0C7E9AA71269A363AB9AA9CEAA4E8EE4C2A3C93C93D274916F928B85924FC7513DFC845E3FF9333DD11A7E690A22A931D606CB15286649E2C3A32DA54CECE3232B2BD943281FEFB83827C9F172FD0A6F9E9BC7FAA83749B95C634252B9E38DB80CC04737E1E6DC9FB5067B2265F610D4CA708B6E5FC8BE54A6A8D1494049BEFC50071E8FF4A53DD8C12781C5A418D298979DBEC699C601DF33B5C3FA68CDD1451858522DE2BC60B2300AF74B6B46881AB09B49627D490FC9D65E4FA29C0028C04A554037F2736F0CCAD3AE51B91272CA6E02DADB2E9E8CE9B53BD17A06F80B04B61A7274C4F2F13B1DFDF85A54DA1BD5AAE6F58305FEB00778B7D06F14D54E03EB4A782CCB67F45623ED2FE58FB64885BF27D4EF472B5F0C0332642102E669598E8B330B8C2C5221AFE5239B0C753C9B2120636E7B971A0866EEAE51A8AA2050537BD7DCB2C863BB3A09C6ED1B2F2CDB41277914EA71DC3FF5F087A2B0F1E3954C4F6B926A5D507AF6B50375D42FCDA9B6A77B7C350F864FA5F6807534D57200430C6FBFA7FFC8952AFB23C2D9432C13633DB4B61DEE58C28234F5B856E2A5ABC9068C2FB864E2830A3EA68AFBAC94BB968F08485B406B67EE8917DDA4ABB70F62D8C02770A0741E2B17148CCDA1C905DEB20472E5FFAAF41DF37CF39F26E244748361D40F09CEDF1A12F90EA6A312C961AD426F035D2B2BCC187B2AD2FB3D53ADD9DF6C25658A91787D8E4F0448D36C914F27A00A72B79E97F5D75FDBF2DB5A84863321C530AB4864630284CD249FB5D256DA8ADAD9791721074536B7BF1334BAC2928782C116E84BD5ABB0B4B205954EC33619DE5DC8F1359E43CF0EE368DFB3C43A5CA7535F46BDAA0F8E1323D869CA8C901A8E53206F1AB85FC6B1196E7E28500376F87374516C47E4B68AD68B339D2F1456B4F3D5EB116B8710EC54BC7B695FD4883210CDE2859FD65CC147AE51B61239B8641ADDE23362E3053B504DAD17BFB8BF6BD65CF6978ACE5EF7D875DFA7578D24058B2C02772FC1F41393E2321245E62B615081BF9FF0EC80FB7B8DBF355A3E09326C938293AA9CFEA2AE5140559EBA992821D784DCA082C4FC8C54904DC296DD1BE87ED5CAAA7043E713BA76BEEE6901546A4B522970011BBED049C95E330F5670610E1DCCD34D6D0BBBEE766371DE5A3E8B124F1C953E907B12D13248D416E698714675986D5A0B76A34E20BB824D12737676745A883BB168EAC31632B54AE62A500C06666C4AB1D67A63262EF307007AA9294F556BF462

        }




    }
}
