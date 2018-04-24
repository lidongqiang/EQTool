
// EQToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EQTool.h"
#include "EQToolDlg.h"
#include "cmfuns.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CEQToolDlg 对话框

UINT ThreadScanDevice(LPVOID lpParam)
{
	CEQToolDlg* pMainDlg = (CEQToolDlg*)lpParam;
	pMainDlg->ScanDeviceProc();
	return 0;
}


CEQToolDlg::CEQToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEQToolDlg::IDD, pParent),m_DlgEq(m_Configs,m_LocalLan),m_DlgDrc(m_Configs,m_LocalLan),m_DlgEq1(m_Configs,m_LocalLan),m_DlgLimit(m_Configs,m_LocalLan)
	, m_edtGain(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEQToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_INFO, m_tabInfo);
	DDX_Control(pDX, IDC_COMBO_CHANUM, m_ComChannel);
	DDX_Control(pDX, IDC_LABEL_DEVICE, m_lblDevice);
	DDX_Text(pDX, IDC_EDIT_GAIN1, m_edtGain);
	DDV_MinMaxInt(pDX, m_edtGain, -12, 12);
	DDX_Control(pDX, IDC_COMBO_EQMODE, m_ComEqMode);
	DDX_Control(pDX, IDC_COMBO_DRCMODE, m_ComDrcMode);
	DDX_Control(pDX, IDC_COMBO_EQMODE2, m_ComEqMode1);
	DDX_Control(pDX, IDC_COMBO_LIMITMODE, m_ComLimitMode);
}

BEGIN_MESSAGE_MAP(CEQToolDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CEQToolDlg::OnBnClickedButton1)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_INFO, &CEQToolDlg::OnTcnSelchangeTabInfo)
	ON_BN_CLICKED(IDC_BUTTON_LEQ, &CEQToolDlg::OnBnClickedButtonLeq)
	ON_BN_CLICKED(IDC_BUTTON_LDRC, &CEQToolDlg::OnBnClickedButtonLdrc)
	ON_BN_CLICKED(IDC_BUTTON_REQ, &CEQToolDlg::OnBnClickedButtonReq)
	ON_BN_CLICKED(IDC_BUTTONRDRC, &CEQToolDlg::OnBnClickedButtonrdrc)
	ON_COMMAND(ID_COMPORT_SETTING, &CEQToolDlg::OnComportSetting)
	ON_COMMAND(ID_FILE_SAVEAS, &CEQToolDlg::OnFileSaveas)
	ON_COMMAND(ID_FILE_LOAD, &CEQToolDlg::OnFileLoad)
	ON_BN_CLICKED(IDC_CHECK_LINK, &CEQToolDlg::OnBnClickedCheckLink)
	ON_EN_KILLFOCUS(IDC_EDIT_GAIN1, &CEQToolDlg::OnEnKillfocusEditGain)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANUM, &CEQToolDlg::OnCbnSelchangeComboChanum)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CEQToolDlg::OnBnClickedButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_READ, &CEQToolDlg::OnBnClickedButtonRead)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CEQToolDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CEQToolDlg::OnBnClickedButtonCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_EQMODE, &CEQToolDlg::OnCbnSelchangeComboEqmode)
	ON_CBN_SELCHANGE(IDC_COMBO_DRCMODE, &CEQToolDlg::OnCbnSelchangeComboDrcmode)
	ON_CBN_SELCHANGE(IDC_COMBO_EQMODE2, &CEQToolDlg::OnCbnSelchangeComboEqmode2)
	ON_CBN_SELCHANGE(IDC_COMBO_LIMITMODE, &CEQToolDlg::OnCbnSelchangeComboLimitmode)
	ON_EN_KILLFOCUS(IDC_EDIT_GAIN2, &CEQToolDlg::OnEnKillfocusEditGain2)
END_MESSAGE_MAP()


// CEQToolDlg 消息处理程序

BOOL CEQToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//ShowWindow(SW_MAXIMIZE);

	// TODO: 在此添加额外的初始化代码
	std::wstring  strTitle = TEXT(APP_VERSION);
	this->SetWindowText(strTitle.c_str());

	m_pScanEvent        = NULL;
	m_pScanThread       = NULL;
	m_bUpgradeDllInitOK = FALSE;
	m_bTerminated = FALSE;

	m_strModulePath     = cmPath::GetModulePath();
	LoadConfig();

	INIT_DEV_INFO InitDevInfo;
	INIT_LOG_INFO InitLogInfo;
	INIT_CALLBACK_INFO InitCallbackInfo;
	if (m_Configs.strLogPath.empty())
	{
		m_Configs.strLogPath=m_strModulePath + _T("Log\\");
		m_strLogPath = m_Configs.strLogPath.c_str();
	}
	else
	{
		m_strLogPath = m_Configs.strLogPath.c_str();
	}
	if ( !cmFile::IsExisted(m_strLogPath) )
	{
		CreateDirectory(m_strLogPath,NULL);
	}

	//InitDevInfo.bScan4FsUsb = FALSE;
	//InitDevInfo.emSupportDevice = 0;
	//InitDevInfo.uiRockMscTimeout = 30;
	//InitDevInfo.uiRockusbTimeout = 30;
	//InitDevInfo.usRockMscPid = 0;
	//InitDevInfo.usRockMscVid = 0;
	//InitDevInfo.usRockusbPid = 0;
	//InitDevInfo.usRockusbVid = 0;

	//InitLogInfo.bLogEnable = TRUE;
	//InitLogInfo.lpszLogPathName = (LPTSTR)(LPCTSTR)m_strLogPath;

	//InitCallbackInfo.pProgressPromptProc = NULL;//you can set it to ProgressPromptProc for showing upgrade info;
	//InitCallbackInfo.pUpgradeStepPromptProc = NULL;//you can set it to UpgradeStepPromptProc for showing progress info;
	//m_bUpgradeDllInitOK = RK_Initialize(InitDevInfo, InitLogInfo, InitCallbackInfo);
	//if (!m_bUpgradeDllInitOK)
	//{
	//	MessageBox(_T("Initialize RKUpgrade dll failed!"),_T("ERROR"),MB_ICONERROR|MB_OK);
	//}
	//else
	//{
	//	m_pScanThread = AfxBeginThread(ThreadScanDevice,(LPVOID)this);
	//}

	InitUi();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CEQToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CEQToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CEQToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CEQToolDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
}

void CEQToolDlg::OnSizeCtl( int cx, int cy)
{
	int i;
	if (::IsWindow(m_tabInfo.GetSafeHwnd())) {
		m_tabInfo.MoveWindow(10,10,cx - 20 ,cy - 60,TRUE);
		for( i = 0; i < sizeof(pDialog)/sizeof(pDialog[0]); i++ ) {
			if(pDialog[i]) pDialog[i]->MoveWindow(0,20,cx - 20,cy - 80 ,TRUE);
		}
	}
}
void CEQToolDlg::OnTcnSelchangeTabInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	int     iNewSel = m_tabInfo.GetCurSel();
	if(pDialog[iNewSel]) {
		pDialog[m_iCurSelTab]->ShowWindow(SW_HIDE);
		m_iCurSelTab = iNewSel;
		pDialog[m_iCurSelTab]->ShowWindow(SW_SHOW);
	}else {
		//m_tabconfsw.SetCurSel(m_iCurSelTab);
	}
}

void CEQToolDlg::InitUi()
{
	m_ComChannel.AddString(_T("channel0"));
	m_ComChannel.AddString(_T("channel1"));
	m_ComChannel.SetCurSel(m_Configs.nChannel);
	m_ComEqMode.AddString(_T("OFF"));
	m_ComEqMode.AddString(_T("ON"));
	m_ComEqMode.SetCurSel(m_Configs.bEQSwtch);
	m_ComEqMode1.AddString(_T("OFF"));
	m_ComEqMode1.AddString(_T("ON"));
	m_ComEqMode1.SetCurSel(m_Configs.bEQSwtch1);
	m_ComLimitMode.AddString(_T("OFF"));
	m_ComLimitMode.AddString(_T("ON"));
	m_ComLimitMode.SetCurSel(m_Configs.bLimitSwtch);
	m_ComDrcMode.AddString(_T("OFF"));
	m_ComDrcMode.AddString(_T("ON"));
	m_ComDrcMode.SetCurSel(m_Configs.bDrcSwtch);
	if (m_Configs.bLink)
	{
		((CButton*)GetDlgItem(IDC_CHECK_LINK))->SetCheck(BST_CHECKED);
		GetDlgItem(IDC_COMBO_CHANUM)->EnableWindow(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECK_LINK))->SetCheck(BST_UNCHECKED);
		GetDlgItem(IDC_COMBO_CHANUM)->EnableWindow(TRUE);
	}
	if (m_Configs.nChannel)
	{
		SetDlgItemText(IDC_EDIT_GAIN1,cmNumString::NumToStr(m_Configs.ScrGainR1,10));
		SetDlgItemText(IDC_EDIT_GAIN2,cmNumString::NumToStr(m_Configs.ScrGainR2,10));
	}
	else
	{
		SetDlgItemText(IDC_EDIT_GAIN1,cmNumString::NumToStr(m_Configs.ScrGainL1,10));
		SetDlgItemText(IDC_EDIT_GAIN2,cmNumString::NumToStr(m_Configs.ScrGainL2,10));
	}

	//为Tab Control增加两个页面  
	m_tabInfo.InsertItem(0, _T("EQ10"));  
	m_tabInfo.InsertItem(1, _T("DRC"));
	m_tabInfo.InsertItem(2, _T("EQ8"));
	m_tabInfo.InsertItem(3, _T("Limit"));

	//创建两个对话框  
	m_DlgEq.Create(IDD_DIALOG_EQ, &m_tabInfo);  
	m_DlgDrc.Create(IDD_DIALOG_DRC, &m_tabInfo);
	m_DlgEq1.Create(IDD_DIALOG_EQ1, &m_tabInfo);
	m_DlgLimit.Create(IDD_DIALOG_LIMIT, &m_tabInfo);
	//设定在Tab内显示的范围  
	CRect rc;  
	m_tabInfo.GetClientRect(rc);
	rc.top += 20;  

	m_DlgEq.MoveWindow(&rc);  
	m_DlgDrc.MoveWindow(&rc);
	m_DlgEq1.MoveWindow(&rc);
	m_DlgLimit.MoveWindow(&rc);

	//把对话框对象指针保存起来  
	pDialog[0] = &m_DlgEq;  
	pDialog[1] = &m_DlgDrc;  
	pDialog[2] = &m_DlgEq1;
	pDialog[3] = &m_DlgLimit;  

	m_iCurSelTab    = 0;
	pDialog[m_iCurSelTab]->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LABEL_DEVICE)->ShowWindow(FALSE);
}

