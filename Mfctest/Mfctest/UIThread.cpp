// UIThread.cpp : ʵ���ļ�
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
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	m_udlg.Create(IDD_DIALOG1);//������ID�ŵĶԻ��򴰿�
	m_udlg.ShowWindow(SW_SHOW);
	m_pMainWnd=&m_udlg;
	
	return TRUE;
}

int CUIThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	m_udlg.DestroyWindow();
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CUIThread, CWinThread)
END_MESSAGE_MAP()


// CUIThread ��Ϣ�������
