#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")
void error_handling(char* message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}

int main(int argc,char* argv[])
{
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr; 

	char message[30];
	int strlen;
	if(argc!=3)
	{
		printf("Usage : %s <ip> <port>\n",argv[0]);
		exit(1);
	}
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
		error_handling("WSAStartup error");
	hSocket=socket(PF_INET,SOCK_STREAM,0);
	if(hSocket==INVALID_SOCKET)
		error_handling("socket error");
	memset(&servAddr,0,sizeof(servAddr));
	servAddr.sin_family=AF_INET;
	servAddr.sin_addr.s_addr=inet_addr(argv[1]);
	servAddr.sin_port=htons(atoi(argv[2]));
	if(connect(hSocket,(SOCKADDR*)&servAddr,sizeof(servAddr))==SOCKET_ERROR)
		error_handling("connect error");
	strlen=recv(hSocket,message,sizeof(message)-1,0);
	if(strlen==-1)
		error_handling("recv error");
	printf("Message from server: %s\n",message);
	closesocket(hSocket);
	WSACleanup();
	return 0;
}
