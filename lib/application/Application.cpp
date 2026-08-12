#include "Application.h"

#include <lvgl.h>

Application::Application()
{
}

void Application::initialiser()
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

void Application::executer()
{
    lv_timer_handler();
    actualiserHorloge();
    delay(DELAI_BOUCLE_MS);
}

void Application::initialiserCommunicationSerie()
{
    Serial.begin(VITESSE_BAUD);
}

void Application::initialiserBatterie()
{
    batterie.initialiser();
}

void Application::connecterReseau()
{
    Serial.println("Connexion au Wi-Fi...");

    if(!reseau.connecter())
        Serial.println("Echec de connexion au Wi-Fi.");
}

void Application::afficherInformationsReseau()
{
    if(!reseau.estConnecte())
        return;

    Serial.print("Adresse IP : ");
    Serial.println(reseau.obtenirAdresseIp());
}

void Application::initialiserHorloge()
{
    horloge.initialiser();

    if(!horloge.synchroniser())
        Serial.println("Echec de synchronisation NTP.");
}

void Application::recupererMeteo()
{
    Serial.println("Recuperation de la meteo...");

    if(!clientMeteo.recuperer(donneesMeteo))
        Serial.println("Echec de recuperation meteo.");
}

void Application::initialiserAffichage()
{
    e1001_display_init(&piloteEcran);
    accueil.creer();
}

void Application::actualiserInterface()
{
    accueil.actualiser(horloge.obtenirHeure(),
                       horloge.obtenirDate(),
                       batterie.obtenirPourcentage(),
                       donneesMeteo);
}

void Application::actualiserHorloge()
{
    if(!horloge.minuteChangee())
        return;

    actualiserInterface();
    rafraichirEcran();
}

void Application::rafraichirEcran()
{
    lv_timer_handler();
    e1001_display_refresh(&piloteEcran);
}

void Application::afficherInformationsBatterie()
{
    Serial.print("Tension batterie : ");
    Serial.print(batterie.mesurerTension());
    Serial.println(" V");

    Serial.print("Batterie : ");
    Serial.print(batterie.obtenirPourcentage());
    Serial.println(" %");
}