#include "IconeMeteo.h"

namespace
{
constexpr int16_t CENTRE_ASTRE_X = 45;
constexpr int16_t CENTRE_ASTRE_Y = 39;

constexpr int16_t RAYON_SOLEIL = 21;

constexpr int16_t RAYON_SOLEIL_VERTICAL_X = 45;

constexpr int16_t RAYON_SOLEIL_HAUT_DEBUT_Y = 3;
constexpr int16_t RAYON_SOLEIL_HAUT_FIN_Y   = 14;

constexpr int16_t RAYON_SOLEIL_BAS_DEBUT_Y = 64;
constexpr int16_t RAYON_SOLEIL_BAS_FIN_Y   = 75;

constexpr int16_t RAYON_SOLEIL_HORIZONTAL_Y = 39;

constexpr int16_t RAYON_SOLEIL_GAUCHE_DEBUT_X = 7;
constexpr int16_t RAYON_SOLEIL_GAUCHE_FIN_X   = 18;

constexpr int16_t RAYON_SOLEIL_DROIT_DEBUT_X = 72;
constexpr int16_t RAYON_SOLEIL_DROIT_FIN_X   = 83;

constexpr int16_t DIAGONALE_GAUCHE_X_DEBUT = 17;
constexpr int16_t DIAGONALE_GAUCHE_X_FIN   = 25;

constexpr int16_t DIAGONALE_DROITE_X_DEBUT = 65;
constexpr int16_t DIAGONALE_DROITE_X_FIN   = 73;

constexpr int16_t DIAGONALE_HAUT_Y_DEBUT = 11;
constexpr int16_t DIAGONALE_HAUT_Y_FIN   = 19;

constexpr int16_t DIAGONALE_BAS_Y_DEBUT = 67;
constexpr int16_t DIAGONALE_BAS_Y_FIN   = 59;

constexpr int16_t CENTRE_LUNE_EXTERIEURE_X = 45;
constexpr int16_t CENTRE_LUNE_EXTERIEURE_Y = 40;
constexpr int16_t RAYON_LUNE_EXTERIEURE    = 30;

constexpr int16_t ANGLE_LUNE_EXTERIEURE_DEBUT = 45;
constexpr int16_t ANGLE_LUNE_EXTERIEURE_FIN   = 315;

constexpr int16_t CENTRE_LUNE_INTERIEURE_X = 57;
constexpr int16_t CENTRE_LUNE_INTERIEURE_Y = 35;
constexpr int16_t RAYON_LUNE_INTERIEURE    = 25;

constexpr int16_t ANGLE_LUNE_INTERIEURE_DEBUT = 90;
constexpr int16_t ANGLE_LUNE_INTERIEURE_FIN   = 270;

constexpr int16_t CENTRE_NUAGE_GAUCHE_X = 73;
constexpr int16_t CENTRE_NUAGE_GAUCHE_Y = 76;
constexpr int16_t RAYON_NUAGE_GAUCHE    = 19;

constexpr int16_t CENTRE_NUAGE_CENTRE_X = 98;
constexpr int16_t CENTRE_NUAGE_CENTRE_Y = 64;
constexpr int16_t RAYON_NUAGE_CENTRE    = 27;

constexpr int16_t CENTRE_NUAGE_DROIT_X = 126;
constexpr int16_t CENTRE_NUAGE_DROIT_Y = 77;
constexpr int16_t RAYON_NUAGE_DROIT    = 18;

constexpr int16_t BASE_NUAGE_X_DEBUT = 54;
constexpr int16_t BASE_NUAGE_X_FIN   = 144;
constexpr int16_t BASE_NUAGE_Y       = 94;

constexpr int16_t PLUIE_Y_DEBUT = 103;
constexpr int16_t PLUIE_Y_FIN   = 120;

constexpr int16_t PLUIE_GAUCHE_X_DEBUT = 71;
constexpr int16_t PLUIE_GAUCHE_X_FIN   = 65;

constexpr int16_t PLUIE_CENTRE_X_DEBUT = 99;
constexpr int16_t PLUIE_CENTRE_X_FIN   = 93;

constexpr int16_t PLUIE_DROITE_X_DEBUT = 127;
constexpr int16_t PLUIE_DROITE_X_FIN   = 121;

constexpr int16_t NEIGE_GAUCHE_X = 76;
constexpr int16_t NEIGE_DROITE_X = 112;

constexpr int16_t NEIGE_Y_DEBUT  = 103;
constexpr int16_t NEIGE_Y_CENTRE = 113;
constexpr int16_t NEIGE_Y_FIN    = 123;

constexpr int16_t NEIGE_DEMI_LARGEUR = 9;

constexpr int16_t BROUILLARD_X_HAUT_DEBUT = 28;
constexpr int16_t BROUILLARD_X_HAUT_FIN   = 137;
constexpr int16_t BROUILLARD_Y_HAUT       = 49;

constexpr int16_t BROUILLARD_X_CENTRE_DEBUT = 18;
constexpr int16_t BROUILLARD_X_CENTRE_FIN   = 147;
constexpr int16_t BROUILLARD_Y_CENTRE       = 72;

constexpr int16_t BROUILLARD_X_BAS_DEBUT = 32;
constexpr int16_t BROUILLARD_X_BAS_FIN   = 133;
constexpr int16_t BROUILLARD_Y_BAS       = 95;

constexpr int16_t ORAGE_X_DROIT  = 105;
constexpr int16_t ORAGE_X_GAUCHE = 88;

constexpr int16_t ORAGE_Y_HAUT   = 100;
constexpr int16_t ORAGE_Y_CENTRE = 117;
constexpr int16_t ORAGE_Y_BAS    = 135;
}

