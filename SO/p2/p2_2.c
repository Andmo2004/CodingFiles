/*PRÁCTICA 2: EJERCICIO 2*/

/*Implemente un programa que cuente las líneas de los ficheros de texto que se le pasen como
parámetros y al final muestre el número de líneas totales (contando las de todos los ficheros juntos).
Ejemplo de llamada: ./a.out fichero1 fichero2 fichero3
Debe crear un hilo por cada fichero indicado por linea de argumentos, de forma que todos los
ficheros se procesen de manera paralela, uno por cada hilo.*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void * cuentaLineas(void * fichero){
    printf("Contando el fichero\n");
    int * nLineas = malloc(sizeof(int));
    FILE * f = fopen(fichero, "r");
    *nLineas=0;
    char s[264];

    if(f==NULL){
        perror("Fopen error");
        fprintf(stderr, "errno: %i\n", errno);
        exit(EXIT_FAILURE);
    }
    while(fgets(s, 264, f)){
        *nLineas = *nLineas + 1;
    }
    pthread_exit((void *) nLineas);
}


int main(int argc, char** argv){
    int numhilos = (argc-1);
    pthread_t hilos[numhilos];
    int * nLineas;

    for (int i=0; i < numhilos; i++){
        if(pthread_create(&hilos[i], NULL, (void *) cuentaLineas, argv[i+1])){
            perror("pthread_create error");
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < numhilos; i++){
        if(pthread_join(hilos[i], (void **) &nLineas)){
            perror("pthread_create error");
            exit(EXIT_FAILURE);
        }
    }

    int nline = &nLineas;
    printf("El numero de lineas del fichero: %ls\n", &nline);

}