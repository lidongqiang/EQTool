
// EQToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EQTool.h"
#include "EQToolDlg.h"
#include "cmfuns.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CEQToolDlg �Ի���

UINT ThreadScanDevice(LPVOID lpParam)
{
	CEQToolDlg* pMainDlg = (CEQToolDlg*)lpParam;
	pMainDlg->ScanDeviceProc();
	return 0;
}


CEQToolDlg::CEQToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEQToolDlg::IDD, pParent),m_DlgEq(m_Configs,m_LocalLan),m_DlgDrc(m_Configs,m_LocalLan)
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
	DDX_Text(pDX, IDC_EDIT_GAIN, m_edtGain);
	DDV_MinMaxInt(pDX, m_edtGain, -12, 12);
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
	ON_EN_KILLFOCUS(IDC_EDIT_GAIN, &CEQToolDlg::OnEnKillfocusEditGain)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANUM, &CEQToolDlg::OnCbnSelchangeComboChanum)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CEQToolDlg::OnBnClickedButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_READ, &CEQToolDlg::OnBnClickedButtonRead)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CEQToolDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CEQToolDlg::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CEQToolDlg ��Ϣ��������

BOOL CEQToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵������ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//ShowWindow(SW_MAXIMIZE);

	// TODO: �ڴ����Ӷ���ĳ�ʼ������
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

	InitDevInfo.bScan4FsUsb = FALSE;
	InitDevInfo.emSupportDevice = 0;
	InitDevInfo.uiRockMscTimeout = 30;
	InitDevInfo.uiRockusbTimeout = 30;
	InitDevInfo.usRockMscPid = 0;
	InitDevInfo.usRockMscVid = 0;
	InitDevInfo.usRockusbPid = 0;
	InitDevInfo.usRockusbVid = 0;

	InitLogInfo.bLogEnable = TRUE;
	InitLogInfo.lpszLogPathName = (LPTSTR)(LPCTSTR)m_strLogPath;

	InitCallbackInfo.pProgressPromptProc = NULL;//you can set it to ProgressPromptProc for showing upgrade info;
	InitCallbackInfo.pUpgradeStepPromptProc = NULL;//you can set it to UpgradeStepPromptProc for showing progress info;
	m_bUpgradeDllInitOK = RK_Initialize(InitDevInfo, InitLogInfo, InitCallbackInfo);
	if (!m_bUpgradeDllInitOK)
	{
		MessageBox(_T("Initialize RKUpgrade dll failed!"),_T("ERROR"),MB_ICONERROR|MB_OK);
	}
	else
	{
		m_pScanThread = AfxBeginThread(ThreadScanDevice,(LPVOID)this);
	}

	InitUi();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի���������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CEQToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
		SetDlgItemText(IDC_EDIT_GAIN,cmNumString::NumToStr(m_Configs.ScrGainR));
	}
	else
	{
		SetDlgItemText(IDC_EDIT_GAIN,cmNumString::NumToStr(m_Configs.ScrGainL));
	}

	//ΪTab Control��������ҳ��  
	m_tabInfo.InsertItem(0, _T("EQ"));  
	m_tabInfo.InsertItem(1, _T("DRC"));  

	//���������Ի���  
	m_DlgEq.Create(IDD_DIALOG_EQ, &m_tabInfo);  
	m_DlgDrc.Create(IDD_DIALOG_DRC, &m_tabInfo);
	//�趨��Tab����ʾ�ķ�Χ  
	CRect rc;  
	m_tabInfo.GetClientRect(rc);
	rc.top += 20;  

	m_DlgEq.MoveWindow(&rc);  
	m_DlgDrc.MoveWindow(&rc);  

	//�ѶԻ������ָ�뱣������  
	pDialog[0] = &m_DlgEq;  
	pDialog[1] = &m_DlgDrc;  

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
			/*If the specified item is a pop-up menu (as opposed to an item within the pop-up menu), the return value is �C1 **/
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
	TCHAR szFilter[] = _T("�ı��ļ�(*.bin)|*.bin|�����ļ�(*.*)|*.*||");  
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
	/* 1.1 ���������������� */
	afPara[PARA_CHANUM]    = m_Configs.shwChaNum;                      // ������
	afPara[PARA_EQSWTCH]   = m_Configs.bEQSwtch;                // EQ����
	afPara[PARA_DRCSWTCH]  = m_Configs.bDrcSwtch;                // DRC����
	afPara[PARA_FS]        = m_Configs.swFs;                           // ������

	/* 1.2 ���������� */
	/* 1.2.1 ���������� */
	afPara[PARA_L_GAIN] = m_Configs.ScrGainL;
	//afPara[PARA_L_GAIN] = -6;
	/* 1.2.2 ������EQ���� */
	//Gain
	afPara[PARA_LEQ_GBASS]    = m_Configs.EqGainLeft[0];                           // ��һ���˲�������ͨ��ʽ����ͨ������                    
	afPara[PARA_LEQ_GPEAK1]   = m_Configs.EqGainLeft[1];                           // �ڶ����˲�������ʽ���ķ�ֵ����               
	afPara[PARA_LEQ_GPEAK1+1] = m_Configs.EqGainLeft[2];                          // �������˲�������ʽ���ķ�ֵ����                    
	afPara[PARA_LEQ_GPEAK1+2] = m_Configs.EqGainLeft[3];                           // ���ĸ��˲�������ʽ���ķ�ֵ����                   
	afPara[PARA_LEQ_GPEAK1+3] = m_Configs.EqGainLeft[4];                           // ������˲�������ʽ���ķ�ֵ����                    
	afPara[PARA_LEQ_GPEAK1+4] = m_Configs.EqGainLeft[5];                           // �������˲�������ʽ���ķ�ֵ����                   
	afPara[PARA_LEQ_GPEAK1+5] = m_Configs.EqGainLeft[6];                           // ���߸��˲�������ʽ���ķ�ֵ����                    
	afPara[PARA_LEQ_GPEAK1+6] = m_Configs.EqGainLeft[7];                           // �ڰ˸��˲�������ʽ���ķ�ֵ����                   
	afPara[PARA_LEQ_GTREBLE]  = m_Configs.EqGainLeft[8];                         // �ھŸ��˲�������ͨ��ʽ����ͨ������
	//CF
	afPara[PARA_LEQ_CFBASS]    = m_Configs.EqCFLeft[0];                         // ��һ���˲�������ͨ��ʽ���Ľ�ֹƵ��                        
	afPara[PARA_LEQ_CFPEAK1]   = m_Configs.EqCFLeft[1];                        // �ڶ����˲�������ʽ��������Ƶ��                     
	afPara[PARA_LEQ_CFPEAK1+1] = m_Configs.EqCFLeft[2];                        // �������˲�������ʽ��������Ƶ��                     
	afPara[PARA_LEQ_CFPEAK1+2] = m_Configs.EqCFLeft[3];                       // ���ĸ��˲�������ʽ��������Ƶ��                      
	afPara[PARA_LEQ_CFPEAK1+3] = m_Configs.EqCFLeft[4];                       // ������˲�������ʽ��������Ƶ��                       
	afPara[PARA_LEQ_CFPEAK1+4] = m_Configs.EqCFLeft[5];                       // �������˲�������ʽ��������Ƶ��                      
	afPara[PARA_LEQ_CFPEAK1+5] = m_Configs.EqCFLeft[6];                      // ���߸��˲�������ʽ��������Ƶ��                        
	afPara[PARA_LEQ_CFPEAK1+6] = m_Configs.EqCFLeft[7];                      // �ڰ˸��˲�������ʽ��������Ƶ��                      
	afPara[PARA_LEQ_CFTREBLE]  = m_Configs.EqCFLeft[8];                      // �ھŸ��˲�������ͨ��ʽ���Ľ�ֹƵ��
	//Q
	afPara[PARA_LEQ_Q1]   = m_Configs.EqQLeft[0];                             // �ڶ����˲�������ʽ����Qֵ               
	afPara[PARA_LEQ_Q1+1] = m_Configs.EqQLeft[1];                             // �������˲�������ʽ����Qֵ                        
	afPara[PARA_LEQ_Q1+2] = m_Configs.EqQLeft[2];                             // ���ĸ��˲�������ʽ����Qֵ                        
	afPara[PARA_LEQ_Q1+3] = m_Configs.EqQLeft[3];                             // ������˲�������ʽ����Qֵ  
	afPara[PARA_LEQ_Q1+4] = m_Configs.EqQLeft[4];                             // �������˲�������ʽ����Qֵ  
	afPara[PARA_LEQ_Q1+5] = m_Configs.EqQLeft[5];                             // ���߸��˲�������ʽ����Qֵ  
	afPara[PARA_LEQ_Q1+6] = m_Configs.EqQLeft[6];                             // �ڰ˸��˲�������ʽ����Qֵ  
	/* 1.2.3 ������DRC���� */ 
	afPara[PARA_LDRC_DIVFREQ] = m_Configs.DivFreq_L;                        // ����RMS������ͳ��ʱ�䣬��λms
	// ��Ƶ�Ӵ�
	afPara[PARA_LDRC_B1_ECALTIME] = m_Configs.Ecaltime_LL;                     // ����RMS������ͳ��ʱ�䣬��λms
	afPara[PARA_LDRC_B1_MAKEUPG]   = m_Configs.Offset_LL;                       // ���Զ�����dB��
	afPara[PARA_LDRC_B1_THREL]    = m_Configs.Threl_LL;                     // ���ܶ�������ֵ����λdB
	afPara[PARA_LDRC_B1_THREH]    = m_Configs.Threh_LL;                     // ���ܶ�������ֵ����λdB
	afPara[PARA_LDRC_B1_RATLNOM]  = m_Configs.Ratlnom_LL;                       // ���ܶ�ѹ�������ķ���
	afPara[PARA_LDRC_B1_RATLDEN]  = m_Configs.Ratlden_LL;                       // ���ܶ�ѹ�������ķ�ĸ
	afPara[PARA_LDRC_B1_RATHNOM]  = m_Configs.Rathnom_LL;                       // ���ܶ�ѹ�������ķ���
	afPara[PARA_LDRC_B1_RATHDEN]  = m_Configs.Rathden_LL;                       // ���ܶ�ѹ�������ķ�ĸ
	afPara[PARA_LDRC_B1_RLSTIME]  = m_Configs.Rlstime_LL;                      // release time����λms
	afPara[PARA_LDRC_B1_SMTHTIME] = m_Configs.Smthtime_LL;                      // �м��ʱ��ƽ��ʱ�䣬��λms
	afPara[PARA_LDRC_B1_ATTATIME] = m_Configs.Attatime_LL;                      // attack time����λms
	// ��Ƶ�Ӵ�
	afPara[PARA_LDRC_B2_ECALTIME] = m_Configs.Ecaltime_LH;                     // ����RMS������ͳ��ʱ�䣬��λms
	afPara[PARA_LDRC_B2_MAKEUPG]   = m_Configs.Offset_LH;                       // ���Զ�����dB��
	afPara[PARA_LDRC_B2_THREL]    = m_Configs.Threl_LH;                     // ���ܶ�������ֵ����λdB
	afPara[PARA_LDRC_B2_THREH]    = m_Configs.Threh_LH;                     // ���ܶ�������ֵ����λdB
	afPara[PARA_LDRC_B2_RATLNOM]  = m_Configs.Ratlnom_LH;                       // ���ܶ�ѹ�������ķ���
	afPara[PARA_LDRC_B2_RATLDEN]  = m_Configs.Ratlden_LH;                       // ���ܶ�ѹ�������ķ�ĸ
	afPara[PARA_LDRC_B2_RATHNOM]  = m_Configs.Rathnom_LH;                       // ���ܶ�ѹ�������ķ���
	afPara[PARA_LDRC_B2_RATHDEN]  = m_Configs.Rathden_LH;                       // ���ܶ�ѹ�������ķ�ĸ
	afPara[PARA_LDRC_B2_RLSTIME]  = m_Configs.Rlstime_LH;                      // release time����λms
	afPara[PARA_LDRC_B2_SMTHTIME] = m_Configs.Smthtime_LH;                      // �м��ʱ��ƽ��ʱ�䣬��λms
	afPara[PARA_LDRC_B2_ATTATIME] = m_Configs.Attatime_LH;                      // attack time����λms

	/* 1.3 ���������� */
	if (m_Configs.shwChaNum == 2)
	{
		/* 1.2.1 ���������� */
		afPara[PARA_R_GAIN] = m_Configs.ScrGainR;
		/* 1.2.2 ������EQ���� */
		//Gain
		afPara[PARA_REQ_GBASS]    = m_Configs.EqGainRight[0];                     // ��һ���˲�������ͨ��ʽ����ͨ������             
		afPara[PARA_REQ_GPEAK1]   = m_Configs.EqGainRight[1];                       // �ڶ����˲�������ʽ���ķ�ֵ����                        
		afPara[PARA_REQ_GPEAK1+1] = m_Configs.EqGainRight[2];                       // �������˲�������ʽ���ķ�ֵ����                       
		afPara[PARA_REQ_GPEAK1+2] = m_Configs.EqGainRight[3];                       // ���ĸ��˲�������ʽ���ķ�ֵ����                
		afPara[PARA_REQ_GPEAK1+3] = m_Configs.EqGainRight[4];                       // ������˲�������ʽ���ķ�ֵ����                
		afPara[PARA_REQ_GPEAK1+4] = m_Configs.EqGainRight[5];                      // �������˲�������ʽ���ķ�ֵ����               
		afPara[PARA_REQ_GPEAK1+5] = m_Configs.EqGainRight[6];                       // ���߸��˲�������ʽ���ķ�ֵ����                
		afPara[PARA_REQ_GPEAK1+6] = m_Configs.EqGainRight[7];                       // �ڰ˸��˲�������ʽ���ķ�ֵ����               
		afPara[PARA_REQ_GTREBLE]  = m_Configs.EqGainRight[8];                       // �ھŸ��˲�������ͨ��ʽ����ͨ������
		//CF
		afPara[PARA_REQ_CFBASS]    = m_Configs.EqCFRight[0];                     // ��һ���˲�������ͨ��ʽ���Ľ�ֹƵ��                  
		afPara[PARA_REQ_CFPEAK1]   = m_Configs.EqCFRight[1];                    // �ڶ����˲�������ʽ��������Ƶ��                  
		afPara[PARA_REQ_CFPEAK1+1] = m_Configs.EqCFRight[2];                    // �������˲�������ʽ��������Ƶ��                  
		afPara[PARA_REQ_CFPEAK1+2] = m_Configs.EqCFRight[3];                   // ���ĸ��˲�������ʽ��������Ƶ��                   
		afPara[PARA_REQ_CFPEAK1+3] = m_Configs.EqCFRight[4];                   // ������˲�������ʽ��������Ƶ��                    
		afPara[PARA_REQ_CFPEAK1+4] = m_Configs.EqCFRight[5];                   // �������˲�������ʽ��������Ƶ��                    
		afPara[PARA_REQ_CFPEAK1+5] = m_Configs.EqCFRight[6];                  // ���߸��˲�������ʽ��������Ƶ��                      
		afPara[PARA_REQ_CFPEAK1+6] = m_Configs.EqCFRight[7];                  // �ڰ˸��˲�������ʽ��������Ƶ��                    
		afPara[PARA_REQ_CFTREBLE]  = m_Configs.EqCFRight[8];                  // �ھŸ��˲�������ͨ��ʽ���Ľ�ֹƵ��
		//Q
		afPara[PARA_REQ_Q1]   = m_Configs.EqQRight[0];                         // �ڶ����˲�������ʽ����Qֵ              
		afPara[PARA_REQ_Q1+1] = m_Configs.EqQRight[1];                         // �������˲�������ʽ����Qֵ             
		afPara[PARA_REQ_Q1+2] = m_Configs.EqQRight[2];                         // ���ĸ��˲�������ʽ����Qֵ             
		afPara[PARA_REQ_Q1+3] = m_Configs.EqQRight[3];                         // ������˲�������ʽ����Qֵ
		afPara[PARA_REQ_Q1+4] = m_Configs.EqQRight[4];                         // �������˲�������ʽ����Qֵ
		afPara[PARA_REQ_Q1+5] = m_Configs.EqQRight[5];                         // ���߸��˲�������ʽ����Qֵ 
		afPara[PARA_REQ_Q1+6] = m_Configs.EqQRight[6];                         // �ڰ˸��˲�������ʽ����Qֵ
		/* 1.2.3 ������DRC���� */ 
		afPara[PARA_RDRC_DIVFREQ] = m_Configs.DivFreq_R;                    // ����RMS������ͳ��ʱ�䣬��λms
		// ��Ƶ�Ӵ�
		afPara[PARA_RDRC_B1_ECALTIME] = m_Configs.Ecaltime_RL;                 // ����RMS������ͳ��ʱ�䣬��λms
		afPara[PARA_RDRC_B1_MAKEUPG]   = m_Configs.Offset_RL;                   // ���Զ�����dB��
		afPara[PARA_RDRC_B1_THREL]    = m_Configs.Threl_RL;                 // ���ܶ�������ֵ����λdB
		afPara[PARA_RDRC_B1_THREH]    = m_Configs.Threh_RL;                 // ���ܶ�������ֵ����λdB
		afPara[PARA_RDRC_B1_RATLNOM]  = m_Configs.Ratlnom_RL;                   // ���ܶ�ѹ�������ķ���
		afPara[PARA_RDRC_B1_RATLDEN]  = m_Configs.Ratlden_RL;                   // ���ܶ�ѹ�������ķ�ĸ
		afPara[PARA_RDRC_B1_RATHNOM]  = m_Configs.Rathnom_RL;                   // ���ܶ�ѹ�������ķ���
		afPara[PARA_RDRC_B1_RATHDEN]  = m_Configs.Rathden_RL;                   // ���ܶ�ѹ�������ķ�ĸ
		afPara[PARA_RDRC_B1_RLSTIME]  = m_Configs.Rlstime_RL;                  // release time����λms
		afPara[PARA_RDRC_B1_SMTHTIME] = m_Configs.Smthtime_RL;                  // �м��ʱ��ƽ��ʱ�䣬��λms
		afPara[PARA_RDRC_B1_ATTATIME] = m_Configs.Attatime_RL;                  // attack time����λms
		// ��Ƶ�Ӵ�
		afPara[PARA_RDRC_B2_ECALTIME] = m_Configs.Ecaltime_RH;                 // ����RMS������ͳ��ʱ�䣬��λms
		afPara[PARA_RDRC_B2_MAKEUPG]   = m_Configs.Offset_RH;                   // ���Զ�����dB��
		afPara[PARA_RDRC_B2_THREL]    = m_Configs.Threl_RH;                 // ���ܶ�������ֵ����λdB
		afPara[PARA_RDRC_B2_THREH]    = m_Configs.Threh_RH;                 // ���ܶ�������ֵ����λdB
		afPara[PARA_RDRC_B2_RATLNOM]  = m_Configs.Ratlnom_RH;                   // ���ܶ�ѹ�������ķ���
		afPara[PARA_RDRC_B2_RATLDEN]  = m_Configs.Ratlden_RH;                   // ���ܶ�ѹ�������ķ�ĸ
		afPara[PARA_RDRC_B2_RATHNOM]  = m_Configs.Rathnom_RH;                   // ���ܶ�ѹ�������ķ���
		afPara[PARA_RDRC_B2_RATHDEN]  = m_Configs.Rathden_RH;                   // ���ܶ�ѹ�������ķ�ĸ
		afPara[PARA_RDRC_B2_RLSTIME]  = m_Configs.Rlstime_RH;                  // release time����λms
		afPara[PARA_RDRC_B2_SMTHTIME] = m_Configs.Smthtime_RH;                  // �м��ʱ��ƽ��ʱ�䣬��λms
		afPara[PARA_RDRC_B2_ATTATIME] = m_Configs.Attatime_RH;                  // attack time����λms
	}
	/* 1. ���EQ */
	fMinFreq = 20;
	swCurveLen = 1000;
	EQProduct lvEQProduct = (EQProduct)GetProcAddress(m_DlgEq.AudioHnd, "EQProduct");
	lvEQProduct(&(afPara[PARA_LEQ_GBASS]), afCurve1, m_Configs.swFs, fMinFreq, swCurveLen);
	lvEQProduct(&(afPara[PARA_REQ_GBASS]), afCurve2, m_Configs.swFs, fMinFreq, swCurveLen);

	fwrite(afPara, sizeof(float), PARANUM, fpPara);

	fclose(fpPara);
}
void CEQToolDlg::OnFileLoad()
{
	// TODO: Add your command handler code here
	// ���ù�����   
	TCHAR szFilter[] = _T("�ı��ļ�(*.bin)|*.bin|�����ļ�(*.*)|*.*||");   
	// ������ļ��Ի���   
	CFileDialog fileDlg(TRUE, _T("bin"), NULL, 0, szFilter, this);   
	CString strFilePath;   

	// ��ʾ���ļ��Ի���   
	if (IDOK == fileDlg.DoModal())   
	{   
		// ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����   
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
	m_Configs.ScrGainL = afPara[PARA_L_GAIN];
	/* 1.2.2 ������EQ���� */
	//Gain
	m_Configs.EqGainLeft[0] = afPara[PARA_LEQ_GBASS];                           // ��һ���˲�������ͨ��ʽ����ͨ������                    
	m_Configs.EqGainLeft[1] = afPara[PARA_LEQ_GPEAK1];                           // �ڶ����˲�������ʽ���ķ�ֵ����               
	m_Configs.EqGainLeft[2] = afPara[PARA_LEQ_GPEAK1+1];                          // �������˲�������ʽ���ķ�ֵ����                    
	m_Configs.EqGainLeft[3] = afPara[PARA_LEQ_GPEAK1+2];                           // ���ĸ��˲�������ʽ���ķ�ֵ����                   
	m_Configs.EqGainLeft[4] = afPara[PARA_LEQ_GPEAK1+3];                           // ������˲�������ʽ���ķ�ֵ����                    
	m_Configs.EqGainLeft[5] = afPara[PARA_LEQ_GPEAK1+4];                           // �������˲�������ʽ���ķ�ֵ����                   
	m_Configs.EqGainLeft[6] = afPara[PARA_LEQ_GPEAK1+5];                           // ���߸��˲�������ʽ���ķ�ֵ����                    
	m_Configs.EqGainLeft[7] = afPara[PARA_LEQ_GPEAK1+6];                           // �ڰ˸��˲�������ʽ���ķ�ֵ����                   
	m_Configs.EqGainLeft[8] = afPara[PARA_LEQ_GTREBLE];                         // �ھŸ��˲�������ͨ��ʽ����ͨ������
	//CF
	m_Configs.EqCFLeft[0] = afPara[PARA_LEQ_CFBASS];                     // ��һ���˲�������ͨ��ʽ���Ľ�ֹƵ��                  
	m_Configs.EqCFLeft[1] = afPara[PARA_LEQ_CFPEAK1];                    // �ڶ����˲�������ʽ��������Ƶ��                  
	m_Configs.EqCFLeft[2] = afPara[PARA_LEQ_CFPEAK1+1];                    // �������˲�������ʽ��������Ƶ��                  
	m_Configs.EqCFLeft[3] = afPara[PARA_LEQ_CFPEAK1+2];                   // ���ĸ��˲�������ʽ��������Ƶ��                   
	m_Configs.EqCFLeft[4] = afPara[PARA_LEQ_CFPEAK1+3];                   // ������˲�������ʽ��������Ƶ��                    
	m_Configs.EqCFLeft[5] = afPara[PARA_LEQ_CFPEAK1+4];                   // �������˲�������ʽ��������Ƶ��                    
	m_Configs.EqCFLeft[6] = afPara[PARA_LEQ_CFPEAK1+5];                  // ���߸��˲�������ʽ��������Ƶ��                      
	m_Configs.EqCFLeft[7] = afPara[PARA_LEQ_CFPEAK1+6];                  // �ڰ˸��˲�������ʽ��������Ƶ��                    
	m_Configs.EqCFLeft[8] = afPara[PARA_LEQ_CFTREBLE];                  // �ھŸ��˲�������ͨ��ʽ���Ľ�ֹƵ��
	//Q
	m_Configs.EqQLeft[0] = afPara[PARA_LEQ_Q1];                         // �ڶ����˲�������ʽ����Qֵ              
	m_Configs.EqQLeft[1] = afPara[PARA_LEQ_Q1+1];                         // �������˲�������ʽ����Qֵ             
	m_Configs.EqQLeft[2] = afPara[PARA_LEQ_Q1+2];                         // ���ĸ��˲�������ʽ����Qֵ             
	m_Configs.EqQLeft[3] = afPara[PARA_LEQ_Q1+3];                         // ������˲�������ʽ����Qֵ
	m_Configs.EqQLeft[4] = afPara[PARA_LEQ_Q1+4];                         // �������˲�������ʽ����Qֵ
	m_Configs.EqQLeft[5] = afPara[PARA_LEQ_Q1+5];                         // ���߸��˲�������ʽ����Qֵ 
	m_Configs.EqQLeft[6] = afPara[PARA_LEQ_Q1+6];                         // �ڰ˸��˲�������ʽ����Qֵ
	/* 1.2.3 ������DRC���� */ 
	m_Configs.DivFreq_L = afPara[PARA_LDRC_DIVFREQ];                    // ����RMS������ͳ��ʱ�䣬��λms
	// ��Ƶ�Ӵ�
	m_Configs.Ecaltime_LL = afPara[PARA_LDRC_B1_ECALTIME];                 // ����RMS������ͳ��ʱ�䣬��λms
	m_Configs.Offset_LL = afPara[PARA_LDRC_B1_MAKEUPG];                   // ���Զ�����dB��
	m_Configs.Threl_LL = afPara[PARA_LDRC_B1_THREL];                 // ���ܶ�������ֵ����λdB
	m_Configs.Threh_LL = afPara[PARA_LDRC_B1_THREH];                 // ���ܶ�������ֵ����λdB
	m_Configs.Ratlnom_LL = afPara[PARA_LDRC_B1_RATLNOM];                   // ���ܶ�ѹ�������ķ���
	m_Configs.Ratlden_LL = afPara[PARA_LDRC_B1_RATLDEN];                   // ���ܶ�ѹ�������ķ�ĸ
	m_Configs.Rathnom_LL = afPara[PARA_LDRC_B1_RATHNOM];                   // ���ܶ�ѹ�������ķ���
	m_Configs.Rathden_LL = afPara[PARA_LDRC_B1_RATHDEN];                   // ���ܶ�ѹ�������ķ�ĸ
	m_Configs.Rlstime_LL = afPara[PARA_LDRC_B1_RLSTIME];                  // release time����λms
	m_Configs.Smthtime_LL = afPara[PARA_LDRC_B1_SMTHTIME];                  // �м��ʱ��ƽ��ʱ�䣬��λms
	m_Configs.Attatime_LL = afPara[PARA_LDRC_B1_ATTATIME];                  // attack time����λms
	// ��Ƶ�Ӵ�
	m_Configs.Ecaltime_LH = afPara[PARA_LDRC_B2_ECALTIME];                 // ����RMS������ͳ��ʱ�䣬��λms
	m_Configs.Offset_LH = afPara[PARA_LDRC_B2_MAKEUPG];                   // ���Զ�����dB��
	m_Configs.Threl_LH = afPara[PARA_LDRC_B2_THREL];                 // ���ܶ�������ֵ����λdB
	m_Configs.Threh_LH = afPara[PARA_LDRC_B2_THREH];                 // ���ܶ�������ֵ����λdB
	m_Configs.Ratlnom_LH = afPara[PARA_LDRC_B2_RATLNOM];                   // ���ܶ�ѹ�������ķ���
	m_Configs.Ratlden_LH = afPara[PARA_LDRC_B2_RATLDEN];                   // ���ܶ�ѹ�������ķ�ĸ
	m_Configs.Rathnom_LH = afPara[PARA_LDRC_B2_RATHNOM];                   // ���ܶ�ѹ�������ķ���
	m_Configs.Rathden_LH = afPara[PARA_LDRC_B2_RATHDEN];                   // ���ܶ�ѹ�������ķ�ĸ
	m_Configs.Rlstime_LH = afPara[PARA_LDRC_B2_RLSTIME];                  // release time����λms
	m_Configs.Smthtime_LH = afPara[PARA_LDRC_B2_SMTHTIME];                  // �м��ʱ��ƽ��ʱ�䣬��λms
	m_Configs.Attatime_LH = afPara[PARA_LDRC_B2_ATTATIME];                  // attack time����λms


	/* 1.2.2 ������EQ���� */
	//Gain
	m_Configs.EqGainRight[0] = afPara[PARA_REQ_GBASS];                           // ��һ���˲�������ͨ��ʽ����ͨ������                    
	m_Configs.EqGainRight[1] = afPara[PARA_REQ_GPEAK1];                           // �ڶ����˲�������ʽ���ķ�ֵ����               
	m_Configs.EqGainRight[2] = afPara[PARA_REQ_GPEAK1+1];                          // �������˲�������ʽ���ķ�ֵ����                    
	m_Configs.EqGainRight[3] = afPara[PARA_REQ_GPEAK1+2];                           // ���ĸ��˲�������ʽ���ķ�ֵ����                   
	m_Configs.EqGainRight[4] = afPara[PARA_REQ_GPEAK1+3];                           // ������˲�������ʽ���ķ�ֵ����                    
	m_Configs.EqGainRight[5] = afPara[PARA_REQ_GPEAK1+4];                           // �������˲�������ʽ���ķ�ֵ����                   
	m_Configs.EqGainRight[6] = afPara[PARA_REQ_GPEAK1+5];                           // ���߸��˲�������ʽ���ķ�ֵ����                    
	m_Configs.EqGainRight[7] = afPara[PARA_REQ_GPEAK1+6];                           // �ڰ˸��˲�������ʽ���ķ�ֵ����                   
	m_Configs.EqGainRight[8] = afPara[PARA_REQ_GTREBLE];                         // �ھŸ��˲�������ͨ��ʽ����ͨ������
	//CF
	m_Configs.EqCFRight[0] = afPara[PARA_REQ_CFBASS];                     // ��һ���˲�������ͨ��ʽ���Ľ�ֹƵ��                  
	m_Configs.EqCFRight[1] = afPara[PARA_REQ_CFPEAK1];                    // �ڶ����˲�������ʽ��������Ƶ��                  
	m_Configs.EqCFRight[2] = afPara[PARA_REQ_CFPEAK1+1];                    // �������˲�������ʽ��������Ƶ��                  
	m_Configs.EqCFRight[3] = afPara[PARA_REQ_CFPEAK1+2];                   // ���ĸ��˲�������ʽ��������Ƶ��                   
	m_Configs.EqCFRight[4] = afPara[PARA_REQ_CFPEAK1+3];                   // ������˲�������ʽ��������Ƶ��                    
	m_Configs.EqCFRight[5] = afPara[PARA_REQ_CFPEAK1+4];                   // �������˲�������ʽ��������Ƶ��                    
	m_Configs.EqCFRight[6] = afPara[PARA_REQ_CFPEAK1+5];                  // ���߸��˲�������ʽ��������Ƶ��                      
	m_Configs.EqCFRight[7] = afPara[PARA_REQ_CFPEAK1+6];                  // �ڰ˸��˲�������ʽ��������Ƶ��                    
	m_Configs.EqCFRight[8] = afPara[PARA_REQ_CFTREBLE];                  // �ھŸ��˲�������ͨ��ʽ���Ľ�ֹƵ��
	//Q
	m_Configs.EqQRight[0] = afPara[PARA_REQ_Q1];                         // �ڶ����˲�������ʽ����Qֵ              
	m_Configs.EqQRight[1] = afPara[PARA_REQ_Q1+1];                         // �������˲�������ʽ����Qֵ             
	m_Configs.EqQRight[2] = afPara[PARA_REQ_Q1+2];                         // ���ĸ��˲�������ʽ����Qֵ             
	m_Configs.EqQRight[3] = afPara[PARA_REQ_Q1+3];                         // ������˲�������ʽ����Qֵ
	m_Configs.EqQRight[4] = afPara[PARA_REQ_Q1+4];                         // �������˲�������ʽ����Qֵ
	m_Configs.EqQRight[5] = afPara[PARA_REQ_Q1+5];                         // ���߸��˲�������ʽ����Qֵ 
	m_Configs.EqQRight[6] = afPara[PARA_REQ_Q1+6];                         // �ڰ˸��˲�������ʽ����Qֵ
	/* 1.2.3 ������DRC���� */ 
	m_Configs.DivFreq_R = afPara[PARA_RDRC_DIVFREQ];                    // ����RMS������ͳ��ʱ�䣬��λms
	// ��Ƶ�Ӵ�
	m_Configs.Ecaltime_RL = afPara[PARA_RDRC_B1_ECALTIME];                 // ����RMS������ͳ��ʱ�䣬��λms
	m_Configs.Offset_RL = afPara[PARA_RDRC_B1_MAKEUPG];                   // ���Զ�����dB��
	m_Configs.Threl_RL = afPara[PARA_RDRC_B1_THREL];                 // ���ܶ�������ֵ����λdB
	m_Configs.Threh_RL = afPara[PARA_RDRC_B1_THREH];                 // ���ܶ�������ֵ����λdB
	m_Configs.Ratlnom_RL = afPara[PARA_RDRC_B1_RATLNOM];                   // ���ܶ�ѹ�������ķ���
	m_Configs.Ratlden_RL = afPara[PARA_RDRC_B1_RATLDEN];                   // ���ܶ�ѹ�������ķ�ĸ
	m_Configs.Rathnom_RL = afPara[PARA_RDRC_B1_RATHNOM];                   // ���ܶ�ѹ�������ķ���
	m_Configs.Rathden_RL = afPara[PARA_RDRC_B1_RATHDEN];                   // ���ܶ�ѹ�������ķ�ĸ
	m_Configs.Rlstime_RL = afPara[PARA_RDRC_B1_RLSTIME];                  // release time����λms
	m_Configs.Smthtime_RL = afPara[PARA_RDRC_B1_SMTHTIME];                  // �м��ʱ��ƽ��ʱ�䣬��λms
	m_Configs.Attatime_RL = afPara[PARA_RDRC_B1_ATTATIME];                  // attack time����λms
	// ��Ƶ�Ӵ�
	m_Configs.Ecaltime_RH = afPara[PARA_RDRC_B2_ECALTIME];                 // ����RMS������ͳ��ʱ�䣬��λms
	m_Configs.Offset_RH = afPara[PARA_RDRC_B2_MAKEUPG];                   // ���Զ�����dB��
	m_Configs.Threl_RH = afPara[PARA_RDRC_B2_THREL];                 // ���ܶ�������ֵ����λdB
	m_Configs.Threh_RH = afPara[PARA_RDRC_B2_THREH];                 // ���ܶ�������ֵ����λdB
	m_Configs.Ratlnom_RH = afPara[PARA_RDRC_B2_RATLNOM];                   // ���ܶ�ѹ�������ķ���
	m_Configs.Ratlden_RH = afPara[PARA_RDRC_B2_RATLDEN];                   // ���ܶ�ѹ�������ķ�ĸ
	m_Configs.Rathnom_RH = afPara[PARA_RDRC_B2_RATHNOM];                   // ���ܶ�ѹ�������ķ���
	m_Configs.Rathden_RH = afPara[PARA_RDRC_B2_RATHDEN];                   // ���ܶ�ѹ�������ķ�ĸ
	m_Configs.Rlstime_RH = afPara[PARA_RDRC_B2_RLSTIME];                  // release time����λms
	m_Configs.Smthtime_RH = afPara[PARA_RDRC_B2_SMTHTIME];                  // �м��ʱ��ƽ��ʱ�䣬��λms
	m_Configs.Attatime_RH = afPara[PARA_RDRC_B2_ATTATIME];                  // attack time����λms

	if (m_Configs.nChannel)
	{
		SetDlgItemText(IDC_EDIT_GAIN,cmNumString::NumToStr(m_Configs.ScrGainR));
	}
	else
	{
		SetDlgItemText(IDC_EDIT_GAIN,cmNumString::NumToStr(m_Configs.ScrGainL));
	}
	m_DlgEq.InitUi(m_Configs.nChannel);
	m_DlgDrc.InitUi(m_Configs.nChannel);
}

void CEQToolDlg::storeParaData1(FILE *fpPara)
{
	signed short int shwChaNum;
	signed int swFs;
	float afPara[PARANUM] = {0.0f};

	/* 1. ���ò��Բ��� */
	shwChaNum = 2;      // ������
	swFs      = 44100;  // ������

	/* 1.1 ���������������� */
	afPara[PARA_CHANUM]    = shwChaNum;                      // ������
	afPara[PARA_EQSWTCH]   = m_Configs.bEQSwtch;                // EQ����
	afPara[PARA_DRCSWTCH]  =  m_Configs.bDrcSwtch;                // DRC����
	afPara[PARA_FS]        = swFs;                           // ������

	/* 1.2 ���������� */
	/* 1.2.1 ���������� */
	afPara[PARA_L_GAIN] = -6;
	/* 1.2.2 ������EQ���� */
	//Gain
	afPara[PARA_LEQ_GBASS]    = 0;                           // ��һ���˲�������ͨ��ʽ����ͨ������                    
	afPara[PARA_LEQ_GPEAK1]   = 0;                           // �ڶ����˲�������ʽ���ķ�ֵ����               
	afPara[PARA_LEQ_GPEAK1+1] = 15;                          // �������˲�������ʽ���ķ�ֵ����                    
	afPara[PARA_LEQ_GPEAK1+2] = 0;                           // ���ĸ��˲�������ʽ���ķ�ֵ����                   
	afPara[PARA_LEQ_GPEAK1+3] = 0;                           // ������˲�������ʽ���ķ�ֵ����                    
	afPara[PARA_LEQ_GPEAK1+4] = 0;                           // �������˲�������ʽ���ķ�ֵ����                   
	afPara[PARA_LEQ_GPEAK1+5] = 0;                           // ���߸��˲�������ʽ���ķ�ֵ����                    
	afPara[PARA_LEQ_GPEAK1+6] = 0;                           // �ڰ˸��˲�������ʽ���ķ�ֵ����                   
	afPara[PARA_LEQ_GTREBLE]  = -15;                         // �ھŸ��˲�������ͨ��ʽ����ͨ������
	//CF
	afPara[PARA_LEQ_CFBASS]    = 60;                         // ��һ���˲�������ͨ��ʽ���Ľ�ֹƵ��                        
	afPara[PARA_LEQ_CFPEAK1]   = 150;                        // �ڶ����˲�������ʽ��������Ƶ��                     
	afPara[PARA_LEQ_CFPEAK1+1] = 400;                        // �������˲�������ʽ��������Ƶ��                     
	afPara[PARA_LEQ_CFPEAK1+2] = 1000;                       // ���ĸ��˲�������ʽ��������Ƶ��                      
	afPara[PARA_LEQ_CFPEAK1+3] = 3000;                       // ������˲�������ʽ��������Ƶ��                       
	afPara[PARA_LEQ_CFPEAK1+4] = 7000;                       // �������˲�������ʽ��������Ƶ��                      
	afPara[PARA_LEQ_CFPEAK1+5] = 15000;                      // ���߸��˲�������ʽ��������Ƶ��                        
	afPara[PARA_LEQ_CFPEAK1+6] = 17000;                      // �ڰ˸��˲�������ʽ��������Ƶ��                      
	afPara[PARA_LEQ_CFTREBLE]  = 17500;                      // �ھŸ��˲�������ͨ��ʽ���Ľ�ֹƵ��
	//Q
	afPara[PARA_LEQ_Q1]   = 2.5;                             // �ڶ����˲�������ʽ����Qֵ               
	afPara[PARA_LEQ_Q1+1] = 2.5;                             // �������˲�������ʽ����Qֵ                        
	afPara[PARA_LEQ_Q1+2] = 2.5;                             // ���ĸ��˲�������ʽ����Qֵ                        
	afPara[PARA_LEQ_Q1+3] = 2.5;                             // ������˲�������ʽ����Qֵ  
	afPara[PARA_LEQ_Q1+4] = 2.5;                             // �������˲�������ʽ����Qֵ  
	afPara[PARA_LEQ_Q1+5] = 2.5;                             // ���߸��˲�������ʽ����Qֵ  
	afPara[PARA_LEQ_Q1+6] = 2.5;                             // �ڰ˸��˲�������ʽ����Qֵ  
	/* 1.2.3 ������DRC���� */ 
	afPara[PARA_LDRC_DIVFREQ] = 1000;                        // ����RMS������ͳ��ʱ�䣬��λms
	// ��Ƶ�Ӵ�
	afPara[PARA_LDRC_B1_ECALTIME] = 300;                     // ����RMS������ͳ��ʱ�䣬��λms
	afPara[PARA_LDRC_B1_MAKEUPG]   = 6;                       // ���Զ�����dB��
	afPara[PARA_LDRC_B1_THREL]    = -84;                     // ���ܶ�������ֵ����λdB
	afPara[PARA_LDRC_B1_THREH]    = -18;                     // ���ܶ�������ֵ����λdB
	afPara[PARA_LDRC_B1_RATLNOM]  = 1;                       // ���ܶ�ѹ�������ķ���
	afPara[PARA_LDRC_B1_RATLDEN]  = 1;                       // ���ܶ�ѹ�������ķ�ĸ
	afPara[PARA_LDRC_B1_RATHNOM]  = 5;                       // ���ܶ�ѹ�������ķ���
	afPara[PARA_LDRC_B1_RATHDEN]  = 2;                       // ���ܶ�ѹ�������ķ�ĸ
	afPara[PARA_LDRC_B1_RLSTIME]  = 20;                      // release time����λms
	afPara[PARA_LDRC_B1_SMTHTIME] = 20;                      // �м��ʱ��ƽ��ʱ�䣬��λms
	afPara[PARA_LDRC_B1_ATTATIME] = 20;                      // attack time����λms
	// ��Ƶ�Ӵ�
	afPara[PARA_LDRC_B2_ECALTIME] = 200;                     // ����RMS������ͳ��ʱ�䣬��λms
	afPara[PARA_LDRC_B2_MAKEUPG]   = 8;                       // ���Զ�����dB��
	afPara[PARA_LDRC_B2_THREL]    = -70;                     // ���ܶ�������ֵ����λdB
	afPara[PARA_LDRC_B2_THREH]    = -10;                     // ���ܶ�������ֵ����λdB
	afPara[PARA_LDRC_B2_RATLNOM]  = 1;                       // ���ܶ�ѹ�������ķ���
	afPara[PARA_LDRC_B2_RATLDEN]  = 1;                       // ���ܶ�ѹ�������ķ�ĸ
	afPara[PARA_LDRC_B2_RATHNOM]  = 2;                       // ���ܶ�ѹ�������ķ���
	afPara[PARA_LDRC_B2_RATHDEN]  = 1;                       // ���ܶ�ѹ�������ķ�ĸ
	afPara[PARA_LDRC_B2_RLSTIME]  = 30;                      // release time����λms
	afPara[PARA_LDRC_B2_SMTHTIME] = 30;                      // �м��ʱ��ƽ��ʱ�䣬��λms
	afPara[PARA_LDRC_B2_ATTATIME] = 30;                      // attack time����λms

	/* 1.3 ���������� */
	if (shwChaNum == 2)
	{
		/* 1.2.1 ���������� */
		afPara[PARA_R_GAIN] = -6;
		/* 1.2.2 ������EQ���� */
		//Gain
		afPara[PARA_REQ_GBASS]    = -15;                     // ��һ���˲�������ͨ��ʽ����ͨ������                         
		afPara[PARA_REQ_GPEAK1]   = 0;                       // �ڶ����˲�������ʽ���ķ�ֵ����                        
		afPara[PARA_REQ_GPEAK1+1] = 0;                       // �������˲�������ʽ���ķ�ֵ����                       
		afPara[PARA_REQ_GPEAK1+2] = 0;                       // ���ĸ��˲�������ʽ���ķ�ֵ����                
		afPara[PARA_REQ_GPEAK1+3] = 0;                       // ������˲�������ʽ���ķ�ֵ����                
		afPara[PARA_REQ_GPEAK1+4] = 15;                      // �������˲�������ʽ���ķ�ֵ����                
		afPara[PARA_REQ_GPEAK1+5] = 0;                       // ���߸��˲�������ʽ���ķ�ֵ����                
		afPara[PARA_REQ_GPEAK1+6] = 0;                       // �ڰ˸��˲�������ʽ���ķ�ֵ����               
		afPara[PARA_REQ_GTREBLE]  = 0;                       // �ھŸ��˲�������ͨ��ʽ����ͨ������
		//CF
		afPara[PARA_REQ_CFBASS]    = 60;                     // ��һ���˲�������ͨ��ʽ���Ľ�ֹƵ��                  
		afPara[PARA_REQ_CFPEAK1]   = 150;                    // �ڶ����˲�������ʽ��������Ƶ��                  
		afPara[PARA_REQ_CFPEAK1+1] = 400;                    // �������˲�������ʽ��������Ƶ��                  
		afPara[PARA_REQ_CFPEAK1+2] = 1000;                   // ���ĸ��˲�������ʽ��������Ƶ��                   
		afPara[PARA_REQ_CFPEAK1+3] = 3000;                   // ������˲�������ʽ��������Ƶ��                    
		afPara[PARA_REQ_CFPEAK1+4] = 7000;                   // �������˲�������ʽ��������Ƶ��                    
		afPara[PARA_REQ_CFPEAK1+5] = 15000;                  // ���߸��˲�������ʽ��������Ƶ��                      
		afPara[PARA_REQ_CFPEAK1+6] = 17000;                  // �ڰ˸��˲�������ʽ��������Ƶ��                    
		afPara[PARA_REQ_CFTREBLE]  = 17500;                  // �ھŸ��˲�������ͨ��ʽ���Ľ�ֹƵ��
		//Q
		afPara[PARA_REQ_Q1]   = 2.5;                         // �ڶ����˲�������ʽ����Qֵ              
		afPara[PARA_REQ_Q1+1] = 2.5;                         // �������˲�������ʽ����Qֵ             
		afPara[PARA_REQ_Q1+2] = 2.5;                         // ���ĸ��˲�������ʽ����Qֵ             
		afPara[PARA_REQ_Q1+3] = 2.5;                         // ������˲�������ʽ����Qֵ
		afPara[PARA_REQ_Q1+4] = 2.5;                         // �������˲�������ʽ����Qֵ
		afPara[PARA_REQ_Q1+5] = 2.5;                         // ���߸��˲�������ʽ����Qֵ 
		afPara[PARA_REQ_Q1+6] = 2.5;                         // �ڰ˸��˲�������ʽ����Qֵ
		/* 1.2.3 ������DRC���� */ 
		afPara[PARA_RDRC_DIVFREQ] = 1000;                    // ����RMS������ͳ��ʱ�䣬��λms
		// ��Ƶ�Ӵ�
		afPara[PARA_RDRC_B1_ECALTIME] = 300;                 // ����RMS������ͳ��ʱ�䣬��λms
		afPara[PARA_RDRC_B1_MAKEUPG]   = 6;                   // ���Զ�����dB��
		afPara[PARA_RDRC_B1_THREL]    = -84;                 // ���ܶ�������ֵ����λdB
		afPara[PARA_RDRC_B1_THREH]    = -18;                 // ���ܶ�������ֵ����λdB
		afPara[PARA_RDRC_B1_RATLNOM]  = 1;                   // ���ܶ�ѹ�������ķ���
		afPara[PARA_RDRC_B1_RATLDEN]  = 1;                   // ���ܶ�ѹ�������ķ�ĸ
		afPara[PARA_RDRC_B1_RATHNOM]  = 5;                   // ���ܶ�ѹ�������ķ���
		afPara[PARA_RDRC_B1_RATHDEN]  = 2;                   // ���ܶ�ѹ�������ķ�ĸ
		afPara[PARA_RDRC_B1_RLSTIME]  = 20;                  // release time����λms
		afPara[PARA_RDRC_B1_SMTHTIME] = 20;                  // �м��ʱ��ƽ��ʱ�䣬��λms
		afPara[PARA_RDRC_B1_ATTATIME] = 20;                  // attack time����λms
		// ��Ƶ�Ӵ�
		afPara[PARA_RDRC_B2_ECALTIME] = 200;                 // ����RMS������ͳ��ʱ�䣬��λms
		afPara[PARA_RDRC_B2_MAKEUPG]   = 8;                   // ���Զ�����dB��
		afPara[PARA_RDRC_B2_THREL]    = -70;                 // ���ܶ�������ֵ����λdB
		afPara[PARA_RDRC_B2_THREH]    = -10;                 // ���ܶ�������ֵ����λdB
		afPara[PARA_RDRC_B2_RATLNOM]  = 1;                   // ���ܶ�ѹ�������ķ���
		afPara[PARA_RDRC_B2_RATLDEN]  = 1;                   // ���ܶ�ѹ�������ķ�ĸ
		afPara[PARA_RDRC_B2_RATHNOM]  = 2;                   // ���ܶ�ѹ�������ķ���
		afPara[PARA_RDRC_B2_RATHDEN]  = 1;                   // ���ܶ�ѹ�������ķ�ĸ
		afPara[PARA_RDRC_B2_RLSTIME]  = 30;                  // release time����λms
		afPara[PARA_RDRC_B2_SMTHTIME] = 30;                  // �м��ʱ��ƽ��ʱ�䣬��λms
		afPara[PARA_RDRC_B2_ATTATIME] = 30;                  // attack time����λms
	}

	fwrite(afPara, sizeof(float), PARANUM, fpPara);

	fclose(fpPara);
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
	//CString strValue;
	//GetDlgItemText(IDC_EDIT_GAIN,strValue);
	//if (m_Configs.bLink)
	//{
	//	m_Configs.ScrGainL = cmNumString::StrToDouble(strValue);
	//	m_Configs.ScrGainR = cmNumString::StrToDouble(strValue);
	//}else
	//{
	//	if (m_Configs.nChannel)
	//	{
	//		m_Configs.ScrGainR = cmNumString::StrToDouble(strValue);
	//	}
	//	else
	//	{
	//		m_Configs.ScrGainL = cmNumString::StrToDouble(strValue);
	//	}
	//}
	//m_Configs.SaveToolSetting(_T(""));
}

void CEQToolDlg::OnCbnSelchangeComboChanum()
{
	// TODO: Add your control notification handler code here
	//m_DlgEq.SavePara(m_Configs.nChannel);
	//m_DlgDrc.SavePara(m_Configs.nChannel);
	m_Configs.nChannel = m_ComChannel.GetCurSel();
	m_DlgEq.InitUi(m_Configs.nChannel);
	m_DlgDrc.InitUi(m_Configs.nChannel);
	if (m_Configs.nChannel)
	{
		SetDlgItemText(IDC_EDIT_GAIN,cmNumString::NumToStr(m_Configs.ScrGainR));
	}
	else
	{
		SetDlgItemText(IDC_EDIT_GAIN,cmNumString::NumToStr(m_Configs.ScrGainL));
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
	if (m_Configs.bLink)
	{
		m_DlgEq.SavePara(0);
		m_DlgEq.SavePara(1);
		m_DlgDrc.SavePara(0);
		m_DlgDrc.SavePara(1);
	}
	else
	{
		m_DlgEq.SavePara(m_Configs.nChannel);
		m_DlgDrc.SavePara(m_Configs.nChannel);
	}
	//����������豸�ˣ�����EQ����
	if (UpdatePara(TRUE)<0)
	{
		AfxMessageBox(_T("����ʧ��"));
		return;
	}

	m_DlgEq.InitChartCtrl();
	m_Configs.SaveToolSetting(_T(""));
	AfxMessageBox(_T("���óɹ�"));
}

void CEQToolDlg::OnBnClickedButtonRead()
{
	// TODO: Add your control notification handler code here
	if(UpdatePara(FALSE)<0)
	{
		AfxMessageBox(_T("��ȡ����ʧ��"));
		return;
	}
	AfxMessageBox(_T("��ȡ�����ɹ�"));
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
	CString strValue;
	GetDlgItemText(IDC_EDIT_GAIN,strValue);
	if (m_Configs.bLink)
	{
		m_DlgEq.SavePara(0);
		m_DlgEq.SavePara(1);
		m_DlgDrc.SavePara(0);
		m_DlgDrc.SavePara(1);
		m_Configs.ScrGainL = cmNumString::StrToDouble(strValue);
		m_Configs.ScrGainR = cmNumString::StrToDouble(strValue);
	}
	else
	{
		m_DlgEq.SavePara(m_Configs.nChannel);
		m_DlgDrc.SavePara(m_Configs.nChannel);
		if (m_Configs.nChannel)
		{
			m_Configs.ScrGainR = cmNumString::StrToDouble(strValue);
		}
		else
		{
			m_Configs.ScrGainL = cmNumString::StrToDouble(strValue);
		}
	}
	m_DlgEq.InitChartCtrl();
	m_Configs.SaveToolSetting(_T(""));
	AfxMessageBox(_T("����ɹ�"));
}

void CEQToolDlg::OnBnClickedButtonCancel()
{
	// TODO: Add your control notification handler code here
	m_DlgEq.InitUi(m_Configs.nChannel);
	m_DlgDrc.InitUi(m_Configs.nChannel);
	if (m_Configs.nChannel)
	{
		SetDlgItemText(IDC_EDIT_GAIN,cmNumString::NumToStr(m_Configs.ScrGainR));
	}
	else
	{
		SetDlgItemText(IDC_EDIT_GAIN,cmNumString::NumToStr(m_Configs.ScrGainL));
	}
}