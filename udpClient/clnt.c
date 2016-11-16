//////////////////////////////////////////////////////////////////////////
//////File: clnt.c
//////Description: UDP¿Í»§¶Ë´úÂë
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
	SOCKET servSock;  
	SOCKADDR_IN servAdr;  
	char message[BUF_SIZE]="hello world\n";  
	int strLen;  

	if(argc!=3)  
	{  
		printf("Usage %s <ip> <port>",argv[0]);  
		//exit(1);  
	}  

	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)  
	{  
		error_handling("WSASatrtup error");  
	}  
	servSock=socket(PF_INET,SOCK_DGRAM,0);  
	if(servSock==INVALID_SOCKET)  
	{  
		error_handling("socket error");  
	}  

	memset(&servAdr,0,sizeof(servAdr));  
	servAdr.sin_family=AF_INET;  
	servAdr.sin_addr.s_addr=inet_addr("127.0.0.1");  
	servAdr.sin_port=htons(atoi("9190"));  

	connect(servSock,(SOCKADDR*)&servAdr,sizeof(servAdr));  

	while(1)  
	{  
		memset(message,0,BUF_SIZE);  
		fputs("client(q to quit): ",stdout);  
		fgets(message,BUF_SIZE,stdin);  
		if(!strcmp(message,"q")||!strcmp(message,"Q\n"))  
		{  
			break;  
		}  
		send(servSock,message,strlen(message),0);  
		memset(message,0,BUF_SIZE);  
		strLen=recv(servSock,message,BUF_SIZE-1,0);  
		message[strLen]=0;  
		printf("server: %s\n",message);  
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