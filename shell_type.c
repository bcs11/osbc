#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

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
	args[t][j]='\0';
}

void typeline(char op[], char fname[])
{
	FILE *fp;
	int tot_lines=0,ch,n,cnt;
	
	fp= fopen(fname,"r");
	
	if( fp == NULL )
	{
		printf("\n Unable to open file");
	}
	else
	{
		while (ch != EOF)
		{
			ch = fgetc(fp);
			
			if(ch == '\n') 
				tot_lines++;
		}
		fclose(fp);
		
		ch=' ';
		
		if(op[0]=='a') 
		{
			fp = fopen(fname,"r");
			
			while (ch != EOF)
			{
				ch = fgetc(fp);
				printf("%c",ch);
			}
			fclose(fp);
		}
		else if(op[0] == '+') 
		{
			//n = atoi(op+1);
			n=5;
			if(n > tot_lines)
			{	
				printf("\n Invalid  option");
			}
			else
			{
				fp= fopen(fname,"r");
				cnt = 0;
				while( cnt < n )
				{
					ch = fgetc(fp);
					printf("%c",ch);
					if(ch == '\n')
						cnt++;
				}
				fclose(fp);
			}
		}
		else if(op[0] =='-') 
		{
			//n = atoi(op+1);
			n=5;
			if(n > tot_lines)
			{	
				printf("\n Invalid option");
			}
			else
			{
				fp= fopen(fname,"r");
				cnt = 0;
				while(cnt < tot_lines-n)
				{
					ch = fgetc(fp);
					if(ch == '\n')
						cnt++;
				}
				ch = ' ';
				while(ch!=EOF)
				{
					ch=fgetc(fp);
					printf("%c",ch);	
				}
				fclose(fp);
			}
		}
		else
		{
			printf("\n Invalid option");
		}
	}
}

void take_action()
{
	if(strcmp(args[0],"typeline")==0)
	{
		typeline(args[1],args[2]);
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
		printf("\n myshell$ ");
		get_comm();
		sep_args();
		take_action();
	}

	return 0;
}
