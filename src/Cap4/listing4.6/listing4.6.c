/* Descripcion:
Desactivando la cancelacion de hilos.
En este ejemplo un hilo esta realizando una transaccion, por lo que este hilo no
puede ser cancelado por ningun motivo.
*/
#include <pthread.h>
#include <stdio.h>
#include <string.h>

/*  An  array  of  balances  in  accounts,  indexed  by  account  number.  */
float *account_balances;

// funcion que simula que se esta realizando una transaccion de dinero.
int process_transaction(int from_acct, int to_acct, float dollars) {
  int old_cancel_state;
  if (account_balances[from_acct] < dollars)
    return 1;

  /* Begin  critical  section.  */
  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
  account_balances[to_acct] += dollars;
  account_balances[from_acct] -= dollars;

  pthread_setcancelstate(old_cancel_state, NULL);
  /* End  critical  section.  */
  return 0;
}

// Listing 4.6: protect a Bank Transaction with a Critical Section
int main(int argc, char *argv[]) {
  return 0;
}
