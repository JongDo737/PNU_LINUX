#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int status;
    if((status = system("date")) <0) {
        perror("system() 오류");
    }
    printf("종료코드 %d\n",WEXITSTATUS(status));

    if((status = system("hello")) <0) {
        perror("system() 오류");
    }
    printf("종료코드 %d\n",WEXITSTATUS(status));

    if((status = system("who; exit 44")) < 0) {
        perror("system() 오류");
    }
    printf("종료코드 %d\n",WEXITSTATUS(status));


    return 0;
}
