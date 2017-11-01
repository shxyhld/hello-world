#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int main()
{
	char ch;
	while((ch = getchar()) != EOF && isdigit(ch))
	{
		putchar(ch);
	}
	putchar('\n');
	ungetc(ch, stdin);
	printf("return char:%c\n", ch);
	//fflush(stdin);
	ch = 'o';
	ch = getchar();
	printf("re get char:%c\n", ch);
	exit(0);
}
