// SDK_DEMO_VCDlg.h : header file
//

#if !defined(AFX_SDK_DEMO_VCDLG_H__F840663C_3F5F_4616_8E18_C068EC3DCBC8__INCLUDED_)
#define AFX_SDK_DEMO_VCDLG_H__F840663C_3F5F_4616_8E18_C068EC3DCBC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSDK_DEMO_VCDlg dialog

class CSDK_DEMO_VCDlg : public CDialog
{
// Construction
public:
	CSDK_DEMO_VCDlg(CWnd* pParent = NULL);	// standard constructor

public:
	int nCountCai;
public:
	char		 szLocalIP[15];
	char		 DeviceIP[15];
	int			 nLocalPort;
	int			 nDevicePort;
	int			 WaitTimout;
	int			 nRet;
	CString      m_sReturnError;
	char		 ReMACBuffer[10];

	int			 nReaderNo;    //reader 1-4,
	int			 nReaderRight;    //reader open access 1-4,
	int          PassType;//card (0) or card+password (1)
	int          OpenType;
	int          RightGroup;

	CString NetParaStr;

public:
	void registerQrCode(CString StartCardNo,CString QRStartCodeStr,int nQRLength,int nNumber=1);

	BOOL ShowPicJPG(void *src, DWORD size);
	void Qsortcai(unsigned int a[], int left, int right);
	void DisplayInfoforRecieve(LPCTSTR str);
	void AddStringtoList(CString OperatStatus,CString EventExplain=_T(""),CString ErrorInfo=_T(""));
	void BroadCastForFillList(NET_CARD_DEVICENETPARA *pNetParameter, char *pReturnIP, int *nIPLength, char *pReturnMAC);
	BOOL InitNetSDK();
	static UINT RevThreadProc(LPVOID pParam);
// Dialog Data
	//{{AFX_DATA(CSDK_DEMO_VCDlg)
	enum { IDD = IDD_SDK_DEMO_VC_DIALOG };
	CStatic	m_cOriPicStatic;
	CEdit	m_wndList1;
	CListCtrl	m_wndOutputList;
	CString	m_sCOM_MAC;
	CString	m_sCOM_PORT;
	CString	m_sCOM_MASK;
	CString	m_sCOM_GATE;
	CString	m_sCOM_IP;
	CString	m_sNEW_MAC;
	CString	m_sNEW_GATE;
	CString	m_sNEW_MASK;
	CString	m_sNEW_PORT;
	CString	m_sNEW_IP;
	CString	m_sLocalPort;
	int		m_nLockDelay;
	int		m_nAlarmOutDelay1;
	int		m_nAlarmOutDelay2;
	int		m_nAlarmOutDelay3;
	int		m_nAlarmOutDelay4;
	CString	m_sPassword1;
	CString	m_sPassword2;
	CString	m_sPassword3;
	CString	m_sPassword4;
	CString	m_sDruessPass;
	int		m_nDruessDelay;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDK_DEMO_VCDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSDK_DEMO_VCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnButton31Serach();
	afx_msg void OnButton2();
	afx_msg void OnButton1Setnetwork();
	afx_msg void OnButton3();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton28();
	afx_msg void OnButton29();
	afx_msg void OnDoorCheck1();
	afx_msg void OnDoorCheck2();
	afx_msg void OnDoorCheck3();
	afx_msg void OnDoorCheck4();
	afx_msg void OnButton16();
	afx_msg void OnButton17();
	afx_msg void OnButton18();
	afx_msg void OnButton19();
	afx_msg void OnButton22();
	afx_msg void OnButton23();
	afx_msg void OnDoorCheck11();
	afx_msg void OnButton24();
	afx_msg void OnButton25();
	afx_msg void OnButton27();
	afx_msg void OnButton26();
	afx_msg void OnButton31();
	afx_msg void OnButton30();
	afx_msg void OnDoorCheck5();
	afx_msg void OnDoorCheck6();
	afx_msg void OnDoorCheck7();
	afx_msg void OnDoorCheck8();
	afx_msg void OnDoorCheck9();
	afx_msg void OnDoorCheck10();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnButton12();
	afx_msg void OnButton13();
	afx_msg void OnButton14();
	afx_msg void OnButton20();
	afx_msg void OnButton21();
	afx_msg void OnButton15();
	afx_msg void OnButton9();
	afx_msg void OnButton33();
	afx_msg void OnButton34();
	afx_msg void OnButton35();
	afx_msg void OnButton36();
	afx_msg void OnButton37();
	afx_msg void OnButton32();
	afx_msg void OnButton38();
	afx_msg void OnButton31Serach2();
	afx_msg void OnButton39();
	afx_msg void OnButton31Serach3();
	afx_msg void OnButton31Serach5();
	afx_msg void OnButton31Serach7();
	afx_msg void OnButton31Serach4();
	afx_msg void OnButton31Serach9();
	afx_msg void OnButton31Serach10();
	afx_msg void OnButton31Serach6();
	afx_msg void OnButton40();
	afx_msg void OnDoorCheck17();
	afx_msg void OnOk2();
	afx_msg void OnButton31Serach11();
	afx_msg void OnButton31Serach12();
	afx_msg void OnCancelsave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDK_DEMO_VCDLG_H__F840663C_3F5F_4616_8E18_C068EC3DCBC8__INCLUDED_)
