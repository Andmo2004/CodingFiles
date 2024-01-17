#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int* funcion()
{
    int *sumar = malloc(sizeof(int));
    *sumar = 1;
    pthread_exit((void*)sumar);
}
int main(int argc, char** argv)
{
    if(argc<2){exit(EXIT_FAILURE);}
    printf("error b\n");
    int numhebras = atoi(argv[1]);
    printf("error a\n");
    if(numhebras<1){return -1;}

    pthread_t hilos[numhebras];
    int *suma, suma_total=0;



    for(int i=0; i< numhebras; ++i)
    {
        if(pthread_create(&hilos[i], NULL, (void*)funcion, NULL))//NULL -> argumentos
        {
            printf("error 1");
            exit(EXIT_FAILURE);
        }
    }
    for(int i=0; i< numhebras; ++i)
    {
        if(pthread_join(hilos[i], (void**)&suma))
        {
            printf("error 2");
            exit(EXIT_FAILURE);
        }
        suma_total += *suma;
    }
    printf("el res= %d\n", suma_total);
    exit(EXIT_SUCCESS);
}

