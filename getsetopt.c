//////////////////////////////////////////////////////////////////////////
//////File: getsetopt.c
//////Description: 网络编程（10）——  通过设置可选项取消socket的TImeWait状态以及开启Nagle算法
//////Author: Hyman
//////Date: 2016/11/19
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<linux/tcp.h>
#define TRUE 1
#define FLASE 0
void error_handling(char* message);

int main(int argc,char* argv[])
{
    int serv_sock,clnt_sock;
    char message[30];
    struct sockaddr_in serv_addr,clnt_addr;
    int clntAdrLen,strLen,optlen,option;
    if(argc!=2)
    {
        printf("Usage %s <port>\n",argv[0]);
        exit(1);
    }
    
    //创建socket
    serv_sock=socket(AF_INET,SOCK_STREAM,0);
    if(serv_sock==-1)
            error_handling("socket error");
    
    //设置Time_Wait状态下套接字可重新分配
    optlen=sizeof(option);
    option=TRUE;
    setsockopt(serv_sock,SOL_SOCKET,SO_REUSEADDR,(void*)&option,optlen);

    //设置Nagle算法禁用
    optlen=sizeof(option);
    optlen=TRUE;
    setsockopt(serv_sock,IPPROTO_TCP,TCP_NODELAY,(void*)&option,optlen);

    //准备通信地址
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));

    //socket和通信地址的bind
    if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))!=0)
        error_handling("bind error");
    
    //监听
    if(listen(serv_sock,5)==-1)
            error_handling("listen error");
    
    //接收连接
    clntAdrLen=sizeof(clnt_addr);
    clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clntAdrLen);
    
    //读取数据
    while((strLen=read(clnt_sock,message,sizeof(message)))!=0)
    {
        printf("sizeof(message) = %d\n",sizeof(message));
        printf("接收到的数据是:%s 数据长度:%d\n",message,strLen);
        write(clnt_sock,message,strLen);
        //write(1,message,strLen);
        fputs("回送成功。",stdout);
        fputc('\n',stdout);
    }
    
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