void CEQToolDlg::OnBnClickedButtonLeq()
{
	// TODO: Add your control notification handler code here
	pDialog[m_iCurSelTab]->ShowWindow(SW_HIDE);
	m_iCurSelTab = 0;
	m_tabInfo.SetCurSel(m_iCurSelTab);
	pDialog[m_iCurSelTab]->ShowWindow(SW_SHOW);
	m_Configs.nChannel = 0;
	m_DlgEq.InitUi(0);
	m_DlgDrc.InitUi(0);
	m_ComChannel.SetCurSel(0);
}

void CEQToolDlg::OnBnClickedButtonLdrc()
{
	// TODO: Add your control notification handler code here
	pDialog[m_iCurSelTab]->ShowWindow(SW_HIDE);
	m_iCurSelTab = 1;
	m_tabInfo.SetCurSel(m_iCurSelTab);
	pDialog[m_iCurSelTab]->ShowWindow(SW_SHOW);
	m_Configs.nChannel = 0;
	m_DlgEq.InitUi(m_Configs.nChannel);
	m_DlgDrc.InitUi(m_Configs.nChannel);
	m_ComChannel.SetCurSel(m_Configs.nChannel);
}

void CEQToolDlg::OnBnClickedButtonReq()
{
	// TODO: Add your control notification handler code here
	pDialog[m_iCurSelTab]->ShowWindow(SW_HIDE);
	m_iCurSelTab = 0;
	m_tabInfo.SetCurSel(m_iCurSelTab);
	pDialog[m_iCurSelTab]->ShowWindow(SW_SHOW);
	m_Configs.nChannel = 1;
	m_DlgEq.InitUi(m_Configs.nChannel);
	m_DlgDrc.InitUi(m_Configs.nChannel);
	m_ComChannel.SetCurSel(m_Configs.nChannel);
}

void CEQToolDlg::OnBnClickedButtonrdrc()
{
	// TODO: Add your control notification handler code here
	pDialog[m_iCurSelTab]->ShowWindow(SW_HIDE);
	m_iCurSelTab = 1;
	m_tabInfo.SetCurSel(m_iCurSelTab);
	pDialog[m_iCurSelTab]->ShowWindow(SW_SHOW);
	m_Configs.nChannel = 1;
	m_DlgEq.InitUi(m_Configs.nChannel);
	m_DlgDrc.InitUi(m_Configs.nChannel);
	m_ComChannel.SetCurSel(m_Configs.nChannel);
}

BOOL CEQToolDlg::LoadConfig()
{
	CString strConfigPath;
	strConfigPath = m_strModulePath + _T("config.ini");
	if (!cmFile::IsExisted(strConfigPath))
	{
		return FALSE;
	}
	bool bLoadConfig = m_Configs.LoadToolSetting(strConfigPath.GetString());
	if (!bLoadConfig)
	{
		return FALSE;
	}
	strConfigPath = m_strModulePath + m_Configs.strLanPath.c_str();
	if (m_Configs.nCurLan == 1)
	{
		strConfigPath = strConfigPath + m_Configs.strCnFilename.c_str();
	}
	else
	{
		strConfigPath = strConfigPath + m_Configs.strEnFilename.c_str();
	}
	if (!cmFile::IsExisted(strConfigPath))
	{
		return FALSE;
	}
	bLoadConfig = m_LocalLan.LoadToolSetting(strConfigPath.GetString());
	m_LocalLan.TreeControls(m_hWnd,m_Configs.bDebug?TRUE:FALSE,this->IDD,true);
	if (!bLoadConfig)
	{
		return FALSE;
	}
	if(!m_Configs.bDebug) {
		WalkMenu(GetMenu(),TEXT("MENU"));
	}
	GetLocalString(TEXT("LANG:IDS_TEXT_APPNAME"));
	return TRUE;
}

std::wstring CEQToolDlg::GetLocalString(std::wstring strKey)
{
	return m_LocalLan.GetLanStr(strKey);
}

VOID CEQToolDlg::WalkMenu(CMenu *pMenu,CString strMainKeyPart)
{
	CString strKey;
	int     id ;
	UINT    i;
	if(NULL == pMenu) return ;
	for (i=0;i < pMenu->GetMenuItemCount();i++) {
		strKey.Format(_T("%s_%d"),strMainKeyPart,i);
		id = pMenu->GetMenuItemID(i);
		if (0 == id) { 
			/*If nPos corresponds to a SEPARATOR menu item, the return value is 0. **/
		} else if (-1 == id) { 
			/*If the specified item is a pop-up menu (as opposed to an item within the pop-up menu), the return value is –1 **/
			pMenu->ModifyMenu(i, MF_BYPOSITION, i, m_LocalLan.GetStr((LPCTSTR)strKey).c_str());
			WalkMenu(pMenu->GetSubMenu(i),strKey);
		} else {
			pMenu->ModifyMenu(id, MF_BYCOMMAND, id,m_LocalLan.GetStr((LPCTSTR)strKey).c_str());
		}
	}
}
void CEQToolDlg::OnComportSetting()
{
	// TODO: Add your command handler code here
	CComSet ComDlg(m_ctrlcomm);
	if (IDOK == ComDlg.DoModal())
	{
		
	}
}

