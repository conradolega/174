#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 5

typedef struct {
	int rank;
	sem_t *sem;
} philo_t;

int main() {
	int i = 0;
	pthread_t philosophers[NUM_THREADS];
	philo_t *philo_data[NUM_THREADS];
	sem_t sem;

	sem_init(&sem, 0, 1);
	for (i = 0; i < NUM_THREADS; i++) {
		philo_data[i] = (philo_t *) malloc(sizeof(philo_t));
		philo_data[i]->rank = i;
		philo_data[i]->sem = &sem;
	}

	pthread_exit(NULL);
}
