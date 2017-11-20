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
}


BEGIN_MESSAGE_MAP(CDlgEq, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgEq::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CDlgEq message handlers
void CDlgEq::InitChartCtrl()
{
	CChartLineSerie* pLineSerie = m_ChartEq.CreateLineSerie();

	//signed short int  shwChaNum;
	signed int swCurveLen;
	float  fMinFreq;
	float  afPara[PARANUM];
	float  afCurve1[3000];
	float  afCurve2[3000];


	/* 1.1 左右声道公共参数 */
	afPara[PARA_CHANUM]    = m_Configs.shwChaNum;
	afPara[PARA_EQSWTCH]   = m_Configs.bEQSwtch;
	afPara[PARA_DRCSWTCH]  = m_Configs.bDrcSwtch;
	afPara[PARA_FS]        = m_Configs.swFs;

	/* 1.2 左声道参数 */
	/* 1.2.1 左声道增益 */
	afPara[PARA_L_GAIN] = m_Configs.ScrGainL;
	/* 1.2.2 左声道EQ参数 */
	//Gain
	afPara[PARA_LEQ_GBASS]    = m_Configs.EqGainLeft[0];                        
	afPara[PARA_LEQ_GPEAK1]   = m_Configs.EqGainLeft[1];                       
	afPara[PARA_LEQ_GPEAK1+1] = m_Configs.EqGainLeft[2];                       
	afPara[PARA_LEQ_GPEAK1+2] = m_Configs.EqGainLeft[3];                       
	afPara[PARA_LEQ_GPEAK1+3] = m_Configs.EqGainLeft[4];                        
	afPara[PARA_LEQ_GPEAK1+4] = m_Configs.EqGainLeft[5];                       
	afPara[PARA_LEQ_GPEAK1+5] = m_Configs.EqGainLeft[6];                        
	afPara[PARA_LEQ_GPEAK1+6] = m_Configs.EqGainLeft[7];                       
	afPara[PARA_LEQ_GTREBLE]  = m_Configs.EqGainLeft[8]; 
	//CF
	afPara[PARA_LEQ_CFBASS]    = m_Configs.EqCFLeft[0];                        
	afPara[PARA_LEQ_CFPEAK1]   = m_Configs.EqCFLeft[1];                       
	afPara[PARA_LEQ_CFPEAK1+1] = m_Configs.EqCFLeft[2];                       
	afPara[PARA_LEQ_CFPEAK1+2] = m_Configs.EqCFLeft[3];                       
	afPara[PARA_LEQ_CFPEAK1+3] = m_Configs.EqCFLeft[4];                        
	afPara[PARA_LEQ_CFPEAK1+4] = m_Configs.EqCFLeft[5];                       
	afPara[PARA_LEQ_CFPEAK1+5] = m_Configs.EqCFLeft[6];                        
	afPara[PARA_LEQ_CFPEAK1+6] = m_Configs.EqCFLeft[7];                      
	afPara[PARA_LEQ_CFTREBLE]  = m_Configs.EqCFLeft[8];
	//Q
	afPara[PARA_LEQ_Q1]   = m_Configs.EqQLeft[0];                        
	afPara[PARA_LEQ_Q1+1] = m_Configs.EqQLeft[1];                       
	afPara[PARA_LEQ_Q1+2] = m_Configs.EqQLeft[2];                       
	afPara[PARA_LEQ_Q1+3] = m_Configs.EqQLeft[3]; 
	afPara[PARA_LEQ_Q1+4] = m_Configs.EqQLeft[4]; 
	afPara[PARA_LEQ_Q1+5] = m_Configs.EqQLeft[5]; 
	afPara[PARA_LEQ_Q1+6] = m_Configs.EqQLeft[6]; 

	/* 1.3 右声道参数 */
	if (m_Configs.nChannel == 1)
	{
		afPara[PARA_R_GAIN] = m_Configs.ScrGainR;
		//Gain
		afPara[PARA_REQ_GBASS]    = m_Configs.EqGainRight[0];                        
		afPara[PARA_REQ_GPEAK1]   = m_Configs.EqGainRight[1];                       
		afPara[PARA_REQ_GPEAK1+1] = m_Configs.EqGainRight[2];                       
		afPara[PARA_REQ_GPEAK1+2] = m_Configs.EqGainRight[3];                       
		afPara[PARA_REQ_GPEAK1+3] = m_Configs.EqGainRight[4];                        
		afPara[PARA_REQ_GPEAK1+4] = m_Configs.EqGainRight[5];                       
		afPara[PARA_REQ_GPEAK1+5] = m_Configs.EqGainRight[6];                        
		afPara[PARA_REQ_GPEAK1+6] = m_Configs.EqGainRight[7];                       
		afPara[PARA_REQ_GTREBLE]  = m_Configs.EqGainRight[8]; 
		//CF
		afPara[PARA_REQ_CFBASS]    = m_Configs.EqCFRight[0];                        
		afPara[PARA_REQ_CFPEAK1]   = m_Configs.EqCFRight[1];                       
		afPara[PARA_REQ_CFPEAK1+1] = m_Configs.EqCFRight[2];                       
		afPara[PARA_REQ_CFPEAK1+2] = m_Configs.EqCFRight[3];                       
		afPara[PARA_REQ_CFPEAK1+3] = m_Configs.EqCFRight[4];                        
		afPara[PARA_REQ_CFPEAK1+4] = m_Configs.EqCFRight[5];                       
		afPara[PARA_REQ_CFPEAK1+5] = m_Configs.EqCFRight[6];                        
		afPara[PARA_REQ_CFPEAK1+6] = m_Configs.EqCFRight[7];                      
		afPara[PARA_REQ_CFTREBLE]  = m_Configs.EqCFRight[8];
		//Q
		afPara[PARA_REQ_Q1]   = m_Configs.EqQRight[0];                        
		afPara[PARA_REQ_Q1+1] = m_Configs.EqQRight[1];                       
		afPara[PARA_REQ_Q1+2] = m_Configs.EqQRight[2];                       
		afPara[PARA_REQ_Q1+3] = m_Configs.EqQRight[3]; 
		afPara[PARA_REQ_Q1+4] = m_Configs.EqQRight[4]; 
		afPara[PARA_REQ_Q1+5] = m_Configs.EqQRight[5]; 
		afPara[PARA_REQ_Q1+6] = m_Configs.EqQRight[6]; 
	}

	/* 1. 设计EQ */
	fMinFreq = 20;
	swCurveLen = 1000;
	EQProduct lvEQProduct = (EQProduct)GetProcAddress(AudioHnd, "EQProduct");
	lvEQProduct(&(afPara[PARA_LEQ_GBASS]), afCurve1, m_Configs.swFs, fMinFreq, swCurveLen);


	/* 1.2 右声道EQ */
	if (m_Configs.nChannel == 1)
	{
		// 设计
		//EQProduct(&(afPara[AUDIOPOST_REQ_SCRGBASS]), afCurve2, swFs, fMinFreq, swCurveLen);
		lvEQProduct(&(afPara[PARA_REQ_GBASS]), afCurve1, m_Configs.swFs, fMinFreq, swCurveLen);
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
	InitUi(m_Configs.nChannel);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgEq::OnBnClickedButtonSave()
{
	// TODO: Add your control notification handler code here
	if (m_Configs.bLink)
	{
		SavePara(0);
		SavePara(1);
	}
	else
	{
		SavePara(m_Configs.nChannel);
	}
	//发送命令给设备端，设置EQ参数
	if (0)
	{
		return ;
	}

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
		m_Configs.EqGainRight[0] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GAIN2,strValue);
		m_Configs.EqGainRight[1] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GAIN3,strValue);
		m_Configs.EqGainRight[2] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GAIN4,strValue);
		m_Configs.EqGainRight[3] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GAIN5,strValue);
		m_Configs.EqGainRight[4] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GAIN6,strValue);
		m_Configs.EqGainRight[5] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GAIN7,strValue);
		m_Configs.EqGainRight[6] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GAIN8,strValue);
		m_Configs.EqGainRight[7] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GAIN9,strValue);
		m_Configs.EqGainRight[8] = cmNumString::StrToDouble(strValue);

		GetDlgItemText(IDC_EDIT_GF1,strValue);
		m_Configs.EqCFRight[0] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GF2,strValue);
		m_Configs.EqCFRight[1] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GF3,strValue);
		m_Configs.EqCFRight[2] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GF4,strValue);
		m_Configs.EqCFRight[3] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GF5,strValue);
		m_Configs.EqCFRight[4] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GF6,strValue);
		m_Configs.EqCFRight[5] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GF7,strValue);
		m_Configs.EqCFRight[6] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GF8,strValue);
		m_Configs.EqCFRight[7] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GF9,strValue);
		m_Configs.EqCFRight[8] = cmNumString::StrToDouble(strValue);

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
	}
	else
	{
		GetDlgItemText(IDC_EDIT_GAIN1,strValue);
		m_Configs.EqGainLeft[0] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GAIN2,strValue);
		m_Configs.EqGainLeft[1] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GAIN3,strValue);
		m_Configs.EqGainLeft[2] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GAIN4,strValue);
		m_Configs.EqGainLeft[3] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GAIN5,strValue);
		m_Configs.EqGainLeft[4] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GAIN6,strValue);
		m_Configs.EqGainLeft[5] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GAIN7,strValue);
		m_Configs.EqGainLeft[6] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GAIN8,strValue);
		m_Configs.EqGainLeft[7] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GAIN9,strValue);
		m_Configs.EqGainLeft[8] = cmNumString::StrToDouble(strValue);

		GetDlgItemText(IDC_EDIT_GF1,strValue);
		m_Configs.EqCFLeft[0] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GF2,strValue);
		m_Configs.EqCFLeft[1] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GF3,strValue);
		m_Configs.EqCFLeft[2] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GF4,strValue);
		m_Configs.EqCFLeft[3] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GF5,strValue);
		m_Configs.EqCFLeft[4] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GF6,strValue);
		m_Configs.EqCFLeft[5] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GF7,strValue);
		m_Configs.EqCFLeft[6] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GF8,strValue);
		m_Configs.EqCFLeft[7] = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_GF9,strValue);
		m_Configs.EqCFLeft[8] = cmNumString::StrToDouble(strValue);

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
	}
}

