import java.lang.*;
import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;

import java.net.Socket;
import java.net.SocketException;
import java.net.SocketTimeoutException;
import java.util.Date; 
import java.util.Map;
import java.text.SimpleDateFormat; 

class SocketServer implements Runnable
{
    Socket client;
    Object object;
    Object objectClearAllCard;
    Map<String, Object> map;
    byte[] b = new byte[1500];
    int secieveLen=0;
    byte[] DeviceMac =new byte[6];

    //命令字，具体命令字的说明请看，通讯协议和命令解析文档
    public static final int Control_InitCode		=  0x3000;
    public static final int User_Control_InitCode  	=  0x3001;
    public static final int Control_RESTCode 		=  0x3002;
    public static final int ReadControl_versionCode	=  0x3100;
    public static final int DownloadSYSTimeCode		=  0x3200;
    public static final int ReadSYSTimeCode 		=  0x3300;
    public static final int DownloadOpenDoorKeyCode	=  0x4000;
    public static final int DownloadMenaceKeyCode 	=  0x4001;
    public static final int Run_StatusCode 			=  0x4100;
    public static final int DownloadCardInfoCode 	=  0x4200;
    public static final int BatchDownloadCardInfoCode 	=  	0x4201;
    public static final int  ClearALLCardInfoCode		=	0x4202;
    public static final int  FirstBatchDownloadCardInfoCode =0x4203;
    public static final int  DownloadCardInfoQRCode	=	0x4215; 
    public static final int  ReadQRCodeCounterCode	=	0x4216; 
    public static final int  ClearQRCodeCounterCode	=	0x4217;
    public static final int  ReadloadCardInfoCode		=	0x4300;
    public static final int  BatchReadloadCardInfoCode	=	0x4301;
    public static final int  StartRealTimeCortrolCode	=	0x4400;
    public static final int  StopRealTimeCortrolCode	=	0x4401;
    public static final int  SubsystemRealTimeRecordCodeUDP=	0x4406;
    public static final int  TCPSubsystemRealTimeRecordCode=	0x4407;
    public static final int  UDPSubsystemRealTimeRecordCode=	0x4408;
    public static final int  ReadRecordCode				=	0x4500;
    public static final int  ClearALLRecordCode			=	0x4501;
    public static final int  AddReadRecordPointerCode	=	0x4502;
    public static final int  ReadRealTimeRecordCode		=	0x4503;
    public static final int  BatchReadRecordCode		=	0x4505;
    public static final int  HeartBeepCodeFromServer	=	0x4508;
    public static final int  AutoUploadRecordCode 		= 	0x4511;//记录自动上传指令
    public static final int  HeartBeepCodeFromDevice	=	0x4518;
    public static final int  ReadTCPandUDPIPPortCode	=	0x450A;
    public static final int  DownloadHolidayListCode	=	0x4600;
    public static final int  ReadHolidayListCode		=	0x4700;
    public static final int  DownloadWeekListCode		=	0x4800;
    public static final int  ReadWeekListCode			=	0x4900;
    public static final int  DownloadOpenDoorTimeCode	=	0x4A00;
    public static final int  DownloadCustomOutTimeCode	=	0x4A01;
    public static final int  DownloadCallPolicemenTimeCode=		0x4A02;
    public static final int  DownloadLockTypeCode		=	0x4A03;
    public static final int  DistanceOpenDoorCode		=	0x5000;
    public static final int  DistanceCloseDoorCode		=	0x5001;
    public static final int  ConstantOpenDoorCode		=	0x5002;
    public static final int  DistanceOpenDoorwithUserInfo=	0x5005; 
    public static final int  DownloadPortCollocateCode	=	0x5200;
    public static final int  ReadloadPortCollocateCode	=	0x5300;
    public static final int  DownloadNetParameterCode	=	0x5400;
    public static final int  ReadloadNetParameterCode	=	0x5500;
    public static final int  MACReadloadNetParameterCode=	0x5501;
    public static final int  DeviceNetParametereUpload	=	0x5502;
    public static final int  IDInforUpload				=	0x5505;
    public static final int  ICCardRealtimeUpload		=	0x5525;//IC Card Autoupdate
    public static final int  ReadNetParameterBroadcastCode= 0x5503;
    
