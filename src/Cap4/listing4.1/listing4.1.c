// Listing 4.1: thread creation
#include <pthread.h>
#include <stdio.h>

// Prints x's to stderr.  The parameter is unused.  Does not return
void *print_xs(void *_) {
  while (1)
    fputc('x', stderr);
  return NULL;
}

// The main program.
int main() {
  pthread_t thread_id;

  // Create a new thread.
  pthread_create(&thread_id, NULL, &print_xs, NULL);

  // Print o's continuously  to stderr.
  while (1)
    fputc('o', stderr);
  return 0;
}
/*
 * Descripcion:
 *  El programa imprime O de manera infinita dentro del hilo principal, mientras
 *  un hilo hijo imprime X.
 *  Esto es para demostrar el uso de los hilos
 * */
