#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
/*
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
int fcntl(int fd, int cmd, struct flock *lock);
cmd에 따라 잠금 검사 혹은 잠금 설정을 한다. 성공하면 0, 실패하면 -1을 리턴
*/
int main(int argc, char const *argv[])
{
    int fd;
    struct flock *lock;
    if(fd = open(argv[1], O_WRONLY | O_CREAT, 0600)){
        printf("error");
        exit(1);
    }
    if(fcntl(fd, F_SETLK, lock) != 0) {
        printf("error");
        exit(1);
    }
    print("성공");
    




    return 0;
}
