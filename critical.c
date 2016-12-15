#include<stdio.h>
#include<pthread.h>
int num=0;
void* pthread_main1()
{
    int i=0;
    for(i=0;i<1000000000;i++)
    {
         num++;
    }
}

void* pthread_main2()
{
    int i=0;
    for(i=0;i<1000000000;i++)
    {
        num--;
    } 
}
int main()
{
    int i=0;
    pthread_t pid[2];
    pthread_create((void*)&(pid[0]),NULL,(void*)pthread_main1,NULL);
    pthread_create((void*)&(pid[1]),NULL,(void*)pthread_main2,NULL);
    for(i=0;i<2;i++)
    {
        pthread_join(pid[i],NULL);
    }
    printf("%d\n",num);
    return 0;
}

