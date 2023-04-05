#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void print_date();
int a = 0;

int main(){
	signal(SIGINT, print_date); //시그날 지정 
	while(1)
		pause();  //프로그램 억지로 실행중 
}

void print_date(){
	if(a == 3){
		exit(0);		//4번째일때 종
	} else {
		if(system("date") == -1){
				printf("실행 안됨 종료!");
				exit(1);
		} else a++;
	}
}
