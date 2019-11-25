#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "display.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include <pthread.h>
#include <stdlib.h>

void *myfunc(void *myvar);
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[])
{
  pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

  pthread_t thread1, thread2;
  char *msg1 = "Hello world\n";
  char *msg2 = "Kalimera kosme\n";
  int ret1, ret2;

  ret1 = pthread_create(&thread1, NULL, myfunc, (void *) msg1);
  ret2 = pthread_create(&thread2, NULL, myfunc, (void *) msg2);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  
  pthread_mutex_destroy(&mutex1);
  exit (0);
}


void *myfunc(void *myvar)
{
   pthread_mutex_lock( &mutex1 );
   char *msg;
   msg = (char *) myvar;
   int i;
   for (i=0;i<10;i++)
   {
      display(msg);
   }  
   pthread_mutex_unlock( &mutex1 );
   return NULL;
}
