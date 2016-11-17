//////////////////////////////////////////////////////////////////////////
//////File: clnt.c
//////Description: TCP socket客户端
//////Author: Hyman
//////Date: 2016/11/17
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<unistd.h>  
#include<arpa/inet.h>  
#include<sys/socket.h>  
  
#define BUF_SIZE 30  
  
void error_handling(char *message);  
  
int main(int argc,char * argv[])  
{  
    int serv_sock;  
    FILE* fp;  
    int read_cnt;  
    char buf[BUF_SIZE];  
  
    struct sockaddr_in serv_adr;  
    if(argc!=3)  
    {  
        printf("Usage %s <addr> <port>",argv[0]);  
        exit(1);  
    }  
    fp=fopen("recieve.dat","wb");  
    serv_sock=socket(AF_INET,SOCK_STREAM,0);  
  
    memset(&serv_adr,0,sizeof(serv_adr));  
    serv_adr.sin_family=AF_INET;  
    serv_adr.sin_addr.s_addr=inet_addr(argv[1]);  
    serv_adr.sin_port=htons(atoi(argv[2]));  
  
    connect(serv_sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr));  
      
    while((read_cnt=read(serv_sock,buf,BUF_SIZE))!=0)  
    {  
        fwrite((void*)buf,1,read_cnt,fp);  
        printf("read_cnt= %d\n",read_cnt);  
    }  
  
    puts("recieved all data");  
    write(serv_sock,"Thank you",10);  
    fclose(fp);  
    close(serv_sock);  
}  
  
  
void error_handling(char *message)  
{  
    fputs(message,stderr);  
    fputc('\n',stderr);  
    exit(1);  
}  

