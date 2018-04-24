// DlgEq.cpp : implementation file
//

#include "stdafx.h"
#include "EQTool.h"
#include "DlgEq.h"
#include <math.h>

// CDlgEq dialog

IMPLEMENT_DYNAMIC(CDlgEq, CDialog)

CDlgEq::CDlgEq(CIniSettingBase &Config,CIniLocalLan &LocalLang,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEq::IDD, pParent),m_Configs(Config),m_LocalLang(LocalLang)
{

}

CDlgEq::~CDlgEq()
{
}

void CDlgEq::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ChartCtrl_EQ, m_ChartEq);  
	DDX_Control(pDX, IDC_COMBO_CHANNUM, m_ComChannum);
}


BEGIN_MESSAGE_MAP(CDlgEq, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgEq::OnBnClickedButtonSave)
	ON_EN_KILLFOCUS(IDC_EDIT_GAIN1, &CDlgEq::OnEnKillfocusEditGain1)
	ON_EN_KILLFOCUS(IDC_EDIT_GAIN2, &CDlgEq::OnEnKillfocusEditGain2)
	ON_EN_KILLFOCUS(IDC_EDIT_GAIN3, &CDlgEq::OnEnKillfocusEditGain3)
	ON_EN_KILLFOCUS(IDC_EDIT_GAIN4, &CDlgEq::OnEnKillfocusEditGain4)
	ON_EN_KILLFOCUS(IDC_EDIT_GAIN5, &CDlgEq::OnEnKillfocusEditGain5)
	ON_EN_KILLFOCUS(IDC_EDIT_GAIN6, &CDlgEq::OnEnKillfocusEditGain6)
	ON_EN_KILLFOCUS(IDC_EDIT_GAIN7, &CDlgEq::OnEnKillfocusEditGain7)
	ON_EN_KILLFOCUS(IDC_EDIT_GAIN8, &CDlgEq::OnEnKillfocusEditGain8)
	ON_EN_KILLFOCUS(IDC_EDIT_GF1, &CDlgEq::OnEnKillfocusEditGf1)
	ON_EN_KILLFOCUS(IDC_EDIT_GF2, &CDlgEq::OnEnKillfocusEditGf2)
	ON_EN_KILLFOCUS(IDC_EDIT_GF3, &CDlgEq::OnEnKillfocusEditGf3)
	ON_EN_KILLFOCUS(IDC_EDIT_GF4, &CDlgEq::OnEnKillfocusEditGf4)
	ON_EN_KILLFOCUS(IDC_EDIT_GF5, &CDlgEq::OnEnKillfocusEditGf5)
	ON_EN_KILLFOCUS(IDC_EDIT_GF6, &CDlgEq::OnEnKillfocusEditGf6)
	ON_EN_KILLFOCUS(IDC_EDIT_GF7, &CDlgEq::OnEnKillfocusEditGf7)
	ON_EN_KILLFOCUS(IDC_EDIT_GF8, &CDlgEq::OnEnKillfocusEditGf8)
	ON_EN_KILLFOCUS(IDC_EDIT_Q1, &CDlgEq::OnEnKillfocusEditQ1)
	ON_EN_KILLFOCUS(IDC_EDIT_Q2, &CDlgEq::OnEnKillfocusEditQ2)
	ON_EN_KILLFOCUS(IDC_EDIT_Q3, &CDlgEq::OnEnKillfocusEditQ3)
	ON_EN_KILLFOCUS(IDC_EDIT_Q4, &CDlgEq::OnEnKillfocusEditQ4)
	ON_EN_SETFOCUS(IDC_EDIT_Q5, &CDlgEq::OnEnSetfocusEditQ5)
	ON_EN_KILLFOCUS(IDC_EDIT_Q6, &CDlgEq::OnEnKillfocusEditQ6)
	ON_EN_KILLFOCUS(IDC_EDIT_Q7, &CDlgEq::OnEnKillfocusEditQ7)
	ON_EN_KILLFOCUS(IDC_EDIT_Q8, &CDlgEq::OnEnKillfocusEditQ8)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNUM, &CDlgEq::OnCbnSelchangeComboChannum)
	ON_BN_CLICKED(IDC_CHECK_LINK, &CDlgEq::OnBnClickedCheckLink)
