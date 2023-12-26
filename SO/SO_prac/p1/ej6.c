#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> //Varias estructuras de datos.
#include <sys/wait.h>
#include <unistd.h> //API10 de POSIX y creación de un proceso.
#include <errno.h>

int main(int argc, char** argv)
{
    if(argc!=2)
    {
        printf("Numero de argumentos invalido... \nintente de nuevo.");
        exit(EXIT_FAILURE);
    }
    int num_child = atoi(argv[1]), cont = 0;

    if (num_child <= 0) 
    {
        fprintf(stderr, "El número de procesos debe ser un entero positivo.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Proceso padre (ID %d)\n", getpid());
        for(int i=0; i<num_child; i++)
        {
            pid_t child_pid = fork();
            switch(child_pid)
            {
                case -1: //Error durante la creacion de un nuevo hijo.
                    perror("fork error");
                    printf("errno value = %d \n",errno);
                    exit(EXIT_FAILURE);

                case 0:  //Nuevo hijo creado, ejecuta su proceso.
                    printf("Soy el hijo %d, y el pid de mi padre es %d\n",getpid(),getppid());
                    cont++;
                    printf("El contador está a: %d\n", cont);
                    exit(EXIT_SUCCESS);
            }

        }
        int status;
        for(int i=0; i<num_child; i++) //Bucle de recogidad de hijos.
        {
            //W_IF_EXITED: Indica si el proceso esta en estado terminado, devuelve true/false.
            //W_EXIT_STATUS: Devuelve el estado de terminación.
            wait(&status);
            if(WIFEXITED(status))
            {
                printf("Proceso hijo %d terminado con estado %d\n", i, WEXITSTATUS(status));
                //Finalizacion de proceso hijo
            }
            else
            {
                printf("Proceso hijo %d terminado anormalmente\n", i); 
                //Error al finalizar proceso hijo.
            }
        }
        printf("Todos los procesos hijos han terminado y contador = %d.\n", cont);


    }
};