#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
    if(argc!=3)
    {
        printf("Error al introducir los valores por la linea de comandos...\n");
        exit(EXIT_FAILURE);
    }
    int status, child_pid;
    printf("Proceso padre (ID %d)\n", getpid());
    for(int i = 0; i<2; i++)
    {
        child_pid = fork();
        if(child_pid==-1)
        {
            printf("Error en el fork");
            exit(EXIT_FAILURE);
        }
        if(child_pid==0)
        {
            printf("Hijo %d con ID %d\n", i+1, getpid());
            if (i==0){
                sleep(5);
                execlp("./factorial", "./factorial", argv[1], NULL );
            }
            else{
                execlp("./factorial", "./factorial", argv[2], NULL );
            }
            exit(EXIT_SUCCESS);
        }
    }
    //Finalizacion procesos
    for(int i = 1; i < 3; i++)
    {
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
    printf("Todos los procesos hijos han terminado.\n");
    return 0;
}


