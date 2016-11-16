//////////////////////////////////////////////////////////////////////////
//////File: clnt.c
//////Description: UDP·þÎñ¶Ë´úÂë
//////Author: Hyman
//////Date: 2016/11/16
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#include<stdio.h>  
#include<stdlib.h>  
#include <string.h>  
#include<winsock2.h>  
#pragma comment(lib,"ws2_32.lib")

#define BUF_SIZE 30  

void error_handling(char* message);  
int main(int argc,char* argv[])  
{  
	WSADATA wsaData;  
	SOCKET  servSock;  
	char message[BUF_SIZE];  
	int strLen;  
	int clntAdrSz;  

	SOCKADDR_IN servAdr,clntAdr;  

	if(argc!=2)  
	{  
		printf("Usage %s <Port>",argv[0]);  
		//exit(1);  
	}  

	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)  
		error_handling("WSASatrt() error");  
	servSock=socket(PF_INET,SOCK_DGRAM,0);  
	if(servSock==INVALID_SOCKET)  
	{  
		error_handling("udp socket createtion error");  
	}  

	memset(&servAdr,0,sizeof(servAdr));  
	servAdr.sin_family=AF_INET;  
	servAdr.sin_addr.s_addr=htonl(INADDR_ANY);  
	servAdr.sin_port=htons(atoi("9190"));  

	if(bind(servSock,(SOCKADDR*)&servAdr,sizeof(servAdr))==SOCKET_ERROR)  
	{  
		error_handling("bind error");  
	}  

	while(1)  
	{  
		memset(message,0,BUF_SIZE);  
		clntAdrSz=sizeof(clntAdr);  
		strLen=recvfrom(servSock,message,BUF_SIZE-1,0,  
			(SOCKADDR*)&clntAdr,&clntAdrSz);  
		message[strLen]=0;  
		printf("client: %s",message);  
		memset(message,0,BUF_SIZE);  
		fputs("server: ",stdout);  
		fgets(message,BUF_SIZE,stdin);  
		sendto(servSock,message,strlen(message),0,  
			(SOCKADDR*)&clntAdr,sizeof(clntAdr));  
	}  
	closesocket(servSock);  
	WSACleanup();  
	return 0;  
}  

void error_handling(char* message)  
{  
	fputs(message,stderr);  
	fputc('\n',stderr);  
	exit(1);  
}  