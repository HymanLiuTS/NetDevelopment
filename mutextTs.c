#include<stdio.h>
#include<pthread.h>
int num=0;
pthread_mutex_t mutex;
void* pthread_main1()
{
    int i=0;
    pthread_mutex_lock(&mutex);
    for(i=0;i<1000000000;i++)
    {
        --num;
    }
    pthread_mutex_unlock(&mutex);
}

void* pthread_main2()
{
    int i=0;
    pthread_mutex_lock(&mutex);
    for(i=0;i<1000000000;i++)
    {
        ++num;
    }
    pthread_mutex_unlock(&mutex);
}



int main()
{
    int i=0;
    pthread_mutex_init(&mutex,NULL);
    printf("mutex=%d\n",mutex);
    pthread_t pid[2];
    pthread_create((void*)&(pid[0]),NULL,(void*)pthread_main1,NULL);
    pthread_create((void*)&(pid[1]),NULL,(void*)pthread_main2,NULL);
    for(i=0;i<2;i++)
    {
        pthread_join(pid[i],NULL);
    }
    printf("%d\n",num);
    pthread_mutex_destroy(&mutex);
    return 0;
}

