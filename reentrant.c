//////////////////////////////////////////////////////////////////////////
//////Description: 使用线程安全函数
//////Author: Hyman
//////Date: 2016/12/14
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#define _REENTRANT
#include<stdio.h>
#include<pthread.h>
#include<netdb.h>
void* pthread_main(void* param)
{
    struct hostent* pent;
    char* name = (char*)param;
    pent=gethostbyname(name);
    printf("the ip is: %s \n",
			inet_ntoa(*((struct in_addr*)pent->h_addr_list[0])));
}
int main()
{
	int i=0;
	pthread_t pid[2];
	char* name1="localhost";
	char* name2="www.baidu.com";
	pthread_create(&pid[0],NULL,(void*)pthread_main,(void*)name1);
	pthread_create(&pid[1],NULL,(void*)pthread_main,(void*)name2);
	for(i=0;i<2;i++)
	{
		pthread_join(pid[i],NULL);
	}
    return 0;
}

