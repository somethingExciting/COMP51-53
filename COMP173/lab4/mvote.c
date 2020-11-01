#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
	srand(time(NULL));
	int fd[100][2]; //fd[0] = reading; fd[1] = writing; max=100
	int yes = 0, no = 0, voters = 0, temp, restart = 0;
	int choice; 
	pid_t childpid[100]; 

	while(voters < 3 || voters > 100) {
		printf("Enter an amount of voters (max=100): ");
		scanf("%i", &voters);
	}

	while(restart == 0) {
		for (int i = 0; i < voters; i++) {
			//printf("Creating pipefd[%d]\n", i);
			temp = rand() % 2;
			pipe(fd[i]);
			if((childpid[i] = fork()) == -1) {
				perror("error on fork");
				exit(1);
			}		
			if(childpid[i] == 0) {
				/* Child process closes up input side of pipe */
				close(fd[i][0]);

				if(write(fd[i][1], &temp, sizeof(int)) == -1) {
					printf("Write failed...\n ");
				}
				exit(0);
			}
			else {
				/* Parent process closes up output side of pipe */
				close(fd[i][1]);

				/* Read in a string from the pipe */
				if(read(fd[i][0], &temp, sizeof(int)) == -1) {
					printf("Read failed...\n"); 
				}
				if(temp == 0) {
					yes++;
				}
				else {
					no++;
				}
			}
		}

		printf("YES: %d \t NO: %d \n", yes, no);
		if(yes > no) {
			printf("Judge decides on YES.\n");
		}
		else if(yes < no) {
			printf("Judge decides on NO.\n");
		}
		else {
			printf("Judge decides on a draw.\n");
		}
		//printf("%i",restart);
		if (restart != 1) {
			printf("Vote again? (Y/N) (1 for yes, anything else for no): ");
			scanf("%i", &choice);
			choice = toupper(choice);
			yes = 0;
			no = 0;
		}
		if(choice != 1) {
			printf("Voting has ended.\n");
				restart = 1;
		}

	} 

	return (0);
}
