#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
int main (int argc, char ** argv){

    int fd;

    /*잠금 동작*/
    fd = open(argv[1], O_WRONLY | O_CREAT, 0600);
    if(flock(fd, LOCK_EX) != 0) {
        printf("flock error\n");
        exit(0);
    }

    /* 자신의 프로세스 번호를 리턴*/
    for(int i=0; i<5; i++) {
        printf("file lock %d : %d", getpid(), i);
        sleep(1);
    }

    /* 잠금 해제 */
    if(flock(fd,LOCK_UN) != 0) {
        printf("unlock error\n");
    }
}