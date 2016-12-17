#include<stdio.h>  
#include<pthread.h>  
#include<semaphore.h>  
int num=0;  
sem_t sem;  
void* pthread_main1()  
{  
    int i=0;  
    sem_wait(&sem);  
    for(i=0;i<1000000000;i++)  
    {  
        --num;  
    }  
    sem_post(&sem);  
}  
void* pthread_main2()  
{  
    int i=0;  
    sem_wait(&sem);   
    for(i=0;i<1000000000;i++)  
    {  
        ++num;  
    }  
    sem_post(&sem);   
}  
  
int main()  
{  
    int i=0;  
    sem_init(&sem,0,1);  
    pthread_t pid[2];  
    pthread_create((void*)&(pid[0]),NULL,(void*)pthread_main1,NULL);  
    pthread_create((void*)&(pid[1]),NULL,(void*)pthread_main2,NULL);  
    for(i=0;i<2;i++)  
    {  
        pthread_join(pid[i],NULL);  
    }  
    printf("%d\n",num);  
    sem_destroy(&sem);  
    return 0;  
}  

