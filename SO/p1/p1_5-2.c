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
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <número1> <número2>\n", argv[0]);
        return 1;
    }

    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);

    pid_t child1, child2;

    child1 = fork();

    if (child1 == 0) {
        // Proceso hijo 1
        printf("Proceso hijo 1 calculando el factorial de %d\n", num1);
        char num1_str[10];
        snprintf(num1_str, sizeof(num1_str), "%d", num1);
        char *args[] = {"./factorial", num1_str, NULL};
        execv(args[0], args);
    } else if (child1 < 0) {
        perror("Error al crear el primer proceso hijo");
    }

    child2 = fork();

    if (child2 == 0) {
        // Proceso hijo 2
        printf("Proceso hijo 2 calculando el factorial de %d\n", num2);
        char num2_str[10];
        snprintf(num2_str, sizeof(num2_str), "%d", num2);
        char *args[] = {"./factorial", num2_str, NULL};
        execv(args[0], args);
    } else if (child2 < 0) {
        perror("Error al crear el segundo proceso hijo");
    }

    // Esperar a que ambos procesos hijos terminen
    int status;
    waitpid(child1, &status, 0);
    waitpid(child2, &status, 0);

    return 0;
}
