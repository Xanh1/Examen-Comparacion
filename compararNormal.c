#include <stdio.h>
#include "especie/especie.h"
#include <stdlib.h>
#include <time.h>

int main() {
    clock_t inicio, fin;
    double tiempo_total;

    inicio = clock();

    int cantidad = 0;
    struct Especie* especies = cargarEspecies("datos/especies.txt", &cantidad);

    struct Especie base = especies[0];

    for (int i = 1; i < cantidad ; i++){

        int procentajeSimilitud;

        procentajeSimilitud = similitud(base, especies[i]);

        printf("El porcentaje de similitud entre %s y %s es de %d%%\n", 
                base.nombre, 
                especies[i].nombre, 
                procentajeSimilitud);
    }
    
    free(especies);

    fin = clock();

    tiempo_total = (double)(fin - inicio) / CLOCKS_PER_SEC;

    printf("Tiempo de ejecución total: %f segundos\n", tiempo_total);

    return 0;
}
