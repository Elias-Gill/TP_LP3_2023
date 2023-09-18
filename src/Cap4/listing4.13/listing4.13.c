/*
 * Descripcion:
  "Suppose that you write a thread function that executes a loop infinitely,
  performing some work on each iteration. The thread loop, however, needs to be
  controlled by a flag: The loop runs only when the flag is set; when the flag
 is not set, the loop pauses."
                                        - Advance linux programming
  La siguiente implementacion simple es correcta, pero presenta un fallo en
 cuanto a diseno, ya que no resulta optima.
 * */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int thread_flag;
pthread_mutex_t thread_flag_mutex;

void initialize_flag() {
  pthread_mutex_init(&thread_flag_mutex, NULL);
  thread_flag = 0;
}

/* Calls do_work repeatedly while the thread flag is set; otherwise
   spins.  */
void do_work() {
  printf("Doing some work\n");
  sleep(1);
}

void *thread_function(void *thread_arg) {
  while (1) {
    int flag_is_set;
    /* Protect the flag with a mutex lock.  */
    pthread_mutex_lock(&thread_flag_mutex);
    flag_is_set = thread_flag;
    pthread_mutex_unlock(&thread_flag_mutex);

    if (flag_is_set)
      do_work();
  }
  return NULL;
}

// changes the flag value periodically
void *setter_function(void *_) {
  while (1) {
    // set the flag into a different state
    pthread_mutex_lock(&thread_flag_mutex);
    if (thread_flag) {
      thread_flag = 0;
    } else {
      thread_flag = 1; // intercalar entre 0 y 1 la bandera
    }
    printf("La bandera tiene valor %d\n", thread_flag);
    pthread_mutex_unlock(&thread_flag_mutex);
    sleep(3);
  }
  return NULL;
}

// listing 4.13: Condition variable
int main(int argc, char *argv[]) {
  initialize_flag();
  // inicializar el hilo de trabajo
  pthread_t working_thread;
  pthread_create(&working_thread, NULL, &thread_function, NULL);

  // inicializar el hilo encargado de cambiar el estado de la flag
  pthread_t flag_setter;
  pthread_create(&working_thread, NULL, &setter_function, NULL);

  // esperar a los hilos hijos
  pthread_join(working_thread, NULL);
  pthread_join(flag_setter, NULL);
  return 0;
}