void CDlgEq::InitUi(int nChannel)
{
	GetDlgItem(IDC_BUTTON_SAVE)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CANCEL)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_Q1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Q9)->EnableWindow(FALSE);
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

		SetDlgItemText(IDC_EDIT_GF1,cmNumString::NumToStr(m_Configs.EqCFRight[0],10));
		SetDlgItemText(IDC_EDIT_GF2,cmNumString::NumToStr(m_Configs.EqCFRight[1],10));
		SetDlgItemText(IDC_EDIT_GF3,cmNumString::NumToStr(m_Configs.EqCFRight[2],10));
		SetDlgItemText(IDC_EDIT_GF4,cmNumString::NumToStr(m_Configs.EqCFRight[3],10));
		SetDlgItemText(IDC_EDIT_GF5,cmNumString::NumToStr(m_Configs.EqCFRight[4],10));
		SetDlgItemText(IDC_EDIT_GF6,cmNumString::NumToStr(m_Configs.EqCFRight[5],10));
		SetDlgItemText(IDC_EDIT_GF7,cmNumString::NumToStr(m_Configs.EqCFRight[6],10));
		SetDlgItemText(IDC_EDIT_GF8,cmNumString::NumToStr(m_Configs.EqCFRight[7],10));
		SetDlgItemText(IDC_EDIT_GF9,cmNumString::NumToStr(m_Configs.EqCFRight[8],10));

		SetDlgItemText(IDC_EDIT_Q2,cmNumString::NumToStr(m_Configs.EqQRight[0]));
		SetDlgItemText(IDC_EDIT_Q3,cmNumString::NumToStr(m_Configs.EqQRight[1]));
		SetDlgItemText(IDC_EDIT_Q4,cmNumString::NumToStr(m_Configs.EqQRight[2]));
		SetDlgItemText(IDC_EDIT_Q5,cmNumString::NumToStr(m_Configs.EqQRight[3]));
		SetDlgItemText(IDC_EDIT_Q6,cmNumString::NumToStr(m_Configs.EqQRight[4]));
		SetDlgItemText(IDC_EDIT_Q7,cmNumString::NumToStr(m_Configs.EqQRight[5]));
		SetDlgItemText(IDC_EDIT_Q8,cmNumString::NumToStr(m_Configs.EqQRight[6]));
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

		SetDlgItemText(IDC_EDIT_GF1,cmNumString::NumToStr(m_Configs.EqCFLeft[0],10));
		SetDlgItemText(IDC_EDIT_GF2,cmNumString::NumToStr(m_Configs.EqCFLeft[1],10));
		SetDlgItemText(IDC_EDIT_GF3,cmNumString::NumToStr(m_Configs.EqCFLeft[2],10));
		SetDlgItemText(IDC_EDIT_GF4,cmNumString::NumToStr(m_Configs.EqCFLeft[3],10));
		SetDlgItemText(IDC_EDIT_GF5,cmNumString::NumToStr(m_Configs.EqCFLeft[4],10));
		SetDlgItemText(IDC_EDIT_GF6,cmNumString::NumToStr(m_Configs.EqCFLeft[5],10));
		SetDlgItemText(IDC_EDIT_GF7,cmNumString::NumToStr(m_Configs.EqCFLeft[6],10));
		SetDlgItemText(IDC_EDIT_GF8,cmNumString::NumToStr(m_Configs.EqCFLeft[7],10));
		SetDlgItemText(IDC_EDIT_GF9,cmNumString::NumToStr(m_Configs.EqCFLeft[8],10));

		SetDlgItemText(IDC_EDIT_Q2,cmNumString::NumToStr(m_Configs.EqQLeft[0]));
		SetDlgItemText(IDC_EDIT_Q3,cmNumString::NumToStr(m_Configs.EqQLeft[1]));
		SetDlgItemText(IDC_EDIT_Q4,cmNumString::NumToStr(m_Configs.EqQLeft[2]));
		SetDlgItemText(IDC_EDIT_Q5,cmNumString::NumToStr(m_Configs.EqQLeft[3]));
		SetDlgItemText(IDC_EDIT_Q6,cmNumString::NumToStr(m_Configs.EqQLeft[4]));
		SetDlgItemText(IDC_EDIT_Q7,cmNumString::NumToStr(m_Configs.EqQLeft[5]));
		SetDlgItemText(IDC_EDIT_Q8,cmNumString::NumToStr(m_Configs.EqQLeft[6]));
	}

	InitChartCtrl();
}