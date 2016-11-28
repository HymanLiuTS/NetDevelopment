#include<stdio.h>
#include<string.h>
#include<sys/uio.h>
int main()
{
    struct iovec iv1,iv2;
    struct iovec iovs[2];

    iv1.iov_base="123456789\n";
    iv1.iov_len=strlen("123456789\n");

    iv2.iov_base="qwertyuiop\n";
    iv2.iov_len=strlen("qwertyuiop\n");

    iovs[0]=iv1;
    iovs[1]=iv2;

    writev(1,iovs,2);//1是标准输出缓冲区的文件描述符。
    return 0;
}
