#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main()
{
    int sock1,sock2;
    sock1=socket(AF_INET,SOCK_STREAM,0);
    sock2=sock1;
    printf("sock1=%d\n",sock1);
    printf("sock2=%d\n",sock2);
    return 0;
}
