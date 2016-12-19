#include<stdio.h>
#include<pthread.h>
int flag=0;
void* pthread_main()
{	
        int i=0;	
        for(i=0;i<5;i++)	
        {		
                puts("pthread_main called...");		
                sleep(1);	
        }	
        flag=1;
}
int main()
{	
        pthread_t tid;	
        pthread_create(&tid,NULL,(void*)pthread_main,NULL);	
        pthread_detach(tid);	
        while(!flag)	
        {		
                sleep(1);		
                puts("waiting child thread edned!");	
        }	
        return 0;
}
