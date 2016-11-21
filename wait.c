//////////////////////////////////////////////////////////////////////////
//////File: getsetopt.c
//////Description: 网络编程（11）——  进程和僵尸进程
//////Author: Hyman
//////Date: 2016/11/19
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
    int status;
    pid_t pid=fork();
    if(pid==0)
    {
        sleep(20);
        return 3;
    }
    else
    {
        printf("当前子进程ID:%d\n",pid);
        wait(&status);
        if(WIFEXITED(status))
                printf("子进程返回值:%d\n",WEXITSTATUS(status));
    }
    return 0;
}


