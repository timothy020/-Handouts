// QR_Setting.h : main header file for the QR_SETTING application
//

#if !defined(AFX_QR_SETTING_H__AA010B48_3B2A_4255_B7F8_30362AEE0D6D__INCLUDED_)
#define AFX_QR_SETTING_H__AA010B48_3B2A_4255_B7F8_30362AEE0D6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CQR_SettingApp:
// See QR_Setting.cpp for the implementation of this class
//

class CQR_SettingApp : public CWinApp
{
public:
	BOOL ReadorWriteIniFile(BOOL Read=TRUE);
	CQR_SettingApp();
public:
	CString ExeFilePath;
	CString DeviceKeyStr;
	CString DeviceKeyStr2;
	CString TCPServerIPStr;
	CString TCPServerPortStr;
	CString UDPServerIPStr;
	CString UDPServerPortStr;
	CString RecordServerIPStr;
	CString RecordServerPortStr;

	CString QR_IDStr;
	CString QR_Count;
	CString QR_StartTime;
	CString QR_EndTime;
	CString QR_DeviceTime;
	CString QR_DeviceMACs;

	CString QR_OpenDelay;
	CString QR_TimeLimit;
	CString QR_OpenType;
	CString QR_ProjectCode;
	CString QR_StringNoEncrypt;
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQR_SettingApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CQR_SettingApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CQR_SettingApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QR_SETTING_H__AA010B48_3B2A_4255_B7F8_30362AEE0D6D__INCLUDED_)