END_MESSAGE_MAP()


// CDlgEq message handlers
void CDlgEq::InitChartCtrl()
{
	CChartLineSerie* pLineSerie = m_ChartEq.CreateLineSerie();

	//signed short int  shwChaNum;
	signed int swCurveLen;
	float  fMinFreq;
	float  afPara[PARANUM] =  {0.0f};
	float  afCurve1[3000];
	float  afCurve2[3000];


	/* 1.1 左右声道公共参数 */
	afPara[PARA_CHANUM]    = m_Configs.shwChaNum;
	afPara[PARA_EQ10SWTCH]   = m_Configs.bEQSwtch;
	afPara[PARA_DRCSWTCH]  = m_Configs.bDrcSwtch;
	afPara[PARA_FS]        = m_Configs.swFs;

	/* 1.2 左声道参数 */
	/* 1.2.1 左声道增益 */
	afPara[PARA_L_GAIN1] = m_Configs.ScrGainL1;
	/* 1.2.2 左声道EQ参数 */
	//Gain
	afPara[PARA_LEQ10_GBASS]    = m_Configs.EqGainLeft[0];                        
	afPara[PARA_LEQ10_GPEAK1]   = m_Configs.EqGainLeft[1];                       
	afPara[PARA_LEQ10_GPEAK1+1] = m_Configs.EqGainLeft[2];                       
	afPara[PARA_LEQ10_GPEAK1+2] = m_Configs.EqGainLeft[3];                       
	afPara[PARA_LEQ10_GPEAK1+3] = m_Configs.EqGainLeft[4];                        
	afPara[PARA_LEQ10_GPEAK1+4] = m_Configs.EqGainLeft[5];                       
	afPara[PARA_LEQ10_GPEAK1+5] = m_Configs.EqGainLeft[6];                        
	afPara[PARA_LEQ10_GPEAK1+6] = m_Configs.EqGainLeft[7];
	afPara[PARA_LEQ10_GPEAK1+7] = m_Configs.EqGainLeft[8]; 
	afPara[PARA_LEQ10_GTREBLE]  = m_Configs.EqGainLeft[9]; 
	//CF
	afPara[PARA_LEQ10_CFBASS]    = m_Configs.EqCFLeft[0];                        
	afPara[PARA_LEQ10_CFPEAK1]   = m_Configs.EqCFLeft[1];                       
	afPara[PARA_LEQ10_CFPEAK1+1] = m_Configs.EqCFLeft[2];                       
	afPara[PARA_LEQ10_CFPEAK1+2] = m_Configs.EqCFLeft[3];                       
	afPara[PARA_LEQ10_CFPEAK1+3] = m_Configs.EqCFLeft[4];                        
	afPara[PARA_LEQ10_CFPEAK1+4] = m_Configs.EqCFLeft[5];                       
	afPara[PARA_LEQ10_CFPEAK1+5] = m_Configs.EqCFLeft[6];                        
	afPara[PARA_LEQ10_CFPEAK1+6] = m_Configs.EqCFLeft[7];
	afPara[PARA_LEQ10_CFPEAK1+7] = m_Configs.EqCFLeft[8]; 
	afPara[PARA_LEQ10_CFTREBLE]  = m_Configs.EqCFLeft[9];
	//Q
	afPara[PARA_LEQ10_Q1]   = m_Configs.EqQLeft[0];                        
	afPara[PARA_LEQ10_Q1+1] = m_Configs.EqQLeft[1];                       
	afPara[PARA_LEQ10_Q1+2] = m_Configs.EqQLeft[2];                       
	afPara[PARA_LEQ10_Q1+3] = m_Configs.EqQLeft[3]; 
	afPara[PARA_LEQ10_Q1+4] = m_Configs.EqQLeft[4]; 
	afPara[PARA_LEQ10_Q1+5] = m_Configs.EqQLeft[5]; 
	afPara[PARA_LEQ10_Q1+6] = m_Configs.EqQLeft[6]; 
	afPara[PARA_LEQ10_Q1+7] = m_Configs.EqQLeft[7]; 

	/* 1.3 右声道参数 */
	if (m_Configs.nEQChannel == 1)
	{
		afPara[PARA_R_GAIN1] = m_Configs.ScrGainR1;
		//Gain
		afPara[PARA_REQ10_GBASS]    = m_Configs.EqGainRight[0];                        
		afPara[PARA_REQ10_GPEAK1]   = m_Configs.EqGainRight[1];                       
		afPara[PARA_REQ10_GPEAK1+1] = m_Configs.EqGainRight[2];                       
		afPara[PARA_REQ10_GPEAK1+2] = m_Configs.EqGainRight[3];                       
		afPara[PARA_REQ10_GPEAK1+3] = m_Configs.EqGainRight[4];                        
		afPara[PARA_REQ10_GPEAK1+4] = m_Configs.EqGainRight[5];                       
		afPara[PARA_REQ10_GPEAK1+5] = m_Configs.EqGainRight[6];                        
		afPara[PARA_REQ10_GPEAK1+6] = m_Configs.EqGainRight[7];
		afPara[PARA_REQ10_GPEAK1+7] = m_Configs.EqGainRight[8];
		afPara[PARA_REQ10_GTREBLE]  = m_Configs.EqGainRight[9]; 
		//CF
		afPara[PARA_REQ10_CFBASS]    = m_Configs.EqCFRight[0];                        
		afPara[PARA_REQ10_CFPEAK1]   = m_Configs.EqCFRight[1];                       
		afPara[PARA_REQ10_CFPEAK1+1] = m_Configs.EqCFRight[2];                       
		afPara[PARA_REQ10_CFPEAK1+2] = m_Configs.EqCFRight[3];                       
		afPara[PARA_REQ10_CFPEAK1+3] = m_Configs.EqCFRight[4];                        
		afPara[PARA_REQ10_CFPEAK1+4] = m_Configs.EqCFRight[5];                       
		afPara[PARA_REQ10_CFPEAK1+5] = m_Configs.EqCFRight[6];                        
		afPara[PARA_REQ10_CFPEAK1+6] = m_Configs.EqCFRight[7];
		afPara[PARA_REQ10_CFPEAK1+7] = m_Configs.EqCFRight[8];
		afPara[PARA_REQ10_CFTREBLE]  = m_Configs.EqCFRight[9];
		//Q
		afPara[PARA_REQ10_Q1]   = m_Configs.EqQRight[0];                        
		afPara[PARA_REQ10_Q1+1] = m_Configs.EqQRight[1];                       
		afPara[PARA_REQ10_Q1+2] = m_Configs.EqQRight[2];                       
		afPara[PARA_REQ10_Q1+3] = m_Configs.EqQRight[3]; 
		afPara[PARA_REQ10_Q1+4] = m_Configs.EqQRight[4]; 
		afPara[PARA_REQ10_Q1+5] = m_Configs.EqQRight[5]; 
		afPara[PARA_REQ10_Q1+6] = m_Configs.EqQRight[6];
		afPara[PARA_REQ10_Q1+7] = m_Configs.EqQRight[7]; 
	}

	/* 1. 设计EQ */
	fMinFreq = 20;
	swCurveLen = 1000;
	EQProduct lvEQProduct = (EQProduct)GetProcAddress(AudioHnd, "EQ10Product");
	lvEQProduct(&(afPara[PARA_LEQ10_GBASS]), afCurve1, m_Configs.swFs, fMinFreq, swCurveLen);

	/* 1.2 右声道EQ */
	if (m_Configs.nEQChannel == 1 )
	{
		lvEQProduct(&(afPara[PARA_REQ10_GBASS]), afCurve1, m_Configs.swFs, fMinFreq, swCurveLen);
	}
	m_ChartEq.RemoveAllSeries();
	double tmp = 0.0; 
	double XValues[1000],YValues[1000];  
	for (int i=0;i<swCurveLen;i++)  
	{   
		XValues[i] = i;
		YValues[i] = afCurve1[i];
	}  
	pLineSerie = m_ChartEq.CreateLineSerie();  
	pLineSerie->SetPoints(XValues,YValues,swCurveLen);  
	pLineSerie->SetColor(RGB(255,0,0)); 
	pLineSerie->SetWidth(pLineSerie->GetWidth()*2);


}
BOOL CDlgEq::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	AudioHnd = NULL;
	AudioHnd = LoadLibrary(TEXT("Tool.dll"));
	if (AudioHnd==NULL)
	{
		AfxMessageBox(_T("load Tool.dll fail!"));
	}
	m_LocalLang.TreeControls(m_hWnd,m_Configs.bDebug?TRUE:FALSE,this->IDD,false);

	//画图
	double XValues[1000];
	double YValues[1000];
	for (int i= 0;i<1000;i++)
	{
		XValues[i] = i;
		YValues[i] = 0;
	}
	CChartStandardAxis* pBottomAxis = m_ChartEq.CreateStandardAxis(CChartCtrl::BottomAxis); 
	pBottomAxis->SetMinMax(0, 1000); 
	pBottomAxis->GetLabel()->SetText(_T("CF"));
	CChartStandardAxis* pLeftAxis = m_ChartEq.CreateStandardAxis(CChartCtrl::LeftAxis);  
	pLeftAxis->SetMinMax(-15, 15);
	pLeftAxis->GetLabel()->SetText(_T("GAIN"));
	CChartLineSerie* pLineSerie = m_ChartEq.CreateLineSerie();
	pLineSerie->SetPoints(XValues,YValues,1000);  
	pLineSerie->SetColor(RGB(255,0,0)); 
	pLineSerie->SetWidth(pLineSerie->GetWidth()*2);

	m_ComChannum.AddString(_T("channel0"));
	m_ComChannum.AddString(_T("channel1"));
	m_ComChannum.SetCurSel(m_Configs.nEQChannel);
	InitUi(m_Configs.nEQChannel);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgEq::OnBnClickedButtonSave()
{
	// TODO: Add your control notification handler code here
	SaveConfig();
	InitChartCtrl();
	m_Configs.SaveToolSetting(_T(""));
	AfxMessageBox(_T("保存成功"));
}

