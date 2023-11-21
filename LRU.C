/*Program for LRU Page replacement simulation*/

#include<stdio.h>

struct node
{
  	int pno,reftime;
}frames[100];

int n,i;

void init()
{
	for(i=0;i<n;i++)
   	{ 
	   	frames[i].pno = -1;
	 	frames[i].reftime = -1;
   	}
}

int page_found(int pno)
{
	for(i=0;i<n;i++)
	{
		if(frames[i].pno==pno)
		{
			return i;
		}
	}
	
	return -1;
}

int get_free_frame()
{  
	for (i=0; i<=n; i++)
  	{
		if (frames[i].pno==-1)
		{
			return(i);
		}
	}
   	
	return(-1);
}

int get_lru_frame()
{
  	int selfno=0;

  	for(i=0;i<n;i++)
  	{
  		if(frames[i].reftime < frames[selfno].reftime)
  		{
			selfno=i;
		}
	}

  	return selfno;
}

int main()
{
   	int pg_req[]={5,8,10,14,10,9,5,10,8,5,1,10,9,12,10};
   	int size=15,currtime=0;
   	int page_fault=0,i,j,fno;
  
   	printf("\n Enter No. of Frames : ");
	scanf("%d",&n);
   
   	init();

   	printf("\n PageNo     Page Frames          Page Fault");
   	printf("\n--------------------------------------------");
   
   	for(i=0;i<size;i++)
   	{
   		fno = page_found(pg_req[i]);
   		
	 	if(fno==-1) 
	 	{
	   		fno=get_free_frame();
	   		
			if (fno==-1) 
			{
				fno=get_lru_frame();
			}
	   		
			page_fault++;
		   
		   	frames[fno].pno=pg_req[i];
		   	frames[fno].reftime=currtime;
		   
		   	printf("\n %d",pg_req[i]);
		   	
			for(j=0;j<n;j++)
			{
				printf("\t %d",frames[j].pno);
			}
		   	
			printf(" : Y");
	 	}
		else
		{
			frames[fno].pno=pg_req[i];
		   	frames[fno].reftime=currtime;
		   	
			printf("\n %d",pg_req[i]);
		   	
		   	for(j=0;j<n;j++)
			{
			 	printf("\t %d",frames[j].pno);
			}
		   	printf(" : N");
		}
		
	   	currtime++;
   	}
   	
  	printf("\n-------------------------------------------");
	printf("\n Total Page Faults are = %d",page_fault);
	printf("\n-------------------------------------------");
	
	return 0;
}
