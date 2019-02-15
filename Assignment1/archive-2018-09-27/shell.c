#include <sys/stat.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h> 
#include <string.h>
#include <dirent.h>
#include <shell.h>
#include <fcntl.h>
#include <signal.h>

int main()
{
	char **args1, **args2, **commands;
	char name[50],currwd[200],home[200], iopipe[50];
	getcwd(home,200);
	int x=strlen(home);
	struct utsname sname;
	uname(&sname);
	gethostname(name, 50);
	signal(SIGINT,SIG_IGN);
    signal(SIGQUIT,SIG_IGN);
    signal(SIGTSTP,SIG_IGN);
	while(1)
	{
		getcwd(currwd,200);
		char tmfile[100];
		strcpy(tmfile, currwd);
		strcat(tmfile,"/tempfile");
		if(strcmp(currwd,home)==0)
			printf("<\033[0;32m%s\033[0m@\033[0;34m%s:~\033[0m>",name,sname.sysname);
		else if(strcmp(currwd,home)>0)
			printf("<\033[0;32m%s\033[0m@\033[0;34m%s:~%s\033[0m>",name,sname.sysname,&currwd[x]);
		else
			printf("<\033[0;32m%s\033[0m@\033[0;34m%s:%s\033[0m>",name,sname.sysname,currwd);		
		char *line = getInput();
	    int j=0;
	    commands=arg_splitter(line,1);
	    while(commands[j]!=NULL)
	    {
	    	int m=0,k=0,ki;
	    	while(commands[j][m]!='\0')
	    	{
	    		if(commands[j][m]=='>' || commands[j][m]=='<' || commands[j][m]=='|')
	    		{
	    			iopipe[k++]=commands[j][m];
	    		}
	    		m++;
	    	}
	    	iopipe[k]='\0';
	    	ki=k+1;
	    	k=0;
	    	args2=arg_splitter(commands[j++],3);
	    	
	    	if(args2[1]==NULL)
	    	{
	  	  		args1=arg_splitter(args2[0],2);
	  			if(args1[0]==NULL)
	  				continue;
	  			shellxecute(args1,0,NULL,home);
		    }
		    else 
		    {
		    	char **args3;
		    	while(iopipe[k]!='\0')
		    	{


		    		if(iopipe[k]=='>')
			    	{
			    		int z=0, flagb=1,flagc=0;
			    		if(args2[k+1]!=NULL)
			    		{
				    		char **temp=arg_splitter(args2[k+1],2);
				    		if(temp[0]==NULL)
				    			flagc=1;
			    		}
			    		else
			    			flagc=1;
				    	if(iopipe[k+1]=='>' && flagc==1)
				    		flagb=2;
			    		args3=arg_splitter(args2[k+1],2);
			    		args1=arg_splitter(args2[k],2);
			    		shellxecute(args1,flagb,args3[0],home);
			    		break;
			    	}

			    	else if(iopipe[k]=='<')
			    	{
			    		args1=arg_splitter(args2[k],2);
			    		int l=0;
			    		while(args1[l]!=NULL) 
			    			l++;
			    		args3=arg_splitter(args2[k+1],2);
			    		char line2[50];
			    		strcpy(line2,args3[0]);
			    		args1[l]=line2;
			    		int fdth=shellxecute(args1,3,NULL,home);
			    		remove(tmfile);
			    		char path[PATH_MAX];
			    		snprintf(path, PATH_MAX, "/proc/self/fd/%d", fdth);
			    		linkat(AT_FDCWD, path, AT_FDCWD, "tempfile", AT_SYMLINK_FOLLOW);
			    		close(fdth);
			    		if(iopipe[k+1]=='|' || iopipe[k+1]=='>')
			    		{
			    			strcpy(line2,"  cat tempfile ");
			    			args2[k+1]=line2;
			    		}
			    		int fk=open("tempfile",O_RDONLY);
			    		int pos=lseek(fk,0,SEEK_END);
			    		lseek(fk,0,SEEK_SET);
			    		int p=0;
			    		char a[1];
			    		while(pos>0)
			    		{
			    			read(fk,a,1);
			    			printf("%c",a[0]);
			    			pos--;
			    		}
			    		close(fk);
			    		k++;
			    	}

			    	else if(iopipe[k]=='|')
			    	{
			    		args1=arg_splitter(args2[k],2);
			    		int fdth=shellxecute(args1,3,NULL,home);
			    		remove(tmfile);
			    		char path[PATH_MAX];
			    		snprintf(path, PATH_MAX, "/proc/self/fd/%d", fdth);
			    		linkat(AT_FDCWD, path, AT_FDCWD, "tempfile", AT_SYMLINK_FOLLOW);
			    		close(fdth);
			    		char line2[200];
			    		strcpy(line2,"done");
			    		int g=0;
			    		char last[100];
			    		while(args2[g]!=NULL)
			    		{
			    			if(g==ki-1)
			    				strcpy(last,args2[g]);
			    			g++;
			    		}
			    		g=0;
			    		while(args2[g]!=NULL)
			    		{
			    			if(g==0);
			    			else if (g<k+1)
			    				strcat(line2,"done");
			    			else if(g==k+1)
			    			{
			    				strcat(line2,args2[g]);
		    					strcat(line2, " tempfile");
			    			}
			    			else
			    			{
			    				if(g==ki-1)
			    					strcat(line2,last);
			    				else
			    					strcat(line2,args2[g]);
			    			}
			    			if(g!=ki-1)
			    				strcat(line2,"|");
			    			g++;
			    		}	
			    		strcat(line2,"\0");
			    		args2=arg_splitter(line2,3);
			    		if(iopipe[k+1]=='\0')
			    		{
			    			args1=arg_splitter(args2[k+1],2);
			    			shellxecute(args1,0,NULL,home);
			    			break;
			    		}
			    		k++;
			    	}
	    		}
	    		remove(tmfile);
		    } 
		}
	}
	return 0;
}