/*
La idea tras la implementación es la siguiente: 

Se quiere comprobar que pasa si una hebra que ha ejecutado un pause() dentro de un 
pthread_mutex_lock(&lock), recibe un SIGKILL sin haber ejecutado pthread_mutex_unlock(&lock).

¿Que pasa con la otra hebra, se queda bloqueada para siempre?

Vamos a ver que las señales enviadas a una hebra realmente se tratan a nivel de proceso.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;//Lo utilizo para bloquear el acceso a la sección critica
int global=0;//Declaramos una variable global


void * h1(void * recibido)//Esta será la función que ejecuten las hebra 1
{
  int * orden = (int * ) recibido;

  pthread_mutex_lock(&lock);//Bloqueamos el acceso a la sección critica

     printf("Hebra %lu con orden de creacion %d dentro de la SC\n", pthread_self(), *orden);     
     global++;//Incrementa la variable global
     pause();//La ponemos a esperar a SIGKILL

  pthread_mutex_unlock(&lock);//Desbloqueamos el acceso a la sección critica

  pthread_exit(NULL);//Una vez la hebra ha acabado finaliza su ejecución
}

void * h2(void * recibido)//Esta será la función que ejecuten la hebra 2
{
  int * orden = (int * ) recibido;  
 
  printf("Hebra %lu con orden de creacion %d intentando acceder a SC...\n", pthread_self(), *orden);
  
  pthread_mutex_lock(&lock);//Bloqueamos el acceso a la sección critica

     printf("Hebra %lu con orden de creacion %d dentro de la SC\n", pthread_self(), *orden);
     global++;//Incrementará la variable global
  
  pthread_mutex_unlock(&lock);//Desbloqueamos el acceso a la sección critica

  pthread_exit(NULL);//Una vez la hebra ha acabado finaliza su ejecución
}

int main()
{
    pthread_t hebra1, hebra2; //Almacena el identificador cada una de las hebras
    int v[2] = {1,2};

    printf("Main (antes del incremento), el valor de variable global es: %d\n", global);
  
    if(pthread_create(&hebra1, NULL, (void *) h1, (void *) &v[0]))
    {
      fprintf(stderr, "Error creating thread\n");//Ha ocurrido un error al crear la hebra
      exit(EXIT_FAILURE); 
    }

    /*Vamos a dejar tiempo para que la hebra 1 llegue al pause() y poder simular el experimento.
    Utilizado solo a modo divulgativo. No usar para sincronizar procesos*/
    sleep(2); 

    if(pthread_create(&hebra2, NULL, (void *) h2, (void *) &v[1]))
    {
      fprintf(stderr, "Error creating thread\n");//Ha ocurrido un error al crear la hebra
      exit(EXIT_FAILURE); 
    }
	
	//Vamos a dejar tiempo para que la hebra 2 pueda llegar al pthread_mutex_lock() y quede bloqueada
    sleep(2); 

    printf("Main (despues del incremento de la hebra 1), el valor de variable global es: %d\n", global);

    //Mandamos la señal
    //PRUEBE A QUITAR ESTA LINEA DE CÓDIGO Y A EJECUTAR EL PROGRAMA. ¿QUÉ OCURRE?
    pthread_kill(hebra1, SIGKILL);

    //Espera de la hebra1
    if(pthread_join(hebra1, NULL)) 
    {   //Entramos si falla el join
        fprintf(stderr, "Error joining thread\n");//Informamos al usuario
        exit(EXIT_FAILURE);//Salimos
    }

    //Espera de la hebra2
    if(pthread_join(hebra2, NULL)) 
    {   //Entramos si falla el join
        fprintf(stderr, "Error joining thread\n");//Informamos al usuario
        exit(EXIT_FAILURE);//Salimos
    }  

    printf("Main (final), el valor de variable global es: %d\n", global);//Imprimimos el valor de la variable global
    exit(EXIT_SUCCESS);
}

/*
struct myStruct{
    pthread_mutex_t *m;
    int *glob;;
    int posicion;
}
int main()
{
    int *global = 0;                                     //int global = 0;
    struct myStruct s[2];
    pthread_mutex_t  *mutex = malloc(sizeof(pthread));   //pthread_mutex_t mutex = MACRO;
    mutex<-INICILIZAR;
    
    for(int i=0; i<2;i++){
        s[i].m= mutex;                                   // s[i].m = &mutex;
        s[i].glob = global;                              // s[i].glob = &global;
        s[i].posicion = i;
        pthread_create(,,,&s[i]);
    }
}
*/