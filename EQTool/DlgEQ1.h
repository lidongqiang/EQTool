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

// CDlgEQ1 dialog

class CDlgEQ1 : public CDialog
{
	DECLARE_DYNAMIC(CDlgEQ1)

public:
	CDlgEQ1(CIniSettingBase &Config,CIniLocalLan &LocalLang,CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgEQ1();

// Dialog Data
	enum { IDD = IDD_DIALOG_EQ1 };
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
	typedef int(*EQ8Product) (float *pfPara, float *pfCurve, signed int swFs, float fMinFreq, signed int swCurvePNum);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_ComChannum;
	afx_msg void OnCbnSelchangeComboChannum();
	afx_msg void OnBnClickedCheckLink();
};
