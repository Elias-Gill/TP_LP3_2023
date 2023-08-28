# Tp de LP3
### Consideraciones

#### Desarrollar los ejemplos del libro 
Capitulos 1,2,3,4. Desarrollarlos con el siguiente formato:
```
- TP_LP3_2023
    - src
        Cap1
            listing1.1
            listing1.2
        Cap2
            listing2.1
            listing2.2
        Cap3
            listing3.1
            ...
        Cap4
            ...

        Makefile
```

#### Subir todo en un repositorio github o gitlab
ID del profesor: @joaquinlima

#### Los programas deben soportar
Compilacion global o individual con el comando `make`

**Para la compilacion grupal**:
- El comando `make all` debe generar dentro de una carpeta **build** los compilados con el mismo formato que _src_

- Tambien debe soportar la compilacion individual, por ejemplo:
```sh
make listingx.y
```

Debe generar:
```
- TP_LP3_2023
    - build
        Cap1
            listing1.1
            listing1.2
```
