#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
	int segment_id;				//identifier of the shared memory segment 
	unsigned short mode; 		// permissions of the segment 
	struct shmid_ds shmbuffer; //the shared memory segment 

	// 0. parse the command line arguement
	// segment_id = user input
	// 1. if user doesn't provide segment_id, generate with shmget()
	if (argv[1] == NULL) {
		segment_id = shmget(IPC_PRIVATE, 100*sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
	}
	else {
		segment_id = atoi(argv[1]);
	}
	shmbuffer.shm_perm.uid = segment_id;
	printf("ID: %d\n", shmbuffer.shm_perm.uid);
	printf("KEY: %d\n", shmbuffer.shm_perm.__key);

	if (shmctl(segment_id, IPC_STAT, &shmbuffer) == -1) {
 		printf("Unable to access segment %d\n", segment_id);
 		return 0;
	}
	printf("MODE: ");
	// Output mode in the right format
	mode = shmbuffer.shm_perm.mode;
	/** OWNER */
	if (mode & 0400)
		printf("r");
	else
		printf("-");
	if (mode & 0200)
		printf("w");
	else
		printf("-");
	if (mode & 0100)
		printf("a");
	else
		printf("-");

	/** GROUP */
	if (mode & 0040)
		printf("r");
	else
		printf("-");
	if (mode & 0020)
		printf("w");
	else
		printf("-");
	if (mode & 0010)
		printf("a");
	else
		printf("-");

	/** WORLD */
	if (mode & 0004)
		printf("r");
	else
		printf("-");
	if (mode & 0002)
		printf("w");
	else
		printf("-");
	if (mode & 0001)
		printf("a");
	else
		printf("-");

	printf("\nOWNER_UID: %i\n", shmbuffer.shm_cpid);
	printf("SIZE: %lu\n", shmbuffer.shm_segsz);
	printf("ATTACHES: %lu\n", shmbuffer.shm_nattch);

}
