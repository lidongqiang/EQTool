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
	void InitUi(int nChannel);
	void SavePara(int nChannel);
	typedef void(*EQProduct) (float *pfPara, float *pfCurve, signed int swFs, float fMinFreq, signed int swCurvePNum);
public:
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSave();
};
