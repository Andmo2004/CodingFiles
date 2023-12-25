/* Implemente un programa que pidiendo un número de procesos totales N por línea de argumentos
cree las siguientes jerarquías de procesos en abanico (los procesos ejecutan en paralelo):*/

/*CORRECTO*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main() {

    int n;

    printf("Introduce el numero de hijos a crear:\n");
    scanf("%d",&n);


    if (n <= 0) {
        fprintf(stderr, "El número de procesos debe ser un entero positivo.\n");
        return EXIT_FAILURE;
    }

    printf("Proceso padre (ID %d)\n", getpid());

    for (int i = 1; i <= n; i++) {
        
        pid_t child_pid = fork();
        switch(child_pid){

            case -1:
                perror("fork error");
                printf("errno value = %d \n",errno);
                exit(EXIT_FAILURE);
            case 0:
                printf("Soy el hijo %d, y el pid de mi padre es %d\n",getpid(),getppid());
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

    printf("Todos los procesos hijos han terminado.\n");
}

