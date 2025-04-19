// SDK_DEMO_VC.h : main header file for the SDK_DEMO_VC application
//

#if !defined(AFX_SDK_DEMO_VC_H__5DF544F0_07E2_4088_B990_F6002364587A__INCLUDED_)
#define AFX_SDK_DEMO_VC_H__5DF544F0_07E2_4088_B990_F6002364587A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include <Winsock2.h>
#include ".\include\DLNetSDK.h"	
#include "SDK_DEMO_VCDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CSDK_DEMO_VCApp:
// See SDK_DEMO_VC.cpp for the implementation of this class
//
#define WSA_VERSION  MAKEWORD(2,0)
#define MAX_HOSTNAME 256
#define MAX_HOSTADDR 40

class CSDK_DEMO_VCApp : public CWinApp
{
public:
	BOOL ReadorWriteIniFile(BOOL Read=TRUE);
	CSDK_DEMO_VCApp();
public:
	CString   m_sCommandState[13];
	HINSTANCE m_hLangDLL;

	CString	 m_sLocalComputerIP;
	CString	 m_sLocalComputerPORT;
	CString  m_sDevice_IP;

	CString  ExeFilePath;
	CStringArray SysNetCardArray;
	CString CurCardIDStr;
	 unsigned int nCardArray[100];
	 
public:
	BOOL TransIPfromCStringtoBYTE(CString m_sIP, unsigned char  *IPArray);
	CString TransfromASCII(unsigned char *pByteArray,int dwCount);
	CString TransfromBYTE(unsigned char *pByteArray,int dwCount,int nType=0);
public:
	BOOL GetIPCards();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDK_DEMO_VCApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSDK_DEMO_VCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CSDK_DEMO_VCApp theApp;
extern CSDK_DEMO_VCDlg *g_pMainDlg;
extern CString m_sStrOutputInfo[40];
extern CString EventString[100];

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDK_DEMO_VC_H__5DF544F0_07E2_4088_B990_F6002364587A__INCLUDED_)