void CDlgEq::SavePara(int nChannel)
{
	CString strValue;
	if (nChannel)
	{
		GetDlgItemText(IDC_EDIT_GAIN1,strValue);
		m_Configs.EqGainRight[0] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN2,strValue);
		m_Configs.EqGainRight[1] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN3,strValue);
		m_Configs.EqGainRight[2] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN4,strValue);
		m_Configs.EqGainRight[3] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN5,strValue);
		m_Configs.EqGainRight[4] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN6,strValue);
		m_Configs.EqGainRight[5] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN7,strValue);
		m_Configs.EqGainRight[6] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN8,strValue);
		m_Configs.EqGainRight[7] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN9,strValue);
		m_Configs.EqGainRight[8] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN10,strValue);
		m_Configs.EqGainRight[9] = cmNumString::StrToInt32(strValue);

		GetDlgItemText(IDC_EDIT_GF1,strValue);
		m_Configs.EqCFRight[0] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF2,strValue);
		m_Configs.EqCFRight[1] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF3,strValue);
		m_Configs.EqCFRight[2] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF4,strValue);
		m_Configs.EqCFRight[3] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF5,strValue);
		m_Configs.EqCFRight[4] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF6,strValue);
		m_Configs.EqCFRight[5] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF7,strValue);
		m_Configs.EqCFRight[6] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF8,strValue);
		m_Configs.EqCFRight[7] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF9,strValue);
		m_Configs.EqCFRight[8] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF10,strValue);
		m_Configs.EqCFRight[9] = cmNumString::StrToInt32(strValue);

		GetDlgItemText(IDC_EDIT_Q2,strValue);
		m_Configs.EqQRight[0] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q3,strValue);
		m_Configs.EqQRight[1] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q4,strValue);
		m_Configs.EqQRight[2] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q5,strValue);
		m_Configs.EqQRight[3] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q6,strValue);
		m_Configs.EqQRight[4] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q7,strValue);
		m_Configs.EqQRight[5] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q8,strValue);
		m_Configs.EqQRight[6] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q9,strValue);
		m_Configs.EqQRight[7] = cmNumString::StrToDouble(strValue);
	}
	else
	{
		GetDlgItemText(IDC_EDIT_GAIN1,strValue);
		m_Configs.EqGainLeft[0] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN2,strValue);
		m_Configs.EqGainLeft[1] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN3,strValue);
		m_Configs.EqGainLeft[2] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN4,strValue);
		m_Configs.EqGainLeft[3] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN5,strValue);
		m_Configs.EqGainLeft[4] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN6,strValue);
		m_Configs.EqGainLeft[5] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN7,strValue);
		m_Configs.EqGainLeft[6] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN8,strValue);
		m_Configs.EqGainLeft[7] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN9,strValue);
		m_Configs.EqGainLeft[8] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN10,strValue);
		m_Configs.EqGainLeft[9] = cmNumString::StrToInt32(strValue);

		GetDlgItemText(IDC_EDIT_GF1,strValue);
		m_Configs.EqCFLeft[0] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF2,strValue);
		m_Configs.EqCFLeft[1] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF3,strValue);
		m_Configs.EqCFLeft[2] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF4,strValue);
		m_Configs.EqCFLeft[3] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF5,strValue);
		m_Configs.EqCFLeft[4] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF6,strValue);
		m_Configs.EqCFLeft[5] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF7,strValue);
		m_Configs.EqCFLeft[6] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF8,strValue);
		m_Configs.EqCFLeft[7] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF9,strValue);
		m_Configs.EqCFLeft[8] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF10,strValue);
		m_Configs.EqCFLeft[9] = cmNumString::StrToInt32(strValue);

		GetDlgItemText(IDC_EDIT_Q2,strValue);
		m_Configs.EqQLeft[0] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q3,strValue);
		m_Configs.EqQLeft[1] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q4,strValue);
		m_Configs.EqQLeft[2] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q5,strValue);
		m_Configs.EqQLeft[3] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q6,strValue);
		m_Configs.EqQLeft[4] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q7,strValue);
		m_Configs.EqQLeft[5] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q8,strValue);
		m_Configs.EqQLeft[6] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q9,strValue);
		m_Configs.EqQLeft[7] = cmNumString::StrToDouble(strValue);
	}
}

