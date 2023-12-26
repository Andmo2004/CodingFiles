#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *CuentaLineas(FILE *archivo;)
{
    int contador = 0;
    int caracter;

    while ((caracter = fgetc(archivo)) != EOF)
    {
        if (caracter == '\n') 
        {
            contador++;
        }
    }

    if (contador > 0 || (caracter != '\n' && caracter != EOF)) {
        contador++;
    }

    return contador;
}

int main(int argc, char** argv)
{
    int num_total_lineas=0, num_hebras = argc-1;
    pthread_t hilos[num_hebras];

    for
}