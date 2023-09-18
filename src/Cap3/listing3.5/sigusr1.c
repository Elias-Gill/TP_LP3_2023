#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
sig_atomic_t sigusr1_count = 0;
void handler(int signal_number) { ++sigusr1_count; }
int main() {
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = &handler;
  sigaction(SIGUSR1, &sa, NULL);
  /* Do some lengthy stuff here. */
  /*
       Se agrega un for para mantener el programa en ejecución
      y permitir la recepción de la señal desde el mismo proceso;
      despues de generar una señal se espera 2 segundos.
  */
  for (int i = 0; i < 20; i++) {
    // Genera una señal SIGUSR1
    raise(SIGUSR1);
    sleep(2);
  }

  printf("SIGUSR1 was raised %d times\n", sigusr1_count);
  return 0;
}