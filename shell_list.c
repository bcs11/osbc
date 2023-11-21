#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <dirent.h>

char comm[80],*args[5];

void get_comm()
{
	int len;
	
	fgets(comm,80,stdin);
	len = strlen(comm);
	comm[len-1] = '\0';
}

void sep_args()
{
	int i,j=0,t=0;
	
	args[t] = (char*) malloc(sizeof(char)*20);
	
	for(i=0;comm[i]!='\0';i++)
	{
		if(comm[i]==' ')
		{
			args[t][j]='\0';
			t++;
			j=0;
			args[t] = (char*) malloc(sizeof(char)*20);
		}
		else
		{
			args[t][j] = comm[i];
			j++;
		}
	}
}

void list( char option, char dirname[])
{
	DIR *dp;
	struct dirent *dent;
	int cnt=0;
	
	switch(option)
	{
		case 'f' : // list all dir entries
				dp= opendir(".");
				if( dp == NULL )
				{
					printf("\n Unable to open dir");
					return;
				}
	
				while( dent = readdir(dp) )
				{
					printf("\n %s",dent->d_name);
				}
				break;
				
		case 'n' : // list number all dir entries
				cnt =0;
				dp= opendir(".");
				if( dp == NULL )
				{
					printf("\n Unable to open dir");
					return;
				}
				while( dent = readdir(dp) )
				{
					cnt++;
				}
				printf("\n Total dir entries = %d",cnt);
				closedir(dp);
				break;
		case 'i' : // list all dir entries with inode
				dp= opendir(".");
				if( dp == NULL )
				{
					printf("\n Unable to open dir");
					return;
				}
	
				while(dent = readdir(dp))
				{
					printf("\n %s %ld",dent->d_name,dent->d_ino);
				}
				closedir(dp);
				break;
		default :	printf("\n Invalid option");
	} 
}

void take_action()
{
	if(strcmp(args[0],"list")==0)
	{
		list(args[1][0],args[2]);
	}
	else if(strcmp(args[0],"quit")==0)
	{
		exit(0);
	}
	else
	{
		printf("\n %s: Command not found",args[0]);
	}
}

int main()
{
	while(1)
	{
		printf("MyShell$ ");
		get_comm();
		sep_args();
		take_action();
	}
}
