// _beginthreadTs.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Windows.h"  
#include "stdio.h"  
#include "process.h"  

void ThreadFunc(void* pargs)  
{  
	char* str=(char*)pargs;  
	puts(str);  
}  

int _tmain(int argc, _TCHAR* argv[])  
{  
	char* str="我是主线程传进来的字符串";  
	HANDLE hThread1 = (HANDLE)_beginthread(ThreadFunc,0,(void*)str);  
	Sleep(5000);  
	return 0;  
}  

