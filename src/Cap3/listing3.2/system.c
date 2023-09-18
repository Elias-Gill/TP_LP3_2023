/*
 * Descripcion:
  Invoca el comando ls para mostrar el contenido del directorio raiz
  como si escribiera ls -l / en un shell
 * */
#include <stdlib.h>
int main()
{
  int return_value;
  return_value = system("ls -l /");
  return return_value;
}