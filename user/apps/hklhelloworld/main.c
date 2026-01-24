
#include <sys/syscall.h>
#include <stdio.h>

int main()
{
    printf("Hello World!\n");
    unsigned int ret=syscall(2333);
    printf("Systemcall %d \n",ret);
    return 0;
}

