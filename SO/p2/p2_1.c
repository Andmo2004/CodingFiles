/*PRÁCTICA 2: EJERCICIO 1*/

/*Implemente un programa que cree un número  N  de hebras. Cada hebra creará 2 números
aleatorios flotantes (consulte Moodle para la generación de aleatorios) y guardará su suma en una
variable   para   ello,   que   será   devuelta   a   la   hebra   principal   o   llamadora   (la   que   invocó
pthread_create()). 
La hebra principal ira recogiendo los valores devueltos por las N  hebras y los ira sumando en
una variable no global cuyo resultado mostrará al final por pantalla. Para ver que los resultados
finales son los que usted espera, muestre los 2 números que va creando cada hebra y su suma, de
forma que pueda comparar esas sumas parciales con la suma final que realizará el main() o hebra
principal.   Utilice   macros   definidas   y   comprobación   de   errores   en   sus   programas   (errno  y
comprobación de valores devueltos en cada llamada, con sus posibles alternativas).*/


#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>


void * aleatorio();
int main(){
    int n;
    printf("Introduzca el numero de hebras a crear: \n"); 
    scanf("%d", &n);
    float total = 0, * subtotal;
    pthread_t hilos[n];
    srand48(time(NULL));

    for (int i=0; i < n; i++){
        if(pthread_create(&hilos[i], NULL, (void *) aleatorio, NULL)){
            perror("pthread_create error");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < n; i++){
        if(pthread_join(hilos[i], (void **) &subtotal)){
            perror("pthread_create error");
            exit(EXIT_FAILURE);
        }
        printf("[HILO PRINCIPAL] Valor recibido: %0.2f\n", *subtotal);
        total += *subtotal;
    }   

    printf("[HILO PRINCIPAL] La suma total es: %0.2f\n", total);
    exit(EXIT_SUCCESS);
}

void * aleatorio(){
    float f1 = drand48()*10, f2 = drand48()*10;
    printf("[HILO HIJO] El numero aleatorio 1 es: %f\n", f1);
    printf("[HILO HIJO] El numero aleatorio 2 es: %f\n", f2);
    float * f3 = calloc(1, sizeof(float));
    *f3 = f1+f2;
    printf("[HILO HIJO] %0.2f + %0.2f = %0.2f\n", f1, f2, *f3);
    pthread_exit((void *) f3);
}
