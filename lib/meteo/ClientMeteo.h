#ifndef CLIENT_METEO_H
#define CLIENT_METEO_H

#include <Arduino.h>

#include "DonneesMeteo.h"

class ClientMeteo
{
  public:
    ClientMeteo();

    bool recuperer(DonneesMeteo& donnees);

  private:
    static constexpr unsigned int PRECISION_COORDONNEES = 4;

    static constexpr uint8_t CODE_CIEL_DEGAGE       = 0;
    static constexpr uint8_t CODE_NUAGEUX_MAX       = 3;
    static constexpr uint8_t CODE_BROUILLARD_MAX    = 48;
    static constexpr uint8_t CODE_BRUINE_MAX        = 57;
    static constexpr uint8_t CODE_PLUIE_MAX         = 67;
    static constexpr uint8_t CODE_NEIGE_MAX         = 77;
    static constexpr uint8_t CODE_AVERSES_MAX       = 82;
    static constexpr uint8_t CODE_AVERSES_NEIGE_MAX = 86;

    String construireUrl() const;
    String convertirCondition(uint8_t code) const;

    bool effectuerRequete(String& reponse);

    bool analyserReponse(const String& reponse, DonneesMeteo& donnees);
};

#endif // CLIENT_METEO_H