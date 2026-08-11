#include "IconeMeteo.h"

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

void IconeMeteo::actualiser(uint8_t codeMeteo)
{
    effacer();

    const TypeIconeMeteo type = convertirCode(codeMeteo);

    dessiner(type);
}

void IconeMeteo::effacer()
{
    lv_canvas_fill_bg(canvas, lv_color_white(), LV_OPA_COVER);
}

void IconeMeteo::dessiner(TypeIconeMeteo type)
{
    switch(type)
    {
        case TypeIconeMeteo::Soleil:
            dessinerSoleil();
            break;

        case TypeIconeMeteo::PartiellementNuageux:
            dessinerSoleil();
            dessinerNuage();
            break;

        case TypeIconeMeteo::Nuageux:
            dessinerNuage();
            break;

        case TypeIconeMeteo::Brouillard:
            dessinerBrouillard();
            break;

        case TypeIconeMeteo::Pluie:
            dessinerNuage();
            dessinerPluie();
            break;

        case TypeIconeMeteo::Neige:
            dessinerNuage();
            dessinerNeige();
            break;

        case TypeIconeMeteo::Orage:
            dessinerNuage();
            dessinerOrage();
            break;
    }
}

void IconeMeteo::dessinerSoleil()
{
    dessinerCercle(42, 38, 19);

    dessinerLigne(42, 5, 42, 16);
    dessinerLigne(42, 60, 42, 71);

    dessinerLigne(9, 38, 20, 38);
    dessinerLigne(64, 38, 75, 38);

    dessinerLigne(18, 14, 26, 22);
    dessinerLigne(58, 54, 66, 62);

    dessinerLigne(18, 62, 26, 54);
    dessinerLigne(58, 22, 66, 14);
}

void IconeMeteo::dessinerNuage()
{
    dessinerCercle(72, 73, 18);
    dessinerCercle(94, 62, 25);
    dessinerCercle(119, 75, 17);

    dessinerLigne(55, 90, 136, 90);
}

void IconeMeteo::dessinerPluie()
{
    dessinerLigne(69, 99, 64, 113);
    dessinerLigne(94, 99, 89, 113);
    dessinerLigne(119, 99, 114, 113);
}

void IconeMeteo::dessinerNeige()
{
    dessinerLigne(72, 100, 72, 116);
    dessinerLigne(64, 108, 80, 108);

    dessinerLigne(105, 100, 105, 116);
    dessinerLigne(97, 108, 113, 108);
}

void IconeMeteo::dessinerBrouillard()
{
    dessinerLigne(28, 48, 122, 48);
    dessinerLigne(18, 68, 132, 68);
    dessinerLigne(32, 88, 118, 88);
}

void IconeMeteo::dessinerOrage()
{
    dessinerLigne(98, 96, 84, 111);
    dessinerLigne(84, 111, 98, 111);
    dessinerLigne(98, 111, 84, 126);
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
    lv_layer_t couche;
    lv_canvas_init_layer(canvas, &couche);

    lv_draw_arc_dsc_t description;
    lv_draw_arc_dsc_init(&description);

    description.color       = lv_color_black();
    description.width       = EPAISSEUR_TRAIT;
    description.center      = { x, y };
    description.radius      = rayon;
    description.start_angle = 0;
    description.end_angle   = 360;

    lv_draw_arc(&couche, &description);
    lv_canvas_finish_layer(canvas, &couche);
}

TypeIconeMeteo IconeMeteo::convertirCode(uint8_t codeMeteo) const
{
    if(codeMeteo == CODE_CIEL_DEGAGE)
        return TypeIconeMeteo::Soleil;

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