#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 100
char* exitTrigger = "EXIT";

int main(int argc, char* argv[]) 
{
   int n, pid, fd1[2], fd2[2], i;
   char line[MAXLINE];
   char input[MAXLINE];
   char result[MAXLINE];

   pipe(fd1);
   pipe(fd2);
   pid = fork();
    
   if (pid == 0) {      // 자식일 때
        close(fd1[0]);
        close(fd2[1]);
      while(1){     
        fgets(input, MAXLINE, stdin);
        write(fd1[1],input,strlen(input)+1);
        printf("%s",result);
      }
    } else {       // 부모일 때           
        close(fd1[1]);
        close(fd2[0]);
        while ((n = read(fd1[0], line, MAXLINE)) > 0){ 
            i=0;
            // 대문자 출력
            while(line[i]!='\0'){
                line[i]=toupper(line[i]);
                i++;
            }
            printf("%s",line);
            if(strncmp(line,exitTrigger,4)==0) {
                break;
            }
        }
    }
    exit(0); 
}