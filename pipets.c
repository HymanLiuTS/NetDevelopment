#include<stdio.h>
#include<unistd.h>

#define BUF_SIZE 30
int main()
{
    char buf[BUF_SIZE]="hello world";
    pid_t pid;
    int fds[2];
    pipe(fds);
    pid=fork();
    if(pid==0)
    {
        write(fds[1],buf,BUF_SIZE);
    }
    else
    {
        read(fds[0],buf,BUF_SIZE);
        puts(buf);
    }
    return 0;
}

