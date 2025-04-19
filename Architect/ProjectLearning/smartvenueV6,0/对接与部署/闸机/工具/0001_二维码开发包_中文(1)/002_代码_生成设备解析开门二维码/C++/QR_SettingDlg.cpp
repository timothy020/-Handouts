// QR_SettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "QR_Setting.h"
#include "QR_SettingDlg.h"
#include "QR_Encode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQR_SettingDlg dialog

CQR_SettingDlg::CQR_SettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQR_SettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQR_SettingDlg)
	m_StartDate = COleDateTime::GetCurrentTime();
	m_EndDate = COleDateTime::GetCurrentTime();
	m_StartTime = COleDateTime::GetCurrentTime();
	m_EndTime = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nSymbleSize =6;
	m_pSymbleDC=NULL;
	m_pOldBitmap=NULL;
	m_pSymbleBitmap=NULL;

	QRFileNameStr =_T("");
	m_bStartSetTimer =FALSE;

}

void CQR_SettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQR_SettingDlg)
	DDX_Control(pDX, IDC_DATETIME_QUERY4, m_cEndTime);
	DDX_Control(pDX, IDC_DATETIME_QUERY2, m_cEndDate);
	DDX_Control(pDX, IDC_DATETIME_QUERY3, m_cStartTime);
	DDX_Control(pDX, IDC_DATETIME_QUERY, m_cStartDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_QUERY, m_StartDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_QUERY2, m_EndDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_QUERY3, m_StartTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_QUERY4, m_EndTime);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CQR_SettingDlg, CDialog)
	//{{AFX_MSG_MAP(CQR_SettingDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_ARADIO3, OnAradio3)
	ON_BN_CLICKED(IDC_ARADIO4, OnAradio4)
	ON_BN_CLICKED(IDC_ARADIO5, OnAradio5)
	ON_BN_CLICKED(IDC_BUTTON17, OnButton17)
	ON_BN_CLICKED(IDC_BUTTON15, OnButton15)
	ON_BN_CLICKED(IDC_CHECK22, OnCheck22)
	ON_BN_CLICKED(IDC_CHECK23, OnCheck23)
	ON_BN_CLICKED(IDC_CHECK24, OnCheck24)
	ON_BN_CLICKED(IDC_CHECK25, OnCheck25)
	ON_BN_CLICKED(IDC_CHECK26, OnCheck26)
	ON_BN_CLICKED(IDC_CHECK27, OnCheck27)
	ON_BN_CLICKED(IDC_CHECK28, OnCheck28)
	ON_BN_CLICKED(IDC_CHECK29, OnCheck29)
	ON_BN_CLICKED(IDC_CHECK30, OnCheck30)
	ON_BN_CLICKED(IDC_CHECK31, OnCheck31)
	ON_BN_CLICKED(IDC_CHECK32, OnCheck32)
	ON_BN_CLICKED(IDC_CHECK33, OnCheck33)
	ON_BN_CLICKED(IDC_CHECK34, OnCheck34)
	ON_BN_CLICKED(IDC_CHECK35, OnCheck35)
	ON_BN_CLICKED(IDC_CHECK36, OnCheck36)
	ON_BN_CLICKED(IDC_CHECK37, OnCheck37)
	ON_BN_CLICKED(IDC_CHECK38, OnCheck38)
	ON_BN_CLICKED(IDC_CHECK39, OnCheck39)
	ON_BN_CLICKED(IDC_CHECK_NOKEY, OnCheckNokey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQR_SettingDlg message handlers

BOOL CQR_SettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	((CEdit*)GetDlgItem(IDC_EDIT4))->SetWindowText(theApp.DeviceKeyStr);
	((CEdit*)GetDlgItem(IDC_EDIT35))->SetWindowText(theApp.DeviceKeyStr2);

	((CEdit*)GetDlgItem(IDC_EDIT22))->SetWindowText(theApp.QR_IDStr);

	((CEdit*)GetDlgItem(IDC_EDIT9))->SetWindowText(theApp.QR_Count);


	((CEdit*)GetDlgItem(IDC_EDIT10))->SetWindowText(theApp.QR_OpenDelay);


	if(theApp.QR_TimeLimit=="1")
	{
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(1);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);
		((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(0);
	}

	if(theApp.QR_OpenType=="0")
	{
		OnAradio3() ;
	}
	else if(theApp.QR_OpenType=="1")
	{
		OnAradio4();
	}
	else if(theApp.QR_OpenType=="2")
	{
		OnAradio5();
	}

	CString tmpstr;
	CTimeSpan timeSpan(10,0,0,0);
	CTime curTime = CTime::GetCurrentTime();
	CTime dateFrom = curTime + timeSpan;

	m_EndDate.SetDateTime(dateFrom.GetYear(), dateFrom.GetMonth(), dateFrom.GetDay(), 
			dateFrom.GetHour(), dateFrom.GetMinute(), dateFrom.GetSecond());

	UpdateData(FALSE);

	((CEdit*)GetDlgItem(IDC_EDIT1))->SetWindowText("UserDataInput");
	

	((CEdit*)GetDlgItem(IDC_EDIT23))->SetWindowText(theApp.QR_ProjectCode);


	for(int kk=0;kk<3;kk++)
	{
		((CButton*)GetDlgItem(IDC_CHECK22+kk))->SetCheck(1);
		CString StrTmp;
		StrTmp.Format("030105%02d",kk+1);
		((CEdit*)GetDlgItem(IDC_EDIT12+kk))->SetWindowText(StrTmp);
	}
	for( kk=0;kk<3;kk++)
	{
		((CButton*)GetDlgItem(IDC_CHECK31+kk))->SetCheck(1);
		CString StrTmp;
		StrTmp.Format("9210%02d",kk+1);
		((CEdit*)GetDlgItem(IDC_EDIT26+kk))->SetWindowText(StrTmp);
	}
	((CEdit*)GetDlgItem(IDC_EDIT24))->SetWindowText("3");
	((CEdit*)GetDlgItem(IDC_EDIT25))->SetWindowText("3");

	if(theApp.QR_StringNoEncrypt=="1")
	{
		((CButton*)GetDlgItem(IDC_CHECK_NOKEY))->SetCheck(1);
		theApp.DeviceKeyStr="00000000";
		((CEdit*)GetDlgItem(IDC_EDIT4))->SetWindowText(theApp.DeviceKeyStr);
	}
	else
	{
	    ((CButton*)GetDlgItem(IDC_CHECK_NOKEY))->SetCheck(0);
	}
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CQR_SettingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CQR_SettingDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CQR_SettingDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//产生二维码
int CQR_SettingDlg::ProductImage(CString QRString)
{
	int nLevel = 1;//m_pwndRightView->m_comboLevel.GetCurSel();//Lever 1
	int nVersion =0;// m_pwndRightView->m_comboVersion.GetCurSel();//version 0
	BOOL bAutoExtent = 1;//(m_pwndRightView->m_checkAutoExtent.GetCheck() != 0);//自动拉伸1
	int nMaskingNo = -1;//m_pwndRightView->m_comboMaskingNo.GetCurSel() - 1;//边框 -1

	CString strEncodeData;

	strEncodeData = QRString;
	
	int i, j;

	CQR_Encode* pQR_Encode = new CQR_Encode;

	BOOL m_bDataEncoded = pQR_Encode->EncodeData(nLevel, nVersion, bAutoExtent, nMaskingNo, strEncodeData);

	if (m_bDataEncoded)
	{
		if (m_pSymbleDC != NULL)
		{
			m_pSymbleDC->SelectObject(m_pOldBitmap);

			delete m_pSymbleBitmap;
			delete m_pSymbleDC;
		}

		m_nSymbleSize = pQR_Encode->m_nSymbleSize + (QR_MARGIN * 2);

		m_pSymbleBitmap = new CBitmap;
		m_pSymbleBitmap->CreateBitmap(m_nSymbleSize, m_nSymbleSize, 1, 1, NULL);

		m_pSymbleDC = new CDC;
		m_pSymbleDC->CreateCompatibleDC(NULL);

		m_pOldBitmap = m_pSymbleDC->SelectObject(m_pSymbleBitmap);

		m_pSymbleDC->PatBlt(0, 0, m_nSymbleSize, m_nSymbleSize, WHITENESS);

		for (i = 0; i < pQR_Encode->m_nSymbleSize; ++i)
		{
			for (j = 0; j < pQR_Encode->m_nSymbleSize; ++j)
			{
				if (pQR_Encode->m_byModuleData[i][j])
				{
					m_pSymbleDC->SetPixel(i + QR_MARGIN, j + QR_MARGIN, RGB(0, 0, 0));
				}
			}
		}

	}
	if(pQR_Encode)
	{
		delete pQR_Encode;
		pQR_Encode =NULL;
	}
	if(m_bDataEncoded)
		return 1;
	else
		return 0;
}
//把生成的二维码生成图片
int CQR_SettingDlg::SaveQRtoPic(CString FileName, int nSize)
{
	int nPixelSize = m_nSymbleSize * nSize;
	if(nSize<=0)
	{
		nSize=1;
	}

	int nBmpSize = ((nPixelSize + 31) / 32) * 32 / 8;
	nBmpSize *= nPixelSize;

	CString m_strSavePath =FileName;

	HANDLE hFile = CreateFile(m_strSavePath, GENERIC_READ | GENERIC_WRITE, 0, NULL,
							  CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{		
#ifdef ENGLISHC
		AfxMessageBox(m_strSavePath+"File read or write Fail",  MB_ICONSTOP);
#else
		AfxMessageBox(m_strSavePath+"文件读写失败",  MB_ICONSTOP);
#endif
		m_strSavePath.Empty();
		return FALSE;
	}

	HANDLE hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READWRITE | SEC_COMMIT, 0, 
						  sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 2 + nBmpSize, NULL);
	LPBYTE lpbyMapView = (LPBYTE)MapViewOfFile(hFileMapping, FILE_MAP_WRITE, 0, 0, 0);

	ZeroMemory(lpbyMapView, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 2 + nBmpSize);


	LPBITMAPFILEHEADER pbfh = (LPBITMAPFILEHEADER)lpbyMapView;
	LPBITMAPINFO       pbmi = (LPBITMAPINFO)(lpbyMapView + sizeof(BITMAPFILEHEADER));
	LPVOID             pbdt = lpbyMapView + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 2;

	// BITMAPFILEHEADER
	pbfh->bfType      = (WORD) (('M' << 8) | 'B'); // "BM"
	pbfh->bfSize      = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 2 + nBmpSize;
	pbfh->bfReserved1 = 0;
	pbfh->bfReserved2 = 0;
	pbfh->bfOffBits   = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 2;

	// LPBITMAPINFO->BITMAPINFOHEADER
	pbmi->bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth			= nPixelSize;
	pbmi->bmiHeader.biHeight		= nPixelSize;
	pbmi->bmiHeader.biPlanes		= 1;
	pbmi->bmiHeader.biBitCount		= 1;
	pbmi->bmiHeader.biCompression	= BI_RGB;
	pbmi->bmiHeader.biSizeImage		= nBmpSize;
	pbmi->bmiHeader.biXPelsPerMeter = 3780;
	pbmi->bmiHeader.biYPelsPerMeter = 3780;
	pbmi->bmiHeader.biClrUsed		= 0;
	pbmi->bmiHeader.biClrImportant	= 0;

	CDC* pWorkDC = new CDC;
	pWorkDC->CreateCompatibleDC(NULL);

	CBitmap* pWorkBitmap = new CBitmap;
	pWorkBitmap->CreateBitmap(nPixelSize, nPixelSize, 1, 1, NULL);

	CBitmap* pOldBitmap = pWorkDC->SelectObject(pWorkBitmap);
	pWorkDC->StretchBlt(0, 0, nPixelSize, nPixelSize, m_pSymbleDC, 0, 0, m_nSymbleSize, m_nSymbleSize, SRCCOPY);

	GetDIBits(pWorkDC->m_hDC, (HBITMAP)*pWorkBitmap, 0, nPixelSize, pbdt, pbmi, DIB_RGB_COLORS);

	pWorkDC->SelectObject(pOldBitmap);
	delete pWorkBitmap;
	delete pWorkDC;

	UnmapViewOfFile(lpbyMapView);
	CloseHandle(hFileMapping);
	CloseHandle(hFile);

	return TRUE;
}
//显示二维码图片到指定位置
BOOL CQR_SettingDlg::ShowQRPic(CString strFile)
{

	if(strFile.IsEmpty())
		return FALSE;
	CRect SnapRect;
	CString lpstrFile;	
	int nScrWidth,nScrHeight;
	HDC hDC_Temp;
	IPicture *pPic=NULL; 
	IStream *pStm=NULL; 
	BOOL bResult; 

	CString   modifyDiskStr,tempstr;

	((CStatic*)GetDlgItem(IDC_STATIC_QRVIEW))->GetClientRect(&SnapRect);
	lpstrFile=strFile;
	nScrWidth=SnapRect.Width();
	nScrHeight=SnapRect.Height();

	hDC_Temp=::GetDC(((CStatic*)GetDlgItem(IDC_STATIC_QRVIEW))->GetSafeHwnd()); 

	HANDLE hFile=NULL; 
	DWORD dwFileSize,dwByteRead; 
	
	//打开硬盘中的图形文件 
	hFile=CreateFile(lpstrFile,GENERIC_READ, 
		FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL); 
	
	if (hFile!=INVALID_HANDLE_VALUE) 
	{ 
		dwFileSize=GetFileSize(hFile,NULL);//获取文件字节数 		
		if (dwFileSize==0xFFFFFFFF) 
			return E_FAIL; 
	} 
	else 
	{ 
		return E_FAIL; 
	} 
	
	//分配全局存储空间 
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, dwFileSize); 

	LPVOID pvData = NULL; 

	if (hGlobal == NULL) 
		return E_FAIL; 
	
	if ((pvData = GlobalLock(hGlobal)) == NULL)//锁定分配内存块 
		return E_FAIL; 
	
	ReadFile(hFile,pvData,dwFileSize,&dwByteRead,NULL);//把文件读入内存缓冲区 

	char	*BMPBufferSnap;
	BMPBufferSnap = new char[dwByteRead + 1];
	if(BMPBufferSnap)
	{
		memcpy(BMPBufferSnap,pvData,dwByteRead);//将二维码图片数据复制到BMPBufferSnap
	}
	
	GlobalUnlock(hGlobal); 
	
	CreateStreamOnHGlobal(hGlobal, TRUE, &pStm); 
	
	//装入图形文件 
	bResult=OleLoadPicture(pStm,dwFileSize,TRUE,IID_IPicture,(LPVOID*)&pPic); 
	
	if(FAILED(bResult)) 
		return E_FAIL; 

	pStm->Release(); 
	pStm=NULL;
	GlobalFree(hGlobal);
	FreeResource(hGlobal); 
	
	OLE_XSIZE_HIMETRIC hmWidth;//图片的真实宽度 
	OLE_YSIZE_HIMETRIC hmHeight;//图片的真实高度 
	pPic->get_Width(&hmWidth); 
	pPic->get_Height(&hmHeight); 
	
	//将图形输出到屏幕上（有点像BitBlt） 
	bResult=pPic->Render(hDC_Temp,0,0,nScrWidth,nScrHeight,0,hmHeight,hmWidth,-hmHeight,NULL); 
	
	pPic->Release(); 
	
	CloseHandle(hFile);//关闭打开的文件 
	::ReleaseDC(m_hWnd,hDC_Temp);
	if (SUCCEEDED(bResult)) 
	{ 

		return S_OK; 
	} 
	else 
	{ 
		return E_FAIL; 
	} 
	if(BMPBufferSnap)
	{
		delete [] BMPBufferSnap	;
		BMPBufferSnap =NULL;
	}
}

void CQR_SettingDlg::OnTimer(UINT nIDEvent) 
{
	CString tmpstr;
	if(nIDEvent==1)
	{
		CTime time=CTime::GetCurrentTime() ;
		tmpstr.Format("%d-%02d-%02d %02d:%02d:%02d",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
		((CEdit*)GetDlgItem(IDC_EDIT1))->SetWindowText(tmpstr);	
		if(m_bStartSetTimer)
		{
			OnButton1();//设置时间
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CQR_SettingDlg::OnButton1() 
{

	CString m_sOperateComm;
	CTime time=CTime::GetCurrentTime() ;
	CString strtt,strt;
	int m_itemp=0;

	m_sOperateComm="113200FF";

    //int nYear,nMonth,nDay,nHour,nMinute,nSecond;
    //sscanf(strTime,"%d-%02d-%02d %02d:%02d:%02d",&nYear,&nMonth,&nDay,&nHour,&nMinute,&nSecond);

	strtt.Format("%d",time.GetYear());//年
	strtt=strtt.Right(2);
	sscanf(strtt, "%x",&m_itemp);
	strtt.Format("%02x",m_itemp);
	strt+=strtt;

	strtt.Format("%02d",time.GetMonth());//月
	sscanf(strtt, "%x",&m_itemp);
	strtt.Format("%02x",m_itemp);
	strt+=strtt;

	strtt.Format("%02d",time.GetDay());//日
	sscanf(strtt, "%x",&m_itemp);
	strtt.Format("%02x",m_itemp);
	strt+=strtt;

	strtt.Format("%02d",time.GetHour());//时
	sscanf(strtt, "%x",&m_itemp);
	strtt.Format("%02x",m_itemp);
	strt+=strtt;


	strtt.Format("%02d",time.GetMinute());//分
	sscanf(strtt, "%x",&m_itemp);
	strtt.Format("%02x",m_itemp);
	strt+=strtt;

	strtt.Format("%02d",time.GetSecond());//秒
	sscanf(strtt, "%x",&m_itemp);
	strtt.Format("%02x",m_itemp);
	strt+=strtt;

	m_sOperateComm+=strt;
	GenerateQRBMP(m_sOperateComm);
	
}
#define     QRKEY            0x00543210
CString CQR_SettingDlg::GenerateQRBMP(CString QRString,BOOL isNewKey)
{
	CString QRStringEnd;
	CString FileNameStr="Aa";


//	QRStringEnd = encryptXXTEA("010302000000000017041116080717041416080702920992920993",isNewKey);


	QRStringEnd = encryptXXTEA(QRString,isNewKey);

	//显示二维码字符串
	((CEdit*)GetDlgItem(IDC_EDIT2))->SetWindowText(QRPreStr + QRStringEnd);

	//生成二维码，存成文件，并显示出来
	if(ProductImage(QRPreStr+QRStringEnd))
	{
		FileNameStr=theApp.ExeFilePath+"\\QRTmpApp.BMP";
		SaveQRtoPic(FileNameStr);
	}
	else
	{
#ifdef ENGLISHC
		AfxMessageBox("Generate QR code Fail");
#else
		AfxMessageBox("生成二维码失败");
#endif
		return FileNameStr;
	}
	ShowQRPic(FileNameStr);	
	//解密测试
	int nRetCount=0;
	unsigned int a[100]={0};

	nRetCount = decryptXXTEA(QRStringEnd,a);
	if(nRetCount)
	{
	   unsigned int key[4] = {QRKEY, QRKEY,QRKEY,QRKEY};
	   unsigned int UserKey,UserKey2;
	   //将用户设置的KEY放到key[4]的key[0],key[2]
	   sscanf(theApp.DeviceKeyStr, "%x",&UserKey);
	   sscanf(theApp.DeviceKeyStr2, "%x",&UserKey2);

	   key[0] = key[2] = UserKey;
	   if(isNewKey)
	   {
		 key[1] = key[3] = UserKey;
	   }
	   else
	   {
		 key[1] = key[3] = UserKey2;
	   }


	   //XXTEA加密
	   btea(a, -nRetCount,key);

	   //得到加密后的字符串
	   //字符串最后一个字节，为了避免出现00001234前面有0000字符串
	   //所以先将数值转换成字符串，如果字符串长度为奇数，则前面补加0，补齐

	   CString StrTmp,DecryptStr;

	   //得到字符串（除最后一个字节外）
	   for(int kk=0;kk<nRetCount-1;kk++)
	   {
		  StrTmp.Format("%08X",a[kk]);
		  DecryptStr+=StrTmp;
	   }
	   int nRemainCount=0;
	   //得到4取整的余数值
	   sscanf(QRStringEnd.Mid(2,2), "%X",&nRemainCount);

	   //最后一个字节的处理
	   StrTmp.Format("%08X",a[nRetCount-1]);

	   
	   if((nRemainCount==0)||(nRemainCount==0x7F))//没有余数 或者是新的设备秘钥（设置设备秘钥的指令是没有余数的）
	   {
		   DecryptStr+=StrTmp;
	   }
	   else if(nRemainCount<=3)//余数1-3，取最后一个数的后面的字符
	   {
		   DecryptStr+=StrTmp.Right(nRemainCount*2);			
	   }

	   //加密整形的个数+加密字符串
	   StrTmp.Format("%02X%02X",nRetCount,nRemainCount);
	   DecryptStr =QRPreStr+StrTmp+theApp.DeviceKeyStr+DecryptStr;

	   ((CEdit*)GetDlgItem(IDC_EDIT7))->SetWindowText(DecryptStr);

	}
	return FileNameStr;
	//OnPrint(FileNameStr,TicketNOStr,RowNameStr,SeatNOStr);
}

void CQR_SettingDlg::OnButton3() 
{
	CString QRStringEnd,QRString;
	CString FileNameStr="Aa";

	((CEdit*)GetDlgItem(IDC_EDIT2))->GetWindowText(QRStringEnd);
	QRStringEnd.TrimLeft();
	QRStringEnd.TrimRight();

	
	//显示二维码字符串
	((CEdit*)GetDlgItem(IDC_EDIT2))->SetWindowText(QRStringEnd);

	//生成二维码，存成文件，并显示出来
	if(ProductImage(QRStringEnd))
	{
		FileNameStr=theApp.ExeFilePath+"\\QRTmpApp.BMP";
		SaveQRtoPic(FileNameStr);
	}
	else
	{
#ifdef ENGLISHC
		AfxMessageBox("Generate QR code Fail");
#else
		AfxMessageBox("生成二维码失败");
#endif
	}
	ShowQRPic(FileNameStr);	
	
}
//生成密钥
void CQR_SettingDlg::OnButton4() 
{
	int seed=0;
	int m_itemp=0;
	CString strtt;
	if(IDOK!=AfxMessageBox("秘钥是设备识别二维码的重要数据，确定要重新设置吗？\n\n默认的密钥是0x00543210,请参看配置文件QRConfig.ini",MB_OKCANCEL|MB_DEFBUTTON2))
		return;

	//产生一个不大于0x0FFFFFFF的随机整数
	seed = (::GetTickCount()) % 0x0FFFFFFF;
	strtt.Format("%08X",seed);
	((CEdit*)GetDlgItem(IDC_EDIT4))->SetWindowText(strtt);


	//将随机数据进行保存
	theApp.DeviceKeyStr = strtt;
	theApp.ReadorWriteIniFile(FALSE);
	
	
}
//XXTEA加密算法
#define MX (z>>5^y<<2) + (y>>3^z<<4)^(sum^y) + (k[p&3^e]^z)
unsigned int CQR_SettingDlg::btea(unsigned int *v, int n, unsigned int *k)
{
	unsigned int z=v[n-1], y=v[0], sum=0, e, DELTA=0x9e3779b9;
	long p, q ;
	if (n > 1) 
	{          
	  q = 6 + 52/n;
	  while (q-- > 0) {
		sum += DELTA;
		e = (sum >> 2) & 3;
		for (p=0; p<n-1; p++) y = v[p+1], z = v[p] += MX;
		y = v[0];
		z = v[n-1] += MX;
	  }
	  return 0 ; 
	} 

	else if (n < -1) 
	{  

	  n = -n;
	  q = 6 + 52/n;
	  sum = q*DELTA ;
	  while (sum != 0) {
		e = (sum >> 2) & 3;
		for (p=n-1; p>0; p--) z = v[p-1], y = v[p] -= MX;
		z = v[n-1];
		y = v[0] -= MX;
		sum -= DELTA;
	  }
	  return 0;
	}
	return 1;

}

#define     QRKEY            0x00543210
CString CQR_SettingDlg::encryptXXTEA(CString QRString,BOOL isNewKey)
{
   unsigned int key[4] = {QRKEY, QRKEY,QRKEY,QRKEY};
   unsigned int UserKey,UserKey2;
   //将用户设置的KEY放到key[4]的key[0],key[2]
   sscanf(theApp.DeviceKeyStr, "%x",&UserKey);
   sscanf(theApp.DeviceKeyStr2, "%x",&UserKey2);
   key[0] = key[2] = UserKey;
   if(isNewKey)
   {
	  key[1] = key[3] = UserKey;
   }
   else
   {
	  key[1] = key[3] = UserKey2;
   }


   //将16进制数值的字符串，变成8位的整形
   int nIntCount=0,nRemainCount=0;
   unsigned int a[100]={0};

   nIntCount = TranHexStrToInt(QRString,a);

   //余数= 剩余几个字节（一个INT整数为4个字节，不够4字节（一个INT），那得告诉解码取4的余数是多少）
   int nLen=QRString.GetLength();
   nRemainCount =(QRString.GetLength()%8)/2;

   //XXTEA加密
   btea(a, nIntCount,key);
   //得到加密后的字符串
   CString StrTmp,encryptStr;
   for(int kk=0;kk<nIntCount;kk++)
   {
	  StrTmp.Format("%08X",a[kk]);
	  encryptStr+=StrTmp;
   }
   //加密整形的个数+加密字符串
   if(isNewKey)
   {
	   nRemainCount=0x7F;
   }

   StrTmp.Format("%02X%02X",nIntCount,nRemainCount);
   encryptStr =StrTmp+theApp.DeviceKeyStr+encryptStr;
   return encryptStr;


}

int CQR_SettingDlg::TranHexStrToInt(CString QRString,unsigned int *a)
{
	int nStrLen=0;
	int nStrAllLen=0;
	CString StrTmp;
	nStrAllLen = QRString.GetLength();
	nStrLen = nStrAllLen/8;
	for(int i=0;i<nStrLen;i++)
	{
		StrTmp = QRString.Mid(i*8,8);
		sscanf(StrTmp, "%x",&a[i]);
	}
	if(nStrAllLen%8!=0)
	{
		StrTmp=QRString.Right(nStrAllLen%8);
		sscanf(StrTmp, "%x",&a[i]);
		nStrLen++;
	}
	return nStrLen;
}

int CQR_SettingDlg::decryptXXTEA(CString DeCodeStr,unsigned int *a)
{

	CString QRString,QRStrLen,StrTmp;
	if(DeCodeStr.GetLength()<=16)
		return 0;

	QRString = DeCodeStr.Right(DeCodeStr.GetLength()-12);

	QRStrLen = DeCodeStr.Mid(0,2);

	int nQRLen = atoi(QRStrLen);

	if((nQRLen*8)!=QRString.GetLength())
	{
		return 0;
	}

	for(int i=0;i<nQRLen;i++)
	{
		StrTmp = QRString.Mid(i*8,8);
		sscanf(StrTmp, "%x",&a[i]);			
	}
	return nQRLen;






}
//调试用远程开门1 5806
void CQR_SettingDlg::OnButton2() 
{
	CString strtt,m_sOperateComm;
	m_sOperateComm="115806FF";
	strtt=_T("010104");
	GenerateQRBMP(m_sOperateComm+strtt);
	
}
//调试用远程开门2 5806
void CQR_SettingDlg::OnButton6() 
{
	CString strtt,m_sOperateComm;
	m_sOperateComm="115806FF";
	strtt=_T("020104");
	GenerateQRBMP(m_sOperateComm+strtt);	
}
//锁1锁2延时（锁3锁4没有启用）
void CQR_SettingDlg::OnButton11() 
{
	CString QRStringEnd;
	CString strtt,m_sOperateComm;
	((CEdit*)GetDlgItem(IDC_EDIT9))->GetWindowText(QRStringEnd);
	QRStringEnd.TrimLeft();
	QRStringEnd.TrimRight();

	int nSecond = 0;
	sscanf(QRStringEnd, "%d",&nSecond);	

	m_sOperateComm="114A00FF";
	strtt.Format("%02X%02X%02X%02X",nSecond,nSecond,nSecond,nSecond);
	GenerateQRBMP(m_sOperateComm+strtt);
	
}
//锁1锁2电控锁
void CQR_SettingDlg::OnButton7() 
{
	CString strtt,m_sOperateComm;
	m_sOperateComm="114A03FF";
	strtt=_T("FF");
	GenerateQRBMP(m_sOperateComm+strtt);
	
}
//锁1锁2磁力锁或电插锁
void CQR_SettingDlg::OnButton8() 
{
	CString strtt,m_sOperateComm;
	m_sOperateComm="114A03FF";
	strtt=_T("F0");
	GenerateQRBMP(m_sOperateComm+strtt);	
	
}
//锁1电控锁锁2磁力锁
void CQR_SettingDlg::OnButton9() 
{
	CString strtt,m_sOperateComm;
	m_sOperateComm="114A03FF";
	strtt=_T("FD");
	GenerateQRBMP(m_sOperateComm+strtt);
}


//锁1磁力锁锁2电控锁
void CQR_SettingDlg::OnButton10() 
{
	CString strtt,m_sOperateComm;
	m_sOperateComm="114A03FF";
	strtt=_T("FE");
	GenerateQRBMP(m_sOperateComm+strtt);	
}
//取消超时报警
void CQR_SettingDlg::OnButton14() 
{
	CString strtt,m_sOperateComm;
	m_sOperateComm="115E00FF";
	strtt=_T("00");
	GenerateQRBMP(m_sOperateComm+strtt);
	
}
//启动记录实时上传
void CQR_SettingDlg::OnButton19() 
{
	CString m_sOperateComm;
	m_sOperateComm="114400FF";
	GenerateQRBMP(m_sOperateComm);
	
}
//停止记录实时上传
void CQR_SettingDlg::OnButton20() 
{

	CString m_sOperateComm;
	m_sOperateComm="114401FF";
	GenerateQRBMP(m_sOperateComm);
	
}
CString CQR_SettingDlg::TransIPfromCStringtoBYTE(CString m_sIP)
{
	int ii1,ii2,ii3;
	CString StrTmp,EndStr;
	ii1=0;
	for(int kk=0;kk<3;kk++)
	{		
		ii2=m_sIP.Find(".",ii1);
		sscanf(m_sIP.Mid(ii1,ii2-ii1), "%d",&ii3);
		StrTmp.Format("%02X",ii3);
		EndStr+=StrTmp;
		ii1=ii2+1;
	}
	sscanf(m_sIP.Mid(ii1,m_sIP.GetLength()-ii1), "%d",&ii3);
	StrTmp.Format("%02X",ii3);
	EndStr+=StrTmp;
	return EndStr;
}

//设置TCP IP和端口
void CQR_SettingDlg::OnButton21() 
{
	CString strtt,m_sOperateComm;
	m_sOperateComm="114407FF";

	int	  nServerPort;

	CString m_sServerIP,m_sServerPort,m_sServerIPEnd;
	
	((CEdit*)GetDlgItem(IDC_EDIT12))->GetWindowText(m_sServerIP);
	m_sServerIP.TrimLeft();
	m_sServerIP.TrimRight();
	
	((CEdit*)GetDlgItem(IDC_EDIT13))->GetWindowText(m_sServerPort);
	m_sServerPort.TrimLeft();
	m_sServerPort.TrimRight();

	sscanf(m_sServerPort, "%d",&nServerPort);	
	strtt.Format("%04X",nServerPort);
	m_sServerIPEnd=TransIPfromCStringtoBYTE(m_sServerIP);
	GenerateQRBMP(m_sOperateComm+m_sServerIPEnd+strtt);

	theApp.TCPServerIPStr	= m_sServerIP;
	theApp.TCPServerPortStr = m_sServerPort;
	theApp.ReadorWriteIniFile(FALSE);	


//02 00 11 FF FF FF FF FF FF 11 44 07 FF C0 A8 01 FD 49 C7 FF 03 
	
}
//设置UDP IP和端口
void CQR_SettingDlg::OnButton22() 
{
	CString strtt,m_sOperateComm;
	m_sOperateComm="114406FF00";

	int	  nServerPort;
	CString m_sServerIP,m_sServerPort,m_sServerIPEnd;
	
	((CEdit*)GetDlgItem(IDC_EDIT14))->GetWindowText(m_sServerIP);
	m_sServerIP.TrimLeft();
	m_sServerIP.TrimRight();
	
	((CEdit*)GetDlgItem(IDC_EDIT15))->GetWindowText(m_sServerPort);
	m_sServerPort.TrimLeft();
	m_sServerPort.TrimRight();

	sscanf(m_sServerPort, "%d",&nServerPort);	
	strtt.Format("%04X",nServerPort);
	m_sServerIPEnd=TransIPfromCStringtoBYTE(m_sServerIP);
	GenerateQRBMP(m_sOperateComm+m_sServerIPEnd+strtt);

	theApp.UDPServerIPStr	= m_sServerIP;
	theApp.UDPServerPortStr = m_sServerPort;
	theApp.ReadorWriteIniFile(FALSE);	

}
//记录上传UDP IP和端口
void CQR_SettingDlg::OnButton23() 
{
	CString strtt,m_sOperateComm;
	m_sOperateComm="114408FF";

	int	  nServerPort;
	CString m_sServerIP,m_sServerPort,m_sServerIPEnd;
	
	((CEdit*)GetDlgItem(IDC_EDIT16))->GetWindowText(m_sServerIP);
	m_sServerIP.TrimLeft();
	m_sServerIP.TrimRight();
	
	((CEdit*)GetDlgItem(IDC_EDIT17))->GetWindowText(m_sServerPort);
	m_sServerPort.TrimLeft();
	m_sServerPort.TrimRight();

	sscanf(m_sServerPort, "%d",&nServerPort);	
	strtt.Format("%04X",nServerPort);
	m_sServerIPEnd=TransIPfromCStringtoBYTE(m_sServerIP);
	GenerateQRBMP(m_sOperateComm+m_sServerIPEnd+strtt);

	theApp.RecordServerIPStr	= m_sServerIP;
	theApp.RecordServerPortStr  = m_sServerPort;
	theApp.ReadorWriteIniFile(FALSE);	

}

//保存二维码到图片
void CQR_SettingDlg::OnButton5() 
{
	// CFileDialog 僋儔僗峔抸
	CString NameDptStr,Filepath,m_strSavePath;

	m_strSavePath = theApp.ExeFilePath+"\\QRCode.BMP";

	CFileDialog* pFileDialog = new CFileDialog(FALSE, "bmp", m_strSavePath, OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST,
											   "picture (*.bmp)|*.bmp| (*.*)|*.*||", this);

	pFileDialog->m_ofn.lpstrTitle = "save QR Picture";

	CString strFileName;

	if (pFileDialog->DoModal() == IDOK)
		strFileName = pFileDialog->GetPathName();

	delete 	pFileDialog;

	if (strFileName.IsEmpty())
		return;
	m_strSavePath=strFileName;

	if(SaveQRtoPic(strFileName,6))
	{
		AfxMessageBox("保存成功");
		return ;
	}

	
}
//
void CQR_SettingDlg::OnCheck1() 
{

	
}
//生成设备秘钥
void CQR_SettingDlg::OnButton13() 
{
	//将随机数据进行保存
	CString strtt,m_sOperateComm;
	m_sOperateComm="114410FF";
	GenerateQRBMP(m_sOperateComm+theApp.DeviceKeyStr2,TRUE);	
	
}

//更改设备秘钥
void CQR_SettingDlg::OnButton12() 
{

	int seed=0;
	int m_itemp=0;
	CString strtt,m_sOperateComm;

	if(IDOK!=AfxMessageBox("设备秘钥是设备识别二维码的重要数据，要重新设置吗？\n\n修改后，需要将设备秘钥设置到设备上，否则将不能解码\n\n默认设备密钥是0x00123456,请参见或修改配置文件的值",MB_OKCANCEL|MB_DEFBUTTON2))
		return;
	//产生一个不大于0x0FFFFFFF的随机整数
	seed = (::GetTickCount()) % 0x0FFFFFFF;
	strtt.Format("%08X",seed);
	((CEdit*)GetDlgItem(IDC_EDIT3))->SetWindowText(strtt);

	//将随机数据进行保存
	theApp.DeviceKeyStr2 = strtt;
	theApp.ReadorWriteIniFile(FALSE);

	m_sOperateComm="114410FF";
	GenerateQRBMP(m_sOperateComm+strtt);	
	
}

void CQR_SettingDlg::OnButton16() 
{
	CString strtt,m_sOperateComm;
	m_sOperateComm="114415FF";

	int	  nServerPort;

	CString m_sServerIP,m_sServerPort,m_sServerIPEnd;
	
	((CEdit*)GetDlgItem(IDC_EDIT12))->GetWindowText(m_sServerIP);
	m_sServerIP.TrimLeft();
	m_sServerIP.TrimRight();
	
	((CEdit*)GetDlgItem(IDC_EDIT13))->GetWindowText(m_sServerPort);
	m_sServerPort.TrimLeft();
	m_sServerPort.TrimRight();

	sscanf(m_sServerPort, "%d",&nServerPort);	
	strtt.Format("%04X",nServerPort);
	m_sServerIPEnd=TransIPfromCStringtoBYTE(m_sServerIP);
	GenerateQRBMP(m_sOperateComm+m_sServerIPEnd+strtt);

	theApp.TCPServerIPStr	= m_sServerIP;
	theApp.TCPServerPortStr = m_sServerPort;
	theApp.ReadorWriteIniFile(FALSE);	

}

void CQR_SettingDlg::OnRadio1() 
{
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(0);
	theApp.QR_TimeLimit="0";

}

void CQR_SettingDlg::OnRadio2() 
{
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(1);
	theApp.QR_TimeLimit="1";	
}

void CQR_SettingDlg::OnAradio3() 
{
	((CButton*)GetDlgItem(IDC_ARADIO3))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_ARADIO4))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_ARADIO5))->SetCheck(0);

	for(int kk=0;kk<3;kk++)
	{
		((CEdit*)GetDlgItem(IDC_EDIT23+kk))->EnableWindow(FALSE);
	}
	for( kk=0;kk<9;kk++)
	{
		((CEdit*)GetDlgItem(IDC_EDIT12+kk))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK22+kk))->EnableWindow(FALSE);
		
	}
	for( kk=0;kk<9;kk++)
	{
		((CEdit*)GetDlgItem(IDC_EDIT26+kk))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK31+kk))->EnableWindow(FALSE);
	}

	theApp.QR_OpenType="0";
	
}