IconeMeteo::IconeMeteo() : canvas(nullptr), tampon(nullptr)
{
}

void IconeMeteo::creer(lv_obj_t* parent)
{
    canvas = lv_canvas_create(parent);

    tampon = lv_draw_buf_create(LARGEUR, HAUTEUR, LV_COLOR_FORMAT_L8, LV_STRIDE_AUTO);

    lv_canvas_set_draw_buf(canvas, tampon);

    lv_obj_align(canvas, LV_ALIGN_LEFT_MID, DECALAGE_X, DECALAGE_Y);

    effacer();
}

void IconeMeteo::actualiser(uint8_t codeMeteo, bool estJour)
{
    effacer();

    const TypeIconeMeteo type = convertirCode(codeMeteo);

    dessiner(type, estJour);
}

void IconeMeteo::effacer()
{
    lv_canvas_fill_bg(canvas, lv_color_white(), LV_OPA_COVER);
}

void IconeMeteo::dessiner(TypeIconeMeteo type, bool estJour)
{
    switch(type)
    {
        case TypeIconeMeteo::Degage:
            dessinerAstre(estJour);
            break;

        case TypeIconeMeteo::PartiellementNuageux:
            dessinerAstre(estJour);
            dessinerNuage();
            break;

        case TypeIconeMeteo::Nuageux:
            dessinerNuage();
            break;

        case TypeIconeMeteo::Brouillard:
            dessinerBrouillard();
            break;

        case TypeIconeMeteo::Pluie:
            dessinerAstre(estJour);
            dessinerNuage();
            dessinerPluie();
            break;

        case TypeIconeMeteo::Neige:
            dessinerAstre(estJour);
            dessinerNuage();
            dessinerNeige();
            break;

        case TypeIconeMeteo::Orage:
            dessinerAstre(estJour);
            dessinerNuage();
            dessinerOrage();
            break;
    }
}

void IconeMeteo::dessinerAstre(bool estJour)
{
    if(estJour)
    {
        dessinerSoleil();
        return;
    }

    dessinerLune();
}

