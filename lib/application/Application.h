#ifndef APPLICATION_H
#define APPLICATION_H

#include <Arduino.h>
#include "Accueil.h"
#include "Batterie.h"
#include "ClientMeteo.h"
#include "DonneesMeteo.h"
#include "Horloge.h"
#include "Reseau.h"
#include "e1001_display.h"

class Application
{
  private:
    static constexpr uint32_t VITESSE_BAUD             = 115200UL;
    static constexpr uint32_t DELAI_BOUCLE_MS          = 1000UL;
    static constexpr uint32_t DUREE_MINUTE_MS          = 60000UL;
    static constexpr uint8_t  INTERVALLE_METEO_MINUTES = 15;
    static constexpr uint32_t INTERVALLE_METEO_MS      = INTERVALLE_METEO_MINUTES * DUREE_MINUTE_MS;

    e1001_driver_t piloteEcran;
    Batterie       batterie;
    Horloge        horloge;
    Accueil        accueil;
    Reseau         reseau;
    ClientMeteo    clientMeteo;
    DonneesMeteo   donneesMeteo;
    uint32_t       derniereActualisationMeteo;

    void initialiserCommunicationSerie();
    void initialiserBatterie();
    void connecterReseau();
    void initialiserHorloge();
    void initialiserAffichage();
    bool recupererMeteo();
    void actualiserInterface();
    void actualiserHorloge();
    bool actualiserMeteoPeriodiquement();
    bool meteoDoitEtreActualisee() const;
    void rafraichirEcran();
    void afficherInformationsReseau();
    void afficherInformationsBatterie();

  public:
    Application();

    void initialiser();
    void executer();
};

#endif // APPLICATION_H