// DlgEditforViewIP.cpp : implementation file
//

#include "stdafx.h"
#include "SDK_DEMO_VC.h"
#include "DlgEditforViewIP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEditforViewIP dialog


CDlgEditforViewIP::CDlgEditforViewIP(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEditforViewIP::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEditforViewIP)
	m_sEditDlg = _T("192.168.1.15");
	m_sEditDlgPort = _T("9998");
	//}}AFX_DATA_INIT
}


void CDlgEditforViewIP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEditforViewIP)
	DDX_Text(pDX, IDC_EDIT_DLGEDITIP, m_sEditDlg);
	DDX_Text(pDX, IDC_EDIT_DLGEDITIP2, m_sEditDlgPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEditforViewIP, CDialog)
	//{{AFX_MSG_MAP(CDlgEditforViewIP)
	ON_BN_CLICKED(IDC_IPCHECK1, OnIpcheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEditforViewIP message handlers

void CDlgEditforViewIP::OnIpcheck1() 
{
	((CButton*)GetDlgItem(IDC_EDIT_DLGEDITIP))->SetWindowText("255.255.255.255");	

}

BOOL CDlgEditforViewIP::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	((CButton*)GetDlgItem(IDC_EDIT_DLGEDITIP))->SetWindowText("255.255.255.255");	
	((CButton*)GetDlgItem(IDC_IPCHECK1))->SetCheck(1);	

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
