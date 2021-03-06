#include <signal.h>
#include <stdio.h>
static void	sig_usr(int);	/* one handler for both signals */

int
main(void)
{
	FILE *fp;

	int threshold = 15; // 배터리기준점 설정
	int pid = getpid();

	fp = fopen("/proc/battery_notify","w");
	fprintf(fp,"%d",pid); // 파일에 PID 기록
	fclose(fp);

	fp = fopen("/proc/battery_threshold","w");
	fprintf(fp,"%d",threshold); // 파일에 기준점 기록
	fclose(fp);

	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
		printf("can't catch SIGUSR1\n");
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
		printf("can't catch SIGUSR2\n");
	for ( ; ; )
		pause();
}

static void
sig_usr(int signo)		/* argument is signal number */
{
	if (signo == SIGUSR1)
		printf("\n**********Power saving mode**********\n\n"); // 절전모드 설정
	else if (signo == SIGUSR2)
		printf("\n**********Power normal mode**********\n\n"); // 일반모드 설정
	else
	printf("received signal %d\n", signo);
}
