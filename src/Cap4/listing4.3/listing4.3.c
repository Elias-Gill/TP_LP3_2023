/*
 * Descripcion:
  Ejemplo de creacion de dos hilos pero ahora si ulizando pthread_join()
 * */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

struct char_print_parms {
  /* The character to print.*/
  char character;
  /* The number of times to print it.  */
  int count;
};

void *char_print(void *parameters) {
  /* Cast the cookie pointer to the right type.  */
  struct char_print_parms *p = (struct char_print_parms *)parameters;
  int i;

  for (i = 0; i < p->count; ++i)
    fputc(p->character, stderr);
  return NULL;
}

// Listing 4.3: Revised main for listing 4.2
int main() {
  printf("\nA diferencia del listing 4.2, ahora deberiamos poder apreciar un "
         "hilo imprimiendo\n'X' y otro 'O', ya que ahora correctamente "
         "utilizamos pthread_join()\n\n");
  sleep(3);
  pthread_t thread1_id;
  pthread_t thread2_id;
  struct char_print_parms thread1_args;
  struct char_print_parms thread2_args;
  /* Create  a  new  thread  to  print  3,000  x's.  */
  thread1_args.character = 'x';
  thread1_args.count = 3000;
  pthread_create(&thread1_id, NULL, &char_print, &thread1_args);

  /* Create  a  new  thread  to  print  2,000  o's.  */
  thread2_args.character = 'o';
  thread2_args.count = 2000;
  pthread_create(&thread2_id, NULL, &char_print, &thread2_args);

  /* Make  sure  all the threads  had  finished.  */
  pthread_join(thread1_id, NULL);
  pthread_join(thread2_id, NULL);

  /* Now  we  can  safely  return.  */
  return 0;
}
