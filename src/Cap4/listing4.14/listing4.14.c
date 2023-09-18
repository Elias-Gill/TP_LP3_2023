/*
 * Descripcion:
  "Suppose that you write a thread function that executes a loop infinitely,
  performing some work on each iteration. The thread loop, however, needs to be
  controlled by a flag: The loop runs only when the flag is set; when the flag
 is not set, the loop pauses."
                                        - Advance linux programming

  La siguiente implementacion es una version mejorada del listing4.13,
 utilizando las variables de condicion proporcionadas por el sistema operativo
 dentro de la libreria pthread. Siendo una solucion mas optima en cuanto al uso
 de recursos.
 * */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int thread_flag;
pthread_cond_t thread_flag_cv;
pthread_mutex_t thread_flag_mutex;

void do_work() {
  printf("Doing some work\n");
  sleep(1);
}

void initialize_flag() {
  /* Initialize the mutex and condition variable.  */
  pthread_mutex_init(&thread_flag_mutex, NULL);
  pthread_cond_init(&thread_flag_cv, NULL);
  /* Initialize  the  flag  value.  */
  thread_flag = 0;
}

/* Calls do_work repeatedly while the thread flag is set; blocks if
   the flag is clear.  */

void *thread_function(void *thread_arg) {
  /* Loop infinitely.  */
  while (1) {
    /* Lock the mutex before accessing the flag value.  */
    pthread_mutex_lock(&thread_flag_mutex);
    while (!thread_flag)
      // If the flag is not setted then
      // wait for a signal on the condition variable,
      // indicating that the flag value has changed.
      pthread_cond_wait(&thread_flag_cv, &thread_flag_mutex);
    pthread_mutex_unlock(&thread_flag_mutex);
    /* Do some work.  */
    do_work();
  }
  return NULL;
}

// This thread changes the flag value periodically
void *setter_function(void *_) {
  while (1) {
    /* Lock the mutex before accessing the flag value.  */
    pthread_mutex_lock(&thread_flag_mutex);

    // set the flag into a different state
    if (thread_flag) {
      thread_flag = 0;
    } else {
      thread_flag = 1; // intercalar entre 0 y 1 la bandera
    }

    // Now signal in case thread_function is waiting
    // for the condition variable to be changed
    pthread_cond_signal(&thread_flag_cv);
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
