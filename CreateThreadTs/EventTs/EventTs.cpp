// EventTs.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"  
#include "windows.h"  
#include "iostream"  

int g_i=0;  
HANDLE evt;  

unsigned WINAPI AddThreadFunc(void* param)  
{  
	WaitForSingleObject(evt,INFINITE);  
	ResetEvent(evt);  
	for (int i=0;i<1000000;i++)  
	{  
		g_i++;  
	}  
	SetEvent(evt);  
	return 0;  
}  
unsigned WINAPI DevThreadFunc(void* param)  
{  
	WaitForSingleObject(evt,INFINITE);  
	ResetEvent(evt);  
	for (int i=0;i<1000000;i++)  
	{  
		g_i--;  
	}  
	SetEvent(evt);  
	return 0;  
}  
int _tmain(int argc, _TCHAR* argv[])  
{  
	evt=CreateEvent(NULL,true,false,NULL);  
	HANDLE handles[2];  
	handles[0] = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)AddThreadFunc,NULL,0,NULL);  
	handles[1] = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)DevThreadFunc,NULL,0,NULL);  
	SetEvent(evt);  
	WaitForMultipleObjects(2,handles,true,INFINITE);  
	std::cout<<"g_i="<<g_i<<std::endl;  
	CloseHandle(evt);
	return 0;  
} 
