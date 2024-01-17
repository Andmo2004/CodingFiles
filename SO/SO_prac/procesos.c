#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    for(int i=0; i<2; ++i)
    {
        pid_t child_pid = fork();
        if(child_pid==0)
        {
            printf("Soy el hijo %d, y el pid de mi padre es %d\n", getpid(), getppid());
            exit(EXIT_SUCCESS);
        }
        if(child_pid==-1)
        {
            perror("Fork error\n");
            exit(EXIT_FAILURE);
        }
        // else
        // {
        //     printf("Soy el padre %d, y estoy esperando a mi hijo\n", getppid());
        //     exit(EXIT_FAILURE);
        // }
    }

    int status;
    for(int i=0; i<2; ++i)
    {
        wait(&status);
        if(WIFEXITED(status))
        {
            printf("El hijo %d, ha finalizado con estado:%d\n", i, WEXITSTATUS(status));
        }
        else{printf("Algo salio mal");}
    }
    printf("Programa terminado");
    return 0;
}