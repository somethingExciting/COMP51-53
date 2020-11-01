#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define HAIRCUT 2 //length of a single haircut
#define OPEN_TIME 5 //amount of time that the shop is open

//shared variable
int flag = 0; //flag to stop barber when done

//semaphores
sem_t barb_slep; //barber sleeps if no customers
sem_t seat; //customer sits if open and waits until barber is done cutting hair 

//thread prototypes
void *barber(void *param); //barber thread 
void *customer(void *param); //customer thread

int main() {
	srand(time(NULL));
	pthread_t btid; //barber tid
	pthread_t ctid[OPEN_TIME]; //array of customer tids
	int arr[OPEN_TIME], i, x;

	for(i = 0; i < OPEN_TIME; i++) {
		arr[i] = i;
	}

	//intializing semaphores
	sem_init(&barb_slep, 0, 0);
	sem_init(&seat, 0, 0);

	pthread_create(&btid, NULL, barber, NULL); //create barber pthread

	//let's create some customers!
	for(i = 0; i < OPEN_TIME; i++) {
		if(rand() % 2 == 0) {
			pthread_create(&ctid[i], NULL, customer, (void* )&arr[i]);
			x++;
		}
	}

	for(i = 0; i < x; i++) {
		pthread_join(ctid[i], NULL); 
	}

	printf("Shop is now closed\n");
	flag = 1; //barber stops since it is closing time
	sem_post(&barb_slep); //barber wakes and leaves
	pthread_join(btid, NULL);
	//printf("Shop is now closed\n");
    pthread_exit(NULL);

	//printf("Barber serviced %d customers today.\n", served);

	return 0;
}

void *customer(void *param) { //signal
	int num = *(int *)param;

	printf("Customer %d arrives \n", num);
	//sleep(HAIRCUT);
	//printf("Customer %d woke up barber \n", num);
	sem_post (&barb_slep); //wakes up barber if he is asleep
	sem_wait(&seat); //wait for haircut to finish
	printf("Customer %d leaves \n", num);

	return 0;
}


void *barber(void *param) { //wait
	while(!flag) {
		printf("Barber is sleeping, waiting for customer...\n");
		sem_wait(&barb_slep); //waiting for customer
		if(!flag) {
			printf("Awake! Doing barberly actions...\n");
		  	sleep(HAIRCUT);
			printf("Done!\n");
			sem_post(&seat);
			//served++;
		}
	}
	return 0;
}

