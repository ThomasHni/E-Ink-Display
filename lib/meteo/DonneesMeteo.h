#ifndef DONNEES_METEO_H
#define DONNEES_METEO_H

#include <Arduino.h>

struct DonneesMeteo
{
    float temperatureActuelle = 0.0F;
    float temperatureMinimale = 0.0F;
    float temperatureMaximale = 0.0F;

    uint8_t codeMeteo = 0;

    bool estJour = true;

    String condition = "Indisponible";
};

#endif // DONNEES_METEO_H