#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 30

void error_handling(char* message);

int main(int argc,char* argv[])
{
    int recv_sock;
    struct sockaddr_in recv_addr;
    char buf[BUF_SIZE];
    struct ip_mreq join_adr;
    int str_len;
    if(argc!=3)
    {
        printf("Usage %s <adress> <port>\n",argv[0]);
        exit(1);
    }
    recv_sock=socket(AF_INET,SOCK_DGRAM,0);

    recv_addr.sin_family=AF_INET;
    recv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    recv_addr.sin_port=htons(atoi(argv[2]));

    if(bind(recv_sock,(struct sockaddr*)&recv_addr,sizeof(recv_addr))==-1)
            error_handling("bind error");
    
    join_adr.imr_multiaddr.s_addr=inet_addr(argv[1]);
    join_adr.imr_interface.s_addr=htonl(INADDR_ANY);

    setsockopt(recv_sock,IPPROTO_IP,
                    IP_ADD_MEMBERSHIP,(void*)&join_adr,sizeof(join_adr));
    
    while(1)
    {
       str_len=recvfrom(recv_sock,buf,BUF_SIZE-1,MSG_DONTWAIT,NULL,0);
       printf("接收到 %d 字节。\n",str_len); 
       if(str_len<=0)
                break;

        buf[str_len]=0;
        fputs(buf,stdout);
    }
    
    close(recv_sock);

    return 0;
}

void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

