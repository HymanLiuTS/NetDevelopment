#include<stdio.h>  
int main()  
{  
int i=0;  
int* restrict pi=&i;  
int* pi1 = &i;  
*pi1 = 1;  
printf("i=%d\n",i);  
}  

