/*
    Cree un programa que reciba por la linea de argumentos un número y calcule el factorial de ese
número. Compílelo y compruebe su funcionamiento.

A partir de ahí cree otro programa aparte que reciba dos números enteros como parámetros en la
linea de argumentos y cree dos procesos hijos, de manera que cada uno calcule el factorial de uno
de los números usando el ejecutable creado anteriormente (“./a.out 3 5”). use para ello la familia de
funciones exec(). En el programa que calcula el factorial ponga un sleep(1) entre los cálculos
parciales para poder observar en consola como se van ejecutando los dos procesos que se lanzarán
en paralelo.

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <número_de_niveles>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int num = atoi(argv[1]);
    int fact=1;
    for(int i=1;i<=num;i++){
        fact = fact * i;
    }
    printf("El factorial de %d ese %d\n",num, fact);

}