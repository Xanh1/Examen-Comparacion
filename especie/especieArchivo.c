#include <stdio.h>
#include "especie.h"
#include <stdlib.h>

int contarLineas(const char* archivo) {
    FILE* f = fopen(archivo, "r");
    if (!f) return 0;

    int c, count = 0;
    while ((c = fgetc(f)) != EOF) {
        if (c == '\n') count++;
    }
    fclose(f);
    return count;
}

struct Especie* cargarEspecies(const char* archivo, int* total) {
    *total = contarLineas(archivo);
    struct Especie* especies = malloc(sizeof(struct Especie) * (*total));

    FILE* f = fopen(archivo, "r");
    if (!f || !especies) {
        perror("Error");
        return NULL;
    }

    int i = 0;
    while (i < *total && fscanf(f, "%49[^,],%f,%f,%f,%f\n",
        especies[i].nombre,
        &especies[i].humedad,
        &especies[i].densidad,
        &especies[i].contracccion,
        &especies[i].radial) == 5) {
        i++;
    }

    fclose(f);
    *total = i;
    return especies;
}

