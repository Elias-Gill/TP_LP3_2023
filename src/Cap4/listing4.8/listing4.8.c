/* Descripcion:
Ejemplo de limpieza de hilos cancelados utilizando handlers
*/
#include <malloc.h>
#include <pthread.h>

/* Allocate  a  temporary  buffer.  */
void *allocate_buffer(size_t size) { return malloc(size); }

/* Deallocate a temporary buffer. */
void deallocate_buffer(void *buffer) { 
  printf("Exiting before the thread function is completed\n");
  printf("Cleaning the canceled thread");
  free(buffer); 
}

void do_some_work() {
  /* Allocate a temporary buffer. */
  void *temp_buffer = allocate_buffer(1024);

  /* Register a cleanup handler */
  pthread_cleanup_push(deallocate_buffer, temp_buffer);

  // cancel the thread execution before the end of the function
  pthread_exit(NULL);

  // unregister the cleanup handler because the thread succesfully terminated
  pthread_cleanup_pop(1);
}

void* function(void*_) {
  do_some_work();
  return NULL;
}

// Thread Cleanup Handler
int main(int argc, char *argv[]) {
  printf("Ejemplo de limpiado de los hilos ante una cancelacion\n\n");
  pthread_t hilo;
  pthread_create(&hilo, NULL, function, NULL);
  pthread_join(hilo, NULL);
  return 0;
}
