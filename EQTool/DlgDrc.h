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

// CDlgDrc dialog

class CDlgDrc : public CDialog
{
	DECLARE_DYNAMIC(CDlgDrc)

public:
	CDlgDrc(CIniSettingBase &Config,CIniLocalLan &LocalLang,CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgDrc();

// Dialog Data
	enum { IDD = IDD_DIALOG_DRC };

public:
	CIniSettingBase &m_Configs;
	CIniLocalLan    &m_LocalLang;
	CChartCtrl m_ChartDrc;
	void InitUi(int nChannel);
	void SavePara(int nChannel);
	void InitChartCtrl();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonCan();
};