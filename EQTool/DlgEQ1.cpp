// DlgEQ1.cpp : implementation file
//

#include "stdafx.h"
#include "EQTool.h"
#include "DlgEQ1.h"


// CDlgEQ1 dialog

IMPLEMENT_DYNAMIC(CDlgEQ1, CDialog)

CDlgEQ1::CDlgEQ1(CIniSettingBase &Config,CIniLocalLan &LocalLang,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEQ1::IDD, pParent),m_Configs(Config),m_LocalLang(LocalLang)
{

}

CDlgEQ1::~CDlgEQ1()
{
}

void CDlgEQ1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ChartCtrl_EQ, m_ChartEq);
	DDX_Control(pDX, IDC_COMBO_CHANNUM, m_ComChannum);
}


BEGIN_MESSAGE_MAP(CDlgEQ1, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNUM, &CDlgEQ1::OnCbnSelchangeComboChannum)
	ON_BN_CLICKED(IDC_CHECK_LINK, &CDlgEQ1::OnBnClickedCheckLink)
END_MESSAGE_MAP()


// CDlgEQ1 message handlers
void CDlgEQ1::InitChartCtrl()
{
	CChartLineSerie* pLineSerie = m_ChartEq.CreateLineSerie();

	//signed short int  shwChaNum;
	signed int swCurveLen;
	float  fMinFreq;
	float  afPara[PARANUM] = {0.0f};
	float  afCurve1[2000];
	float  afCurve2[2000];


	/* 1.1 左右声道公共参数 */
	afPara[PARA_CHANUM]    = m_Configs.shwChaNum;
	afPara[PARA_CHANUM]    =1;
	afPara[PARA_EQ8SWTCH]   = m_Configs.bEQSwtch1;
	afPara[PARA_FS]        = m_Configs.swFs;

	/* 1.2 左声道参数 */
	/* 1.2.1 左声道增益 */
	afPara[PARA_L_GAIN2] = m_Configs.ScrGainL1;
	/* 1.2.2 左声道EQ参数 */
	//Gain
	afPara[PARA_LEQ8_GBASS]    = m_Configs.EqGainLeft1[0];                        
	afPara[PARA_LEQ8_GPEAK1]   = m_Configs.EqGainLeft1[1];                       
	afPara[PARA_LEQ8_GPEAK1+1] = m_Configs.EqGainLeft1[2];                       
	afPara[PARA_LEQ8_GPEAK1+2] = m_Configs.EqGainLeft1[3];                       
	afPara[PARA_LEQ8_GPEAK1+3] = m_Configs.EqGainLeft1[4];                        
	afPara[PARA_LEQ8_GPEAK1+4] = m_Configs.EqGainLeft1[5];                       
	afPara[PARA_LEQ8_GPEAK1+5] = m_Configs.EqGainLeft1[6];                                               
	afPara[PARA_LEQ8_GPEAK1]  = m_Configs.EqGainLeft1[7]; 
	//CF
	afPara[PARA_LEQ8_CFBASS]    = m_Configs.EqCFLeft1[0];                        
	afPara[PARA_LEQ8_CFPEAK1]   = m_Configs.EqCFLeft1[1];                       
	afPara[PARA_LEQ8_CFPEAK1+1] = m_Configs.EqCFLeft1[2];                       
	afPara[PARA_LEQ8_CFPEAK1+2] = m_Configs.EqCFLeft1[3];                       
	afPara[PARA_LEQ8_CFPEAK1+3] = m_Configs.EqCFLeft1[4];                        
	afPara[PARA_LEQ8_CFPEAK1+4] = m_Configs.EqCFLeft1[5];                       
	afPara[PARA_LEQ8_CFPEAK1+5] = m_Configs.EqCFLeft1[6];                                             
	afPara[PARA_LEQ8_CFTREBLE]  = m_Configs.EqCFLeft1[7];
	//Q
	afPara[PARA_LEQ8_Q1]   = m_Configs.EqQLeft1[0];                        
	afPara[PARA_LEQ8_Q1+1] = m_Configs.EqQLeft1[1];                       
	afPara[PARA_LEQ8_Q1+2] = m_Configs.EqQLeft1[2];                       
	afPara[PARA_LEQ8_Q1+3] = m_Configs.EqQLeft1[3]; 
	afPara[PARA_LEQ8_Q1+4] = m_Configs.EqQLeft1[4]; 
	afPara[PARA_LEQ8_Q1+5] = m_Configs.EqQLeft1[5]; 

	/* 1.3 右声道参数 */
	if (m_Configs.nEQ1Channel == 1)
	{
		afPara[PARA_R_GAIN2] = m_Configs.ScrGainR1;
		//Gain
		afPara[PARA_REQ8_GBASS]    = m_Configs.EqGainRight1[0];                        
		afPara[PARA_REQ8_GPEAK1]   = m_Configs.EqGainRight1[1];                       
		afPara[PARA_REQ8_GPEAK1+1] = m_Configs.EqGainRight1[2];                       
		afPara[PARA_REQ8_GPEAK1+2] = m_Configs.EqGainRight1[3];                       
		afPara[PARA_REQ8_GPEAK1+3] = m_Configs.EqGainRight1[4];                        
		afPara[PARA_REQ8_GPEAK1+4] = m_Configs.EqGainRight1[5];                       
		afPara[PARA_REQ8_GPEAK1+5] = m_Configs.EqGainRight1[6];                                             
		afPara[PARA_REQ8_GTREBLE]  = m_Configs.EqGainRight1[7]; 
		//CF
		afPara[PARA_REQ8_CFBASS]    = m_Configs.EqCFRight1[0];                        
		afPara[PARA_REQ8_CFPEAK1]   = m_Configs.EqCFRight1[1];                       
		afPara[PARA_REQ8_CFPEAK1+1] = m_Configs.EqCFRight1[2];                       
		afPara[PARA_REQ8_CFPEAK1+2] = m_Configs.EqCFRight1[3];                       
		afPara[PARA_REQ8_CFPEAK1+3] = m_Configs.EqCFRight1[4];                        
		afPara[PARA_REQ8_CFPEAK1+4] = m_Configs.EqCFRight1[5];                       
		afPara[PARA_REQ8_CFPEAK1+5] = m_Configs.EqCFRight1[6];                                              
		afPara[PARA_REQ8_CFTREBLE]  = m_Configs.EqCFRight1[7];
		//Q
		afPara[PARA_REQ8_Q1]   = m_Configs.EqQRight1[0];                        
		afPara[PARA_REQ8_Q1+1] = m_Configs.EqQRight1[1];                       
		afPara[PARA_REQ8_Q1+2] = m_Configs.EqQRight1[2];                       
		afPara[PARA_REQ8_Q1+3] = m_Configs.EqQRight1[3]; 
		afPara[PARA_REQ8_Q1+4] = m_Configs.EqQRight1[4]; 
		afPara[PARA_REQ8_Q1+5] = m_Configs.EqQRight1[5]; 
		afPara[PARA_REQ8_Q1+6] = m_Configs.EqQRight1[6]; 
	}

	/* 1. 设计EQ */
	fMinFreq = 20;
	swCurveLen = 1000;
	EQ8Product lvEQProduct = (EQ8Product)GetProcAddress(AudioHnd, "EQ8Product");
	lvEQProduct(&(afPara[PARA_LEQ8_GBASS]), afCurve1, m_Configs.swFs, fMinFreq, swCurveLen);

	/* 1.2 右声道EQ */
	if (m_Configs.nEQ1Channel == 1)
	{
		lvEQProduct(&(afPara[PARA_REQ8_GBASS]), afCurve1, m_Configs.swFs, fMinFreq, swCurveLen);

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


BOOL CDlgEQ1::OnInitDialog()
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
	m_ComChannum.SetCurSel(m_Configs.nEQ1Channel);
	InitUi(m_Configs.nEQ1Channel);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgEQ1::SavePara(int nChannel)
{
	CString strValue;
	if (nChannel)
	{
		GetDlgItemText(IDC_EDIT_GAIN1,strValue);
		m_Configs.EqGainRight1[0] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN2,strValue);
		m_Configs.EqGainRight1[1] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN3,strValue);
		m_Configs.EqGainRight1[2] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN4,strValue);
		m_Configs.EqGainRight1[3] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN5,strValue);
		m_Configs.EqGainRight1[4] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN6,strValue);
		m_Configs.EqGainRight1[5] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN7,strValue);
		m_Configs.EqGainRight1[6] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN8,strValue);
		m_Configs.EqGainRight1[7] = cmNumString::StrToInt32(strValue);

		GetDlgItemText(IDC_EDIT_GF1,strValue);
		m_Configs.EqCFRight1[0] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF2,strValue);
		m_Configs.EqCFRight1[1] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF3,strValue);
		m_Configs.EqCFRight1[2] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF4,strValue);
		m_Configs.EqCFRight1[3] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF5,strValue);
		m_Configs.EqCFRight1[4] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF6,strValue);
		m_Configs.EqCFRight1[5] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF7,strValue);
		m_Configs.EqCFRight1[6] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF8,strValue);
		m_Configs.EqCFRight1[7] = cmNumString::StrToInt32(strValue);

		GetDlgItemText(IDC_EDIT_Q2,strValue);
		m_Configs.EqQRight1[0] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q3,strValue);
		m_Configs.EqQRight1[1] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q4,strValue);
		m_Configs.EqQRight1[2] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q5,strValue);
		m_Configs.EqQRight1[3] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q6,strValue);
		m_Configs.EqQRight1[4] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q7,strValue);
		m_Configs.EqQRight1[5] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q8,strValue);
		m_Configs.EqQRight1[6] = cmNumString::StrToDouble(strValue);
	}
	else
	{
		GetDlgItemText(IDC_EDIT_GAIN1,strValue);
		m_Configs.EqGainLeft1[0] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN2,strValue);
		m_Configs.EqGainLeft1[1] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN3,strValue);
		m_Configs.EqGainLeft1[2] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN4,strValue);
		m_Configs.EqGainLeft1[3] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN5,strValue);
		m_Configs.EqGainLeft1[4] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN6,strValue);
		m_Configs.EqGainLeft1[5] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN7,strValue);
		m_Configs.EqGainLeft1[6] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GAIN8,strValue);
		m_Configs.EqGainLeft1[7] = cmNumString::StrToInt32(strValue);

		GetDlgItemText(IDC_EDIT_GF1,strValue);
		m_Configs.EqCFLeft1[0] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF2,strValue);
		m_Configs.EqCFLeft1[1] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF3,strValue);
		m_Configs.EqCFLeft1[2] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF4,strValue);
		m_Configs.EqCFLeft1[3] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF5,strValue);
		m_Configs.EqCFLeft1[4] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF6,strValue);
		m_Configs.EqCFLeft1[5] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF7,strValue);
		m_Configs.EqCFLeft1[6] = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_GF8,strValue);
		m_Configs.EqCFLeft1[7] = cmNumString::StrToInt32(strValue);

		GetDlgItemText(IDC_EDIT_Q2,strValue);
		m_Configs.EqQLeft1[0] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q3,strValue);
		m_Configs.EqQLeft1[1] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q4,strValue);
		m_Configs.EqQLeft1[2] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q5,strValue);
		m_Configs.EqQLeft1[3] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q6,strValue);
		m_Configs.EqQLeft1[4] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q7,strValue);
		m_Configs.EqQLeft1[5] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_Q8,strValue);
		m_Configs.EqQLeft1[6] = cmNumString::StrToDouble(strValue);
	}
}

