#include <shell.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

typedef struct 
{
  char text[50];
  int id;
}reminder;
reminder rem[50],remt[50];
int rcount=0,rtcount=0;

void sigchld_handler1(int sig)
{
	rtcount=0;
	for(int i=0; i<rcount; i++)
	{
		if(waitpid(rem[i].id,NULL,WNOHANG)!=-0)
			printf("\nReminder:%s \n",rem[i].text);
		else
			remt[rtcount++]=rem[i];
	}
	rcount=0;
	for(int i=0; i<rtcount; i++)
		rem[rcount++]=remt[i];
}


void disp_reminder(char **args)
{
	signal(SIGCHLD,sigchld_handler1);
	strcpy(args[0],"sleep");
	int i=2;
	strcpy(rem[rcount].text," ");
	while(args[i]!=NULL)
	{
    	strcat(rem[rcount].text,args[i++]);
    	strcat(rem[rcount].text," ");
	}
    rcount++;
    args[2]=NULL;
	int pid,flag=0,status;
	int x=0;
	while(args[x]!=NULL)
		x++;
	pid = fork();
	if(pid!=0)
		rem[rcount-1].id=pid;
	if(pid==0)
	{
		if(execvp(args[0], args)==-1)
		{
			fprintf(stderr,"%s: command not found\n",args[0]);
		}
		exit(0);
	}
}