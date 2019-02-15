#include <shell.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
void list_contents(char **args)
{
	DIR *dir;
	int buffer=5;
	char *arg;
	char **args1=malloc(buffer*sizeof(char*));
	int size=0;
	struct stat fd;
	char lswd[200],lswd1[200],lswd2[200],date[50];
	getcwd(lswd,200);
	int flag1=0,flag2=0;
	int i=1;
	struct dirent *pDirent;
    while(args[i]!=NULL)
    {
    	if(strcmp(args[i],"-a")==0)
    		flag1=1;
    	else if(strcmp(args[i],"-l")==0)
    		flag2=1;
    	else if(strcmp(args[i],"-la")==0||strcmp(args[i],"-al")==0)
    	{
    		flag1=1;
    		flag2=1;
    	}
    	else
    	{
    		args1[size++]=args[i];
    		if(size>buffer)
    		{
	  			buffer+=5;
	  			args1=realloc(args1, buffer*sizeof(char*));
	  			if (!args1) 
				{
		    		fprintf(stderr, "shell: allocation error\n");
 					exit(EXIT_FAILURE);
	  			}
	  		}	
    	}
    	i++;
    }
    args1[size]=NULL;
    //printf("%s\n",args1[size-1]);
    i=0;
    if(args1[i]==NULL)
    {
	    dir=opendir(lswd);
	    if(flag1==0&&flag2==0)
	    {
	    	while ((pDirent = readdir(dir)) != NULL)
	    	if(pDirent->d_name[0]!='.') 
	            printf ("%s  ", pDirent->d_name);
	        printf("\n");
	    }
	    else if(flag1==1&&flag2==0)
	    {
	    	while ((pDirent = readdir(dir)) != NULL)
	         	printf ("%s  ", pDirent->d_name);
	        printf("\n");
	    }
	    else if(flag1==0&&flag2==1)
			while ((pDirent = readdir(dir)) != NULL)
			{
				stat(pDirent->d_name,&fd);
				struct tm *time = localtime(&(fd.st_mtime));
				if(pDirent->d_name[0]!='.')
				{ 
	    			strftime(date, 100, "%h %d %H:%M",time);
			        printf((S_ISDIR(fd.st_mode))?"d":"-");
			        printf((fd.st_mode & S_IRUSR)?"r":"-");
			        printf((fd.st_mode & S_IWUSR)?"w":"-");
			        printf((fd.st_mode & S_IXUSR)?"x":"-");
			        printf((fd.st_mode & S_IRGRP)?"r":"-");
			        printf((fd.st_mode & S_IWGRP)?"w":"-");
			        printf((fd.st_mode & S_IXGRP)?"x":"-");
			        printf((fd.st_mode & S_IROTH)?"r":"-");
			        printf((fd.st_mode & S_IWOTH)?"w":"-");
			        printf((fd.st_mode & S_IXOTH)?"x":"-");
			        printf(" %ld",fd.st_nlink);
			        struct group  *gr = getgrgid(fd.st_gid);
			        struct passwd *pw = getpwuid(fd.st_uid);
			        printf(" %s",pw->pw_name);
			        printf(" %s",gr->gr_name);
			        printf(" %7ld",fd.st_size);
			        printf(" %s",date);
			        printf(" %s",pDirent->d_name);
			 		printf("\n");
			    }
			}
		else
			while ((pDirent = readdir(dir)) != NULL)
			{
				stat(pDirent->d_name,&fd);
				struct tm *time = localtime(&(fd.st_mtime));
	   			strftime(date, 100, "%h %d %H:%M",time);
		        printf((S_ISDIR(fd.st_mode))?"d":"-");
		        printf((fd.st_mode & S_IRUSR)?"r":"-");
		        printf((fd.st_mode & S_IWUSR)?"w":"-");
		        printf((fd.st_mode & S_IXUSR)?"x":"-");
		        printf((fd.st_mode & S_IRGRP)?"r":"-");
		        printf((fd.st_mode & S_IWGRP)?"w":"-");
		        printf((fd.st_mode & S_IXGRP)?"x":"-");
		        printf((fd.st_mode & S_IROTH)?"r":"-");
		        printf((fd.st_mode & S_IWOTH)?"w":"-");
		        printf((fd.st_mode & S_IXOTH)?"x":"-");
		        printf(" %ld",fd.st_nlink);
		        struct group  *gr = getgrgid(fd.st_gid);
		        struct passwd *pw = getpwuid(fd.st_uid);
		        printf(" %s",pw->pw_name);
		        printf(" %s",gr->gr_name);
			    printf(" %7ld",fd.st_size);
		        printf(" %s",date);
			    printf(" %s",pDirent->d_name);
			 	printf("\n");
			}
		closedir(dir);
	}
	else
		while(args1[i]!=NULL)
		{
			strcpy(lswd1,lswd);
			strcat(lswd1,"/");
			strcat(lswd1,args1[i++]);
			dir=opendir(lswd1);			
			if(dir==NULL)
			{
  				printf("No such file or directory\n");
  				continue;
  			}  			
		    if(flag1==0&&flag2==0)
		    {
		    	while ((pDirent = readdir(dir)) != NULL)
		    	if(pDirent->d_name[0]!='.') 
		            printf ("%s  ", pDirent->d_name);
		        printf("\n");
		    }
		    else if(flag1==1&&flag2==0)
		    {
		    	while ((pDirent = readdir(dir)) != NULL)
		         	printf ("%s  ", pDirent->d_name);
		        printf("\n");
		    }
		    else if(flag1==0&&flag2==1)
				while ((pDirent = readdir(dir)) != NULL)
				{
					strcpy(lswd2,lswd1);
					strcat(lswd2,"/");
					strcat(lswd2,pDirent->d_name);
					stat(lswd2,&fd);
					struct tm *time = localtime(&(fd.st_mtime));
					if(pDirent->d_name[0]!='.')
					{ 
		    			strftime(date, 100, "%h %d %H:%M",time);
				        printf((S_ISDIR(fd.st_mode))?"d":"-");
				        printf((fd.st_mode & S_IRUSR)?"r":"-");
				        printf((fd.st_mode & S_IWUSR)?"w":"-");
				        printf((fd.st_mode & S_IXUSR)?"x":"-");
				        printf((fd.st_mode & S_IRGRP)?"r":"-");
				        printf((fd.st_mode & S_IWGRP)?"w":"-");
				        printf((fd.st_mode & S_IXGRP)?"x":"-");
				        printf((fd.st_mode & S_IROTH)?"r":"-");
				        printf((fd.st_mode & S_IWOTH)?"w":"-");
				        printf((fd.st_mode & S_IXOTH)?"x":"-");
				        printf(" %ld",fd.st_nlink);
				        struct group  *gr = getgrgid(fd.st_gid);
				        struct passwd *pw = getpwuid(fd.st_uid);
				        printf(" %s",pw->pw_name);
				        printf(" %s",gr->gr_name);
				        printf(" %7ld",fd.st_size);
				        printf(" %s",date);
				        printf(" %s",pDirent->d_name);
				 		printf("\n");
				    }
				}
			else
				while ((pDirent = readdir(dir)) != NULL)
				{
					strcpy(lswd2,lswd1);
					strcat(lswd2,"/");
					strcat(lswd2,pDirent->d_name);
					stat(lswd2,&fd);
					struct tm *time = localtime(&(fd.st_mtime));
		   			strftime(date, 100, "%h %d %H:%M",time);
			        printf((S_ISDIR(fd.st_mode))?"d":"-");
			        printf((fd.st_mode & S_IRUSR)?"r":"-");
			        printf((fd.st_mode & S_IWUSR)?"w":"-");
			        printf((fd.st_mode & S_IXUSR)?"x":"-");
			        printf((fd.st_mode & S_IRGRP)?"r":"-");
			        printf((fd.st_mode & S_IWGRP)?"w":"-");
			        printf((fd.st_mode & S_IXGRP)?"x":"-");
			        printf((fd.st_mode & S_IROTH)?"r":"-");
			        printf((fd.st_mode & S_IWOTH)?"w":"-");
			        printf((fd.st_mode & S_IXOTH)?"x":"-");
			        printf(" %ld",fd.st_nlink);
			        struct group  *gr = getgrgid(fd.st_gid);
			        struct passwd *pw = getpwuid(fd.st_uid);
			        printf(" %s",pw->pw_name);
			        printf(" %s",gr->gr_name);
				    printf(" %7ld",fd.st_size);
			        printf(" %s",date);
				    printf(" %s",pDirent->d_name);
				 	printf("\n");
				}
			closedir(dir);
			}
}