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

// CDlgEq dialog
struct EQparam
{
	
};
class CDlgEq : public CDialog
{
	DECLARE_DYNAMIC(CDlgEq)

public:
	CDlgEq(CIniSettingBase &Config,CIniLocalLan &LocalLang,CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgEq();

// Dialog Data
	enum { IDD = IDD_DIALOG_EQ };

public:
	CIniSettingBase &m_Configs;
	CIniLocalLan    &m_LocalLang;
	HMODULE			AudioHnd;

	CChartCtrl m_ChartEq;
	void InitChartCtrl();
	void CheckGain(int ID);
	void CheckQ(int ID);
	void CheckCf(int ID);
	void InitUi(int nChannel);
	void SavePara(int nChannel);
	void SaveConfig();
	typedef void(*EQProduct) (float *pfPara, float *pfCurve, signed int swFs, float fMinFreq, signed int swCurvePNum);
public:
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnEnKillfocusEditGain1();
	afx_msg void OnEnKillfocusEditGain2();
	afx_msg void OnEnKillfocusEditGain3();
	afx_msg void OnEnKillfocusEditGain4();
	afx_msg void OnEnKillfocusEditGain5();
	afx_msg void OnEnKillfocusEditGain6();
	afx_msg void OnEnKillfocusEditGain7();
	afx_msg void OnEnKillfocusEditGain8();
	afx_msg void OnEnKillfocusEditGf1();
	afx_msg void OnEnKillfocusEditGf2();
	afx_msg void OnEnKillfocusEditGf3();
	afx_msg void OnEnKillfocusEditGf4();
	afx_msg void OnEnKillfocusEditGf5();
	afx_msg void OnEnKillfocusEditGf6();
	afx_msg void OnEnKillfocusEditGf7();
	afx_msg void OnEnKillfocusEditGf8();
	afx_msg void OnEnKillfocusEditQ1();
	afx_msg void OnEnKillfocusEditQ2();
	afx_msg void OnEnKillfocusEditQ3();
	afx_msg void OnEnKillfocusEditQ4();
	afx_msg void OnEnSetfocusEditQ5();
	afx_msg void OnEnKillfocusEditQ6();
	afx_msg void OnEnKillfocusEditQ7();
	afx_msg void OnEnKillfocusEditQ8();
	CComboBox m_ComChannum;
	afx_msg void OnCbnSelchangeComboChannum();
	afx_msg void OnBnClickedCheckLink();
};
