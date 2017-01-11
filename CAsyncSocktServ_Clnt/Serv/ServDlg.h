
// ServDlg.h : ͷ�ļ�
//

#pragma once

#include "MySocket.h"


// CServDlg �Ի���
class CServDlg : public CDialogEx
{
// ����
public:
	CServDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SERV_DIALOG };

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
	CListBox m_ctListBox;
private:
	CMySocket m_Sock;
	CList<CMySocket*> m_pClnts;
protected:
	afx_msg LRESULT OnMysocket(WPARAM wParam, LPARAM lParam);
};
