//////////////////////////////////////////////////////////////////////////
//////File: Clnt.cpp
//////Author: Hyman
//////Date: 2016/12/13
//////Description: ���̵߳�socket�ͻ���
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "winsock2.h"
#include "stdio.h"
#include "process.h"
//ws2_32.lib��
#pragma comment(lib,"ws2_32.lib")

#define BUF_SIZE 30
void ErrorHandler(char* message);
unsigned WINAPI WriteHandler(void* param);
unsigned WINAPI ReadHandler(void* param);
//�¼��������������̵߳Ķ�д
HANDLE evts[2];
//��ȡ�ı�׼����ĳ��ȣ��������տͻ������ݵ����ֵ
int strLen=0;


int _tmain(int argc, _TCHAR* argv[])
{
	SOCKET sock;
	sockaddr_in addr;
	WSADATA wsaData;
	HANDLE hThreads[2];
	int strLen;
	//ͨ���������Ĳ�������IP��ַ�Ͷ˿ں�
	if(argc!=3)
	{
		printf("Usage %s <addr> <port>\n",argv[0]);
		//exit(1);
	}
	if(WSAStartup(MAKEWORD(2,2),&wsaData)==SOCKET_ERROR)
		ErrorHandler("WSAStartup() error");

	sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock==INVALID_SOCKET)
		ErrorHandler("socket() error");

	memset(&addr,0,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	addr.sin_port=htons(atoi("8888"));

	if(connect(sock,(sockaddr*)&addr,sizeof(addr))==SOCKET_ERROR)
		ErrorHandler("connect() error");
	//�����߳�����д�Ͷ�
	hThreads[0]=(HANDLE)_beginthreadex(NULL,0,WriteHandler,&sock,0,NULL);
	hThreads[1]=(HANDLE)_beginthreadex(NULL,0,ReadHandler,&sock,0,NULL);
	//�����¼�����Ϊmanual-resetģʽ������д���¼���������ź�״̬�������¼���������ź�״̬
	evts[0]=CreateEvent(NULL,true,true,NULL);
	evts[1]=CreateEvent(NULL,true,false,NULL);

	WaitForMultipleObjects(2,hThreads,true,INFINITE);

	CloseHandle(evts[0]);
	CloseHandle(evts[1]);
	return 0;
}

//���ڴ�����Ϣ��ӡ
void ErrorHandler(char* message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}

//����д�߳�
unsigned WINAPI WriteHandler(void* param)
{
	char buf[BUF_SIZE];
	SOCKET sock=*((SOCKET*)(param));
	while(1)
	{
		WaitForSingleObject(evts[0],INFINITE);
		fputs("input:",stdout);
		memset(buf,0,BUF_SIZE);
		fgets(buf,BUF_SIZE,stdin);
		if(!strcmp(buf,"q\n")||!strcmp(buf,"Q\n"))
		{
			strLen=-1;
			SetEvent(evts[1]);
			break;
		}
		strLen=strlen(buf);
		send(sock,buf,strLen,0);
		ResetEvent(evts[0]);
		SetEvent(evts[1]);
	}
	return 0;
}

//���ڶ��߳�
unsigned WINAPI ReadHandler(void* param)
{
	char buf[BUF_SIZE];
	SOCKET sock=*((SOCKET*)(param));
	while(1)
	{
		int temp=0;
		WaitForSingleObject(evts[1],INFINITE);
		if(strLen==-1)
		{
			SetEvent(evts[0]);
			break;;
		}
		while(temp<strLen)
		{
			temp+=recv(sock,buf,BUF_SIZE,0);
		}
		buf[temp]=0;
		fputs("the meesgae from serv:",stdout);
		printf("%s",buf);
		ResetEvent(evts[1]);
		SetEvent(evts[0]);
	}
	return 0;
}

