#pragma once


// UIDlg 对话框

class UIDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UIDlg)

public:
	UIDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~UIDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	int m_index;
};
