#include <Arduino.h>
#include <lvgl.h>

#include "e1001_display.h"
#include "Accueil.h"
#include "Batterie.h"
#include "Horloge.h"
#include "Reseau.h"
#include "ClientMeteo.h"
#include "DonneesMeteo.h"

static constexpr uint32_t VITESSE_BAUD    = 115200;
static constexpr uint32_t DELAI_BOUCLE_MS = 1000;

e1001_driver_t piloteEcran;

Batterie     batterie;
Horloge      horloge;
Accueil      accueil;
Reseau       reseau;
ClientMeteo  clientMeteo;
DonneesMeteo donneesMeteo;

void initialiserCommunicationSerie()
{
    Serial.begin(VITESSE_BAUD);
}

void initialiserBatterie()
{
    batterie.initialiser();
}

void connecterReseau()
{
    Serial.println("Connexion au Wi-Fi...");

    if(!reseau.connecter())
        Serial.println("Echec de connexion au Wi-Fi.");
}

void afficherInformationsReseau()
{
    if(!reseau.estConnecte())
        return;

    Serial.print("Adresse IP : ");
    Serial.println(reseau.obtenirAdresseIp());
}

void initialiserHorloge()
{
    horloge.initialiser();

    if(!horloge.synchroniser())
        Serial.println("Echec de synchronisation NTP.");
}

void initialiserAffichage()
{
    e1001_display_init(&piloteEcran);
    accueil.creer();
}

void actualiserInterface()
{
    accueil.actualiser(horloge.obtenirHeure(),
                       horloge.obtenirDate(),
                       batterie.obtenirPourcentage(),
                       donneesMeteo);
}

void rafraichirEcran()
{
    lv_timer_handler();
    e1001_display_refresh(&piloteEcran);
}

void actualiserHorloge()
{
    if(!horloge.minuteChangee())
        return;

    actualiserInterface();
    rafraichirEcran();
}

void recupererMeteo()
{
    Serial.println("Recuperation de la meteo...");

    if(!clientMeteo.recuperer(donneesMeteo))
        Serial.println("Echec de recuperation meteo.");
}

void afficherInformationsBatterie()
{
    Serial.print("Tension batterie : ");
    Serial.print(batterie.mesurerTension());
    Serial.println(" V");

    Serial.print("Batterie : ");
    Serial.print(batterie.obtenirPourcentage());
    Serial.println(" %");
}

void initialiserApplication()
{
    initialiserCommunicationSerie();
    initialiserBatterie();
    connecterReseau();
    afficherInformationsReseau();
    initialiserHorloge();
    recupererMeteo();
    initialiserAffichage();
    actualiserInterface();
    rafraichirEcran();
    horloge.minuteChangee();
    afficherInformationsBatterie();
}

void setup()
{
    initialiserApplication();
}

void loop()
{
    lv_timer_handler();
    actualiserHorloge();
    delay(DELAI_BOUCLE_MS);
}