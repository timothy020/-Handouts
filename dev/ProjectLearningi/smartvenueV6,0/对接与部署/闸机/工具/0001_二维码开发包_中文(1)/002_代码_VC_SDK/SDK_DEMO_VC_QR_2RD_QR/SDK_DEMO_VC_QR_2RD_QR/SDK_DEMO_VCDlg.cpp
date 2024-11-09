// SDK_DEMO_VCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SDK_DEMO_VC.h"
#include "SDK_DEMO_VCDlg.h"
#include "DlgEditforViewIP.h"
#include "DlgEditBatchDownLoadCard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSDK_DEMO_VCDlg dialog


int CALLBACK GetRealtimeDataProcessEx(char *pData,int *DataLength,int nType,char *pReturnIP,int *ReturnIPLen,char *pReturnDevMAC,char *pIDBuffer,int *ReturnIDBufferLen,int IDReaderNo)
{
	char ReturnIP[15];
	char ReturnMAC[6];
	int  nRetDataLen;
	int  nReturnIPLen;
	unsigned char data[1200];


	int  nReturnIDBufLen;


	CString NationArray[56]={"汉","蒙古","回","藏","维吾尔","苗","彝","壮","布依","朝鲜","满","侗","瑶","白","土家",\
		"哈尼","哈萨克","傣","黎","傈僳","佤","畲","高山","拉祜","水","东乡","纳西","景颇","柯尔克孜","土",\
		"达斡尔","仫佬","羌","布朗","撒拉","毛南","仡佬","锡伯","阿昌","普米","塔吉克","怒","乌孜别克","俄罗斯","鄂温克",\
		"德昂","保安","裕固","京","塔塔尔","独龙","鄂伦春","赫哲","门巴","珞巴","基诺"};



	NET_CARD_IDCARDINFO IDCardInfo;

	nRetDataLen=*DataLength;

	if(nType==1)//二代身份证数据
	{
		if(ReturnIDBufferLen!=NULL)
			nReturnIDBufLen =*ReturnIDBufferLen;
		else
			nReturnIDBufLen =0;

		if(nReturnIDBufLen==38862)//图片已正确解码
		{
			//身份证图片信息写入文件
			CFile	 RFile;	
			CString  RFileNameStr;
			RFileNameStr="C:\\EmployeePic.BMP";
			if(RFile.Open(RFileNameStr, CFile::modeCreate | CFile::modeReadWrite))
			{
				if(pIDBuffer!=NULL)
				{
				   RFile.Write(pIDBuffer, 38862);
				}
			}
			RFile.Close();
			g_pMainDlg->ShowPicJPG(pIDBuffer, 38862);

		}
		else if(nReturnIDBufLen==1280)//身份证信息原始数据，
		{

		}

		memcpy(&IDCardInfo,pData,sizeof(NET_CARD_IDCARDINFO));
		//显示身份证的信息
		CString strTmp1,strTmpStr;

		strTmpStr=IDCardInfo.IDCard_Name;
		strTmp1+="姓名:"+ strTmpStr+"\r\n";
		if(IDCardInfo.IDCard_Sex!=0x31)
			strTmpStr="女";
		else
			strTmpStr="男";
		strTmp1+="性别:"+ strTmpStr+"\r\n";

		int nNation;
		nNation =IDCardInfo.IDCard_National-0x30;//atoi(IDCardInfo.IDCard_National);
		if((nNation>=0)&&(nNation<=55))
		{
			strTmp1+="民族:"+ NationArray[nNation]+"\r\n";
		}
		else
		{
			strTmp1+="民族:汉\r\n";
		}

		strTmpStr=IDCardInfo.IDCard_Birthday;
		strTmp1+="出生年月:"+ strTmpStr+"\r\n";

		strTmpStr=IDCardInfo.IDCard_Address;
		strTmp1+="住址:"+ strTmpStr+"\r\n";

		strTmpStr=IDCardInfo.IDCard_IDNumber;
		strTmp1+="身份证号码:"+ strTmpStr+"\r\n";

		strTmpStr=IDCardInfo.IDCard_Issuing;
		strTmp1+="签证机关:"+ strTmpStr+"\r\n";

		strTmpStr=IDCardInfo.IDCard_Validity_StartDate;
		strTmp1+="开始有效期:"+ strTmpStr+"\r\n";

		strTmpStr=IDCardInfo.IDCard_Validity_EndDate;
		strTmp1+="截止有效期:"+ strTmpStr+"\r\n";

		strTmpStr.Format("身份证读头号:%d",IDReaderNo);
		strTmp1+=strTmpStr+"\r\n";

		g_pMainDlg->DisplayInfoforRecieve(strTmp1);
	}

	else if(nType==8)//
	{
		CFile	 RFile;	
		CString  RFileNameStr;
		RFileNameStr="C:\\EmployeePic.BIN";
		if(RFile.Open(RFileNameStr, CFile::modeCreate | CFile::modeReadWrite))
		{
			if(pIDBuffer!=NULL)
			{
			   RFile.Write(pData, nRetDataLen);
			}
		}
		RFile.Close();

	}



	else if(nType==2)//二维码或条码数据
	{
		//显示条码信息或其它信息
		if(nRetDataLen<1200)
		{
			memcpy(&data[0],&pData[0],30);
			if((nRetDataLen==21)&&(data[15]==0x00)&&(data[16]==0xFF))//键盘
			{
				CString strTmp1,strTmp2;
				int nDataLength=nRetDataLen-14-2;

				CString strData,strData2;
				for(int i = 0;i<2;i++)
				{
					strData2.Format( "%02X",   (BYTE)pData[17+i]); 
					strData+=strData2;
				}
				g_pMainDlg->DisplayInfoforRecieve("键盘数据："+strData);

				strTmp2.Format("读头号:%d",pData[14]);
				g_pMainDlg->DisplayInfoforRecieve(strTmp2);


			}
			else
			{
				CString strTmp1,strTmp2;
				int nDataLength=nRetDataLen-14-2;
				memcpy(&data[0],&pData[14],nDataLength);
				data[nDataLength]='\0';
				strTmp1=data;
				strTmp2.Format("条码读头号:%d",pData[13]);
				g_pMainDlg->DisplayInfoforRecieve(strTmp2);
				g_pMainDlg->DisplayInfoforRecieve("条码数据："+strTmp1);
			}

		}

	}
	else if(nType==20)//TCP Server 连接时转发的网络参数
	{
		char sIP[30];
		int  nIPLen,nDevicePort;
		NET_CARD_DEVICENETPARA  NetParameter;
		CString  strTmp1,strTmp2;
		CString  m_sIP,m_sMAC,m_sGate,m_sMask,m_sPort,m_sVersion,m_sDoorNum;

		int		nItem=0;
		BOOL	m_bFind=FALSE;

		if(ReturnIDBufferLen!=NULL)
			nReturnIDBufLen =*ReturnIDBufferLen;

		nIPLen =*ReturnIPLen;
		memset(&NetParameter,0,sizeof(NET_CARD_DEVICENETPARA));

		if(nRetDataLen!=sizeof(NET_CARD_DEVICENETPARA))
		{
			g_pMainDlg->DisplayInfoforRecieve("返回网络参数长度不对");
		}
		else
		{
			if(pData!=NULL)
			{
				memcpy(&NetParameter,pData,sizeof(NET_CARD_DEVICENETPARA));
				memcpy(&sIP,pReturnIP,nIPLen);
				sIP[nIPLen]='\0';	   
				//数据赋值与转换
				m_sIP		=theApp.TransfromBYTE(NetParameter.m_sNetIP,4,1);
				m_sMAC		=theApp.TransfromBYTE(NetParameter.m_sNetMAC,6,0);
				m_sGate	    =theApp.TransfromBYTE(NetParameter.m_sNetGate,4,1);
				m_sMask		=theApp.TransfromBYTE(NetParameter.m_sNetMask,4,1);
				nDevicePort	=NetParameter.m_nNetPort[0]<<8 | NetParameter.m_nNetPort[1];
				m_sPort.Format("%d",nDevicePort);
				m_sDoorNum  =theApp.TransfromASCII(&NetParameter.m_nDoorNum, 1);//ASCII
				m_sVersion  =theApp.TransfromASCII(NetParameter.m_sVersion, 16);//ASCII
			
				strTmp1 ="\r\n";
				strTmp1+="IP:"		+ m_sIP		+"\r\n";
				strTmp1+="PORT:"	+ m_sPort	+"\r\n";
				strTmp1+="MAC:"		+ m_sMAC	+"\r\n";
				strTmp1+="GATE:"	+ m_sGate	+"\r\n";
				strTmp1+="MASK:"	+ m_sMask	+"\r\n";
				strTmp1+="DOORS:"	+ m_sDoorNum+"\r\n";
				strTmp1+="VERSION:"	+ m_sVersion+"\r\n";
				strTmp1+="\r\n";

				g_pMainDlg->DisplayInfoforRecieve(strTmp1);		

			}
		}
	}
	else if(nType==9)//915读头数据
	{
		if(nRetDataLen<1200)
		{
			CString strTmp1;
			memcpy(&data[0],pData,nRetDataLen);
			CString strData,strData2;
			for(int i = 0;i<nRetDataLen;i++)
			{
				strData2.Format( "%02X",   (BYTE)pData[i]); 
				strData+=strData2;
			}
			g_pMainDlg->DisplayInfoforRecieve("915 EPC："+strData);
			
			int nReader =data[13];
			int nCardNum=data[14];
			char Carddata[20];

			for(int kk=0;kk<nCardNum;kk++)
			{
				memcpy(Carddata,pData+15+12*kk,12);
				strData=_T("");
				for(int i = 0;i<12;i++)
				{
					strData2.Format( "%02X",   (BYTE)Carddata[i]); 
					strData+=strData2;

				}
				CString StrTmp;
				StrTmp.Format("Reader=%d,EPC No=%d:",nReader,kk+1);

				g_pMainDlg->DisplayInfoforRecieve(StrTmp+strData);
			}

		
		}

	}
	else 
	{
		//显示条码信息或其它信息
		if(nRetDataLen<1200)
		{
			CString strTmp1;
			memcpy(&data[0],pData,nRetDataLen);
			CString strData,strData2;
			for(int i = 0;i<nRetDataLen;i++)
			{
				strData2.Format( "%02X",   (BYTE)pData[i]); 
				strData+=strData2;
			}
			g_pMainDlg->DisplayInfoforRecieve("其它数据："+strData);
		}

	}
	memcpy(ReturnMAC,pReturnDevMAC,6);
	ReturnMAC[6]='\0';

	nReturnIPLen=*ReturnIPLen;
	if(nReturnIPLen<=15)
	{
		memcpy(ReturnIP,pReturnIP,nReturnIPLen);
		ReturnIP[nReturnIPLen]='\0';
	}

	return 0;
}
int CALLBACK GetBroadcastSerachProcess(NET_CARD_DEVICENETPARA *pNetParameter,char *pReturnIP,int *nIPLength,char *pReturnMAC)
{

	g_pMainDlg->BroadCastForFillList(pNetParameter,pReturnIP,nIPLength,pReturnMAC);

	return 0;
}
int CALLBACK GetRealtimeDataProcess(NET_CARD_RECORDINFO *pRecordInfo,char *pReturnIP,int *ReturnIPLen,char *pReturnMAC)
{
	char ReturnIP[15];
	char ReturnMAC[6];
	int  nReturnIPLen;
	NET_CARD_RECORDINFO  RecordInfo;
	nReturnIPLen=*ReturnIPLen;
	memcpy(&RecordInfo,pRecordInfo,sizeof(NET_CARD_RECORDINFO));
	memcpy(ReturnMAC,pReturnMAC,6);
	ReturnMAC[6]='\0';
	if(nReturnIPLen<=15)
	{
		memcpy(ReturnIP,pReturnIP,nReturnIPLen);
		ReturnIP[nReturnIPLen]='\0';
	}
////////////////////////////////
	//card series
	CString strCardRecord;
	strCardRecord.Format("%02X%02X%02X%02X",RecordInfo.Record_CardID[0],RecordInfo.Record_CardID[1],RecordInfo.Record_CardID[2],RecordInfo.Record_CardID[3]);//得到卡号
	//Time
	CString strDateRecord;
	strDateRecord.Format("20%02X-%02X-%02X %02X:%02X:%02X",RecordInfo.Record_Time[0],RecordInfo.Record_Time[1],RecordInfo.Record_Time[2],RecordInfo.Record_Time[3],RecordInfo.Record_Time[4],RecordInfo.Record_Time[5]);
	//Event ID
	int m_iEvent=0;
	CString  m_sEventStr;
	m_iEvent = RecordInfo.Record_EventNum;
	if(m_iEvent<100)
		m_sEventStr = EventString[m_iEvent];
	else
		m_sEventStr ="Unknow Event";

	CString  OperatTimeStr,strTmp1;
	CTime Endtime=CTime::GetCurrentTime() ;
	OperatTimeStr.Format("%04d-%02d-%02d:%02d:%02d:%02d",Endtime.GetYear(),Endtime.GetMonth(),Endtime.GetDay(),Endtime.GetHour(),Endtime.GetMinute(),Endtime.GetSecond() );//年月日 2010 09 08

	//card series=FFFFFFFF,it is door open/close status
	if(strCardRecord=="FFFFFFFF")
	{	
		CString AllDoorStatus,SwitchNametmp;
		int nDoorStatue=RecordInfo.Record_DoorNum & 0x0f;
		for(int ii=0;ii<4;ii++)
		{
			int m_iDoor;
			m_iDoor=(nDoorStatue&(1<<ii));					
			if(m_iDoor)
			{
				SwitchNametmp.Format("door%d open ",ii+1);
			}else{
				SwitchNametmp.Format("door%d close ",ii+1);
			}
			AllDoorStatus +=SwitchNametmp;
		}
		OperatTimeStr +="\r\n";
		OperatTimeStr +=AllDoorStatus;;
		g_pMainDlg->DisplayInfoforRecieve(OperatTimeStr);
	}
	else
	{
		//MAC to CString
		CString  m_sDevMACStr;
		m_sDevMACStr = theApp.TransfromBYTE((unsigned char*)ReturnMAC,6,0);
		//Reader NO.
		CString  m_sInOrOut="IN";
		int nReaderNo= RecordInfo.Record_DoorNum &0x07 ;
		if(nReaderNo>=4)
		{
			m_sInOrOut="OUT";
			nReaderNo =nReaderNo-4;
		}

		CString tmpStr;
		strTmp1+="Gather Time:"		+ OperatTimeStr		+"\r\n";
		strTmp1+="Card Series:"		+ strCardRecord		+"\r\n";
		tmpStr=ReturnIP;
		strTmp1+="IP:"		+ tmpStr		+"\r\n";
		tmpStr.Format("%d",nReaderNo);
		strTmp1+="Reader No.:"		+ tmpStr		+"\r\n";
		tmpStr.Format("%d",m_iEvent);		
		strTmp1+="Event ID:"		+ tmpStr		+"\r\n";
		strTmp1+="Event Name:"		+ m_sEventStr	+"\r\n";
		strTmp1+="Event Time:"		+ strDateRecord	+"\r\n";
		strTmp1+="Device MAC:"		+ m_sDevMACStr	+"\r\n";
		strTmp1+="IN  or OUT:"		+ m_sInOrOut	+"\r\n";
		strTmp1+="\r\n";
		g_pMainDlg->DisplayInfoforRecieve(strTmp1);

	}
	 return 0;
}


CSDK_DEMO_VCDlg::CSDK_DEMO_VCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSDK_DEMO_VCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSDK_DEMO_VCDlg)
	m_sCOM_MAC = _T("008139000015");
	m_sCOM_PORT = _T("9998");
	m_sCOM_MASK = _T("255.255.255.0");
	m_sCOM_GATE = _T("192.168.1.1");
	m_sCOM_IP = _T("192.168.1.15");
	m_sNEW_MAC = _T("008139000015");
	m_sNEW_GATE = _T("192.168.1.1");
	m_sNEW_MASK = _T("255.255.255.0");
	m_sNEW_PORT = _T("9998");
	m_sNEW_IP = _T("192.168.1.15");
	m_sLocalPort = _T("");
	m_nLockDelay = 10;
	m_nAlarmOutDelay1 = 20;
	m_nAlarmOutDelay2 = 20;
	m_nAlarmOutDelay3 = 20;
	m_nAlarmOutDelay4 = 20;
	m_sPassword1 = _T("1234");
	m_sPassword2 = _T("5678");
	m_sPassword3 = _T("1122");
	m_sPassword4 = _T("3344");
	m_sDruessPass = _T("7788");
	m_nDruessDelay = 20;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	nCountCai =0;
}

