// DlgDrc.cpp : implementation file
//

#include "stdafx.h"
#include "EQTool.h"
#include "DlgDrc.h"


// CDlgDrc dialog

IMPLEMENT_DYNAMIC(CDlgDrc, CDialog)

CDlgDrc::CDlgDrc(CIniSettingBase &Config,CIniLocalLan &LocalLang,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDrc::IDD, pParent),m_Configs(Config),m_LocalLang(LocalLang)
{

}

CDlgDrc::~CDlgDrc()
{
}

void CDlgDrc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_ChartCtrl_DRC, m_ChartDrc);  
}


BEGIN_MESSAGE_MAP(CDlgDrc, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgDrc::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CAN, &CDlgDrc::OnBnClickedButtonCan)
END_MESSAGE_MAP()


// CDlgDrc message handlers
void CDlgDrc::InitChartCtrl()
{
	//CChartStandardAxis* pBottomAxis =   
	//	m_ChartDrc.CreateStandardAxis(CChartCtrl::BottomAxis);  
	//pBottomAxis->SetMinMax(0, 15);  
	//CChartStandardAxis* pLeftAxis =  
	//	m_ChartDrc.CreateStandardAxis(CChartCtrl::LeftAxis);  
	//pLeftAxis->SetMinMax(0, 15);  
	//CChartLineSerie* pLineSerie = m_ChartDrc.CreateLineSerie();  
	//double XValues[1000],YValues[1000];  
	//for (int i=0;i<10;i++)  
	//{   
	//	YValues[i] = i;
	//	XValues[i] = YValues[i]+5;
	//}  
	//pLineSerie = m_ChartDrc.CreateLineSerie();  
	//pLineSerie->SetPoints(XValues,YValues,10);  
	//pLineSerie->SetColor(RGB(255,0,0)); 
	//pLineSerie->SetWidth(pLineSerie->GetWidth()*2);

}
BOOL CDlgDrc::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_LocalLang.TreeControls(m_hWnd,m_Configs.bDebug?TRUE:FALSE,this->IDD,false);

	InitUi(m_Configs.nChannel);

	InitChartCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgDrc::InitUi(int nChannel)
{
	GetDlgItem(IDC_BUTTON_SAVE)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CAN)->ShowWindow(FALSE);
	if (nChannel)
	{
		SetDlgItemText(IDC_EDIT_DIVFREQ,cmNumString::NumToStr(m_Configs.DivFreq_R,10));
		//low band
		SetDlgItemText(IDC_EDIT_THREL_L,cmNumString::NumToStr(m_Configs.Threl_RL,10));
		SetDlgItemText(IDC_EDIT_THREH_L,cmNumString::NumToStr(m_Configs.Threh_RL,10));
		SetDlgItemText(IDC_EDIT_OFFSET_L,cmNumString::NumToStr(m_Configs.Offset_RL,10));
		SetDlgItemText(IDC_EDIT_SMTHTIME_L,cmNumString::NumToStr(m_Configs.Smthtime_RL,10));
		SetDlgItemText(IDC_EDIT_RLSTIME_L,cmNumString::NumToStr(m_Configs.Rlstime_RL,10));
		SetDlgItemText(IDC_EDIT_ECALTIME_L,cmNumString::NumToStr(m_Configs.Ecaltime_RL,10));
		SetDlgItemText(IDC_EDIT_ATTATIME_L,cmNumString::NumToStr(m_Configs.Attatime_RL,10));
		SetDlgItemText(IDC_EDIT_RATLNOM_L,cmNumString::NumToStr(m_Configs.Ratlnom_RL,10));
		SetDlgItemText(IDC_EDIT_RATLDEN_L,cmNumString::NumToStr(m_Configs.Ratlden_RL,10));
		SetDlgItemText(IDC_EDIT_RATHNOM_L,cmNumString::NumToStr(m_Configs.Rathnom_RL,10));
		SetDlgItemText(IDC_EDIT_RATHDEN_L,cmNumString::NumToStr(m_Configs.Rathden_RL,10));

		//higt band 
		SetDlgItemText(IDC_EDIT_THREL_H,cmNumString::NumToStr(m_Configs.Threl_RH,10));
		SetDlgItemText(IDC_EDIT_THREH_H,cmNumString::NumToStr(m_Configs.Threh_RH,10));
		SetDlgItemText(IDC_EDIT_OFFSET_H,cmNumString::NumToStr(m_Configs.Offset_RH,10));
		SetDlgItemText(IDC_EDIT_SMTHTIME_H,cmNumString::NumToStr(m_Configs.Smthtime_RH,10));
		SetDlgItemText(IDC_EDIT_RLSTIME_H,cmNumString::NumToStr(m_Configs.Rlstime_RH,10));
		SetDlgItemText(IDC_EDIT_ECALTIME_H,cmNumString::NumToStr(m_Configs.Ecaltime_RH,10));
		SetDlgItemText(IDC_EDIT_ATTATIME_H,cmNumString::NumToStr(m_Configs.Attatime_RH,10));
		SetDlgItemText(IDC_EDIT_RATLNOM_H,cmNumString::NumToStr(m_Configs.Ratlnom_RH,10));
		SetDlgItemText(IDC_EDIT_RATLDEN_H,cmNumString::NumToStr(m_Configs.Ratlden_RH,10));
		SetDlgItemText(IDC_EDIT_RATHNOM_H,cmNumString::NumToStr(m_Configs.Rathnom_RH,10));
		SetDlgItemText(IDC_EDIT_RATHDEN_H,cmNumString::NumToStr(m_Configs.Rathden_RH,10));
	}
	else
	{
		SetDlgItemText(IDC_EDIT_DIVFREQ,cmNumString::NumToStr(m_Configs.DivFreq_L,10));
		//low band
		SetDlgItemText(IDC_EDIT_THREL_L,cmNumString::NumToStr(m_Configs.Threl_LL,10));
		SetDlgItemText(IDC_EDIT_THREH_L,cmNumString::NumToStr(m_Configs.Threh_LL,10));
		SetDlgItemText(IDC_EDIT_OFFSET_L,cmNumString::NumToStr(m_Configs.Offset_LL,10));
		SetDlgItemText(IDC_EDIT_SMTHTIME_L,cmNumString::NumToStr(m_Configs.Smthtime_LL,10));
		SetDlgItemText(IDC_EDIT_RLSTIME_L,cmNumString::NumToStr(m_Configs.Rlstime_LL,10));
		SetDlgItemText(IDC_EDIT_ECALTIME_L,cmNumString::NumToStr(m_Configs.Ecaltime_LL,10));
		SetDlgItemText(IDC_EDIT_ATTATIME_L,cmNumString::NumToStr(m_Configs.Attatime_LL,10));
		SetDlgItemText(IDC_EDIT_RATLNOM_L,cmNumString::NumToStr(m_Configs.Ratlnom_LL,10));
		SetDlgItemText(IDC_EDIT_RATLDEN_L,cmNumString::NumToStr(m_Configs.Ratlden_LL,10));
		SetDlgItemText(IDC_EDIT_RATHNOM_L,cmNumString::NumToStr(m_Configs.Rathnom_LL,10));
		SetDlgItemText(IDC_EDIT_RATHDEN_L,cmNumString::NumToStr(m_Configs.Rathden_LL,10));

		//higt band 
		SetDlgItemText(IDC_EDIT_THREL_H,cmNumString::NumToStr(m_Configs.Threl_LH,10));
		SetDlgItemText(IDC_EDIT_THREH_H,cmNumString::NumToStr(m_Configs.Threh_LH,10));
		SetDlgItemText(IDC_EDIT_OFFSET_H,cmNumString::NumToStr(m_Configs.Offset_LH,10));
		SetDlgItemText(IDC_EDIT_SMTHTIME_H,cmNumString::NumToStr(m_Configs.Smthtime_LH,10));
		SetDlgItemText(IDC_EDIT_RLSTIME_H,cmNumString::NumToStr(m_Configs.Rlstime_LH,10));
		SetDlgItemText(IDC_EDIT_ECALTIME_H,cmNumString::NumToStr(m_Configs.Ecaltime_LH,10));
		SetDlgItemText(IDC_EDIT_ATTATIME_H,cmNumString::NumToStr(m_Configs.Attatime_LH,10));
		SetDlgItemText(IDC_EDIT_RATLNOM_H,cmNumString::NumToStr(m_Configs.Ratlnom_LH,10));
		SetDlgItemText(IDC_EDIT_RATLDEN_H,cmNumString::NumToStr(m_Configs.Ratlden_LH,10));
		SetDlgItemText(IDC_EDIT_RATHNOM_H,cmNumString::NumToStr(m_Configs.Rathnom_LH,10));
		SetDlgItemText(IDC_EDIT_RATHDEN_H,cmNumString::NumToStr(m_Configs.Rathden_LH,10));
	}

}

