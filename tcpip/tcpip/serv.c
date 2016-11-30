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
	char buf[BUF_SIZE];
	int s_bro=1;
	if(argc!=3)
	{
		printf("Usage %s <address> <port>\n",argv[0]);
		//exit(1);
	}
	WSAStartup(MAKEWORD(2,2),&wsaData);

	sock=socket(AF_INET,SOCK_DGRAM,0);
	
	memset(&addr,0,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr("192.168.5.255");
	addr.sin_port=htons(atoi("8888"));

	setsockopt(sock,SOL_SOCKET,SO_BROADCAST,(void*)&s_bro,sizeof(s_bro));
	while(1)
	{
		fputs("input:",stdout);
		fgets(buf,BUF_SIZE,stdin);
		sendto(sock,buf,BUF_SIZE,0,(SOCKADDR*)&addr,sizeof(addr));
	}
	
}