void CSDK_DEMO_VCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSDK_DEMO_VCDlg)
	DDX_Control(pDX, IDC_STATIC_PIC, m_cOriPicStatic);
	DDX_Control(pDX, IDC_INFO_EDIT1, m_wndList1);
	DDX_Control(pDX, IDC_CLIENT_LIST1, m_wndOutputList);
	DDX_Text(pDX, IDC_EDIT_OLDMAC, m_sCOM_MAC);
	DDX_Text(pDX, IDC_EDIT_OLDPORT, m_sCOM_PORT);
	DDX_Text(pDX, IDC_EDIT_OLDMASK, m_sCOM_MASK);
	DDX_Text(pDX, IDC_EDIT_OLDGATE, m_sCOM_GATE);
	DDX_Text(pDX, IDC_EDIT_OLDIP, m_sCOM_IP);
	DDX_Text(pDX, IDC_EDIT_NEWMAC, m_sNEW_MAC);
	DDX_Text(pDX, IDC_EDIT_NEWGATE, m_sNEW_GATE);
	DDX_Text(pDX, IDC_EDIT_NEWMASK, m_sNEW_MASK);
	DDX_Text(pDX, IDC_EDIT_NEWPORT, m_sNEW_PORT);
	DDX_Text(pDX, IDC_EDIT_NEWIP, m_sNEW_IP);
	DDX_Text(pDX, IDC_EDIT_LOCALPORT, m_sLocalPort);
	DDX_Text(pDX, IDC_EDIT_LOCKDELAY, m_nLockDelay);
	DDV_MinMaxInt(pDX, m_nLockDelay, 1, 254);
	DDX_Text(pDX, IDC_EDIT_OUTDELAY1, m_nAlarmOutDelay1);
	DDV_MinMaxInt(pDX, m_nAlarmOutDelay1, 1, 65535);
	DDX_Text(pDX, IDC_EDIT_OUTDELAY2, m_nAlarmOutDelay2);
	DDV_MinMaxInt(pDX, m_nAlarmOutDelay2, 1, 65535);
	DDX_Text(pDX, IDC_EDIT_OUTDELAY3, m_nAlarmOutDelay3);
	DDV_MinMaxInt(pDX, m_nAlarmOutDelay3, 1, 65535);
	DDX_Text(pDX, IDC_EDIT_OUTDELAY4, m_nAlarmOutDelay4);
	DDV_MinMaxInt(pDX, m_nAlarmOutDelay4, 1, 65535);
	DDX_Text(pDX, IDC_EDIT_OPENPASS1, m_sPassword1);
	DDX_Text(pDX, IDC_EDIT_OPENPASS2, m_sPassword2);
	DDX_Text(pDX, IDC_EDIT_OPENPASS3, m_sPassword3);
	DDX_Text(pDX, IDC_EDIT_OPENPASS4, m_sPassword4);
	DDX_Text(pDX, IDC_EDIT_DRUESSPASS, m_sDruessPass);
	DDX_Text(pDX, IDC_EDIT_DRUESSOUTDELAY, m_nDruessDelay);
	DDV_MinMaxInt(pDX, m_nDruessDelay, 1, 254);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSDK_DEMO_VCDlg, CDialog)
	//{{AFX_MSG_MAP(CSDK_DEMO_VCDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON31_SERACH, OnButton31Serach)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON1_SETNETWORK, OnButton1Setnetwork)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON28, OnButton28)
	ON_BN_CLICKED(IDC_BUTTON29, OnButton29)
	ON_BN_CLICKED(IDC_DOOR_CHECK1, OnDoorCheck1)
	ON_BN_CLICKED(IDC_DOOR_CHECK2, OnDoorCheck2)
	ON_BN_CLICKED(IDC_DOOR_CHECK3, OnDoorCheck3)
	ON_BN_CLICKED(IDC_DOOR_CHECK4, OnDoorCheck4)
	ON_BN_CLICKED(IDC_BUTTON16, OnButton16)
	ON_BN_CLICKED(IDC_BUTTON17, OnButton17)
	ON_BN_CLICKED(IDC_BUTTON18, OnButton18)
	ON_BN_CLICKED(IDC_BUTTON19, OnButton19)
	ON_BN_CLICKED(IDC_BUTTON22, OnButton22)
	ON_BN_CLICKED(IDC_BUTTON23, OnButton23)
	ON_BN_CLICKED(IDC_DOOR_CHECK11, OnDoorCheck11)
	ON_BN_CLICKED(IDC_BUTTON24, OnButton24)
	ON_BN_CLICKED(IDC_BUTTON25, OnButton25)
	ON_BN_CLICKED(IDC_BUTTON27, OnButton27)
	ON_BN_CLICKED(IDC_BUTTON26, OnButton26)
	ON_BN_CLICKED(IDC_BUTTON31, OnButton31)
	ON_BN_CLICKED(IDC_BUTTON30, OnButton30)
	ON_BN_CLICKED(IDC_DOOR_CHECK5, OnDoorCheck5)
	ON_BN_CLICKED(IDC_DOOR_CHECK6, OnDoorCheck6)
	ON_BN_CLICKED(IDC_DOOR_CHECK7, OnDoorCheck7)
	ON_BN_CLICKED(IDC_DOOR_CHECK8, OnDoorCheck8)
	ON_BN_CLICKED(IDC_DOOR_CHECK9, OnDoorCheck9)
	ON_BN_CLICKED(IDC_DOOR_CHECK10, OnDoorCheck10)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_BUTTON12, OnButton12)
	ON_BN_CLICKED(IDC_BUTTON13, OnButton13)
	ON_BN_CLICKED(IDC_BUTTON14, OnButton14)
	ON_BN_CLICKED(IDC_BUTTON20, OnButton20)
	ON_BN_CLICKED(IDC_BUTTON21, OnButton21)
	ON_BN_CLICKED(IDC_BUTTON15, OnButton15)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON33, OnButton33)
	ON_BN_CLICKED(IDC_BUTTON34, OnButton34)
	ON_BN_CLICKED(IDC_BUTTON35, OnButton35)
	ON_BN_CLICKED(IDC_BUTTON36, OnButton36)
	ON_BN_CLICKED(IDC_BUTTON37, OnButton37)
	ON_BN_CLICKED(IDC_BUTTON32, OnButton32)
	ON_BN_CLICKED(IDC_BUTTON38, OnButton38)
	ON_BN_CLICKED(IDC_BUTTON31_SERACH2, OnButton31Serach2)
	ON_BN_CLICKED(IDC_BUTTON39, OnButton39)
	ON_BN_CLICKED(IDC_BUTTON31_SERACH3, OnButton31Serach3)
	ON_BN_CLICKED(IDC_BUTTON31_SERACH5, OnButton31Serach5)
	ON_BN_CLICKED(IDC_BUTTON31_SERACH7, OnButton31Serach7)
	ON_BN_CLICKED(IDC_BUTTON31_SERACH4, OnButton31Serach4)
	ON_BN_CLICKED(IDC_BUTTON31_SERACH9, OnButton31Serach9)
	ON_BN_CLICKED(IDC_BUTTON31_SERACH10, OnButton31Serach10)
	ON_BN_CLICKED(IDC_BUTTON31_SERACH6, OnButton31Serach6)
	ON_BN_CLICKED(IDC_BUTTON40, OnButton40)
	ON_BN_CLICKED(IDC_DOOR_CHECK17, OnDoorCheck17)
	ON_BN_CLICKED(IDCANCELSAVE, OnOk2)
	ON_BN_CLICKED(IDC_BUTTON31_SERACH11, OnButton31Serach11)
	ON_BN_CLICKED(IDC_BUTTON31_SERACH12, OnButton31Serach12)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSDK_DEMO_VCDlg message handlers

BOOL CSDK_DEMO_VCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
#ifndef ENGLISH
	m_wndOutputList.InsertColumn(0, "序号" ,	 LVCFMT_CENTER, 80);
	m_wndOutputList.InsertColumn(1, "操作时间" , LVCFMT_CENTER, 150);
	m_wndOutputList.InsertColumn(2, "操作状态" , LVCFMT_CENTER,	150);
	m_wndOutputList.InsertColumn(3, "事件说明" , LVCFMT_CENTER,	500);
	m_wndOutputList.InsertColumn(4, "提示信息" , LVCFMT_CENTER, 200);
	m_wndOutputList.SetExtendedStyle(LVS_EX_FULLROWSELECT);
#else
	m_wndOutputList.InsertColumn(0, "NO." ,	 LVCFMT_CENTER, 80);
	m_wndOutputList.InsertColumn(1, "Time" , LVCFMT_CENTER, 150);
	m_wndOutputList.InsertColumn(2, "Statue" , LVCFMT_CENTER,	150);
	m_wndOutputList.InsertColumn(3, "Event Infomation" , LVCFMT_LEFT,	500);
	m_wndOutputList.InsertColumn(4, "Error Infomation" , LVCFMT_CENTER, 250);
	m_wndOutputList.SetExtendedStyle(LVS_EX_FULLROWSELECT);
#endif
/////////Find All NetCards and Set correct  IP Communicate
	int NetCardNumber=0;
	theApp.GetIPCards();
	NetCardNumber=theApp.SysNetCardArray.GetSize();
	if(NetCardNumber<=0)
	{
		AfxMessageBox(m_sStrOutputInfo[10]);
	}
	CString strtmp;
	for(int kk=0;kk<NetCardNumber;kk++)
	{
	   strtmp=theApp.SysNetCardArray.GetAt(kk);
	   ((CComboBox*)GetDlgItem(IDC_NETCARD_COMBO1))->AddString(strtmp);
	   if(theApp.m_sLocalComputerIP==strtmp)
	   {
			((CComboBox*)GetDlgItem(IDC_NETCARD_COMBO1))->SetCurSel(kk);
	   }
	}
	m_sCOM_IP = theApp.m_sDevice_IP;
	sprintf(DeviceIP, "%s", m_sCOM_IP);

	nDevicePort = atoi(m_sCOM_PORT);
	//Set correct  Communicate Port
	GetDlgItem(IDC_EDIT_LOCALPORT)->SetWindowText(theApp.m_sLocalComputerPORT);

((CEdit*)GetDlgItem(IDC_EDIT_LOCALPORT2))->SetWindowText(theApp.m_sLocalComputerIP);
((CEdit*)GetDlgItem(IDC_EDIT_LOCALPORT4))->SetWindowText(theApp.m_sLocalComputerIP);
((CEdit*)GetDlgItem(IDC_EDIT_LOCALPORT6))->SetWindowText(theApp.m_sLocalComputerIP);


((CEdit*)GetDlgItem(IDC_EDIT_LOCALPORT3))->SetWindowText(theApp.m_sLocalComputerPORT);
((CEdit*)GetDlgItem(IDC_EDIT_LOCALPORT5))->SetWindowText(theApp.m_sLocalComputerPORT);
((CEdit*)GetDlgItem(IDC_EDIT_LOCALPORT7))->SetWindowText(theApp.m_sLocalComputerPORT);


((CEdit*)GetDlgItem(IDC_EDIT_LOCALPORT8))->SetWindowText("19100");

((CEdit*)GetDlgItem(IDC_EDIT_OUTDELAY7))->SetWindowText("DLQR-06");

((CEdit*)GetDlgItem(IDC_EDIT_OUTDELAY8))->SetWindowText("1234");



	InitNetSDK();

	nReaderNo =0x0F;//door1.2.3.4

	((CButton*)GetDlgItem(IDC_DOOR_CHECK1))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_DOOR_CHECK2))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_DOOR_CHECK3))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_DOOR_CHECK4))->SetCheck(1);
	((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);

	((CButton*)GetDlgItem(IDC_RADIO5))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO6))->SetCheck(1);

	//card series
	GetDlgItem(IDC_EDIT_CARDSERIES)->SetWindowText(theApp.CurCardIDStr);
	//period of validity
	GetDlgItem(IDC_EDIT_ENDDATE)->SetWindowText("181020");//2018-10-20
	//card + password  password
	GetDlgItem(IDC_EDIT_OPENPASSWORD)->SetWindowText("1234");//2018-10-20

	GetDlgItem(IDC_EDIT_OUTDELAY5)->SetWindowText("04");//2018-10-20

	
	
	//0xF0 The lower four bits 0000 --> Left to right  1st bit door4 .. 4th bit door 1(0 Yes 1 NO)
	nReaderRight =0xF0;//door 1,2,3,4,have open access
	
	((CButton*)GetDlgItem(IDC_DOOR_CHECK5))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_DOOR_CHECK6))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_DOOR_CHECK7))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_DOOR_CHECK8))->SetCheck(1);
	//0 card open door
	PassType =0x00;	
	((CButton*)GetDlgItem(IDC_DOOR_CHECK9))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_DOOR_CHECK10))->SetCheck(0);

	//0 Ordinary card to open the door
	OpenType =0x00;
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(0);

	RightGroup =0xff;

	m_sLocalPort =theApp.m_sLocalComputerPORT;

	((CEdit*)GetDlgItem(IDC_EDIT_OUTDELAY6))->SetWindowText("123456789987654321");


	UpdateData(FALSE);


	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSDK_DEMO_VCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSDK_DEMO_VCDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSDK_DEMO_VCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CSDK_DEMO_VCDlg::InitNetSDK()
{
	CString  ErrorStr;	

	//软件通讯IP地址
	//SoftWare Socket IP
	sprintf(szLocalIP, "%s", theApp.m_sLocalComputerIP);
	//软件通讯端口号
	//SoftWare Socket Port
	nLocalPort=atoi(theApp.m_sLocalComputerPORT);
	//网络通讯等待延时设置为3秒
	//communication Maximum waiting time 3S
	WaitTimout =3000;
	//初始化DLL网络参数
	//Init the parameter of Network Communication for DLL;
	if(NET_CARD_InitEx(szLocalIP,nLocalPort,WaitTimout)!=0)
	{
		ErrorStr.Format("IP or Port is incorrect,please check config.ini file, err=%ld",GetLastError());
		MessageBox(ErrorStr,"ERROR",IDOK);
		return FALSE;
	}
	//写入输出LIST
	AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[11]+theApp.m_sLocalComputerIP+" "+theApp.m_sLocalComputerPORT);

	//设置记录获取回调函数
	//Set a callback function for  Get records
	NET_CARD_RealTimeDataCallback(GetRealtimeDataProcess);
	NET_CARD_RealTimeDataCallbackEx(GetRealtimeDataProcessEx);
	//设置广播设备搜索回调函数
	//Set a callback function for Broadcast  Search all devices
	NET_CARD_BroadcastSerachDevice(GetBroadcastSerachProcess);

	

	return TRUE;
}
//display recieve infomation to list window
void CSDK_DEMO_VCDlg::DisplayInfoforRecieve(LPCTSTR str)
{
	int iLineNum=m_wndList1.GetLineCount();
	if(iLineNum<=100)
	{
		m_wndList1.SetSel(-1, -1);
		m_wndList1.ReplaceSel((CString)str+"\r\n");
	}else{
		m_wndList1.SetSel(0, -1);
		m_wndList1.Clear(); 
		m_wndList1.SetWindowText("");     
		m_wndList1.Invalidate();
	}
	return;

}
void CSDK_DEMO_VCDlg::BroadCastForFillList(NET_CARD_DEVICENETPARA *pNetParameter, char *pReturnIP, int *nIPLength, char *pReturnMAC)
{

	char sIP[30];
	char sMAC[30];
	int  nIPLen,nDevicePort;
	NET_CARD_DEVICENETPARA  NetParameter;
	CString  strTmp1,strTmp2;
	CString  m_sIP,m_sMAC,m_sGate,m_sMask,m_sPort,m_sVersion,m_sDoorNum;

	int		nItem=0;
	BOOL	m_bFind=FALSE;

	nIPLen =*nIPLength;
	memset(&NetParameter,0,sizeof(NET_CARD_DEVICENETPARA));
    memcpy(&sMAC,pReturnMAC,6);
    sMAC[6]='\0';

	if(pNetParameter!=NULL)
	{
		memcpy(&NetParameter,pNetParameter,sizeof(NET_CARD_DEVICENETPARA));
		memcpy(&sIP,pReturnIP,nIPLen);
		sIP[nIPLen]='\0';	   
		//数据赋值与转换
		m_sIP		=theApp.TransfromBYTE(NetParameter.m_sNetIP,4,1);
		m_sMAC		=theApp.TransfromBYTE(NetParameter.m_sNetMAC,6,0);
		m_sGate	    =theApp.TransfromBYTE(NetParameter.m_sNetGate,4,1);
		m_sMask		=theApp.TransfromBYTE(NetParameter.m_sNetMask,4,1);
		nDevicePort	=NetParameter.m_nNetPort[0]<<8 | NetParameter.m_nNetPort[1];
		m_sPort.Format("%d",nDevicePort);
		m_sDoorNum  =theApp.TransfromASCII(&NetParameter.m_nDoorNum, 1);//ASCII
		m_sVersion  =theApp.TransfromASCII(NetParameter.m_sVersion, 16);//ASCII
	
		strTmp1 ="\r\n";
		strTmp1+="IP:"		+ m_sIP		+"\r\n";
		strTmp1+="PORT:"	+ m_sPort	+"\r\n";
		strTmp1+="MAC:"		+ m_sMAC	+"\r\n";
		strTmp1+="GATE:"	+ m_sGate	+"\r\n";
		strTmp1+="MASK:"	+ m_sMask	+"\r\n";
		strTmp1+="DOORS:"	+ m_sDoorNum+"\r\n";
		strTmp1+="VERSION:"	+ m_sVersion+"\r\n";
		strTmp1+="\r\n";
		DisplayInfoforRecieve(strTmp1);


		m_sCOM_IP =m_sIP;
		sprintf(DeviceIP, "%s", m_sCOM_IP);
		m_sCOM_PORT = m_sPort;
		nDevicePort = atoi(m_sCOM_PORT);

		m_sCOM_MAC =m_sMAC;
		m_sCOM_GATE =m_sGate;
		m_sCOM_MASK =m_sMask;

		((CEdit*)GetDlgItem(IDC_EDIT_OLDIP))->SetWindowText(m_sCOM_IP);
		((CEdit*)GetDlgItem(IDC_EDIT_NEWIP))->SetWindowText(m_sCOM_IP);

		((CEdit*)GetDlgItem(IDC_EDIT_OLDPORT))->SetWindowText(m_sCOM_PORT);
		((CEdit*)GetDlgItem(IDC_EDIT_NEWPORT))->SetWindowText(m_sCOM_PORT);

		((CEdit*)GetDlgItem(IDC_EDIT_OLDMASK))->SetWindowText(m_sMask);
		((CEdit*)GetDlgItem(IDC_EDIT_NEWMASK))->SetWindowText(m_sMask);

		((CEdit*)GetDlgItem(IDC_EDIT_OLDGATE))->SetWindowText(m_sGate);
		((CEdit*)GetDlgItem(IDC_EDIT_NEWGATE))->SetWindowText(m_sGate);

		((CEdit*)GetDlgItem(IDC_EDIT_OLDMAC))->SetWindowText(m_sMAC);
		((CEdit*)GetDlgItem(IDC_EDIT_NEWMAC))->SetWindowText(m_sMAC);
		

	}

}

