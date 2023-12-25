/*
Cree dos hilos de manera que uno ejecute escribirA() y el otro escribirB(). Implemente un programa
que introduzca los semáforos oportunos para que la salida sea BABABABABA. No olvide indicar
los valores iniciales de los semáforos que utilice.
*/

#include <semaphore.h>
#include <pthread.h>
#include <stdint.h>  // Include <stdint.h> for intptr_t
#include <stdlib.h>
#include <stdio.h>

sem_t s1;
sem_t s2;

void *escribirA (void *p)
{
 int i;
 for (i= 0; i< 5; i++)
 {
 sem_wait(&s2);   
 printf ("A");
 fflush(NULL);
 sem_post(&s1);
 }
 pthread_exit(NULL);
}

void *escribirB (void *p)
{
 int i;
 for (i= 0;i< 5; i++)
 {
 sem_wait(&s1);
 printf ("B");
 fflush(NULL);
 sem_post(&s2);
 }
 pthread_exit(NULL);
}

int main(){
    pthread_t ptid1, ptid2;
    sem_init(&s1,0,1);
    sem_init(&s2,0,0);

    printf("Se inicia el create:\n");

    if (pthread_create(&ptid1, NULL, escribirA, NULL)) {
        perror("pthread_create error");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&ptid2, NULL, escribirB, NULL)) {
        perror("pthread_create error");
        exit(EXIT_FAILURE);
    }

    printf("Se inicia el join:\n");

    if (pthread_join(ptid1, NULL)) {
        perror("pthread_create error");
        exit(EXIT_FAILURE);
    }
    if (pthread_join(ptid2, NULL)) {
        perror("pthread_create error");
        exit(EXIT_FAILURE);
    }
printf("\n");

}