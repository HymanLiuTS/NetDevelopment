#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<poll.h>

#define BUF_SIZE 30
#define POLL_SIZE 20


void error_handler(const char* message);
int main(int argc,char* argv[])
{
    int serv_sock,clnt_sock;
    struct sockaddr_in serv_addr,clnt_addr;
    int clnt_addr_sz,str_len;
    char buf[BUF_SIZE];

    struct pollfd fds[POLL_SIZE];
    int plnum,fpnum,i;

    if(argc!=2)
    {
        printf("Usage %s <port>\n",argv[0]);
        exit(1);
    }
    
    serv_sock=socket(AF_INET,SOCK_STREAM,0);
    
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));

    if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
        error_handler("bind error");

    if(listen(serv_sock,5)==-1)
        error_handler("listen error");

    for(i=0;i<POLL_SIZE;i++)
        fds[i].fd=-1;
    fds[0].fd=serv_sock;
    fds[0].events=POLLIN;
    fpnum=0; 
    while(1)
    {
        plnum=poll(fds,fpnum+1,INFTIM);
        printf("poll returned");
        if((fds[0].revents&POLLIN)==POLLIN)
        {
            clnt_addr_sz=sizeof(clnt_addr);
            clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_sz);
            for(i=0;i<POLL_SIZE;i++)
            {
                if(fds[i].fd<0)
                {
                    fds[i].fd=clnt_sock;
                    fds[i].events=POLLIN;
                }
            }
            if(fpnum<i)
                fpnum=i;
        }

        for(i=1;i<fpnum;i++)
        {
            if(fds[i].fd<0) continue;
            str_len=read(fds[i].fd,buf,BUF_SIZE);
            if(str_len<=0)
            {
                close(fds[i].fd);
                fds[i].fd==-1;
            }
            else
            {                     
                write(fds[i].fd,buf,str_len);
            }
        }
    }

    return 0;
}

void error_handler(const char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}