void CSDK_DEMO_VCDlg::AddStringtoList(CString OperatStatus, CString EventExplain, CString ErrorInfo)
{
   int nItemCount=0;
    CString	OperatTimeStr,strtemp;

//	WaitForSingleObject(theApp.OutPutList_Mute,INFINITE);
	CTime Endtime=CTime::GetCurrentTime() ;
	OperatTimeStr.Format("%04d-%02d-%02d:%02d:%02d:%02d",Endtime.GetYear(),Endtime.GetMonth(),Endtime.GetDay(),Endtime.GetHour(),Endtime.GetMinute(),Endtime.GetSecond() );
	nItemCount=m_wndOutputList.GetItemCount();
	if(nItemCount>500)
	{
		m_wndOutputList.DeleteAllItems();	
		nItemCount = 0;
	}
	strtemp.Format("%03d",nItemCount+1);
	m_wndOutputList.InsertItem(nItemCount, strtemp);
	m_wndOutputList.SetItemText(nItemCount, 1, OperatTimeStr);
	m_wndOutputList.SetItemText(nItemCount, 2, OperatStatus);
	m_wndOutputList.SetItemText(nItemCount, 3, EventExplain);
	m_wndOutputList.SetItemText(nItemCount, 4, ErrorInfo);
	m_wndOutputList.EnsureVisible(nItemCount,true);
	m_wndOutputList.SetItemState(nItemCount, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
    nItemCount = m_wndOutputList.GetItemCount();
	if(nItemCount>500)
	{
		m_wndOutputList.DeleteAllItems();	
		nItemCount = 0;
	}
//	ReleaseMutex(theApp.OutPutList_Mute);
	return;
}

void CSDK_DEMO_VCDlg::OnOK() 
{
	//Save Parameter to INI File
	UpdateData(TRUE);
	theApp.m_sLocalComputerPORT =m_sLocalPort;
	theApp.m_sDevice_IP=m_sCOM_IP;
	int nIndex=((CComboBox*)GetDlgItem(IDC_NETCARD_COMBO1))->GetCurSel();
	if(nIndex>=0)
	{
	  ((CComboBox*)GetDlgItem(IDC_NETCARD_COMBO1))->GetLBText(nIndex,theApp.m_sLocalComputerIP);
	}

	theApp.ReadorWriteIniFile(FALSE);

	CDialog::OnOK();
}
//Device search
void CSDK_DEMO_VCDlg::OnButton31Serach() 
{
	int  nRemotePort;
	CString m_sInputIP,m_sInputPort;

	CDlgEditforViewIP dlg;
	if(dlg.DoModal()!=IDOK)
		return;

	m_sInputIP	=dlg.m_sEditDlg;
	m_sInputPort=dlg.m_sEditDlgPort;
	m_sInputPort.TrimLeft();
	m_sInputPort.TrimRight();
	m_sInputIP.TrimLeft();
	m_sInputIP.TrimRight();
	nRemotePort=atoi(m_sInputPort);

	char InputIP[15];
	sprintf(InputIP, "%s", m_sInputIP);


	nRet=NET_CARD_BroadCastSearchDevice(DEVICE_NET_ACCESS,InputIP,nRemotePort);

	if(nRet>0)
	{
		//写入输出LIST
		CString OperatTimeStr,EventExplainStr,m_sReturnError;
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[12]+m_sStrOutputInfo[0]);
	}
	else
	{
		//写入输出LIST
		CString m_sReturnError;
		m_sReturnError.Format("%d",nRet);
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[12]+m_sStrOutputInfo[1],m_sReturnError);
	}
	
}
//Get NetWork Parameter
void CSDK_DEMO_VCDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	
}


//Set network parameter
void CSDK_DEMO_VCDlg::OnButton1Setnetwork() 
{
	NET_CARD_DEVICENETPARA  NetParameter;

	int  nRemotePort=0;
	int  nDevicePortNew =0;
	int	 m_nDoorNum =0;
	char MACTmp[6];
	char OldNetMAC[6];
	CString  m_sIP,m_sMAC,m_sGate,m_sMask,m_sVersion,m_sPort,m_sDoorNum;
	CString  strSQL,strTmp1,strTmp2;

	sprintf(DeviceIP, "%s", m_sCOM_IP);
	nDevicePort = atoi(m_sCOM_PORT);

	UpdateData(TRUE);

	memset(&NetParameter,0,sizeof(NET_CARD_DEVICENETPARA));
	//IP
	theApp.TransIPfromCStringtoBYTE(m_sNEW_IP,NetParameter.m_sNetIP);
//	strSQL.Format("%u,%u,%u,%u",NetParameter.m_sNetIP[0],NetParameter.m_sNetIP[1],NetParameter.m_sNetIP[2],NetParameter.m_sNetIP[3]);
	//MAC
	for(int kk=0;kk<m_sNEW_MAC.GetLength()/2;kk++)
	{
		strTmp1=m_sNEW_MAC.Mid(2*kk,2);
		sscanf(strTmp1, "%x", MACTmp+kk);
	}
	memcpy(NetParameter.m_sNetMAC,MACTmp,6);
	

	//GATE
	theApp.TransIPfromCStringtoBYTE(m_sNEW_GATE,NetParameter.m_sNetGate);
	//MASK
	theApp.TransIPfromCStringtoBYTE(m_sNEW_MASK,NetParameter.m_sNetMask);
	//PORT
	nDevicePortNew = atoi(m_sNEW_PORT);
	NetParameter.m_nNetPort[0] =  (nDevicePortNew >> 8) & 0xff;
	NetParameter.m_nNetPort[1] =  (nDevicePortNew) & 0xff;
	//OLD MAC
	for(kk=0;kk<m_sCOM_MAC.GetLength()/2;kk++)
	{
		strTmp1=m_sCOM_MAC.Mid(2*kk,2);
		sscanf( strTmp1, "%x", MACTmp+kk);//Scanf()会影响后面的变量
	}
	memcpy(OldNetMAC,MACTmp,6);
	nRet = NET_CARD_SetNetWorkParameter(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,OldNetMAC,&NetParameter,ReMACBuffer);
	if(nRet == 0)
	{
		//写入输出LIST
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[13]);
	}
	else 
	{
		char DeviceIPTmp[15];
		sprintf(DeviceIPTmp, "%s", "255.255.255.255");
		nRet = NET_CARD_SetNetWorkParameter(DEVICE_NET_ACCESS,DeviceIPTmp,nDevicePort,OldNetMAC,&NetParameter,ReMACBuffer);
		if(nRet == 0)
		{
			//写入输出LIST
			AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[13]);
		}
		else
		{
			//写入输出LIST
			m_sReturnError.Format("%d",nRet);	
			AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[13],m_sReturnError);
		}
	}

	
}
//online detect
void CSDK_DEMO_VCDlg::OnButton3() 
{
	NET_CARD_TIME DeviceTime;
	memset(&DeviceTime,0,sizeof(NET_CARD_TIME));
	nRet=NET_CARD_DetectDeviceOnline(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,ReMACBuffer,&DeviceTime);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[14]);
	}else{
		//写入输出LIST
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[14],m_sReturnError);
	}
	
}
//Get Device time <==> online detect
void CSDK_DEMO_VCDlg::OnButton7() 
{
	NET_CARD_TIME DeviceTime;
	memset(&DeviceTime,0,sizeof(NET_CARD_TIME));
	nRet=NET_CARD_DetectDeviceOnline(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,ReMACBuffer,&DeviceTime);
	if(nRet==0)
	{
		CString DeviceTimeStr;
		DeviceTimeStr.Format("20%02X-%02X-%02X %02X:%02X:%02X",DeviceTime.wYear,DeviceTime.byMonth,DeviceTime.byDay,DeviceTime.byHour,DeviceTime.byMinute,DeviceTime.bySecond);
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[14]+DeviceTimeStr);
	}else{
		//写入输出LIST
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[14],m_sReturnError);
	}
	
}
//set device time 
void CSDK_DEMO_VCDlg::OnButton8() 
{
	unsigned char TimeBuffer[]={0x13,0x11,0x07,0x12,0x28,0x28};
	CString strTmp1,OperatTimeStr;
	NET_CARD_TIME  CurTime;

	CTime Endtime=CTime::GetCurrentTime() ;
	OperatTimeStr.Format("%02d%02d%02d%02d%02d%02d",Endtime.GetYear()-2000,Endtime.GetMonth(),Endtime.GetDay(),Endtime.GetHour(),Endtime.GetMinute(),Endtime.GetSecond() );
	for(int kk=0;kk<OperatTimeStr.GetLength()/2;kk++)
	{
		strTmp1=OperatTimeStr.Mid(2*kk,2);
		sscanf( strTmp1, "%x", TimeBuffer+kk);
	}
	CurTime.wYear		= TimeBuffer[0];
	CurTime.byMonth		= TimeBuffer[1];
	CurTime.byDay		= TimeBuffer[2];
	CurTime.byHour		= TimeBuffer[3];
	CurTime.byMinute	= TimeBuffer[4];
	CurTime.bySecond	= TimeBuffer[5];
	nRet = NET_CARD_SetDeviceTime(DEVICE_NET_ACCESS,DeviceIP,nDevicePort, &CurTime,ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[16]);

	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[16],m_sReturnError);

	}
	
}
//Get Version
void CSDK_DEMO_VCDlg::OnButton4() 
{
	CString DevVersionStr;
	char  DevVersion[17];
	nRet = NET_CARD_ReadDeviceVersion(DEVICE_NET_ACCESS,DeviceIP,nDevicePort, ReMACBuffer,DevVersion);
	if(nRet==0)
	{
		DevVersionStr = DevVersion;//DevVersion本身就是ASCII码表示的,可以直接转换成CString;
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[17],DevVersionStr);

	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[17],m_sReturnError);
	}
	
}
//device init
void CSDK_DEMO_VCDlg::OnButton5() 
{
	nRet=NET_CARD_DeviceInit(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[18]);
	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[18],m_sReturnError);
	}
	
}
//set upload IP and port
void CSDK_DEMO_VCDlg::OnButton6() 
{
	int	  nServerPort;
	char  ServerIP[5];
	nServerPort =nLocalPort;
	theApp.TransIPfromCStringtoBYTE(theApp.m_sLocalComputerIP,(unsigned char*)ServerIP);
	nRet = NET_CARD_SetServerIPandPort(DEVICE_NET_ACCESS,DeviceIP, nDevicePort,ServerIP,nServerPort,ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[19]);

	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[19],m_sReturnError);
	}
	
}
//Start real moniter
void CSDK_DEMO_VCDlg::OnButton28() 
{

	nRet = NET_CARD_EnableRealTimeMonitor(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[20]);

	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[20],m_sReturnError);
	}

	
}
//Stop real moniter
void CSDK_DEMO_VCDlg::OnButton29() 
{
	nRet = NET_CARD_DisbleRealTimeMonitor(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[21]);

	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[21],m_sReturnError);
	}
	
}
//door1
void CSDK_DEMO_VCDlg::OnDoorCheck1() 
{	
	BOOL m_bCheck=((CButton*)GetDlgItem(IDC_DOOR_CHECK1))->GetCheck();
	if(m_bCheck)
	{
		nReaderNo |=0x01;
	}else{
		nReaderNo &=0x0E;
	}
}
//door2
void CSDK_DEMO_VCDlg::OnDoorCheck2() 
{
	BOOL m_bCheck=((CButton*)GetDlgItem(IDC_DOOR_CHECK2))->GetCheck();
	if(m_bCheck)
	{
		nReaderNo |=0x02;
	}else{
		nReaderNo &=0x0D;
	}	
}
//door3
void CSDK_DEMO_VCDlg::OnDoorCheck3() 
{
	BOOL m_bCheck=((CButton*)GetDlgItem(IDC_DOOR_CHECK3))->GetCheck();
	if(m_bCheck)
	{
		nReaderNo |=0x04;
	}else{
		nReaderNo &=0x0B;
	}	
}

