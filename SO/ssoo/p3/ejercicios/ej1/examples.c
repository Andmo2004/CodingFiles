#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void func1()
{
    pthread_mutex_lock(&mutex);
        //PROCESS HERE
    pthread_mutex_unlock(&mutex);
}


//_____________________________//

sem_t sem1;

void func2()
{
    sem_wait(&sem1);
        //PROCESS HERE
    sem_post(&sem1);
}

int main(int argc, char** argv)
{
    sem_init(&sem1, 0, 1);
}