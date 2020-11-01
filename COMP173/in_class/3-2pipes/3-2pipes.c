#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
	int fd[2]; //fd[0] = reading; fd[1] = writing
	int nbytes = 0, length = 0; 
	pid_t childpid; 
    char string[] = "Yikes!\n";
    char readbuffer[80];

	printf("Orginal string: %s", string);

	pipe(fd);

	printf("Sending through pipes...\n");

    if((childpid = fork()) == -1) {
		perror("error on fork");
		exit(1);
	}
	
	if(childpid == 0) {
		/* Child process closes up input side of pipe */
		close(fd[0]);

        write(fd[1], string, (strlen(string)+1));
		exit(0);
    }
    else {
        /* Parent process closes up output side of pipe */
        close(fd[1]);

        /* Read in a string from the pipe */
        nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
		length = strlen(readbuffer);
		for (int i = 0; i < length; i++) {
			if (isupper(readbuffer[i])) {
				readbuffer[i] = tolower(readbuffer[i]);
			}
			else if (islower(readbuffer[i])) {
				readbuffer[i] = toupper(readbuffer[i]);
			} 
		}
        printf("Received string: %s", readbuffer);
		printf("No. of bytes: %i\n", nbytes);
    }

	return (0); 

}
