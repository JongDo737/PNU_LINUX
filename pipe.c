#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 100

/* ㅍ파이프를 통해 자식에서 부모로 데이터 보는 프로그램*/
int main(int argc, char const *argv[])
{
    /* code */
    int n, length, fd[2];
    int pid;
    char message[MAXLINE], line[MAXLINE];

    pipe(fd); /*파이프 생성*/
    if((pid = fork()) == 0) {   /* 자식 프로세스 */
        close[fd[0]];
        sprintf(message, "Hello from PID", getpid());
        length = strlen(message) +1;
        write(fd[1], line, MAXLINE);
    }else { /* 부모 프로세스*/
        close(fd[1]);
        n = read(fd[0], line, MAXLINE);
        printf("[%d] %s", getpid(), line);

    }
    exit(0);
}