void CSDK_DEMO_VCDlg::OnDoorCheck4() 
{
	BOOL m_bCheck=((CButton*)GetDlgItem(IDC_DOOR_CHECK4))->GetCheck();
	if(m_bCheck)
	{
		nReaderNo |=0x08;
	}else{
		nReaderNo &=0x07;
	}
}
//remote open the door
void CSDK_DEMO_VCDlg::OnButton16() 
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
	nRet = NET_CARD_RemoteOpen(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,nReaderNo,ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[22]);
	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[22],m_sReturnError);
	}
	
}
//remote Close the door
void CSDK_DEMO_VCDlg::OnButton17() 
{
	nRet = NET_CARD_RemoteClose(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,nReaderNo,ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[22]);
	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[22],m_sReturnError);
	}
	
}
//door distant open
void CSDK_DEMO_VCDlg::OnButton18() 
{
	// TODO: Add your control notification handler code here
	
}
//Restore the door state
void CSDK_DEMO_VCDlg::OnButton19() 
{
	// TODO: Add your control notification handler code here
	
}
//Set interlock
void CSDK_DEMO_VCDlg::OnButton22() 
{

	char MuxLock[5];
	CString m_sMuxLock;
	int m_iMuxLock=((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();
	m_sMuxLock=_T("00000000");
	switch(m_iMuxLock)
	{
		case 0: m_sMuxLock=_T("00000000");break;
		case 1: m_sMuxLock=_T("01010000");break;
		case 2: m_sMuxLock=_T("01000100");break;
		case 3: m_sMuxLock=_T("01000001");break;
		case 4: m_sMuxLock=_T("00010100");break;
		case 5: m_sMuxLock=_T("00010001");break;
		case 6: m_sMuxLock=_T("00000101");break;
		case 7: m_sMuxLock=_T("01010100");break;
		case 8: m_sMuxLock=_T("01010001");break;
		case 9: m_sMuxLock=_T("01000101");break;
		case 10: m_sMuxLock=_T("00010101");break;
		case 11: m_sMuxLock=_T("01010101");break;
	}
	//OLD MAC
	for(int kk=0;kk<m_sMuxLock.GetLength()/2;kk++)
	{
		sscanf( m_sMuxLock.Mid(2*kk,2), "%x", MuxLock+kk);
	}
	nRet = NET_CARD_SetInterLock(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,MuxLock,ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[24]);
	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[24],m_sReturnError);
	}

	
}
//Set lock delay
void CSDK_DEMO_VCDlg::OnButton23() 
{
	UpdateData(TRUE);	
	NET_CARD_OPEN_DELAY DoorDelay;
	DoorDelay.Door01DelayTime=m_nLockDelay;//lock 1 delay
	DoorDelay.Door02DelayTime=m_nLockDelay;//lock 2 delay
	DoorDelay.Door03DelayTime=m_nLockDelay;//lock 3 delay
	DoorDelay.Door04DelayTime=m_nLockDelay;//lock 4 delay
	nRet = NET_CARD_SetOpenDelayTime(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,&DoorDelay,ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[25]);
	}else{
		m_sReturnError.Format("%d",nRet);
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[25],m_sReturnError);
	}	
}
//Enable door overtime alarm
void CSDK_DEMO_VCDlg::OnDoorCheck11() 
{
	int nAlarm;
	BOOL m_bCheck=((CButton*)GetDlgItem(IDC_DOOR_CHECK11))->GetCheck();
	if(m_bCheck)
		nAlarm=nReaderNo;
	else
		nAlarm=0;
	nRet = NET_CARD_EnableTimeOutAlarm(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,nAlarm,ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[26]);
	}else{
		m_sReturnError.Format("%d",nRet);
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[26],m_sReturnError);
	}	
}
//set lock type
void CSDK_DEMO_VCDlg::OnButton24() 
{
	int nLockType;
	BOOL m_bCheck=((CButton*)GetDlgItem(IDC_RADIO6))->GetCheck();//电控锁
	if(m_bCheck)
		nLockType=nReaderNo;
	else
		nLockType=nReaderNo^0xff;
	nRet = NET_CARD_SetLockType(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,nLockType,ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[26]);
	}else{
		m_sReturnError.Format("%d",nRet);
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[26],m_sReturnError);
	}	
}
//set alarm out delay
void CSDK_DEMO_VCDlg::OnButton25() 
{
	UpdateData(TRUE);
	NET_CARD_ALARM_DELAY  AlarmDelay;
	AlarmDelay.Alarm01DelayTime=m_nAlarmOutDelay1;
	AlarmDelay.Alarm02DelayTime=m_nAlarmOutDelay2;
	AlarmDelay.Alarm03DelayTime=m_nAlarmOutDelay3;
	AlarmDelay.Alarm04DelayTime=m_nAlarmOutDelay4;

	nRet = NET_CARD_SetAlarmDelayTime(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,&AlarmDelay,ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[27]);
	}else{
		m_sReturnError.Format("%d",nRet);
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[27],m_sReturnError);
	}
	
}
//set password for 1-4 door, Each door 4 password 
void CSDK_DEMO_VCDlg::OnButton27() 
{
	CString m_sPassword;
	char Password[20];
	NET_CARD_DOORPASSWORD  DoorPassword;
	UpdateData(TRUE);
	m_sPassword1.TrimLeft();
	m_sPassword1.TrimRight();
	m_sPassword2.TrimLeft();
	m_sPassword2.TrimRight();
	m_sPassword3.TrimLeft();
	m_sPassword3.TrimRight();
	m_sPassword4.TrimLeft();
	m_sPassword4.TrimRight();
	//ffff==>NO password
	if( ((m_sPassword1.GetLength()!=4)&&(m_sPassword1.GetLength()!=0))||((m_sPassword2.GetLength()!=4)&&(m_sPassword2.GetLength()!=0))||\
		((m_sPassword3.GetLength()!=4)&&(m_sPassword3.GetLength()!=0))||((m_sPassword4.GetLength()!=4)&&(m_sPassword4.GetLength()!=0)))
	{
		AfxMessageBox(m_sStrOutputInfo[28]);
		return;
	}
	m_sPassword=m_sPassword1+m_sPassword2+m_sPassword3+m_sPassword4;

	for(int kk=0;kk<m_sPassword.GetLength()/2;kk++)
	{
		sscanf( m_sPassword.Mid(2*kk,2), "%x", Password+kk);
	}
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

	nRet = NET_CARD_SetDoorPassWord(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,&DoorPassword,ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[33]);
	}else{
		m_sReturnError.Format("%d",nRet);
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[33],m_sReturnError);
	}

}
//Set Magnetometer Out Delay and Druess Out Delay;
void CSDK_DEMO_VCDlg::OnButton26() 
{
	NET_CARD_LIGHT_DELAY  Light_Delay;
	UpdateData(TRUE);
	Light_Delay.LightOpenDelayTime	=30; //Magnetometer Out Delay
	Light_Delay.DruessDelayTime		=m_nDruessDelay;
	nRet = NET_CARD_SetDuressAlarmDelayTime(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,&Light_Delay,ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[29]);
	}else{
		m_sReturnError.Format("%d",nRet);
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[29],m_sReturnError);
	}
}
//Druess open door's password 
void CSDK_DEMO_VCDlg::OnButton31() 
{
	char Password[10];
	NET_CARD_DOORDURESSWORD  DruessPassword;

	UpdateData(TRUE);
	for(int kk=0;kk<m_sDruessPass.GetLength()/2;kk++)
	{
		sscanf(m_sDruessPass.Mid(2*kk,2), "%x", Password+kk);
	}
	//door 1
	DruessPassword.Door01Password[0]=Password[0]; 
	DruessPassword.Door01Password[1]=Password[1];
	//door 2
	DruessPassword.Door02Password[0]=Password[0];
	DruessPassword.Door02Password[1]=Password[1];
	//door 3
	DruessPassword.Door03Password[0]=Password[0];
	DruessPassword.Door03Password[1]=Password[1];
	//door 4
	DruessPassword.Door04Password[0]=Password[0];
	DruessPassword.Door04Password[1]=Password[1];

	nRet = NET_CARD_SetDoorDuressPassWord(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,&DruessPassword,ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[30]);
	}else{
		m_sReturnError.Format("%d",nRet);
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[30],m_sReturnError);
	}
}
//Get door state (door open or close)
void CSDK_DEMO_VCDlg::OnButton30() 
{

	NET_CARD_DOORSTATUS DoorStatus;
	nRet = NET_CARD_GetRunStatus(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,&DoorStatus,ReMACBuffer);
	if(nRet==0)
	{

		CString DoorCiStr;
		((CButton*)GetDlgItem(IDC_DOOR_CHECK12))->SetCheck(1);
		((CButton*)GetDlgItem(IDC_DOOR_CHECK13))->SetCheck(1);
		((CButton*)GetDlgItem(IDC_DOOR_CHECK14))->SetCheck(1);
		((CButton*)GetDlgItem(IDC_DOOR_CHECK15))->SetCheck(1);
		if(DoorStatus.m_iDoorCi &0x01)
		{
			DoorCiStr =" Door: Open";				
		}
		else
		{
			DoorCiStr =" Door: Close";
			((CButton*)GetDlgItem(IDC_DOOR_CHECK12))->SetCheck(0);	
		}
		if(DoorStatus.m_iDoorCi &0x02)
		{
			DoorCiStr +=" Open";
		}
		else
		{
			DoorCiStr +=" Close";
			((CButton*)GetDlgItem(IDC_DOOR_CHECK13))->SetCheck(0);	
		}
		if(DoorStatus.m_iDoorCi &0x04)
		{
			DoorCiStr +=" Open";
		}
		else
		{
			DoorCiStr +=" Close";
			((CButton*)GetDlgItem(IDC_DOOR_CHECK14))->SetCheck(0);
		}
		if(DoorStatus.m_iDoorCi &0x08)
		{
			DoorCiStr +=" Open";
		}
		else
		{
			DoorCiStr +=" Close";
			((CButton*)GetDlgItem(IDC_DOOR_CHECK15))->SetCheck(0);
		}

		CString OpenBtnStr;
		if(DoorStatus.m_iDoorCi &0x01)
		{
			OpenBtnStr =" BTN: Open";
		}
		else
		{
			OpenBtnStr =" BTN: Close";
		}
		if(DoorStatus.m_iDoorCi &0x02)
		{
			OpenBtnStr +=" Open";
		}
		else
		{
			OpenBtnStr +=" Close";			
		}
		if(DoorStatus.m_iDoorCi &0x04)
		{
			OpenBtnStr +=" Open";
		}
		else
		{
			OpenBtnStr +=" Close";
		}
		if(DoorStatus.m_iDoorCi &0x08)
		{
			OpenBtnStr +=" Open";
		}
		else
		{
			OpenBtnStr +=" Close";
		}

		CString InputStr;
		if(DoorStatus.m_iDoorCi &0x01)
			InputStr =" Input: Open";
		else
			InputStr =" Input: Close";
		if(DoorStatus.m_iDoorCi &0x02)
			InputStr +=" Open";
		else
			InputStr +=" Close";			
		if(DoorStatus.m_iDoorCi &0x04)
			InputStr +=" Open";
		else
			InputStr +=" Close";
		if(DoorStatus.m_iDoorCi &0x08)
			InputStr +=" Open";
		else
			InputStr +=" Close";

		CString HistoryRecordStr;
		HistoryRecordStr.Format("HistoryRecord Num.=%d",DoorStatus.m_iDisOnlineCardNums);
		CString RealRecordStr;
		RealRecordStr.Format("RealRecord Num.=%d",DoorStatus.m_iRealCardNums);

		CString TempCardNumStr;
		TempCardNumStr.Format("TempCard Num.=%d",DoorStatus.m_iCardNumTemp);
		CString SortCardNumStr;
		SortCardNumStr.Format("SortCard Num.=%d",DoorStatus.m_iCardNumSort);

		CString OutPutStr;
		OutPutStr =DoorCiStr+"\r\n";
		OutPutStr +=OpenBtnStr+"\r\n";
		OutPutStr +=InputStr+"\r\n";
		OutPutStr +=HistoryRecordStr+"\r\n";
		OutPutStr +=RealRecordStr+"\r\n";
		OutPutStr +=TempCardNumStr+"\r\n";
		OutPutStr +=SortCardNumStr+"\r\n";
		
		DisplayInfoforRecieve(OutPutStr);

	}else{
		m_sReturnError.Format("%d",nRet);
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[30],m_sReturnError);
	}
	
}
//door 1 have open access
//0xF0 The lower four bits 0000 --> Left to right  1st bit door4 .. 4th bit door 1(0 Yes 1 NO)
//0xF3 The lower four bits 0011 --> door 1,2 Yes  3,4 NO
void CSDK_DEMO_VCDlg::OnDoorCheck5() 
{
	BOOL m_bCheck=((CButton*)GetDlgItem(IDC_DOOR_CHECK5))->GetCheck();
	if(!m_bCheck)
	{
		nReaderRight |=0x01;
	}else{
		nReaderRight ^= (0x01<<0);
	}
	
}
//door 2 have open access
void CSDK_DEMO_VCDlg::OnDoorCheck6() 
{
	BOOL m_bCheck=((CButton*)GetDlgItem(IDC_DOOR_CHECK6))->GetCheck();
	if(!m_bCheck)
	{
		nReaderRight |=0x02;
	}else{
		nReaderRight ^= (0x01<<1);
	}	
}
//door 3 have open access
void CSDK_DEMO_VCDlg::OnDoorCheck7() 
{
	BOOL m_bCheck=((CButton*)GetDlgItem(IDC_DOOR_CHECK7))->GetCheck();
	if(!m_bCheck)
	{
		nReaderRight |=0x04;
	}else{
		nReaderRight ^= (0x01<<2);
	}
}
//door 4 have open access
void CSDK_DEMO_VCDlg::OnDoorCheck8() 
{
	BOOL m_bCheck=((CButton*)GetDlgItem(IDC_DOOR_CHECK8))->GetCheck();
	if(!m_bCheck)
	{
		nReaderRight |=0x08;
	}else{
		nReaderRight ^= (0x01<<3);
	}
	
}
//card open
void CSDK_DEMO_VCDlg::OnDoorCheck9() 
{
	BOOL m_bCheck=((CButton*)GetDlgItem(IDC_DOOR_CHECK9))->GetCheck();
	if(m_bCheck)
	{
		PassType=0;
	}else{
		PassType=1;
	}
}

void CSDK_DEMO_VCDlg::OnDoorCheck10() 
{
	BOOL m_bCheck=((CButton*)GetDlgItem(IDC_DOOR_CHECK9))->GetCheck();
	if(m_bCheck)
	{
		PassType=1;
	}else{
		PassType=0;
	}	
}

