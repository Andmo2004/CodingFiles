/*Realizar un programa padre que expanda un hijo y al cual le envíe cada 1 segundo una señal
personalizada de usuario SIGUSR1. El hijo debe imprimir un mensaje en pantalla cada vez que
recibe la señal del padre, tratándola en una función aparte llamada tratarSennal(). Enviados 5
mensajes los procesos deben salir. Utiliza las funciones signal() y kill().*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void tratarSennal()
{
    printf("Señal,recibida\n");
}

int main()
{
    printf("Proceso padre (ID %d)\n", getpid());
    int status;

    pid_t child_pid;
    child_pid = fork();

    if(child_pid==-1)
    {
        printf("Error en fork");
        exit(EXIT_FAILURE);
    }
    if(child_pid==0){
        signal(SIGUSR1,tratarSennal);
        for(int i=0; i<5; i++)
        {
            pause();
        }
        sleep(1);
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("Esperando a que mi hijo acabe \n");
        for (int i = 0; i<5; i++){
            sleep(1);
            kill(child_pid, SIGUSR1); //En child_pid se ha guardado el pid del hijo (así funciona el fork)
            // Cuando llamamos a kill, manda a child_pid la señal SIGUSR1
        }

        sleep(1);//Si quitamos este sleep, matamos al proceso hijo antes de que le de tiempo a imprimir el mensaje numero 5
        kill(child_pid, SIGKILL); //Mandamos a id (proceso hijo) la señal SIGKILL para que la casque
        sleep(4);//Si ponemos este sleep, el proceso hijo se queda en modo zombie esperando a ser recogido por el padre
        wait(&status);
        printf("Hijo finalizado con código de salida %d \n", WEXITSTATUS(status));
    }

    return 0;
}