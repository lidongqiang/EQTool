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
	int flag = _ttoi(portnums);//����ת��Ϊ��ֵ����
	if (flag)//�������Ĵ��ڱ��Ϊ����������ִ����������
	{
		if (m_ctrlcomm.get_PortOpen())
		{
			m_ctrlcomm.put_PortOpen(FALSE);
		}
		m_ctrlcomm.put_CommPort(flag); //ѡ��COM
		m_ctrlcomm.put_InBufferSize(1024); //���ջ�����
		m_ctrlcomm.put_OutBufferSize(1024);//���ͻ�����
		m_ctrlcomm.put_InputLen(0);//���õ�ǰ���������ݳ���Ϊ0,��ʾȫ����ȡ
		m_ctrlcomm.put_InputMode(1);//�Զ����Ʒ�ʽ��д����
		m_ctrlcomm.put_RThreshold(1);//���ջ�������1����1�������ַ�ʱ���������������ݵ�OnComm
		m_ctrlcomm.put_Settings(_T("115200,n,8,1"));//������9600�޼���λ��8������λ��1��ֹͣλ

		if (!m_ctrlcomm.get_PortOpen())//�������û�д����
		{
			m_ctrlcomm.put_PortOpen(TRUE);//�򿪴���
			AfxMessageBox(_T("���ڴ򿪳ɹ�"));
		}
		else
		{
			m_ctrlcomm.put_OutBufferCount(0);
			AfxMessageBox(_T("���ڴ�ʧ��"));
		}
	}
	else
	{
		AfxMessageBox(_T("����������Ҫ�򿪴��ڱ��"));
	}
}
