#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

int *CuentaLineas(void* argv)
{
    int *contador = malloc(sizeof(int));
    *contador = 0;

    char *fname = (char*)argv; 
    char aux[256];

    int caracter;
    FILE* archivo=fopen(fname, "r");

    if (archivo==NULL){                           //Si el fichero no se ha abierto correctamente, nos saltara el error

        printf("Error al abrir el archivo. Codigo de error: %d\n", errno);
        pthread_exit(NULL);                 //No ponemos exit(EXIT_FAILURE) porque si la usamos, en vez de finalizar la hebra, finalizaria el proceso (el programa)
    }

    while (fgets(aux, 256, archivo)!=NULL){       //Cada vez que entremos en el bucle aumentara el numero de lineas
        ++*contador;                       //Aumentamos el numero de lineas que tiene el fichero
    }
    fclose(archivo);
    printf("[HILO HIJO] El numero de lineas de este archivo = %d\n", *contador);
    pthread_exit((void*)contador);
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Error debe llamar al programa de la siguiente forma: ./ej2 nombrefichero1, nombrefichero2, ..., nombreficheron\n");
        exit(EXIT_FAILURE);
    }

    int num_total_lineas=0, num_hebras = argc-1, *lineas_archivo;
    pthread_t hilos[num_hebras];

    for(int i=0; i<num_hebras; i++)
    {
        if(pthread_create(&hilos[i], NULL, (void*)CuentaLineas, (void*)argv[i+1]))
        {
            perror("pthread_create error");
            exit(EXIT_FAILURE);
        }
    }
    for(int i=0; i<num_hebras; i++)
    {
        if(pthread_join(hilos[i], (void**)&lineas_archivo))
        {
            perror("pthread_join error");
            exit(EXIT_FAILURE);           
        }
        printf("[HILO PADRE] El valor recibido es %d\n",*lineas_archivo);
        num_total_lineas = num_total_lineas + *lineas_archivo;
    }
    printf("[HILO PADRE] el numero de lineas total = %d \n", num_total_lineas);
    exit(EXIT_SUCCESS);
}