void CDlgEQ1::SaveConfig()
{
	if (m_Configs.bEQLink1)
	{
		SavePara(0);
		SavePara(1);
	}
	else
	{
		SavePara(m_Configs.nEQ1Channel);
	}
}

void CDlgEQ1::InitUi(int nChannel)
{
	GetDlgItem(IDC_BUTTON_SAVE)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CANCEL)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_Q1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Q8)->EnableWindow(FALSE);
	if (m_Configs.bEQLink1)
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
		SetDlgItemText(IDC_EDIT_GAIN1,cmNumString::NumToStr(m_Configs.EqGainRight1[0],10));
		SetDlgItemText(IDC_EDIT_GAIN2,cmNumString::NumToStr(m_Configs.EqGainRight1[1],10));
		SetDlgItemText(IDC_EDIT_GAIN3,cmNumString::NumToStr(m_Configs.EqGainRight1[2],10));
		SetDlgItemText(IDC_EDIT_GAIN4,cmNumString::NumToStr(m_Configs.EqGainRight1[3],10));
		SetDlgItemText(IDC_EDIT_GAIN5,cmNumString::NumToStr(m_Configs.EqGainRight1[4],10));
		SetDlgItemText(IDC_EDIT_GAIN6,cmNumString::NumToStr(m_Configs.EqGainRight1[5],10));
		SetDlgItemText(IDC_EDIT_GAIN7,cmNumString::NumToStr(m_Configs.EqGainRight1[6],10));
		SetDlgItemText(IDC_EDIT_GAIN8,cmNumString::NumToStr(m_Configs.EqGainRight1[7],10));

		SetDlgItemText(IDC_EDIT_GF1,cmNumString::NumToStr(m_Configs.EqCFRight1[0],10));
		SetDlgItemText(IDC_EDIT_GF2,cmNumString::NumToStr(m_Configs.EqCFRight1[1],10));
		SetDlgItemText(IDC_EDIT_GF3,cmNumString::NumToStr(m_Configs.EqCFRight1[2],10));
		SetDlgItemText(IDC_EDIT_GF4,cmNumString::NumToStr(m_Configs.EqCFRight1[3],10));
		SetDlgItemText(IDC_EDIT_GF5,cmNumString::NumToStr(m_Configs.EqCFRight1[4],10));
		SetDlgItemText(IDC_EDIT_GF6,cmNumString::NumToStr(m_Configs.EqCFRight1[5],10));
		SetDlgItemText(IDC_EDIT_GF7,cmNumString::NumToStr(m_Configs.EqCFRight1[6],10));
		SetDlgItemText(IDC_EDIT_GF8,cmNumString::NumToStr(m_Configs.EqCFRight1[7],10));

		SetDlgItemText(IDC_EDIT_Q2,cmNumString::NumToStr(m_Configs.EqQRight1[0]));
		SetDlgItemText(IDC_EDIT_Q3,cmNumString::NumToStr(m_Configs.EqQRight1[1]));
		SetDlgItemText(IDC_EDIT_Q4,cmNumString::NumToStr(m_Configs.EqQRight1[2]));
		SetDlgItemText(IDC_EDIT_Q5,cmNumString::NumToStr(m_Configs.EqQRight1[3]));
		SetDlgItemText(IDC_EDIT_Q6,cmNumString::NumToStr(m_Configs.EqQRight1[4]));
		SetDlgItemText(IDC_EDIT_Q7,cmNumString::NumToStr(m_Configs.EqQRight1[5]));
		SetDlgItemText(IDC_EDIT_Q8,cmNumString::NumToStr(m_Configs.EqQRight1[6]));
	}
	else
	{
		SetDlgItemText(IDC_EDIT_GAIN1,cmNumString::NumToStr(m_Configs.EqGainLeft1[0],10));
		SetDlgItemText(IDC_EDIT_GAIN2,cmNumString::NumToStr(m_Configs.EqGainLeft1[1],10));
		SetDlgItemText(IDC_EDIT_GAIN3,cmNumString::NumToStr(m_Configs.EqGainLeft1[2],10));
		SetDlgItemText(IDC_EDIT_GAIN4,cmNumString::NumToStr(m_Configs.EqGainLeft1[3],10));
		SetDlgItemText(IDC_EDIT_GAIN5,cmNumString::NumToStr(m_Configs.EqGainLeft1[4],10));
		SetDlgItemText(IDC_EDIT_GAIN6,cmNumString::NumToStr(m_Configs.EqGainLeft1[5],10));
		SetDlgItemText(IDC_EDIT_GAIN7,cmNumString::NumToStr(m_Configs.EqGainLeft1[6],10));
		SetDlgItemText(IDC_EDIT_GAIN8,cmNumString::NumToStr(m_Configs.EqGainLeft1[7],10));

		SetDlgItemText(IDC_EDIT_GF1,cmNumString::NumToStr(m_Configs.EqCFLeft1[0],10));
		SetDlgItemText(IDC_EDIT_GF2,cmNumString::NumToStr(m_Configs.EqCFLeft1[1],10));
		SetDlgItemText(IDC_EDIT_GF3,cmNumString::NumToStr(m_Configs.EqCFLeft1[2],10));
		SetDlgItemText(IDC_EDIT_GF4,cmNumString::NumToStr(m_Configs.EqCFLeft1[3],10));
		SetDlgItemText(IDC_EDIT_GF5,cmNumString::NumToStr(m_Configs.EqCFLeft1[4],10));
		SetDlgItemText(IDC_EDIT_GF6,cmNumString::NumToStr(m_Configs.EqCFLeft1[5],10));
		SetDlgItemText(IDC_EDIT_GF7,cmNumString::NumToStr(m_Configs.EqCFLeft1[6],10));
		SetDlgItemText(IDC_EDIT_GF8,cmNumString::NumToStr(m_Configs.EqCFLeft1[7],10));

		SetDlgItemText(IDC_EDIT_Q2,cmNumString::NumToStr(m_Configs.EqQLeft1[0]));
		SetDlgItemText(IDC_EDIT_Q3,cmNumString::NumToStr(m_Configs.EqQLeft1[1]));
		SetDlgItemText(IDC_EDIT_Q4,cmNumString::NumToStr(m_Configs.EqQLeft1[2]));
		SetDlgItemText(IDC_EDIT_Q5,cmNumString::NumToStr(m_Configs.EqQLeft1[3]));
		SetDlgItemText(IDC_EDIT_Q6,cmNumString::NumToStr(m_Configs.EqQLeft1[4]));
		SetDlgItemText(IDC_EDIT_Q7,cmNumString::NumToStr(m_Configs.EqQLeft1[5]));
	}

	InitChartCtrl();
}

void CDlgEQ1::CheckGain(int ID)
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
void CDlgEQ1::CheckQ(int ID)
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
void CDlgEQ1::CheckCf(int ID)
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
void CDlgEQ1::OnCbnSelchangeComboChannum()
{
	// TODO: Add your control notification handler code here
	m_Configs.nEQ1Channel = m_ComChannum.GetCurSel();
	InitUi(m_Configs.nEQ1Channel);
	m_Configs.SaveToolSetting(_T(""));
}

void CDlgEQ1::OnBnClickedCheckLink()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_COMBO_CHANNUM)->EnableWindow(m_Configs.bEQLink1);
	m_Configs.bEQLink1 = !m_Configs.bEQLink1;
	m_Configs.SaveToolSetting(_T(""));
}