void CDlgEq::SaveConfig()
{
	if (m_Configs.bEQLink)
	{
		SavePara(0);
		SavePara(1);
	}
	else
	{
		SavePara(m_Configs.nEQChannel);
	}
}

void CDlgEq::InitUi(int nChannel)
{
	GetDlgItem(IDC_BUTTON_SAVE)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CANCEL)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_Q1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Q10)->EnableWindow(FALSE);
	if (m_Configs.bEQLink)
	{
		((CButton*)GetDlgItem(IDC_CHECK_LINK))->SetCheck(BST_CHECKED);
		GetDlgItem(IDC_COMBO_CHANNUM)->EnableWindow(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECK_LINK))->SetCheck(BST_UNCHECKED);
		GetDlgItem(IDC_COMBO_CHANNUM)->EnableWindow(TRUE);
	}
	if (nChannel)
	{
		SetDlgItemText(IDC_EDIT_GAIN1,cmNumString::NumToStr(m_Configs.EqGainRight[0],10));
		SetDlgItemText(IDC_EDIT_GAIN2,cmNumString::NumToStr(m_Configs.EqGainRight[1],10));
		SetDlgItemText(IDC_EDIT_GAIN3,cmNumString::NumToStr(m_Configs.EqGainRight[2],10));
		SetDlgItemText(IDC_EDIT_GAIN4,cmNumString::NumToStr(m_Configs.EqGainRight[3],10));
		SetDlgItemText(IDC_EDIT_GAIN5,cmNumString::NumToStr(m_Configs.EqGainRight[4],10));
		SetDlgItemText(IDC_EDIT_GAIN6,cmNumString::NumToStr(m_Configs.EqGainRight[5],10));
		SetDlgItemText(IDC_EDIT_GAIN7,cmNumString::NumToStr(m_Configs.EqGainRight[6],10));
		SetDlgItemText(IDC_EDIT_GAIN8,cmNumString::NumToStr(m_Configs.EqGainRight[7],10));
		SetDlgItemText(IDC_EDIT_GAIN9,cmNumString::NumToStr(m_Configs.EqGainRight[8],10));
		SetDlgItemText(IDC_EDIT_GAIN10,cmNumString::NumToStr(m_Configs.EqGainRight[9],10));

		SetDlgItemText(IDC_EDIT_GF1,cmNumString::NumToStr(m_Configs.EqCFRight[0],10));
		SetDlgItemText(IDC_EDIT_GF2,cmNumString::NumToStr(m_Configs.EqCFRight[1],10));
		SetDlgItemText(IDC_EDIT_GF3,cmNumString::NumToStr(m_Configs.EqCFRight[2],10));
		SetDlgItemText(IDC_EDIT_GF4,cmNumString::NumToStr(m_Configs.EqCFRight[3],10));
		SetDlgItemText(IDC_EDIT_GF5,cmNumString::NumToStr(m_Configs.EqCFRight[4],10));
		SetDlgItemText(IDC_EDIT_GF6,cmNumString::NumToStr(m_Configs.EqCFRight[5],10));
		SetDlgItemText(IDC_EDIT_GF7,cmNumString::NumToStr(m_Configs.EqCFRight[6],10));
		SetDlgItemText(IDC_EDIT_GF8,cmNumString::NumToStr(m_Configs.EqCFRight[7],10));
		SetDlgItemText(IDC_EDIT_GF9,cmNumString::NumToStr(m_Configs.EqCFRight[8],10));
		SetDlgItemText(IDC_EDIT_GF10,cmNumString::NumToStr(m_Configs.EqCFRight[9],10));

		SetDlgItemText(IDC_EDIT_Q2,cmNumString::NumToStr(m_Configs.EqQRight[0]));
		SetDlgItemText(IDC_EDIT_Q3,cmNumString::NumToStr(m_Configs.EqQRight[1]));
		SetDlgItemText(IDC_EDIT_Q4,cmNumString::NumToStr(m_Configs.EqQRight[2]));
		SetDlgItemText(IDC_EDIT_Q5,cmNumString::NumToStr(m_Configs.EqQRight[3]));
		SetDlgItemText(IDC_EDIT_Q6,cmNumString::NumToStr(m_Configs.EqQRight[4]));
		SetDlgItemText(IDC_EDIT_Q7,cmNumString::NumToStr(m_Configs.EqQRight[5]));
		SetDlgItemText(IDC_EDIT_Q8,cmNumString::NumToStr(m_Configs.EqQRight[6]));
		SetDlgItemText(IDC_EDIT_Q9,cmNumString::NumToStr(m_Configs.EqQRight[7]));
	}
	else
	{
		SetDlgItemText(IDC_EDIT_GAIN1,cmNumString::NumToStr(m_Configs.EqGainLeft[0],10));
		SetDlgItemText(IDC_EDIT_GAIN2,cmNumString::NumToStr(m_Configs.EqGainLeft[1],10));
		SetDlgItemText(IDC_EDIT_GAIN3,cmNumString::NumToStr(m_Configs.EqGainLeft[2],10));
		SetDlgItemText(IDC_EDIT_GAIN4,cmNumString::NumToStr(m_Configs.EqGainLeft[3],10));
		SetDlgItemText(IDC_EDIT_GAIN5,cmNumString::NumToStr(m_Configs.EqGainLeft[4],10));
		SetDlgItemText(IDC_EDIT_GAIN6,cmNumString::NumToStr(m_Configs.EqGainLeft[5],10));
		SetDlgItemText(IDC_EDIT_GAIN7,cmNumString::NumToStr(m_Configs.EqGainLeft[6],10));
		SetDlgItemText(IDC_EDIT_GAIN8,cmNumString::NumToStr(m_Configs.EqGainLeft[7],10));
		SetDlgItemText(IDC_EDIT_GAIN9,cmNumString::NumToStr(m_Configs.EqGainLeft[8],10));
		SetDlgItemText(IDC_EDIT_GAIN10,cmNumString::NumToStr(m_Configs.EqGainLeft[9],10));

		SetDlgItemText(IDC_EDIT_GF1,cmNumString::NumToStr(m_Configs.EqCFLeft[0],10));
		SetDlgItemText(IDC_EDIT_GF2,cmNumString::NumToStr(m_Configs.EqCFLeft[1],10));
		SetDlgItemText(IDC_EDIT_GF3,cmNumString::NumToStr(m_Configs.EqCFLeft[2],10));
		SetDlgItemText(IDC_EDIT_GF4,cmNumString::NumToStr(m_Configs.EqCFLeft[3],10));
		SetDlgItemText(IDC_EDIT_GF5,cmNumString::NumToStr(m_Configs.EqCFLeft[4],10));
		SetDlgItemText(IDC_EDIT_GF6,cmNumString::NumToStr(m_Configs.EqCFLeft[5],10));
		SetDlgItemText(IDC_EDIT_GF7,cmNumString::NumToStr(m_Configs.EqCFLeft[6],10));
		SetDlgItemText(IDC_EDIT_GF8,cmNumString::NumToStr(m_Configs.EqCFLeft[7],10));
		SetDlgItemText(IDC_EDIT_GF9,cmNumString::NumToStr(m_Configs.EqCFLeft[8],10));
		SetDlgItemText(IDC_EDIT_GF10,cmNumString::NumToStr(m_Configs.EqCFLeft[9],10));

		SetDlgItemText(IDC_EDIT_Q2,cmNumString::NumToStr(m_Configs.EqQLeft[0]));
		SetDlgItemText(IDC_EDIT_Q3,cmNumString::NumToStr(m_Configs.EqQLeft[1]));
		SetDlgItemText(IDC_EDIT_Q4,cmNumString::NumToStr(m_Configs.EqQLeft[2]));
		SetDlgItemText(IDC_EDIT_Q5,cmNumString::NumToStr(m_Configs.EqQLeft[3]));
		SetDlgItemText(IDC_EDIT_Q6,cmNumString::NumToStr(m_Configs.EqQLeft[4]));
		SetDlgItemText(IDC_EDIT_Q7,cmNumString::NumToStr(m_Configs.EqQLeft[5]));
		SetDlgItemText(IDC_EDIT_Q8,cmNumString::NumToStr(m_Configs.EqQLeft[6]));
		SetDlgItemText(IDC_EDIT_Q9,cmNumString::NumToStr(m_Configs.EqQLeft[7]));
	}

	InitChartCtrl();
}

