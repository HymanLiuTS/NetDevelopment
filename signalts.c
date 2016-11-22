//////////////////////////////////////////////////////////////////////////
//////File: getsetopt.c
//////Description: 网络编程（13）—— 利用信号处理函数销毁僵尸进程
//////Author: Hyman
//////Date: 2016/11/22
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
void timeout(int sig)
{
    if(sig==SIGALRM)
            puts("Time out");
    alarm(2);
}
void keycontrol(int sig)
{
    if(sig==SIGINT)
            puts("CTRL + C pressed");
}
int main()
{
    int i;
    signal(SIGALRM,timeout);
    signal(SIGINT,keycontrol);
    alarm(2);
    for(i=0;i<3;i++)
    {
        puts("wait...");
        sleep(100);
    }
    return 0;
}

