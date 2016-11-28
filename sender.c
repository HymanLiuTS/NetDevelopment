#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define BUF_SIZE 30
void error_handling(char* message);
int main(int argc,char* argv[])
{
    int target_sock;
    struct sockaddr_in target_addr;
    FILE* fp;
    char buf[BUF_SIZE];
    int time_live=64;
    if(argc!=3)
    {
        printf("Usage %s <address> <port> \n",argv[0]);
        exit(1);
    }
    target_sock=socket(AF_INET,SOCK_DGRAM,0);
    
    target_addr.sin_family=AF_INET;
    target_addr.sin_addr.s_addr=inet_addr(argv[1]);
    target_addr.sin_port=htons(atoi(argv[2]));
    
   fp=fopen("news.txt","r");
   if(fp==NULL)
   {
        error_handling("fopen error!");
   }

    setsockopt(target_sock,IPPROTO_IP,
                    IP_MULTICAST_TTL,(void*)&time_live,sizeof(time_live));

    while(!feof(fp))
    {
        fgets(buf,BUF_SIZE,fp);
        sendto(target_sock,buf,strlen(buf),
                        0,(struct sockaddr*)&target_addr,sizeof(target_addr));
        sleep(2);
    }

    fclose(fp);
    close(target_sock);
    return 0;
}
void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

