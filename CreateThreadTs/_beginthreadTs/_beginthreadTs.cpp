// _beginthreadTs.cpp : �������̨Ӧ�ó������ڵ㡣
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
	char* str="�������̴߳��������ַ���";  
	HANDLE hThread1 = (HANDLE)_beginthread(ThreadFunc,0,(void*)str);  
	Sleep(5000);  
	return 0;  
}  

