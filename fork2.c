#include<unistd.h>
    #include<stdio.h>  
    #include<stdlib.h>  
    int main()  
    {  
        pid_t pid=fork();  
        if(pid==0)//子进程  
        {  
            printf("hi I'm a child process!\n");  
        }  
        else  
        {  
            printf("I'm parent process!\n");   
            sleep(30);  
        }  
        if(pid==0)  
            puts("End child process");  
        else  
            puts("End parent process");  
        return 0;  
    }  
