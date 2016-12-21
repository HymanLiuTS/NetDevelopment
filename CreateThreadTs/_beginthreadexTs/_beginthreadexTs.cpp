// _beginthreadexTs.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Windows.h"  
#include "stdio.h"  
#include "process.h"  

unsigned WINAPI ThreadFunc1(void* pargs)  
{  
	while (1)  
	{  
		puts("ThreadFunc1 Run ...");  
		Sleep(1000);  
	}  
	return 0;  
}  
unsigned WINAPI ThreadFunc2(void* pargs)  
{  
	while(1)  
	{  
		puts("ThreadFunc2 Run ...");  
		Sleep(1000);  
	}  
	return 0;  
}  

int _tmain(int argc, _TCHAR* argv[])  
{  
	//创ä¡ä建¡§一°?个?线?程¨¬初?始º?状Á¡ä态¬?为a运?行D  
	HANDLE hThread1 = (HANDLE)_beginthreadex(NULL,0,ThreadFunc1,NULL,0,NULL);  
	//创ä¡ä建¡§另¢¨ª一°?个?线?程¨¬，ê?初?始º?状Á¡ä态¬?为a挂¨°起e  
	HANDLE hThread2 = (HANDLE)_beginthreadex(NULL,0,ThreadFunc2,NULL,CREATE_SUSPENDED,NULL);  

	Sleep(5000);  
	puts("ResumeThread ...");  
	ResumeThread(hThread2);  
	Sleep(10000);  
	return 0;  
}  
