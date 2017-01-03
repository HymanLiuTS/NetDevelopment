// SelectServ.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdio.h"
#include "winsock2.h"

#pragma comment(lib,"ws2_32.lib")
#define BUF_SIZE 30
#define SOCK_SIZE 20

void ErrorHandler(const char* message);

int _tmain(int argc, _TCHAR* argv[])
{
	SOCKET servSock,clntSock;
	SOCKADDR_IN servAddr,clntAddr;
	int clntAddrSz;
	int strLen;
	char buf[BUF_SIZE];

	fd_set	fds,copyRead;
	SOCKET socks[SOCK_SIZE];
	TIMEVAL tm;
	int sockNum = 0;
	unsigned long ul=1; 

	WSADATA	wsaData;
	if(WSAStartup(MAKEWORD(2,2),&wsaData)==SOCKET_ERROR)
	{
		ErrorHandler("WSAStartUp Error");
	}
	servSock=socket(AF_INET,SOCK_STREAM,0);
	if(servSock==INVALID_SOCKET)
		ErrorHandler("socket error");
	//��socket���óɷ�����ģʽ
	//ioctlsocket(servSock,FIONBIO,&ul);

	memset(&servAddr,0,sizeof(servAddr));
	servAddr.sin_family=AF_INET;
	servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servAddr.sin_port=htons(atoi("8888"));

	if(bind(servSock,(const sockaddr*)&servAddr,sizeof(servAddr))==SOCKET_ERROR)
	{
		ErrorHandler("bind error");
	}

	if(listen(servSock,SOCK_SIZE)==SOCKET_ERROR)
	{
		ErrorHandler("listen error");
	}
	//����socks�������е�Ԫ��������Ч��socket
	for(int i=0;i<SOCK_SIZE;i++)
		socks[i] = INVALID_SOCKET;
	sockNum += 1;
	
	socks[0]=servSock;
	FD_ZERO(&fds);
	FD_SET(servSock,&fds);
	tm.tv_sec=100000;
	tm.tv_usec=0;
	
	while(1)
	{
		copyRead=fds;
		int selResult = select(sockNum,&copyRead,0,0,&tm);
		printf("select return...\n");
		if(selResult==-1)
			puts("select error");
		else if(selResult==0)
			puts("timeout!");
		else
		{
			//���ж��Ƿ������µĿͻ�������
			if(FD_ISSET(socks[0],&copyRead))
			{
				clntAddrSz = sizeof(clntAddr);
				clntSock = accept(servSock,(SOCKADDR*)&clntAddr,&clntAddrSz);
				//��socket���óɷ�����ģʽ
				ioctlsocket(clntSock,FIONBIO,&ul);
				for(int i=0;i<SOCK_SIZE;i++)
				{
					//����socks����Ԫ��Ϊ��Ч��socket������ͻ��˵�socket
					if(socks[i] == INVALID_SOCKET)
					{
						FD_SET(clntSock,&fds);
						socks[i]=clntSock;
						sockNum++;
						break;
					}
				}
			}
			//�������еĿͻ���socket��0��λ��Ϊ����˵�socket�����Դ�1��ʼ
			for (int i=1;i<SOCK_SIZE;i++)
			{
				//�������Ч��socket ���ش���
				if(socks[i]==INVALID_SOCKET) continue;
				if(FD_ISSET(socks[i],&copyRead))
				{
					strLen=recv(socks[i],buf,BUF_SIZE,0);
					if(strLen <= 0)//�ͻ��˶Ͽ�������
					{
						closesocket(socks[i]);
						//��fdsɾ���ͻ���socket
						FD_CLR(socks[i],&fds);
						//����Ӧ��λ���ٴ���Ϊ��Чsocket
						socks[i] == INVALID_SOCKET;
						sockNum--;
					}
					else if(strLen > 0)
					{
						send(socks[i],buf,strLen,0);
					}
				}
			}
		}
	}
	closesocket(servSock);
	return 0;
}

void ErrorHandler(const char* message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}


