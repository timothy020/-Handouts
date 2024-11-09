// QR_SettingDlg.h : header file
//

#if !defined(AFX_QR_SETTINGDLG_H__B82E0F16_A549_42C2_9680_F1A72D55575B__INCLUDED_)
#define AFX_QR_SETTINGDLG_H__B82E0F16_A549_42C2_9680_F1A72D55575B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CQR_SettingDlg dialog

class CQR_SettingDlg : public CDialog
{
// Construction
public:
	int ProductImage(CString QRString);
	CQR_SettingDlg(CWnd* pParent = NULL);	// standard constructor
public:
	CDC* m_pSymbleDC;
	CBitmap* m_pOldBitmap;
	CBitmap* m_pSymbleBitmap;
	int m_nSymbleSize;
	CString QRFileNameStr;
	CString QRPreStr;
public:
	CString TransIPfromCStringtoBYTE(CString m_sIP);
	int decryptXXTEA(CString DeCodeStr,unsigned int *a);
	int TranHexStrToInt(CString QRString,unsigned int *a);
	CString encryptXXTEA(CString QRString,BOOL isNewKey=FALSE);
	unsigned int btea(unsigned int *v, int n, unsigned int *k);//unsigned int *v, int n, unsigned int *k
	CString GenerateQRBMP(CString QRString,BOOL isNewKey=FALSE);
	BOOL ShowQRPic(CString strFile);
	int  SaveQRtoPic(CString FileName, int nSize=6);
	BOOL m_bStartSetTimer;
public:
	void totalAllCheck(int nType);
	CString GenerateQRBMPQR(CString QRString);
// Dialog Data
	//{{AFX_DATA(CQR_SettingDlg)
	enum { IDD = IDD_QR_SETTING_DIALOG };
	CDateTimeCtrl	m_cEndTime;
	CDateTimeCtrl	m_cEndDate;
	CDateTimeCtrl	m_cStartTime;
	CDateTimeCtrl	m_cStartDate;
	COleDateTime	m_StartDate;
	COleDateTime	m_EndDate;
	COleDateTime	m_StartTime;
	COleDateTime	m_EndTime;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQR_SettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CQR_SettingDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButton1();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton2();
	afx_msg void OnButton6();
	afx_msg void OnButton11();
	afx_msg void OnButton7();
	afx_msg void OnButton9();
	afx_msg void OnButton8();
	afx_msg void OnButton10();
	afx_msg void OnButton18();
	afx_msg void OnButton13();
	afx_msg void OnButton14();
	afx_msg void OnButton24();
	afx_msg void OnButton19();
	afx_msg void OnButton20();
	afx_msg void OnButton21();
	afx_msg void OnButton22();
	afx_msg void OnButton23();
	afx_msg void OnButton5();
	afx_msg void OnCheck1();
	afx_msg void OnButton12();
	afx_msg void OnButton16();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnAradio3();
	afx_msg void OnAradio4();
	afx_msg void OnAradio5();
	afx_msg void OnButton17();
	afx_msg void OnButton15();
	afx_msg void OnCheck22();
	afx_msg void OnCheck23();
	afx_msg void OnCheck24();
	afx_msg void OnCheck25();
	afx_msg void OnCheck26();
	afx_msg void OnCheck27();
	afx_msg void OnCheck28();
	afx_msg void OnCheck29();
	afx_msg void OnCheck30();
	afx_msg void OnCheck31();
	afx_msg void OnCheck32();
	afx_msg void OnCheck33();
	afx_msg void OnCheck34();
	afx_msg void OnCheck35();
	afx_msg void OnCheck36();
	afx_msg void OnCheck37();
	afx_msg void OnCheck38();
	afx_msg void OnCheck39();
	afx_msg void OnCheckNokey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QR_SETTINGDLG_H__B82E0F16_A549_42C2_9680_F1A72D55575B__INCLUDED_)
