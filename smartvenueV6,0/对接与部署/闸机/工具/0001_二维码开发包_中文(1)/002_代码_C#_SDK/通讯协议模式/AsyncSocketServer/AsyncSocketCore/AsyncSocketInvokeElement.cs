using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;
using System.Threading;

using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Net;
using System.IO;

namespace AsyncSocketServer
{
    //异步Socket调用对象，所有的协议处理都从本类继承
    public class AsyncSocketInvokeElement
    {

        public const int Control_InitCode = 0x3000;
        public const int User_Control_InitCode = 0x3001;
        public const int Control_RESTCode = 0x3002;
        public const int ReadControl_versionCode = 0x3100;
        public const int DownloadSYSTimeCode = 0x3200;
        public const int ReadSYSTimeCode = 0x3300;
        public const int DownloadOpenDoorKeyCode = 0x4000;
        public const int DownloadMenaceKeyCode = 0x4001;
        public const int Run_StatusCode = 0x4100;
        public const int DownloadCardInfoCode = 0x4200;
        public const int BatchDownloadCardInfoCode = 0x4201;
        public const int ClearALLCardInfoCode = 0x4202;
        public const int FirstBatchDownloadCardInfoCode = 0x4203;
        public const int DownloadCardInfoQRCode = 0x4215; //下载条码数据99字节
        public const int ReadQRCodeCounterCode = 0x4216; //读取二维码卡数量
        public const int ClearQRCodeCounterCode = 0x4217; //清除二维码
        public const int ReadloadCardInfoCode = 0x4300;
        public const int BatchReadloadCardInfoCode = 0x4301;
        public const int StartRealTimeCortrolCode = 0x4400;//开始记录实时监控，开实时监控后记录才会向TCP或UDP发送
        public const int StopRealTimeCortrolCode = 0x4401;//停止记录实时监控
        public const int SubsystemRealTimeRecordCodeUDP = 0x4406;//设置UDP服务器IP和端口
        public const int TCPSubsystemRealTimeRecordCode = 0x4407;//设置TCP服务器IP和端口
        public const int UDPSubsystemRealTimeRecordCode = 0x4408;//记录上传UDP服务器IP和端口
        public const int ReadRecordCode = 0x4500;
        public const int ClearALLRecordCode = 0x4501;
        public const int AddReadRecordPointerCode = 0x4502;
        public const int ReadRealTimeRecordCode = 0x4503;
        public const int BatchReadRecordCode = 0x4505;
        public const int HeartBeepCodeFromServer = 0x4508;//心跳代码 服务器向设备发心跳指令
        public const int AutoUploadRecordCode = 0x4511;//记录自动上传指令20170810增加
        public const int HeartBeepCodeFromDevice = 0x4518;//心跳代码 设备向服务器心跳指令
        public const int ReadTCPandUDPIPPortCode = 0x450A;//获取上传服务器TCPIP与端口UDPIP与端口
        public const int DownloadHolidayListCode = 0x4600;
        public const int ReadHolidayListCode = 0x4700;
        public const int DownloadWeekListCode = 0x4800;
        public const int ReadWeekListCode = 0x4900;
        public const int DownloadOpenDoorTimeCode = 0x4A00;
        public const int DownloadCustomOutTimeCode = 0x4A01;
        public const int DownloadCallPolicemenTimeCode = 0x4A02;
        public const int DownloadLockTypeCode = 0x4A03;
        public const int DistanceOpenDoorCode = 0x5000;//远程开门
        public const int DistanceCloseDoorCode = 0x5001;//远程关门
        public const int ConstantOpenDoorCode = 0x5002;//门常开
        public const int DistanceOpenDoorwithUserInfo = 0x5005; //远程开门+用户数据
        public const int DownloadPortCollocateCode = 0x5200;
        public const int ReadloadPortCollocateCode = 0x5300;
        public const int DownloadNetParameterCode = 0x5400;
        public const int ReadloadNetParameterCode = 0x5500;//读网络参数
        public const int MACReadloadNetParameterCode = 0x5501;//根据MAC读网络参数
        public const int DeviceNetParametereUpload = 0x5502;//设备在TCP连接时，主动上传设备网络参数（不能读取）
        public const int ReadNetParameterBroadcastCode = 0x5503;
        public const int QRCodeUpload = 0x5506;
        public const int IDCardCodeRealUpload = 0x5525;

