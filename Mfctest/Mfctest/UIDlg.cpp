// UIDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Mfctest.h"
#include "UIDlg.h"
#include "afxdialogex.h"


// UIDlg �Ի���

IMPLEMENT_DYNAMIC(UIDlg, CDialogEx)

UIDlg::UIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(UIDlg::IDD, pParent),
	m_index(0)
{

}

UIDlg::~UIDlg()
{
}

void UIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(UIDlg, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// UIDlg ��Ϣ�������


BOOL UIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	SetTimer(1,1000,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void UIDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString str;
	str.Format("%d",m_index++);
	this->GetDlgItem(IDC_EDIT1)->SetWindowText(str);

	CDialogEx::OnTimer(nIDEvent);
}