void CEQToolDlg::OnFileSaveas()
{
	// TODO: Add your command handler code here
	CFile file;  
	CString filepath;  
	TCHAR szFilter[] = _T("文本文件(*.bin)|*.bin|所有文件(*.*)|*.*||");  
	CFileDialog fileDlg(FALSE, _T("bin"), _T("Para"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	HANDLE          hFile;
	BOOL            bWrite;
	DWORD           dwBytesWritten;

	if (IDOK == fileDlg.DoModal())  
	{  
		filepath = fileDlg.GetPathName();  
		//file.Open(filepath, CFile::modeCreate | CFile::modeWrite | CFile::typeText);  
		FILE *fpPara = fopen(m_Configs.wstr2str(filepath.GetString()).c_str(), "wb");
		storeParaData(fpPara);
		//fwrite(afPara, sizeof(float), PARANUM, fpPara);

		//fclose(fpPara);
		//file.Write(afPara,PARANUM);
		//file.Close();  
	}  
}
void CEQToolDlg::storeParaData(FILE *fpPara)
{
	int fMinFreq,swCurveLen;
	float  afCurve1[3000];
	float  afCurve2[3000];
	float afPara[PARANUM] = {0.0f};
	/* 1.1 左右声道公共参数 */
	afPara[PARA_CHANUM]    = m_Configs.shwChaNum;                      // 声道数
	afPara[PARA_EQ10SWTCH]  = m_Configs.bEQSwtch;                // EQ开关
	afPara[PARA_EQ8SWTCH]  = m_Configs.bEQSwtch1;
	afPara[PARA_DRCSWTCH]  = m_Configs.bDrcSwtch;                // DRC开关
	afPara[PARA_LIMITERSWTCH]  = m_Configs.bLimitSwtch;
	afPara[PARA_FS]        = m_Configs.swFs;                           // 采样率

	/* 1.2 左声道参数 */
	/* 1.2.1 左声道增益 */
	afPara[PARA_L_GAIN1] = m_Configs.ScrGainL1;
	/* 1.2.2 左声道10EQ参数 */
	//Gain
	afPara[PARA_LEQ10_GBASS]    = m_Configs.EqGainLeft[0];                           // 第一个滤波器（低通坡式）的通带增益                    
	afPara[PARA_LEQ10_GPEAK1]   = m_Configs.EqGainLeft[1];                           // 第二个滤波器（峰式）的峰值增益               
	afPara[PARA_LEQ10_GPEAK1+1] = m_Configs.EqGainLeft[2];                          // 第三个滤波器（峰式）的峰值增益                    
	afPara[PARA_LEQ10_GPEAK1+2] = m_Configs.EqGainLeft[3];                           // 第四个滤波器（峰式）的峰值增益                   
	afPara[PARA_LEQ10_GPEAK1+3] = m_Configs.EqGainLeft[4];                           // 第五个滤波器（峰式）的峰值增益                    
	afPara[PARA_LEQ10_GPEAK1+4] = m_Configs.EqGainLeft[5];                           // 第六个滤波器（峰式）的峰值增益                   
	afPara[PARA_LEQ10_GPEAK1+5] = m_Configs.EqGainLeft[6];                           // 第七个滤波器（峰式）的峰值增益                    
	afPara[PARA_LEQ10_GPEAK1+6] = m_Configs.EqGainLeft[7];                           // 第八个滤波器（峰式）的峰值增益
	afPara[PARA_LEQ10_GPEAK1+7] = m_Configs.EqGainLeft[8];                           // 第九个滤波器（峰式）的峰值增益
	afPara[PARA_LEQ10_GTREBLE]  = m_Configs.EqGainLeft[9];                         // 第十个滤波器（高通坡式）的通带增益
	//CF
	afPara[PARA_LEQ10_CFBASS]    = m_Configs.EqCFLeft[0];                         // 第一个滤波器（低通坡式）的截止频率                        
	afPara[PARA_LEQ10_CFPEAK1]   = m_Configs.EqCFLeft[1];                        // 第二个滤波器（峰式）的中心频率                     
	afPara[PARA_LEQ10_CFPEAK1+1] = m_Configs.EqCFLeft[2];                        // 第三个滤波器（峰式）的中心频率                     
	afPara[PARA_LEQ10_CFPEAK1+2] = m_Configs.EqCFLeft[3];                       // 第四个滤波器（峰式）的中心频率                      
	afPara[PARA_LEQ10_CFPEAK1+3] = m_Configs.EqCFLeft[4];                       // 第五个滤波器（峰式）的中心频率                       
	afPara[PARA_LEQ10_CFPEAK1+4] = m_Configs.EqCFLeft[5];                       // 第六个滤波器（峰式）的中心频率                      
	afPara[PARA_LEQ10_CFPEAK1+5] = m_Configs.EqCFLeft[6];                      // 第七个滤波器（峰式）的中心频率                        
	afPara[PARA_LEQ10_CFPEAK1+6] = m_Configs.EqCFLeft[7];                      // 第八个滤波器（峰式）的中心频率
	afPara[PARA_LEQ10_CFPEAK1+7] = m_Configs.EqCFLeft[8];                      // 第九个滤波器（峰式）的中心频率 
	afPara[PARA_LEQ10_CFTREBLE]  = m_Configs.EqCFLeft[9];                      // 第十个滤波器（高通坡式）的截止频率
	//Q
	afPara[PARA_LEQ10_Q1]   = m_Configs.EqQLeft[0];                             // 第二个滤波器（峰式）的Q值               
	afPara[PARA_LEQ10_Q1+1] = m_Configs.EqQLeft[1];                             // 第三个滤波器（峰式）的Q值                        
	afPara[PARA_LEQ10_Q1+2] = m_Configs.EqQLeft[2];                             // 第四个滤波器（峰式）的Q值                        
	afPara[PARA_LEQ10_Q1+3] = m_Configs.EqQLeft[3];                             // 第五个滤波器（峰式）的Q值  
	afPara[PARA_LEQ10_Q1+4] = m_Configs.EqQLeft[4];                             // 第六个滤波器（峰式）的Q值  
	afPara[PARA_LEQ10_Q1+5] = m_Configs.EqQLeft[5];                             // 第七个滤波器（峰式）的Q值  
	afPara[PARA_LEQ10_Q1+6] = m_Configs.EqQLeft[6];                             // 第八个滤波器（峰式）的Q值 
	afPara[PARA_LEQ10_Q1+7] = m_Configs.EqQLeft[7];                             // 第九个滤波器（峰式）的Q值 
	/* 1.2.3 左声道DRC参数 */ 
	afPara[PARA_LDRC_DIVFREQ] = m_Configs.DivFreq_L;                        // 计算RMS能量的统计时间，单位ms
	// 低频子带
	afPara[PARA_LDRC_B1_ECALTIME] = m_Configs.Ecaltime_LL;                     // 计算RMS能量的统计时间，单位ms
	afPara[PARA_LDRC_B1_MAKEUPG]   = m_Configs.Offset_LL;                       // 线性段提升dB数
	afPara[PARA_LDRC_B1_THREL]    = m_Configs.Threl_LL;                     // 低能段能量阈值，单位dB
	afPara[PARA_LDRC_B1_THREH]    = m_Configs.Threh_LL;                     // 高能段能量阈值，单位dB
	afPara[PARA_LDRC_B1_RATLNOM]  = m_Configs.Ratlnom_LL;                       // 低能段压缩比例的分子
	afPara[PARA_LDRC_B1_RATLDEN]  = m_Configs.Ratlden_LL;                       // 低能段压缩比例的分母
	afPara[PARA_LDRC_B1_RATHNOM]  = m_Configs.Rathnom_LL;                       // 高能段压缩比例的分子
	afPara[PARA_LDRC_B1_RATHDEN]  = m_Configs.Rathden_LL;                       // 高能段压缩比例的分母
	afPara[PARA_LDRC_B1_RLSTIME]  = m_Configs.Rlstime_LL;                      // release time，单位ms
	afPara[PARA_LDRC_B1_SMTHTIME] = m_Configs.Smthtime_LL;                      // 中间段时域平滑时间，单位ms
	afPara[PARA_LDRC_B1_ATTATIME] = m_Configs.Attatime_LL;                      // attack time，单位ms
	 //高频子带
	afPara[PARA_LDRC_B2_ECALTIME] = m_Configs.Ecaltime_LH;                     // 计算RMS能量的统计时间，单位ms
	afPara[PARA_LDRC_B2_MAKEUPG]   = m_Configs.Offset_LH;                       // 线性段提升dB数
	afPara[PARA_LDRC_B2_THREL]    = m_Configs.Threl_LH;                     // 低能段能量阈值，单位dB
	afPara[PARA_LDRC_B2_THREH]    = m_Configs.Threh_LH;                     // 高能段能量阈值，单位dB
	afPara[PARA_LDRC_B2_RATLNOM]  = m_Configs.Ratlnom_LH;                       // 低能段压缩比例的分子
	afPara[PARA_LDRC_B2_RATLDEN]  = m_Configs.Ratlden_LH;                       // 低能段压缩比例的分母
	afPara[PARA_LDRC_B2_RATHNOM]  = m_Configs.Rathnom_LH;                       // 高能段压缩比例的分子
	afPara[PARA_LDRC_B2_RATHDEN]  = m_Configs.Rathden_LH;                       // 高能段压缩比例的分母
	afPara[PARA_LDRC_B2_RLSTIME]  = m_Configs.Rlstime_LH;                      // release time，单位ms
	afPara[PARA_LDRC_B2_SMTHTIME] = m_Configs.Smthtime_LH;                      // 中间段时域平滑时间，单位ms
	afPara[PARA_LDRC_B2_ATTATIME] = m_Configs.Attatime_LH;                      // attack time，单位ms

	/* 1.2.2 左声道8EQ参数 */
	//Gain
	afPara[PARA_LEQ8_GBASS]    = m_Configs.EqGainLeft1[0];                           // 第一个滤波器（低通坡式）的通带增益                    
	afPara[PARA_LEQ8_GPEAK1]   = m_Configs.EqGainLeft1[1];                           // 第二个滤波器（峰式）的峰值增益               
	afPara[PARA_LEQ8_GPEAK1+1] = m_Configs.EqGainLeft1[2];                          // 第三个滤波器（峰式）的峰值增益                    
	afPara[PARA_LEQ8_GPEAK1+2] = m_Configs.EqGainLeft1[3];                           // 第四个滤波器（峰式）的峰值增益                   
	afPara[PARA_LEQ8_GPEAK1+3] = m_Configs.EqGainLeft1[4];                           // 第五个滤波器（峰式）的峰值增益                    
	afPara[PARA_LEQ8_GPEAK1+4] = m_Configs.EqGainLeft1[5];                           // 第六个滤波器（峰式）的峰值增益                   
	afPara[PARA_LEQ8_GPEAK1+5] = m_Configs.EqGainLeft1[6];                           // 第七个滤波器（峰式）的峰值增益                    
	afPara[PARA_LEQ8_GTREBLE]  = m_Configs.EqGainLeft1[7];                         // 第八个滤波器（高通坡式）的通带增益
	//CF
	afPara[PARA_LEQ8_CFBASS]    = m_Configs.EqCFLeft1[0];                         // 第一个滤波器（低通坡式）的截止频率                        
	afPara[PARA_LEQ8_CFPEAK1]   = m_Configs.EqCFLeft1[1];                        // 第二个滤波器（峰式）的中心频率                     
	afPara[PARA_LEQ8_CFPEAK1+1] = m_Configs.EqCFLeft1[2];                        // 第三个滤波器（峰式）的中心频率                     
	afPara[PARA_LEQ8_CFPEAK1+2] = m_Configs.EqCFLeft1[3];                       // 第四个滤波器（峰式）的中心频率                      
	afPara[PARA_LEQ8_CFPEAK1+3] = m_Configs.EqCFLeft1[4];                       // 第五个滤波器（峰式）的中心频率                       
	afPara[PARA_LEQ8_CFPEAK1+4] = m_Configs.EqCFLeft1[5];                       // 第六个滤波器（峰式）的中心频率                      
	afPara[PARA_LEQ8_CFPEAK1+5] = m_Configs.EqCFLeft1[6];                      // 第七个滤波器（峰式）的中心频率                        
	afPara[PARA_LEQ8_CFTREBLE]  = m_Configs.EqCFLeft1[7];                      // 第八个滤波器（高通坡式）的截止频率
	//Q
	afPara[PARA_LEQ8_Q1]   = m_Configs.EqQLeft1[0];                             // 第二个滤波器（峰式）的Q值               
	afPara[PARA_LEQ8_Q1+1] = m_Configs.EqQLeft1[1];                             // 第三个滤波器（峰式）的Q值                        
	afPara[PARA_LEQ8_Q1+2] = m_Configs.EqQLeft1[2];                             // 第四个滤波器（峰式）的Q值                        
	afPara[PARA_LEQ8_Q1+3] = m_Configs.EqQLeft1[3];                             // 第五个滤波器（峰式）的Q值  
	afPara[PARA_LEQ8_Q1+4] = m_Configs.EqQLeft1[4];                             // 第六个滤波器（峰式）的Q值  
	afPara[PARA_LEQ8_Q1+5] = m_Configs.EqQLeft1[5];                             // 第七个滤波器（峰式）的Q值
	/* 1.2.4 左声道Limiter参数 */ 
	afPara[PARA_LLMT_ECALTIME]   = m_Configs.fLimitEca_L;                        // Static time：计算RMS能量的统计时间，单位ms
	afPara[PARA_LLMT_THRESHOLD]  = m_Configs.fLimitThres_L;                       // Threshold：输入信号能量高于该阈值时，Limiter开始限制输出幅度，单位dB
	// -12dB < Threshold < 0dB
	afPara[PARA_LLMT_ATTACKTIME] = m_Configs.fLimitAtt_L;                      // attack time，单位ms
	afPara[PARA_LLMT_SMOOTHTIME] = m_Configs.fLimitSmo_L;                       // smooth time，单位ms

	afPara[PARA_L_GAIN2] = m_Configs.ScrGainL2;
	/* 1.3 右声道参数 */
	if (m_Configs.shwChaNum == 2)
	{
		/* 1.2.1 右声道增益 */
		afPara[PARA_R_GAIN1] = m_Configs.ScrGainR1;
		/* 1.2.2 右声道EQ参数 */
		//Gain
		afPara[PARA_REQ10_GBASS]    = m_Configs.EqGainRight[0];                     // 第一个滤波器（低通坡式）的通带增益             
		afPara[PARA_REQ10_GPEAK1]   = m_Configs.EqGainRight[1];                       // 第二个滤波器（峰式）的峰值增益                        
		afPara[PARA_REQ10_GPEAK1+1] = m_Configs.EqGainRight[2];                       // 第三个滤波器（峰式）的峰值增益                       
		afPara[PARA_REQ10_GPEAK1+2] = m_Configs.EqGainRight[3];                       // 第四个滤波器（峰式）的峰值增益                
		afPara[PARA_REQ10_GPEAK1+3] = m_Configs.EqGainRight[4];                       // 第五个滤波器（峰式）的峰值增益                
		afPara[PARA_REQ10_GPEAK1+4] = m_Configs.EqGainRight[5];                      // 第六个滤波器（峰式）的峰值增益               
		afPara[PARA_REQ10_GPEAK1+5] = m_Configs.EqGainRight[6];                       // 第七个滤波器（峰式）的峰值增益                
		afPara[PARA_REQ10_GPEAK1+6] = m_Configs.EqGainRight[7];                       // 第八个滤波器（峰式）的峰值增益
		afPara[PARA_REQ10_GPEAK1+7] = m_Configs.EqGainRight[8];                       // 第九个滤波器（峰式）的峰值增益
		afPara[PARA_REQ10_GTREBLE]  = m_Configs.EqGainRight[9];                       // 第十个滤波器（高通坡式）的通带增益
		//CF
		afPara[PARA_REQ10_CFBASS]    = m_Configs.EqCFRight[0];                     // 第一个滤波器（低通坡式）的截止频率                  
		afPara[PARA_REQ10_CFPEAK1]   = m_Configs.EqCFRight[1];                    // 第二个滤波器（峰式）的中心频率                  
		afPara[PARA_REQ10_CFPEAK1+1] = m_Configs.EqCFRight[2];                    // 第三个滤波器（峰式）的中心频率                  
		afPara[PARA_REQ10_CFPEAK1+2] = m_Configs.EqCFRight[3];                   // 第四个滤波器（峰式）的中心频率                   
		afPara[PARA_REQ10_CFPEAK1+3] = m_Configs.EqCFRight[4];                   // 第五个滤波器（峰式）的中心频率                    
		afPara[PARA_REQ10_CFPEAK1+4] = m_Configs.EqCFRight[5];                   // 第六个滤波器（峰式）的中心频率                    
		afPara[PARA_REQ10_CFPEAK1+5] = m_Configs.EqCFRight[6];                  // 第七个滤波器（峰式）的中心频率                      
		afPara[PARA_REQ10_CFPEAK1+6] = m_Configs.EqCFRight[7];                  // 第八个滤波器（峰式）的中心频率 
		afPara[PARA_REQ10_CFPEAK1+7] = m_Configs.EqCFRight[8];                  // 第九个滤波器（峰式）的中心频率
		afPara[PARA_REQ10_CFTREBLE]  = m_Configs.EqCFRight[9];                  // 第十个滤波器（高通坡式）的截止频率
		//Q
		afPara[PARA_REQ10_Q1]   = m_Configs.EqQRight[0];                         // 第二个滤波器（峰式）的Q值              
		afPara[PARA_REQ10_Q1+1] = m_Configs.EqQRight[1];                         // 第三个滤波器（峰式）的Q值             
		afPara[PARA_REQ10_Q1+2] = m_Configs.EqQRight[2];                         // 第四个滤波器（峰式）的Q值             
		afPara[PARA_REQ10_Q1+3] = m_Configs.EqQRight[3];                         // 第五个滤波器（峰式）的Q值
		afPara[PARA_REQ10_Q1+4] = m_Configs.EqQRight[4];                         // 第六个滤波器（峰式）的Q值
		afPara[PARA_REQ10_Q1+5] = m_Configs.EqQRight[5];                         // 第七个滤波器（峰式）的Q值 
		afPara[PARA_REQ10_Q1+6] = m_Configs.EqQRight[6];                         // 第八个滤波器（峰式）的Q值
		afPara[PARA_REQ10_Q1+7] = m_Configs.EqQRight[7];                         // 第九个滤波器（峰式）的Q值
		/* 1.2.3 右声道DRC参数 */ 
		afPara[PARA_RDRC_DIVFREQ] = m_Configs.DivFreq_R;                    // 计算RMS能量的统计时间，单位ms
		// 低频子带
		afPara[PARA_RDRC_B1_ECALTIME] = m_Configs.Ecaltime_RL;                 // 计算RMS能量的统计时间，单位ms
		afPara[PARA_RDRC_B1_MAKEUPG]   = m_Configs.Offset_RL;                   // 线性段提升dB数
		afPara[PARA_RDRC_B1_THREL]    = m_Configs.Threl_RL;                 // 低能段能量阈值，单位dB
		afPara[PARA_RDRC_B1_THREH]    = m_Configs.Threh_RL;                 // 高能段能量阈值，单位dB
		afPara[PARA_RDRC_B1_RATLNOM]  = m_Configs.Ratlnom_RL;                   // 低能段压缩比例的分子
		afPara[PARA_RDRC_B1_RATLDEN]  = m_Configs.Ratlden_RL;                   // 低能段压缩比例的分母
		afPara[PARA_RDRC_B1_RATHNOM]  = m_Configs.Rathnom_RL;                   // 高能段压缩比例的分子
		afPara[PARA_RDRC_B1_RATHDEN]  = m_Configs.Rathden_RL;                   // 高能段压缩比例的分母
		afPara[PARA_RDRC_B1_RLSTIME]  = m_Configs.Rlstime_RL;                  // release time，单位ms
		afPara[PARA_RDRC_B1_SMTHTIME] = m_Configs.Smthtime_RL;                  // 中间段时域平滑时间，单位ms
		afPara[PARA_RDRC_B1_ATTATIME] = m_Configs.Attatime_RL;                  // attack time，单位ms
		 //高频子带
		afPara[PARA_RDRC_B2_ECALTIME] = m_Configs.Ecaltime_RH;                 // 计算RMS能量的统计时间，单位ms
		afPara[PARA_RDRC_B2_MAKEUPG]   = m_Configs.Offset_RH;                   // 线性段提升dB数
		afPara[PARA_RDRC_B2_THREL]    = m_Configs.Threl_RH;                 // 低能段能量阈值，单位dB
		afPara[PARA_RDRC_B2_THREH]    = m_Configs.Threh_RH;                 // 高能段能量阈值，单位dB
		afPara[PARA_RDRC_B2_RATLNOM]  = m_Configs.Ratlnom_RH;                   // 低能段压缩比例的分子
		afPara[PARA_RDRC_B2_RATLDEN]  = m_Configs.Ratlden_RH;                   // 低能段压缩比例的分母
		afPara[PARA_RDRC_B2_RATHNOM]  = m_Configs.Rathnom_RH;                   // 高能段压缩比例的分子
		afPara[PARA_RDRC_B2_RATHDEN]  = m_Configs.Rathden_RH;                   // 高能段压缩比例的分母
		afPara[PARA_RDRC_B2_RLSTIME]  = m_Configs.Rlstime_RH;                  // release time，单位ms
		afPara[PARA_RDRC_B2_SMTHTIME] = m_Configs.Smthtime_RH;                  // 中间段时域平滑时间，单位ms
		afPara[PARA_RDRC_B2_ATTATIME] = m_Configs.Attatime_RH;                  // attack time，单位ms
		/* 1.2.4 右声道8EQ参数 */
		//Gain
		afPara[PARA_REQ8_GBASS]    = m_Configs.EqGainRight1[0];                     // 第一个滤波器（低通坡式）的通带增益             
		afPara[PARA_REQ8_GPEAK1]   = m_Configs.EqGainRight1[1];                       // 第二个滤波器（峰式）的峰值增益                        
		afPara[PARA_REQ8_GPEAK1+1] = m_Configs.EqGainRight1[2];                       // 第三个滤波器（峰式）的峰值增益                       
		afPara[PARA_REQ8_GPEAK1+2] = m_Configs.EqGainRight1[3];                       // 第四个滤波器（峰式）的峰值增益                
		afPara[PARA_REQ8_GPEAK1+3] = m_Configs.EqGainRight1[4];                       // 第五个滤波器（峰式）的峰值增益                
		afPara[PARA_REQ8_GPEAK1+4] = m_Configs.EqGainRight1[5];                      // 第六个滤波器（峰式）的峰值增益               
		afPara[PARA_REQ8_GPEAK1+5] = m_Configs.EqGainRight1[6];                       // 第七个滤波器（峰式）的峰值增益                
		afPara[PARA_REQ8_GTREBLE]  = m_Configs.EqGainRight1[7];                       // 第十个滤波器（高通坡式）的通带增益
		//CF
		afPara[PARA_REQ8_CFBASS]    = m_Configs.EqCFRight1[0];                     // 第一个滤波器（低通坡式）的截止频率                  
		afPara[PARA_REQ8_CFPEAK1]   = m_Configs.EqCFRight1[1];                    // 第二个滤波器（峰式）的中心频率                  
		afPara[PARA_REQ8_CFPEAK1+1] = m_Configs.EqCFRight1[2];                    // 第三个滤波器（峰式）的中心频率                  
		afPara[PARA_REQ8_CFPEAK1+2] = m_Configs.EqCFRight1[3];                   // 第四个滤波器（峰式）的中心频率                   
		afPara[PARA_REQ8_CFPEAK1+3] = m_Configs.EqCFRight1[4];                   // 第五个滤波器（峰式）的中心频率                    
		afPara[PARA_REQ8_CFPEAK1+4] = m_Configs.EqCFRight1[5];                   // 第六个滤波器（峰式）的中心频率                    
		afPara[PARA_REQ8_CFPEAK1+5] = m_Configs.EqCFRight1[6];                  // 第七个滤波器（峰式）的中心频率                      
		afPara[PARA_REQ8_CFTREBLE]  = m_Configs.EqCFRight1[7];                  // 第十个滤波器（高通坡式）的截止频率
		//Q
		afPara[PARA_REQ8_Q1]   = m_Configs.EqQRight[0];                         // 第二个滤波器（峰式）的Q值              
		afPara[PARA_REQ8_Q1+1] = m_Configs.EqQRight[1];                         // 第三个滤波器（峰式）的Q值             
		afPara[PARA_REQ8_Q1+2] = m_Configs.EqQRight[2];                         // 第四个滤波器（峰式）的Q值             
		afPara[PARA_REQ8_Q1+3] = m_Configs.EqQRight[3];                         // 第五个滤波器（峰式）的Q值
		afPara[PARA_REQ8_Q1+4] = m_Configs.EqQRight[4];                         // 第六个滤波器（峰式）的Q值
		afPara[PARA_REQ8_Q1+5] = m_Configs.EqQRight[5];                         // 第七个滤波器（峰式）的Q值 
		/* 1.3.4 右声道Limiter参数 */ 
		afPara[PARA_RLMT_ECALTIME]   = m_Configs.fLimitEca_R;                    // Static time：计算RMS能量的统计时间，单位ms
		afPara[PARA_RLMT_THRESHOLD]  = m_Configs.fLimitThres_R;                   // Threshold：输入信号能量高于该阈值时，Limiter开始限制输出幅度，单位dB
		// -12dB < Threshold < 0dB
		afPara[PARA_RLMT_ATTACKTIME] = m_Configs.fLimitAtt_R;                  // smooth time，单位ms
		afPara[PARA_RLMT_SMOOTHTIME] = m_Configs.fLimitSmo_R;                   // attack time，单位ms
		afPara[PARA_R_GAIN2] = m_Configs.ScrGainR2;
	}
	/* 1. 设计EQ */
	fMinFreq = 20;
	swCurveLen = 1000;
	EQ10Product lvEQ10Product = (EQ10Product)GetProcAddress(m_DlgEq.AudioHnd, "EQ10Product");
	EQ8Product lvEQ8Product = (EQ8Product)GetProcAddress(m_DlgEq.AudioHnd, "EQ8Product");
	lvEQ10Product(&(afPara[PARA_LEQ10_GBASS]), afCurve1, m_Configs.swFs, fMinFreq, swCurveLen);
	lvEQ10Product(&(afPara[PARA_REQ10_GBASS]), afCurve1, m_Configs.swFs, fMinFreq, swCurveLen);
	lvEQ8Product(&(afPara[PARA_LEQ8_GBASS]), afCurve2, m_Configs.swFs, fMinFreq, swCurveLen);
	lvEQ8Product(&(afPara[PARA_REQ8_GBASS]), afCurve2, m_Configs.swFs, fMinFreq, swCurveLen);

	fwrite(afPara, sizeof(float), PARANUM, fpPara);

	fclose(fpPara);
}
void CEQToolDlg::OnFileLoad()
{
	// TODO: Add your command handler code here
	// 设置过滤器   
	TCHAR szFilter[] = _T("文本文件(*.bin)|*.bin|所有文件(*.*)|*.*||");   
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("bin"), NULL, 0, szFilter, this);   
	CString strFilePath;   

	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())   
	{   
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();   
		FILE *fpPara = fopen(m_Configs.wstr2str(strFilePath.GetString()).c_str(), "rb");
		LoadParaData(fpPara);
	}
	//UpdatePara(FALSE);
}