    public static final int  QRCodeUpload				=	0x5506;    
    public static final int  BlockageDoorPopedomCode	=	0x5600;
    public static final int  UnchainDoorPopedomCode		=	0x5601;
    public static final int  ReadloadDoorPopedomCode	=	0x5602;
    public static final int  CortrolReaderIssueCardCode	=	0x5900;
    public static final int  ReadIssueCardNOCode		=	0x5901;			
    public static final int SetupDoor_Call_PolicemeCode	=	0x5E00;
    public static final int ReadDoor_Call_PolicemenCode	=	0x5E01;
    public static final int  RequestUpgradeCode			=	0xF000;
    public static final int  SendUpgradeDataCode		=	0xF001;
    public static final int  OverUpgradeCode			=	0xF002;
    public static final int  ShowLEDandOpenCarCode		=	0x5806;
    public static final int  ShowLEDandSoundCode		=	0x5803;
    public static final int BT_SetNameCode				=	0x8100;	     
    public static final int BT_SetPasswordCode			=	0x8101;
//	private static final String NET_CARD_ONECARDINFO = null;
	private static final DataOutputStream NULL = null;
    
    public String[] EventString = new String[]
            {
    		 "正常刷卡开门",	"远程开门",		"双卡开门",			"密码开门",		"胁迫码开门",
    		 "自定义输入开门",	"首卡开门",		"开门按扭开门",		"非法进入",	"非法离开",
    		 "进入刷卡","离开刷卡", "人员已经进入",	"非法时段",	"密码无效",
    		 "双卡无效",	    "紧急开门",		"未刷首卡",			"卡片非法",		"双卡刷卡",
    		 "门开超时报警",	"胁迫报警",	    "多卡组合正确",		"此卡已过期",	"互锁条件限制",
    		 "门常开",			"远程关门",		"钥匙或强制开门",		"紧急关门",		"门被紧急关闭",
    		 "门常闭",		"恢复门到常态",		"三卡刷卡",			"四卡刷卡",		"五卡刷卡",
    		 "三卡无效",	"四卡无效",			"五卡无效",			"三卡开门",		"四卡开门",
    		 "五卡开门",	"单卡确认开门",		"双卡确认开门",		"三卡确认开门",	"四卡确认开门",	
    		 "五卡确认开门","多卡重复刷卡",     "此卡已过期",		"远程确认开门","保留",
    		 "系统正常","系统满员","系统超员","保留","保留",
    		 "双开恢复正常","双闭恢复正常","手控盒双开","手控盒双闭","手控盒开门",
    		 "手控盒复位","锁舌故障","锁故障恢复正常","此卡为删除卡","旋钮或钥匙开门",
    		 "对讲请求开门","验证自动加卡","管理卡加卡开门","","",
    		 "条码正常开门","条码次数不够",		"条码已过期",		"未到生效日期","MAC不匹配",
    		 "项目编号非法","楼栋编号不匹配",	"秘钥不对",			"条码长度错误","设备已过期",
    		 "MAC地址个数异常","其它异常错误","保留","保留","保留",
    		 "保留","保留","保留","保留","保留",
    		 "保留","保留","保留","保留","保留",
    		 "保留","保留","保留","保留","保留"	    	     
    	     
            };
    
    /*******************Communication status return code Э����״̬λ��ʾ�ĺ���**********************/
    //状态值的说明
    public String[] strStateArray = {
    	     "successful",		
    	     "Command is invalid",
    	     "Invalid parameter",
    	     "before sort download,clear all cards",
    	     "Unknown command",					
    	    "have not authorized",				
    	    "Equipment troubl",	
    	    "command fail",		
    	    "command recieve fail", 
    	    "Flash is insufficient",
    	    "No record in the controller",
    	    "No Card in the controller",
    	    "Record have been read" 
    };
    //身份证民族编号对应的民族名称
    public String NationArray[]={"汉","蒙古","回","藏","维吾尔","苗","彝","壮","布依","朝鲜","满","侗","瑶","白","土家",
			"哈尼","哈萨克","傣","黎","傈僳","佤","畲","高山","拉祜","水","东乡","纳西","景颇","柯尔克孜","土",
			"达斡尔","仫佬","羌","布朗","撒拉","毛南","仡佬","锡伯","阿昌","普米","塔吉克","怒","乌孜别克","俄罗斯","鄂温克",
			"德昂","保安","裕固","京","塔塔尔","独龙","鄂伦春","赫哲","门巴","珞巴","基诺"};    
   /* 
    strStateArray[0] =  "successful";		//����ɹ�
    strStateArray[1] =  "Command is invalid";//������Ч
    strStateArray[2] =  "Invalid parameter";//��Ч����
    strStateArray[3] =  "before sort download,clear all cards";//"�����������ؿ���Ϣ������տ�����";
    strStateArray[4] =  "Unknown command";						//δ֪����
    strStateArray[5] =  "have not authorized";					//û��Ȩ��
    strStateArray[6] =  "Equipment troubl";						//�豸��
    strStateArray[7] =  "command fail";							//�������ʧ��
    strStateArray[8] =  "command recieve fail";  				//������ܲ��ɹ�  
    strStateArray[9] =  "Flash is insufficient";					//�������洢�ռ䲻��
    strStateArray[10] = "No record in the controller";			//���������޼�¼   
    strStateArray[11] = "No Card in the controller";				//���������޸ÿ���Ϣ��û��������ز���
    strStateArray[12] = "Record have been read";   				//�������ڼ�¼�Ѷ���
   */
    