void CQR_SettingDlg::OnAradio4() 
{
	((CButton*)GetDlgItem(IDC_ARADIO3))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_ARADIO4))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_ARADIO5))->SetCheck(0);

	((CEdit*)GetDlgItem(IDC_EDIT23))->EnableWindow(TRUE);
	for(int kk=0;kk<9;kk++)
	{
		((CEdit*)GetDlgItem(IDC_EDIT12+kk))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_CHECK22+kk))->EnableWindow(TRUE);
		
	}
	for( kk=0;kk<9;kk++)
	{
		((CEdit*)GetDlgItem(IDC_EDIT26+kk))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK31+kk))->EnableWindow(FALSE);
	}

	theApp.QR_OpenType="1";	
}

void CQR_SettingDlg::OnAradio5() 
{
	((CButton*)GetDlgItem(IDC_ARADIO3))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_ARADIO4))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_ARADIO5))->SetCheck(1);


	((CEdit*)GetDlgItem(IDC_EDIT23))->EnableWindow(FALSE);
	for(int kk=0;kk<9;kk++)
	{
		((CEdit*)GetDlgItem(IDC_EDIT12+kk))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK22+kk))->EnableWindow(FALSE);
		
	}
	for( kk=0;kk<9;kk++)
	{
		((CEdit*)GetDlgItem(IDC_EDIT26+kk))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_CHECK31+kk))->EnableWindow(TRUE);
	}

	theApp.QR_OpenType="2";		
}
//保存参数
void CQR_SettingDlg::OnButton17() 
{
	CString StrTmp;
	int nTmp=0;
	
	((CEdit*)GetDlgItem(IDC_EDIT22))->GetWindowText(StrTmp);
	if(StrTmp.GetLength()>8)
	{
		AfxMessageBox("关联卡号不对");
		((CEdit*)GetDlgItem(IDC_EDIT10))->SetWindowText(theApp.QR_IDStr);
		return;
	}
	theApp.QR_IDStr.Format("%08d",atoi(StrTmp));

	((CEdit*)GetDlgItem(IDC_EDIT9))->GetWindowText(StrTmp);
	if(atoi(StrTmp)>255)
	{
		AfxMessageBox("开门次数不对");
		((CEdit*)GetDlgItem(IDC_EDIT9))->SetWindowText(theApp.QR_Count);
		return;
	}
	theApp.QR_Count.Format("%d",atoi(StrTmp));

	((CEdit*)GetDlgItem(IDC_EDIT10))->GetWindowText(StrTmp);
	if(atoi(StrTmp)>65535)
	{
		((CEdit*)GetDlgItem(IDC_EDIT10))->SetWindowText(theApp.QR_OpenDelay);
		return;
	}
	theApp.QR_OpenDelay.Format("%d",atoi(StrTmp));

	if(((CButton*)GetDlgItem(IDC_CHECK_NOKEY))->GetCheck())
	{
		theApp.QR_StringNoEncrypt="1";
	}
	else
	{
		theApp.QR_StringNoEncrypt="0";
	}

	theApp.ReadorWriteIniFile(FALSE);
	
}
//生成开门二维码
void CQR_SettingDlg::OnButton15() 
{

	
	CString StrTmp,QRTmp[6],StrTmp2[10];
	//1用户数据 nB
	((CEdit*)GetDlgItem(IDC_EDIT1))->GetWindowText(QRTmp[0]);
	QRTmp[0].TrimLeft();
	QRTmp[0].TrimRight();

	//2二维码关联的卡号 4B
	((CEdit*)GetDlgItem(IDC_EDIT22))->GetWindowText(StrTmp);
	StrTmp.TrimLeft();
	StrTmp.TrimRight();	

	QRTmp[1].Format("%08X",atoi(StrTmp));
	if(QRTmp[1].GetLength()!=8)
	{
		AfxMessageBox(StrTmp+"卡号输入有误"+QRTmp[0]);
		return;
	}
	BOOL m_bNoEncrypt;
	m_bNoEncrypt = ((CButton*)GetDlgItem(IDC_CHECK_NOKEY))->GetCheck();//是否启用明码

	
	//4.管理字节4字节  8B
	//时段限制1B
	if(theApp.QR_TimeLimit=="0")
	{
		StrTmp2[0] = "00";
	}else{
		StrTmp2[0] = "01";
	}
	//次数限制1B
	int nQR_Count=0;
	((CEdit*)GetDlgItem(IDC_EDIT9))->GetWindowText(StrTmp);
	StrTmp.TrimLeft();
	StrTmp.TrimRight();	
	nQR_Count = atoi(StrTmp);
	if((nQR_Count<0)||(nQR_Count>255))
	{
		AfxMessageBox(StrTmp+"次数不对，次数值范围0-255");
		return;
	}
	StrTmp2[1].Format("%02X",nQR_Count);

	//开门方式1B
	if(theApp.QR_OpenType=="0")
	{
		StrTmp2[2] = "00";
	}else if(theApp.QR_OpenType=="1"){
		StrTmp2[2] = "01";
	}else if(theApp.QR_OpenType=="2"){
		StrTmp2[2] = "02";
	}
	//开门时长 2B
	int nQR_Delay=0;
	((CEdit*)GetDlgItem(IDC_EDIT10))->GetWindowText(StrTmp);
	StrTmp.TrimLeft();
	StrTmp.TrimRight();	
	nQR_Delay = atoi(StrTmp);
	if((nQR_Delay<0)||(nQR_Count>65535))
	{
		AfxMessageBox(StrTmp+"开门时长不对(0-65535");
		return;
	}
	StrTmp2[3].Format("%04X",nQR_Delay);
	//保留字节3B
	StrTmp2[4]=_T("000000");
	QRTmp[3] =StrTmp2[0]+StrTmp2[1]+StrTmp2[2]+StrTmp2[3]+StrTmp2[4];//8B

	//5、开始日期和结束日期
	CTime Starttime,Endtime,Starttime1,Endtime1;
	m_cStartDate.GetTime(Starttime);
	m_cStartTime.GetTime(Starttime1);
	m_cEndDate.GetTime(Endtime);
	m_cEndTime.GetTime(Endtime1);
	CString startdatestr,enddatestr;
	startdatestr.Format("%d%02d%02d%02d%02d%02d",Starttime.GetYear(),Starttime.GetMonth(),Starttime.GetDay(),Starttime1.GetHour(),Starttime1.GetMinute(),Starttime1.GetSecond());
	enddatestr.Format(  "%d%02d%02d%02d%02d%02d",Endtime.GetYear(),Endtime.GetMonth(),Endtime.GetDay(),Endtime1.GetHour(),Endtime1.GetMinute(),Endtime1.GetSecond());
	startdatestr=startdatestr.Right(startdatestr.GetLength()-2);//去年年的20 如2016==》16
	enddatestr  =enddatestr.Right(enddatestr.GetLength()-2);//去年年的20 如2016==》16
	QRTmp[4] = startdatestr+enddatestr;

	//6.项目编号和楼栋编号或可开设备的MAC低四位地址

	if(theApp.QR_OpenType=="1")//项目编号+房间编号组合
	{
		//楼栋数据
		((CEdit*)GetDlgItem(IDC_EDIT24))->GetWindowText(StrTmp);
		StrTmp2[0].Format("%02X",atoi(StrTmp));
		//项目编号
		((CEdit*)GetDlgItem(IDC_EDIT23))->GetWindowText(StrTmp);
		StrTmp.TrimLeft();
		StrTmp.TrimRight();	
		if(StrTmp.GetLength()!=8)
		{
			AfxMessageBox(StrTmp+"项目编号不对，长度8位(如：41590501)");
			return;
		}
		StrTmp2[1]=StrTmp;

		//房间组合
		StrTmp2[2]=_T("");
		for(int kk=0;kk<9;kk++)
		{
			if(((CButton*)GetDlgItem(IDC_CHECK22+kk))->GetCheck())
			{
				((CEdit*)GetDlgItem(IDC_EDIT12+kk))->GetWindowText(StrTmp);
				StrTmp.TrimLeft();
				StrTmp.TrimRight();	
				if(StrTmp.GetLength()!=8)
				{
					AfxMessageBox(StrTmp+"楼栋房间编号不对，长度8位(如：03010201 3栋1单元2层1室)");
					return;
				}
				StrTmp2[2]+=StrTmp;
			}						
		}
		QRTmp[5] = StrTmp2[0]+StrTmp2[1]+StrTmp2[2];
	
	}
	else if(theApp.QR_OpenType=="2")//MAC地址组合
	{
		//楼栋数据
		((CEdit*)GetDlgItem(IDC_EDIT25))->GetWindowText(StrTmp);
		StrTmp2[0].Format("%02X",atoi(StrTmp));

		//房间组合
		StrTmp2[1]=_T("");
		for(int kk=0;kk<9;kk++)
		{
			if(((CButton*)GetDlgItem(IDC_CHECK31+kk))->GetCheck())
			{
				((CEdit*)GetDlgItem(IDC_EDIT26+kk))->GetWindowText(StrTmp);
				StrTmp.TrimLeft();
				StrTmp.TrimRight();	
				if(StrTmp.GetLength()!=6)
				{
					AfxMessageBox(StrTmp+"MAC地址不对，取设备MAC地址后6位(如：MAC:008139921016==>921016)");
					return;
				}
				StrTmp2[1]+=StrTmp;
			}						
		}
		QRTmp[5] = StrTmp2[0]+StrTmp2[1];	
	}
	//3.加密参数 6B
	//计算加密字符长度
	CString encryptionQRStr;//需要加密的字符串
	encryptionQRStr = QRTmp[3]+QRTmp[4]+QRTmp[5];
	if(encryptionQRStr.GetLength()>500)
	{
		AfxMessageBox("加密字符长度过长");
		return;
	}
	if(m_bNoEncrypt)
	{
		int nLength=encryptionQRStr.GetLength();
		StrTmp2[0].Format("%04X",nLength);
		StrTmp2[2]="00000000";
		QRTmp[2]=StrTmp2[0]+StrTmp2[2];
	}
	else
	{
		//加密字符长度,8个字符长度为1个整形长度
		int nLength=encryptionQRStr.GetLength()/8;
		if((encryptionQRStr.GetLength()%8)!=0)
			nLength++;
		StrTmp2[0].Format("%02X",nLength);
		//余数
		StrTmp2[1].Format("%02X",(encryptionQRStr.GetLength()%8)/2);
		//二维码加密秘钥
		StrTmp2[2]=theApp.DeviceKeyStr;
		
		QRTmp[2]=StrTmp2[0]+StrTmp2[1]+StrTmp2[2];
	}

	CString AllQRStr;//所有二维码字符串

	AllQRStr = QRTmp[0] +"|" + QRTmp[1] + QRTmp[2] + encryptionQRStr;

	QRPreStr = QRTmp[0] +"|" + QRTmp[1] ;


	((CEdit*)GetDlgItem(IDC_EDIT2))->SetWindowText(AllQRStr);
	((CEdit*)GetDlgItem(IDC_EDIT6))->SetWindowText(encryptionQRStr);
	((CEdit*)GetDlgItem(IDC_EDIT8))->SetWindowText(AllQRStr);

	
	if(m_bNoEncrypt)
	{
		CString FileNameStr;
		((CEdit*)GetDlgItem(IDC_EDIT7))->SetWindowText("");
		//生成二维码，存成文件，并显示出来
		if(ProductImage(AllQRStr))
		{
			FileNameStr=theApp.ExeFilePath+"\\QRTmpApp.BMP";
			SaveQRtoPic(FileNameStr);
		}
		else
		{
	#ifdef ENGLISHC
			AfxMessageBox("Generate QR code Fail");
	#else
			AfxMessageBox("生成二维码失败");
	#endif
			return ;
		}
		ShowQRPic(FileNameStr);	
	}
	else
	{
		GenerateQRBMP(encryptionQRStr);
	}
	
	//关联卡号+1
	((CEdit*)GetDlgItem(IDC_EDIT22))->GetWindowText(StrTmp);
	theApp.QR_IDStr.Format("%08d",atoi(StrTmp)+1);
	((CEdit*)GetDlgItem(IDC_EDIT22))->SetWindowText(theApp.QR_IDStr);

	







	
}

