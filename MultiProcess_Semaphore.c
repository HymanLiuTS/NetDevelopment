#include<stdio.h>  
#include<stdlib.h>  
#include<pthread.h>  
#include<semaphore.h>  
#include<string.h>  
#include<sys/mman.h>  
#include<unistd.h>  
#include<sys/types.h>  
#include<sys/stat.h>  
#include<fcntl.h>  
#define BUF_SIZE 30  
  
void readfile(sem_t* psem1,sem_t* psem2)  
{  
    FILE* fp;  
    char buf[BUF_SIZE];  
    int str_len,str_seek=0;  
    while(1)  
    {  
        sem_wait(psem1);  
        fp=fopen("data.txt","r+");  
        if(fp==NULL)  
        return ;  
        memset(buf,0,sizeof(BUF_SIZE));  
        fseek(fp,str_seek,SEEK_SET);  
        str_len=fread(buf,sizeof(char),BUF_SIZE-1,fp);  
        buf[str_len]=0;  
        str_seek+=str_len;  
        fputs("output:",stdout);  
        puts(buf);  
        fclose(fp);  
        sem_post(psem2);  
    }  
}  
void writefile(sem_t* psem1,sem_t* psem2)  
{  
        FILE* fp;  
        char buf[BUF_SIZE];  
        while(1)  
        {  
            sem_wait(psem2);  
            fp=fopen("data.txt","a");  
            if(fp==NULL)  
            return;  
            memset(buf,0,BUF_SIZE);  
            fputs("Input:",stdout);  
            fgets(buf,BUF_SIZE,stdin);  
            fwrite(buf,sizeof(char),strlen(buf),fp);  
            fclose(fp);  
            sem_post(psem1);  
        }  
}  
  
int main()  
{  
    int pid;  
    int fd1,fd2;  
    void* pv;  
    sem_t* psem1;  
    sem_t* psem2;  
    fd1=open("data1",O_CREAT|O_RDWR|O_TRUNC,0666);  
    fd2=open("data2",O_CREAT|O_RDWR|O_TRUNC,0666);  
    ftruncate(fd1,8192);  
    ftruncate(fd2,8192);  
    //lseek(fd,5000,SEEK_SET);  
    psem1=(sem_t*)mmap(NULL,sizeof(sem_t),PROT_READ|PROT_WRITE,MAP_SHARED,fd1,0);  
    psem2=(sem_t*)mmap(NULL,sizeof(sem_t),PROT_READ|PROT_WRITE,MAP_SHARED,fd2,0);  
    sem_init(psem1,1,0);  
    sem_init(psem2,1,1);  
    pid=fork();  
    if(pid==0)  
    {  
        puts("进入子进程");  
        writefile(psem1,psem2);  
    }  
    else  
    {  
        puts("进入父进程");  
        readfile(psem1,psem2);  
    }  
    sem_destroy(psem1);  
    sem_destroy(psem2);  
    munmap(psem1,sizeof(sem_t));  
    munmap(psem2,sizeof(sem_t));  
    close(fd1);  
    close(fd2);  
    return 0;   
} 

