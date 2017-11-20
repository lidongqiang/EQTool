
// EQToolDlg.h : 头文件
//

#pragma once
#include "cmLog.h"
#include "cmIniFile.h"
#include "cmPath.h"
#include "cmFile.h"
#include "cmNumString.h"
#include "cmStrCode.h"
#include "cmCommonDlg.h"
using namespace cm;
#include "afxwin.h"
#include "afxcmn.h"
#include "settings/SettingBase.h"
#include "debug.h"
#include "DlgDrc.h"
#include "DlgEq.h"
#include "ComSet.h"
#include "upgradeLib/RKUpgradeDll.h"

// CEQToolDlg 对话框
class CEQToolDlg : public CDialog
{
// 构造
public:
	CEQToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EQTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	CDlgDrc			m_DlgDrc;
	CDlgEq			m_DlgEq;
	CDialog*		pDialog[2];
	int				m_iCurSelTab;

	void			OnSizeCtl( int cx, int cy);
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CIniSettingBase m_Configs;
	CIniLocalLan	m_LocalLan;

	CString         m_strModulePath;
	CString			m_strLogPath;
	CString			m_strLoader;
	CLogger         *m_pLog;
	CMscomm_eq		m_ctrlcomm;
	CWinThread		*m_pScanThread;
	CEvent			*m_pScanEvent;
	CCriticalSection m_csScanLock;
	BOOL			m_bUpgradeDllInitOK;
	BOOL			m_bTerminated;
	UINT			m_nDeviceCount;
	BOOL			m_bExistMsc;
	BOOL			m_bExistAdb;
	BOOL			m_bExistLoader;

	void			InitUi();
	BOOL			LoadConfig();
	void			storeParaData(FILE *fpPara);
	void			storeParaData1(FILE *fpPara);
	void			LoadParaData(FILE *fpPara);
	std::wstring	GetLocalString(std::wstring strKey);
	VOID			WalkMenu(CMenu *pMenu,CString strMainKeyPart);
	int				UpdatePara(bool bSet);
	void			ScanDeviceProc();
	typedef void(*EQProduct) (float *pfPara, float *pfCurve, signed int swFs, float fMinFreq, signed int swCurvePNum);
public:
	CTabCtrl m_tabInfo;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTcnSelchangeTabInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonLeq();
	afx_msg void OnBnClickedButtonLdrc();
	afx_msg void OnBnClickedButtonReq();
	afx_msg void OnBnClickedButtonrdrc();
	afx_msg void OnComportSetting();
	afx_msg void OnFileSaveas();
	afx_msg void OnFileLoad();
	afx_msg void OnBnClickedCheckLink();
	afx_msg void OnEnKillfocusEditGain();
	afx_msg void OnCbnSelchangeComboChanum();
	CComboBox m_ComChannel;
	int m_edtGain;
	CStatic		m_lblDevice;
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnBnClickedButtonRead();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonCancel();
};
