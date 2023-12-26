/*Creo otro programa aparte que reciba por línea de argumentos un ID de un proceso, y su cometido
sea enviar una señal SIGUSR1 al proceso cuyo ID ha recibido por dicha línea de argumentos. Una
vez enviada la señal SIGUSR1 esperará durante 1 segundo y enviará al mismo proceso al que envió
la señal SIGUSR1 la señal de KILL. Compruebe por consola si el proceso al que ha enviado ambas
señales existe ya en el sistema.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
    if(argc!=2)
    {
        printf("Error al introducir los argumentos... \n");
        exit(EXIT_FAILURE);
    }
    pid_t id = atoi(argv[1]);
    if(id<0)
    {
        printf("Introduciste un id negativo :(\n");
        exit(EXIT_FAILURE);
    }
    if(kill(id, SIGUSR1))
    {
        printf("Error al enviar SIGUSR1: %s \n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if(kill(id, SIGKILL))
    {
        printf("Error al enviar SIGKILL: %s \n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
    return 0;
}