        public const int BlockageDoorPopedomCode = 0x5600;
        public const int UnchainDoorPopedomCode = 0x5601;
        public const int ReadloadDoorPopedomCode = 0x5602;
        public const int CortrolReaderIssueCardCode = 0x5900;
        public const int ReadIssueCardNOCode = 0x5901;
        public const int SetupDoor_Call_PolicemeCode = 0x5E00;
        public const int ReadDoor_Call_PolicemenCode = 0x5E01;
        public const int RequestUpgradeCode = 0xF000;//开始升级指令
        public const int SendUpgradeDataCode = 0xF001;//发升级数据包指令
        public const int OverUpgradeCode = 0xF002;//升级结束指令
        public const int ShowLEDandOpenCarCode = 0x5806;//语音+开门指令
        public const int ShowLEDandSoundCode = 0x5803;//发语音指令 
        public const int BT_SetNameCode = 0x8100;	 //蓝牙名称的设置    
        public const int BT_SetPasswordCode = 0x8101;//蓝牙密码的设置   

        public string[] m_sCommandState = new string[15]
    {
        "命令成功",
        "命令无效",
        "参数无效",
        "现在不能排序下载卡信息，请清空卡后重试",
        "未知命令",
        "没有权限",
        "设备损坏",
        "命令操作失败",
        "命令接受不成功",
        "控制器存储空间不足",
        "控制器内无记录",
        "控制器内无该卡信息或没有启动相关操作",
        "控制器内记录已读完",
        "",
        ""
    };

        public string[] EventString = new string[]
        {
	     "刷卡开门",		"远程开门",		"双卡开门",			"密码开门",		"胁迫码开门",
	     "出读头恢复正常",	"首卡开门",		"开门按扭开门",		"非法进入",		"非法离开",
	     "进入刷卡",		"离开刷卡",		"人员已经进入",		"人员已经离开",	"密码无效",
	     "双卡无效",	    "紧急开门",		"未刷首卡",			"卡片非法",		"双卡刷卡",
	     "门开超时报警",	"胁迫报警",	    "多卡组合正确",		"此卡已过期",	"互锁条件限制",
	     "门常开",			"远程关门",		"门强制打开",		"紧急关门",		"门被紧急关闭",
	     "门常闭",			"恢复门到常态",	"三卡刷卡",			"四卡刷卡",		"五卡刷卡",
	     "三卡无效",		"四卡无效",		"五卡无效",			"三卡开门",		"四卡开门",
	     "五卡开门",		"单卡确认开门",	"双卡确认开门",		"三卡确认开门",	"四卡确认开门",	
	     "五卡确认开门",	"多卡重复刷卡", "此卡已过期",		"远程确认开门",	"保留",
	     "系统正常",		"系统满员",		"系统超员",			"保留",			"保留",
	     "红外1感应",		"红外2感应",	"红外3感应",		"红外4感应",	"红外5感应",
	     "条码刷卡",		"身份证刷卡",	"无卡进入",			"无卡离开",     "人员进出",
	     "请求对讲",		"次数不够",	"重复进入",			"重复外出",		"未到生效日期",

	     "条码正常开门","条码次数不够",		"条码已过期",		"未到生效日期","MAC不匹配",
	     "项目编号非法","楼栋编号不匹配",	"秘钥不对",			"条码长度错误","设备已过期",

	     "MAC地址个数异常","其它异常错误","保留","保留","保留",
	     "保留","保留","保留","保留","保留",
	     "保留","保留","保留","保留","保留",
	     "保留","保留","保留","保留","保留"
        };

        protected AsyncSocketServer m_asyncSocketServer;
        protected AsyncSocketUserToken m_asyncSocketUserToken;
        public AsyncSocketUserToken AsyncSocketUserToken { get { return m_asyncSocketUserToken; } }

