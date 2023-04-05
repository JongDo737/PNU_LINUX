#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>

#define MAX_FILE_COUNT 100

int n = 0;

char type(mode_t);
char *perm(mode_t);
void printStat(char*, char*, struct stat*);

int main(int argc, char **argv){
	DIR *dp;
	char *dir;
	struct stat st;
	struct dirent *d;
	char path[BUFSIZ + 1], tmp[256];
	int cnt, i, j;
	char fname[MAX_FILE_COUNT][256];

	if(argc == 1)
		dir = ".";
	else dir = argv[1];

	if((dp = opendir(dir)) == NULL)
		perror(dir);

	cnt = 0;
	while((d = readdir(dp)) != NULL){
		if(d -> d_name[0] != '.'){		//숨김파일 제외
			sprintf(fname[cnt], "%s", d -> d_name);
			cnt++;
		}
	}

	for (i = 0; i < cnt; i++){
		for(j = 0; j < cnt - 1; j++){
			if(strcmp(fname[j], fname[j + 1]) > 0){
				strcpy(tmp, fname[j]);
				strcpy(fname[j], fname[j + 1]);
				strcpy(fname[j + 1], tmp);
			}
		}	
	}

	for(i = 0; i < cnt; i++){
		sprintf(path, "%s/%s", dir, fname[i]);

		if(lstat(path, &st) < 0)
			perror(path);
		else{
			printStat(path, fname[i], &st);
		}
	}
	closedir(dp);
	exit(0);
}

/* 파일 상태 정보를 출력 */
void printStat(char *pathname, char *file, struct stat *st) {
    if(S_ISREG(st->st_mode)){ 			//일반파일만 출력
        printf("%-18s", file);
        printf("%-13s", perm(st->st_mode));
        printf("%6ld ", st->st_size);
        printf("%-7s", getpwuid(st->st_uid)->pw_name);
        printf("%.24s\n", ctime(&st->st_mtime));  
    }
}

/* 파일 타입을 리턴 */
char type(mode_t mode) {

    if (S_ISREG(mode)) 
        return('-');
    if (S_ISDIR(mode)) 
        return('d');
    if (S_ISCHR(mode)) 
        return('c');
    if (S_ISBLK(mode)) 
        return('b');
    if (S_ISLNK(mode)) 
        return('l');
    if (S_ISFIFO(mode)) 
        return('p');
    if (S_ISSOCK(mode)) 
        return('s');
}

/* 파일 허가권을 리턴 */
char* perm(mode_t mode) {
    int i;
    static char perms[10]; 

    strcpy(perms, "---------");

    for (i=0; i < 3; i++) {
        if (mode & (S_IREAD >> i*3)) 
            perms[i*3] = 'r';
        if (mode & (S_IWRITE >> i*3)) 
            perms[i*3+1] = 'w';
        if (mode & (S_IEXEC >> i*3)) 
            perms[i*3+2] = 'x';
    }
   return(perms);
}
