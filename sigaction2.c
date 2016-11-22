//////////////////////////////////////////////////////////////////////////
//////File: getsetopt.c
//////Description: 网络编程（13）—— 利用信号处理函数销毁僵尸进程
//////Author: Hyman
//////Date: 2016/11/22
//////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>

void childproHandler(int sig)
{
    int status;
    pid_t pid;
    if(sig==SIGCHLD)
    {
        pid = waitpid(-1,&status,WNOHANG);
        if(WIFEXITED(status))
        {
            printf("removed prc id:%d \n",pid);
            printf("child send:%d \n",WEXITSTATUS(status));
        }
    }
}

int main()
{
    pid_t pid;
    struct sigaction act;
    act.sa_handler=childproHandler;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    sigaction(SIGCHLD,&act,0);
    pid=fork();
    if(pid==0)
    {
        puts("I'm child process");
        sleep(10);
        return 12;
    }
    else
    {
        printf("child process id %id\n",pid);
        pid=fork();
        if(pid==0)
        {
            puts("I'm child process");
            sleep(10);
            exit(24);
        }
        else
        {
            int i=0;
            printf("child process id:%d\n",pid);
            for(i=0;i<5;i++)
            {
                puts("wait ...");
                sleep(5);
            }
        }
    }
    return 0;
}

