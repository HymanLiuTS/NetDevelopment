#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/select.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/epoll.h>
#define BUF_SIZE 30

void error_handling(char* message);

int main(int argc,char* argv[])
{
    int serv_sock,clnt_sock;
    struct sockaddr_in serv_addr,clnt_addr;
    int clnt_addr_sz;
    int epoll_fd;
    struct epoll_event event;
    struct epoll_event* pevents;
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
    //创建epoll描述符,以及用来接收发生变化事件的数组，空间占用50个字节
    epoll_fd=epoll_create(50);
    pevents=malloc(sizeof(struct epoll_event)*50);
    //利用epoll_ctl注册socket描述符
    event.events=EPOLLIN;
    event.data.fd=serv_sock;
    epoll_ctl(epoll_fd,EPOLL_CTL_ADD,serv_sock,&event);
    while(1)
    {
        //等待socket状态的变化，返回发生状态变化的文件描述符数
        fd_num=epoll_wait(epoll_fd,pevents,50,-1);
        puts("wait succeed");
        for(i=0;i<fd_num;i++)
        {
            if(serv_sock==pevents[i].data.fd)
            {
                clnt_addr_sz=sizeof(clnt_addr);
                clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_sz);
                puts("accept succeed");
                //把客户端添加到监视事件中
                event.events=EPOLLIN;
                event.data.fd=clnt_sock;
                epoll_ctl(epoll_fd,EPOLL_CTL_ADD,clnt_sock,&event);
            }
            else
            {
                str_len=read(pevents[i].data.fd,buf,BUF_SIZE);
                if(str_len==0)
                {
                    epoll_ctl(epoll_fd,EPOLL_CTL_DEL,pevents[i].data.fd,NULL);
                    close(pevents[i].data.fd);
                }
                else
                {
                    printf("client:%s\n",buf);
                    write(pevents[i].data.fd,buf,str_len);
                }
            }
        }


    }
    close(epoll_fd);
    close(serv_sock);
    return 0;
}

void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

