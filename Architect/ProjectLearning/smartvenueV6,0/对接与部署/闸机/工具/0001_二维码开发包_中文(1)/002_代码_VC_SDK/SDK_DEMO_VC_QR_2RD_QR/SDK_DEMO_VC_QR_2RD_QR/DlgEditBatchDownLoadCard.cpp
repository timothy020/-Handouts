// DlgEditBatchDownLoadCard.cpp : implementation file
//

#include "stdafx.h"
#include "SDK_DEMO_VC.h"
#include "DlgEditBatchDownLoadCard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEditBatchDownLoadCard dialog


CDlgEditBatchDownLoadCard::CDlgEditBatchDownLoadCard(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEditBatchDownLoadCard::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEditBatchDownLoadCard)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgEditBatchDownLoadCard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEditBatchDownLoadCard)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEditBatchDownLoadCard, CDialog)
	//{{AFX_MSG_MAP(CDlgEditBatchDownLoadCard)
	ON_BN_CLICKED(IDC_BATCH_BUTTON1, OnBatchButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEditBatchDownLoadCard message handlers
//自动生成卡号
void CDlgEditBatchDownLoadCard::OnBatchButton1() 
{
	CString  m_sTempStr;
	unsigned int nCardseries;
	nCardseries =0x01020304;
	for(int kk=0;kk<20;kk++)
	{
		m_sTempStr.Format("%08x",nCardseries+kk);
	   ((CEdit*)GetDlgItem(IDC_BATCH_EDIT1+kk))->SetWindowText(m_sTempStr);
	}

}

BOOL CDlgEditBatchDownLoadCard::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString  m_sTempStr;
	unsigned int nCardseries;
	nCardseries =0x01020304;
	for(int kk=0;kk<40;kk++)
	{
		m_sTempStr.Format("%08x",nCardseries+kk);
	   ((CEdit*)GetDlgItem(IDC_BATCH_EDIT1+kk))->SetWindowText(m_sTempStr);
	   
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgEditBatchDownLoadCard::OnOK() 
{
	CString  m_sTempStr;
	unsigned int nCardseries;
	nCardseries =0;
	for(int kk=0;kk<40;kk++)
	{
		m_sTempStr.Format("%08x",nCardseries+kk);
	   ((CEdit*)GetDlgItem(IDC_BATCH_EDIT1+kk))->GetWindowText(m_sTempStr);
	   sscanf(m_sTempStr,"%x", &nCardseries);
	   theApp.nCardArray[kk]=nCardseries;
	}

	CDialog::OnOK();
}