void CSDK_DEMO_VCDlg::OnRadio1() 
{
	BOOL m_bCheck=((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck();
	if(m_bCheck)
	{
		OpenType=0;
	}
		
}

void CSDK_DEMO_VCDlg::OnRadio2() 
{
	BOOL m_bCheck=((CButton*)GetDlgItem(IDC_RADIO2))->GetCheck();
	if(m_bCheck)
	{
		OpenType=1;
	}
	
}

void CSDK_DEMO_VCDlg::OnRadio3() 
{
	BOOL m_bCheck=((CButton*)GetDlgItem(IDC_RADIO3))->GetCheck();
	if(m_bCheck)
	{
		OpenType=2;
	}
	
}

void CSDK_DEMO_VCDlg::OnRadio4() 
{
	BOOL m_bCheck=((CButton*)GetDlgItem(IDC_RADIO4))->GetCheck();
	if(m_bCheck)
	{
		OpenType=3;
	}	
}
//Download a card to a temporary district
void CSDK_DEMO_VCDlg::OnButton12() 
{
	CString m_sTempStr;
	char cTmp[20];
	NET_CARD_ONECARDINFO  OneCardInfo;
	memset(&OneCardInfo,0xff,sizeof(NET_CARD_ONECARDINFO));

	//card series
	((CEdit*)GetDlgItem(IDC_EDIT_CARDSERIES))->GetWindowText(m_sTempStr);
	if(m_sTempStr.GetLength()!=8)
		return;
	for(int kk=0;kk<m_sTempStr.GetLength()/2;kk++)
	{
		sscanf(m_sTempStr.Mid(2*kk,2), "%x", cTmp+kk);
	}

	unsigned int  uCardID=0;
	sscanf(m_sTempStr,"%x", &uCardID);

	cTmp[0]=uCardID>>24;
	cTmp[1]=uCardID>>16;
	cTmp[2]=uCardID>>8;
	cTmp[3]=uCardID&0x00ff;
	uCardID++;
	m_sTempStr.Format("%08x",uCardID);
	((CEdit*)GetDlgItem(IDC_EDIT_CARDSERIES))->SetWindowText(m_sTempStr);
	theApp.CurCardIDStr = m_sTempStr;



	memcpy(OneCardInfo.CardID,cTmp,4);
	//OpenType
	OneCardInfo.OpenType=OpenType;
	//pass password for door1
	((CEdit*)GetDlgItem(IDC_EDIT_OPENPASSWORD))->GetWindowText(m_sTempStr);
	if(m_sTempStr.GetLength()!=4)
		return;
	for(kk=0;kk<m_sTempStr.GetLength()/2;kk++)
	{
		sscanf(m_sTempStr.Mid(2*kk,2), "%x", cTmp+kk);
	}
	memcpy(OneCardInfo.Door01Password,cTmp,2);
	//door1 ==>door2 door3 door4 
	memcpy(OneCardInfo.Door02Password,OneCardInfo.Door01Password,2);
	memcpy(OneCardInfo.Door03Password,OneCardInfo.Door01Password,2);
	memcpy(OneCardInfo.Door04Password,OneCardInfo.Door01Password,2);

	//Enable the card's  period of validity
	BOOL m_bCheck=((CButton*)GetDlgItem(IDC_DOOR_CHECK16))->GetCheck();
	if(m_bCheck)
	{
		((CEdit*)GetDlgItem(IDC_EDIT_ENDDATE))->GetWindowText(m_sTempStr);
		if(m_sTempStr.GetLength()!=6)
			return;
		for(kk=0;kk<m_sTempStr.GetLength()/2;kk++)
		{
			sscanf(m_sTempStr.Mid(2*kk,2), "%x", cTmp+kk);
		}
		OneCardInfo.EndYear	=cTmp[0];
		OneCardInfo.EndMonth=cTmp[1];
		OneCardInfo.EndDay	=cTmp[2];
		OneCardInfo.CardStatus =0x02;//Enable card's validity
	}
	else
	{
		OneCardInfo.CardStatus =0x00;
	}	
	OneCardInfo.OpenDoorType			= OpenType;
	OneCardInfo.OpenWhichDoor			= nReaderRight;
	OneCardInfo.WeekAndHolidayCode[0]	= 0x00;
	OneCardInfo.WeekAndHolidayCode[1]	= 0x00;
	OneCardInfo.WeekAndHolidayCode[2]	= 0x00;
	OneCardInfo.WeekAndHolidayCode[3]	= 0x00;

	nRet = NET_CARD_DownOneCardInfo(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,&OneCardInfo,sizeof(NET_CARD_ONECARDINFO),ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[31]);
	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[30],m_sReturnError);
	}

}
//delete a card 
void CSDK_DEMO_VCDlg::OnButton13() 
{
	CString m_sTempStr;
	char cTmp[20];
	NET_CARD_ONECARDINFO  OneCardInfo;
	memset(&OneCardInfo,0xff,sizeof(NET_CARD_ONECARDINFO));

	//card series
	((CEdit*)GetDlgItem(IDC_EDIT_CARDSERIES))->GetWindowText(m_sTempStr);
	if(m_sTempStr.GetLength()!=8)
		return;
	for(int kk=0;kk<m_sTempStr.GetLength()/2;kk++)
	{
		sscanf(m_sTempStr.Mid(2*kk,2), "%x", cTmp+kk);
	}
	memcpy(OneCardInfo.CardID,cTmp,4);
	//OpenType
	OneCardInfo.OpenType=OpenType;
	//pass password for door1
	((CEdit*)GetDlgItem(IDC_EDIT_OPENPASSWORD))->GetWindowText(m_sTempStr);
	if(m_sTempStr.GetLength()!=4)
		return;
	for(kk=0;kk<m_sTempStr.GetLength()/2;kk++)
	{
		sscanf(m_sTempStr.Mid(2*kk,2), "%x", cTmp+kk);
	}
	memcpy(OneCardInfo.Door01Password,cTmp,2);
	//door1 ==>door2 door3 door4 
	memcpy(OneCardInfo.Door02Password,OneCardInfo.Door01Password,2);
	memcpy(OneCardInfo.Door03Password,OneCardInfo.Door01Password,2);
	memcpy(OneCardInfo.Door04Password,OneCardInfo.Door01Password,2);

	//Enable the card's  period of validity
	BOOL m_bCheck=((CButton*)GetDlgItem(IDC_DOOR_CHECK16))->GetCheck();
	if(m_bCheck)
	{
		((CEdit*)GetDlgItem(IDC_EDIT_ENDDATE))->GetWindowText(m_sTempStr);
		if(m_sTempStr.GetLength()!=6)
			return;
		for(kk=0;kk<m_sTempStr.GetLength()/2;kk++)
		{
			sscanf(m_sTempStr.Mid(2*kk,2), "%x", cTmp+kk);
		}
		OneCardInfo.EndYear	=cTmp[0];
		OneCardInfo.EndMonth=cTmp[1];
		OneCardInfo.EndDay	=cTmp[2];
		OneCardInfo.CardStatus =0x02;//Enable card's validity
	}

	OneCardInfo.CardStatus =0x03;//card's status is 0x03 
	
	OneCardInfo.OpenDoorType			= OpenType;
	OneCardInfo.OpenWhichDoor			= nReaderRight;
	OneCardInfo.WeekAndHolidayCode[0]	= 0x00;

	nRet = NET_CARD_DownOneCardInfo(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,&OneCardInfo,sizeof(NET_CARD_ONECARDINFO),ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[31]);
	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[31],m_sReturnError);
	}
	
}
//Clear all card 
//Before batch download cards, must clear all card;
void CSDK_DEMO_VCDlg::OnButton14() 
{
	nRet = NET_CARD_ClearAllCardInfo(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[32]);
	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[32],m_sReturnError);
	}	
}
//Get a card infomation from device
void CSDK_DEMO_VCDlg::OnButton20() 
{
	char cCardID[5];
	CString m_sTempStr;
	NET_CARD_ONECARDINFO  OneCardInfo;
	memset(&OneCardInfo,0xff,sizeof(NET_CARD_ONECARDINFO));

	
	//card series
	((CEdit*)GetDlgItem(IDC_EDIT_CARDSERIES))->GetWindowText(m_sTempStr);
	if(m_sTempStr.GetLength()!=8)
		return;
	for(int kk=0;kk<m_sTempStr.GetLength()/2;kk++)
	{
		sscanf(m_sTempStr.Mid(2*kk,2), "%x", cCardID+kk);
	}

	nRet = NET_CARD_GetOneCardInfo(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,cCardID,&OneCardInfo,ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[34]);
		CString strTmp1,CardSeriesStr,OpenTypeStr,CardEndDateStr,CardStatusStr;
		CString OpenDoorTypeStr,OpenWhichDoorStr,WeekAndHolidayCodeStr;

		CardSeriesStr.Format("%02X%02X%02X%02X",OneCardInfo.CardID[0],OneCardInfo.CardID[1],OneCardInfo.CardID[2],OneCardInfo.CardID[3]);//得到卡号
		if(OneCardInfo.OpenType==0x00)
			OpenTypeStr="卡";
		else
			OpenTypeStr="卡+密码";

		CardEndDateStr.Format("%02X%02X%02X",OneCardInfo.EndYear,OneCardInfo.EndMonth,OneCardInfo.EndDay);
		if(CardEndDateStr=="FFFFFF")
			CardEndDateStr="卡无期限";

		CardStatusStr.Format("%02X",OneCardInfo.CardStatus);
		if(CardStatusStr=="00")
			CardStatusStr="正常卡";
		else if(CardStatusStr=="02")
			CardStatusStr="期限限制卡";
		else if(CardStatusStr=="03")
			CardStatusStr="此卡已删除";

		OpenDoorTypeStr.Format("%02X",OneCardInfo.OpenDoorType);
		if(OpenDoorTypeStr=="00")
			OpenDoorTypeStr="单卡通行";
		else if(OpenDoorTypeStr=="01")
			OpenDoorTypeStr="双卡通行";

		if((OneCardInfo.OpenWhichDoor&0x0E)==0)
			OpenWhichDoorStr+="门1";
		if((OneCardInfo.OpenWhichDoor&0x0D)==0)
			OpenWhichDoorStr+="门2";
		if((OneCardInfo.OpenWhichDoor&0x0B)==0)
			OpenWhichDoorStr+="门3";
		if((OneCardInfo.OpenWhichDoor&0x07)==0)
			OpenWhichDoorStr+="门4";


		WeekAndHolidayCodeStr.Format("%02X,%02X,%02X,%02X",OneCardInfo.WeekAndHolidayCode[0],OneCardInfo.WeekAndHolidayCode[1],OneCardInfo.WeekAndHolidayCode[2],OneCardInfo.WeekAndHolidayCode[3]);


		
		strTmp1+="卡号:"+ CardSeriesStr+"\r\n";
		strTmp1+="开门方式(卡或卡+密码):"+ OpenTypeStr+"\r\n";
		strTmp1+="结止有效期:"+ CardEndDateStr+"\r\n";
		strTmp1+="卡状态:"+ CardStatusStr+"\r\n";
		strTmp1+="通行方式:"+ OpenDoorTypeStr+"\r\n";
		strTmp1+="开门哪些门:"+ OpenWhichDoorStr+"\r\n";
		strTmp1+="周编程假日编程号:"+ WeekAndHolidayCodeStr+"\r\n";



		DisplayInfoforRecieve(strTmp1);





	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[34],m_sReturnError);
	}
	
}
//Download administrator card
void CSDK_DEMO_VCDlg::OnButton21() 
{
	// TODO: Add your control notification handler code here
	
}
//download batch cards 
void CSDK_DEMO_VCDlg::OnButton15() 
{
//1)Get all cards Series
//2)Sort all cards Series (from small to big)
//3)Clear all card
//4)Download all the cards (8 cards,16 cards 32cards a group)

	//1)Get all cards Series
	CDlgEditBatchDownLoadCard Dlg;
	if(Dlg.DoModal() != IDOK)
		return;

	//2)Sort all cards Series (from small to big)
	Qsortcai(theApp.nCardArray,0,40-1);

	nRet = NET_CARD_ClearAllCardInfo(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[32]);
	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[32],m_sReturnError);
		return;
	}

	//Get a card Info
	//////////////////////////////////////////////////////
	CString m_sTempStr;
	char cTmp[100];
	NET_CARD_ONECARDINFO  OneCardInfo;
	memset(&OneCardInfo,0xff,sizeof(NET_CARD_ONECARDINFO));

	//card series
	((CEdit*)GetDlgItem(IDC_EDIT_CARDSERIES))->GetWindowText(m_sTempStr);
	if(m_sTempStr.GetLength()!=8)
		return;
	for(int kk=0;kk<m_sTempStr.GetLength()/2;kk++)
	{
		sscanf(m_sTempStr.Mid(2*kk,2), "%x", cTmp+kk);
	}
	memcpy(OneCardInfo.CardID,cTmp,4);
	//OpenType
	OneCardInfo.OpenType=OpenType;
	//pass password for door1
	((CEdit*)GetDlgItem(IDC_EDIT_OPENPASSWORD))->GetWindowText(m_sTempStr);
	if(m_sTempStr.GetLength()!=4)
		return;
	for(kk=0;kk<m_sTempStr.GetLength()/2;kk++)
	{
		sscanf(m_sTempStr.Mid(2*kk,2), "%x", cTmp+kk);
	}
	memcpy(OneCardInfo.Door01Password,cTmp,2);
	//door1 ==>door2 door3 door4 
	memcpy(OneCardInfo.Door02Password,OneCardInfo.Door01Password,2);
	memcpy(OneCardInfo.Door03Password,OneCardInfo.Door01Password,2);
	memcpy(OneCardInfo.Door04Password,OneCardInfo.Door01Password,2);

	//Enable the card's  period of validity
	BOOL m_bCheck=((CButton*)GetDlgItem(IDC_DOOR_CHECK16))->GetCheck();
	if(m_bCheck)
	{
		((CEdit*)GetDlgItem(IDC_EDIT_ENDDATE))->GetWindowText(m_sTempStr);
		if(m_sTempStr.GetLength()!=6)
			return;
		for(kk=0;kk<m_sTempStr.GetLength()/2;kk++)
		{
			sscanf(m_sTempStr.Mid(2*kk,2), "%x", cTmp+kk);
		}
		OneCardInfo.EndYear	=cTmp[0];
		OneCardInfo.EndMonth=cTmp[1];
		OneCardInfo.EndDay	=cTmp[2];
		OneCardInfo.CardStatus =0x02;//Enable card's validity
	}
	else
	{
		OneCardInfo.CardStatus =0x00;
	}	
	OneCardInfo.OpenDoorType			= OpenType;
	OneCardInfo.OpenWhichDoor			= nReaderRight;
	OneCardInfo.WeekAndHolidayCode[0]	= 0x00;
	OneCardInfo.WeekAndHolidayCode[1]	= 0x00;
	OneCardInfo.WeekAndHolidayCode[2]	= 0x00;
	OneCardInfo.WeekAndHolidayCode[3]	= 0x00;


	NET_CARD_ONECARDINFO  AllCardsInfo[40];
	for(kk=0;kk<40;kk++)
	{
		memcpy(&AllCardsInfo[kk],&OneCardInfo,sizeof(NET_CARD_ONECARDINFO));
		cTmp[0]=theApp.nCardArray[kk]>>24;
		cTmp[1]=theApp.nCardArray[kk]>>16;
		cTmp[2]=theApp.nCardArray[kk]>>8;
		cTmp[3]=theApp.nCardArray[kk]&0x00ff;
		memcpy(AllCardsInfo[kk].CardID,cTmp,4);
	}

//	NET_CARD_BatchDownCardInfo(int DevType,char *szRemoteIP, int nRemotePort,NET_CARD_ONECARDINFO *pALLCardInfo,int ALLCardInfoLength,int nCardNo,char *pReturnDevMAC)
	////////////////////////////////////////////////
	for(int ii=0;ii<40/16;ii++)
	{
		nRet = NET_CARD_BatchDownCardInfo(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,&AllCardsInfo[ii*16],sizeof(NET_CARD_ONECARDINFO)*16,ii*16,16,ReMACBuffer);
		if(nRet==0)
		{
			AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[35]);
		}else{
			
			if((nRet>0)&&(nRet<13))
				m_sReturnError.Format("%d",theApp.m_sCommandState[nRet]);	
			else
				m_sReturnError.Format("%d",nRet);	
			AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[35],m_sReturnError);
			return;
		}
	}
	int nRestcards=40%16;

	nRet = NET_CARD_BatchDownCardInfo(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,&AllCardsInfo[ii*16],sizeof(NET_CARD_ONECARDINFO)*nRestcards,ii*16,nRestcards,ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[35]);
	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[35],m_sReturnError);
		return;
	}

}


void CSDK_DEMO_VCDlg::Qsortcai(unsigned int a[], int left, int right)
{
 //CString tmpstr,tmpstr1;
  unsigned int pivot,temp;
  int l,r;
  l=left;r=right;
  pivot=a[(left+right)/2];
  while(l<=r)
  {
	  while(a[l]<pivot)++l;
	  while(a[r]>pivot)--r;
	  if(l>=r)break;     
	  temp=a[l]; 
//	  tmpstr=APP->filefullnamearray_cai->GetAt(l);
//	  tmpstr1=APP->filefullnamearray_cai->GetAt(l);

	  a[l]=a[r]; 
	  //APP->filefullnamearray_cai->SetAt(l,APP->filefullnamearray_cai->GetAt(r));
	  //APP->filefullnamearray_cai->SetAt(l,APP->filefullnamearray_cai->GetAt(r));

	  a[r]=temp; 
	  //APP->filefullnamearray_cai->SetAt(r,tmpstr);
	  //APP->filefullnamearray_cai->SetAt(r,tmpstr1);

	  ++l;--r;
  }
  if(l==r)l++;
  if(left<r)Qsortcai(a,left,l-1);
  if(l<right)Qsortcai(a,r+1,right);
}
//设备升级
void CSDK_DEMO_VCDlg::OnButton9() 
{
/*
	//升级下载工具
	CString		sExcelFile;
	CString     strFilter;
	strFilter  = "Excel Files (*.bin)|*.bin|";

	CFileDialog fileDlg (FALSE, NULL, NULL,OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, strFilter,this);
	#ifndef ENGLISHC	
	fileDlg.m_ofn.lpstrTitle = "选择升级文件";
	#else
	fileDlg.m_ofn.lpstrTitle = "Select Update File";
	#endif
	if( fileDlg.DoModal()==IDOK)
	{
		sExcelFile = fileDlg.GetPathName();    // 要建立的Excel文件
		sExcelFile.TrimLeft();
		sExcelFile.TrimRight();
		if(sExcelFile.GetLength()==0)
		   return;
		CFileFind finder;
		BOOL bWorking = finder.FindFile(sExcelFile);//寻找文件
		if (!bWorking)//如果已经存在文件,则删除
		{
			AfxMessageBox("文件名不存在");
			return;
		}
		APP->AutoUpdateFileStr =sExcelFile;
		
	}
#ifndef ENGLISHC
	if(IDOK!=AfxMessageBox("警告！再一次确认是否升级？\n升级文件名："+APP->AutoUpdateFileStr,MB_OKCANCEL|MB_DEFBUTTON1))
#else
	if(IDOK!=AfxMessageBox("Warning! Once again confirm the upgrade\nUpgrade file name："+APP->AutoUpdateFileStr,MB_OKCANCEL|MB_DEFBUTTON1))
#endif
	{
		APP->AutoUpdateFileStr =_T("");
		m_iCurBTNPush=-1;
		APP->m_bHaveExitUpdate=FALSE;
		return;	
	}
	APP->m_bHaveExitUpdate=TRUE;
	lpMainFrame->StartCardRightDistribute(1);
*/
}
UINT CSDK_DEMO_VCDlg::RevThreadProc(LPVOID pParam)
{

	return 0;
}
//设置 身份证二维码上传的服务器软件UDP IP、Port
void CSDK_DEMO_VCDlg::OnButton33() 
{
	int	  nServerPort;
	char  ServerIP[5];
	CString m_sServerIP,m_sServerPort;
	
	((CEdit*)GetDlgItem(IDC_EDIT_LOCALPORT2))->GetWindowText(m_sServerIP);
	m_sServerIP.TrimLeft();
	m_sServerIP.TrimRight();
	
	((CEdit*)GetDlgItem(IDC_EDIT_LOCALPORT3))->GetWindowText(m_sServerPort);
	m_sServerPort.TrimLeft();
	m_sServerPort.TrimRight();

	nServerPort =atoi(m_sServerPort);

	
	theApp.TransIPfromCStringtoBYTE(m_sServerIP,(unsigned char*)ServerIP);
	nRet = NET_CARD_Set_QR_ServerUDPIPAndPort(DEVICE_NET_ACCESS,DeviceIP, nDevicePort,ServerIP,nServerPort,ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[19]);

	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[19],m_sReturnError);
	}
	

}

void CSDK_DEMO_VCDlg::OnButton34() 
{
	int	  nServerPort;
	char  ServerIP[5];
	CString m_sServerIP,m_sServerPort;
	
	((CEdit*)GetDlgItem(IDC_EDIT_LOCALPORT4))->GetWindowText(m_sServerIP);
	m_sServerIP.TrimLeft();
	m_sServerIP.TrimRight();
	
	((CEdit*)GetDlgItem(IDC_EDIT_LOCALPORT5))->GetWindowText(m_sServerPort);
	m_sServerPort.TrimLeft();
	m_sServerPort.TrimRight();

	nServerPort =atoi(m_sServerPort);

	
	theApp.TransIPfromCStringtoBYTE(m_sServerIP,(unsigned char*)ServerIP);
	nRet = NET_CARD_Set_RecordUpLoad_UDPIPAndPort(DEVICE_NET_ACCESS,DeviceIP, nDevicePort,ServerIP,nServerPort,ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[19]);

	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[19],m_sReturnError);
	}	
}

