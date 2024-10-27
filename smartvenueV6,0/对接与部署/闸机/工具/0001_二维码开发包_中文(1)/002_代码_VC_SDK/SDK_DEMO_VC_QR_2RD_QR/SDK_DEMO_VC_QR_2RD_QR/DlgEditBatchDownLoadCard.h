#if !defined(AFX_DLGEDITBATCHDOWNLOADCARD_H__A62CA79F_A2EE_4F05_B7A1_3A832B866E98__INCLUDED_)
#define AFX_DLGEDITBATCHDOWNLOADCARD_H__A62CA79F_A2EE_4F05_B7A1_3A832B866E98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEditBatchDownLoadCard.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgEditBatchDownLoadCard dialog

class CDlgEditBatchDownLoadCard : public CDialog
{
// Construction
public:
	CDlgEditBatchDownLoadCard(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgEditBatchDownLoadCard)
	enum { IDD = IDD_DIALOG_BATCHLOAD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEditBatchDownLoadCard)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgEditBatchDownLoadCard)
	afx_msg void OnBatchButton1();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEDITBATCHDOWNLOADCARD_H__A62CA79F_A2EE_4F05_B7A1_3A832B866E98__INCLUDED_)
