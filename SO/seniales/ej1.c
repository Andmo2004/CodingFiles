#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <errno.h>
#include <signal.h>

int  counter=0;

void func_ring()
{
    printf("*RING* %d\n", counter+1);
    counter++;
    if( counter == 4 ) kill(getpid(), SIGKILL);

}

int main(int argc, char** argv)
{
    signal(SIGALRM, func_ring);
    for(int i=1; i<6; ++i)
    {
        alarm(i*2);
        pause();
    }
    exit(EXIT_SUCCESS);
}