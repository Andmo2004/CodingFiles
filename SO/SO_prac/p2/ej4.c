/*Implemente un programa que cree dos hebras y cada una incremente 10000 veces en un bucle
una variable global (recuerde que la variable global, al estar en el mismo espacio de memoria para
las dos hebras, es compartida, y que su uso es “peligroso”). Imprima al final del programa principal
el valor de la variable (en cada ejecución posiblemente obtenga un valor diferente a 20000 –
problema de concurrencia –). Intente razonar el resultado, el cual le servirá como concepto
introductorio de la siguiente práctica de la asignatura*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

int variable_global = 0;

void* Incrementox10000()
{
    printf("[HEBRA %lu]", pthread_self());
    for(int i=0; i<10000; ++i)
    {
        variable_global++;
    }
    printf("La variable global tras el incremento de la hebra vale %d\n", variable_global);
    pthread_exit(NULL);
}

int main()
{
    pthread_t hilos[2];
    
    for(int i=0; i<2; ++i)
    {
        if(pthread_create(&hilos[i], NULL, (void *)Incrementox10000, NULL))
        {
            printf("Error al crear la hebra. Codigo de error %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }
    for(int i=0; i<2; ++i)
    {
        if(pthread_join(hilos[i], NULL))
        {
            printf("Error al esperar la hebra. Codigo de error %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }
    
    printf("La variable global tras la creacion e incremento de ambas hebras vale %d\n", variable_global);      //Imprimimos por pantalla el valor de la variable global tras ser incrementada
    exit(EXIT_SUCCESS);
}