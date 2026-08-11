#include "Accueil.h"

#include "Configuration.h"

Accueil::Accueil() :
    labelHeure(nullptr), labelDate(nullptr), labelBatterie(nullptr), labelVersion(nullptr),
    labelTemperature(nullptr), labelCondition(nullptr), labelTemperaturesJour(nullptr)
{
}

void Accueil::creer()
{
    lv_obj_clean(lv_scr_act());

    creerEntete();
    creerMeteo();
    creerPiedPage();
    creerSeparateurs();
    appliquerStyles();
}

void Accueil::creerEntete()
{
    labelDate  = lv_label_create(lv_scr_act());
    labelHeure = lv_label_create(lv_scr_act());

    lv_obj_set_width(labelDate, LARGEUR_DATE);
    lv_label_set_long_mode(labelDate, LV_LABEL_LONG_CLIP);

    lv_obj_align(labelDate, LV_ALIGN_TOP_LEFT, MARGE_HORIZONTALE, MARGE_ENTETE);

    lv_obj_align(labelHeure, LV_ALIGN_TOP_RIGHT, -MARGE_HORIZONTALE, MARGE_ENTETE);
}

void Accueil::creerMeteo()
{
    iconeMeteo.creer(lv_scr_act());

    labelTemperature      = lv_label_create(lv_scr_act());
    labelCondition        = lv_label_create(lv_scr_act());
    labelTemperaturesJour = lv_label_create(lv_scr_act());

    lv_obj_align(labelTemperature, LV_ALIGN_CENTER, DECALAGE_X_METEO, DECALAGE_Y_TEMPERATURE);

    lv_obj_align(labelCondition, LV_ALIGN_CENTER, DECALAGE_X_METEO, DECALAGE_Y_CONDITION);

    lv_obj_align(labelTemperaturesJour,
                 LV_ALIGN_CENTER,
                 DECALAGE_X_METEO,
                 DECALAGE_Y_TEMPERATURES_JOUR);
}

void Accueil::creerPiedPage()
{
    labelBatterie = lv_label_create(lv_scr_act());
    labelVersion  = lv_label_create(lv_scr_act());

    lv_obj_align(labelBatterie, LV_ALIGN_BOTTOM_LEFT, MARGE_HORIZONTALE, -MARGE_PIED_PAGE);

    lv_obj_align(labelVersion, LV_ALIGN_BOTTOM_RIGHT, -MARGE_HORIZONTALE, -MARGE_PIED_PAGE);

    lv_label_set_text(labelVersion, VERSION_APPLICATION);
}

void Accueil::actualiser(const String&       heure,
                         const String&       date,
                         uint8_t             batterie,
                         const DonneesMeteo& meteo)
{
    actualiserHorloge(heure, date);
    actualiserBatterie(batterie);
    actualiserMeteo(meteo);
}

void Accueil::actualiserHorloge(const String& heure, const String& date)
{
    lv_label_set_text(labelHeure, heure.c_str());
    lv_label_set_text(labelDate, date.c_str());
}

void Accueil::actualiserBatterie(uint8_t batterie)
{
    const String texte = "Batterie : " + String(batterie) + " %";

    lv_label_set_text(labelBatterie, texte.c_str());
}

void Accueil::actualiserMeteo(const DonneesMeteo& meteo)
{
    const String temperature = creerTexteTemperature(meteo);

    const String temperaturesJour = creerTexteTemperaturesJour(meteo);

    iconeMeteo.actualiser(meteo.codeMeteo);

    lv_label_set_text(labelTemperature, temperature.c_str());
    lv_label_set_text(labelCondition, meteo.condition.c_str());
    lv_label_set_text(labelTemperaturesJour, temperaturesJour.c_str());
}

String Accueil::creerTexteTemperature(const DonneesMeteo& meteo) const
{
    return String(meteo.temperatureActuelle, 0) + " °C";
}

String Accueil::creerTexteTemperaturesJour(const DonneesMeteo& meteo) const
{
    String texte = "Min ";
    texte += String(meteo.temperatureMinimale, 0);
    texte += " °C | Max ";
    texte += String(meteo.temperatureMaximale, 0);
    texte += " °C";

    return texte;
}

void Accueil::appliquerStyleEntete()
{
    lv_obj_set_style_text_font(labelDate, &lv_font_montserrat_20, LV_PART_MAIN);

    lv_obj_set_style_text_font(labelHeure, &lv_font_montserrat_24, LV_PART_MAIN);
}

void Accueil::appliquerStyleMeteo()
{
    lv_obj_set_style_text_font(labelTemperature, &lv_font_montserrat_48, LV_PART_MAIN);

    lv_obj_set_style_text_font(labelCondition, &lv_font_montserrat_24, LV_PART_MAIN);

    lv_obj_set_style_text_font(labelTemperaturesJour, &lv_font_montserrat_18, LV_PART_MAIN);
}

void Accueil::appliquerStylePiedPage()
{
    lv_obj_set_style_text_font(labelBatterie, &lv_font_montserrat_18, LV_PART_MAIN);

    lv_obj_set_style_text_font(labelVersion, &lv_font_montserrat_16, LV_PART_MAIN);
}

void Accueil::appliquerStyles()
{
    appliquerStyleEntete();
    appliquerStyleMeteo();
    appliquerStylePiedPage();
}

void Accueil::creerSeparateurs()
{
    creerLigneHorizontale(POSITION_SEPARATEUR_HAUT);
    creerLigneHorizontale(POSITION_SEPARATEUR_BAS);
}

void Accueil::creerLigneHorizontale(int16_t y)
{
    lv_obj_t* ligne = lv_obj_create(lv_scr_act());

    lv_obj_set_size(ligne, LARGEUR_ECRAN, EPAISSEUR_SEPARATEUR);

    lv_obj_set_pos(ligne, 0, y);

    lv_obj_set_style_border_width(ligne, 0, 0);
    lv_obj_set_style_radius(ligne, 0, 0);
    lv_obj_set_style_bg_color(ligne, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(ligne, LV_OPA_COVER, 0);
    lv_obj_set_style_pad_all(ligne, 0, 0);
}