        private bool m_netByteOrder;
        public bool NetByteOrder { get { return m_netByteOrder; } set { m_netByteOrder = value; } } //长度是否使用网络字节顺序

        protected bool m_sendAsync; //标识是否有发送异步事件

        public byte[] m_sDeviceMac = new byte[6];
        public AsyncSocketInvokeElement(AsyncSocketServer asyncSocketServer, AsyncSocketUserToken asyncSocketUserToken)
        {
            m_asyncSocketServer = asyncSocketServer;
            m_asyncSocketUserToken = asyncSocketUserToken;

            m_netByteOrder = false;
            m_sendAsync = false;

        }

        public virtual void Close()
        { 
        }
        public static String byte2HexStr(byte[] b)
        {
            String hs = "";
            for (int n = 0; n < b.Length; n++)
            {
                hs = hs + b[n].ToString("X2");
            }
            return hs;
        } 
        //16进制数据转成字符串
        public static String byte2HexStrforIP(byte[] b)
        {
            String hs = "";
            for (int n = 0; n < b.Length; n++)
            {
                if (n != 0)
                    hs = hs + "." + b[n].ToString("D1");
                else
                    hs = b[n].ToString("D1");
            }
            return hs;
        } 
        //普通命令的解析，以4518心跳信息为例子解析如下
        public bool GetReturnCommand(byte []Recieve,int count)
        {
            String sReturnStr,CommandStr;

            //命令字是在协议的第10，11位
            CommandStr = string.Format("{0:X}{1:X}", Recieve[10], Recieve[11]);
  	      //状态位，在命令的12位
    	    byte isOK =Recieve[12];   
    	    if((isOK > 0)&&(isOK<13))//不是成功状态位，表示发送的指令有异常返回
    	    {
                sReturnStr = m_sCommandState[isOK];
                Program.Logger.InfoFormat("Command:{0},State:{1} \r\n", CommandStr,sReturnStr);
    		    return false;
    	    }
    	    else
    	    {
                sReturnStr = m_sCommandState[0];
                Program.Logger.InfoFormat("Command:{0},State:{1} \r\n", CommandStr, sReturnStr);
    		    return true;		
    	    }
        }

