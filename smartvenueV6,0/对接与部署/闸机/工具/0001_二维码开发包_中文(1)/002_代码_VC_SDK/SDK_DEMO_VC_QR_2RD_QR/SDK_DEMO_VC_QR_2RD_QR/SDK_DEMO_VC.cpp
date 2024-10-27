// SDK_DEMO_VC.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SDK_DEMO_VC.h"
#include "SDK_DEMO_VCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSDK_DEMO_VCApp

BEGIN_MESSAGE_MAP(CSDK_DEMO_VCApp, CWinApp)
	//{{AFX_MSG_MAP(CSDK_DEMO_VCApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSDK_DEMO_VCApp construction

CSDK_DEMO_VCApp::CSDK_DEMO_VCApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_hLangDLL = NULL;


}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSDK_DEMO_VCApp object

CSDK_DEMO_VCApp theApp;
CSDK_DEMO_VCDlg * g_pMainDlg = NULL;	
	
CString m_sStrOutputInfo[40];


//�¼�����
#ifndef ENGLISH
CString EventString[100]=
{
	 "ˢ������",		"Զ�̿���",		"˫������",			"���뿪��",		"в���뿪��",
	 "���뿪��",		"�׿�����",		"���Ű�Ť����",		"�����ѱ�����",	"����1��Ӧ",
	 "����2��Ӧ",		"�뿪ˢ��",		"��Ա���뿪",		"��Ա�ѽ���",	"������Ч",
	 "˫����Ч",	    "��������",		"δˢ�׿�",			"��Ƭ�Ƿ�",		"˫��ˢ��",
	 "�ſ���ʱ����",	"в�ȱ���",	    "�࿨�����ȷ",		"�˿��ѹ���",	"������������",
	 "�ų���",			"Զ�̹���",		"��ǿ�ƴ�",		"��������",		"�ű������ر�",
	 "�ų���",			"�ָ��ŵ���̬",	"����ˢ��",			"�Ŀ�ˢ��",		"�忨ˢ��",
	 "������Ч",		"�Ŀ���Ч",		"�忨��Ч",			"��������",		"�Ŀ�����",
	 "�忨����",		"����ȷ�Ͽ���",	"˫��ȷ�Ͽ���",		"����ȷ�Ͽ���",	"�Ŀ�ȷ�Ͽ���",	
	 "�忨ȷ�Ͽ���",	"�࿨�ظ�ˢ��", "�˿��ѹ���",		"Զ��ȷ�Ͽ���",	"����",
	 "ϵͳ����",		"ϵͳ��Ա",		"ϵͳ��Ա",			"����",			"����",
	 "˫���ָ�����",	"˫�ջָ�����",	"�ֿغ�˫��",		"�ֿغ�˫��",	"�ֿغп���",
	 "�ֿغи�λ",		"�������",		"�����ϻָ�����",	"�˿�Ϊɾ����",	"��ť��Կ�׿���",
	 "����Խ�",		"��֤�Զ��ӿ�",	"�ظ�����",			"�ظ����",		"����",
	 "����","����","����","����","����",
	 "����","����","����","����","����",
	 "����","����","����","����","����",
	 "����","����","����","����","����"
};
#else

