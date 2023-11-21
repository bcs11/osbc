#include<stdio.h>
#include<stdlib.h>

struct proc_info
{
	int atime;
	int btime;
} proc[20];

typedef struct rqnode
{
	int pid;
	struct rqnode *link;
}RQNODE;

RQNODE *head=NULL, *temp, *last;

struct ganttchart
{
	int stime;
	int pid;
	int etime;
} gchart[20];

int i,n,ctime,gi=0,wtime[20],ttime[20];

void getprocs();
void start();
void addprocq();
void attachtoq(int);
void addgchart(int);
void dispgchart();
void disptimes();
int getproc_id();
int finished();

int main()
{
	getprocs();
	ctime=0; 
	start();
	dispgchart();
	disptimes();
	
	return 0;
}

void getprocs()
{
	printf("\nHow many processes : ");
	scanf("%d",&n);

	printf("\nPID \tATIME \tbtime \n");
	for(i=1;i<=n;i++)
	{
		printf("%d\t",i);
		scanf("%d%d",&proc[i].atime,&proc[i].btime);
	}
}

void start()
{
	int pid;
	
	addprocq(); 
	pid=getproc_id();

	while(!finished()) 
	{
		ctime++;  
		addprocq(); 

		if(pid!=-1)
		{ 
			proc[pid].btime--;
			
			if(proc[pid].btime==0)
			{
				printf("\nProc %d completed at time %d...",pid,ctime);
				ttime[pid]=ctime-proc[pid].atime;
				pid=getproc_id(); 
			}
		}
	}
	
	gchart[gi].etime=ctime;
}

void addprocq()
{
	for(i=1;i<=n;i++)
	{
		if(proc[i].atime==ctime)  
		{
			attachtoq(i);
		}
	}
}

void attachtoq(int pid)
{
	temp=(RQNODE*) malloc(sizeof(RQNODE));
	
	temp->pid=pid;
	temp->link=NULL;
	
	if(head==NULL)
	{
		head=temp;
	}
	else
	{
		last->link=temp;
	}
	
	last=temp;
}

int finished() 
{
	for(i=1;i<=n;i++)
	{
		if(proc[i].btime!=0)
		{
			return(0);
		}
	}
	
	return(1);
}

int getproc_id()
{
	int pid;
	
	if(head==NULL)
	{
		return(-1);
	}
	
	pid=head->pid;
	temp=head; 
	head=head->link;
	free(temp);
	addgchart(pid);
	wtime[pid]=ctime-proc[pid].atime;
	
	return(pid);
}

void addgchart(int pid)
{
	gchart[++gi].pid=pid;
	gchart[gi].stime=ctime;
	gchart[gi-1].etime=gchart[gi].stime;
}

void dispgchart()
{
	printf("\n");
	for(i=1;i<=gi;i++)
	{
		printf("|----");
	}
	printf("| \n");
	for(i=1;i<=gi;i++)
	{
		printf("| %d  ",gchart[i].pid);
	}
	printf("| \n");
	for(i=1;i<=gi;i++)
	{
		printf("|----");
	}
	printf("| \n");
	for(i=1;i<=gi;i++)
	{
		printf("%d    ",gchart[i].stime);
	}
	printf("%d\n",gchart[gi].etime);
}

void disptimes()
{
	int sumwt=0,sumtt=0,pid;

	printf("\n **Turnaround Time**\n");
	printf("\nPID \tTtime");
	for(i=1;i<=n;i++)
	{
		printf("\n %d \t %d",i,ttime[i]);
		sumtt+=ttime[i];
	}
	printf("\n Average : %.2f\n",(float)sumtt/n);
	
	printf("\n **Waiting Time**\n");
	printf("\nPID \tWtime");
	for(i=1;i<=n;i++)
	{
		printf("\n %d \t %d",i,wtime[i]);
		sumwt+=wtime[i];
	}
	printf("\n Average : %.2f\n",(float)sumwt/n);
}
