#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

char threshold[5];
char pid[5];
FILE *fp;

void sig(int battery)
{
	fp = fopen("pid_th","r");
	fgets(pid,10,fp); // 파일에서 PID 읽기
	fgets(threshold,10,fp); // 파일에서 기준점 읽기
  	fclose(fp);

	if(battery < atoi(threshold)) 
 		kill(atoi(pid), SIGUSR1); // 배터리가 기준점보다 낮으면 절전모드
	else
		kill(atoi(pid), SIGUSR2); // 배터리가 기준점보다 높으면 일반모드

	return;
} 
