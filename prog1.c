
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
struct printfile {
	char *fileName;
	char mode1;
	char *mode2;
	char *pwname;
	char *time;
	
};
char type(mode_t);
char *perm(mode_t);
struct printfile printStat(char*, char*, struct stat*);
void listSort();
int fileCount;

int main(int argc, char**argv)
{
	DIR * dp;
	char*dir;
	struct stat st;
	struct dirent *d;
	struct printfile list[100];
	char path[BUFSIZ +1];
	fileCount = 0;
	if(argc == 1){
		perror("경로 설정 오류");
		exit(1);
	}
	else dir = argv[1];

	if((dp = opendir(dir)) == NULL) // 디렉토리열기
		perror(dir);

	while((d = readdir(dp)) != NULL) {
		sprintf(path, "%s/%s",dir,d->d_name);
		if(lstat(path, &st) <0){
			printf("%s", path);
			perror(path);
		}else 
			list[fileCount] = printStat(path, d->d_name, &st);
	}	
	listSort(list);

	closedir(dp);
	exit(0);
}
struct printfile printStat(char *pathname, char *file, struct stat*st) {
	struct printfile temp;		
	// 일반 파일 검출
	if(type(st->st_mode) == 'd' && file[0] != '.'){

		fileCount++;

		temp.fileName = file;
		temp.mode1 = type(st->st_mode);
		temp.mode2 = perm(st->st_mode);
		temp.pwname = getpwuid(st->st_uid)->pw_name;
		temp.time = ctime(&st->st_mtime)+4;

	}
	return temp;
}

char type(mode_t mode) {
	if(S_ISREG(mode))		// 일반 파일
		return('-');
	if(S_ISDIR(mode))		// 디렉토리 
		return('d');
	if(S_ISCHR(mode))		// 문장 장치 특수파일
		return('C');
	if(S_ISBLK(mode))		// 블록 장치 특수파일
		return('b');
	if(S_ISLNK(mode))
		return('l');
	if(S_ISFIFO(mode))
		return('p');
	if(S_ISSOCK(mode))
		return('s');
}
char *perm (mode_t mode){
	int i;
	static char perms[10];
	strcpy(perms, "---------");

	for(int i=0; i<3; i++) {
		if(mode&(S_IRUSR >> i*3))
			perms[i*3] = 'r';
		if(mode&(S_IWUSR >> i*3))
			perms[i*3+1] = 'w';
		if(mode&(S_IXUSR >> i*3))
			perms[i*3+2] = 'x';
	}
	return (perms);
}

void listSort(struct printfile* list){

	struct printfile temp;
	for (int i = 0; i < fileCount; i++){	
		for (int j = 0; j < i; j++){	

			if (strcmp(list[i].fileName, list[j].fileName) < 0)
			{
				temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		}
	}

	for(int i=0; i<fileCount; i++) {
		printf("%-12s ", list->fileName);
		printf("%c%s ", list->mode1,list->mode2);
		printf("%s ", list->pwname);
		printf("%s", list->time);
		list++;
	}
}   