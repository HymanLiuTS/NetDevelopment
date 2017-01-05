
// WSAAsyncSelectServDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WSAAsyncSelectServ.h"
#include "WSAAsyncSelectServDlg.h"
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
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWSAAsyncSelectServDlg �Ի���




CWSAAsyncSelectServDlg::CWSAAsyncSelectServDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWSAAsyncSelectServDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWSAAsyncSelectServDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_list);
}

BEGIN_MESSAGE_MAP(CWSAAsyncSelectServDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CWSAAsyncSelectServDlg ��Ϣ�������

BOOL CWSAAsyncSelectServDlg::OnInitDialog()
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
	WSAStartup(MAKEWORD(2,2),&m_wsaData);
	m_servSock=socket(AF_INET,SOCK_STREAM,0);
	
	memset(&m_servAddr,0,sizeof(m_servAddr));
	m_servAddr.sin_family=AF_INET;
	m_servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	m_servAddr.sin_port=htons(atoi("8888"));

	bind(m_servSock,(SOCKADDR*)&m_servAddr,sizeof(m_servAddr));

	listen(m_servSock,5);

	WSAAsyncSelect(m_servSock,this->m_hWnd,WM_SOCKET,FD_ACCEPT|FD_READ);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CWSAAsyncSelectServDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWSAAsyncSelectServDlg::OnPaint()
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
HCURSOR CWSAAsyncSelectServDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CWSAAsyncSelectServDlg::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch(message)
	{
		case WM_SOCKET:
			{
				SOCKET sock = (SOCKET) wParam;
				if(m_servSock == sock)
				{
					//��ȡ
					m_clntAddrSz=sizeof(m_clntAddr);
					m_clntSock=accept(m_servSock,(SOCKADDR*)&m_clntAddr,&m_clntAddrSz);
					WSAAsyncSelect(m_clntSock,this->m_hWnd,WM_SOCKET,FD_READ);
					//��m_clntSock��m_clntAddr�浽ӳ����
					m_sockMap.SetAt(m_clntSock,m_clntAddr);
					PrintClientConnectMsg();
					
				}
				else
				{
					m_strLen = recv(sock,buf,BUF_SIZE - 1,0);
					send(sock,buf,m_strLen,0);
					buf[m_strLen]=0;
					PrintClientSendMsg(sock);
				}
			}
			break;
		default:
			break;
	}

	return CDialogEx::OnWndMsg(message, wParam, lParam, pResult);
}



void CWSAAsyncSelectServDlg::PrintClientConnectMsg(void)
{
	CString str;
	CTime locTime=CTime::GetCurrentTime();    //��ȡ��ǰʱ��
	CString strTime=locTime.Format("%Y-%m-%d %H:%M:%S");//����ǰʱ��ת����CString����
	str.Format("%s Client %s:%d Connectted",strTime,inet_ntoa(m_clntAddr.sin_addr),m_clntAddr.sin_port);
	this->m_list.AddString(str);
}


void CWSAAsyncSelectServDlg::PrintClientSendMsg(SOCKET sock)
{
	CString str;
	m_clntAddr=m_sockMap[sock];
	CTime locTime=CTime::GetCurrentTime();   
	CString strTime=locTime.Format("%Y-%m-%d %H:%M:%S");//����ǰʱ��ת����CString����
	str.Format("%s Client %s:%d say:%s",strTime,inet_ntoa(m_clntAddr.sin_addr),m_clntAddr.sin_port,buf);
	this->m_list.AddString(str);
}