void IconeMeteo::dessinerSoleil()
{
    dessinerCercle(CENTRE_ASTRE_X, CENTRE_ASTRE_Y, RAYON_SOLEIL);

    dessinerLigne(RAYON_SOLEIL_VERTICAL_X,
                  RAYON_SOLEIL_HAUT_DEBUT_Y,
                  RAYON_SOLEIL_VERTICAL_X,
                  RAYON_SOLEIL_HAUT_FIN_Y);

    dessinerLigne(RAYON_SOLEIL_VERTICAL_X,
                  RAYON_SOLEIL_BAS_DEBUT_Y,
                  RAYON_SOLEIL_VERTICAL_X,
                  RAYON_SOLEIL_BAS_FIN_Y);

    dessinerLigne(RAYON_SOLEIL_GAUCHE_DEBUT_X,
                  RAYON_SOLEIL_HORIZONTAL_Y,
                  RAYON_SOLEIL_GAUCHE_FIN_X,
                  RAYON_SOLEIL_HORIZONTAL_Y);

    dessinerLigne(RAYON_SOLEIL_DROIT_DEBUT_X,
                  RAYON_SOLEIL_HORIZONTAL_Y,
                  RAYON_SOLEIL_DROIT_FIN_X,
                  RAYON_SOLEIL_HORIZONTAL_Y);

    dessinerLigne(DIAGONALE_GAUCHE_X_DEBUT,
                  DIAGONALE_HAUT_Y_DEBUT,
                  DIAGONALE_GAUCHE_X_FIN,
                  DIAGONALE_HAUT_Y_FIN);

    dessinerLigne(DIAGONALE_DROITE_X_DEBUT,
                  DIAGONALE_BAS_Y_FIN,
                  DIAGONALE_DROITE_X_FIN,
                  DIAGONALE_BAS_Y_DEBUT);

    dessinerLigne(DIAGONALE_GAUCHE_X_DEBUT,
                  DIAGONALE_BAS_Y_DEBUT,
                  DIAGONALE_GAUCHE_X_FIN,
                  DIAGONALE_BAS_Y_FIN);

    dessinerLigne(DIAGONALE_DROITE_X_DEBUT,
                  DIAGONALE_HAUT_Y_FIN,
                  DIAGONALE_DROITE_X_FIN,
                  DIAGONALE_HAUT_Y_DEBUT);
}

void IconeMeteo::dessinerLune()
{
    dessinerArc(CENTRE_LUNE_EXTERIEURE_X,
                CENTRE_LUNE_EXTERIEURE_Y,
                RAYON_LUNE_EXTERIEURE,
                ANGLE_LUNE_EXTERIEURE_DEBUT,
                ANGLE_LUNE_EXTERIEURE_FIN);

    dessinerArc(CENTRE_LUNE_INTERIEURE_X,
                CENTRE_LUNE_INTERIEURE_Y,
                RAYON_LUNE_INTERIEURE,
                ANGLE_LUNE_INTERIEURE_DEBUT,
                ANGLE_LUNE_INTERIEURE_FIN);
}

void IconeMeteo::dessinerNuage()
{
    dessinerCercle(CENTRE_NUAGE_GAUCHE_X, CENTRE_NUAGE_GAUCHE_Y, RAYON_NUAGE_GAUCHE);

    dessinerCercle(CENTRE_NUAGE_CENTRE_X, CENTRE_NUAGE_CENTRE_Y, RAYON_NUAGE_CENTRE);

    dessinerCercle(CENTRE_NUAGE_DROIT_X, CENTRE_NUAGE_DROIT_Y, RAYON_NUAGE_DROIT);

    dessinerLigne(BASE_NUAGE_X_DEBUT, BASE_NUAGE_Y, BASE_NUAGE_X_FIN, BASE_NUAGE_Y);
}

void IconeMeteo::dessinerPluie()
{
    dessinerLigne(PLUIE_GAUCHE_X_DEBUT, PLUIE_Y_DEBUT, PLUIE_GAUCHE_X_FIN, PLUIE_Y_FIN);

    dessinerLigne(PLUIE_CENTRE_X_DEBUT, PLUIE_Y_DEBUT, PLUIE_CENTRE_X_FIN, PLUIE_Y_FIN);

    dessinerLigne(PLUIE_DROITE_X_DEBUT, PLUIE_Y_DEBUT, PLUIE_DROITE_X_FIN, PLUIE_Y_FIN);
}

