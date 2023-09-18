#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef int temp_file_handle;
temp_file_handle write_temp_file(char *buffer, size_t length) {
  char temp_filename[] = "/tmp/temp_file.XXXXXX";
  int fd = mkstemp(temp_filename);
  unlink(temp_filename);
  write(fd, &length, sizeof(length));
  write(fd, buffer, length);
  return fd;
}
char *read_temp_file(temp_file_handle temp_file, size_t *length) {
  char *buffer;
  int fd = temp_file;
  lseek(fd, 0, SEEK_SET);
  read(fd, length, sizeof(*length));
  buffer = (char *)malloc(*length);
  read(fd, buffer, *length);
  close(fd);
  return buffer;
}
int main() {
  char input_text[] = "Hola, este es un archivo temporal de prueba.";
  size_t input_length = sizeof(input_text) / sizeof(char);

  // Escribir el archivo temporal
  temp_file_handle temp_file = write_temp_file(input_text, input_length);
  printf("Archivo temporal creado.\n");

  // Leer el archivo temporal
  size_t output_length;
  char *output_text = read_temp_file(temp_file, &output_length);
  printf("Contenido del archivo temporal:\n%s\n", output_text);

  // Liberar la memoria del buffer
  free(output_text);

  return 0;
}
