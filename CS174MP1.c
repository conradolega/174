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

int main(int argc, char* argv[]) {

}