void IconeMeteo::dessinerNeige()
{
    dessinerLigne(NEIGE_GAUCHE_X, NEIGE_Y_DEBUT, NEIGE_GAUCHE_X, NEIGE_Y_FIN);

    dessinerLigne(NEIGE_GAUCHE_X - NEIGE_DEMI_LARGEUR,
                  NEIGE_Y_CENTRE,
                  NEIGE_GAUCHE_X + NEIGE_DEMI_LARGEUR,
                  NEIGE_Y_CENTRE);

    dessinerLigne(NEIGE_DROITE_X, NEIGE_Y_DEBUT, NEIGE_DROITE_X, NEIGE_Y_FIN);

    dessinerLigne(NEIGE_DROITE_X - NEIGE_DEMI_LARGEUR,
                  NEIGE_Y_CENTRE,
                  NEIGE_DROITE_X + NEIGE_DEMI_LARGEUR,
                  NEIGE_Y_CENTRE);
}

void IconeMeteo::dessinerBrouillard()
{
    dessinerLigne(BROUILLARD_X_HAUT_DEBUT,
                  BROUILLARD_Y_HAUT,
                  BROUILLARD_X_HAUT_FIN,
                  BROUILLARD_Y_HAUT);

    dessinerLigne(BROUILLARD_X_CENTRE_DEBUT,
                  BROUILLARD_Y_CENTRE,
                  BROUILLARD_X_CENTRE_FIN,
                  BROUILLARD_Y_CENTRE);

    dessinerLigne(BROUILLARD_X_BAS_DEBUT, BROUILLARD_Y_BAS, BROUILLARD_X_BAS_FIN, BROUILLARD_Y_BAS);
}

void IconeMeteo::dessinerOrage()
{
    dessinerLigne(ORAGE_X_DROIT, ORAGE_Y_HAUT, ORAGE_X_GAUCHE, ORAGE_Y_CENTRE);

    dessinerLigne(ORAGE_X_GAUCHE, ORAGE_Y_CENTRE, ORAGE_X_DROIT, ORAGE_Y_CENTRE);

    dessinerLigne(ORAGE_X_DROIT, ORAGE_Y_CENTRE, ORAGE_X_GAUCHE, ORAGE_Y_BAS);
}

void IconeMeteo::dessinerLigne(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
    lv_layer_t couche;
    lv_canvas_init_layer(canvas, &couche);

    lv_draw_line_dsc_t description;
    lv_draw_line_dsc_init(&description);

    description.color = lv_color_black();
    description.width = EPAISSEUR_TRAIT;
    description.p1    = { x1, y1 };
    description.p2    = { x2, y2 };

    lv_draw_line(&couche, &description);
    lv_canvas_finish_layer(canvas, &couche);
}

void IconeMeteo::dessinerCercle(int16_t x, int16_t y, int16_t rayon)
{
    dessinerArc(x, y, rayon, 0, 360);
}

void IconeMeteo::dessinerArc(int16_t x,
                             int16_t y,
                             int16_t rayon,
                             int16_t angleDebut,
                             int16_t angleFin)
{
    lv_layer_t couche;
    lv_canvas_init_layer(canvas, &couche);

    lv_draw_arc_dsc_t description;
    lv_draw_arc_dsc_init(&description);

    description.color       = lv_color_black();
    description.width       = EPAISSEUR_TRAIT;
    description.center      = { x, y };
    description.radius      = rayon;
    description.start_angle = angleDebut;
    description.end_angle   = angleFin;

    lv_draw_arc(&couche, &description);
    lv_canvas_finish_layer(canvas, &couche);
}

TypeIconeMeteo IconeMeteo::convertirCode(uint8_t codeMeteo) const
{
    if(codeMeteo == CODE_CIEL_DEGAGE)
        return TypeIconeMeteo::Degage;

    if(codeMeteo <= CODE_PARTIELLEMENT_NUAGEUX_MAX)
        return TypeIconeMeteo::PartiellementNuageux;

    if(codeMeteo <= CODE_NUAGEUX_MAX)
        return TypeIconeMeteo::Nuageux;

    if(codeMeteo <= CODE_BROUILLARD_MAX)
        return TypeIconeMeteo::Brouillard;

    if(codeMeteo <= CODE_PLUIE_MAX)
        return TypeIconeMeteo::Pluie;

    if(codeMeteo <= CODE_NEIGE_MAX)
        return TypeIconeMeteo::Neige;

    return TypeIconeMeteo::Orage;
}