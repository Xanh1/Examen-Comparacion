#include <math.h>
#include "especie.h"

const float MAX_DIF_HUMEDAD = 20.0;
const float MAX_DIF_DENSIDAD = 5.0;
const float MAX_DIF_CONTRACCION = 0.1;
const float MAX_DIF_RADIAL = 0.1;


int similitud(struct Especie base, struct Especie comparar){

    float totalSimilitud = 0;

    float difHumedad = fabs(base.humedad - comparar.humedad);
    float porcHumedad = (1.0 - (difHumedad / MAX_DIF_HUMEDAD));
    if (porcHumedad < 0) porcHumedad = 0;
    totalSimilitud += porcHumedad * 0.25;

    float difDensidad = fabs(base.densidad - comparar.densidad);
    float porcDensidad = (1.0 - (difDensidad / MAX_DIF_DENSIDAD));
    if (porcDensidad < 0) porcDensidad = 0;
    totalSimilitud += porcDensidad * 0.25;

    float difContraccion = fabs(base.contracccion - comparar.contracccion);
    float porcContraccion = (1.0 - (difContraccion / MAX_DIF_CONTRACCION));
    if (porcContraccion < 0) porcContraccion = 0;
    totalSimilitud += porcContraccion * 0.25;

    float difRadial = fabs(base.radial - comparar.radial);
    float porcRadial = (1.0 - (difRadial / MAX_DIF_RADIAL));
    if (porcRadial < 0) porcRadial = 0;
    totalSimilitud += porcRadial * 0.25;

    return totalSimilitud * 100;
}