#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if(argc!=2)
    {
        printf("Error al introducir los valores por la linea de comandos...\n");
        exit(EXIT_FAILURE);
    }
    int numero = atoi(argv[1]), fact = 1;
    for(int i = 1; i<(numero+1); i++)
    {
        fact = fact * i;
    }
    printf("El factorial de %d, es igual a: %d\n", numero, fact);
    return 0;
}