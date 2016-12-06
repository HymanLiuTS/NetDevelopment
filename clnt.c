#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<sys/socket.h>  
#include<arpa/inet.h>  

  
int main(int argc,char* argv[])
{
	pid_t pid;
	int sout,result;
	int sock;
	struct sockaddr_in addr;
	char buf[1024];
	sock=socket(AF_INET,SOCK_STREAM,0);
	memset(&addr,0,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr(argv[1]);
	addr.sin_port=htons(atoi(argv[2]));
	connect(sock,(struct sockaddr*)&addr,sizeof(addr));
	pid=fork();
	if(pid==0)
	{
		close(sock);
	}
	else
	{
		sleep(2);
		write(sock,"hello world\n",12);
		read(sock,buf,1024);
		fputs(buf,stdout);
	}
	return 0;
}

