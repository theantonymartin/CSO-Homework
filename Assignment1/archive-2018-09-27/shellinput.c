#include <shell.h>
#include <stdio.h>
char *getInput()
{
	char *line = NULL;
	ssize_t bufsize = 0;
	getline(&line, &bufsize, stdin);
	return line;
}