void CQR_SettingDlg::totalAllCheck(int nType)
{
	int nTotal=0,nTotal2=0;
	for(int kk=0;kk<9;kk++)
	{
		if(((CButton*)GetDlgItem(IDC_CHECK22+kk))->GetCheck())
			nTotal++;
	}
	for( kk=0;kk<9;kk++)
	{
		if(((CButton*)GetDlgItem(IDC_CHECK31+kk))->GetCheck())
			nTotal2++;
	}
	CString	StrTmp;
	StrTmp.Format("%d",nTotal);
	((CEdit*)GetDlgItem(IDC_EDIT24))->SetWindowText(StrTmp);
	StrTmp.Format("%d",nTotal2);
	((CEdit*)GetDlgItem(IDC_EDIT25))->SetWindowText(StrTmp);	


}
CString CQR_SettingDlg::GenerateQRBMPQR(CString QRString)
{

	return "Aa";
}

void CQR_SettingDlg::OnCheck22() 
{
	totalAllCheck(0);
	
}
void CQR_SettingDlg::OnCheck23() 
{
	totalAllCheck(0);
}

void CQR_SettingDlg::OnCheck24() 
{
	totalAllCheck(0);
	
}

void CQR_SettingDlg::OnCheck25() 
{
totalAllCheck(0);	
}

