
// WSAAsyncSelectServ.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWSAAsyncSelectServApp:
// �йش����ʵ�֣������ WSAAsyncSelectServ.cpp
//

class CWSAAsyncSelectServApp : public CWinApp
{
public:
	CWSAAsyncSelectServApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWSAAsyncSelectServApp theApp;