/*Implemente un programa que cree un vector de 10 elementos relleno con números aleatorios
entre 1 y 9. No cree el vector de manera global, declárelo en el main(). Reparta ese vector entre 2
hebras o 5 hebras a partes iguales, según se indique por linea de argumentos un 2 o un 5, de forma
que cada hebra sume la parte del vector que le corresponda y se lo devuelva al hilo principal, el cual
mostrará la suma de los resultados devuelto por las hebras creadas.
Ejemplo de invocación del programa para crear 5 hebras que se repartan el vector: ./a.out 5*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int *vector;
    int hebras;
    int i;
}Vector;

void rellenaVector(int *vector)
{
    srand(time(NULL));
    for(int i=0; i<10; ++i)
    {
        vector[i]=(rand()%9 + 1);
    }
}

void imprimeVector(int *vector)
{
    printf("El vector es:\n");
    for(int i=0; i<10; ++i)
    {
        printf(" [%d] ",vector[i]);
    }
    printf("\n");
}

void sumaVector(void* d)
{
    int *suma = malloc(sizeof(int));
    *suma = 0;
    Vector *v;
    v = (Vector*) d;

    if(v->hebras == 2)
    {
        int j = v->i;
        for(j;j<(v->i)+5;j++)
        {
            printf("[HEBRA %lu]\n", pthread_self());
            *suma = *suma + v->vector[j];
        }
        v->i = v->i + 5;
        pthread_exit((void**)suma);
    }

    else
    {
        printf("[HEBRA %lu]\n", pthread_self());
        int j = v->i;
        for(j; j<(v->i)+2; j++)
        {
            printf("[HEBRA %lu]\n", pthread_self());
            *suma = *suma + v->vector[j];
        }
        v->i = v->i + 2;
        pthread_exit((void**)suma);  
    }
}

int main(int argc, char const *argv[])
{

    Vector *v = malloc(sizeof(Vector));

    if (argc != 2){                                     //Comprobamos que se haya llamado al programa de forma adecuada introduciendo 2 argumentos. Hacemos este if primero para evitar un segmentation fault en la linea 79
        printf("Error, llame al programa asi:\n");
        printf("./ej3 2 o /ej3 5\n");
        exit(EXIT_FAILURE);
    }

    v->hebras = atoi(argv[1]);                          //Guardamos en v->hebras el numero de hebras que queremos hacer
    v->i = 0;

    if (v->hebras != 2 && v->hebras != 5){              //Comprobamos que se haya llamado al programa de forma adecuada introduciendo un 2 o un 5
        printf("Error, llame al programa asi:\n");
        printf("./ej3 2 o /ej3 5\n");
        exit(EXIT_FAILURE);
    }

    v->vector = (int*)malloc(10*sizeof(int));
    rellenaVector(v->vector);
    imprimeVector(v->vector);

    pthread_t hilos[v->hebras];                        //Creamos un vector para almacenar los identificadores de los hilos, que seran 2 o 5 segun haya indicado el usuario
    int *sumaLinea, suma = 0; 

    for(int i=0; i< v->hebras; i++)
    {
        if(pthread_create(&(hilos[i]), NULL, (void*)sumaVector, (void*)v))
        {
            perror("pthread_create error");
            exit(EXIT_FAILURE);
        }
    }
    for(int i=0; i<2; i++)
    {
        if(pthread_join(hilos[i], (void**)&sumaLinea))
        {
            perror("pthread_join error");
            exit(EXIT_FAILURE);         
        }
        suma = suma + *sumaLinea;
    }

    printf("\nEl resultado de la suma es: %d\n", suma);
    exit(EXIT_SUCCESS);
}