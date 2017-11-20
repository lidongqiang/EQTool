// ComSet.cpp : implementation file
//

#include "stdafx.h"
#include "EQTool.h"
#include "ComSet.h"


// CComSet dialog

IMPLEMENT_DYNAMIC(CComSet, CDialog)

CComSet::CComSet(CMscomm_eq &Ctrlcomm,CWnd* pParent /*=NULL*/)
	: CDialog(CComSet::IDD, pParent),m_ctrlcomm(Ctrlcomm)
{

}

CComSet::~CComSet()
{
}

void CComSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCOMM_EQ, m_ctrlcomm);
}


BEGIN_MESSAGE_MAP(CComSet, CDialog)
	ON_BN_CLICKED(ID_BTN_OK, &CComSet::OnBnClickedBtnOk)
END_MESSAGE_MAP()


// CComSet message handlers

void CComSet::OnBnClickedBtnOk()
{
	// TODO: Add your control notification handler code here
	CString portnums;
	GetDlgItem(IDC_EDIT_COM)->GetWindowText(portnums);
	int flag = _ttoi(portnums);//将其转化为数值类型
	if (flag)//如果输入的串口编号为正整数，才执行下列命令
	{
		if (m_ctrlcomm.get_PortOpen())
		{
			m_ctrlcomm.put_PortOpen(FALSE);
		}
		m_ctrlcomm.put_CommPort(flag); //选择COM
		m_ctrlcomm.put_InBufferSize(1024); //接收缓冲区
		m_ctrlcomm.put_OutBufferSize(1024);//发送缓冲区
		m_ctrlcomm.put_InputLen(0);//设置当前接收区数据长度为0,表示全部读取
		m_ctrlcomm.put_InputMode(1);//以二进制方式读写数据
		m_ctrlcomm.put_RThreshold(1);//接收缓冲区有1个及1个以上字符时，将引发接收数据的OnComm
		m_ctrlcomm.put_Settings(_T("115200,n,8,1"));//波特率9600无检验位，8个数据位，1个停止位

		if (!m_ctrlcomm.get_PortOpen())//如果串口没有打开则打开
		{
			m_ctrlcomm.put_PortOpen(TRUE);//打开串口
			AfxMessageBox(_T("串口打开成功"));
		}
		else
		{
			m_ctrlcomm.put_OutBufferCount(0);
			AfxMessageBox(_T("串口打开失败"));
		}
	}
	else
	{
		AfxMessageBox(_T("请先输入需要打开串口编号"));
	}
}
