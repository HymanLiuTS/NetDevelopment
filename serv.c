    #include<stdio.h>  
    #include<stdlib.h>  
    #include<sys/socket.h>  
    #include<arpa/inet.h>  
    #include<unistd.h>  
    #include<string.h>  
      
    void error_handling(char* message);  
      
    int main(int argc,char* argv[])  
    {  
        int sock;  
        struct sockaddr_in serv_addr;  
        if(argc!=3)  
        {  
            printf("Usage %s <address> <port>",argv[0]);  
            exit(1);  
        }  
        //创建socket  
        sock=socket(AF_INET,SOCK_STREAM,0);  
        //准备地址信息  
        memset(&serv_addr,0,sizeof(serv_addr));  
        serv_addr.sin_family=AF_INET;  
        serv_addr.sin_addr.s_addr=inet_addr(argv[1]);  
        serv_addr.sin_port=htons(atoi(argv[2]));  
        //连接服务器  
        if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)  
                error_handling("connect error");  
        write(sock,"123",strlen("123"));  
        return 0;  
    }  
      
    void error_handling(char* message)  
    {  
        fputs(message,stderr);      
        fputc('\n',stderr);  
        exit(1);  
    }  
