// UIDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Mfctest.h"
#include "UIDlg.h"
#include "afxdialogex.h"


// UIDlg 对话框

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


// UIDlg 消息处理程序


BOOL UIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	SetTimer(1,1000,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void UIDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString str;
	str.Format("%d",m_index++);
	this->GetDlgItem(IDC_EDIT1)->SetWindowText(str);

	CDialogEx::OnTimer(nIDEvent);
}
