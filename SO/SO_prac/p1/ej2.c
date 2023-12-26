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
    int status;
    //BUCLE CREACION PROCESOS HIJO:
    for(int i=0; i<num_child; i++)
    {
        pid_t child_pid = fork();

            if(child_pid==-1)
            {
                perror("Error en el fork");
                printf("Hijo no creado correctamente...\n");
                exit (EXIT_FAILURE);
            }
            if(child_pid==0)
            {
                printf("Soy el hijo %d, y el pid de mi padre es %d\n",getpid(),getppid());
            }
            else
            {
                printf("Esperando a que mi hijo %d termine \n", i+1);
                wait(&status);
                printf("El proceso %d ha finalizado, codigo de salida: %d \n", child_pid, WEXITSTATUS(status));
                exit(EXIT_SUCCESS);
            }   
    }
};