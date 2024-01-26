#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/time.h>
#include <semaphore.h>
#include <time.h>

#define TAM_BUFFER 5

sem_t mutex;
sem_t full;
sem_t empty;

int indiceConsumicion=0;
int indiceProduccion=0;
int buffer[TAM_BUFFER];

void ProducirDato(int numero)
{
    buffer[indiceProduccion]=numero;//RANDOM_NUMBER
    indiceProduccion = (indiceProduccion+1)%TAM_BUFFER;
        for(int i=0; i<TAM_BUFFER; i++) {printf("|%d", buffer[i]);}
    printf("|\n");
}

int ConsumirDato()
{
    int numConsumido = buffer[indiceConsumicion];
    buffer[indiceConsumicion] = '\0';
    indiceConsumicion=(indiceConsumicion+1)%TAM_BUFFER;
        for(int i=0; i<TAM_BUFFER; i++) {printf("|%d", buffer[i]);}
    printf("|\n");
    return numConsumido;
}

void *productor()
{
    for(int i=0; i<5; ++i)
    {
        sem_wait(&empty);
        sem_wait(&mutex);

        int numero = rand()%101;        
        ProducirDato(numero);
    
        printf("Produciendo un %d, en posicion %d\n", numero, i+1);
        fflush(NULL);

        sem_post(&mutex);
        sem_post(&full);
    }
    pthread_exit(NULL);
}

void *consumidor()
{
    for(int i=0; i<5; ++i)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        
        int numero = ConsumirDato();

        printf("Consumiendo un %d, de la posicion %d\n", numero, i+1);
        fflush(NULL);

        sem_post(&mutex);
        sem_post(&empty);
    }
    pthread_exit(NULL);
}

int main(int argc, char** argv)
{
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, TAM_BUFFER);
    sem_init(&full, 0, 0);
    
    srand(time(NULL));

    //CREACION DE HILOS
    pthread_t ptid_pr, ptid_cs;
    if(pthread_create(&ptid_pr, NULL, (void*)productor), NULL)
    {
        perror("Error en la op pthread_create\n");
        printf("Error al crear el hilo\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(&ptid_cs, NULL, (void*)consumidor), NULL)
    {
        perror("Error en la op pthread_create\n");
        printf("Error al crear el hilo\n");
        exit(EXIT_FAILURE);
    }

    //PTHREAD_JOIN
    if(pthread_join(ptid_pr, NULL))
    {
        perror("Error en la op pthread_join\n");
        printf("Error al crear el hilo\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(ptid_cs, NULL))
    {
        perror("Error en la op pthread_join\n");
        printf("Error al crear el hilo\n");
        exit(EXIT_FAILURE);
    }
    printf("Todo terminado\n");
    exit(EXIT_SUCCESS);
}
