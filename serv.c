#include<stdio.h>  
#include<stdlib.h>  
#include<unistd.h>  
#include<sys/socket.h>  
#include<string.h>  
#include<sys/un.h>//头文件发生了变化  
#define BUF_SIZE 1024  
   
void error_handling(const char* message);  
int main()  
{  
   int serv_sock,clnt_sock;  
     //采用的地址结构体不再是sockaddr_in,而是sockaddr_un  
   struct sockaddr_un serv_addr,clnt_addr;  
   int  clnt_addr_sz,str_len;  
    char buf[BUF_SIZE];  
   char * path="sock";  
                   //创建socket时，协议族改为AF_UNIX  
   serv_sock=socket(AF_UNIX,SOCK_STREAM,0);  
   //填写的地址信息发生变化，没有了IP地址和端口号而是通过本地文件为媒介进行通信  
   serv_addr.sun_family=AF_UNIX;  
   strncpy(serv_addr.sun_path,path,strlen(path));  
   
   if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)  
       error_handling("bind() error");  
   
   if(listen(serv_sock,1)==-1)  
       error_handling("listen() error");  
     
   clnt_addr_sz=sizeof(clnt_addr);  
   if((clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_sz))==-1)  
       error_handling("accept() error");  
     
   while(1)  
    {  
       str_len = read(clnt_sock,buf,BUF_SIZE);  
       if(str_len<=0)  
           break;  
       write(clnt_sock,buf,str_len);  
    }  
   
   close(clnt_sock);  
   close(serv_sock);    
   return 0;  
}  
void error_handling(const char* message)  
{  
   fputs(message,stderr);  
   fputc('\n',stderr);  
   exit(1);  
}  

