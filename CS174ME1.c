#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 5

int main() {
	int i = 0;
	pthread_t philosophers[NUM_THREADS];
	sem_t sem;

	sem_init(&sem, 0, 1);
	pthread_exit(NULL);
}
