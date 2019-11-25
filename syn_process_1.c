#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "display.h"
#include <sys/ipc.h>
#include <sys/sem.h>

int main()
{
  struct sembuf up = {0, 1, 0};
  struct sembuf down = {0, -1, 0};
  int my_sem, i;
  my_sem = semget(IPC_PRIVATE, 1, 0600); /* create semaphore */
	semop(my_sem, &up, 1);
  if (fork())
  {
    for (i=0;i<10;i++)
	{
      semop(my_sem, &down, 1);
      display("Hello world\n");
      semop(my_sem, &up, 1);
      }
     wait(NULL);
  }  
  else
  {
    for (i=0;i<10;i++)
	{
      semop(my_sem, &down, 1);
      display("Kalimera kosme\n");
		semop(my_sem, &up, 1);
        }
  }
  semctl(my_sem, 0, IPC_RMID);
  return 0;
}
