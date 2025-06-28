#ifndef especie
#define especie

struct Especie {
    char nombre[20];
    float humedad;
    float densidad;
    float contracccion;
    float radial;
};

struct Especie* cargarEspecies(const char* archivo, int* total);

int similitud(struct Especie base, struct Especie comparar);

#endif
