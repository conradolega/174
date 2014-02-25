#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
	sem_t *mutex;
	sem_t *sem;
	int counter;
} barrier_t;

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

int main(int argc, char* argv[]) {

}
