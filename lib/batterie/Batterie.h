#ifndef BATTERIE_H
#define BATTERIE_H

#include <Arduino.h>

class Batterie
{
  private:
    static constexpr uint8_t BROCHE_MESURE     = A0;
    static constexpr uint8_t BROCHE_ACTIVATION = 6;

    static constexpr uint8_t  RESOLUTION_ADC = 12;
    static constexpr uint16_t VALEUR_MAX_ADC = 4095;

    static constexpr float TENSION_REFERENCE = 3.3f;
    static constexpr float RAPPORT_DIVISION  = 2.0f;

    static constexpr float TENSION_MINIMALE = 3.20f;
    static constexpr float TENSION_MAXIMALE = 4.20f;

    static constexpr uint8_t NOMBRE_MESURES  = 10;
    static constexpr uint8_t DELAI_MESURE_MS = 10;

    uint16_t mesurerValeurADC();
    uint8_t  calculerPourcentage(float tension);

  public:
    Batterie();
    void    initialiser();
    float   mesurerTension();
    uint8_t obtenirPourcentage();
};

#endif // BATTERIE_H