#include "apue.h"
#include <stdio.h>
int glob = 6;
char buf[] = "a write to stdout\n";
int main()
{
	int var;
	pid_t pid;
	
	var = 88;
	if(write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
		printf("write_error\n");
	printf("before fork");

	pid = fork();
	if(pid < 0)
		printf("create process error!\n");
	else if(pid == 0)
	{
//		fflush(STDOUT_FILENO);
		glob++;
		var++;
	}
	else
	{
		sleep(2);
	}

	printf("pid = %d,glob = %d,var = %d\n",getpid(), glob, var);
	exit(0);
}
