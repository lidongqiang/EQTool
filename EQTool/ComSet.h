#pragma once
#include "mscomm_eq.h"


// CComSet dialog

class CComSet : public CDialog
{
	DECLARE_DYNAMIC(CComSet)

public:
	CComSet(CMscomm_eq &Ctrlcomm,CWnd* pParent = NULL);   // standard constructor
	virtual ~CComSet();

// Dialog Data
	enum { IDD = IDD_DIALOG_COMSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CMscomm_eq &m_ctrlcomm;
public:
	afx_msg void OnBnClickedBtnOk();

};