void CDlgEq::CheckGain(int ID)
{
	CString strValue;
	int nGain;
	GetDlgItemText(ID,strValue);
	nGain = cmNumString::StrToInt32(strValue);
	if ((nGain<-12) || (nGain>12))
	{
		MessageBox(_T("数值不在-12~12范围!"), _T("错误"), MB_OK);
		GetDlgItem(ID)->SetFocus();
	}

}
void CDlgEq::CheckQ(int ID)
{
	CString strValue;
	float nGain;
	GetDlgItemText(ID,strValue);
	nGain = cmNumString::StrToDouble(strValue);
	if (nGain<=0.5)
	{
		MessageBox(_T("数值必须大于0.5!"), _T("错误"), MB_OK);
		GetDlgItem(ID)->SetFocus();
	}

}
void CDlgEq::CheckCf(int ID)
{
	CString strValue;
	int nGain;
	GetDlgItemText(ID,strValue);
	nGain = cmNumString::StrToInt64(strValue);
	if ((nGain<=0) || (nGain>=m_Configs.swFs/2))
	{
		MessageBox(_T("调节范围：0 < CF < 采样率/2",m_Configs.swFs/2), _T("错误"), MB_OK);
		GetDlgItem(ID)->SetFocus();
	}

}
void CDlgEq::OnEnKillfocusEditGain1()
{
	// TODO: Add your control notification handler code here
	CheckGain(IDC_EDIT_GAIN1);
}

