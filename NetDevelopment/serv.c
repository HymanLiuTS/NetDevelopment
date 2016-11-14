//////////////////////////////////////
//////////////////////////////////////
/////File: serv.c
/////Author: Hyman
/////Date: 2016/11/14
//////////////////////////////////////
//////////////////////////////////////


#include <winsock2.h>  
#include <stdio.h>  
#include "stdlib.h"  

#pragma comment(lib,"ws2_32.lib")
void error_handling(char* message);  
int main(int argc,char* argv[])  
{  
	WSADATA wsaData;  
	SOCKET hSeverSock,hClntSock;  
	SOCKADDR_IN servAddr,clntAddr;  
	int szClntAddr;  
	char Message[]="Hello World";  
	if(argc!=2)  
	{  
		printf("Usage : %s <port>\n",argv[0]);  
		exit(1);  
	}  

	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)  
		error_handling("WSAStartup error");  

	hSeverSock=socket(PF_INET,SOCK_STREAM,0);  
	if(hSeverSock==INVALID_SOCKET)  
		error_handling("socket error");  

	memset(&servAddr,0,sizeof(servAddr));  
	servAddr.sin_family=AF_INET;  
	servAddr.sin_addr.s_addr=htonl(INADDR_ANY);  
	servAddr.sin_port=htons(atoi(argv[1]));  

	if(bind(hSeverSock,(SOCKADDR*)&servAddr,sizeof(servAddr))==SOCKET_ERROR)  
		error_handling("bind error");  
	if(listen(hSeverSock,5)==SOCKET_ERROR)  
		error_handling("listen error");  

	szClntAddr=sizeof(clntAddr);  
	hClntSock=accept(hSeverSock,(SOCKADDR*)&clntAddr,&szClntAddr);  
	if(hClntSock==INVALID_SOCKET)  
		error_handling("accept error");  

	send(hClntSock,Message,sizeof(Message),0);  
	closesocket(hClntSock);  
	closesocket(hSeverSock);  
	if(WSACleanup()!=0)  
		error_handling("WSACleanup error");  
	getchar();  
	return 0;  
}  
void error_handling(char* message)  
{  
	fputs(message,stderr);  
	fputc('\n',stderr);  
	exit(1);  
}  