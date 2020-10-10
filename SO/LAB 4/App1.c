#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

int main() {
	
	sem_t Sem;

	sem_init(&Sem, 0, 1);

	sem_wait(&Sem);
	
	sem_post(&Sem);

	sem_wait(&Sem);

	sem_post(&Sem);

	printf("Done\n");

	return 0;
}