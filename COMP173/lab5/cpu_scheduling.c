#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char PID[10][10];
//int n, arr[10], bur[10]; 

void fcfs(int arr[], int bur[], int n) {    
    char t[10];
    int star[10],finish[10],tat[10],wt[10],i,j,temp;
    int totwt=0,tottat=0;

	printf("First Come First Serve");
  
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            if(arr[i]<arr[j]) {
                temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
                temp=bur[i];
                bur[i]=bur[j];
                bur[j]=temp;
                strcpy(t,PID[i]);
                strcpy(PID[i],PID[j]);
                strcpy(PID[j],t);
            } 
        }
    }

    for(i=0; i<n; i++) {
        if(i==0) {
            star[i]=arr[i];
		}
        else {
            star[i]=finish[i-1];
		}
        wt[i]=star[i]-arr[i];
        finish[i]=star[i]+bur[i];
        tat[i]=finish[i]-arr[i];
    }

    printf("\nPID  Arrtime  Start  Finish RunningTime WaitTime ");
    for(i=0; i<n; i++) { 
	printf("\n%s\t%3d\t%3d\t%3d\t%3d\t%3d",PID[i],arr[i],star[i],finish[i],bur[i],wt[i]);
        totwt+=wt[i];
        tottat+=tat[i];
    }
    printf("\nAverage Waiting time: %f",(float)totwt/n);
    printf("\nAverage Turn Around Time: %f\n",(float)tottat/n);
  
}


void sjf(int arr[], int bur[], int n) {
	int *temp, i, j, limit, sum = 0, position;
	float average_wait_time, average_turnaround_time;
	int waiting_time[20], turnaround_time[20];

	printf("Shortest Job First");

	for(i = 0; i < n; i++) {
		position = i;
		for(j = i + 1; j < n; j++) {
		      if(bur[j] < bur[position]) {
		            position = j;
		      }
		}
		temp = &bur[i];
		bur[i] = bur[position];
		bur[position] = *temp;
		//temp = PID[i];
		//PID[i] = PID[position];
		strcpy(PID[i], PID[position]);
		//PID[position] = temp;
	}	

	waiting_time[0] = 0;
	for(i = 1; i < n; i++) {
		waiting_time[i] = 0;
		for(j = 0; j < i; j++) {
			waiting_time[i] = waiting_time[i] + bur[j];
		} 
		sum = sum + waiting_time[i];
	}

	average_wait_time = (float)sum / n;
	sum = 0;
    printf("\nPID Arrtime BurstTime WaitTime Turnaroundtime ");
	for(i = 0; i < n; i++) {
		turnaround_time[i] = bur[i] + waiting_time[i];
		sum = sum + turnaround_time[i];
		printf("\n%s\t%3d\t%3d\t%3d", PID[i], bur[i], waiting_time[i], turnaround_time[i]);
	}
	average_turnaround_time = (float)sum / n;
	printf("\nAverage Waiting Time: %f\n", average_wait_time);
	printf("Average Turnaround Time: %f\n", average_turnaround_time);

}


void rr(int arr[], int bur[], int n) {
	int count, j, time, remain, flag = 0, time_quantum; 
	int wait_time = 0, turnaround_time = 0, rt[10]; 

	printf("Round Robin\n");

	remain = n;
	printf("Enter Time Quantum: "); 
	scanf("%d",&time_quantum); 
    printf("\nPID Arrtime BurstTime WaitTime Turnaroundtime ");
	for(time=0,count=0;remain!=0;) { 
		if(rt[count] <= time_quantum && rt[count] > 0) { 
		  time += rt[count]; 
		  rt[count] = 0; 
		  flag = 1; 
		} 
		else if(rt[count] > 0) { 
		  rt[count] -= time_quantum; 
		  time += time_quantum; 
		} 
		if(rt[count] == 0 && flag == 1) { 
		  remain--; 
		  printf("\n%s\t%d\t%d\t%d\n", PID[count], time-arr[count], time-arr[count],-bur[count]); 
		  wait_time+=time-arr[count]-bur[count]; 
		  turnaround_time+=time-arr[count]; 
		  flag=0; 
		} 
		if(count == n-1) 
		  count = 0; 
		else if (arr[count+1] <= time) 
		  count++; 
		else 
		  count = 0; 
	} 
	printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n); 
	printf("Avg Turnaround Time = %f\n",turnaround_time*1.0/n); 
 
}


int main(int argc, char *argv[]) {
/*
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    for(int i=0; i<n; i++)
    {
        printf("Enter the PID, Arrival Time, and Burst Time: ");
        scanf("%s%d%d",PID[i],&arr[i],&bur[i]);
    }
*/
	FILE *file;
	char buff[255], f, id[10];
	int len = 0, counter = 0, num_proc = 0, arrival[10], burst[10];
	
	file = fopen(argv[1], "r");
	f = fgetc(file);
	if (file == NULL) {
		printf("error opening file");
		exit(0);
	}
	while ((f = fgetc(file)) != EOF) {
		//printf("yikes");
		if(isdigit(f)) {
			//printf("%i %c %i\n",len, f, counter);
			switch(len) {
				case 0:
					num_proc = f - '0';
					len++;
					break;
				case 1:
					id[counter] = f;
					len++;
 					break;
				case 2:
					arrival[counter] = f - '0';
					len++;
					break;
				case 3:
					burst[counter] = f - '0';
					len = 1;
					if (counter == num_proc-1) {
						counter = counter % (num_proc-1);
						break;
					} 
					counter++;
					break;
				default:
					printf("error");
					break;
			}
			f = fgetc(file);
		}
	}
	
	printf("Number of processes: %i\n", num_proc);
	
	for (int i = 0; i < num_proc; i++) {
		printf("id:%c \t arrival:%i \t burst:%i\n", id[i], arrival[i], burst[i]);
	}

	//printf("ids:%ls arrivals:%ls\n bursts:%ls\n", id, arrival, burst);
/*
	while (fgets(buff, 10, file) != NULL) {
		if(!isalpha(buff[0]) && strlen(buff)>0) {
			//printf("file=%s", buff);
			token = strtok(buff, " ");
			while (token != NULL) {
				if (len == 1) {
					num_proc = atoi(token);
					printf("%i\n", num_proc);
					len++;
				}
				else {
					strcpy(buff, token);
					printf("%s", buff);
					len++;
				}
				token = strtok(NULL," ");
			}
		}
	}
	printf("\n");
*/

	printf("\n\n");
	fcfs(arrival, burst, num_proc);
	printf("\n\n");
	sjf(arrival, burst, num_proc);
	printf("\n\n");
	rr(arrival, burst, num_proc);

	return(0);
}
