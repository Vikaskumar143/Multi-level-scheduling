#include<stdio.h>
#include<stdlib.h>

int current_time=0,queue_timer=10,total;
struct Process
{
	
	int process_id;
	int compTime;
	int arrival_time;
	int start;
	int priority;
	int brust_time;
	int temp;
};

void RoundRobin(struct Process p[],int queue_no)
{		
	    printf("Round Robin Algorithm --> RRA is Running at %d sec\n",current_time);
		int time_quantum=10;
		int i;
		for( i=0; i< queue_no; i++ )
		{	
			if( time_quantum <= queue_timer && p[i].arrival_time <= current_time )
			{
			  if( p[i].start == -1 )
			    {
			       p[i].start = current_time;
			    }
			  if( p[i].brust_time >= time_quantum )
			    {
			       p[i].brust_time = p[i].brust_time - time_quantum;
			       current_time = current_time + time_quantum;
			       queue_timer -= time_quantum;
			    }
			  if( p[i].brust_time < time_quantum && p[i].brust_time > 0) 
			    {
			       current_time = current_time + p[i].brust_time;
			       queue_timer -= p[i].brust_time;
			       p[i].brust_time = 0;
			    }
			  if(p[i].brust_time==0&&p[i].compTime==-1)
			    {
				   p[i].compTime = current_time;
				   total--;
			    }
			}
		}
		queue_timer = 10;
}

void FCFS(struct Process p[],int r)
{
	printf("First Come First Serve Method --> FCFS is Running at %d sec\n",current_time);
	int i;
		for(i=0; i<r; i++)
		{	
			if( p[i].brust_time <= queue_timer && p[i].arrival_time <= current_time && p[i].brust_time > 0 )
			   {			
			      if( p[i].start == -1 )
			        p[i].start = current_time;
			        p[i].brust_time = 0;
			        current_time = current_time + p[i].brust_time;
			        queue_timer -= p[i].brust_time;
			      if( p[i].brust_time == 0 && p[i].compTime == -1 )
			        {
				       p[i].compTime = current_time;
				       total--;
			        }
		       }
			else
			{
			  if( (p[i].brust_time - queue_timer > 0) && p[i].arrival_time <= current_time && p[i].brust_time > 0 )
				{
				    if(p[i].start == -1)
				      p[i].start = current_time;
				      p[i].brust_time = p[i].brust_time - queue_timer;
				      current_time = current_time + queue_timer;
				      queue_timer = 0;
				    if(p[i].brust_time == 0 && p[i].compTime == -1)
				      {
					     p[i].compTime = current_time;
					     total--;
				      }
				}
			}
		}
		queue_timer = 10;
}

int PriorityQueue(struct Process p[],int r,int a)
{
	printf("Priority Queue --> Priority Queue is Running at %d sec \n",current_time);
	int s;
	int i;
	while( a != 0 && queue_timer > 0)
	{
	    s=r;
	    for(i=0; i<r; i++)
	    {	
	        if( p[i].arrival_time <= current_time && p[i].priority < p[s].priority && p[i].brust_time > 0)
	        {	
	            s=i;
	        }
	    }
	    if( p[s].start == -1)
	    {
	        p[s].start = current_time;
	    }
	    queue_timer -= 1;
	    p[s].brust_time -= 1;
	    if(p[s].brust_time == 0 && p[s].compTime == -1)
	    {
	    	p[s].compTime = current_time;
	        total--;
	        a--;
	    }
	    current_time += 1;
	}
	queue_timer = 10;
}

int main()
{	
	int n,i;
	int round_robin = 0;
	int priority_queue = 0;
	int fcfs = 0;
	printf("Enter the number of processes: ");
	scanf("%d",&n);
	printf("No. of Processes Entered : %d\n",n);
	total=n;
	struct Process ps[n];
    for(i=0; i<n; i++)
    {
    	printf("\t----------->> [PROCESS %d] <<-----------\n",i+1);
		ps[i].process_id = i+1;
		printf("Enter the values\n");
		printf("Arrival Time :  ");
    	scanf("%d",&ps[i].arrival_time);
    	
    	printf("Burst Time :  ");
    	scanf("%d",&ps[i].brust_time);
		ps[i].temp=ps[i].brust_time;
		ps[i].start =- 1;
    	ps[i].compTime =- 1;
    	
    	printf("Choose the priority\n \t1 for Round Robin Algorithm\n \t2 for First Come First Serve\n \t3 for Priority Queue\n ");
    	printf("Enter the priority:  ");
    	scanf("%d",&ps[i].priority);
    	int c = ps[i].priority;
    	if(c == 1)
    	{
    	    printf("Opted Round Robin for Process %d by Choosing value 1\n",i+1);
    	    round_robin++;
    	}
    	else if(c == 2)
    	{
    	    printf("Opted First Come First Serve for Process %d by Choosing value 2\n",i+1);
    	    fcfs++;
    	}
    	else if(c == 3)
    	{
    	    printf("Opted Priority Queue for Process %d by Choosing value 3",i+1);
    	    priority_queue++;
    	}
    	else
    	{
    	    printf("Entered wrong value");
    	}
		
	}
	int rrid=0,prid=0,fcfsid=0;
	struct Process roundqueue[round_robin],priorqueue[priority_queue+1],fcfsqueue[fcfs];
	for(i=0;i<n;i++)
	{
		if(ps[i].priority == 1)
		{
			roundqueue[rrid]=ps[i];
			rrid++;
		}
		else if(ps[i].priority==2)
		{
			fcfsqueue[fcfsid]=ps[i];
			fcfsid++;
		}
		else if(ps[i].priority==3)
		{
			priorqueue[prid]=ps[i];
			prid++;
		}
	}
	int remain = priority_queue;
	while(total>0)
	{
		RoundRobin(roundqueue,round_robin);
		remain=PriorityQueue(priorqueue,priority_queue,remain);
		FCFS(fcfsqueue,fcfs);
	}
	printf("ProcessId    Arrival\t BrustTime  Starting\tTurnAround Time     Priority\n");
	for(i=0;i<round_robin;i++)
	{
		printf("     %d\t\t%d\t      %d \t%d\t\t%d \t\t%d\n",roundqueue[i].process_id,roundqueue[i].arrival_time,roundqueue[i].temp,roundqueue[i].start,roundqueue[i].compTime,roundqueue[i].priority);
	}
	for(i=0;i<fcfs;i++)
	{
		printf("     %d\t\t%d\t      %d \t%d\t\t%d \t\t%d\n",fcfsqueue[i].process_id,fcfsqueue[i].arrival_time,fcfsqueue[i].temp,fcfsqueue[i].start,fcfsqueue[i].compTime,fcfsqueue[i].priority);
	}
	for(i=0;i<priority_queue;i++)
	{
		printf("     %d\t\t%d\t      %d \t%d\t\t%d \t\t%d\n",priorqueue[i].process_id,priorqueue[i].arrival_time,priorqueue[i].temp,priorqueue[i].start,priorqueue[i].compTime,priorqueue[i].priority);
	}
}
