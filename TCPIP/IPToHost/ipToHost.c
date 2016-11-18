#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>
#include <ws2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

void error_handling(char *message);
int main(int argc,char* argv[])
{
	int i, errornm;
	WSADATA wsaData;
	struct hostent* host;
	struct in_addr addr={0};
	if(argc!=2)
	{
		//printf("Usage %s <port>",argv[0]);
		//exit(1);
	}
	WSAStartup(MAKEWORD(2,2),&wsaData);

	memset(&addr,0,sizeof(addr));
	addr.s_addr=inet_addr("14.215.177.37");
	host=gethostbyaddr((char*)&addr,4,AF_INET);
	if(!host)
	{
		errornm = WSAGetLastError();
		error_handling("gethostbyaddr error");
	}

	printf("official name is %s\n",host->h_name);
	for(i=0;host->h_aliases[i];i++)
	{
		printf("Aliases %d: %s\n",i+1,host->h_aliases[i]);
	}

	printf("Address type: %s\n",
		host->h_addrtype==AF_INET?"AF_INET":"AF_INET6");

	for(i=0;host->h_addr_list[i];i++)
	{
		printf("IP addr %d: %s \n",i+1,
			inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
	}
	WSACleanup();
	return 0;
}

void error_handling(char* message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(0);
}
