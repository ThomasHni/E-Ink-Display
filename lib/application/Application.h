#ifndef APPLICATION_H
#define APPLICATION_H

#include <Arduino.h>

#include "e1001_display.h"
#include "Accueil.h"
#include "Batterie.h"
#include "Horloge.h"
#include "Reseau.h"
#include "ClientMeteo.h"
#include "DonneesMeteo.h"

class Application
{
  private:
    static constexpr uint32_t VITESSE_BAUD    = 115200;
    static constexpr uint32_t DELAI_BOUCLE_MS = 1000;

    e1001_driver_t piloteEcran;
    Batterie       batterie;
    Horloge        horloge;
    Accueil        accueil;
    Reseau         reseau;
    ClientMeteo    clientMeteo;
    DonneesMeteo   donneesMeteo;

    void initialiserCommunicationSerie();
    void initialiserBatterie();
    void connecterReseau();
    void initialiserHorloge();
    void initialiserAffichage();

    void recupererMeteo();
    void actualiserInterface();
    void actualiserHorloge();
    void rafraichirEcran();

    void afficherInformationsReseau();
    void afficherInformationsBatterie();

  public:
    Application();

    void initialiser();
    void executer();
};

#endif // APPLICATION_H