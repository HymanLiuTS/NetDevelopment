
// ClntDlg.h : ͷ�ļ�
//

#pragma once
#include "../Serv/MySocket.h"
#include "afxwin.h"

// CClntDlg �Ի���
class CClntDlg : public CDialogEx
{
// ����
public:
	CClntDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLNT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CMySocket m_servSock;
	CEdit m_send;
	CEdit m_recv;
protected:
	afx_msg LRESULT OnMysocket(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedButton2();
};
