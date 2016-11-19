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
int gval=10;
int main()
{
    int ival=100;
    int pid=fork();
    if(pid==0)//子进程
    {
        ival++;
    }
    else//父进程
    {
        gval++;
    }
    if(pid==0)
    {
        printf("child process: gval=%d,ival=%d\n",gval,ival);
    }
    else
    {
        printf("parent process: gval=%d,ival=%d\n",gval,ival);
    }
    return 0;
}

