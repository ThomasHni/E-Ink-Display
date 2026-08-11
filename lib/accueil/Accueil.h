#ifndef ACCUEIL_H
#define ACCUEIL_H

#include <Arduino.h>
#include <lvgl.h>

#include "DonneesMeteo.h"
#include "IconeMeteo.h"

class Accueil
{
  public:
    Accueil();

    void creer();

    void actualiser(const String&       heure,
                    const String&       date,
                    uint8_t             batterie,
                    const DonneesMeteo& meteo);

  private:
    static constexpr int16_t LARGEUR_DATE = 500;

    static constexpr int16_t MARGE_HORIZONTALE = 20;
    static constexpr int16_t MARGE_ENTETE      = 18;
    static constexpr int16_t MARGE_PIED_PAGE   = 18;

    static constexpr int16_t DECALAGE_X_METEO             = 90;
    static constexpr int16_t DECALAGE_Y_TEMPERATURE       = -55;
    static constexpr int16_t DECALAGE_Y_CONDITION         = 10;
    static constexpr int16_t DECALAGE_Y_TEMPERATURES_JOUR = 50;

    static constexpr int16_t POSITION_SEPARATEUR_HAUT = 50;
    static constexpr int16_t POSITION_SEPARATEUR_BAS  = 430;

    static constexpr int16_t LARGEUR_ECRAN        = 800;
    static constexpr int16_t EPAISSEUR_SEPARATEUR = 2;

    lv_obj_t* labelHeure;
    lv_obj_t* labelDate;
    lv_obj_t* labelBatterie;
    lv_obj_t* labelVersion;

    lv_obj_t* labelTemperature;
    lv_obj_t* labelCondition;
    lv_obj_t* labelTemperaturesJour;

    IconeMeteo iconeMeteo;

    void creerEntete();
    void creerMeteo();
    void creerPiedPage();
    void creerSeparateurs();
    void creerLigneHorizontale(int16_t y);

    void actualiserHorloge(const String& heure, const String& date);

    void actualiserBatterie(uint8_t batterie);
    void actualiserMeteo(const DonneesMeteo& meteo);

    void appliquerStyles();
    void appliquerStyleEntete();
    void appliquerStyleMeteo();
    void appliquerStylePiedPage();

    String creerTexteTemperature(const DonneesMeteo& meteo) const;

    String creerTexteTemperaturesJour(const DonneesMeteo& meteo) const;
};

#endif // ACCUEIL_H