void CEQToolDlg::LoadParaData(FILE *fpPara)
{
	//m_Configs.DivFreq_L = afPara[PARA_RDRC_DIVFREQ];
	float afPara[PARANUM] = {0.0f};
	fread(afPara, sizeof(float), PARANUM, fpPara);
	fclose(fpPara);
	m_Configs.shwChaNum = afPara[PARA_CHANUM];
	m_Configs.swFs = afPara[PARA_FS];
	m_Configs.ScrGainL1 = afPara[PARA_L_GAIN1];
	/* 1.2.2 左声道EQ参数 */
	//Gain
	m_Configs.EqGainLeft[0] = afPara[PARA_LEQ10_GBASS];                           // 第一个滤波器（低通坡式）的通带增益                    
	m_Configs.EqGainLeft[1] = afPara[PARA_LEQ10_GPEAK1];                           // 第二个滤波器（峰式）的峰值增益               
	m_Configs.EqGainLeft[2] = afPara[PARA_LEQ10_GPEAK1+1];                          // 第三个滤波器（峰式）的峰值增益                    
	m_Configs.EqGainLeft[3] = afPara[PARA_LEQ10_GPEAK1+2];                           // 第四个滤波器（峰式）的峰值增益                   
	m_Configs.EqGainLeft[4] = afPara[PARA_LEQ10_GPEAK1+3];                           // 第五个滤波器（峰式）的峰值增益                    
	m_Configs.EqGainLeft[5] = afPara[PARA_LEQ10_GPEAK1+4];                           // 第六个滤波器（峰式）的峰值增益                   
	m_Configs.EqGainLeft[6] = afPara[PARA_LEQ10_GPEAK1+5];                           // 第七个滤波器（峰式）的峰值增益                    
	m_Configs.EqGainLeft[7] = afPara[PARA_LEQ10_GPEAK1+6];                           // 第八个滤波器（峰式）的峰值增益
	m_Configs.EqGainLeft[8] = afPara[PARA_LEQ10_GPEAK1+7];                           // 第八个滤波器（峰式）的峰值增益 
	m_Configs.EqGainLeft[9] = afPara[PARA_LEQ10_GTREBLE];                         // 第九个滤波器（高通坡式）的通带增益
	//CF
	m_Configs.EqCFLeft[0] = afPara[PARA_LEQ10_CFBASS];                     // 第一个滤波器（低通坡式）的截止频率                  
	m_Configs.EqCFLeft[1] = afPara[PARA_LEQ10_CFPEAK1];                    // 第二个滤波器（峰式）的中心频率                  
	m_Configs.EqCFLeft[2] = afPara[PARA_LEQ10_CFPEAK1+1];                    // 第三个滤波器（峰式）的中心频率                  
	m_Configs.EqCFLeft[3] = afPara[PARA_LEQ10_CFPEAK1+2];                   // 第四个滤波器（峰式）的中心频率                   
	m_Configs.EqCFLeft[4] = afPara[PARA_LEQ10_CFPEAK1+3];                   // 第五个滤波器（峰式）的中心频率                    
	m_Configs.EqCFLeft[5] = afPara[PARA_LEQ10_CFPEAK1+4];                   // 第六个滤波器（峰式）的中心频率                    
	m_Configs.EqCFLeft[6] = afPara[PARA_LEQ10_CFPEAK1+5];                  // 第七个滤波器（峰式）的中心频率                      
	m_Configs.EqCFLeft[7] = afPara[PARA_LEQ10_CFPEAK1+6];                  // 第八个滤波器（峰式）的中心频率    
	m_Configs.EqCFLeft[8] = afPara[PARA_LEQ10_CFPEAK1+7];                  // 第八个滤波器（峰式）的中心频率  
	m_Configs.EqCFLeft[9] = afPara[PARA_LEQ10_CFTREBLE];                  // 第九个滤波器（高通坡式）的截止频率
	//Q
	m_Configs.EqQLeft[0] = afPara[PARA_LEQ10_Q1];                         // 第二个滤波器（峰式）的Q值              
	m_Configs.EqQLeft[1] = afPara[PARA_LEQ10_Q1+1];                         // 第三个滤波器（峰式）的Q值             
	m_Configs.EqQLeft[2] = afPara[PARA_LEQ10_Q1+2];                         // 第四个滤波器（峰式）的Q值             
	m_Configs.EqQLeft[3] = afPara[PARA_LEQ10_Q1+3];                         // 第五个滤波器（峰式）的Q值
	m_Configs.EqQLeft[4] = afPara[PARA_LEQ10_Q1+4];                         // 第六个滤波器（峰式）的Q值
	m_Configs.EqQLeft[5] = afPara[PARA_LEQ10_Q1+5];                         // 第七个滤波器（峰式）的Q值 
	m_Configs.EqQLeft[6] = afPara[PARA_LEQ10_Q1+6];                         // 第八个滤波器（峰式）的Q值
	m_Configs.EqQLeft[7] = afPara[PARA_LEQ10_Q1+7];                         // 第八个滤波器（峰式）的Q值
	/* 1.2.3 左声道DRC参数 */ 
	m_Configs.DivFreq_L = afPara[PARA_LDRC_DIVFREQ];                    // 计算RMS能量的统计时间，单位ms
	// 低频子带
	m_Configs.Ecaltime_LL = afPara[PARA_LDRC_B1_ECALTIME];                 // 计算RMS能量的统计时间，单位ms
	m_Configs.Offset_LL = afPara[PARA_LDRC_B1_MAKEUPG];                   // 线性段提升dB数
	m_Configs.Threl_LL = afPara[PARA_LDRC_B1_THREL];                 // 低能段能量阈值，单位dB
	m_Configs.Threh_LL = afPara[PARA_LDRC_B1_THREH];                 // 高能段能量阈值，单位dB
	m_Configs.Ratlnom_LL = afPara[PARA_LDRC_B1_RATLNOM];                   // 低能段压缩比例的分子
	m_Configs.Ratlden_LL = afPara[PARA_LDRC_B1_RATLDEN];                   // 低能段压缩比例的分母
	m_Configs.Rathnom_LL = afPara[PARA_LDRC_B1_RATHNOM];                   // 高能段压缩比例的分子
	m_Configs.Rathden_LL = afPara[PARA_LDRC_B1_RATHDEN];                   // 高能段压缩比例的分母
	m_Configs.Rlstime_LL = afPara[PARA_LDRC_B1_RLSTIME];                  // release time，单位ms
	m_Configs.Smthtime_LL = afPara[PARA_LDRC_B1_SMTHTIME];                  // 中间段时域平滑时间，单位ms
	m_Configs.Attatime_LL = afPara[PARA_LDRC_B1_ATTATIME];                  // attack time，单位ms
	// 高频子带
	m_Configs.Ecaltime_LH = afPara[PARA_LDRC_B2_ECALTIME];                 // 计算RMS能量的统计时间，单位ms
	m_Configs.Offset_LH = afPara[PARA_LDRC_B2_MAKEUPG];                   // 线性段提升dB数
	m_Configs.Threl_LH = afPara[PARA_LDRC_B2_THREL];                 // 低能段能量阈值，单位dB
	m_Configs.Threh_LH = afPara[PARA_LDRC_B2_THREH];                 // 高能段能量阈值，单位dB
	m_Configs.Ratlnom_LH = afPara[PARA_LDRC_B2_RATLNOM];                   // 低能段压缩比例的分子
	m_Configs.Ratlden_LH = afPara[PARA_LDRC_B2_RATLDEN];                   // 低能段压缩比例的分母
	m_Configs.Rathnom_LH = afPara[PARA_LDRC_B2_RATHNOM];                   // 高能段压缩比例的分子
	m_Configs.Rathden_LH = afPara[PARA_LDRC_B2_RATHDEN];                   // 高能段压缩比例的分母
	m_Configs.Rlstime_LH = afPara[PARA_LDRC_B2_RLSTIME];                  // release time，单位ms
	m_Configs.Smthtime_LH = afPara[PARA_LDRC_B2_SMTHTIME];                  // 中间段时域平滑时间，单位ms
	m_Configs.Attatime_LH = afPara[PARA_LDRC_B2_ATTATIME];                  // attack time，单位ms
	/* 1.24 左声道8EQ参数 */
	//Gain
	m_Configs.EqGainLeft1[0] = afPara[PARA_LEQ8_GBASS];                           // 第一个滤波器（低通坡式）的通带增益                    
	m_Configs.EqGainLeft1[1] = afPara[PARA_LEQ8_GPEAK1];                           // 第二个滤波器（峰式）的峰值增益               
	m_Configs.EqGainLeft1[2] = afPara[PARA_LEQ8_GPEAK1+1];                          // 第三个滤波器（峰式）的峰值增益                    
	m_Configs.EqGainLeft1[3] = afPara[PARA_LEQ8_GPEAK1+2];                           // 第四个滤波器（峰式）的峰值增益                   
	m_Configs.EqGainLeft1[4] = afPara[PARA_LEQ8_GPEAK1+3];                           // 第五个滤波器（峰式）的峰值增益                    
	m_Configs.EqGainLeft1[5] = afPara[PARA_LEQ8_GPEAK1+4];                           // 第六个滤波器（峰式）的峰值增益                   
	m_Configs.EqGainLeft1[6] = afPara[PARA_LEQ8_GPEAK1+5];                           // 第七个滤波器（峰式）的峰值增益                    
	m_Configs.EqGainLeft1[7] = afPara[PARA_LEQ8_GTREBLE];                         // 第九个滤波器（高通坡式）的通带增益
	//CF
	m_Configs.EqCFLeft1[0] = afPara[PARA_LEQ8_CFBASS];                     // 第一个滤波器（低通坡式）的截止频率                  
	m_Configs.EqCFLeft1[1] = afPara[PARA_LEQ8_CFPEAK1];                    // 第二个滤波器（峰式）的中心频率                  
	m_Configs.EqCFLeft1[2] = afPara[PARA_LEQ8_CFPEAK1+1];                    // 第三个滤波器（峰式）的中心频率                  
	m_Configs.EqCFLeft1[3] = afPara[PARA_LEQ8_CFPEAK1+2];                   // 第四个滤波器（峰式）的中心频率                   
	m_Configs.EqCFLeft1[4] = afPara[PARA_LEQ8_CFPEAK1+3];                   // 第五个滤波器（峰式）的中心频率                    
	m_Configs.EqCFLeft1[5] = afPara[PARA_LEQ8_CFPEAK1+4];                   // 第六个滤波器（峰式）的中心频率                    
	m_Configs.EqCFLeft1[6] = afPara[PARA_LEQ8_CFPEAK1+5];                  // 第七个滤波器（峰式）的中心频率                       
	m_Configs.EqCFLeft1[9] = afPara[PARA_LEQ8_CFTREBLE];                  // 第九个滤波器（高通坡式）的截止频率
	//Q
	m_Configs.EqQLeft1[0] = afPara[PARA_LEQ8_Q1];                         // 第二个滤波器（峰式）的Q值              
	m_Configs.EqQLeft1[1] = afPara[PARA_LEQ8_Q1+1];                         // 第三个滤波器（峰式）的Q值             
	m_Configs.EqQLeft1[2] = afPara[PARA_LEQ8_Q1+2];                         // 第四个滤波器（峰式）的Q值             
	m_Configs.EqQLeft1[3] = afPara[PARA_LEQ8_Q1+3];                         // 第五个滤波器（峰式）的Q值
	m_Configs.EqQLeft1[4] = afPara[PARA_LEQ8_Q1+4];                         // 第六个滤波器（峰式）的Q值
	m_Configs.EqQLeft1[5] = afPara[PARA_LEQ8_Q1+5];                         // 第七个滤波器（峰式）的Q值 
	/*limit 参数*/
	m_Configs.fLimitEca_L = afPara[PARA_LLMT_ECALTIME];
	m_Configs.fLimitThres_L = afPara[PARA_LLMT_THRESHOLD];
	m_Configs.fLimitAtt_L = afPara[PARA_LLMT_ATTACKTIME];
	m_Configs.fLimitSmo_L = afPara[PARA_LLMT_SMOOTHTIME];
	m_Configs.ScrGainL2 = afPara[PARA_L_GAIN2];

	m_Configs.ScrGainR1 = afPara[PARA_R_GAIN1];
	/* 1.2.2 右声道EQ参数 */
	//Gain
	m_Configs.EqGainRight[0] = afPara[PARA_REQ10_GBASS];                           // 第一个滤波器（低通坡式）的通带增益                    
	m_Configs.EqGainRight[1] = afPara[PARA_REQ10_GPEAK1];                           // 第二个滤波器（峰式）的峰值增益               
	m_Configs.EqGainRight[2] = afPara[PARA_REQ10_GPEAK1+1];                          // 第三个滤波器（峰式）的峰值增益                    
	m_Configs.EqGainRight[3] = afPara[PARA_REQ10_GPEAK1+2];                           // 第四个滤波器（峰式）的峰值增益                   
	m_Configs.EqGainRight[4] = afPara[PARA_REQ10_GPEAK1+3];                           // 第五个滤波器（峰式）的峰值增益                    
	m_Configs.EqGainRight[5] = afPara[PARA_REQ10_GPEAK1+4];                           // 第六个滤波器（峰式）的峰值增益                   
	m_Configs.EqGainRight[6] = afPara[PARA_REQ10_GPEAK1+5];                           // 第七个滤波器（峰式）的峰值增益                    
	m_Configs.EqGainRight[7] = afPara[PARA_REQ10_GPEAK1+6];                           // 第八个滤波器（峰式）的峰值增益 
	m_Configs.EqGainRight[8] = afPara[PARA_REQ10_GPEAK1+7];                           // 第八个滤波器（峰式）的峰值增益  
	m_Configs.EqGainRight[9] = afPara[PARA_REQ10_GTREBLE];                         // 第九个滤波器（高通坡式）的通带增益
	//CF
	m_Configs.EqCFRight[0] = afPara[PARA_REQ10_CFBASS];                     // 第一个滤波器（低通坡式）的截止频率                  
	m_Configs.EqCFRight[1] = afPara[PARA_REQ10_CFPEAK1];                    // 第二个滤波器（峰式）的中心频率                  
	m_Configs.EqCFRight[2] = afPara[PARA_REQ10_CFPEAK1+1];                    // 第三个滤波器（峰式）的中心频率                  
	m_Configs.EqCFRight[3] = afPara[PARA_REQ10_CFPEAK1+2];                   // 第四个滤波器（峰式）的中心频率                   
	m_Configs.EqCFRight[4] = afPara[PARA_REQ10_CFPEAK1+3];                   // 第五个滤波器（峰式）的中心频率                    
	m_Configs.EqCFRight[5] = afPara[PARA_REQ10_CFPEAK1+4];                   // 第六个滤波器（峰式）的中心频率                    
	m_Configs.EqCFRight[6] = afPara[PARA_REQ10_CFPEAK1+5];                  // 第七个滤波器（峰式）的中心频率                      
	m_Configs.EqCFRight[7] = afPara[PARA_REQ10_CFPEAK1+6];                  // 第八个滤波器（峰式）的中心频率
	m_Configs.EqCFRight[8] = afPara[PARA_REQ10_CFPEAK1+7];                  // 第八个滤波器（峰式）的中心频率 
	m_Configs.EqCFRight[9] = afPara[PARA_REQ10_CFTREBLE];                  // 第九个滤波器（高通坡式）的截止频率
	//Q
	m_Configs.EqQRight[0] = afPara[PARA_REQ10_Q1];                         // 第二个滤波器（峰式）的Q值              
	m_Configs.EqQRight[1] = afPara[PARA_REQ10_Q1+1];                         // 第三个滤波器（峰式）的Q值             
	m_Configs.EqQRight[2] = afPara[PARA_REQ10_Q1+2];                         // 第四个滤波器（峰式）的Q值             
	m_Configs.EqQRight[3] = afPara[PARA_REQ10_Q1+3];                         // 第五个滤波器（峰式）的Q值
	m_Configs.EqQRight[4] = afPara[PARA_REQ10_Q1+4];                         // 第六个滤波器（峰式）的Q值
	m_Configs.EqQRight[5] = afPara[PARA_REQ10_Q1+5];                         // 第七个滤波器（峰式）的Q值 
	m_Configs.EqQRight[6] = afPara[PARA_REQ10_Q1+6];                         // 第八个滤波器（峰式）的Q值
	m_Configs.EqQRight[7] = afPara[PARA_REQ10_Q1+7];                         // 第八个滤波器（峰式）的Q值
	/* 1.2.3 右声道DRC参数 */ 
	m_Configs.DivFreq_R = afPara[PARA_RDRC_DIVFREQ];                    // 计算RMS能量的统计时间，单位ms
	// 低频子带
	m_Configs.Ecaltime_RL = afPara[PARA_RDRC_B1_ECALTIME];                 // 计算RMS能量的统计时间，单位ms
	m_Configs.Offset_RL = afPara[PARA_RDRC_B1_MAKEUPG];                   // 线性段提升dB数
	m_Configs.Threl_RL = afPara[PARA_RDRC_B1_THREL];                 // 低能段能量阈值，单位dB
	m_Configs.Threh_RL = afPara[PARA_RDRC_B1_THREH];                 // 高能段能量阈值，单位dB
	m_Configs.Ratlnom_RL = afPara[PARA_RDRC_B1_RATLNOM];                   // 低能段压缩比例的分子
	m_Configs.Ratlden_RL = afPara[PARA_RDRC_B1_RATLDEN];                   // 低能段压缩比例的分母
	m_Configs.Rathnom_RL = afPara[PARA_RDRC_B1_RATHNOM];                   // 高能段压缩比例的分子
	m_Configs.Rathden_RL = afPara[PARA_RDRC_B1_RATHDEN];                   // 高能段压缩比例的分母
	m_Configs.Rlstime_RL = afPara[PARA_RDRC_B1_RLSTIME];                  // release time，单位ms
	m_Configs.Smthtime_RL = afPara[PARA_RDRC_B1_SMTHTIME];                  // 中间段时域平滑时间，单位ms
	m_Configs.Attatime_RL = afPara[PARA_RDRC_B1_ATTATIME];                  // attack time，单位ms
	// 高频子带
	m_Configs.Ecaltime_RH = afPara[PARA_RDRC_B2_ECALTIME];                 // 计算RMS能量的统计时间，单位ms
	m_Configs.Offset_RH = afPara[PARA_RDRC_B2_MAKEUPG];                   // 线性段提升dB数
	m_Configs.Threl_RH = afPara[PARA_RDRC_B2_THREL];                 // 低能段能量阈值，单位dB
	m_Configs.Threh_RH = afPara[PARA_RDRC_B2_THREH];                 // 高能段能量阈值，单位dB
	m_Configs.Ratlnom_RH = afPara[PARA_RDRC_B2_RATLNOM];                   // 低能段压缩比例的分子
	m_Configs.Ratlden_RH = afPara[PARA_RDRC_B2_RATLDEN];                   // 低能段压缩比例的分母
	m_Configs.Rathnom_RH = afPara[PARA_RDRC_B2_RATHNOM];                   // 高能段压缩比例的分子
	m_Configs.Rathden_RH = afPara[PARA_RDRC_B2_RATHDEN];                   // 高能段压缩比例的分母
	m_Configs.Rlstime_RH = afPara[PARA_RDRC_B2_RLSTIME];                  // release time，单位ms
	m_Configs.Smthtime_RH = afPara[PARA_RDRC_B2_SMTHTIME];                  // 中间段时域平滑时间，单位ms
	m_Configs.Attatime_RH = afPara[PARA_RDRC_B2_ATTATIME];                  // attack time，单位ms
	/* 1.2.2 右声道8EQ参数 */
	//Gain
	m_Configs.EqGainRight1[0] = afPara[PARA_REQ10_GBASS];                           // 第一个滤波器（低通坡式）的通带增益                    
	m_Configs.EqGainRight1[1] = afPara[PARA_REQ8_GPEAK1];                           // 第二个滤波器（峰式）的峰值增益               
	m_Configs.EqGainRight1[2] = afPara[PARA_REQ8_GPEAK1+1];                          // 第三个滤波器（峰式）的峰值增益                    
	m_Configs.EqGainRight1[3] = afPara[PARA_REQ8_GPEAK1+2];                           // 第四个滤波器（峰式）的峰值增益                   
	m_Configs.EqGainRight1[4] = afPara[PARA_REQ8_GPEAK1+3];                           // 第五个滤波器（峰式）的峰值增益                    
	m_Configs.EqGainRight1[5] = afPara[PARA_REQ8_GPEAK1+4];                           // 第六个滤波器（峰式）的峰值增益                   
	m_Configs.EqGainRight1[6] = afPara[PARA_REQ8_GPEAK1+5];                           // 第七个滤波器（峰式）的峰值增益                    
	m_Configs.EqGainRight1[7] = afPara[PARA_REQ8_GTREBLE];                         // 第九个滤波器（高通坡式）的通带增益
	//CF
	m_Configs.EqCFRight1[0] = afPara[PARA_REQ8_CFBASS];                     // 第一个滤波器（低通坡式）的截止频率                  
	m_Configs.EqCFRight1[1] = afPara[PARA_REQ8_CFPEAK1];                    // 第二个滤波器（峰式）的中心频率                  
	m_Configs.EqCFRight1[2] = afPara[PARA_REQ8_CFPEAK1+1];                    // 第三个滤波器（峰式）的中心频率                  
	m_Configs.EqCFRight1[3] = afPara[PARA_REQ8_CFPEAK1+2];                   // 第四个滤波器（峰式）的中心频率                   
	m_Configs.EqCFRight1[4] = afPara[PARA_REQ8_CFPEAK1+3];                   // 第五个滤波器（峰式）的中心频率                    
	m_Configs.EqCFRight1[5] = afPara[PARA_REQ8_CFPEAK1+4];                   // 第六个滤波器（峰式）的中心频率                    
	m_Configs.EqCFRight1[6] = afPara[PARA_REQ8_CFPEAK1+5];                  // 第七个滤波器（峰式）的中心频率                      
	m_Configs.EqCFRight1[7] = afPara[PARA_REQ8_CFTREBLE];                  // 第九个滤波器（高通坡式）的截止频率
	//Q
	m_Configs.EqQRight1[0] = afPara[PARA_REQ8_Q1];                         // 第二个滤波器（峰式）的Q值              
	m_Configs.EqQRight1[1] = afPara[PARA_REQ8_Q1+1];                         // 第三个滤波器（峰式）的Q值             
	m_Configs.EqQRight1[2] = afPara[PARA_REQ8_Q1+2];                         // 第四个滤波器（峰式）的Q值             
	m_Configs.EqQRight1[3] = afPara[PARA_REQ8_Q1+3];                         // 第五个滤波器（峰式）的Q值
	m_Configs.EqQRight1[4] = afPara[PARA_REQ8_Q1+4];                         // 第六个滤波器（峰式）的Q值
	m_Configs.EqQRight1[5] = afPara[PARA_REQ8_Q1+5];                         // 第七个滤波器（峰式）的Q值 
	/*limit 参数*/
	m_Configs.fLimitEca_R = afPara[PARA_RLMT_ECALTIME];
	m_Configs.fLimitThres_R = afPara[PARA_RLMT_THRESHOLD];
	m_Configs.fLimitAtt_R = afPara[PARA_RLMT_ATTACKTIME];
	m_Configs.fLimitSmo_R = afPara[PARA_RLMT_SMOOTHTIME];
	m_Configs.ScrGainR2 = afPara[PARA_R_GAIN2];

	if (m_Configs.nChannel)
	{
		SetDlgItemText(IDC_EDIT_GAIN1,cmNumString::NumToStr(m_Configs.ScrGainR1,10));
		SetDlgItemText(IDC_EDIT_GAIN2,cmNumString::NumToStr(m_Configs.ScrGainR2,10));
	}
	else
	{
		SetDlgItemText(IDC_EDIT_GAIN1,cmNumString::NumToStr(m_Configs.ScrGainL1,10));
		SetDlgItemText(IDC_EDIT_GAIN2,cmNumString::NumToStr(m_Configs.ScrGainL2,10));
	}
	m_DlgEq.InitUi(m_Configs.nEQChannel);
	m_DlgDrc.InitUi(m_Configs.nDrcChannel);
	m_DlgEq1.InitUi(m_Configs.nEQ1Channel);
	m_DlgLimit.InitUi(m_Configs.nLimitChannel);
}

