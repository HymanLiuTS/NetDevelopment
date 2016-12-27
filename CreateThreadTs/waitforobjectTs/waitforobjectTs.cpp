// waitforobjectTs.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "windows.h"
#include<process.h>

unsigned WINAPI ThreadFunc1(void* args)
{
	int i=0;
	while(1)
	{

		puts("ThreadFunc1 called ...");
		if(++i==5)
		{
			puts("ThreadFunc1 Ended");
			ExitThread(1);
		}
		Sleep(1000);

	}
}
unsigned WINAPI ThreadFunc2(void* args)
{
	int i=0;
	while(1)
	{
		puts("ThreadFunc2 called ...");
		if(++i==10)
		{
			puts("ThreadFunc2 Ended");
			ExitThread(2);
		}
		Sleep(1000);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD thredID1,thredID2;
	HANDLE handles[2];
	handles[0]=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadFunc1,NULL,0,&thredID1);
	handles[1]=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadFunc2,NULL,0,&thredID2);
	DWORD dr = WaitForMultipleObjects(2,handles,true,INFINITE);
	if(dr==WAIT_OBJECT_0)
	{
		puts("两个内核对象都进入signaled状态");
	}
	else if(dr==WAIT_TIMEOUT)
	{
		puts("等待超时");
	}
	return 0;
}

