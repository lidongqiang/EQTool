// DlgLimit.cpp : implementation file
//

#include "stdafx.h"
#include "EQTool.h"
#include "DlgLimit.h"


// CDlgLimit dialog

IMPLEMENT_DYNAMIC(CDlgLimit, CDialog)

CDlgLimit::CDlgLimit(CIniSettingBase &Config,CIniLocalLan &LocalLang,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLimit::IDD, pParent),m_Configs(Config),m_LocalLang(LocalLang)
{

}

CDlgLimit::~CDlgLimit()
{
}

void CDlgLimit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CHANNUM, m_ComChannum);
}


BEGIN_MESSAGE_MAP(CDlgLimit, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNUM, &CDlgLimit::OnCbnSelchangeComboChannum)
	ON_BN_CLICKED(IDC_CHECK_LINK, &CDlgLimit::OnBnClickedCheckLink)
END_MESSAGE_MAP()


// CDlgLimit message handlers

void CDlgLimit::OnCbnSelchangeComboChannum()
{
	// TODO: Add your control notification handler code here
	m_Configs.nLimitChannel = m_ComChannum.GetCurSel();
	InitUi(m_Configs.nLimitChannel);
	m_Configs.SaveToolSetting(_T(""));
}

BOOL CDlgLimit::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_LocalLang.TreeControls(m_hWnd,m_Configs.bDebug?TRUE:FALSE,this->IDD,false);

	m_ComChannum.AddString(_T("channel0"));
	m_ComChannum.AddString(_T("channel1"));
	m_ComChannum.SetCurSel(m_Configs.nLimitChannel);

	InitUi(m_Configs.nLimitChannel);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLimit::InitUi(int nChannel)
{
	if (m_Configs.bDrcLink)
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
		SetDlgItemText(IDC_EDIT_ECALTIME_L,cmNumString::NumToStr(m_Configs.fLimitEca_R));
		SetDlgItemText(IDC_EDIT_THRES,cmNumString::NumToStr(m_Configs.fLimitThres_R));
		SetDlgItemText(IDC_EDIT_SMTHTIME,cmNumString::NumToStr(m_Configs.fLimitSmo_R));
		SetDlgItemText(IDC_EDIT_ATTATIME,cmNumString::NumToStr(m_Configs.fLimitAtt_R));
	}
	else
	{
		SetDlgItemText(IDC_EDIT_ECALTIME_L,cmNumString::NumToStr(m_Configs.fLimitEca_L));
		SetDlgItemText(IDC_EDIT_THRES,cmNumString::NumToStr(m_Configs.fLimitThres_L));
		SetDlgItemText(IDC_EDIT_SMTHTIME,cmNumString::NumToStr(m_Configs.fLimitSmo_L));
		SetDlgItemText(IDC_EDIT_ATTATIME,cmNumString::NumToStr(m_Configs.fLimitAtt_L));
	}

}

void CDlgLimit::SavePara(int nChannel)
{
	CString strValue;
	if (nChannel)
	{
		GetDlgItemText(IDC_EDIT_ECALTIME_L,strValue);
		m_Configs.fLimitEca_R = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_THRES,strValue);
		m_Configs.fLimitThres_R = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_SMTHTIME,strValue);
		m_Configs.fLimitSmo_R = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_ATTATIME,strValue);
		m_Configs.fLimitAtt_R = cmNumString::StrToDouble(strValue);
	}
	else
	{
		GetDlgItemText(IDC_EDIT_ECALTIME_L,strValue);
		m_Configs.fLimitEca_L = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_THRES,strValue);
		m_Configs.fLimitThres_L = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_SMTHTIME,strValue);
		m_Configs.fLimitSmo_L = cmNumString::StrToDouble(strValue);
		GetDlgItemText(IDC_EDIT_ATTATIME,strValue);
		m_Configs.fLimitAtt_L = cmNumString::StrToDouble(strValue);
	}
}

void CDlgLimit::SaveConfig()
{
	if (m_Configs.bLimitLink)
	{
		SavePara(0);
		SavePara(1);
	}
	else
	{
		SavePara(m_Configs.nLimitChannel);
	}
}
void CDlgLimit::OnBnClickedCheckLink()
{
	// TODO: Add your control notification handler code here
	m_Configs.bLimitLink = !m_Configs.bLimitLink;
	GetDlgItem(IDC_COMBO_CHANNUM)->EnableWindow(m_Configs.bLimitLink);
	m_Configs.SaveToolSetting(_T(""));
}