void CEQToolDlg::OnBnClickedCheckLink()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_COMBO_CHANUM)->EnableWindow(m_Configs.bLink);
	m_Configs.bLink = !m_Configs.bLink;
	m_Configs.SaveToolSetting(_T(""));
}

void CEQToolDlg::OnEnKillfocusEditGain()
{
	// TODO: Add your control notification handler code here
	CString strValue1;
	GetDlgItemText(IDC_EDIT_GAIN1,strValue1);
	if (m_Configs.bLink)
	{
		m_Configs.ScrGainL1 = cmNumString::StrToDouble(strValue1);
		m_Configs.ScrGainR1 = cmNumString::StrToDouble(strValue1);
	}else
	{
		if (m_Configs.nChannel)
		{
			m_Configs.ScrGainR1 = cmNumString::StrToDouble(strValue1);
		}
		else
		{
			m_Configs.ScrGainL1 = cmNumString::StrToDouble(strValue1);
		}
	}
	m_Configs.SaveToolSetting(_T(""));
}

void CEQToolDlg::OnCbnSelchangeComboChanum()
{
	// TODO: Add your control notification handler code here
	m_Configs.nChannel = m_ComChannel.GetCurSel();
	//m_DlgEq.InitUi(m_Configs.nChannel);
	//m_DlgDrc.InitUi(m_Configs.nChannel);
	if (m_Configs.nChannel)
	{
		SetDlgItemText(IDC_EDIT_GAIN1,cmNumString::NumToStr(m_Configs.ScrGainR1,10));
		SetDlgItemText(IDC_EDIT_GAIN2,cmNumString::NumToStr(m_Configs.ScrGainR2,10));
	}
	else
	{
		SetDlgItemText(IDC_EDIT_GAIN1,cmNumString::NumToStr(m_Configs.ScrGainL1,10));
		SetDlgItemText(IDC_EDIT_GAIN2,cmNumString::NumToStr(m_Configs.ScrGainL1,10));
	}
	m_Configs.SaveToolSetting(_T(""));
}