CString EventString[100]=
{"Normal punching card", "Remote opening", "Dual verification", "Password to open the door", "duress code to open the door",
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
#endif
/////////////////////////////////////////////////////////////////////////////
// CSDK_DEMO_VCApp initialization

BOOL CSDK_DEMO_VCApp::InitInstance()
{

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		//AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	WSADATA		WSAData = { 0 };
	if ( 0 != WSAStartup( WSA_VERSION, &WSAData ) )
	{
		// Tell the user that we could not find a usable
		// WinSock DLL.
		if ( LOBYTE( WSAData.wVersion ) != LOBYTE(WSA_VERSION) ||
			 HIBYTE( WSAData.wVersion ) != HIBYTE(WSA_VERSION) )
			 ::MessageBox(NULL, _T("Incorrect version of WS2_32.dll found"), _T("Error"), MB_OK);

		WSACleanup( );
		return FALSE;
	}


	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef ENGLISH
	m_hLangDLL=::LoadLibrary("english.dll");
	AfxSetResourceHandle(m_hLangDLL);
#endif


#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#ifndef ENGLISH
    m_sStrOutputInfo[0]="�����ɹ�!";
	m_sStrOutputInfo[1]="����ʧ��!";
	m_sStrOutputInfo[2]="����";
	m_sStrOutputInfo[3]="����";
	m_sStrOutputInfo[4]="ȷ��ɾ����?";
	m_sStrOutputInfo[5]="IP��ַ��Ч,����������";
	m_sStrOutputInfo[6]="�޸ĳɹ�!";
	m_sStrOutputInfo[7]="�޸�ʧ��!";
	m_sStrOutputInfo[8]="ɾ���ɹ�!";
	m_sStrOutputInfo[9]="ɾ��ʧ��!";
	m_sStrOutputInfo[10]="ϵͳ������!";
	m_sStrOutputInfo[11]="��ʼ��DLL�������";

	m_sStrOutputInfo[12]="�豸����";
	m_sStrOutputInfo[13]="�豸�������";
	m_sStrOutputInfo[14]="�豸���߼��";
	m_sStrOutputInfo[15]="��ȡʱ��";
	m_sStrOutputInfo[16]="����ʱ��";
	m_sStrOutputInfo[17]="��ȡ�汾";
	m_sStrOutputInfo[18]="�豸��ʼ��";
	m_sStrOutputInfo[19]="�����ϴ���������˿ں�";
	m_sStrOutputInfo[20]="����ʵʱ���";
	m_sStrOutputInfo[21]="ֹͣʵʱ���";
	m_sStrOutputInfo[22]="Զ�̿���";
	m_sStrOutputInfo[23]="Զ�̹���";
	m_sStrOutputInfo[24]="���û���";
	m_sStrOutputInfo[25]="��������ʱ";
	m_sStrOutputInfo[26]="�����ſ���ʱ����";
	m_sStrOutputInfo[27]="���ñ���������ʱ";
	m_sStrOutputInfo[28]=" ����Ϊ4λ����(0-9) ";
	m_sStrOutputInfo[29]="�����Ŵ���в�������ʱ";
	m_sStrOutputInfo[30]="����в�ȿ�������";

	m_sStrOutputInfo[31]="���ص��ſ�";
	m_sStrOutputInfo[32]="������п�";

	m_sStrOutputInfo[33]="��������ֱ�ӿ���";

	m_sStrOutputInfo[34]="��ȡ���ſ���Ϣ";

	m_sStrOutputInfo[35]="�������ؿ�";

	m_sStrOutputInfo[36]="����ָ��";
	m_sStrOutputInfo[37]="��������";
	m_sStrOutputInfo[38]="��������";

	m_sCommandState[0]="����ɹ�";
	m_sCommandState[1]="������Ч";
	m_sCommandState[2]="������Ч";
	m_sCommandState[3]="���ڲ����������ؿ���Ϣ������պ�����";
	m_sCommandState[4]="δ֪����";
	m_sCommandState[5]="û��Ȩ��";
	m_sCommandState[6]="�豸��";
	m_sCommandState[7]="�������ʧ��";
	m_sCommandState[8]="������ܲ��ɹ�";
	m_sCommandState[9]="�������洢�ռ䲻��";
	m_sCommandState[10]="���������޼�¼";
	m_sCommandState[11]="���������޸ÿ���Ϣ��û��������ز���";
	m_sCommandState[12]="�������ڼ�¼�Ѷ���";

#else

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
	m_sStrOutputInfo[22]="distant open door";
	m_sStrOutputInfo[23]="distant close door";
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
	m_sStrOutputInfo[37]="Bluetooth name";
	m_sStrOutputInfo[38]="Bluetooth Password";

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

#endif


	


	//��ȡȡ�����ļ�
	ReadorWriteIniFile();

	CSDK_DEMO_VCDlg dlg;
	m_pMainWnd = &dlg;
	g_pMainDlg = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

BOOL CSDK_DEMO_VCApp::ReadorWriteIniFile(BOOL Read)
{

	CString iniNamestr;//,SoftLookModeStr,SoftAppLookStr;
	CString tempath,Filepath;
	CFile theFile;
	TCHAR chara[MAX_PATH];
	::GetModuleFileName(NULL,chara,MAX_PATH);   
	Filepath=chara; 
	Filepath=Filepath.Left(Filepath.ReverseFind('\\'));
	ExeFilePath=Filepath;

	iniNamestr = ExeFilePath+"\\Config.ini";
	CFileFind finder;
	BOOL m_bFind = finder.FindFile(iniNamestr);//Ѱ���ļ�
	if (m_bFind==FALSE)
	{
		AfxMessageBox(iniNamestr+"û���ҵ�");
		return FALSE;
	}
	if(Read)
	{
		
		GetPrivateProfileString("Local_SYSTEMPARAMETER","Local_ComputerIP","192.168.1.253",	m_sLocalComputerIP.GetBuffer(MAX_PATH),		MAX_PATH,iniNamestr); 
		GetPrivateProfileString("Local_SYSTEMPARAMETER","Local_ComputerPORT","18887",		m_sLocalComputerPORT.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 
		GetPrivateProfileString("Local_SYSTEMPARAMETER","Local_Device_IP","192.168.1.15",	m_sDevice_IP.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 
		GetPrivateProfileString("Local_SYSTEMPARAMETER","CurCardID","010A0201",	CurCardIDStr.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 
	


	//	GetPrivateProfileString("Local_SYSTEMPARAMETER","Local_serverSQL",".",				Local_serverSQL.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 
	//	GetPrivateProfileString("Local_SYSTEMPARAMETER","Local_usernameSQL","sa",			Local_usernameSQL.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 
	//	GetPrivateProfileString("Local_SYSTEMPARAMETER","Local_passwordSQL","",				Local_passwordSQL.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 
		m_sLocalComputerIP.ReleaseBuffer();
		m_sLocalComputerPORT.ReleaseBuffer();
	//	Local_usernameSQL.ReleaseBuffer();
	//	Local_passwordSQL.ReleaseBuffer();
	}
	else
	{
		WritePrivateProfileString("Local_SYSTEMPARAMETER","Local_ComputerIP",	m_sLocalComputerIP,		iniNamestr); 
		WritePrivateProfileString("Local_SYSTEMPARAMETER","Local_ComputerPORT",	m_sLocalComputerPORT,	iniNamestr); 
		WritePrivateProfileString("Local_SYSTEMPARAMETER","Local_Device_IP",	m_sDevice_IP,	iniNamestr); 
		WritePrivateProfileString("Local_SYSTEMPARAMETER","CurCardID",	CurCardIDStr,	iniNamestr);
		

		//WritePrivateProfileString("Local_DataBaseSetting","Local_usernameSQL",	Local_usernameSQL,	iniNamestr); 
	//	WritePrivateProfileString("Local_DataBaseSetting","Local_passwordSQL",	Local_passwordSQL,	iniNamestr); 
	}

	return TRUE;
}

BOOL CSDK_DEMO_VCApp::GetIPCards()
{
    char szHostname[256];
    if (gethostname(szHostname, sizeof(szHostname)))
    {
        TRACE(_T("Failed in call to gethostname, WSAGetLastError returns %d\n"), WSAGetLastError());
        return FALSE;
    }
    //get host information from the host name
    HOSTENT* pHostEnt = gethostbyname(szHostname);
    if (pHostEnt == NULL)
    {
        TRACE(_T("Failed in call to gethostbyname, WSAGetLastError returns %d\n"), WSAGetLastError());
        return FALSE;
    }

    //check the length of the IP adress
    if (pHostEnt->h_length != 4)
    {
        TRACE(_T("IP address returned is not 32 bits !!\n"));
        return FALSE;
    }

    //call the virtual callback function in a loop
    int nAdapter = 0;
    CString strtmp;
    while (pHostEnt->h_addr_list[nAdapter])
    {
        in_addr address;
        CopyMemory(&address.S_un.S_addr, pHostEnt->h_addr_list[nAdapter], pHostEnt->h_length);
        strtmp=inet_ntoa(address);
        SysNetCardArray.Add(strtmp);
        nAdapter++;
    }
	//if(nAdapter>1)
		//lpMainFrame->MessageBoxCai("ע�⣺�����ж���������ڣ���鿴���IP��ַѡ���Ƿ���ȷ?");
	return TRUE;
}

int CSDK_DEMO_VCApp::ExitInstance() 
{
	if(m_hLangDLL)
	{
		AfxFreeLibrary(m_hLangDLL);
	}
	NET_CARD_Cleanup();
	SysNetCardArray.RemoveAll();
	


	return CWinApp::ExitInstance();
}
//��BYTE ���ݱ��CString
//nType =0 ֱ�ӽ�unsigned char ����ת����16���Ʊ�ʾ��CString
//nType =0 ֱ�ӽ�unsigned char ����IP��ַ��ʾ��CString
CString CSDK_DEMO_VCApp::TransfromBYTE(unsigned char *pByteArray,int dwCount,int nType)
{
	CString strData,strTmp;
	if(nType==0)
	{
		for(int i = 0;i<dwCount;i++)
		{
			strTmp.Format("%02X", (BYTE)pByteArray[i]); 
			strData+=strTmp;
		}
	}
	else if(nType==1)
	{
		for(int i = 0;i<dwCount;i++)
		{
			strTmp.Format("%d", (BYTE)pByteArray[i]); 
			if(i!=0)
			{
			   strData=strData+"."+strTmp;
			}else{
				strData=strTmp;
			}
		}
	}
	return strData;
}

//��BYTE ASCII��ʾ��ʽ��ɱ��CString
CString CSDK_DEMO_VCApp::TransfromASCII(unsigned char *pByteArray, int dwCount)
{
	char strr[2];
	CString strData,strData2,strTmp;
	for(int i = 0;i < dwCount; i++)
	{	
 		sprintf(strr, "%c", (BYTE)pByteArray[i]); 
 		strData+=strr;
 	}
	return strData;
}

//CString 192.168.1.45 to *char
BOOL CSDK_DEMO_VCApp::TransIPfromCStringtoBYTE(CString m_sIP, unsigned char *IPArray)
{
	int ii1,ii2;
	ii1=0;
	for(int kk=0;kk<3;kk++)
	{		
		ii2=m_sIP.Find(".",ii1);
		sprintf((char *)IPArray+kk, "%c", atoi(m_sIP.Mid(ii1,ii2-ii1))); 
		ii1=ii2+1;
	}
	sprintf((char *)IPArray+3, "%c", atoi(m_sIP.Mid(ii1,m_sIP.GetLength()))); 
	return TRUE;
}
