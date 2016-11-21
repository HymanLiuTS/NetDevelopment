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
        while(waitpid(pid,&status,WNOHANG)==0)  
        {  
            printf("主进程sleep 4秒\n");  
            sleep(4);  
        }  
        if(WIFEXITED(status))  
                printf("子进程返回值:%d\n",WEXITSTATUS(status));  
    }  
    return 0;  
}  

