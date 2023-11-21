#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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

void count(char op,char fname[])
{
	int tot_chars=0,words=0,lines=0;
	char ch;
	FILE *fp;	
	
	fp = fopen(fname,"r");
	
	if(fp==NULL)
	{
		printf("\n File not found");
	}
	else
	{
		while(ch!=EOF)
		{
			ch = fgetc(fp);
			tot_chars++;
			if(ch==' ' || ch=='\t')
			{
				words++;
			}
			else if(ch=='\n')
			{
				lines++;
				words++;
			}
		}		
		
		fclose(fp);
		
		if(op=='l')
		{
			printf("\n Total Lines are : %d",lines);
		}
		else if(op=='w')
		{
			printf("\n Total words are : %d",words);
		}
		else if(op=='c')
		{
			printf("\n Total Characters are : %d",tot_chars);
		}
		else
		{
			printf("\n Invalid Option");
		}
	}
}

void take_action()
{
	if(strcmp(args[0],"count")==0)
	{
		count(args[1][0],args[2]);
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
