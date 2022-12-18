#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main(void){
    int pid1, pid2;

    printf("11111 %d\n", getpid());
    if(pid1 = fork() == 0) 
        printf("22222 %d\n", getpid());
    sleep(1);

    pid2 = fork();
    printf("3333333 %d \n", getpid());
    return 0;
}