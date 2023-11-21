#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>

#include<dirent.h>
#include<bfd.h>
#include<stdlib.h>
#include<config.h>
char comm[100],*ptr;
char *args[10];
int tot_args;
int search(char option,char *pattern,char *fname);
int count(char option,char *fname);
int typeline(char *option,char *fname);
int list(char option,char dirname[]);
mani()
{
	do
	{
		printf("myshell $");
		getcomm();
		sep_arg();
		take_action();
	}while(1);
}
sep_arg()
{
	int i,j;
	i=j=tot_args=0;
	args[tot_args]=(char*)malloc(sizeof(char)*20);
	for(i=0;comm[i]!='\0';i++)
	{
		if(comm[i]==' ')
		{
			args[tot_args][j]='\0';
			tot_args++;
			args[tot_args]=(char*)malloc(sizeof(char)*20);
			j=0;
		}
		else
		{
			args[tot_args][j]=comm[i];
			j++;
		}
	}
	args[tot_args][j]='\0';
	return;
}
getcomm()
{
	int len;
	ptr=fgets(comm,80,stdin);
	len=strlen(comm);
	comm[len-1]='\0';
	return;
}
take_action()
{
	char str[100];
	pid_t pid;
	int status;
	if(strcmp(args[0],"search")==0)
		search(*args[1],args[2],args[3]);
	else
	{
		if(ptr==NULL)
			exit(0);
		if(strlen(comm)<=1)
			return;
		if((pid=fork())<0)
		{
			printf("\n unable to create process");
		}
		else
		if(pid==0)
		{
			scanf(comm,"%s",comm);
			execvp(comm,args);
			strcpy(str,"./");
			strcat(str,args[0]);
			execvp(str,args);
			printf("\n %s:command not found",comm);
			exit(0);
		}
		else
		waitpid(pid,&status,0);
		
	}
}
int search(char option,char *pattern,char* fname)
{
	char buff[100],*ptr;
	int cnt;
	FILE *fp;
	int i;
	fp=fopen(fname,"r");
	if(fp==NULL)
	{
		printf("\n unable to open file");
		exit(0);
	}
	switch(option)
	{
		case "a":while(!feof(fp))
		{
			buff[0]='\0';
			fgets(buff,80,fp);
			ptr=strstr(buff,pattern);
			if(ptr!=NULL)
		}
		fclose(fp);
		break;
		
		case "c":cnt=0;
		while(!feof(fp))
		{
				buff[0]='\0';
				fgets(buff,80,fp);
				ptr=strstr(buff,pattern);
				while(ptr!=NULL)
				{
					cnt++;
					ptr=ptr+strlen(pattern);
					ptr=strstr(ptr,pattern);
				}	
		}
		fclose(fp);
		printf("\n The search string %s occurs %d times",pattern,cnt);
		break;
		
		case "f":while(!feof(fp))
		{
			buff[0]='\0';
			fgets(buff,80,fp);
			ptr=strstr(buff,pattern);
			if(ptr!=NULL)
			{
				printf("%s",buff);
				break;
			}
		}fclose(fp);
		break;
	}
}