        public void GetDeviceNetParameter(byte[] Recieve, int count)
        {
	        byte pos=0;
            byte m_nDoorNum = 0;
    	    short netPort =0;
            byte[] m_sNetIP   = new byte[4];
            byte[] m_sNetMAC  = new byte[6];
            byte[] m_sNetGate = new byte[4];
            byte[] m_sNetMask = new byte[4];
            byte[] m_nNetPort = new byte[2];
            byte[] m_sVersion = new byte[16];
	 	
    	    if(count>=55)
    	    {
    		    pos = 13;
	    	    m_nDoorNum = Recieve[pos+23];
	    	    Array.Copy(Recieve,pos,     m_sNetIP,0,4);
	    	    Array.Copy(Recieve,pos+4,   m_sNetMAC,0,6);
	    	    Array.Copy(Recieve,pos+10,  m_sNetGate,0,4);
	    	    Array.Copy(Recieve,pos+14,  m_sNetMask,0,4);
	    	    Array.Copy(Recieve,pos+18,  m_nNetPort,0,2);
	    	    Array.Copy(Recieve,pos+24,  m_sVersion,0,16);
	       
	    	    String sIP   = byte2HexStrforIP(m_sNetIP);
                String sMAC  = byte2HexStr(m_sNetMAC);
	    	    String sGate = byte2HexStrforIP(m_sNetGate);
	    	    String sMask = byte2HexStrforIP(m_sNetMask);

	    	    netPort = 0x0000;
	    	    netPort = (short) ((m_nNetPort[0]<<8)|(m_nNetPort[1]));
	    	    String sNetPort = netPort.ToString();
                String sDoornum = (m_nDoorNum - 0x30).ToString();//读头是字符'2'，ASCII值为 0x32
                String sVersion = System.Text.Encoding.Default.GetString (m_sVersion);
	    	    		    	
                Program.Logger.InfoFormat("Device Net Parameter:\r\nIP:{0}\r\nMAC:{1}\r\nGAte:{2}\r\nMask:{3}\r\nPort:{4}\r\nDoorNum:{5}\r\nVersion:{6}",
                sIP,sMAC,sGate,sMask,sNetPort,sDoornum,sVersion);
    	    }
        }
    //获取IC卡刷卡的实时记录
      public  void IDCardRealUpload(byte[] Recieve, int count)
        {
            byte pos = 0;
            string  ReaderString,StateString,CardIDStr;
            byte[] RDCardID   = new byte[4];
            byte RDEventID = 0;         	
	 //02 00 10 00 81 39 92 09 92 11 55 25 00 00 12 45 8B 5E 42 03
            pos = 12;
            RDEventID  = Recieve[pos];//返回的状态位，为IC卡刷卡的事件号
            StateString = EventString[RDEventID];//得到事件名称
            ReaderString =  string.Format("{0:D}", Recieve[pos+1] );//读头号
            Array.Copy(Recieve,pos+2, RDCardID,0,4);
            CardIDStr = byte2HexStr(RDCardID);//得到卡号
            Program.Logger.InfoFormat("IC卡刷卡：CardID:{0}ReaderNo: {1} EventName:{2} \r\n", CardIDStr,ReaderString, StateString);                

             
        }
        //获取历史记录数据
        public  void GetHistoryRecord(byte[] Recieve, int count)
        {
            byte pos = 0,i=0;
            byte RecordCount = 0;//记录个数
            byte[] SendCommand = new byte[10];	
            string ReaderString,StateString;
    	    int nDataLength = count - 12;    	// QR数据长度为总长度-12
    	    byte[] QRData = new byte[nDataLength];

            pos = 14;
            RecordCount = Recieve[13];

            byte[] RDCardID   = new byte[4];
            byte[] RDTime     = new byte[6];
            byte RDEventID = 0;


            for (i = 0; i < RecordCount;i++ )
            {
                //记录一共17个字节，4卡号+6时间+1事件号+5保留位(填充的MAC地址后五字节）+读头号（最低二位值）
                Array.Copy(Recieve,pos+i*17, RDCardID,0,4);//得到卡号（卡号为00000000，表示远程开门或报警等事件）
                Array.Copy(Recieve,pos+i*17+4, RDTime,0,6);//得到时间（17 08 10 18 25 38）
                RDEventID  = Recieve[pos+i*17+10];//得到事件号
                StateString = EventString[RDEventID];//得到事件名称
                ReaderString = string.Format("{0:D}", Recieve[pos + i * 17 + 16] & 0x03);//读头号是记录最后一个字节的最后二位

                String TimeStr = byte2HexStr(RDTime);
                String CardIDStr = byte2HexStr(RDCardID);
                Program.Logger.InfoFormat("ID:{0} CardID:｛1｝ ReaderNo: {2} EventName:{3} DateTime:{4}\r\n", i.ToString(),CardIDStr,ReaderString, StateString, TimeStr);                
            }
             
        }
        //获取二维码数据
        public  void GetQRCodeData(byte[] Recieve, int count)
        {
            byte pos = 0;
            byte QRState = 0;
            byte[] SendCommand = new byte[10];	
            string  QRString,ReaderString,StateString;
    	    int nDataLength = count - 12;    	// QR数据长度为总长度-12
    	    byte[] QRData = new byte[nDataLength];
    	
    	    pos = 14;
            Array.Copy(Recieve, pos, QRData, 0, nDataLength);//从接收数据的第14位开始复制到QRData
            QRString = System.Text.Encoding.Default.GetString(QRData);//byte数组转换成字符显示

            QRState = Recieve[12];
            StateString =  EventString[QRState];
            ReaderString = string.Format("{0:D}", Recieve[13] & 0xFF );

          //  DateTime dt = DateTime.Now;
          //  string TimeStr = dt.ToString("yyyy-MM-dd HH:mm:ss");
            Program.Logger.InfoFormat("ReaderNo: {0} QRState:{1} \r\nQRData:{2}", ReaderString,StateString,QRString);
        }
        public bool SendCommandtoDevice(byte[] buffer, int offset, int count) //不是按包格式下发一个内存块，用于日志这类下发协议
        {
            bool result = true;
            int senddatalen = 0;
            byte[] SendBuffer = new byte[1500];
            if (count>1400)           
                return false;
            SendBuffer[0] = 0x02;
            SendBuffer[3] = (byte)0xFF;
            SendBuffer[4] = (byte)0xFF;
            SendBuffer[5] = (byte)0xFF;
            SendBuffer[6] = (byte)0xFF;
            SendBuffer[7] = (byte)0xFF;
            SendBuffer[8] = (byte)0xFF;
            SendBuffer[9] = (byte)0x11;
            Array.Copy(buffer, offset, SendBuffer, 10, count);

            senddatalen = count + 8;
            SendBuffer[1] = (byte)((senddatalen >> 8) & 0x00ff);
            SendBuffer[2] = (byte)(senddatalen & 0x00ff);

            senddatalen = senddatalen + 4;
            SendBuffer[senddatalen - 2] = (byte)0xFF;
            SendBuffer[senddatalen - 1] = (byte)0x03;
            if (!m_sendAsync)
            {
                m_sendAsync = true;
                result = m_asyncSocketServer.SendAsyncEvent(m_asyncSocketUserToken.ConnectSocket, m_asyncSocketUserToken.SendEventArgs,
                       SendBuffer, offset, senddatalen);
            }
            return result;
        }
        public virtual bool ProcessPacket(byte[] buffer,int count) //处理分完包后的数据，把命令和数据分开，并对命令进行解析
        {
            if (count < sizeof(int))
                return false;
            byte[] SendCommand = new byte[100];	
            if(buffer[0]==0x00)
            {
                for(int k=0;k<count-1;k++)
                {
                    buffer[k] = buffer[k + 1];
                }
            }
            //得到指令
            int Command_Code = 0;
			Command_Code = 0x0000;
			Command_Code = buffer[10];
			Command_Code<<=8;
            Command_Code |= buffer[11];


            Array.Copy(buffer, 3, m_sDeviceMac, 0, 6);

            switch (Command_Code)
            {
                case DeviceNetParametereUpload://5502设备TCP连接时得到的设备网络参数，不要再发给设备	
                    GetDeviceNetParameter(buffer, count);
                    break;
                case AutoUploadRecordCode://5506二维码数据指令，本指令不要再发给设备
                    GetHistoryRecord(buffer, count);
                    //收到了4511记录上传指令，返回4512确认指令(注意是4512，不是4511，4511会引起死循环通讯）
                    SendCommand[0] = (byte)0x45;
                    SendCommand[1] = (byte)0x12;
                    SendCommand[2] = (byte)0x00;
                    SendCommandtoDevice(SendCommand, 0,3);
                    break;
                case QRCodeUpload://5506二维码数据指令，本指令不要再发给设备
                    GetQRCodeData(buffer,count);
                    break;
                case IDCardCodeRealUpload://5525实时上传IC卡刷卡卡号
                    IDCardRealUpload(buffer, count);
                    break;
                case HeartBeepCodeFromServer://4508  服务器向设备向发送的心跳指令，不要再发给设备
                    break;
                case HeartBeepCodeFromDevice://4518  设备向服务器发送的心跳指令，要再发给设备
                   // GetReturnCommand(buffer, count);
                    GetDeviceNetParameter(buffer, count);
                    SendCommand[0] = (byte)0x45;
                    SendCommand[1] = (byte)0x08;
                    SendCommand[2] = (byte)0x00;
                    SendCommandtoDevice(SendCommand, 0,3);
                    break;
                case DistanceOpenDoorCode://0x5000 //服务器向设备发的远程开门，设备返回指令，不要再发给设备
                    GetReturnCommand(buffer, count);
                    break;

                default:
                    break;
            }
            return true;

        }


        public virtual bool SendCompleted()
        {
            m_sendAsync = false;//可以继续发包了
            return true;
        }

        //发送回调函数，用于连续下发数据
        public virtual bool SendCallback()
        {
            return true;
        }
  

    }
}