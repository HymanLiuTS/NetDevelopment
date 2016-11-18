//////////////////////////////////////////////////////////////////////////
//////File: getsetopt.c
//////Description: 网络编程（9）—— 怎么获取和设置socket的输出\输入缓冲等多种可选项源代码
//////Author: Hyman
//////Date: 2016/11/18
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>

void error_handling(char* message);

int main(int argc,char* argv)
{
    //声明socket
    int tcp_sock,udp_sock;
    //socket类型
    int sock_type;
    //socket缓冲区大小
    int snd_buf,rev_buf;
    //可选项字节数
    socklen_t optlen;
    //getsockopt返回的状态，0表示获取成功
    int state;
    
    optlen=sizeof(sock_type);
    tcp_sock=socket(PF_INET,SOCK_STREAM,0);
    udp_sock=socket(PF_INET,SOCK_DGRAM,0);
    printf("SOCK_STREAM: %d\n",SOCK_STREAM);
    printf("SOCK_DGRAM: %d\n",SOCK_DGRAM);

    state=getsockopt(tcp_sock,SOL_SOCKET,SO_TYPE,&sock_type,&optlen);
    if(state)
        error_handling("getsockopt one error");
    printf("socket type one: %d\n",sock_type);

    state=getsockopt(udp_sock,SOL_SOCKET,SO_TYPE,&sock_type,&optlen);
    if(state)
        error_handling("getsockopt two error");
    printf("socket type two: %d\n",sock_type);

    optlen=sizeof(snd_buf);
    state=getsockopt(tcp_sock,SOL_SOCKET,SO_SNDBUF,&snd_buf,&optlen);
    if(state==0)
        printf("socket输出缓冲区大小是: %d\n",snd_buf);
    optlen=sizeof(rev_buf);
    state=getsockopt(tcp_sock,SOL_SOCKET,SO_RCVBUF,&rev_buf,&optlen);
    if(state==0)
        printf("socket输入缓冲区大小是: %d\n",rev_buf);

    printf("更改输入和输出缓冲区...\n");

    snd_buf=1024*3;
    rev_buf=1024*6;

    optlen=sizeof(snd_buf);
    state=setsockopt(tcp_sock,SOL_SOCKET,SO_SNDBUF,&snd_buf,optlen);
    if(state==0)
    {
        state=getsockopt(tcp_sock,SOL_SOCKET,SO_SNDBUF,&snd_buf,&optlen);
        printf("更改成功!\n");
        printf("更改后的输出缓冲区大小为:%d\n",snd_buf);
    }
    optlen=sizeof(rev_buf);
    state=setsockopt(tcp_sock,SOL_SOCKET,SO_RCVBUF,&rev_buf,optlen);
    if(state==0)
    {
        state=getsockopt(tcp_sock,SOL_SOCKET,SO_RCVBUF,&rev_buf,&optlen);
        printf("更改后的输入缓冲区大小为:%d\n",rev_buf);
    }
    return 0;
}

void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

