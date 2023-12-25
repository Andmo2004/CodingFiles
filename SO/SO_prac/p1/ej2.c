#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
    if(argc!=2)
    {
        printf("Error en el numero de argumentos de entrada...\n");
        exit (EXIT_FAILURE);
    }
    int num_child = atoi(argv[1]);
    if(num_child<0)
    {
        printf("El numero de hijos debe ser positivo...\n");
        exit (EXIT_FAILURE);
    }

    printf("Proceso padre (ID %d)\n", getpid());

    //BUCLE CREACION PROCESOS HIJO:
    for(int i=0; i<num_child; i++)
    {
        pid_t child_pid = fork();
        switch(child_pid)
        {
            case -1:
                perror("Error en el fork");
                printf("Hijo no creado correctamente...\n");
                exit (EXIT_FAILURE);
            case 0:
                printf("Soy el hijo %d, y el pid de mi padre es %d\n",getpid(),getppid());
                return 0;
        }
    }

    int status;
    //BUCLE RECOGIDA PROCESOS HIJO:
    for(int i=0; i<num_child; i++)
    {
        wait(&status);
        if(WIFEXITED(status)){
            printf("Proceso hijo %d terminado con estado %d\n", i, WEXITSTATUS(status));
            //Finalizacion de proceso hijo
        }
        else
        {
            printf("Proceso hijo %d terminado anormalmente\n", i); 
            //Error al finalizar proceso hijo.
        }
    }
    printf("Todos los procesos hijos han terminado.\n");


};