int CEQToolDlg::UpdatePara(bool bSet)
{
	CSpawn					ShellSpawn;
	wchar_t     strCmd[2600] = {0};  
	CString strParaPath;
	strParaPath = m_strModulePath + _T("EQPara.bin");

	if (bSet)
	{
		FILE *fpPara = fopen(m_Configs.wstr2str(strParaPath.GetString()).c_str(), "wb");
		storeParaData(fpPara);
		swprintf(strCmd,nof(strCmd),TEXT("adb.exe push %s /sdcard/Para.bin"),strParaPath);
	}
	else
	{
		swprintf(strCmd,nof(strCmd),TEXT("adb.exe pull /sdcard/Para.bin %s"),strParaPath);
	}
	if(ShellSpawn.Exe(strCmd,25000, true)) 
	{
		if(0 != ShellSpawn.GetResult()) 
		{
			AfxMessageBox(_T("update parameter fail!"));
			return -1;
		}
	}
	else
	{
		AfxMessageBox(_T("update parameter fail!"));
		return -2;
	}
	if (!bSet)
	{
		FILE *fpPara = fopen(m_Configs.wstr2str(strParaPath.GetString()).c_str(), "rb");
		LoadParaData(fpPara);
	}
	return 0;
}
void CEQToolDlg::OnBnClickedButtonSet()
{
	// TODO: Add your control notification handler code here
	m_DlgEq.SaveConfig();
	m_DlgDrc.SaveConfig();
	m_DlgEq1.SaveConfig();
	m_DlgLimit.SaveConfig();
	//发送命令给设备端，设置EQ参数
	if (UpdatePara(TRUE)<0)
	{
		AfxMessageBox(_T("设置失败"));
		return;
	}

	m_DlgEq.InitChartCtrl();
	m_Configs.SaveToolSetting(_T(""));
	AfxMessageBox(_T("设置成功"));
}

