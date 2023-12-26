/*Realizar un programa que este permanentemente a la espera de capturar una señal SIGUSR1 (en un
bucle while(1) infinito por ejemplo), de forma que cuando la capture imprima su ID. Compílelo y
láncelo por consola.*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

void PrintId()
{
    printf("Mi id: %d. \n", getpid());
}

int main()
{
    signal(SIGUSR1, PrintId);
    while(1)
    {
        pause();
    }
    exit(EXIT_SUCCESS);
    return 0;
}

