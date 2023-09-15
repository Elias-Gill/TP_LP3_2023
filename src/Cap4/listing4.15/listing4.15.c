
/*
 * Descripcion:
  El siguiente programa no realiza nada mas que imprimir ids de los hilos
 * */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *thread_function(void *arg) {
  fprintf(stderr, "child thread pid is %d\n", (int)getpid());

  fprintf(
    stderr,
    "\n\nNow you can run `ps x` to list the pid of all procecess and look for "
    "the thread pids");

  /* Spin forever.*/
  while (1);
  return NULL;
}

// listing 4.15: Print process ids for threads
int main() {
  pthread_t thread;
  fprintf(stderr, "main thread pid is %d\n", (int)getpid());
  pthread_create(&thread, NULL, &thread_function, NULL);

  /* Spin forever.  */
  while (1);
  return 0;
}
