#ifndef ICONE_METEO_H
#define ICONE_METEO_H

#include <Arduino.h>
#include <lvgl.h>

enum class TypeIconeMeteo
{
    Degage,
    PartiellementNuageux,
    Nuageux,
    Brouillard,
    Pluie,
    Neige,
    Orage
};

class IconeMeteo
{
  public:
    IconeMeteo();

    void creer(lv_obj_t* parent);
    void actualiser(uint8_t codeMeteo, bool estJour);

  private:
    static constexpr int16_t LARGEUR = 170;
    static constexpr int16_t HAUTEUR = 140;

    static constexpr int16_t DECALAGE_X = 350;
    static constexpr int16_t DECALAGE_Y = 10;

    static constexpr uint8_t EPAISSEUR_TRAIT = 3;

    static constexpr uint8_t CODE_CIEL_DEGAGE               = 0;
    static constexpr uint8_t CODE_PARTIELLEMENT_NUAGEUX_MAX = 2;
    static constexpr uint8_t CODE_NUAGEUX_MAX               = 3;
    static constexpr uint8_t CODE_BROUILLARD_MAX            = 48;
    static constexpr uint8_t CODE_PLUIE_MAX                 = 67;
    static constexpr uint8_t CODE_NEIGE_MAX                 = 86;

    lv_obj_t*      canvas;
    lv_draw_buf_t* tampon;

    TypeIconeMeteo convertirCode(uint8_t codeMeteo) const;

    void effacer();

    void dessiner(TypeIconeMeteo type, bool estJour);
    void dessinerAstre(bool estJour);

    void dessinerSoleil();
    void dessinerLune();
    void dessinerNuage();
    void dessinerPluie();
    void dessinerNeige();
    void dessinerBrouillard();
    void dessinerOrage();

    void dessinerLigne(int16_t x1, int16_t y1, int16_t x2, int16_t y2);

    void dessinerCercle(int16_t x, int16_t y, int16_t rayon);

    void dessinerArc(int16_t x, int16_t y, int16_t rayon, int16_t angleDebut, int16_t angleFin);
};

#endif // ICONE_METEO_H