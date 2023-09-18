#include <stdio.h>
#include <tiffio.h>
// Si es que el argumento que se le pasa es nulo que mande una cadena vacía,
// emitir un mensaje que se le tiene que proporcionar un argumento
int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Se debe proporcionar un argumento.\n");
    return 1;
  }

  TIFF *tiff;
  tiff = TIFFOpen(argv[1], "r");

  if (tiff == NULL) {
    printf("No se pudo abrir el archivo TIFF.\n");
    return 1;
  }

  TIFFClose(tiff);
  return 0;
}