void CDlgDrc::OnBnClickedButtonSave()
{
	// TODO: Add your control notification handler code here
	CString strValue;
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
	//if (0)
	//{
	//	return ;
	//}
	//CSpawn					ShellSpawn;
	//wchar_t     strCmd[2600] = {0};  

	//swprintf(strCmd,nof(strCmd),TEXT("tftp -i %s put \"%s%s\""));
	//if(ShellSpawn.Exe(strCmd,25000, true)) 
	//{
	//	if(0 != ShellSpawn.GetResult()) 
	//	{
	//		return -1;
	//	}
	//}
	//else
	//{
	//	return -2;
	//}

	m_Configs.SaveToolSetting(_T(""));
	AfxMessageBox(_T("保存成功"));
}

void CDlgDrc::OnBnClickedButtonCan()
{
	// TODO: Add your control notification handler code here
	InitUi(m_Configs.nChannel);
}

void CDlgDrc::SavePara(int nChannel)
{
	CString strValue;
	if (nChannel)
	{
		GetDlgItemText(IDC_EDIT_DIVFREQ,strValue);
		m_Configs.DivFreq_R = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_THREL_L,strValue);
		m_Configs.Threl_RL = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_THREH_L,strValue);
		m_Configs.Threh_RL = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_OFFSET_L,strValue);
		m_Configs.Offset_RL = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_SMTHTIME_L,strValue);
		m_Configs.Smthtime_RL = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_RLSTIME_L,strValue);
		m_Configs.Rlstime_RL = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_ECALTIME_L,strValue);
		m_Configs.Ecaltime_RL = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_ATTATIME_L,strValue);
		m_Configs.Attatime_RL = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_RATLNOM_L,strValue);
		m_Configs.Ratlnom_RL = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_RATLDEN_L,strValue);
		m_Configs.Ratlden_RL = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_RATHNOM_L,strValue);
		m_Configs.Rathnom_RL = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_RATHDEN_L,strValue);
		m_Configs.Rathden_RL = cmNumString::StrToInt32(strValue);

		GetDlgItemText(IDC_EDIT_THREL_H,strValue);
		m_Configs.Threl_RH = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_THREH_H,strValue);
		m_Configs.Threh_RH = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_OFFSET_H,strValue);
		m_Configs.Offset_RH = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_SMTHTIME_H,strValue);
		m_Configs.Smthtime_RH = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_RLSTIME_H,strValue);
		m_Configs.Rlstime_RH = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_ECALTIME_H,strValue);
		m_Configs.Ecaltime_RH = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_ATTATIME_H,strValue);
		m_Configs.Attatime_RH = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_RATLNOM_H,strValue);
		m_Configs.Ratlnom_RH = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_RATLDEN_H,strValue);
		m_Configs.Ratlden_RH = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_RATHNOM_H,strValue);
		m_Configs.Rathnom_RH = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_RATHDEN_H,strValue);
		m_Configs.Rathden_RH = cmNumString::StrToInt32(strValue);
	}
	else
	{
		GetDlgItemText(IDC_EDIT_DIVFREQ,strValue);
		m_Configs.DivFreq_L = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_THREL_L,strValue);
		m_Configs.Threl_LL = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_THREH_L,strValue);
		m_Configs.Threh_LL = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_OFFSET_L,strValue);
		m_Configs.Offset_LL = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_SMTHTIME_L,strValue);
		m_Configs.Smthtime_LL = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_RLSTIME_L,strValue);
		m_Configs.Rlstime_LL = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_ECALTIME_L,strValue);
		m_Configs.Ecaltime_LL = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_ATTATIME_L,strValue);
		m_Configs.Attatime_LL = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_RATLNOM_L,strValue);
		m_Configs.Ratlnom_LL = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_RATLDEN_L,strValue);
		m_Configs.Ratlden_LL = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_RATHNOM_L,strValue);
		m_Configs.Rathnom_LL = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_RATHDEN_L,strValue);
		m_Configs.Rathden_LL = cmNumString::StrToInt32(strValue);

		GetDlgItemText(IDC_EDIT_THREL_H,strValue);
		m_Configs.Threl_LH = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_THREH_H,strValue);
		m_Configs.Threh_LH = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_OFFSET_H,strValue);
		m_Configs.Offset_LH = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_SMTHTIME_H,strValue);
		m_Configs.Smthtime_LH = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_RLSTIME_H,strValue);
		m_Configs.Rlstime_LH = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_ECALTIME_H,strValue);
		m_Configs.Ecaltime_LH = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_ATTATIME_H,strValue);
		m_Configs.Attatime_LH = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_RATLNOM_H,strValue);
		m_Configs.Ratlnom_LH = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_RATLDEN_H,strValue);
		m_Configs.Ratlden_LH = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_RATHNOM_H,strValue);
		m_Configs.Rathnom_LH = cmNumString::StrToInt32(strValue);
		GetDlgItemText(IDC_EDIT_RATHDEN_H,strValue);
		m_Configs.Rathden_LH = cmNumString::StrToInt32(strValue);
	}
}