void CSDK_DEMO_VCDlg::OnButton35() 
{

	int	  nServerPort;
	char  ServerIP[5];
	CString m_sServerIP,m_sServerPort;
	
	((CEdit*)GetDlgItem(IDC_EDIT_LOCALPORT6))->GetWindowText(m_sServerIP);
	m_sServerIP.TrimLeft();
	m_sServerIP.TrimRight();
	
	((CEdit*)GetDlgItem(IDC_EDIT_LOCALPORT7))->GetWindowText(m_sServerPort);
	m_sServerPort.TrimLeft();
	m_sServerPort.TrimRight();

	nServerPort =atoi(m_sServerPort);

	
	theApp.TransIPfromCStringtoBYTE(m_sServerIP,(unsigned char*)ServerIP);
	nRet = NET_CARD_Set_QR_ServerTCPIPAndPort(DEVICE_NET_ACCESS,DeviceIP, nDevicePort,ServerIP,nServerPort,ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[19]);

	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[19],m_sReturnError);
	}

	

}
//得到上传服务器参数表
void CSDK_DEMO_VCDlg::OnButton36() 
{
	int   nRetLen=0;
	char  RetChar[50];
	int   nPos=0;
	int   nPort=0,nPort2=0;
	CString strTmpStr,strTmp1;
	nRet = NET_CARD_Get_ALLServerIPandPort(DEVICE_NET_ACCESS,DeviceIP,nDevicePort, RetChar,&nRetLen,ReMACBuffer);
	if(nRetLen==18)
	{
		
		nPort = 0x00;
		nPort |= (unsigned char)RetChar[4];
		nPort <<= 8;
		nPort |= (unsigned char)RetChar[5];

		nPos=0;
		strTmpStr.Format("TCP server IP:		%d.%d.%d.%d Port=%d",(unsigned char)RetChar[nPos],(unsigned char)RetChar[nPos+1],(unsigned char)RetChar[nPos+2],(unsigned char)RetChar[nPos+3],nPort);
		strTmp1 +=strTmpStr+"\r\n";
		nPos=6;
		nPort = 0x00;
		nPort |= (unsigned char)RetChar[nPos+4];
		nPort <<= 8;
		nPort |= (unsigned char)RetChar[nPos+5];
		strTmpStr.Format("QR UDP Server IP:	%d.%d.%d.%d Port=%d",(unsigned char)RetChar[nPos],(unsigned char)RetChar[nPos+1],(unsigned char)RetChar[nPos+2],(unsigned char)RetChar[nPos+3],nPort);
		strTmp1 +=strTmpStr+"\r\n";
		nPos=12;
		nPort = 0x00;
		nPort |= (unsigned char)RetChar[nPos+4];
		nPort <<= 8;
		nPort |= (unsigned char)RetChar[nPos+5];
		strTmpStr.Format("Record UDP server IP:	%d.%d.%d.%d Port=%d",(unsigned char)RetChar[nPos],(unsigned char)RetChar[nPos+1],(unsigned char)RetChar[nPos+2],(unsigned char)RetChar[nPos+3],nPort);
		strTmp1 +=strTmpStr+"\r\n";

		DisplayInfoforRecieve(strTmp1);

	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[17],m_sReturnError);
	}
	
}
//语音输出+开门
void CSDK_DEMO_VCDlg::OnButton37() 
{
	int  VoiceLength=0;
	char VoiceTmp[40];
	CString m_sTempStr;
	((CEdit*)GetDlgItem(IDC_EDIT_OUTDELAY5))->GetWindowText(m_sTempStr);
	if(m_sTempStr.GetLength()<2)
	{
#ifdef ENGLISH
		AfxMessageBox("Please Input Audio Code");
#else
		AfxMessageBox("请输入语音代码");
#endif
		return;
	}
	m_sTempStr.TrimLeft();
	m_sTempStr.TrimRight();

	VoiceLength = m_sTempStr.GetLength()/2;
	for(int kk=0;kk<VoiceLength;kk++)
	{
		sscanf(m_sTempStr.Mid(2*kk,2), "%x", VoiceTmp+kk);
	}

	int nbOpenDoor=1;
	int nReaderNo=1;

	nRet = NET_CARD_VoiceAndOpen(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,VoiceTmp,VoiceLength,nbOpenDoor,nReaderNo,ReMACBuffer);
	
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[36]);
	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[36],m_sReturnError);
	}
	

	
}

void CSDK_DEMO_VCDlg::OnButton40() 
{
	int  VoiceLength=0;
	char VoiceTmp[40];
	CString m_sTempStr;
	((CEdit*)GetDlgItem(IDC_EDIT_OUTDELAY5))->GetWindowText(m_sTempStr);
	if(m_sTempStr.GetLength()<2)
	{
#ifdef ENGLISH
		AfxMessageBox("Please Input Audio Code");
#else
		AfxMessageBox("请输入语音代码");
#endif
		return;
	}
	m_sTempStr.TrimLeft();
	m_sTempStr.TrimRight();

	VoiceLength = m_sTempStr.GetLength()/2;
	for(int kk=0;kk<VoiceLength;kk++)
	{
		sscanf(m_sTempStr.Mid(2*kk,2), "%x", VoiceTmp+kk);
	}

	int nbOpenDoor=1;
	int nReaderNo=1;

	nRet = NET_CARD_VoiceAndOpen(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,VoiceTmp,VoiceLength,0,nReaderNo,ReMACBuffer);
	
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[36]);
	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[36],m_sReturnError);
	}
	
	
}
BOOL CSDK_DEMO_VCDlg::ShowPicJPG(void *src, DWORD size)
{
	CString lpstrFile;	
	int nScrWidth,nScrHeight;
	IStream  *pStm  = NULL; 
	IPicture *pPic  = NULL; 
	BOOL bResult; 
	DWORD dwFileSize; 
	CString   modifyDiskStr,tempstr;
	BOOL	Find=FALSE;
	CRect rectBJP;

    m_cOriPicStatic.GetClientRect(&rectBJP);   
	nScrWidth=rectBJP.Width();//  SnapRect[view].Width();
	nScrHeight=rectBJP.Height();

	dwFileSize =size;
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, dwFileSize);  
	LPVOID pvData = NULL; 

	if (hGlobal == NULL) 
	{
		return E_FAIL; 
	}
	
	if ((pvData = GlobalLock(hGlobal)) == NULL)//锁定分配内存块 
	{
		return E_FAIL; 
	}
	memcpy(pvData,src,dwFileSize);	
	GlobalUnlock(hGlobal); 
	CreateStreamOnHGlobal(hGlobal, TRUE, &pStm); 		
	//装入图形文件 
	bResult=OleLoadPicture(pStm,dwFileSize,TRUE,IID_IPicture,(LPVOID*)&pPic); 
	
	if(FAILED(bResult)) 
	{
		return E_FAIL; 
	}

	GlobalFree(hGlobal);
	FreeResource(hGlobal); 	

	OLE_XSIZE_HIMETRIC hmWidth;//图片的真实宽度 
	OLE_YSIZE_HIMETRIC hmHeight;//图片的真实高度 
	pPic->get_Width(&hmWidth); 
	pPic->get_Height(&hmHeight); 
	
	HDC		hDC_TempSQLJPG;
	HWND    m_hWndSQLJPG;

	m_hWndSQLJPG = m_cOriPicStatic.GetSafeHwnd();
	hDC_TempSQLJPG=::GetDC(m_hWndSQLJPG); 

	//将图形输出到屏幕上（有点像BitBlt） 
	bResult=pPic->Render(hDC_TempSQLJPG,0,0,nScrWidth,nScrHeight,0,hmHeight,hmWidth,-hmHeight,NULL); 
	
	pPic->Release(); 	
	pStm->Release(); 
	pStm=NULL;

	::ReleaseDC(m_hWndSQLJPG,hDC_TempSQLJPG);
	if (SUCCEEDED(bResult)) 
	{ 
		return S_OK; 
	} 
	else 
	{ 
		return E_FAIL; 
	} 
}
//批量下载1万张卡
void CSDK_DEMO_VCDlg::OnButton32() 
{
	//1)Get all cards Series
	CString m_sTempStr,strTmp2,strTmp1;
	int nMaxCardNum=10000;

	//Get First CardNum
	((CEdit*)GetDlgItem(IDC_EDIT_CARDSERIES))->GetWindowText(m_sTempStr);
	if(m_sTempStr.GetLength()!=8)
		return;

	unsigned int  uCardID=0;
	sscanf(m_sTempStr,"%x", &uCardID);

	//先清除所有卡
	nRet = NET_CARD_ClearAllCardInfo(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[32]);
	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[32],m_sReturnError);
		return;
	}

	//Get a card Info
	//////////////////////////////////////////////////////
//	CString m_sTempStr;
	char cTmp[100];
	NET_CARD_ONECARDINFO  OneCardInfo;
	memset(&OneCardInfo,0xff,sizeof(NET_CARD_ONECARDINFO));

	//card series
	((CEdit*)GetDlgItem(IDC_EDIT_CARDSERIES))->GetWindowText(m_sTempStr);
	if(m_sTempStr.GetLength()!=8)
		return;
	for(int kk=0;kk<m_sTempStr.GetLength()/2;kk++)
	{
		sscanf(m_sTempStr.Mid(2*kk,2), "%x", cTmp+kk);
	}
	memcpy(OneCardInfo.CardID,cTmp,4);
	//OpenType
	OneCardInfo.OpenType=OpenType;
	//pass password for door1
	((CEdit*)GetDlgItem(IDC_EDIT_OPENPASSWORD))->GetWindowText(m_sTempStr);
	if(m_sTempStr.GetLength()!=4)
		return;
	for(kk=0;kk<m_sTempStr.GetLength()/2;kk++)
	{
		sscanf(m_sTempStr.Mid(2*kk,2), "%x", cTmp+kk);
	}
	memcpy(OneCardInfo.Door01Password,cTmp,2);
	//door1 ==>door2 door3 door4 
	memcpy(OneCardInfo.Door02Password,OneCardInfo.Door01Password,2);
	memcpy(OneCardInfo.Door03Password,OneCardInfo.Door01Password,2);
	memcpy(OneCardInfo.Door04Password,OneCardInfo.Door01Password,2);

	//Enable the card's  period of validity
	BOOL m_bCheck=((CButton*)GetDlgItem(IDC_DOOR_CHECK16))->GetCheck();
	if(m_bCheck)
	{
		((CEdit*)GetDlgItem(IDC_EDIT_ENDDATE))->GetWindowText(m_sTempStr);
		if(m_sTempStr.GetLength()!=6)
			return;
		for(kk=0;kk<m_sTempStr.GetLength()/2;kk++)
		{
			sscanf(m_sTempStr.Mid(2*kk,2), "%x", cTmp+kk);
		}
		OneCardInfo.EndYear	=cTmp[0];
		OneCardInfo.EndMonth=cTmp[1];
		OneCardInfo.EndDay	=cTmp[2];
		OneCardInfo.CardStatus =0x02;//Enable card's validity
	}
	else
	{
		OneCardInfo.CardStatus =0x00;
	}	
	OneCardInfo.OpenDoorType			= OpenType;
	OneCardInfo.OpenWhichDoor			= nReaderRight;
	OneCardInfo.WeekAndHolidayCode[0]	= 0x00;
	OneCardInfo.WeekAndHolidayCode[1]	= 0x00;
	OneCardInfo.WeekAndHolidayCode[2]	= 0x00;
	OneCardInfo.WeekAndHolidayCode[3]	= 0x00;



	NET_CARD_ONECARDINFO  AllCardsInfo[40];
	for(int ii=0;ii<nMaxCardNum/16;ii++)
	{
		for(kk=0;kk<16;kk++)
		{
			memcpy(&AllCardsInfo[kk],&OneCardInfo,sizeof(NET_CARD_ONECARDINFO));
			cTmp[0]=uCardID>>24;
			cTmp[1]=uCardID>>16;
			cTmp[2]=uCardID>>8;
			cTmp[3]=uCardID&0x00ff;
			memcpy(AllCardsInfo[kk].CardID,cTmp,4);
			uCardID++;
		}
		nRet = NET_CARD_BatchDownCardInfo(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,&AllCardsInfo[0],sizeof(NET_CARD_ONECARDINFO)*16,ii*16,16,ReMACBuffer);
		if(nRet==0)
		{
			strTmp2.Format(" 批量下载第%d包",ii+1);
			
			if((ii%5)==0)
			{
				strTmp1+= strTmp2+"\r\n";
			}
			else
			{
				strTmp1+= strTmp2;
			}

			DisplayInfoforRecieve(strTmp1);

			//AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[35]);
		}else{
			
			if((nRet>0)&&(nRet<13))
				m_sReturnError.Format("%d",theApp.m_sCommandState[nRet]);	
			else
				m_sReturnError.Format("%d",nRet);	
			AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[35],m_sReturnError);
			return;
		}
	}
	int nRestcards=nMaxCardNum%16;
	for(kk=0;kk<nRestcards;kk++)
	{
		memcpy(&AllCardsInfo[kk],&OneCardInfo,sizeof(NET_CARD_ONECARDINFO));
		cTmp[0]=uCardID>>24;
		cTmp[1]=uCardID>>16;
		cTmp[2]=uCardID>>8;
		cTmp[3]=uCardID&0x00ff;
		memcpy(AllCardsInfo[kk].CardID,cTmp,4);
		uCardID++;
	}
	nRet = NET_CARD_BatchDownCardInfo(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,&AllCardsInfo[0],sizeof(NET_CARD_ONECARDINFO)*nRestcards,ii*16,nRestcards,ReMACBuffer);
	if(nRet==0)
	{
		strTmp2.Format(" 批量下载最后一个包，有卡数%d，总共下载%d张卡",nRestcards,ii*16+nRestcards);
		strTmp1+= strTmp2+"\r\n";
		DisplayInfoforRecieve(strTmp1);
	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[35],m_sReturnError);
		return;
	}

	
}
//单张下载500张卡
void CSDK_DEMO_VCDlg::OnButton38() 
{
	//1)Get all cards Series
	CString m_sTempStr,strTmp2,strTmp1;
	int nMaxCardNum=300;

	//Get First CardNum
	((CEdit*)GetDlgItem(IDC_EDIT_CARDSERIES))->GetWindowText(m_sTempStr);
	if(m_sTempStr.GetLength()!=8)
		return;

	unsigned int  uCardID=0;
	sscanf(m_sTempStr,"%x", &uCardID);


	//Get a card Info
	//////////////////////////////////////////////////////
//	CString m_sTempStr;
	char cTmp[100];
	NET_CARD_ONECARDINFO  OneCardInfo;
	memset(&OneCardInfo,0xff,sizeof(NET_CARD_ONECARDINFO));

	//card series
	((CEdit*)GetDlgItem(IDC_EDIT_CARDSERIES))->GetWindowText(m_sTempStr);
	if(m_sTempStr.GetLength()!=8)
		return;
	for(int kk=0;kk<m_sTempStr.GetLength()/2;kk++)
	{
		sscanf(m_sTempStr.Mid(2*kk,2), "%x", cTmp+kk);
	}
	memcpy(OneCardInfo.CardID,cTmp,4);
	//OpenType
	OneCardInfo.OpenType=OpenType;
	//pass password for door1
	((CEdit*)GetDlgItem(IDC_EDIT_OPENPASSWORD))->GetWindowText(m_sTempStr);
	if(m_sTempStr.GetLength()!=4)
		return;
	for(kk=0;kk<m_sTempStr.GetLength()/2;kk++)
	{
		sscanf(m_sTempStr.Mid(2*kk,2), "%x", cTmp+kk);
	}
	memcpy(OneCardInfo.Door01Password,cTmp,2);
	//door1 ==>door2 door3 door4 
	memcpy(OneCardInfo.Door02Password,OneCardInfo.Door01Password,2);
	memcpy(OneCardInfo.Door03Password,OneCardInfo.Door01Password,2);
	memcpy(OneCardInfo.Door04Password,OneCardInfo.Door01Password,2);

	//Enable the card's  period of validity
	BOOL m_bCheck=((CButton*)GetDlgItem(IDC_DOOR_CHECK16))->GetCheck();
	if(m_bCheck)
	{
		((CEdit*)GetDlgItem(IDC_EDIT_ENDDATE))->GetWindowText(m_sTempStr);
		if(m_sTempStr.GetLength()!=6)
			return;
		for(kk=0;kk<m_sTempStr.GetLength()/2;kk++)
		{
			sscanf(m_sTempStr.Mid(2*kk,2), "%x", cTmp+kk);
		}
		OneCardInfo.EndYear	=cTmp[0];
		OneCardInfo.EndMonth=cTmp[1];
		OneCardInfo.EndDay	=cTmp[2];
		OneCardInfo.CardStatus =0x02;//Enable card's validity
	}
	else
	{
		OneCardInfo.CardStatus =0x00;
	}	
	OneCardInfo.OpenDoorType			= OpenType;
	OneCardInfo.OpenWhichDoor			= nReaderRight;
	OneCardInfo.WeekAndHolidayCode[0]	= 0x00;
	OneCardInfo.WeekAndHolidayCode[1]	= 0x00;
	OneCardInfo.WeekAndHolidayCode[2]	= 0x00;
	OneCardInfo.WeekAndHolidayCode[3]	= 0x00;

	for(int ii=0;ii<nMaxCardNum;ii++)
	{
		cTmp[0]=uCardID>>24;
		cTmp[1]=uCardID>>16;
		cTmp[2]=uCardID>>8;
		cTmp[3]=uCardID&0x00ff;
		memcpy(OneCardInfo.CardID,cTmp,4);
		uCardID++;

		nRet = NET_CARD_DownOneCardInfo(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,&OneCardInfo,sizeof(NET_CARD_ONECARDINFO),ReMACBuffer);

		if(nRet==0)
		{
			strTmp2.Format(" 单卡下载,序号 %d，卡号 %08X",ii+1,uCardID);
			strTmp1+= strTmp2+"\r\n";
			DisplayInfoforRecieve(strTmp1);

		}else{
			m_sReturnError.Format("%d",nRet);	
			AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[30],m_sReturnError);
		}

	}


	
}

