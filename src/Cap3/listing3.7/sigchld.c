/*
 * Descripcion:
 Muestra como se ve un programa que usa un controlador SIGCHLD para limpiar
 sus procesos secundarios.
 * */
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
sig_atomic_t child_exit_status;
void clean_up_child_process(int signal_number)
{
  /* Clean up the child process. */
  int status;
  wait(&status);
  /* Store its exit status in a global variable. */
  child_exit_status = status;
}
int main()
{
  /* Handle SIGCHLD by calling clean_up_child_process. */
  struct sigaction sigchld_action;
  memset(&sigchld_action, 0, sizeof(sigchld_action));
  sigchld_action.sa_handler = &clean_up_child_process;
  sigaction(SIGCHLD, &sigchld_action, NULL);
  /* Now do things, including forking a child process. */
  // Creamos el proceso hijo
  pid_t child_pid;
  // Clonamos el proceso
  child_pid = fork();
  if (child_pid != 0)
  {
    printf("Id proceso padre: %d\n", getpid());
    printf("Id proceso hijo: %d\n", child_pid);
    // El proceso padre duerme por 100s
    sleep(100);
  }
  else
  {
    printf("Id proceso hijo: %d\n", child_pid);
    // El proceso hijo duerme por 10 s
    sleep(10);
  }

  return 0;
}