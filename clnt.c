    #include<stdio.h>  
    #include<stdlib.h>  
    #include<unistd.h>  
    #include<arpa/inet.h>  
    #include<sys/socket.h>  
    #include<string.h>  
      
    #define BUF_SIZE 30  
      
    void error_handling(char* message);  
      
      
    int main(int argc,char* argv[])  
    {  
        int serv_sock,clnt_sock;  
        struct sockaddr_in serv_addr,clnt_addr;  
        int clnt_addr_sz;  
        int str_len;  
        char buf[BUF_SIZE];  
        if(argc!=2)  
        {  
            printf("Usage %s <port>\n",argv[0]);  
            exit(1);  
        }  
        //创建socket  
        serv_sock=socket(AF_INET,SOCK_STREAM,0);  
        //设置地址  
        memset(&serv_addr,0,sizeof(serv_addr));  
        serv_addr.sin_family=AF_INET;  
        serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);  
        serv_addr.sin_port=htons(atoi(argv[1]));  
        //绑定  
        if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)  
                error_handling("bind error");  
        //开启监听  
        listen(serv_sock,5);  
        //接收链接  
        clnt_addr_sz=sizeof(clnt_addr);  
        clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_sz);  
          
        while(1)  
        {  
            str_len=recv(clnt_sock,buf,BUF_SIZE-1,MSG_PEEK|MSG_DONTWAIT);  
            if(str_len>0)  
                    break;  
        }  
        buf[str_len]=0;  
        puts(buf);  
        str_len=recv(clnt_sock,buf,BUF_SIZE-1,0);  
        buf[str_len]=0;  
        puts(buf);  
        return 0;  
    }  
    void error_handling(char* message)  
    {  
        fputs(message,stderr);  
        fputc('\n',stderr);  
        exit(1);  
    }  
