#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "notifier.h"

#define DEVICE_FILE_NAME "/dev/battery" // 디바이스 파일

FILE *fp;
char battery[10];
char buff[128];

int main(int argc, char *argv[]) // argv 값을 받아 디바이스 파일의 IOCTL cmd 값으로 사용
{
	int device;
	int n = atoi(argv[1]);
	
	device = open(DEVICE_FILE_NAME, O_RDWR | O_NDELAY); // 디바이스 파일 열기
	if (device >= 0)
	{
		printf("Device file Open\n\n");
		ioctl(device, n); // argv 값을 디바이스 파일에 cmd 값으로 전달
		
		for( ; ; )
		{
			fp = fopen("battery","r");
			fscanf(fp,"%s",battery); // 파일에서 배터리값 읽기

			write(device, battery, 10); // 디바이스 파일에 배터리값 기록
			read(device, buff, 10); // 디바이스 파일에 기록된 값 읽기

			printf("remaining battery: %s\n", buff);
			sig(atoi(buff)); // 배터리값을 기준으로 모드 설정
			sleep(3);
		}
	}
	else
		perror("Device file open fail");

	fclose(fp);
	exit(EXIT_SUCCESS);
}