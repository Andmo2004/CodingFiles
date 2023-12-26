/*Realizar un programa que capture la señal de alarma, de manera que imprima la cadena “RING”
pasados 5 segundos, después pasados otros 3 segundos y por último cada segundo. Implementar
esto último, utilizando un bucle infinito que vaya imprimiendo el número de timbrazos. Pasados 4
timbrazos, el proceso se debe parar utilizando para ello la función kill().*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int timb = 0;

void RING()
{
    printf("RING %d\n",timb+1);
    timb++;
    if( timb == 4 ) kill(getpid(), SIGKILL);
}

int main()
{

    signal(SIGALRM, RING);//Cuando nos llegue una señal de tipo SIGALRM, ejecutamos la función RING
    for(int i=1; i<6; i++)
    {
        alarm(i*2);
        pause();
    }
    return 0;
}
