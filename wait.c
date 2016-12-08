#include<stdio.h>
#include<stdlib.h>
int main()  
{  
    pid_t pid;  
    int status;  
    pid=fork();  
    if(pid==0)  
    {  
        exit(10);  
    }  
    else  
    {  
        pid = wait(&status);  
        if(WIFEXITED(status))  
        {  
            printf("process %d exited,return value = %d\n",pid,WEXITSTATUS(status));  
        }  
    }  
    return 0;  
}  

