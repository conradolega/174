#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
	sem_t *mutex;
	sem_t *sem;
	int counter;
} barrier_t;

int main(int argc, char* argv[]) {

}
