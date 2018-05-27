// 16.2 How to measure the time of a context switch?
// reference code from http://blog.csdn.net/dashon2011/article/details/7412548
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int x, i, fd[2], p[2];
	int tv[2];
	char send	= 's';
	char receive;
	pipe(fd);
	pipe(p);
	pipe(tv);
	struct timeval tv_start,tv_end;
	struct sched_param param;
	param.sched_priority = 0;

	while ((x = fork()) == -1);
	if (x == 0) {
		sched_setscheduler(getpid(), SCHED_FIFO, &param);
		gettimeofday(&tv_start, NULL);
		write(tv[1], &tv_start, sizeof(tv_start));
		//printf("Before Context Switch Time1.sec %u s\n", tv_start.tv_sec);
		//printf("Before Context Switch Time1.usec %u us\n", tv_start.tv_usec);		
		for (i = 0; i < 10000; i++) {
			read(fd[0], &receive, 1);
			//printf("Child read!\n");
			write(p[1], &send, 1);
			//printf("Child write!\n");
		}
		exit(0);
	}
	else {
		sched_setscheduler(getpid(), SCHED_FIFO, &param);
		for (i = 0; i < 10000; i++) {
			write(fd[1], &send, 1);
			//printf("Parent write!\n");
			read(p[0], &receive, 1);
			//printf("Parent read!\n");
		}
		gettimeofday(&tv_end, NULL);
		//printf("After Context SWitch Time1.sec %u s\n", tv_end.tv_sec);
		//printf("After Context SWitch Time1.usec %u us\n", tv_end.tv_usec);
		
	}
	read(tv[0], &tv_start, sizeof(tv_start));	
	//printf("Before Context Switch Time2.sec %u s\n", tv_start.tv_sec);
	//printf("Before Context Switch Time2.usec %u us\n", tv_start.tv_usec);
	//printf("Before Context Switch Time %u us\n", tv_start.tv_usec);
	//printf("After Context SWitch Time2.sec %u s\n", tv_end.tv_sec);
	//printf("After Context SWitch Time2.usec %u us\n", tv_end.tv_usec);
	printf("Task Switch Time: %f us\n", (1000000 * (tv_end.tv_sec - tv_start.tv_sec) + tv_end.tv_usec - tv_start.tv_usec) / 20000.0);	
	
	return 0;
}