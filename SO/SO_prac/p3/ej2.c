#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

int par=0, impar=0;
sem_t s1;

int *RandomNumbers()
{
    int *suma = malloc(sizeof(int*));
    sem_wait(&s1);
    for(int i=0; i<5; ++i)
    {
        int x = rand()%11;
        *suma = *suma + x;
    }
    pthread_exit((void*)suma);
}

int main(int argc, char** argv)
{
    if(argc<2)
    {
        printf("Numero de argumentos insuficiente...\n");
        exit(EXIT_FAILURE);
    }
    //printf("pin_1\n");
    int hebras = atoi(argv[1]);
    //printf("pin_2\n");
    //printf("pin_3\n");
    if(hebras<1)
    {
        printf("Numero de hebras inferior a 1...\n");
        exit(EXIT_FAILURE);   
    }
    srand(time(NULL));
    pthread_t hilos[hebras];
    sem_init(&s1, 0, 1);
    //printf("pin_4\n");

    for(int i=0; i<hebras; ++i)
    {
        if(pthread_create(&hilos[i], NULL, (void*)RandomNumbers, NULL))
        {
            perror("pthread_create ERROR\n");
            printf("ERROR AL CREAR HILO\n");
            exit(EXIT_FAILURE);
        }
        sem_post(&s1);
    
    }
    //printf("pin_5\n");

    for(int i=1; i<hebras+1; ++i)
    {
        //printf("pin_6\n");
        int suma2 = 0;
        if(i%2==0)
        {
            //printf("pin_7\n");
            if(pthread_join(hilos[i-1], (void**)&suma2))
            {
                perror("pthread_join ERROR\n");
                printf("ERROR AL CREAR HILO\n");
                exit(EXIT_FAILURE); 
            }
            printf("Soy la hebra %d, y la suma = %ls\n", i-1, &suma2);
            par += &suma2;
        }
        else
        {
            //printf("pin_8\n");
            if(pthread_join(hilos[i-1], (void**)&suma2))
            {
                perror("pthread_join ERROR\n");
                printf("ERROR AL CREAR HILO\n");
                exit(EXIT_FAILURE); 
            }
            printf("Soy la hebra %d, y la suma = %ls\n", i-1, &suma2);
            impar += &suma2;
        }
    }
    printf("La variable par = %d\n", par);
    printf("La variable impar = %d\n", impar);
    printf("Programa terminado con exito\n");
    exit(EXIT_SUCCESS);

}