#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE  4096

int main()
{
	char buff[MAX_SIZE];
	int real_size = 0;
	while((real_size = read(STDIN_FILENO, buff, MAX_SIZE)) > 0)
		if(write(STDOUT_FILENO, buff, real_size) != real_size)
			printf("write error!");
	if(real_size < 0)
		printf("read error!");
	exit(0);
}
