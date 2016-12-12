#include<stdio.h>  
#include<stdlib.h>  
#include<pthread.h>  
void pthread_main(int* pmax)  
{  
int i=0;  
for(i=0;i<*pmax;i++)  
{  
puts("child thread called ...");  
sleep(1);  
}  
}  
int main()  
{  
pthread_t ptid;  
int i=10;  
if(pthread_create(&ptid,NULL,(void*)pthread_main,(void*)&i) != 0)  
{  
puts("pthread_create() error");  
exit(1);  
}  
sleep(11);  
return 0;  
}  