void CEQToolDlg::OnBnClickedButtonRead()
{
	// TODO: Add your control notification handler code here
	if(UpdatePara(FALSE)<0)
	{
		AfxMessageBox(_T("读取参数失败"));
		return;
	}
	AfxMessageBox(_T("读取参数成功"));
}

void CEQToolDlg::ScanDeviceProc()
{
	UINT nDeviceCount = 0;
	bool bSendMsg = FALSE;
	m_pScanEvent = new CEvent(FALSE,TRUE);
	m_pScanEvent->ResetEvent();
	m_nDeviceCount = 0;
	m_bExistMsc = FALSE;
	m_bExistAdb = FALSE;
	while (!m_bTerminated)
	{
		nDeviceCount = 0;
		bSendMsg = FALSE;
		m_csScanLock.Lock();
		RK_ScanDevice(nDeviceCount,m_bExistMsc,m_bExistAdb);
		m_csScanLock.Unlock();
		if (m_nDeviceCount==0)
		{
			//m_lblDevice.SetWindowText(GetLocalString(_T("IDS_INFO_DEVICE_ON")).c_str());
			m_lblDevice.SetWindowText(_T("no find devices"));
		}
		else if (m_nDeviceCount==1)
		{
			if (m_bExistMsc)
			{
				m_lblDevice.SetWindowText(GetLocalString(_T("IDS_INFO_DEVICE_MSC")).c_str());
				m_lblDevice.SetWindowText(_T("find a msc devices"));
			}
			else if (m_bExistAdb)
			{
				m_lblDevice.SetWindowText(GetLocalString(_T("IDS_INFO_DEVICE_ADB")).c_str());
				m_lblDevice.SetWindowText(_T("find a adb devices"));
			}
			else
			{
				DWORD dwUsbType,dwDevType,dwLayer;
				RK_GetDeviceInfo(&dwLayer,&dwUsbType,&dwDevType,1);
				if (dwUsbType==1)
				{
					m_lblDevice.SetWindowText(GetLocalString(_T("IDS_INFO_DEVICE_MASKROM")).c_str());
					m_lblDevice.SetWindowText(_T("find a maskroom devices"));
				}
				else
					m_lblDevice.SetWindowText(GetLocalString(_T("IDS_INFO_DEVICE_LOADER")).c_str());

			}
		}
		else if (m_nDeviceCount>1)
		{
			m_lblDevice.SetWindowText(_T("find many devices"));
			m_lblDevice.SetWindowText(GetLocalString(_T("IDS_INFO_DEVICE_MANY")).c_str());
		}
		m_lblDevice.RedrawWindow();

		Sleep(200);
	}
	m_pScanEvent->SetEvent();
}
void CEQToolDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	m_bTerminated = TRUE;
	if (m_pScanThread)
	{
		MSG msg;
		DWORD dwRet;
		while (TRUE)
		{
			dwRet = MsgWaitForMultipleObjects(1, &m_pScanEvent->m_hObject,FALSE, 10000, QS_ALLINPUT);
			if(WAIT_OBJECT_0 ==dwRet )
			{
				break;
			}
			else if( (WAIT_OBJECT_0+1)==dwRet )
			{
				while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}

			}
			else if (WAIT_TIMEOUT==dwRet)
			{
				TerminateThread(m_pScanThread->m_hThread,0);
				break;
			}
		}//end while
		m_pScanThread = NULL;
		delete m_pScanEvent;
		m_pScanEvent = NULL;
	}
	if (m_bUpgradeDllInitOK)
	{
		RK_Uninitialize();
	}

	CDialog::OnClose();
}

