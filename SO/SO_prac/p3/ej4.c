#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t s0;
sem_t s1;

void *escribirA(void *p)
{
    int i;
    for(int i=0; i<5; ++i)
    {
        sem_wait(&s1);
        printf("A");
        fflush(NULL);
        sem_post(&s0);
    }
    pthread_exit(NULL);
}

void *escribirB(void *p)
{
    int i;
    for(int i=0; i<5; ++i)
    {
        sem_wait(&s0);
        printf("B");
        fflush(NULL);
        sem_post(&s1);
    }
    pthread_exit(NULL);
}

int main(int argc, char** argv)
{
    sem_init(&s0, 0, 1);
    sem_init(&s1, 0, 0);

    pthread_t ptid1, ptid2;

//    for(int i=0; i<2; ++i)  //¿? NO SIRVE AQUI
    
    if(pthread_create(&ptid1, NULL, (void*)escribirA, NULL))
    {
        perror("pth_create error\n");
        printf("Error al crearse el hilo\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(&ptid2, NULL, (void*)escribirB, NULL))
    {
        perror("pth_create error\n");
        printf("Error al crearse el hilo\n");
        exit(EXIT_FAILURE);
    }
    
//    for(int i=0; i<2; ++i)  //¿?
    
    if(pthread_join(ptid1, NULL))
    {
        perror("pth_join error\n");
        printf("Error al recoger el hilo\n");
        exit(EXIT_FAILURE);   
    }
    if(pthread_join(ptid2, NULL))
    {
        perror("pth_join error\n");
        printf("Error al recoger el hilo\n");
        exit(EXIT_FAILURE);   
    }

    printf("\n");
    exit(EXIT_SUCCESS);
}