#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/epoll.h>
#include<string.h>

#define BUF_SIZE 30
#define EPOLL_SIZE 30

int main()
{
    int serv_sock,clnt_sock;
    struct sockaddr_in serv_addr,clnt_addr;
    int clnt_addr_sz,str_len;
    char buf[BUF_SIZE];
    
    int ep_fd,event_cnt,i;
    struct epoll_event event;
    struct epoll_event* pevents;

    serv_sock=socket(AF_INET,SOCK_STREAM,0);

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi("8888"));

    bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    listen(serv_sock,5);
    
    ep_fd=epoll_create(EPOLL_SIZE);
    pevents=malloc(sizeof(event)*EPOLL_SIZE);

    event.events=EPOLLIN;
    event.data.fd=serv_sock;
    epoll_ctl(ep_fd,EPOLL_CTL_ADD,serv_sock,&event);
    
    while(1)
    {
        event_cnt=epoll_wait(ep_fd,pevents,EPOLL_SIZE,-1);
        for(i=0;i<event_cnt;i++)
        {
            if(serv_sock==pevents[i].data.fd)
            {
                clnt_addr_sz=sizeof(clnt_addr);
                clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_sz);
                event.events=EPOLLIN;
                event.data.fd=clnt_sock;
                epoll_ctl(ep_fd,EPOLL_CTL_ADD,clnt_sock,&event);
            }
            else
            {
                str_len = read(pevents[i].data.fd,buf,1);
                if(str_len<=0)
                {
                    close(pevents[i].data.fd);
                    epoll_ctl(ep_fd,EPOLL_CTL_DEL,pevents[i].data.fd,NULL);
                }
                buf[str_len]=0;
                printf("epoll_wait() called,recv:%s\n",buf);
                write(pevents[i].data.fd,buf,str_len);
            }
        }
    }

    close(serv_sock);
    close(ep_fd);
    return 0;
}