  //类的构造函数
    public SocketServer(Socket client,Object object,Object objectClearAllCard,Map<String, Object> map)
    {
        this.client = client;
        this.object = object;    
        this.objectClearAllCard = objectClearAllCard;    
        this.map = map;
    }
   //字节数组转换成16进制字符串
    public static String byte2HexStr(byte[] b) 
    {  
        String hs = "";  
        String stmp = "";  	
        for (int n = 0; n < b.length; n++) 
        {  
            stmp = (Integer.toHexString(b[n] & 0XFF));  
            if (stmp.length() == 1)  
                hs = hs + "0" + stmp;  
            else  
                hs = hs + stmp;   
        }         
        return hs.toUpperCase();  
    }   
    //16�������ת���ַ�
    public static String byte2HexStrforIP(byte[] b) 
    {  
        String hs = "";  
        String stmp = "";  
        Integer stmp2 = 0; 	
        for (int n = 0; n < b.length; n++) 
        {          	
            stmp = (Integer.toHexString(b[n] & 0XFF));    
            stmp2 =Integer.parseInt(stmp,16);
            if(n!=0)
            	hs = hs + "." + stmp2.toString();
            else
            	hs = stmp2.toString();
        }                      
        return hs.toUpperCase();  
    }     
    
    /** 
16进制字符串转换成字节数组
     */  
    public static byte[] hexString2Bytes(String src) {  
        int l = src.length() / 2;  
        byte[] ret = new byte[l];  
        for (int i = 0; i < l; i++) {  
            ret[i] = (byte) Integer  
                    .valueOf(src.substring(i * 2, i * 2 + 2), 16).byteValue();  
        }  
        return ret;  
    }
	public static Integer StrToInt(String str) {
		str = str.replace("0x", "");
		int stmp1 = 0;
		int stmp2 = 0;
		stmp1 = Integer.valueOf(str.substring(0, 4), 16);
		stmp2 = Integer.valueOf(str.substring(4, 8), 16);
		int reint = (stmp1 << 16) | stmp2;
		return reint;
	}   
    //�õ�5502�豸�������
    public void GetDeviceNetParameter(byte Recieve[],int Len)
    {
    	byte pos=0;		
    	Short netPort =0;
    	
    	byte[] 	m_sNetIP 	= new byte[4];		//IP
    	byte[]   m_sNetMAC	= new byte[6];       //MAC
    	byte[]   m_sNetGate	= new byte[4];	    //Gate  
    	byte[]   m_sNetMask	= new byte[4];	    //MASK
    	byte[]   m_nNetPort	= new byte[2];      //PORT
    	byte[]   Reserve		= new byte[3];			//1102
    	byte   	m_nDoorNum;					  //Door num
    	byte[]   m_sVersion	= new byte[16];     //Version

	 	
    	if(Len>=55)
    	{
    		pos = 13;
	    	m_nDoorNum = Recieve[pos+23];
	    	System.arraycopy(Recieve,pos,m_sNetIP,0,4);
	    	System.arraycopy(Recieve,pos+4,m_sNetMAC,0,6);
	    	System.arraycopy(Recieve,pos+10,m_sNetGate,0,4);
	    	System.arraycopy(Recieve,pos+14,m_sNetMask,0,4);
	    	System.arraycopy(Recieve,pos+18,m_nNetPort,0,2);
	    	System.arraycopy(Recieve,pos+24,m_sVersion,0,16);
	    
	    	String sIP   = byte2HexStrforIP(m_sNetIP);		   		    	
	    	String sMAC  = byte2HexStr(m_sNetMAC);
	    	String sGate = byte2HexStrforIP(m_sNetGate);
	    	String sMask = byte2HexStrforIP(m_sNetMask);

	    	netPort = 0x0000;
	    	netPort = (short) ((m_nNetPort[0]<<8)|(m_nNetPort[1]));
	    	String sNetPort = netPort.toString();	
	    	String sDoornum = String.valueOf((char)m_nDoorNum);
	    	    		    	
	    	System.out.println("Device Net Parameter:\r\nIP:"+sIP+"\r\nMAC:"+sMAC+
	    			"\r\nGAte:"+sGate+"\r\nMask:"+sMask+"\r\nPort:"+sNetPort+
	    			"\r\nDoorNum:"+sDoornum+"\r\nVersion:"+
	    			new String(m_sVersion));   	
	    	
    	}
    	
    }
    //�õ���ά�����5506
    public void GetQRCodeData(byte Recieve[],int Len)
    {
    	//byte[] SendCommand =new byte[10];
    	
    	byte pos=0;		
    	byte readerNo =0;
 
    	int nDataLength = Len-15;    	
    	byte[] QRData = new byte[nDataLength-1];
    	
    	pos = 14;
    	readerNo = Recieve[13];
    	System.arraycopy(Recieve,pos,QRData,0,nDataLength-1);
    	
    	String QrDataStr = new String(QRData);   	
    	String sReader= (Integer.toHexString(readerNo & 0XFF)); 
    	
	    Date nowTime=new Date(); 
	    SimpleDateFormat time=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss"); 
	    
    	System.out.println(time.format(nowTime)+" QRcode data:\r\nReader:"+sReader+"\r\nQR Date:"+QrDataStr+"\r\n"); 
    	

    		
    } 
    public static byte[] fromUCS2(byte[] ucs2Array) {   
        ByteArrayOutputStream baos = new ByteArrayOutputStream();   
        for (int i = 0; i < ucs2Array.length; i++) {   
            byte ch = ucs2Array[i];   
            if (ch <= 0x007F) {   
                baos.write(ch);   
            } else if (ch <= 0x07FF) {   
                int ub1 = ch >> 8;   
                int ub2 = ch & 0xFF;   
                int b1 = 0xC0 + (ub1 << 2) +  (ub2 >> 6);  //0xC0B_11000000 + (ub1 << 2) +  (ub2 >> 6);   
                int b2 = 0x80 + (ub2 &0x3F);// B_00111111);   //B_10000000
                baos.write(b1);   
                baos.write(b2);   
            } else {   
                int ub1 = ch >> 8;   
                int ub2 = ch & 0xFF;   
                int b1 = 0xE0 + (ub1 >> 4);   
                int b2 = 0x80 + ((ub1 & 0x0F) << 2) + (ub2 >> 6);   
                int b3 = 0x80 + (ub2 & 0x3F);   
                baos.write(b1);   
                baos.write(b2);   
                baos.write(b3);   
            }   
        }   
        return baos.toByteArray();   
    }
    
