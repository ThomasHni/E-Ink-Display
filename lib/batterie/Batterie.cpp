#include "Batterie.h"

Batterie::Batterie()
{
}

void Batterie::initialiser()
{
    analogReadResolution(RESOLUTION_ADC);
    pinMode(BROCHE_MESURE, INPUT);
    pinMode(BROCHE_ACTIVATION, OUTPUT);
    digitalWrite(BROCHE_ACTIVATION, HIGH);
}

uint16_t Batterie::mesurerValeurADC()
{
    uint32_t somme = 0;
    for(uint8_t mesure = 0; mesure < NOMBRE_MESURES; ++mesure)
    {
        somme += analogRead(BROCHE_MESURE);
        delay(DELAI_MESURE_MS);
    }
    return static_cast<uint16_t>(somme / NOMBRE_MESURES);
}

float Batterie::mesurerTension()
{
    const uint16_t valeurAdc  = mesurerValeurADC();
    const float    rapportAdc = valeurAdc / static_cast<float>(VALEUR_MAX_ADC);

    return rapportAdc * TENSION_REFERENCE * RAPPORT_DIVISION;
}

uint8_t Batterie::calculerPourcentage(float tension)
{
    tension = constrain(tension, TENSION_MINIMALE, TENSION_MAXIMALE);

    const float plage  = TENSION_MAXIMALE - TENSION_MINIMALE;
    const float niveau = tension - TENSION_MINIMALE;

    return static_cast<uint8_t>((niveau / plage) * 100.0F);
}

uint8_t Batterie::obtenirPourcentage()
{
    return calculerPourcentage(mesurerTension());
}