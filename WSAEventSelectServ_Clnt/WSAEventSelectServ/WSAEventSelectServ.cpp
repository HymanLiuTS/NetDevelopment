// WSAEventSelectServ.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib")

#define BUF_SIZE 30
#define EVENT_SIZE 64

void ErrorHandler(const char* message);
void CompressEvents(HANDLE* events,int pos,int size);
void CompressSocks(SOCKET* socks,int pos,int size);

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;

	SOCKET servSock,clntSock;
	SOCKADDR_IN servAddr,clntAddr;
	int clntAddrSz;
	SOCKET socks[EVENT_SIZE];
	int strLen;
	int eventNum = 0;

	char buf[BUF_SIZE];

	HANDLE hEvent;
	HANDLE events[EVENT_SIZE];
	int minPos;
	WSANETWORKEVENTS netEvents;
	

	if(WSAStartup(MAKEWORD(2,2),&wsaData)==SOCKET_ERROR)
		ErrorHandler("WSAStartUp Error");

	servSock=socket(AF_INET,SOCK_STREAM,0);
	if(servSock==INVALID_SOCKET)
		ErrorHandler("socket error");

	memset(&servAddr,0,sizeof(servAddr));
	servAddr.sin_family=AF_INET;
	servAddr.sin_addr.s_addr=INADDR_ANY;
	servAddr.sin_port=htons(atoi("8888"));

	if(bind(servSock,(const sockaddr*)&servAddr,sizeof(servAddr))==SOCKET_ERROR)
		ErrorHandler("bind error");

	if(listen(servSock,5)==SOCKET_ERROR)
		ErrorHandler("listen error");

	hEvent=WSACreateEvent();
	//����������servSock���¼��ŵ���һ��λ��
	events[eventNum]=hEvent;
	socks[eventNum]=servSock;

	//ע��servSock
	WSAEventSelect(servSock,hEvent,FD_ACCEPT);

	while(1)
	{
		//����WSAWaitForMultipleEvents�ȴ��¼����signaled״̬�����õȴ�һ���¼�������
		//�Ҳ����ó�ʱ����Զ�ȴ�
		minPos=WSAWaitForMultipleEvents(eventNum + 1,events,false,WSA_INFINITE,false);
		//�õ�����ֵ
		minPos=minPos-WSA_WAIT_EVENT_0;
		//������������Ԫ�أ�����WSAWaitForMultipleEvents����֤����Ԫ�ض�Ӧ���ں˶����Ƿ����
		//signaled״̬
		for (int i=minPos;i<eventNum + 1;i++)
		{
			int otherPos = minPos;
			if(i!=minPos)
			    otherPos =WSAWaitForMultipleEvents(1,events,true,0,false);
			//�ų�δ���signaled״̬���¼�
			if(otherPos==WSA_WAIT_FAILED||otherPos==WSA_WAIT_TIMEOUT)
				continue;

			WSAEnumNetworkEvents(socks[i],events[i],&netEvents);
			if(netEvents.lNetworkEvents & FD_ACCEPT)
			{
				if(netEvents.iErrorCode[FD_ACCEPT_BIT]!=0)
				{
					puts("accept error");
					break;
				}
				clntAddrSz=sizeof(clntAddr);
				clntSock=accept(socks[i],(SOCKADDR*)&clntAddr,&clntAddrSz);
				eventNum++;
				socks[eventNum]=clntSock;
				events[eventNum]=WSACreateEvent();
				WSAEventSelect(socks[eventNum],events[eventNum],FD_READ|FD_CLOSE);
				puts("New Client Connected ...");
			}

			if(netEvents.lNetworkEvents & FD_READ)
			{
				if(netEvents.iErrorCode[FD_READ_BIT]!=0)
				{
					puts("recv error");
					break;
				}
				strLen=recv(socks[i],buf,BUF_SIZE,0);
				send(socks[i],buf,strLen,0);
			}

			if(netEvents.lNetworkEvents & FD_CLOSE)
			{
				if(netEvents.iErrorCode[FD_CLOSE_BIT]!=0)
				{
					puts("close error");
					break;
				}
				WSACloseEvent(events[i]);
				closesocket(socks[i]);
				CompressEvents(events,eventNum,EVENT_SIZE);
				CompressSocks(socks,eventNum,EVENT_SIZE);
				eventNum --;
			}

		}
	}
	WSACleanup();
	return 0;
}

void ErrorHandler(const char* message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}

void CompressEvents(HANDLE* events,int pos,int size)
{
	while(pos<size-1)
	{
		events[pos]=events[pos+1];
	}
}

void CompressSocks(SOCKET* socks,int pos,int size)
{
	while(pos<size-1)
	{
		socks[pos]=socks[pos+1];
	}
}

