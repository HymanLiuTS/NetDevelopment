#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib")

#define BUF_SIZE 30

int main(int argc,char* argv[])
{
	WSADATA wsaData;
	SOCKET sock;
	SOCKADDR_IN addr;
	int addrSize;
	char buf[BUF_SIZE];
	int strLen;
	if(argc!=3)
	{
		printf("Usage %s <address> <port>\n",argv[0]);
		//exit(1);
	}
	WSAStartup(MAKEWORD(2,2),&wsaData);

	sock=socket(AF_INET,SOCK_DGRAM,0);

	memset(&addr,0,sizeof(addr));

	while(1)
	{
		strLen=recvfrom(sock,buf,BUF_SIZE-1,0,(SOCKADDR*)&sock,&addrSize);
		if(strLen>0)
		{
			buf	[strLen]=0;
			fputs(buf,stdout);
		}
		
	}

}