void CQR_SettingDlg::OnCheck26() 
{
totalAllCheck(0);	
}

void CQR_SettingDlg::OnCheck27() 
{
totalAllCheck(0);	
}

void CQR_SettingDlg::OnCheck28() 
{
totalAllCheck(0);	
}

void CQR_SettingDlg::OnCheck29() 
{
totalAllCheck(0);	
}

void CQR_SettingDlg::OnCheck30() 
{
totalAllCheck(0);	
}

void CQR_SettingDlg::OnCheck31() 
{
totalAllCheck(0);	
}

void CQR_SettingDlg::OnCheck32() 
{
totalAllCheck(0);	
}

void CQR_SettingDlg::OnCheck33() 
{
totalAllCheck(0);	
}

void CQR_SettingDlg::OnCheck34() 
{
totalAllCheck(0);	
}

void CQR_SettingDlg::OnCheck35() 
{
totalAllCheck(0);	
}

void CQR_SettingDlg::OnCheck36() 
{
totalAllCheck(0);	
}

void CQR_SettingDlg::OnCheck37() 
{
totalAllCheck(0);	
}

void CQR_SettingDlg::OnCheck38() 
{
totalAllCheck(0);	
}

void CQR_SettingDlg::OnCheck39() 
{
totalAllCheck(0);	
}

void CQR_SettingDlg::OnCheckNokey() 
{
	if(((CButton*)GetDlgItem(IDC_CHECK_NOKEY))->GetCheck())
	{
	    ((CEdit*)GetDlgItem(IDC_EDIT4))->SetWindowText("00000000");	
	}
	else
	{
		((CEdit*)GetDlgItem(IDC_EDIT4))->SetWindowText(theApp.DeviceKeyStr);
	}
}
