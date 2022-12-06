#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
/*
#include <sys/file.h>
int flock(int fd, int operation)
이 함수는 열려진 파일에 대해서 잠금을 적용하거나 해제하는 일을 수행한다.
성공하면 0을 리턴하고, 에러 발생 시에는 음수 값을 리턴
*/
int main(int argc, char **argv)
{
    int fd;
    fd = open(argv[1], O_WRONLY | O_CREAT , 0600);
    if(flock(fd, LOCK_EX) != 0) {
        printf("error");
        exit(1);
    }
    for(int i=0; i<5; i++) {
        printf("file lock %d : %d", getpid(), i);
        sleep(1);
    }

    if(flock(fd,LOCK_UN) != 0) {
        printf("unlock error");
    }
    return 0;
}
