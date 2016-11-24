#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 30

void error_handling(char* message);
void read_childproc(int sig);
int main(int argc,char* argv[])
{
    struct sigaction act;
    int state;
    int servSock,clntSock;
    int adrSize;
    pid_t pid;
    int strLen;
    int fds[2];
    struct sockaddr_in servAddr,clntAddr;
    char buf[BUF_SIZE];
    if(argc!=2)
    {
        printf("Usage %s <port>\n",argv[0]);
        exit(1);
    }
    
    act.sa_handler=read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    state=sigaction(SIGCHLD,&act,0);
    //创建socket
    servSock=socket(AF_INET,SOCK_STREAM,0);

    //创建地址
    servAddr.sin_family=AF_INET;
    servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servAddr.sin_port=htons(atoi(argv[1]));
    
    //进行地址的binding
    if(bind(servSock,(struct sockaddr*)&servAddr,sizeof(servAddr))==-1)
        error_handling("bind() error");
    
    //开启监听
    if(listen(servSock,5)==-1)
            error_handling("listen error");

    //创建管道
    pipe(fds);
    pid=fork();
    if(pid==0)
    {
        FILE* fp=fopen("message.txt","a");
        int i;
        int len;
        if(fp==NULL)
        {
            return 0;
        }
        for(i=0;i<10;i++)
        {
            len=read(fds[0],buf,BUF_SIZE);
            fwrite(buf,1,len,fp);
            printf("保存客户端第%d次数据\n",i+1);
        }
        fclose(fp);
        return 0;
    }
    //接收客户端连接
    while(1)
    {
        adrSize=sizeof(clntAddr);
        clntSock=accept(servSock,(struct sockaddr*)&clntAddr,&adrSize);
        if(clntSock==-1)
            continue;
        else
            puts("new client connected ...");

        pid=fork();
        if(pid==-1)
        {
            close(clntSock);
            continue;
        }
        if(pid==0)
        {
            close(servSock);
            while((strLen=read(clntSock,buf,BUF_SIZE))!=0)
            {
                write(fds[1],buf,strLen);
                write(clntSock,buf,strLen);
            }
            close(clntSock);
            puts("client disconnected ...");
            return 0;
        }
        else
        {
            close(clntSock);
        }
    }
    close(servSock);
    return 0;
}



void read_childproc(int sig)
{
    pid_t pid;
    int status;
    pid=waitpid(-1,&status,WNOHANG);
    printf("removed proc id:%d \n",pid);
}


void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