    //�õ���ά�����5505 //获取身份证信息
    public void GetIDInfoCodeData(byte Recieve[],int Len) throws UnsupportedEncodingException
    {
    	//byte[] SendCommand =new byte[10];
    	
    	 int pos=0;		
    	 byte readerNo =0;
    	
    	 byte[]   IDCard_Name 		= new byte[30];		//Name
		 byte[]	  IDCard_Sex		= new byte[2];		//1 Male 2 Female 3 other ==1 男，2 女，3 其它
		 byte[]   IDCard_National	= new byte[4];		//National ==民族 0-55
		 byte[]   IDCard_Birthday 	= new byte[16];		//birthday ==生日 19801020
		 byte[]   IDCard_Address 	= new byte[70];     //address ==住址 
		 byte[]   IDCard_IDNumber 	= new byte[36];     //IDNumber ==身份证号码
		 byte[]   IDCard_Issuing 	= new byte[30];     //Issuing authority ==签发机关
		 byte[]   IDCard_Validity_StartDate = new byte[16];    //Validity_Start ==有效开始日期
		 byte[]   IDCard_Validity_EndDate 	= new byte[16];      //Validity_Start ==有效结束日期   	

    	int nDataLength = Len-16;    
    	if(nDataLength<256)//长度有问题
    		return;
    	
    	byte[] IDData = new byte[nDataLength];
    	
    	pos = 14;
    	readerNo = Recieve[13];//读头号；一个设备可带多个身份证阅读器，区分是哪个阅读器读上来的
    	System.arraycopy(Recieve,pos,IDData,0,nDataLength);
    
    	pos=0;
    	System.arraycopy(IDData,pos,IDCard_Name,0,IDCard_Name.length);
       	
    	pos = IDCard_Name.length;
    	System.arraycopy(IDData,pos,IDCard_Sex,0,IDCard_Sex.length);
    	pos +=IDCard_Sex.length;
    	
    	System.arraycopy(IDData,pos,IDCard_National,0,IDCard_National.length);
    	pos +=IDCard_National.length;
    	
    	System.arraycopy(IDData,pos,IDCard_Birthday,0,IDCard_Birthday.length);
    	pos +=IDCard_Birthday.length;
    	
    	System.arraycopy(IDData,pos,IDCard_Address,0,IDCard_Address.length);
    	pos +=IDCard_Address.length;
    	
    	System.arraycopy(IDData,pos,IDCard_IDNumber,0,IDCard_IDNumber.length);
    	pos +=IDCard_IDNumber.length;
    	
    	System.arraycopy(IDData,pos,IDCard_Issuing,0,IDCard_Issuing.length);
    	pos +=IDCard_Issuing.length;
    	
    	System.arraycopy(IDData,pos,IDCard_Validity_StartDate,0,IDCard_Validity_StartDate.length);
    	pos +=IDCard_Validity_StartDate.length;   	   	
    	
    	System.arraycopy(IDData,pos,IDCard_Validity_EndDate,0,IDCard_Validity_EndDate.length);
    	pos +=IDCard_Validity_EndDate.length;   
    	//显示身份证信息
    	String sReader= (Integer.toHexString(readerNo & 0XFF)); 
    	
	    Date nowTime=new Date(); 
	    SimpleDateFormat time=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
    	System.out.println(time.format(nowTime)+"身份证信息\r\nReader:"+sReader); 
    	
    	String reValue = new String(IDCard_Name, "UTF-16LE");    	
    	System.out.println(reValue.trim());
    	
    	reValue = new String(IDCard_Sex, "UTF-16LE");    	
    	
		if(reValue.equals("1"))
			reValue="男";
		else
			reValue="女";
				
    	System.out.println(reValue.trim());    	
    	reValue = new String(IDCard_National, "UTF-16LE");    	
    	int stmp = Integer.valueOf(reValue, 10);
    	if((stmp<=55)&&(stmp>=1))
    		reValue = NationArray[stmp-1];    	
    	System.out.println(reValue.trim());    	

    	reValue = new String(IDCard_Birthday, "UTF-16LE");    	
    	System.out.println(reValue.trim());
    	
    	reValue = new String(IDCard_Address, "UTF-16LE");    	
    	System.out.println(reValue.trim());
    	
    	reValue = new String(IDCard_IDNumber, "UTF-16LE");    	
    	System.out.println(reValue.trim());
    	
    	reValue = new String(IDCard_Issuing, "UTF-16LE");    	
    	System.out.println(reValue.trim());
    	
    	reValue = new String(IDCard_Validity_StartDate, "UTF-16LE");    	
    	System.out.println(reValue.trim());
    	
    	reValue = new String(IDCard_Validity_EndDate, "UTF-16LE");    	
    	System.out.println(reValue.trim());    	
    	
    }      
    public static void SendCommandtoDevice(DataOutputStream outtoclient,byte command[],int len) throws IOException
    {
 	   // 02 00 0B FF FF FF FF FF FF 11 45 08 00 FF 03
    	int senddatalen = 0;
    	byte[]  SendBuffer = new byte[1500];
    	
    	SendBuffer[0] = 0x02;
    	
    	SendBuffer[0] =0x02;
    	
    	SendBuffer[3] = (byte)0xFF;
    	SendBuffer[4] = (byte)0xFF;
    	SendBuffer[5] = (byte)0xFF;
    	SendBuffer[6] = (byte)0xFF;
    	SendBuffer[7] = (byte)0xFF;
    	SendBuffer[8] = (byte)0xFF;    	
    	SendBuffer[9] = (byte)0x11;
    	
    	System.arraycopy(command,0,SendBuffer,10,len);
    	
    	senddatalen = len + 8;    	
    	SendBuffer [1] = (byte) ((senddatalen >>8) & 0x00ff);
	    SendBuffer [2] = (byte) (senddatalen & 0x00ff);
	    
	    senddatalen = senddatalen + 4;
	    SendBuffer [senddatalen-2] = (byte)0xFF;
	    SendBuffer [senddatalen-1] = (byte)0x03;
	    
	    outtoclient.write(SendBuffer, 0, senddatalen);
	    
	    byte[] SendDataTmp = new byte[senddatalen];	    
	    System.arraycopy(SendBuffer,0,SendDataTmp,0,senddatalen);
	    String SendDataStr = byte2HexStr(SendDataTmp);
	   
	    
	    Date nowTime=new Date(); 
	    SimpleDateFormat time=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss"); 
	   // System.out.println(time.format(nowTime));
	    
	    System.out.println(time.format(nowTime)+" Send command:"+SendDataStr+"\r\n");
	    
		
    }     
    
