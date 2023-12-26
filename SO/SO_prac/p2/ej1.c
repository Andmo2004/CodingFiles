#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

float *RandNumber()
{
    srand(time(NULL));

    float rand_number1 = drand48()*10;
    float rand_number2 = drand48()*10;
    printf("[HILO HIJO] El numero aleatorio 1 es: %f\n", rand_number1);
    printf("[HILO HIJO] El numero aleatorio 2 es: %f\n", rand_number2);

    float *suma=calloc(1, sizeof(float));
    *suma = rand_number1 + rand_number2;
    printf("[HILO HIJO] %0.2f + %0.2f = %0.2f\n", rand_number1, rand_number2, *suma);
    pthread_exit((void*)suma);
}

int main()
{
    int num_hebras;
    float total = 0, *fsuma;

    printf("Introduzca el numero de hebras a crear: \n"); 
    scanf("%d", &num_hebras);
    pthread_t hilos[num_hebras];

    if(num_hebras<0)
    {
        printf("No puedes crear un numero negativo de hebras\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i<num_hebras; i++)
    {
        if(pthread_create(&hilos[i], NULL, (void*)RandNumber, NULL))
        {
            perror("pthread_create error");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < num_hebras; i++){
        if(pthread_join(hilos[i], (void **) &fsuma)){
            perror("pthread_create error");
            exit(EXIT_FAILURE);
        }
        printf("[HILO PRINCIPAL] Valor recibido: %0.2f\n", *fsuma);
        total += *fsuma;
    }  

    printf("[HILO PRINCIPAL] La suma total es: %0.2f\n", total);
    exit(EXIT_SUCCESS); 
}