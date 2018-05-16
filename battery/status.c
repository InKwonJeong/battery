#include <stdio.h>
#include <stdlib.h>
#include "notifier.h"

int main()
{
	FILE *fp;
	char battery[3];
	
	for( ; ; )
	{
		fp = fopen("battery","r");
		fscanf(fp,"%s",battery); // 배터리값을 읽는다.
		printf("remaining battery:%s\n",battery); // 배터리용량을 표시한다.
		sig(atoi(battery)); // 배터리값을 notifier에 인자로 전달한다.
		sleep(3);
	}
	fclose(fp);
	return 0;
}
