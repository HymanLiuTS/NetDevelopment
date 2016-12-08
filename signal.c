#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
void sig_handling(int sig)  
{  
    int status;  
    pid_t pid;  
    if(sig==SIGCHLD)  
    {  
        pid = waitpid(-1,&status,WNOHANG);  
        if(WIFEXITED(status))  
        {  
            printf("process %d exited,return value=%d\n",pid,WEXITSTATUS(status));  
        }  
    }  
}  
  
  
int main()  
{  
    pid_t pid;  
    signal(SIGCHLD,sig_handling);  
    pid=fork();  
    if(pid==0)  
    {  
        exit(11);  
    }  
    else  
    {  
        sleep(10000);  
    }  
    return 0;  
}  

