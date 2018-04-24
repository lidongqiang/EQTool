#pragma once
#include "cmIniFile.h"
#include "cmPath.h"
#include "cmFile.h"
#include "cmNumString.h"
#include "cmCommonDlg.h"
#include "cmStrCode.h"
using namespace cm;
#include "ChartCtr/ChartCtrl.h"
#include "ChartCtr/ChartAxisLabel.h" 
#include "ChartCtr/ChartAxis.h" 
#include "ChartCtr/ChartLineSerie.h"
#include "settings/SettingBase.h"
#include "scriptexe.h"
#include "afxwin.h"

// CDlgLimit dialog

class CDlgLimit : public CDialog
{
	DECLARE_DYNAMIC(CDlgLimit)

public:
	CDlgLimit(CIniSettingBase &Config,CIniLocalLan &LocalLang,CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgLimit();

// Dialog Data
	enum { IDD = IDD_DIALOG_LIMIT };
public:
	CIniSettingBase &m_Configs;
	CIniLocalLan    &m_LocalLang;
	void InitUi(int nChannel);
	void SavePara(int nChannel);
	void SaveConfig();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboChannum();
	CComboBox m_ComChannum;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckLink();
};
