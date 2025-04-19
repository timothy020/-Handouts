#if !defined(AFX_DLGEDITFORVIEWIP_H__40770812_AA31_47DE_91C9_5758E8BC89C0__INCLUDED_)
#define AFX_DLGEDITFORVIEWIP_H__40770812_AA31_47DE_91C9_5758E8BC89C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEditforViewIP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgEditforViewIP dialog

class CDlgEditforViewIP : public CDialog
{
// Construction
public:
	CDlgEditforViewIP(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgEditforViewIP)
	enum { IDD = IDD_DIALOG_EDIT1 };
	CString	m_sEditDlg;
	CString	m_sEditDlgPort;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEditforViewIP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgEditforViewIP)
	afx_msg void OnIpcheck1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEDITFORVIEWIP_H__40770812_AA31_47DE_91C9_5758E8BC89C0__INCLUDED_)
