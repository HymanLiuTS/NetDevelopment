#pragma once


// UIDlg �Ի���

class UIDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UIDlg)

public:
	UIDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~UIDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	int m_index;
};
