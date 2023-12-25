
/*EJERCICIO 2 PRÁCTICA 3*/
/*Implemente un programa que cree un número N de hilos, donde N será un argumento al programa.
Tenga en cuenta los siguientes supuestos y condiciones:
 Los N hilos comparten dos variables, una llamada "par" e "impar" inicializadas a 0.
 Los hilos deben recibir un valor entero de 1 a N que indica el orden en el cuál se ha creado
el hilo. Así, el primer hilo creado recibe 1, el segundo 2, etc.
 Cada hilo debe generar 5 números aleatorios entre 0 y 10.
 Los hilos de índice de creación par deben ir sumando a la variable "par" los números que
generan.
 Los hilos de índice de creación impar deben ir sumando a la variable "impar" los números
que generan.
 Una vez finalizado cada hilo, éste debe devolver al programa principal la suma total de los
números que ha generado.
 El programa principal debe mostrar la suma devuelta por cada hebra y el valor final de las
variables “par” e “impar”.*/


#include <semaphore.h>
#include <pthread.h>
#include <stdint.h>  // Include <stdint.h> for intptr_t
#include <stdlib.h>
#include <stdio.h>

// Variables par/impar e inicializamos a 0.
int par = 0;
int impar = 0;

// Semaforo general
sem_t sgeneral;

// Declaramos la función aleatorio.
void *aleatorio(void *arg);

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("--Número de argumentos inválido...\n");
        return -1;
    }

    int numhebras = atoi(argv[1]); // Declaramos variable con el número de hebra.
    pthread_t hilos[numhebras];    // Inicializador de los hilos en un vector con capacidad numhebras.

    for (int i = 0; i < numhebras; i++) {
        if (pthread_create(&hilos[i], NULL, aleatorio, (void *)(intptr_t)i)) {
            perror("pthread_create error");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < numhebras; i++) {
        void *result;
        if (pthread_join(hilos[i], &result)) {
            perror("pthread_create error");
            exit(EXIT_FAILURE);
        }

        int suma = (intptr_t)result;
        printf("[HILO --%d] -> la var suma = %d\n", i, suma);
    }

    printf("Valor final de la variable par: %d\n", par);
    printf("Valor final de la variable impar: %d\n", impar);

    return 0;
}

void *aleatorio(void *arg) {
    int i = (intptr_t)arg;
    int suma = 0;

    for (int j = 0; j < 5; j++) {
        int f1 = drand48() * 10;
        suma += f1;
    }
    if (i % 2 == 0) {
        par += suma;
    } else {
        impar += suma;
    }

    pthread_exit((void *)(intptr_t)suma);
}

