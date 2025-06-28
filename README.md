# Programa de Similitud de Especies de Madera

Este programa calcula y muestra el porcentaje de similitud entre una especie base de madera y el resto de las especies registradas en un archivo txt.


## Requisitos

- GCC
- Librería OpenMPI

## Compilación y ejecución

### Versión secuencial

Para compilar y ejecutar la versión secuencial del programa:

```bash
make run
```

### Versión paralela
Para compilar y ejecutar la versión paralela usando MPI:

```bash
make mpi
```

Por defecto, el programa se ejecuta con **4 procesos**.
\
\
Si deseas cambiar la cantidad de procesos, puedes especificarlo con el parámetro NP:
```bash
make mpi NP=6
```
