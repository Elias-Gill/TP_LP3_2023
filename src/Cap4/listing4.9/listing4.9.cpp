
/* Descripcion:
Ejemplo de parada segura de hilos con lanzamiento de excepciones en C++
 */
#include <iostream>
#include <pthread.h>
#include <random>
#include <stdio.h>

// generar un numero aleatorio, si el numero es menor que 4, true, si es mayor
// entonces false
int should_exit_thread_immediately() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(2, 10);

  int random_number = dis(gen);
  std::cout << "Random number between 2 and 10: " << random_number << std::endl;

  return random_number > 4;
}

class ThreadExitException {
public:
  /* Create  an  exception-signaling  thread  exit  with  RETURN_VALUE.  */
  ThreadExitException(void *return_value)
      : thread_return_value_(return_value) {}

  /*  Actually  exit  the  thread,  using  the  return  value  provided  in  the
    constructor.  */
  void *DoThreadExit() { 
        printf("Safely exiting thread");
        pthread_exit(thread_return_value_); 
    }

private:
  /*  The  return  value  that  will  be  used  when  exiting  the  thread.*/
  void *thread_return_value_;
};

void do_some_work() {
  while (1) {
    /*  Do  some  useful  things  here...  */
    if (should_exit_thread_immediately())
      throw ThreadExitException(NULL);
  }
}

void *thread_function(void *) {
  try {
    do_some_work();
  } catch (ThreadExitException ex) {
    ex.DoThreadExit();
  }
  return NULL;
}

int main(int argc, char *argv[]) {
    printf("Ejemplo de parada segura de hilos con excepcion en C++\n\n");
    pthread_t hilo;
    pthread_create(&hilo, NULL, thread_function, NULL);
    pthread_join(hilo, NULL);
    return 0;
}

