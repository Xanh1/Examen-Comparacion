#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "especie/especie.h"

void crearTipoEspecieMpi(MPI_Datatype* tipo);

int main(int argc, char *argv[]) {
    int rank, size;
    int nroEspecies = 0;
    struct Especie* especies = NULL;
    struct Especie base;

    double inicio, fin;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Datatype MPI_ESPECIE;
    crearTipoEspecieMpi(&MPI_ESPECIE);

    if(rank == 0){
        especies = cargarEspecies("datos/especies.txt", &nroEspecies);
        base = especies[0];
    }

    MPI_Bcast(&nroEspecies, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&base, 1, MPI_ESPECIE, 0, MPI_COMM_WORLD);

    int localContador = nroEspecies / size;
    int resto = nroEspecies % size;

    if (rank == size - 1) {
        localContador += resto;
    }

    struct Especie* localEspecies = malloc(localContador * sizeof(struct Especie));
    int* sendcounts = NULL;
    int* displs = NULL;

    if (rank == 0) {
        sendcounts = malloc(size * sizeof(int));
        displs = malloc(size * sizeof(int));
        int offset = 0;

        for (int i = 0; i < size; i++) {
            sendcounts[i] = nroEspecies / size;
            if (i == size - 1) sendcounts[i] += resto;
            displs[i] = offset;
            offset += sendcounts[i];
        }
    }

    MPI_Scatterv(
        especies, sendcounts, displs, MPI_ESPECIE,
        localEspecies, localContador, MPI_ESPECIE,
        0, MPI_COMM_WORLD
    );

    MPI_Barrier(MPI_COMM_WORLD);
    inicio = MPI_Wtime();

    int* localResultados = malloc(localContador * sizeof(int));
    for (int i = 0; i < localContador; i++) {
        localResultados[i] = similitud(base, localEspecies[i]);
    }

    int* resultados = NULL;
    if (rank == 0) {
        resultados = malloc(nroEspecies * sizeof(int));
    }

    MPI_Gatherv(
        localResultados, localContador, MPI_INT,
        resultados, sendcounts, displs, MPI_INT,
        0, MPI_COMM_WORLD
    );

    fin = MPI_Wtime();

    if (rank == 0) {
        for (int i = 0; i < nroEspecies; i++) {
            printf("Similitud con %s: %d%%\n", especies[i].nombre, resultados[i]);
        }
        printf("Tiempo de ejecución total (MPI): %f segundos\n", fin - inicio);
    }

    MPI_Type_free(&MPI_ESPECIE);
    if (rank == 0) {
        free(especies);
        free(sendcounts);
        free(displs);
        free(resultados);
    }

    free(localEspecies);
    free(localResultados);

    MPI_Finalize();
    return 0;
}


void crearTipoEspecieMpi(MPI_Datatype* tipo) {
    int blocklengths[5] = {20, 1, 1, 1, 1};
    MPI_Datatype types[5] = {MPI_CHAR, MPI_FLOAT, MPI_FLOAT, MPI_FLOAT, MPI_FLOAT};
    MPI_Aint offsets[5];

    offsets[0] = offsetof(struct Especie, nombre);
    offsets[1] = offsetof(struct Especie, humedad);
    offsets[2] = offsetof(struct Especie, densidad);
    offsets[3] = offsetof(struct Especie, contracccion);
    offsets[4] = offsetof(struct Especie, radial);

    MPI_Type_create_struct(5, blocklengths, offsets, types, tipo);
    MPI_Type_commit(tipo);
}