
// ClntDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Clnt.h"
#include "ClntDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
//	afx_msg LRESULT OnMysocket(WPARAM wParam, LPARAM lParam);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_MESSAGE(WM_MYSOCKET, &CAboutDlg::OnMysocket)
END_MESSAGE_MAP()


// CClntDlg �Ի���




CClntDlg::CClntDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClntDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClntDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_send);
	DDX_Control(pDX, IDC_EDIT2, m_recv);
}

BEGIN_MESSAGE_MAP(CClntDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CClntDlg::OnBnClickedButton1)
	ON_MESSAGE(WM_MYSOCKET, &CClntDlg::OnMysocket)
	ON_BN_CLICKED(IDC_BUTTON2, &CClntDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CClntDlg ��Ϣ�������

BOOL CClntDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	WSAData wsaData;
	AfxSocketInit(&wsaData);

	
	
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CClntDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CClntDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CClntDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClntDlg::OnBnClickedButton1()
{
	char buf[BUF_SIZE];
	int strLen=m_send.GetWindowText(buf,BUF_SIZE);
	m_servSock.Send(buf,strLen,0);
}



afx_msg LRESULT CClntDlg::OnMysocket(WPARAM wParam, LPARAM lParam)
{
	CMySocket* pSock=(CMySocket*)wParam;
	int param=*((int*)(lParam));
	int recvLen;
	char buf[BUF_SIZE];
	switch(param)
	{
	case RECIEVE:
		{
			int strLen = pSock->Receive(buf,BUF_SIZE-1,0);
			buf[strLen]=0;
			CString str;
			str.Format("%s",buf);
			m_recv.SetWindowText(str);
		}
		break;
	default:
		break;
	}
	return 0;
}



void CClntDlg::OnBnClickedButton2()
{
	m_servSock.Create();
	SOCKADDR_IN servAddr;
	servAddr.sin_family=AF_INET;
	servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servAddr.sin_port=htons(8888);
	m_servSock.m_pWnd=this;
	BOOL ret = m_servSock.Connect((SOCKADDR*)&servAddr,sizeof(servAddr));
}