void CEQToolDlg::OnBnClickedButtonSave()
{
	// TODO: Add your control notification handler code here
	CString strValue1,strValue2;
	GetDlgItemText(IDC_EDIT_GAIN1,strValue1);
	GetDlgItemText(IDC_EDIT_GAIN2,strValue2);
	if (m_Configs.bLink)
	{
		//m_DlgEq.SavePara(0);
		//m_DlgEq.SavePara(1);
		//m_DlgDrc.SavePara(0);
		//m_DlgDrc.SavePara(1);
		//m_DlgEq1.SavePara(0);
		//m_DlgEq1.SavePara(1);
		//m_DlgLimit.SavePara(0);
		//m_DlgLimit.SavePara(1);
		m_Configs.ScrGainL1 = cmNumString::StrToDouble(strValue1);
		m_Configs.ScrGainR1 = cmNumString::StrToDouble(strValue1);
	}
	else
	{
		//m_DlgEq.SavePara(m_Configs.nChannel);
		//m_DlgDrc.SavePara(m_Configs.nChannel);
		//m_DlgEq1.SavePara(m_Configs.nChannel);
		//m_DlgLimit.SavePara(m_Configs.nChannel);
		if (m_Configs.nChannel)
		{
			m_Configs.ScrGainR1 = cmNumString::StrToInt32(strValue2);
		}
		else
		{
			m_Configs.ScrGainL1 = cmNumString::StrToInt32(strValue2);
		}
	}
	m_DlgEq.SaveConfig();
	m_DlgDrc.SaveConfig();
	m_DlgEq1.SaveConfig();
	m_DlgLimit.SaveConfig();
	m_DlgEq.InitChartCtrl();
	m_Configs.SaveToolSetting(_T(""));
	AfxMessageBox(_T("保存成功"));
}

void CEQToolDlg::OnBnClickedButtonCancel()
{
	// TODO: Add your control notification handler code here
	m_DlgEq.InitUi(m_Configs.nChannel);
	m_DlgDrc.InitUi(m_Configs.nChannel);
	if (m_Configs.nChannel)
	{
		SetDlgItemText(IDC_EDIT_GAIN1,cmNumString::NumToStr(m_Configs.ScrGainR1,10));
	}
	else
	{
		SetDlgItemText(IDC_EDIT_GAIN1,cmNumString::NumToStr(m_Configs.ScrGainL1));
	}
}

void CEQToolDlg::OnCbnSelchangeComboEqmode()
{
	// TODO: Add your control notification handler code here
	m_Configs.bEQSwtch = m_ComEqMode.GetCurSel();

	m_Configs.SaveToolSetting(_T(""));
}

void CEQToolDlg::OnCbnSelchangeComboDrcmode()
{
	// TODO: Add your control notification handler code here
	m_Configs.bDrcSwtch = m_ComDrcMode.GetCurSel();

	m_Configs.SaveToolSetting(_T(""));
}

void CEQToolDlg::OnCbnSelchangeComboEqmode2()
{
	// TODO: Add your control notification handler code here
	m_Configs.bEQSwtch1 = m_ComEqMode1.GetCurSel();

	m_Configs.SaveToolSetting(_T(""));
}

void CEQToolDlg::OnCbnSelchangeComboLimitmode()
{
	// TODO: Add your control notification handler code here
	m_Configs.bLimitSwtch = m_ComLimitMode.GetCurSel();

	m_Configs.SaveToolSetting(_T(""));
}

void CEQToolDlg::OnEnKillfocusEditGain2()
{
	// TODO: Add your control notification handler code here
	CString strValue1;
	GetDlgItemText(IDC_EDIT_GAIN2,strValue1);
	if (m_Configs.bLink)
	{
		m_Configs.ScrGainL2 = cmNumString::StrToDouble(strValue1);
		m_Configs.ScrGainR2 = cmNumString::StrToDouble(strValue1);
	}else
	{
		if (m_Configs.nChannel)
		{
			m_Configs.ScrGainR2 = cmNumString::StrToDouble(strValue1);
		}
		else
		{
			m_Configs.ScrGainL2 = cmNumString::StrToDouble(strValue1);
		}
	}
	m_Configs.SaveToolSetting(_T(""));
}
