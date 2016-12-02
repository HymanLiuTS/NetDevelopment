#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<sys/socket.h>  
#include<arpa/inet.h>  
#include<time.h>  
#define BUF_SIZE 10000000  
  
void print_time();  
  
void error_handling(const char* message);  
  
int main(int argc,char* argv[])  
{  
    int sock;  
    struct sockaddr_in serv_addr;  
    int str_len;  
    char buf[BUF_SIZE];  
    int recv_len=0;  
    //创建socket  
    sock=socket(AF_INET,SOCK_STREAM,0);  
    if(sock==-1)  
        error_handling("socket error");  
  
    //准备地址  
    memset(&serv_addr,0,sizeof(serv_addr));  
    serv_addr.sin_family=AF_INET;  
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);  
    serv_addr.sin_port=htons(atoi(argv[2]));  
  
    //链接  
    if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)  
        error_handling("connect error");  
    else  
            puts("connect succeed");  
    while(1)  
    {  
        memset(buf,0,BUF_SIZE);  
        fputs("请输入数据:",stdout);  
        fgets(buf,BUF_SIZE,stdin);  
        if(!strcmp(buf,"q\n")||!strcmp(buf,"Q/n"))  
            break;  
  
        str_len=write(sock,buf,strlen(buf));  
        puts("writed,begin block");  
        print_time();  
        sizeof(buf,0,sizeof(buf));  
        while(recv_len<str_len)  
            recv_len+=read(sock,buf,BUF_SIZE-1);  
        puts("end block");  
        print_time();  
        buf[str_len]=0;  
        printf("服务器传回信息:%s\n",buf);  
    }  
    close(sock);  
    return 0;  
}  
  
void print_time()  
{  
  time_t now=time(0);  
    struct tm* ptm=localtime(&now);  
    char buf[256]={0};  
    sprintf(buf,"time now:[%02d-%02d-%02d %02d:%02d:%02d]",  
        ptm->tm_year+1900,  
            ptm->tm_mon+1,  
            ptm->tm_mday,  
            ptm->tm_hour,  
            ptm->tm_min,  
            ptm->tm_sec);  
    puts(buf);  
}  
  
void error_handling(const char* message)  
{  
    fputs(message,stderr);  
    fputc('\n',stderr);  
    exit(1);  
}  