void CSDK_DEMO_VCDlg::OnButton31Serach2() 
{

	CString m_sTempStr;
	int nRecordCount=0;
	NET_CARD_RECORDINFO  RecordInfo[80];
	memset(&RecordInfo,0x00,sizeof(NET_CARD_RECORDINFO)*80);

	nRet = NET_CARD_GetHistroyRecord(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,80,&nRecordCount,&RecordInfo[0],ReMACBuffer);
	if(nRet==0)
	{
		AfxMessageBox("OK");

	}
	
}

void CSDK_DEMO_VCDlg::OnButton39() 
{

		//身份证图片信息写入文件
		char buff[2000];

		char *BMPBufferSnap;
		BMPBufferSnap = new char[2000];

		CFile	 RFile;	
		CString  RFileNameStr;
		RFileNameStr="D:\\EmployeePic.BIN";
		int nSize=0;
		if(RFile.Open("D:\\EmployeePic.BIN", CFile::modeRead))
		{

		   RFile.Read(buff, 1200);
		   
		}
		RFile.Close();


}
//Register QR Code to Device
void CSDK_DEMO_VCDlg::OnButton31Serach3() 
{
	CString m_sTempStr;
	char cTmp[20];
	NET_CARD_ONECARDINFO  OneCardInfo;
	memset(&OneCardInfo,0xff,sizeof(NET_CARD_ONECARDINFO));

	//card series
	((CEdit*)GetDlgItem(IDC_EDIT_CARDSERIES))->GetWindowText(m_sTempStr);
	if(m_sTempStr.GetLength()!=8)
		return;
	for(int kk=0;kk<m_sTempStr.GetLength()/2;kk++)
	{
		sscanf(m_sTempStr.Mid(2*kk,2), "%x", cTmp+kk);
	}
	unsigned int  uCardID=0;
	sscanf(m_sTempStr,"%x", &uCardID);

	cTmp[0]=uCardID>>24;
	cTmp[1]=uCardID>>16;
	cTmp[2]=uCardID>>8;
	cTmp[3]=uCardID&0x00ff;
	uCardID++;
	m_sTempStr.Format("%08x",uCardID);
	((CEdit*)GetDlgItem(IDC_EDIT_CARDSERIES))->SetWindowText(m_sTempStr);
	theApp.CurCardIDStr = m_sTempStr;

	memcpy(OneCardInfo.CardID,cTmp,4);
	//OpenType
	OneCardInfo.OpenType=OpenType;
	//pass password for door1
	((CEdit*)GetDlgItem(IDC_EDIT_OPENPASSWORD))->GetWindowText(m_sTempStr);
	if(m_sTempStr.GetLength()!=4)
		return;
	for(kk=0;kk<m_sTempStr.GetLength()/2;kk++)
	{
		sscanf(m_sTempStr.Mid(2*kk,2), "%x", cTmp+kk);
	}
	memcpy(OneCardInfo.Door01Password,cTmp,2);
	//door1 ==>door2 door3 door4 
	memcpy(OneCardInfo.Door02Password,OneCardInfo.Door01Password,2);
	memcpy(OneCardInfo.Door03Password,OneCardInfo.Door01Password,2);
	memcpy(OneCardInfo.Door04Password,OneCardInfo.Door01Password,2);

	//Enable the card's  period of validity
	BOOL m_bCheck=((CButton*)GetDlgItem(IDC_DOOR_CHECK16))->GetCheck();
	if(m_bCheck)
	{
		((CEdit*)GetDlgItem(IDC_EDIT_ENDDATE))->GetWindowText(m_sTempStr);
		if(m_sTempStr.GetLength()!=6)
			return;
		for(kk=0;kk<m_sTempStr.GetLength()/2;kk++)
		{
			sscanf(m_sTempStr.Mid(2*kk,2), "%x", cTmp+kk);
		}
		OneCardInfo.EndYear	=cTmp[0];
		OneCardInfo.EndMonth=cTmp[1];
		OneCardInfo.EndDay	=cTmp[2];
		OneCardInfo.CardStatus =0x02;//Enable card's validity
	}
	else
	{
		OneCardInfo.CardStatus =0x00;
	}	
	OneCardInfo.OpenDoorType			= OpenType;
	OneCardInfo.OpenWhichDoor			= nReaderRight;
	OneCardInfo.WeekAndHolidayCode[0]	= 0x00;
	OneCardInfo.WeekAndHolidayCode[1]	= 0x00;
	OneCardInfo.WeekAndHolidayCode[2]	= 0x00;
	OneCardInfo.WeekAndHolidayCode[3]	= 0x00;



//////////////////////////////////////////////
//卡号：人员ID号 4B		0-4 
//卡状态：1B			5
//二维码长度：1B		6
//二维码内容：15B		7-21
//有效期：				27,28,29 
//QR Code CardNum First Byte=0x7E
//二维码卡号第一个字节为0x7E 也就是十制制126作为特殊卡号

	OneCardInfo.CardID[0] =0x7E;  
	//二维码有效期
	OneCardInfo.WeekAndHolidayCode[2] = OneCardInfo.EndYear;
	OneCardInfo.WeekAndHolidayCode[3] = OneCardInfo.EndMonth;
	OneCardInfo.Reserve3[0] = OneCardInfo.EndDay;
    //QR CODE
	int nLengthQR=0;
	char QRCodeString[100];
	CString QRTmp,LengthQRStr,QRCodeStringStr,m_sCardDownCommQR;
	((CEdit*)GetDlgItem(IDC_EDIT_OUTDELAY6))->GetWindowText(QRCodeStringStr);
	QRCodeStringStr.TrimLeft();
	QRCodeStringStr.TrimRight();
	nLengthQR = QRCodeStringStr.GetLength();
	if(nLengthQR<8)
	{
#ifdef ENGLISH
		AfxMessageBox("QR code Length is too short ");
#else
		AfxMessageBox("二维码长度太短");
#endif
		return;
	}



	if(nLengthQR>15)
		QRCodeStringStr=QRCodeStringStr.Right(15);
	else if(nLengthQR<15)
	{
		for(int kk=nLengthQR;kk<15;kk++)
		   QRCodeStringStr+="0";
	}
	sprintf(QRCodeString, "%s", QRCodeStringStr);





	//QR CODE length+15 QR code
	OneCardInfo.Door01Password[0]=nLengthQR;
	kk=0;
	OneCardInfo.Door01Password[1]=QRCodeString[kk++];
	OneCardInfo.Door02Password[0]=QRCodeString[kk++];
	OneCardInfo.Door02Password[1]=QRCodeString[kk++];
	OneCardInfo.Door03Password[0]=QRCodeString[kk++];
	OneCardInfo.Door03Password[1]=QRCodeString[kk++];
	OneCardInfo.Door04Password[0]=QRCodeString[kk++];
	OneCardInfo.Door04Password[1]=QRCodeString[kk++];
	OneCardInfo.EndYear		= QRCodeString[kk++];
	OneCardInfo.EndMonth	= QRCodeString[kk++];
	OneCardInfo.EndDay		= QRCodeString[kk++];
	OneCardInfo.Reserve1[0] = QRCodeString[kk++];
	OneCardInfo.Reserve1[1] = QRCodeString[kk++];
	OneCardInfo.Reserve1[2] = QRCodeString[kk++];

	OneCardInfo.MultiCardType  = QRCodeString[kk++];
	OneCardInfo.RemoteOpenType = QRCodeString[kk++];
///////////////////////////////////////////////////////////////////////NET_CARD_DownOneCardInfo


	nRet = NET_CARD_Down_QR_CardInfo(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,&OneCardInfo,sizeof(NET_CARD_ONECARDINFO),ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[31]);
	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[30],m_sReturnError);
	}

	
}
//UNRegister QR Code to Device
//set OneCardInfo.CardStatus =0x03; other is same as 'Register QR Code to Device'
//注销二维码，其实就是与下载单个二维码一样，只是将卡状态位设置为03即可
void CSDK_DEMO_VCDlg::OnButton31Serach5() 
{

	CString m_sTempStr;
	char cTmp[20];
	NET_CARD_ONECARDINFO  OneCardInfo;
	memset(&OneCardInfo,0xff,sizeof(NET_CARD_ONECARDINFO));

	//card series
	((CEdit*)GetDlgItem(IDC_EDIT_CARDSERIES))->GetWindowText(m_sTempStr);
	if(m_sTempStr.GetLength()!=8)
		return;
	for(int kk=0;kk<m_sTempStr.GetLength()/2;kk++)
	{
		sscanf(m_sTempStr.Mid(2*kk,2), "%x", cTmp+kk);
	}
	
	memcpy(OneCardInfo.CardID,cTmp,4);

	//OpenType
	OneCardInfo.OpenType=OpenType;
	//pass password for door1
	((CEdit*)GetDlgItem(IDC_EDIT_OPENPASSWORD))->GetWindowText(m_sTempStr);
	if(m_sTempStr.GetLength()!=4)
		return;
	for(kk=0;kk<m_sTempStr.GetLength()/2;kk++)
	{
		sscanf(m_sTempStr.Mid(2*kk,2), "%x", cTmp+kk);
	}
	memcpy(OneCardInfo.Door01Password,cTmp,2);
	//door1 ==>door2 door3 door4 
	memcpy(OneCardInfo.Door02Password,OneCardInfo.Door01Password,2);
	memcpy(OneCardInfo.Door03Password,OneCardInfo.Door01Password,2);
	memcpy(OneCardInfo.Door04Password,OneCardInfo.Door01Password,2);

	//Enable the card's  period of validity
	BOOL m_bCheck=((CButton*)GetDlgItem(IDC_DOOR_CHECK16))->GetCheck();
	if(m_bCheck)
	{
		((CEdit*)GetDlgItem(IDC_EDIT_ENDDATE))->GetWindowText(m_sTempStr);
		if(m_sTempStr.GetLength()!=6)
			return;
		for(kk=0;kk<m_sTempStr.GetLength()/2;kk++)
		{
			sscanf(m_sTempStr.Mid(2*kk,2), "%x", cTmp+kk);
		}
		OneCardInfo.EndYear	=cTmp[0];
		OneCardInfo.EndMonth=cTmp[1];
		OneCardInfo.EndDay	=cTmp[2];
		OneCardInfo.CardStatus =0x02;//Enable card's validity
	}
	else
	{
		OneCardInfo.CardStatus =0x00;
	}	
	OneCardInfo.OpenDoorType			= OpenType;
	OneCardInfo.OpenWhichDoor			= nReaderRight;
	OneCardInfo.WeekAndHolidayCode[0]	= 0x00;
	OneCardInfo.WeekAndHolidayCode[1]	= 0x00;
	OneCardInfo.WeekAndHolidayCode[2]	= 0x00;
	OneCardInfo.WeekAndHolidayCode[3]	= 0x00;

	OneCardInfo.CardStatus =0x03;//card's status is 0x03 

//////////////////////////////////////////////
//卡号：人员ID号 4B		0-4 
//卡状态：1B			5
//二维码长度：1B		6
//二维码内容：15B		7-21
//有效期：				27,28,29 
	OneCardInfo.CardID[0] =0x7E;
	//二维码有效期
	OneCardInfo.WeekAndHolidayCode[2] = OneCardInfo.EndYear;
	OneCardInfo.WeekAndHolidayCode[3] = OneCardInfo.EndMonth;
	OneCardInfo.Reserve3[0] = OneCardInfo.EndDay;
	
    //QR CODE
	int nLengthQR=0;
	char QRCodeString[100];
	CString QRTmp,LengthQRStr,QRCodeStringStr,m_sCardDownCommQR;
	((CEdit*)GetDlgItem(IDC_EDIT_OUTDELAY6))->GetWindowText(QRCodeStringStr);
	QRCodeStringStr.TrimLeft();
	QRCodeStringStr.TrimRight();
	nLengthQR = QRCodeStringStr.GetLength();
	if(nLengthQR<8)
	{
#ifdef ENGLISH
		AfxMessageBox("QR code Length is too short ");
#else
		AfxMessageBox("二维码长度太短");
#endif
		return;
	}

	if(nLengthQR>15)
		QRCodeStringStr=QRCodeStringStr.Right(15);
	else if(nLengthQR<15)
	{
		for(int kk=nLengthQR;kk<15;kk++)
		   QRCodeStringStr+="0";
	}
	sprintf(QRCodeString, "%s", QRCodeStringStr);
	//QR CODE length+15 QR code
	OneCardInfo.Door01Password[0]=nLengthQR;
	kk=0;
	OneCardInfo.Door01Password[1]=QRCodeString[kk++];
	OneCardInfo.Door02Password[0]=QRCodeString[kk++];
	OneCardInfo.Door02Password[1]=QRCodeString[kk++];
	OneCardInfo.Door03Password[0]=QRCodeString[kk++];
	OneCardInfo.Door03Password[1]=QRCodeString[kk++];
	OneCardInfo.Door04Password[0]=QRCodeString[kk++];
	OneCardInfo.Door04Password[1]=QRCodeString[kk++];
	OneCardInfo.EndYear		= QRCodeString[kk++];
	OneCardInfo.EndMonth	= QRCodeString[kk++];
	OneCardInfo.EndDay		= QRCodeString[kk++];
	OneCardInfo.Reserve1[0] = QRCodeString[kk++];
	OneCardInfo.Reserve1[1] = QRCodeString[kk++];
	OneCardInfo.Reserve1[2] = QRCodeString[kk++];

	OneCardInfo.MultiCardType  = QRCodeString[kk++];
	OneCardInfo.RemoteOpenType = QRCodeString[kk++];
///////////////////////////////////////////////////////////////////////NET_CARD_DownOneCardInfo


	nRet = NET_CARD_Down_QR_CardInfo(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,&OneCardInfo,sizeof(NET_CARD_ONECARDINFO),ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[31]);
	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[30],m_sReturnError);
	}	
}
//读二维码卡数目
void CSDK_DEMO_VCDlg::OnButton31Serach7() 
{

	int QRNumber=0;
	nRet=NET_CARD_Read_QR_CardNumber(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,&QRNumber,ReMACBuffer);
	if(nRet==0)
	{
		CString DeviceTimeStr;
		DeviceTimeStr.Format("QR Card number = %u",QRNumber);
		DisplayInfoforRecieve(DeviceTimeStr);

	}else{
		//写入输出LIST
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[31],m_sReturnError);
	}
	
}
//注册1K二维码
void CSDK_DEMO_VCDlg::OnButton31Serach4() 
{
	CString m_sTempStr;
	int nLengthQR=0;
	CString QRCodeStringStr;

	//card series
	((CEdit*)GetDlgItem(IDC_EDIT_CARDSERIES))->GetWindowText(m_sTempStr);
	if(m_sTempStr.GetLength()!=8)
		return;

	((CEdit*)GetDlgItem(IDC_EDIT_OUTDELAY6))->GetWindowText(QRCodeStringStr);
	QRCodeStringStr.TrimLeft();
	QRCodeStringStr.TrimRight();
	nLengthQR = QRCodeStringStr.GetLength();
	if(nLengthQR<8)
	{
#ifdef ENGLISH
		AfxMessageBox("QR code Length is too short ");
#else
		AfxMessageBox("二维码长度太短");
#endif
		return;
	}

	if(nLengthQR>15)
		QRCodeStringStr=QRCodeStringStr.Right(15);
	else if(nLengthQR<15)
	{
		for(int kk=nLengthQR;kk<15;kk++)
		   QRCodeStringStr+="0";
	}

	registerQrCode(m_sTempStr, QRCodeStringStr,nLengthQR,1000);
	
}

