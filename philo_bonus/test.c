#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>
#include <errno.h>
#include <semaphore.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

sem_t *semaphore;

static int counter = 0;

void* worker1(void* args) {
	sleep(3);
}


int main() {
	pthread_t thread1;


	pthread_create(&thread1, NULL, worker1, NULL);

	pthread_detach(thread1);
}