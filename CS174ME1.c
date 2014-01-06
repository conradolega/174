#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
	int rank;
	sem_t *left_fork;
	sem_t *right_fork;
} philo_t;

void *philosopher(void *philo_data) {
	philo_t *data = (philo_t *) philo_data;
	while (1) {
		if (data->rank == 0) {
			sem_wait(data->left_fork);
			sem_wait(data->right_fork);
			usleep(2000000);
			sem_post(data->left_fork);
			sem_post(data->right_fork);
		}
		else {
			sem_wait(data->right_fork);
			sem_wait(data->left_fork);
			usleep(2000000);
			sem_post(data->right_fork);
			sem_post(data->left_fork);
		}
	}
	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	int i = 0;
	int NUM_THREADS = atoi(argv[1]);
	sem_t forks[NUM_THREADS];
	pthread_t philosophers[NUM_THREADS];
	philo_t *philo_data[NUM_THREADS];

	for (i = 0; i < NUM_THREADS; i++) sem_init(&forks[i], 0, 1);

	for (i = 0; i < NUM_THREADS; i++) {
		philo_data[i] = (philo_t *) malloc(sizeof(philo_t));
		philo_data[i]->rank = i;
		if (i - 1 < 0) philo_data[i]->left_fork = &forks[NUM_THREADS - 1];
		else philo_data[i]->left_fork = &forks[i - 1];
		philo_data[i]->right_fork = &forks[i];
		pthread_create(&philosophers[i], NULL, philosopher, (void *) philo_data[i]);
	}

	pthread_exit(NULL);
}
