#include <stdio.h> 

#define MEM_FILE 512 //size of the "memory" file (512KB)
#define FRAME_SIZE 512 //size of each frame (512 bytes)
#define FRAMES 1024 //number of frames

int main(int argc, char *argv[]) {
	FILE *file;
	char filename[20], line[50];
	int free_frames[], num_frames[FRAMES];
	//int num_pages = 0;

	file = fopen(argv[1], "r");
	if(argv[1] == NULL) {
		printf("Error opening file...");
		exit(0);
	}
	if(file) {
		while(fgets(line, 10, file) != NULL) {


		}
	}

	return 0;
}
