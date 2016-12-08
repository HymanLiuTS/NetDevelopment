#include<stdio.h>
#include<stdlib.h>
int main()  
{  
    pid_t pid;  
    int status;  
    pid=fork();  
    if(pid==0)  
    {  
        sleep(10);  
        exit(10);  
    }  
    else  
    {  
        while((pid=waitpid(-1,&status,WNOHANG))==0)  
        {  
            puts("wating ...");  
            sleep(2);  
        }  
        if(WIFEXITED(status))  
        {  
            printf("process %d exited,return value = %d\n",pid,WEXITSTATUS(status));  
        }  
    }  
    return 0;  
}  

