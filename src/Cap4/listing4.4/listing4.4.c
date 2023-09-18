/* Descripcion:
Computar de manera concurrente numeros primos mientras se hacen otras coasas
*/
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/* Compute successive prime numbers (very  inefficiently). Return  the
   Nth prime  number, where N is the value pointed to by *ARG.  */
void *compute_prime(void *arg) {
  int candidate = 2;
  int n = *((int *)arg);

  while (1) {
    int factor;
    int is_prime = 1;

    /* Test  primality  by  successive  division.  */
    for (factor = 2; factor < candidate; ++factor)
      if (candidate % factor == 0) {
        is_prime = 0;
        break;
      }

    /* Is  this  the  prime  number  we're  looking  for?  */
    if (is_prime) {
      if (--n == 0)
        return (void *)candidate;
    }
    ++candidate;
  }
  return NULL;
}

// Compute primes numbers in a thread
int main() {
  printf("\nEl programa computa el n-esimo numero primo de manera concurrente "
         "con otros procesos\n\n");

  /* Start  the  computing  thread,  up  to  the  5,000th  prime  number.  */
  pthread_t thread;
  int which_prime = 5000;
  int prime;
  printf("Computando el numero primo numero 5000..\n\n");
  pthread_create(&thread, NULL, &compute_prime, &which_prime);

  for (int i = 0; i < 4; i++) {
    printf("computando otras cosas...\n");
    sleep(1);
  }
  printf("haciendo otras cosas mientras... \n");
  sleep(1);
  /* Wait  for  the  prime  number  thread  to  complete,  and  get  the
result.  */
  pthread_join(thread, (void *)&prime);
  /* Print  the  largest  prime  it  computed.  */
  printf("The  %dth  prime  number  is  %d.\n", which_prime, prime);
  return 0;
}
