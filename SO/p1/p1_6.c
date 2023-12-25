/*
Use el ejercicio 1a) y cree una variable global de tipo entero inicializada a 0. Haga que cada hijo
aumente en uno el valor de esa variable global y que el padre imprima el resultado final. ¿Qué
ocurre? Correcto, su valor no se modifica porque los hijos son procesos nuevos que no comparten
memoria. Para ello, y concretamente en sistemas basados en POSIX, se utilizan métodos de
intercomunicación de procesos como son memoria compartida y semáforos, los cuales se estudiarán
en otra práctica de la asignatura.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <número_de_procesos>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int var = 0;

    int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "El número de procesos debe ser un entero positivo.\n");
        return EXIT_FAILURE;
    }

    printf("Proceso padre (ID %d)\n", getpid());

    for (int i = 1; i <= n; i++) {
        pid_t child_pid = fork();

        if (child_pid < 0) {
            var=i;
            perror("Error al crear el proceso hijo");
            return EXIT_FAILURE;
        } else if (child_pid == 0) { // Proceso hijo
            printf("Proceso hijo %d (ID %d) de padre %d\n", i, getpid(), getppid());
            exit(EXIT_SUCCESS);
        }
    }

    // Proceso padre esperando a que todos los hijos terminen
    int status;
    for (int i = 1; i <= n; i++) {
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Proceso hijo %d terminado con estado %d\n", i, WEXITSTATUS(status));
        } else {
            printf("Proceso hijo %d terminado anormalmente\n", i);
        }
    }

    printf("[%d] es Var // Todos los procesos hijos han terminado.\n",var);
    return EXIT_SUCCESS;
}