void CSDK_DEMO_VCDlg::registerQrCode(CString StartCardNo, CString QRStartCodeStr,int nQRLength,int nNumber)
{
	CString m_sTempStr;
	char cTmp[20];
	NET_CARD_ONECARDINFO  OneCardInfo;
	memset(&OneCardInfo,0xff,sizeof(NET_CARD_ONECARDINFO));


	if(StartCardNo.GetLength()!=8)
		return;
	for(int kk=0;kk<StartCardNo.GetLength()/2;kk++)
	{
		sscanf(StartCardNo.Mid(2*kk,2), "%x", cTmp+kk);
	}
	
	memcpy(OneCardInfo.CardID,cTmp,4);

	//OpenType
	OneCardInfo.OpenType=OpenType;
	//pass password for door1
	((CEdit*)GetDlgItem(IDC_EDIT_OPENPASSWORD))->GetWindowText(m_sTempStr);
	if(m_sTempStr.GetLength()!=4)
		return;
	for(kk=0;kk<m_sTempStr.GetLength()/2;kk++)
	{
		sscanf(m_sTempStr.Mid(2*kk,2), "%x", cTmp+kk);
	}
	memcpy(OneCardInfo.Door01Password,cTmp,2);
	memcpy(OneCardInfo.Door02Password,OneCardInfo.Door01Password,2);
	memcpy(OneCardInfo.Door03Password,OneCardInfo.Door01Password,2);
	memcpy(OneCardInfo.Door04Password,OneCardInfo.Door01Password,2);

	OneCardInfo.CardStatus =0x00;
	OneCardInfo.OpenDoorType			= OpenType;
	OneCardInfo.OpenWhichDoor			= nReaderRight;
	OneCardInfo.WeekAndHolidayCode[0]	= 0x00;
	OneCardInfo.WeekAndHolidayCode[1]	= 0x00;
	OneCardInfo.WeekAndHolidayCode[2]	= 0x00;
	OneCardInfo.WeekAndHolidayCode[3]	= 0x00;

//////////////////////////////////////////////
//卡号：人员ID号 4B		0-4 
//卡状态：1B			5
//二维码长度：1B		6
//二维码内容：15B		7-21
//有效期：				27,28,29 
	OneCardInfo.CardID[0] =0x7E;
	//二维码有效期
	OneCardInfo.WeekAndHolidayCode[2] = OneCardInfo.EndYear;
	OneCardInfo.WeekAndHolidayCode[3] = OneCardInfo.EndMonth;
	OneCardInfo.Reserve3[0] = OneCardInfo.EndDay;
    //QR CODE

	char  QRCodeString[50];
	sprintf(QRCodeString, "%s", QRStartCodeStr);
	//QR CODE length+15 QR code
	OneCardInfo.Door01Password[0]=nQRLength;
	kk=0;
	OneCardInfo.Door01Password[1]=QRCodeString[kk++];
	OneCardInfo.Door02Password[0]=QRCodeString[kk++];
	OneCardInfo.Door02Password[1]=QRCodeString[kk++];
	OneCardInfo.Door03Password[0]=QRCodeString[kk++];
	OneCardInfo.Door03Password[1]=QRCodeString[kk++];
	OneCardInfo.Door04Password[0]=QRCodeString[kk++];
	OneCardInfo.Door04Password[1]=QRCodeString[kk++];
	OneCardInfo.EndYear		= QRCodeString[kk++];
	OneCardInfo.EndMonth	= QRCodeString[kk++];
	OneCardInfo.EndDay		= QRCodeString[kk++];
	OneCardInfo.Reserve1[0] = QRCodeString[kk++];
	OneCardInfo.Reserve1[1] = QRCodeString[kk++];
	OneCardInfo.Reserve1[2] = QRCodeString[kk++];

	OneCardInfo.MultiCardType  = QRCodeString[kk++];
	OneCardInfo.RemoteOpenType = QRCodeString[kk++];
///////////////////////////////////////////////////////////////////////NET_CARD_DownOneCardInfo

	unsigned int nCardSeries=0;
	nCardSeries = OneCardInfo.CardID[0];
	nCardSeries = nCardSeries<<8;
	nCardSeries = nCardSeries | OneCardInfo.CardID[1];
	nCardSeries = nCardSeries<<8;
	nCardSeries = nCardSeries | OneCardInfo.CardID[2];
	nCardSeries = nCardSeries<<8;
	nCardSeries = nCardSeries | OneCardInfo.CardID[3];

	CFile theFile;
	if(!theFile.Open("C:\\QRCode_DownLoad.txt",CFile::modeWrite))
		theFile.Open("C:\\QRCode_DownLoad.txt",CFile::modeCreate|CFile::modeWrite);

	CTime time=CTime::GetCurrentTime() ;
	CString tmpstr1;
	tmpstr1.Format("%d-%02d-%02d %02d:%02d:%02d ",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
	tmpstr1  +="\r\n";
	theFile.SeekToEnd();
	theFile.Write(tmpstr1,tmpstr1.GetLength());
	theFile.Close();

	for( int i=0;i<nNumber;i++)
	{
		//卡号变化
		OneCardInfo.CardID[0] = 0x7E;
		OneCardInfo.CardID[1] = (nCardSeries >>16) &0x00FF;
		OneCardInfo.CardID[2] = (nCardSeries >>8) &0x00FF;
		OneCardInfo.CardID[3] = nCardSeries  &0x00FF;

		//sprintf(QRCodeString, "%s", QRCodeStringStr);

		kk=0;
		OneCardInfo.Door01Password[1]=QRCodeString[kk++];
		OneCardInfo.Door02Password[0]=QRCodeString[kk++];
		OneCardInfo.Door02Password[1]=QRCodeString[kk++];
		OneCardInfo.Door03Password[0]=QRCodeString[kk++];
		OneCardInfo.Door03Password[1]=QRCodeString[kk++];
		OneCardInfo.Door04Password[0]=QRCodeString[kk++];
		OneCardInfo.Door04Password[1]=QRCodeString[kk++];
		OneCardInfo.EndYear		= QRCodeString[kk++];
		OneCardInfo.EndMonth	= QRCodeString[kk++];
		OneCardInfo.EndDay		= QRCodeString[kk++];
		OneCardInfo.Reserve1[0] = QRCodeString[kk++];
		OneCardInfo.Reserve1[1] = QRCodeString[kk++];
		OneCardInfo.Reserve1[2] = QRCodeString[kk++];
		OneCardInfo.MultiCardType  = QRCodeString[kk++];
		OneCardInfo.RemoteOpenType = QRCodeString[kk++];		

		nRet = NET_CARD_Down_QR_CardInfo(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,&OneCardInfo,sizeof(NET_CARD_ONECARDINFO),ReMACBuffer);
		if(nRet==0)
		{
			CString DeviceTimeStr[5],DeviceTimeAllStr;
			//DisplayInfoforRecieve(QRCodeString);
			DeviceTimeStr[0].Format(" %02x",OneCardInfo.CardID[0]);
			DeviceTimeStr[1].Format(" %02x",OneCardInfo.CardID[1]);
			DeviceTimeStr[2].Format(" %02x",OneCardInfo.CardID[2]);
			DeviceTimeStr[3].Format(" %02x",OneCardInfo.CardID[3]);
			DeviceTimeStr[4].Format(" counter=%d ",i+1);


			DeviceTimeAllStr = DeviceTimeStr[0]+DeviceTimeStr[1]+DeviceTimeStr[2]+DeviceTimeStr[3]+DeviceTimeStr[4];
			DisplayInfoforRecieve(QRCodeString +DeviceTimeAllStr);

			CFile theFile;
			if(!theFile.Open("C:\\QRCode_DownLoad.txt",CFile::modeWrite))
				theFile.Open("C:\\QRCode_DownLoad.txt",CFile::modeCreate|CFile::modeWrite);

			CTime time=CTime::GetCurrentTime() ;
			CString tmpstr1;
			//tmpstr1.Format("%d-%02d-%02d %02d:%02d:%02d ",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());

			tmpstr1  +=QRCodeString;
			tmpstr1  +="  ";
			tmpstr1  +=DeviceTimeAllStr;
			tmpstr1  +="\r\n";
			theFile.SeekToEnd();
			theFile.Write(tmpstr1,tmpstr1.GetLength());
			theFile.Close();

		}else{
			CString DeviceTimeStr;
#ifdef ENGLISH
			DeviceTimeStr.Format("QR Card Download Fail= %d",i);
#else
			DeviceTimeStr.Format("二维码卡下载失败，失败止于= %d",i);
#endif
			DisplayInfoforRecieve(DeviceTimeStr);
			break;
		}

		nCardSeries++;

		if(QRCodeString[3]>=0x39)
		{
		   if(QRCodeString[2]>=0x39)
		   {
			   if(QRCodeString[1]>=0x39)
			   {
				   if(QRCodeString[0]>0x39)
					   break;
				   else
				   {
						QRCodeString[0]++;
						QRCodeString[1]=0x30;
						QRCodeString[2]=0x30;
						QRCodeString[3]=0x30;
				   }

			   }				
			   else
			   {
				   QRCodeString[1]++;
				   QRCodeString[2]=0x30;
				   QRCodeString[3]=0x30;
			   }
		   }
		   else
		   {
			   QRCodeString[2]++;
			   QRCodeString[3]=0x30;
		   }
		}
		else
		{
			QRCodeString[3]++;
		}


	}

	if(!theFile.Open("C:\\QRCode_DownLoad.txt",CFile::modeWrite))
		theFile.Open("C:\\QRCode_DownLoad.txt",CFile::modeCreate|CFile::modeWrite);
	CTime time2=CTime::GetCurrentTime() ;
	tmpstr1.Format("%d-%02d-%02d %02d:%02d:%02d ",time2.GetYear(),time2.GetMonth(),time2.GetDay(),time2.GetHour(),time2.GetMinute(),time2.GetSecond());
	tmpstr1  +="\r\n";
	theFile.SeekToEnd();
	theFile.Write(tmpstr1,tmpstr1.GetLength());
	theFile.Close();

}

void CSDK_DEMO_VCDlg::OnButton31Serach9() 
{
	CString m_sTempStr;
	int nLengthQR=0;
	CString QRCodeStringStr;

	//card series
	((CEdit*)GetDlgItem(IDC_EDIT_CARDSERIES))->GetWindowText(m_sTempStr);
	if(m_sTempStr.GetLength()!=8)
		return;

	((CEdit*)GetDlgItem(IDC_EDIT_OUTDELAY6))->GetWindowText(QRCodeStringStr);
	QRCodeStringStr.TrimLeft();
	QRCodeStringStr.TrimRight();
	nLengthQR = QRCodeStringStr.GetLength();
	if(nLengthQR<8)
	{
#ifdef ENGLISH
		AfxMessageBox("QR code Length is too short ");
#else
		AfxMessageBox("二维码长度太短");
#endif
		return;
	}

	if(nLengthQR>15)
		QRCodeStringStr=QRCodeStringStr.Right(15);
	else if(nLengthQR<15)
	{
		for(int kk=nLengthQR;kk<15;kk++)
		   QRCodeStringStr+="0";
	}

	registerQrCode(m_sTempStr, QRCodeStringStr,nLengthQR,3000);
		
}

void CSDK_DEMO_VCDlg::OnButton31Serach10() 
{
	CString m_sTempStr;
	int nLengthQR=0;
	CString QRCodeStringStr;

	//card series
	((CEdit*)GetDlgItem(IDC_EDIT_CARDSERIES))->GetWindowText(m_sTempStr);
	if(m_sTempStr.GetLength()!=8)
		return;

	((CEdit*)GetDlgItem(IDC_EDIT_OUTDELAY6))->GetWindowText(QRCodeStringStr);
	QRCodeStringStr.TrimLeft();
	QRCodeStringStr.TrimRight();
	nLengthQR = QRCodeStringStr.GetLength();
	if(nLengthQR<8)
	{
#ifdef ENGLISH
		AfxMessageBox("QR code Length is too short ");
#else
		AfxMessageBox("二维码长度太短");
#endif
		return;
	}

	if(nLengthQR>15)
		QRCodeStringStr=QRCodeStringStr.Right(15);
	else if(nLengthQR<15)
	{
		for(int kk=nLengthQR;kk<15;kk++)
		   QRCodeStringStr+="0";
	}

	registerQrCode(m_sTempStr, QRCodeStringStr,nLengthQR,6000);
		
}
//Clear ALL QRCode
void CSDK_DEMO_VCDlg::OnButton31Serach6() 
{

	nRet=NET_CARD_Clear_QR_CardNumber(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,ReMACBuffer);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[32]);
	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[32],m_sReturnError);
	}
	
	
}


void CSDK_DEMO_VCDlg::OnDoorCheck17() 
{

	int m_nEnableTCPServerMode=((CButton*)GetDlgItem(IDC_DOOR_CHECK17))->GetCheck();
	if(m_nEnableTCPServerMode)
	{
		if(IDOK!=AfxMessageBox("设置为SDK与TCP服务器通讯模式，是指设备主动与TCP服务器建立TCP连接，\n\nSDK操作前端设备时，数据将通过TCP服务器的TCP连接传输到设备，\n\nTCP server模式要配合TCP服务器软件一起使用\n\n是否继续?",MB_OKCANCEL|MB_DEFBUTTON2))
			return;	
		
		CString  m_sMACTmp;
		((CEdit*)GetDlgItem(IDC_EDIT_OLDMAC))->GetWindowText(m_sMACTmp);
		m_sMACTmp.TrimLeft();
		m_sMACTmp.TrimRight();
		if(m_sMACTmp.GetLength()!=12)
		{
			AfxMessageBox("设备MAC地址不对");
			return;
		}
		CString strtt;
		for(int kk=0;kk<m_sMACTmp.GetLength()/2;kk++)
		{
			strtt=m_sMACTmp.Mid(2*kk,2);
			sscanf( strtt, "%x", ReMACBuffer+kk);
		}
	}
	int	  nTCPServerUDPPort;

	CString m_sServerPort;

	((CEdit*)GetDlgItem(IDC_EDIT_LOCALPORT8))->GetWindowText(m_sServerPort);
	if(m_sServerPort.IsEmpty())
		m_sServerPort="19100";

	m_sServerPort.TrimLeft();
	m_sServerPort.TrimRight();
	nTCPServerUDPPort =atoi(m_sServerPort);//19100


	nRet = NET_CARD_EnableTCPServerMode(szLocalIP,nTCPServerUDPPort,m_nEnableTCPServerMode);
	if(nRet==0)
	{
		AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[26]);
	}else{
		
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[26],"该SDK不支持该模式");
	}	
}
//参数保存
void CSDK_DEMO_VCDlg::OnOk2() 
{
	UpdateData(TRUE);


	theApp.m_sLocalComputerPORT =m_sLocalPort;
	theApp.m_sDevice_IP=m_sCOM_IP;
	int nIndex=((CComboBox*)GetDlgItem(IDC_NETCARD_COMBO1))->GetCurSel();
	if(nIndex>=0)
	{
	  ((CComboBox*)GetDlgItem(IDC_NETCARD_COMBO1))->GetLBText(nIndex,theApp.m_sLocalComputerIP);
	}
	sprintf(DeviceIP, "%s", m_sCOM_IP);
	nDevicePort = atoi(m_sCOM_PORT);



	theApp.ReadorWriteIniFile(FALSE);


	
}
//设置蓝牙名称
void CSDK_DEMO_VCDlg::OnButton31Serach11() 
{
	int  VoiceLength=0;
	BYTE NameByte[40];
	CString m_sTempStr;
	((CEdit*)GetDlgItem(IDC_EDIT_OUTDELAY7))->GetWindowText(m_sTempStr);
	if(m_sTempStr.GetLength()>20)
	{
#ifdef ENGLISH
		AfxMessageBox("Please Input Audio Code");
#else
		AfxMessageBox("蓝牙名称小于20个字符");
#endif
		return;
	}
	m_sTempStr.TrimLeft();
	m_sTempStr.TrimRight();

	int nLength=0;
	CString m_sNameStr,tmpStr,str;
	nLength =m_sTempStr.GetLength();
	str.Format("%02X",nLength);
	memcpy(NameByte,m_sTempStr.GetBuffer(0),nLength); 
	for( int i = 0;i<nLength;i++)
	{
		tmpStr.Format( "%02X",   NameByte[i]); 
		m_sNameStr+=tmpStr;
		if(NameByte[i] & 0x80)
		{
		    AfxMessageBox("不要写中文字符");
		    return;
		}
	}


	int nbOpenDoor=1;
	int nReaderNo=1;

	nRet = NET_CARD_Set_BTName(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,NameByte,nLength,ReMACBuffer);
	
	if(nRet==0)
	{
	    AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[37]);
	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[37],m_sReturnError);
	}	
}

void CSDK_DEMO_VCDlg::OnButton31Serach12() 
{
	int  VoiceLength=0;
	BYTE NameByte[40];
	CString m_sTempStr;
	((CEdit*)GetDlgItem(IDC_EDIT_OUTDELAY8))->GetWindowText(m_sTempStr);

	m_sTempStr.TrimLeft();
	m_sTempStr.TrimRight();
	if(m_sTempStr.GetLength()!=4)
	{
		AfxMessageBox("蓝牙密码必须是4个数字");
		return;
	}
	int nLength=0;
	CString m_sNameStr,tmpStr,str;
	nLength =m_sTempStr.GetLength();
	str.Format("%02X",nLength);
	memcpy(NameByte,m_sTempStr.GetBuffer(0),nLength); 
	for( int i = 0;i<nLength;i++)
	{
		tmpStr.Format( "%02X",   NameByte[i]); 
		m_sNameStr+=tmpStr;
	}
	nRet = NET_CARD_Set_BTPassword(DEVICE_NET_ACCESS,DeviceIP,nDevicePort,NameByte,nLength,ReMACBuffer);	
	if(nRet==0)
	{
	    AddStringtoList(m_sStrOutputInfo[0],m_sStrOutputInfo[38]);
	}else{
		m_sReturnError.Format("%d",nRet);	
		AddStringtoList(m_sStrOutputInfo[1],m_sStrOutputInfo[38],m_sReturnError);
	}	
}


BOOL CSDK_DEMO_VCDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	theApp.ReadorWriteIniFile(FALSE);
	return CDialog::DestroyWindow();
}
