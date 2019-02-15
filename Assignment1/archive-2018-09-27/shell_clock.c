#include <shell.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <ctype.h>
int timer1=0, timer2=0;
void sigint_handler()
{
	timer1=1;
}
void sigstp_handler()
{
	timer2=1;
}
/*void sigalrm_handler(int sig)
{
	struct rtc_time t;
	int fd;
	fd=open("/dev/rtc",O_RDONLY);
	printf("%d\n",fd);
	ioctl(fd,RTC_RD_TIME,&t);
	printf("\n%d ",t.tm_mday);
	switch(t.tm_mon)
	{
		case 0:
		printf("January ");
		break;
		case 1:
		printf("February ");
		break;
		case 2:
		printf("March ");
		break;
		case 3:
		printf("April ");
		break;
		case 4:
		printf("May ");
		break;
		case 5:
		printf("June ");
		break;
		case 6:
		printf("July ");
		break;
		case 7:
		printf("August ");
		break;
		case 8:
		printf("September ");
		break;
		case 9:
		printf("October ");
		break;
		case 10:
		printf("November ");
		break;
		case 11:
		printf("December ");
		break;
	}
	printf("%d, %d:%d:%d\n",t.tm_year+1900,t.tm_hour,t.tm_min,t.tm_sec);
	close(fd);
}*/


void disp_clock(char **args)
{
	int flag1=0,flag2=0;
	char *interval=args[2], *tlength=args[4];
	while(*interval)
		if(isdigit(*interval++)==0)
		{
			flag1=1;
			break;
		}
	while(*tlength)
		if(isdigit(*tlength++)==0)
		{
			flag2=1;
			break;
		}
	if(strcmp(args[1],"-t")!=0 || strcmp(args[3],"-n")!=0 || flag1==1 || flag2==1)
	{
		fprintf(stderr,"command not found\n");
		return ;
	}
	int i=2;
	int pid,status;
	int x=0;
	while(args[x]!=NULL)
		x++;
	if(x<=4)
	{
		fprintf(stderr,"command not found\n");
		exit(0);
	}
	//printf("%d\n",atoi(args[2]));
	/*if(args[x-1][strlen(args[x-1])-1]=='&')
	{
		strcpy(proc[count].name,args[0]);
		count++;
		flag=1;
		if(strlen(args[x-1])>1)
			args[x-1][strlen(args[x-1])-1]='\0';
		else 
			args[x-1]=NULL;
	}*/
	pid = fork();
	if(pid==0)
	{
		signal(SIGINT,SIG_DFL);
		signal(SIGTSTP,SIG_DFL);
		struct tm *t;
		time_t start, end, start1;
		time(&start1);
		time(&start);
		while(1)
		{
			time(&end);
			if(difftime(end,start1)>=atoi(args[4]))
				break;
			sleep(atoi(args[2]));
			if(difftime(end,start1)>=atoi(args[4]))
				break;
			time(&start);
				t=localtime(&start);
				printf("\n%d ",t->tm_mday);
				switch(t->tm_mon)
				{
					case 0:
					printf("January ");
					break;
					case 1:
					printf("February ");
					break;
					case 2:
					printf("March ");
					break;
					case 3:
					printf("April ");
					break;
					case 4:
					printf("May ");
					break;
					case 5:
					printf("June ");
					break;
					case 6:
					printf("July ");
					break;
					case 7:
					printf("August ");
					break;
					case 8:
					printf("September ");
					break;
					case 9:
					printf("October ");
					break;
					case 10:
					printf("November ");
					break;
					case 11:
					printf("December ");
					break;
				}
				printf("%d, %d:%d:%d\n",t->tm_year+1900,t->tm_hour,t->tm_min,t->tm_sec);
		}
		/*do{
			time(&end);
			if(difftime(end,start1)==atoi(args[4]))
				break;
			if(difftime(end,start)==atoi(args[2]))
			{
				time(&start);
				t=localtime(&start);
				printf("\n%d ",t->tm_mday);
				switch(t->tm_mon)
				{
					case 0:
					printf("January ");
					break;
					case 1:
					printf("February ");
					break;
					case 2:
					printf("March ");
					break;
					case 3:
					printf("April ");
					break;
					case 4:
					printf("May ");
					break;
					case 5:
					printf("June ");
					break;
					case 6:
					printf("July ");
					break;
					case 7:
					printf("August ");
					break;
					case 8:
					printf("September ");
					break;
					case 9:
					printf("October ");
					break;
					case 10:
					printf("November ");
					break;
					case 11:
					printf("December ");
					break;
				}
				printf("%d, %d:%d:%d\n",t->tm_year+1900,t->tm_hour,t->tm_min,t->tm_sec);
			}
		}while(difftime(end,start)<=atoi(args[2]));*/
	}
	else 
	{
			wait(NULL);
	}
}