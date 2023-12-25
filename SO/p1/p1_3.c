/**/

/**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso incorrecto. Debe proporcionar un número N como argumento.\n");
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "El número de procesos debe ser un entero positivo.\n");
        return EXIT_FAILURE;
    }

    printf("Proceso padre (ID %d)\n", getpid());

    // Manejador de señales para los hijos
    void child_handler(int signum) {
        // No hacemos nada aquí, simplemente permitimos que el hijo continúe.
    }

    for (int i = 1; i <= n; i++) {
        pid_t child_pid = fork();
        switch (child_pid) {
            case -1:
                perror("fork error");
                printf("errno value = %d \n", errno);
                exit(EXIT_FAILURE);
            case 0:
                // Configurar el manejador de señales para el hijo
                signal(SIGUSR1, child_handler);

                printf("Soy el hijo %d, y el pid de mi padre es %d\n", getpid(), getppid());

                // Esperar el tiempo apropiado usando señales
                for (int j = 1; j <= 10 * i; j++) {
                    kill(getpid(), SIGUSR1);
                    pause();  // Esperar hasta que se reciba una señal
                }
                exit(EXIT_SUCCESS);
        }
    }

    // Proceso padre esperando a que todos los hijos terminen
    int status;
    for (int i = 1; i <= n; i++) {
        pid_t terminated_pid = wait(&status);
        if (WIFEXITED(status)) {
            printf("Proceso hijo %d (PID %d) terminado con estado %d\n", i, terminated_pid, WEXITSTATUS(status));
        } else {
            printf("Proceso hijo %d (PID %d) terminado anormalmente\n", i, terminated_pid);
        }
    }

    printf("Todos los procesos hijos han terminado.\n");

    return EXIT_SUCCESS;
}

//_________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

 int main(int argc, char** argv) {

    if(argc!=2){
        printf("Numero de argumentos incorrecto\n");
        return -1;
    }

    int n = atoi(argv[1]);

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
                pid_t wait(int getpid());
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
*/