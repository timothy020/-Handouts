// QR_Setting.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "QR_Setting.h"
#include "QR_SettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQR_SettingApp

BEGIN_MESSAGE_MAP(CQR_SettingApp, CWinApp)
	//{{AFX_MSG_MAP(CQR_SettingApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQR_SettingApp construction

CQR_SettingApp::CQR_SettingApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CQR_SettingApp object

CQR_SettingApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CQR_SettingApp initialization

BOOL CQR_SettingApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif



	ReadorWriteIniFile(TRUE);

	CQR_SettingDlg dlg;
	m_pMainWnd = &dlg;
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
//将重要的参数进行保存
BOOL CQR_SettingApp::ReadorWriteIniFile(BOOL Read)
{
	CString iniNamestr;//,SoftLookModeStr,SoftAppLookStr;
	CString tempath,Filepath;
	CFile theFile;
	TCHAR chara[MAX_PATH];
	::GetModuleFileName(NULL,chara,MAX_PATH);   
	Filepath=chara; 
	Filepath=Filepath.Left(Filepath.ReverseFind('\\'));
	ExeFilePath=Filepath;

	iniNamestr = ExeFilePath+"\\QRQRConfig.ini";
	CFileFind finder;
	BOOL m_bFind = finder.FindFile(iniNamestr);//寻找文件
	if (m_bFind==FALSE)
	{
		AfxMessageBox(iniNamestr+"没有找到");
		return FALSE;
	}
	if(Read)
	{
	/*	
		GetPrivateProfileString("Local_SYSTEMPARAMETER","Local_ComputerIP","192.168.1.253",	m_sLocalComputerIP.GetBuffer(MAX_PATH),		MAX_PATH,iniNamestr); 
		GetPrivateProfileString("Local_SYSTEMPARAMETER","Local_ComputerPORT","18887",		m_sLocalComputerPORT.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 
		GetPrivateProfileString("Local_SYSTEMPARAMETER","Local_Device_IP","192.168.1.15",	m_sDevice_IP.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 
		GetPrivateProfileString("Local_SYSTEMPARAMETER","CurCardID","010A0201",	CurCardIDStr.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 
	*/
		GetPrivateProfileString("Local_QRCODEPARA","DeviceKey",		"00543210",			DeviceKeyStr.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 
		GetPrivateProfileString("Local_QRCODEPARA","DeviceKey2",	"00123456",			DeviceKeyStr2.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 
		GetPrivateProfileString("Local_QRCODEPARA","TCPServerIP",	"192.168.1.253",	TCPServerIPStr.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 
		GetPrivateProfileString("Local_QRCODEPARA","TCPServerPort",	"18887",			TCPServerPortStr.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 
		GetPrivateProfileString("Local_QRCODEPARA","UDPServerIP",	"192.168.1.253",	UDPServerIPStr.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 
		GetPrivateProfileString("Local_QRCODEPARA","UDPServerPort",	"18887",			UDPServerPortStr.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 
		GetPrivateProfileString("Local_QRCODEPARA","RecordServerIP","192.168.1.253",	RecordServerIPStr.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 
		GetPrivateProfileString("Local_QRCODEPARA","RecordServerPort","18887",			RecordServerPortStr.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 

		GetPrivateProfileString("Local_QRCODEPARA","QR_IDStr",		"00000018",			QR_IDStr.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 
		GetPrivateProfileString("Local_QRCODEPARA","QR_Count",		"01",				QR_Count.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 
		GetPrivateProfileString("Local_QRCODEPARA","QR_StartTime",	"1701121015",		QR_StartTime.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 
		GetPrivateProfileString("Local_QRCODEPARA","QR_EndTime",	"1701151015",		QR_EndTime.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 
		GetPrivateProfileString("Local_QRCODEPARA","QR_DeviceTime",	"171015",			QR_DeviceTime.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 
		GetPrivateProfileString("Local_QRCODEPARA","QR_DeviceMACs",	"1115",				QR_DeviceMACs.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 

		GetPrivateProfileString("Local_QRCODEPARA","QR_OpenDelay",	"10",				QR_OpenDelay.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 
		GetPrivateProfileString("Local_QRCODEPARA","QR_TimeLimit",	"1",				QR_TimeLimit.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 
		GetPrivateProfileString("Local_QRCODEPARA","QR_OpenType",	"2",				QR_OpenType.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 
		GetPrivateProfileString("Local_QRCODEPARA","QR_ProjectCode","51810102",			QR_ProjectCode.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 
		GetPrivateProfileString("Local_QRCODEPARA","QR_StringNoEncrypt","0",			QR_StringNoEncrypt.GetBuffer(MAX_PATH),	MAX_PATH,iniNamestr); 


		QR_IDStr.ReleaseBuffer();
		QR_Count.ReleaseBuffer();
		QR_StartTime.ReleaseBuffer();
		QR_EndTime.ReleaseBuffer();
		QR_DeviceTime.ReleaseBuffer();
		QR_DeviceMACs.ReleaseBuffer();

		DeviceKeyStr.ReleaseBuffer();
		DeviceKeyStr2.ReleaseBuffer();
		TCPServerIPStr.ReleaseBuffer();
		TCPServerPortStr.ReleaseBuffer();
		UDPServerIPStr.ReleaseBuffer();
		UDPServerPortStr.ReleaseBuffer();
		RecordServerIPStr.ReleaseBuffer();
		RecordServerPortStr.ReleaseBuffer();
		QR_OpenDelay.ReleaseBuffer();
		QR_TimeLimit.ReleaseBuffer();
		QR_OpenType.ReleaseBuffer();
		QR_ProjectCode.ReleaseBuffer();
		QR_StringNoEncrypt.ReleaseBuffer();
		


	}
	else
	{
		WritePrivateProfileString("Local_QRCODEPARA","DeviceKey",			DeviceKeyStr,		iniNamestr); 
		WritePrivateProfileString("Local_QRCODEPARA","DeviceKey2",			DeviceKeyStr2,		iniNamestr); 
		WritePrivateProfileString("Local_QRCODEPARA","TCPServerIP",			TCPServerIPStr,		iniNamestr); 
		WritePrivateProfileString("Local_QRCODEPARA","TCPServerPort",		TCPServerPortStr,	iniNamestr); 
		WritePrivateProfileString("Local_QRCODEPARA","UDPServerIP",			UDPServerIPStr,		iniNamestr); 
		WritePrivateProfileString("Local_QRCODEPARA","UDPServerPort",		UDPServerPortStr,	iniNamestr); 
		WritePrivateProfileString("Local_QRCODEPARA","RecordServerIP",		RecordServerIPStr,		iniNamestr); 
		WritePrivateProfileString("Local_QRCODEPARA","RecordServerPort",	RecordServerPortStr,	iniNamestr); 
	
		WritePrivateProfileString("Local_QRCODEPARA","QR_IDStr",		QR_IDStr,		iniNamestr); 
		WritePrivateProfileString("Local_QRCODEPARA","QR_Count",		QR_Count,		iniNamestr); 
		WritePrivateProfileString("Local_QRCODEPARA","QR_StartTime",	QR_StartTime,	iniNamestr); 
		WritePrivateProfileString("Local_QRCODEPARA","QR_EndTime",		QR_EndTime,		iniNamestr); 
		WritePrivateProfileString("Local_QRCODEPARA","QR_DeviceTime",	QR_DeviceTime,	iniNamestr); 
		WritePrivateProfileString("Local_QRCODEPARA","QR_DeviceMACs",	QR_DeviceMACs,	iniNamestr);

		WritePrivateProfileString("Local_QRCODEPARA","QR_OpenDelay",	QR_OpenDelay,	iniNamestr);
		WritePrivateProfileString("Local_QRCODEPARA","QR_TimeLimit",	QR_TimeLimit,	iniNamestr);
		WritePrivateProfileString("Local_QRCODEPARA","QR_OpenType",		QR_OpenType,	iniNamestr);

		WritePrivateProfileString("Local_QRCODEPARA","QR_ProjectCode",	QR_ProjectCode,	iniNamestr);
		WritePrivateProfileString("Local_QRCODEPARA","QR_StringNoEncrypt",	QR_StringNoEncrypt,	iniNamestr);


/*
		WritePrivateProfileString("Local_SYSTEMPARAMETER","Local_ComputerIP",	m_sLocalComputerIP,		iniNamestr); 
		WritePrivateProfileString("Local_SYSTEMPARAMETER","Local_ComputerPORT",	m_sLocalComputerPORT,	iniNamestr); 
		WritePrivateProfileString("Local_SYSTEMPARAMETER","Local_Device_IP",	m_sDevice_IP,	iniNamestr); 
		WritePrivateProfileString("Local_SYSTEMPARAMETER","CurCardID",	CurCardIDStr,	iniNamestr);
*/		
	}

	return TRUE;
}
