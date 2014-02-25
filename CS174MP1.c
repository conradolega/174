#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int NUM_THREADS;

typedef struct {
	sem_t *mutex;
	sem_t *sem;
	int counter;
} barrier_t;

typedef struct {
	barrier_t *barrier;
	int rank;
} data_t;

void barrier_init(barrier_t *barrier, int threads) {
	barrier->mutex = (sem_t *) malloc(sizeof(sem_t));
	barrier->sem = (sem_t *) malloc(sizeof(sem_t));
	sem_init(barrier->mutex, 0, 1);
	sem_init(barrier->sem, 0, 0);
	barrier->counter = 0;
}

void barrier_wait(barrier_t *barrier) {
	sem_wait(barrier->mutex);
	barrier->counter++;
	if (barrier->counter == NUM_THREADS) {
		printf("Last thread to enter the barrier\n");
		int i;
		for (i = 0; i < NUM_THREADS; i++) {
			sem_post(barrier->sem);
		}
	}
	sem_post(barrier->mutex);
	sem_wait(barrier->sem);
}

void *thread(void *d) {
	data_t *data = (data_t *) d;
	int rank = data->rank;
	printf("Thread %d waiting...\n", rank);
	barrier_wait(data->barrier);
	printf("Thread %d exiting...\n", rank);
	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	NUM_THREADS = atoi(argv[1]);
	int i;
	barrier_t barrier;
	barrier_init(&barrier, NUM_THREADS);

	pthread_t threads[NUM_THREADS];
	data_t data[NUM_THREADS];

	for (i = 0; i < NUM_THREADS; i++) {
		data[i].barrier = &barrier;
		data[i].rank = i;
		pthread_create(&threads[i], NULL, thread, (void *) &data[i]);
	}

	pthread_exit(NULL);
}
