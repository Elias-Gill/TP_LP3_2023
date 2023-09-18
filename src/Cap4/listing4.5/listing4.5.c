/* Descripcion:
Esqueleto de programas con hilos "desacoplados"
*/
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *thread_function(void *thread_arg) {
  printf("Este es un hilo fue desacoplado, \npor lo que sera limpiado por el "
         "sistema operativo cuando este termine su trabajo");
  return NULL;
}

// Listing 4.5: Skeleton for detached threads
int main() {
  pthread_attr_t attr;
  pthread_t thread;

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  pthread_create(&thread, &attr, &thread_function, NULL);
  pthread_attr_destroy(&attr);

  /* Do  work  here...  */
  /* No  need  to  join  the  second  thread.  */
  return 0;
}