    public byte GetReturnCommand(byte Recieve[],int Len)
    {
    	String  sReturnStr,stmp1,stmp2;    	
    	byte isOK =Recieve[12];   
   	
    	stmp1 = (Integer.toHexString(Recieve[10] & 0XFF));
    	stmp2 = (Integer.toHexString(Recieve[11] & 0XFF));
    	
	    Date nowTime=new Date(); 
	    SimpleDateFormat time=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss"); 
	    //System.out.println(time.format(nowTime));
	    
    	if((isOK > 0)&&(isOK<13))//状态值，可查看命令解析文档，了解返回状态值的说明
    	{
    		sReturnStr = strStateArray[isOK];    
    		System.out.println(time.format(nowTime) + " return error:"+sReturnStr+"\r\n");
    		return 0;
    	}
    	else
    	{
    		sReturnStr = strStateArray[0];    
    		System.out.println(time.format(nowTime) + " recieve "+stmp1+stmp2+" is "+sReturnStr+"\r\n");
    		return 1;		
    		
    	}
     		
    }  
    public static void NET_CARD_ClearAllCard(DataOutputStream outtoclient) throws IOException
    {
    	byte[]  SendCommand = new byte[10];
		SendCommand[0] = (byte)0x42;
		SendCommand[1] = (byte)0x02;
		SendCommand[2] = (byte)0x00;							
		SendCommandtoDevice(outtoclient,SendCommand,3);  			
    }
    //download single card to device
    public void NET_CARD_DownOneCardInfo(DataOutputStream outtoclient) throws IOException
    {

  	    byte[]  CardIdInfo = new byte[40];   
  	    byte[]  CardId = new byte[10]; 
  	    
  		//String subCardIdStr;    	
  		
  		String cardIdStr  	=  new String("077DA36D"); //���ֽڿ���
  	    byte nPos=0;	

  	    CardIdInfo[0] = (byte)0x42;
  	    CardIdInfo[1] = (byte)0x00;
  	    CardIdInfo[2] = (byte)0xFF;
  		
  	    nPos =3;
  	    
  	    CardId = hexString2Bytes(cardIdStr);
  	    
  	    System.arraycopy(CardId,0,CardIdInfo,3,4);
  	   		
  		nPos +=4;		
  		CardIdInfo[nPos] = 0x00;
  		nPos +=1;
  		nPos +=8;
  		CardIdInfo[nPos++] = 0x17; //��Ч�� 2017��10��19��ǰ��Ч����19�գ���2016��10��20�պ���Ч
  		CardIdInfo[nPos++] = 0x10;
  		CardIdInfo[nPos++] = 0x18;
  		
  		nPos = 3+23;
  		CardIdInfo[nPos++] = 0x02; //��״̬ 00���02��Ч�ڿ���03ɾ��
  		CardIdInfo[nPos++] = (byte)0xf0;//�ܿ���Щ�� 0xf0�ܿ���1-��4  0xFE�ܿ���1
  				
  		SendCommandtoDevice(outtoclient,CardIdInfo,33+3);
  		    
    }  
    
