#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include<errno.h>

int main(int argc, char** argv)
{
    if(argc<2)
    {
        printf("Numero de argumentos invalido... \nIntente de nuevo.\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i<argc; i++)
    {
        pid_t child_pid = fork();
        
        if(child_pid==-1)
        {
            perror("fork error");
            printf("errno value = %d \n",errno);
            exit(EXIT_FAILURE);
        }
        if(child_pid==0)
        {
           printf("Hijo %d con ID %d creado con exito \n", i+1, getpid());

            if(i==0){
                execlp(argv[1], argv[1], NULL);
            }

            else{
                execlp(argv[2], argv[2], NULL);
                
            }
            exit(EXIT_SUCCESS);

        }
    }

    //Finalizacion de procesos
    pid_t pidh1, pidh2;
    int status;

    pidh1 = wait(&status);
    printf("Ya ha acabado mi hijo %d con el codigo de salida: %d\n", pidh1, WEXITSTATUS(status));
    
    pidh2 = wait(&status);
    printf("Ya ha acabado mi hijo %d con el codigo de salida: %d\n", pidh2, WEXITSTATUS(status));
    

    return 0;
}