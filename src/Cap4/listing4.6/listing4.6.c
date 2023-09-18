/* Descripcion:
Desactivando la cancelacion de hilos.
En este ejemplo un hilo esta realizando una transaccion, por lo que este hilo no
puede ser cancelado por ningun motivo.
*/
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*  An  array  of  balances  in  accounts,  indexed  by  account  number.  */
float account_balances[] = {100, 100};

// funcion que simula que se esta realizando una transaccion de dinero.
int process_transaction(int from_acct, int to_acct, float dollars) {
  int old_cancel_state;
  if (account_balances[from_acct] < dollars)
    return 1;

  /* Begin  critical  section.  */
  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);

  printf("Ahora el hilo no puede ser cancelado\n");
  account_balances[to_acct] += dollars;
  account_balances[from_acct] -= dollars;
  sleep(3);

  pthread_setcancelstate(old_cancel_state, NULL);
  printf("Ahora el hilo puede volver a ser cancelado\n");
  /* End  critical  section.  */
  return 0;
}

void *thread_function(void *_) {
  printf("Este es un nuevo hilo...\n");
  process_transaction(0, 1, 50);
  printf("El hilo termino sin interrupciones\n");
  return NULL;
}

// Listing 4.6: protect a Bank Transaction with a Critical Section
int main(int argc, char *argv[]) {
  printf("Este programa es un ejemplo de desactivacion de cancelacion de "
         "hilos...\nSe observa que el hilo se puede cancelar puesto que no se "
         "imprime el mensaje de exito\nPero esto ocurre solamente despues de "
         "que la seccion critica termine\n\n");
  pthread_t hilo;
  pthread_create(&hilo, NULL, thread_function, NULL);

  // tratar de cancelar el hilo
  sleep(1);
  printf("Tratando de cancelar el hilo desde main\n");
  pthread_cancel(hilo);

  pthread_join(hilo, NULL);
  return 0;
}
