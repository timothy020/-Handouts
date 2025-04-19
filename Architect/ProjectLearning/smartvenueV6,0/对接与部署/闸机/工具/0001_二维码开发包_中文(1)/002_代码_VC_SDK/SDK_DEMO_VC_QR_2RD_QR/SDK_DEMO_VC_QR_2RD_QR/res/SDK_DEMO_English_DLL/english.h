// english.h : main header file for the ENGLISH DLL
//

#if !defined(AFX_ENGLISH_H__33916005_D9FA_4A2C_AC47_0179E0570489__INCLUDED_)
#define AFX_ENGLISH_H__33916005_D9FA_4A2C_AC47_0179E0570489__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEnglishApp
// See english.cpp for the implementation of this class
//

class CEnglishApp : public CWinApp
{
public:
	CEnglishApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnglishApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CEnglishApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENGLISH_H__33916005_D9FA_4A2C_AC47_0179E0570489__INCLUDED_)
