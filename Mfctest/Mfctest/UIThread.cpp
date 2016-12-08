// UIThread.cpp : 实现文件
//

#include "stdafx.h"
#include "Mfctest.h"
#include "UIThread.h"


// CUIThread

IMPLEMENT_DYNCREATE(CUIThread, CWinThread)

CUIThread::CUIThread()
{
}

CUIThread::~CUIThread()
{
}

BOOL CUIThread::InitInstance()
{
	// TODO: 在此执行任意逐线程初始化
	m_udlg.Create(IDD_DIALOG1);//创建此ID号的对话框窗口
	m_udlg.ShowWindow(SW_SHOW);
	m_pMainWnd=&m_udlg;
	
	return TRUE;
}

int CUIThread::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	m_udlg.DestroyWindow();
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CUIThread, CWinThread)
END_MESSAGE_MAP()


// CUIThread 消息处理程序
