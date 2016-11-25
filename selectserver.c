//////////////////////////////////////////////////////////////////////////
//////File: selectserver
//////Description: 一个使用select进行IO复用的socket服务端。
//////Author: Hyman
//////Date: 2016/11/25
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/select.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define BUF_SIZE 30

void error_handling(char* message);

int main(int argc,char* argv[])
{
    int serv_sock,clnt_sock;
    struct sockaddr_in serv_addr,clnt_addr;
    int addr_sz;
    fd_set reads,copy_reads;
    int fd_max;
    struct timeval timeout;
    int fd_num,i;
    int str_len;
    char buf[BUF_SIZE];
    if(argc!=2)
    {
        printf("Uasge %s <port>\n",argv[0]);
        exit(1);
    }

    //创建socket
    serv_sock=socket(AF_INET,SOCK_STREAM,0);
    //准备地址
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));
    //绑定
    if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
    {
        error_handling("bind error");
    }
    //监听
    if(listen(serv_sock,5)==-1)
    {
        error_handling("listen error");
    }
    FD_ZERO(&reads);
    FD_SET(serv_sock,&reads);
    fd_max=serv_sock;
    while(1)
    {
        copy_reads=reads;
        timeout.tv_sec=5;
        timeout.tv_usec=0;
        
        if((fd_num=select(fd_max+1,&copy_reads,0,0,&timeout))==-1)
                break;
        if(fd_num==0)
                continue;

        for(i=0;i<fd_max+1;i++)
        {
            if(FD_ISSET(i,&copy_reads))
            {
                if(i==serv_sock)
                {
                    addr_sz=sizeof(clnt_addr);
                    //接收连接
                    clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&addr_sz);
                    FD_SET(clnt_sock,&reads);
                    if(fd_max<clnt_sock)
                            fd_max=clnt_sock;
                    printf("connected client: %d \n",clnt_sock);
                }
                else
                {
                    str_len=read(i,buf,BUF_SIZE);
                    if(str_len==0)
                    {
                        FD_CLR(i,&reads);
                        close(i);
                        printf("close client: %d\n",i);
                    }
                    else
                    {
                        write(i,buf,str_len);
                    }
                }
            }
        }

    }
    close(serv_sock);
    return 0;
}

void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}



