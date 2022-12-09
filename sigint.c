#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void intHandler(int signo) {
    printf("Ctrl+C");
    printf("시그널 번호 : %d", signo);
    exit(0);
}

int main(int argc, char const *argv[])
{
    
    signal(SIGINT, intHandler);

    while(1) {
        pause();
    }
    printf("실행안됌");
    return 0;
}