    public void GetICCardForRealUpload(byte Recieve[],int Len)
    {
  	    byte[]  CardId = new byte[4]; 
  
    	Integer  readerNo= (int)Recieve[13];
    	System.arraycopy(Recieve,14,CardId,0,4);    	
    	String SendDataStr = byte2HexStr(CardId);	
	    Date nowTime=new Date(); 
	    SimpleDateFormat time=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss"); 	    
    	System.out.println(time.format(nowTime)+" Reader:"+readerNo.toString()+" IC Series:"+SendDataStr+"\r\n"); 
        		
    }  
    public  void GetHistoryRecord(byte[] Recieve, int Len)
    {
    	Integer i=0;
        byte pos = 0;;
        byte RecordCount = 0;//记录个数
        String ReaderString,StateString;
        byte[] ByteDeviceMAC = new byte[6];
	    //int nDataLength = Len - 12;    	// QR数据长度为总长度-12

        pos = 14;
        RecordCount = Recieve[13];

        byte[] RDCardID   = new byte[4];
        byte[] RDTime     = new byte[6];
        byte RDEventID = 0;

    	System.arraycopy(Recieve,3,ByteDeviceMAC,0,6);
    	String StringByteDeviceMAC = byte2HexStr(ByteDeviceMAC);  
    	System.out.println("/////////////DeviceMAC:"+StringByteDeviceMAC); 

    	    	
        for (i = 0; i < RecordCount;i++ )
        {
            //记录一共17个字节，4卡号+6时间+1事件号+5保留位(填充的MAC地址后五字节）+读头号（最低二位值）
        	System.arraycopy(Recieve,pos+i*17, RDCardID,0,4);//得到卡号（卡号为00000000，表示远程开门或报警等事件）
        	System.arraycopy(Recieve,pos+i*17+4, RDTime,0,6);//得到时间（17 08 10 18 25 38）
            RDEventID  = Recieve[pos+i*17+10];//得到事件号
            if((RDEventID<100)&&(RDEventID>=0))
            	StateString = EventString[RDEventID];//得到事件名称
            else
            	StateString="异常事件";
            ReaderString= (Integer.toHexString(Recieve[pos + i * 17 + 16] & 0x03)); 
            //ReaderString = String.format("{0:D}", Recieve[pos + i * 17 + 16] & 0x03);//读头号是记录最后一个字节的最后二位

            String TimeStr = byte2HexStr(RDTime);
            String CardIDStr = byte2HexStr(RDCardID);      
            System.out.println("记录上传ID:"+i.toString()+" CardID:"+CardIDStr+" ReaderNo:"+ReaderString+" EventName:"+StateString+"Time:"+TimeStr);        
        }
         
    }
//02 00 1A 00 81 39 22 33 10 11 41 00 00 
//00 00 01 00 00 1A 00 00 04 00 00 00 00 18 E6 12 03     
    public void GetDeviceStatus(byte Recieve[],int Len)
    {  
		byte  DoorState  = Recieve[13];
		byte  ButtonState= Recieve[14];
		byte  InPutState = Recieve[15];
		
		byte[]  EachDoorState = new byte[4]; 
		byte[]  EachButtonState = new byte[4];
		byte[]  EachInPutState = new byte[4];
		String EachDoorStateStr="",EachButtonStateStr="",EachInPutStateStr="";
		String StrTmp="";
		for(int k=0;k<4;k++)
		{
			EachDoorState[k]	=(byte) ((DoorState>>k)&0x01);
			EachButtonState[k]	=(byte) ((ButtonState>>k)&0x01);
			EachInPutState[k]	=(byte) ((InPutState>>k)&0x01);		
			
			StrTmp = (Integer.toHexString(k+1));  			
			if(EachDoorState[k]==0x01)
			{
				EachDoorStateStr +=StrTmp+" Open ";				
			}
			else
			{
				EachDoorStateStr +=StrTmp+" Close ";					
			}
			if(EachButtonState[k]==0x01)
			{
				EachButtonStateStr +=StrTmp+" Open ";				
			}
			else
			{
				EachButtonStateStr +=StrTmp+" Close ";					
			}	
			if(EachInPutState[k]==0x01)
			{
				EachInPutStateStr +=StrTmp+" Open ";				
			}
			else
			{
				EachInPutStateStr +=StrTmp+" Close ";					
			}				
		}
		//历史记录数量 
		int nPos=16;
		int HistoryEventConut=0;
		HistoryEventConut = Recieve[nPos];
		HistoryEventConut = (HistoryEventConut<<8) | Recieve[nPos+1];
		HistoryEventConut = (HistoryEventConut<<8) | Recieve[nPos+2];
		
		//历史记录数量 
		nPos =19;
		int RealEventConut=0;
		RealEventConut = Recieve[nPos];
		RealEventConut = (RealEventConut<<8) | Recieve[nPos+1];
		RealEventConut = (RealEventConut<<8) | Recieve[nPos+2];
		
		//设备内临时卡区卡数量
		nPos =22;
		int TempCards=0;
		TempCards = Recieve[nPos];
		TempCards = (TempCards<<8) | Recieve[nPos+1];
		TempCards = (TempCards<<8) | Recieve[nPos+2];
	
		//设备内排序卡区卡数量
		nPos =25;
		int SortCards=0;
		SortCards = Recieve[nPos];
		SortCards = (SortCards<<8) | Recieve[nPos+1];
		SortCards = (SortCards<<8) | Recieve[nPos+2];
		
	    Date nowTime=new Date(); 
	    SimpleDateFormat time=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss"); 	    
	    System.out.println(time.format(nowTime)+" DoorState:"+EachDoorStateStr+"\r\n"); 
	    System.out.println(time.format(nowTime)+" ButtonState:"+EachButtonStateStr+"\r\n"); 
	    System.out.println(time.format(nowTime)+" InPutState:"+EachInPutStateStr+"\r\n"); 
        		
    }      
    
