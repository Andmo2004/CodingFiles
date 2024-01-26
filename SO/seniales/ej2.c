#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/time.h>

int counter = 1;

void tratarSennial()
{
    printf("Mensaje_recibido --> %d\n", counter);
    counter++;
}

int main(int argc, char** argv)
{
    pid_t pid;
    pid = fork();
        if(pid == 0)
        {
            signal(SIGUSR1, tratarSennial);
            for(int i=0; i<5; ++i)
            {
                pause();
            }
            sleep(1);
            exit(EXIT_SUCCESS);
        }
        if(pid == -1)
        {
            perror("fork_error");
            printf("fork_error");
            exit(EXIT_FAILURE);
        }
    
    for(int i=0; i<5; ++i)
    {
        sleep(1);
        kill(pid, SIGUSR1);
    }

    int status;
    wait(&status);
    if(WIFEXITED(status))
    {
        printf("Proceso hijo ha terminado con estado %d\n", WEXITSTATUS(status));
    }
    else
    {
        printf("Proceso hijo terminado anormalmente\n"); 
    }
    exit(EXIT_SUCCESS);
    
}