void CDlgEq::OnEnKillfocusEditGain2()
{
	// TODO: Add your control notification handler code here
	CheckGain(IDC_EDIT_GAIN2);
}

void CDlgEq::OnEnKillfocusEditGain3()
{
	// TODO: Add your control notification handler code here
	CheckGain(IDC_EDIT_GAIN3);
}

void CDlgEq::OnEnKillfocusEditGain4()
{
	// TODO: Add your control notification handler code here
	CheckGain(IDC_EDIT_GAIN4);
}

void CDlgEq::OnEnKillfocusEditGain5()
{
	// TODO: Add your control notification handler code here
	CheckGain(IDC_EDIT_GAIN5);
}

void CDlgEq::OnEnKillfocusEditGain6()
{
	// TODO: Add your control notification handler code here
	CheckGain(IDC_EDIT_GAIN6);
}

void CDlgEq::OnEnKillfocusEditGain7()
{
	// TODO: Add your control notification handler code here
	CheckGain(IDC_EDIT_GAIN7);
}

void CDlgEq::OnEnKillfocusEditGain8()
{
	// TODO: Add your control notification handler code here
	CheckGain(IDC_EDIT_GAIN8);
}

void CDlgEq::OnEnKillfocusEditGf1()
{
	// TODO: Add your control notification handler code here
	CheckCf(IDC_EDIT_GF1);
}