    public void run()
    {    	  
    //	Socket clientTest;
        DataInputStream input;
        DataOutputStream output;
        int Command_Code =0;
        byte[] SendCommand =new byte[10];
        byte[] ByteDeviceMAC =new byte[6];
        String StringByteDeviceMAC="";
        String clientAddress = client.getLocalSocketAddress() + ">";
        
        try 
        {
			client.setSoTimeout(300*1000);
		} catch (SocketException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

        try
        {
            input = new DataInputStream(client.getInputStream());
            output = new DataOutputStream(client.getOutputStream());
        
            System.out.println(clientAddress+"#login successfully##");
			
            while (true)
            {
            	try
            	{
	            	secieveLen = input.read(b);
	            	if(secieveLen == -1)
	            		break;
	            		                        	
	                if((b[0] == 0x02)&&(b[9] == 0x11)&& (secieveLen>=0x0f))
	                {	     	                		            	
						Command_Code = 0x0000;
						Command_Code = b[10];
						Command_Code<<=8;
						Command_Code |= b[11];	
						
						if(StringByteDeviceMAC.equals("")
						{
			            	System.arraycopy(b,3,ByteDeviceMAC,0,6);
			            	StringByteDeviceMAC = byte2HexStr(ByteDeviceMAC);  
			            	System.out.println("DeviceMAC:"+StringByteDeviceMAC+"\r\n"); 
			            	map.put(StringByteDeviceMAC, output);			            		            	
						}
		            	
						switch ( Command_Code )
						{
							case DeviceNetParametereUpload://5502设备在连接上TCP SERVER后，立即会发送5502指令到软件，但带WIFI功能的TCP连接没有此命令
								GetDeviceNetParameter(b,secieveLen);
								break;
							
								
							case QRCodeUpload://5506接收设备发过来的二维码命令
								GetQRCodeData(b,secieveLen);//解析接收到的二维码函数								
								/* 
								SendCommand[0] = (byte)0x50;
								SendCommand[1] = (byte)0x00;
								SendCommand[2] = (byte)0xFF;
								SendCommand[3] = (byte)0x01;
								SendCommandtoDevice(output,SendCommand,4);		
									
								//接收到二维码后，触发一下获取状态指令4100
								SendCommand[0] = (byte)0x41;
								SendCommand[1] = (byte)0x00;
								SendCommand[2] = (byte)0x00;							
								SendCommandtoDevice(output,SendCommand,3);		
								*/								
								break;
							case IDInforUpload://5505											
								GetIDInfoCodeData(b,secieveLen);
								break;	
			                case AutoUploadRecordCode://4511二维码数据指令，本指令不要再发给设备
			                    GetHistoryRecord(b, secieveLen);
			                    //收到了4511记录上传指令，返回4512确认指令(注意是4512，不是4511，4511会引起死循环通讯）
			                    SendCommand[0] = (byte)0x45;
			                    SendCommand[1] = (byte)0x12;
			                    SendCommand[2] = (byte)0x00;
			                    SendCommandtoDevice(output,SendCommand,3);
			                    break;								
							case HeartBeepCodeFromServer://4508 软件发的4508指令，设备返回4508应答
								break;									
							case HeartBeepCodeFromDevice://4518  接收到的设备发过来的心跳命令，接收到心跳命令后，软件发4508指令响应，
								GetReturnCommand(b,secieveLen);
								SendCommand[0] = (byte)0x45;
								SendCommand[1] = (byte)0x08;
								SendCommand[2] = (byte)0x00;							
								SendCommandtoDevice(output,SendCommand,3);
								//NET_CARD_DownBatchSortedCardInfo(output);
								//NET_CARD_DownOneCardInfo(output);
								break;	
							case DistanceOpenDoorCode://接收到远程开门的返回后，		
								break;	
							case Run_StatusCode://获取设备状态 
								GetDeviceStatus(b,secieveLen);								
								break;									
								
							case ICCardRealtimeUpload:
								GetICCardForRealUpload(b,secieveLen);
								break;
							case ClearALLCardInfoCode://0x4202 //清除卡的返回
					  			synchronized(objectClearAllCard){
					  				objectClearAllCard.notifyAll();	  				    					  				
					  			}							
								break;									
									
							case FirstBatchDownloadCardInfoCode://是批量下载卡返回，则将通知object信号有效	
								if((b[12]==0x00)||b[12]==0x09)//00 成功 07 记录已满 记录已满表示，不能再下载了，
								{
						  			synchronized(object){
						  				object.notifyAll();	  				    					  				
						  			}
								}								   								  
					  			break;
							default:
								break;						
						}                	  		               
	                }

            	}            	
	        	catch(SocketTimeoutException e)//read time out
	        	{  
	                e.printStackTrace();  
	                break;
	            }             	
            }
    	    if (input != null)
    	    {
	    	    try
	    	    {
	    	    	input.close();
	    	    }
	    	    catch (IOException e) 
	    	    {
	    	        e.printStackTrace();
	    	    }
    	    }
    	    if (output != null)
    	    {
	    	    try
	    	    {
	    	    	output.close();
	    	    }
	    	    catch (IOException e) 
	    	    {
	    	        e.printStackTrace();
	    	    }    	    	
    	    }           
        } 
        catch (IOException e)
        {
            e.printStackTrace();
        }
    	finally
    	{    		
    		if(client != null)
    		{
	    	    try 
	    		{
	    	    	///map.remove 需要考虑多线程并发操作，可能会引起多线程并发操作异常
	    	    	map.remove(StringByteDeviceMAC);	//去掉MAP中的这个MAC对应的 DataOutputStream output
	    	    	client.close();
	    	    } 
	    		catch (IOException e1) 
	    		{
	    	        e1.printStackTrace();
	    	    }
    		}
    	}            
    }
   
    
    
    
}


