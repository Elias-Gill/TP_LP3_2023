/*
 * Descripcion:
 *  El programa genera una job_queue para demostrar las posibles race
 *  conditions. Por ello se deberian de apreciar ocasionales trabajos repetidos o
 *  inclusive alguna segmentation fault
 * */

#include <malloc.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct job {
  struct job *next;
  int job_id;
} job;

job *cola;
job *inicio;

// El trabajo sera simplemente imprimir un nuevo trabajo en la cola
void process_job(int id_hilo, int id_trabajo) {
  printf("HILO %d, trabajo %d\n", id_hilo, id_trabajo);
  int random_number = 1 + rand() % (3 - 1 + 1);
  sleep(random_number);
  return;
}

/* Process queued jobs until the queue is empty.  */
void *thread_function(void *args) {
  int *id_hilo = (int *)(args);
  while (cola != NULL) {
    // desencolar la lista de trabajos
    job *next_job = cola;
    cola = cola->next;

    // realizar un trabajo
    process_job(*id_hilo, next_job->job_id);
    free(next_job);
  }
  return NULL;
}

// Listing 4.10: Jobs Queue
int main(int argc, char *argv[]) {
  printf("\nDurante la ejecucion del programa se deberian apreciar varias race conditions: \n");
  printf("En la forma de errores de memoria o como trabajos repetidos por hilos distintos\n\n");
  sleep(3);
  // inicializar la cola
  job *aux = malloc(sizeof(job));
  aux->job_id = 0;
  cola = aux;
  inicio = aux;
  // anadir nuevos trabajos a la cola
  for (int i = 1; i < 100; i++) {
    job *n = malloc(sizeof(job));
    n->job_id = i;
    inicio->next = n;
    inicio = n;
  }

  // crear los hilos
  pthread_t hilos[10];
  int ids[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  for (int i = 0; i < 10; i++)
    pthread_create(&hilos[i], NULL, &thread_function, &ids[i]);

  for (int i = 0; i < 10; i++)
    pthread_join(hilos[i], NULL);

  return 0;
}