void CDlgEq::OnEnKillfocusEditGf2()
{
	// TODO: Add your control notification handler code here
	CheckCf(IDC_EDIT_GF2);
}

void CDlgEq::OnEnKillfocusEditGf3()
{
	// TODO: Add your control notification handler code here
	CheckCf(IDC_EDIT_GF3);
}

void CDlgEq::OnEnKillfocusEditGf4()
{
	// TODO: Add your control notification handler code here
	CheckCf(IDC_EDIT_GF4);
}

void CDlgEq::OnEnKillfocusEditGf5()
{
	// TODO: Add your control notification handler code here
	CheckCf(IDC_EDIT_GF5);
}

void CDlgEq::OnEnKillfocusEditGf6()
{
	// TODO: Add your control notification handler code here
	CheckCf(IDC_EDIT_GF6);
}

void CDlgEq::OnEnKillfocusEditGf7()
{
	// TODO: Add your control notification handler code here
	CheckCf(IDC_EDIT_GF7);
}

void CDlgEq::OnEnKillfocusEditGf8()
{
	// TODO: Add your control notification handler code here
	CheckCf(IDC_EDIT_GF8);
}

void CDlgEq::OnEnKillfocusEditQ1()
{
	// TODO: Add your control notification handler code here
	CheckQ(IDC_EDIT_Q1);
}

