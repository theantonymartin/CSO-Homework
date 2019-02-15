#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <shell.h>
char **arg_splitter(char* line, int x)
{
	int buffer=65;
	char* arg;
	char **args=malloc(buffer*sizeof(char*));
	int size=0;

	
  if (!args) 
	{
  	fprintf(stderr, "shell: allocation error\n");
    exit(EXIT_FAILURE);
  }


  if(x==1)
    arg=strtok(line,";");
  else if(x==2)
    arg=strtok(line," \t\r\n\a<>");
  else if(x==3)
    arg=strtok(line,"<>|");

  while(arg!=NULL)
  {
  	args[size++]=arg;
  	if(size>buffer)
  	{
  		buffer+=65;
  		args=realloc(args, buffer*sizeof(char*));
  		if (!args) 
		{
   		fprintf(stderr, "shell: allocation error\n");
   		exit(EXIT_FAILURE);
  		}
  	}
    if(x==1)
  	 arg=strtok(NULL,";");
    else if(x==2)
     arg=strtok(NULL," \t\r\n\a");
    else if(x==3)
      arg=strtok(NULL,"<>|");
  }
  

  args[size]=NULL;
  return args;
}