void CDlgEq::OnEnKillfocusEditQ2()
{
	// TODO: Add your control notification handler code here
	CheckQ(IDC_EDIT_Q2);
}

void CDlgEq::OnEnKillfocusEditQ3()
{
	// TODO: Add your control notification handler code here
	CheckQ(IDC_EDIT_Q3);
}

void CDlgEq::OnEnKillfocusEditQ4()
{
	// TODO: Add your control notification handler code here
	CheckQ(IDC_EDIT_Q4);
}

void CDlgEq::OnEnSetfocusEditQ5()
{
	// TODO: Add your control notification handler code here
	CheckQ(IDC_EDIT_Q5);
}

void CDlgEq::OnEnKillfocusEditQ6()
{
	// TODO: Add your control notification handler code here
	CheckQ(IDC_EDIT_Q6);
}

void CDlgEq::OnEnKillfocusEditQ7()
{
	// TODO: Add your control notification handler code here
	CheckQ(IDC_EDIT_Q7);
}

void CDlgEq::OnEnKillfocusEditQ8()
{
	// TODO: Add your control notification handler code here
	CheckQ(IDC_EDIT_Q8);
}

void CDlgEq::OnCbnSelchangeComboChannum()
{
	// TODO: Add your control notification handler code here
	m_Configs.nEQChannel = m_ComChannum.GetCurSel();
	InitUi(m_Configs.nEQChannel);
	m_Configs.SaveToolSetting(_T(""));
}

void CDlgEq::OnBnClickedCheckLink()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_COMBO_CHANNUM)->EnableWindow(m_Configs.bEQLink);
	m_Configs.bEQLink = !m_Configs.bEQLink;
	m_Configs.SaveToolSetting(_T(""));
}
