#include "Horloge.h"

#include "Configuration.h"

Horloge::Horloge() : minutePrecedente(-1)
{
}

void Horloge::initialiser()
{
    configTzTime(FUSEAU_HORAIRE, SERVEUR_NTP_PRINCIPAL, SERVEUR_NTP_SECONDAIRE);
}

bool Horloge::obtenirInformationsTemps(tm& informationsTemps)
{
    uint8_t tentative = 0;

    while(tentative < NOMBRE_TENTATIVES_NTP)
    {
        if(getLocalTime(&informationsTemps))
            return true;

        delay(DELAI_SYNCHRONISATION_NTP_MS);
        tentative++;
    }

    return false;
}

bool Horloge::synchroniser()
{
    tm informationsTemps = {};

    return obtenirInformationsTemps(informationsTemps);
}

String Horloge::obtenirHeure()
{
    tm informationsTemps = {};

    if(!obtenirInformationsTemps(informationsTemps))
        return "--:--";

    char heure[TAILLE_HEURE];
    strftime(heure, sizeof(heure), "%H:%M", &informationsTemps);

    return String(heure);
}

String Horloge::obtenirDate()
{
    tm informationsTemps = {};

    if(!obtenirInformationsTemps(informationsTemps))
        return "Date indisponible";

    return formaterDate(informationsTemps);
}

String Horloge::formaterDate(const tm& informationsTemps)
{
    static const char* JOURS[] = { "Dimanche", "Lundi",    "Mardi", "Mercredi",
                                   "Jeudi",    "Vendredi", "Samedi" };

    static const char* MOIS[] = { "janvier",   "fevrier", "mars",     "avril",
                                  "mai",       "juin",    "juillet",  "aout",
                                  "septembre", "octobre", "novembre", "decembre" };

    char date[TAILLE_DATE];

    snprintf(date,
             sizeof(date),
             "%s %d %s %d",
             JOURS[informationsTemps.tm_wday],
             informationsTemps.tm_mday,
             MOIS[informationsTemps.tm_mon],
             informationsTemps.tm_year + 1900);

    return String(date);
}

bool Horloge::minuteChangee()
{
    tm informationsTemps = {};

    if(!obtenirInformationsTemps(informationsTemps))
        return false;

    if(informationsTemps.tm_min == minutePrecedente)
        return false;

    minutePrecedente = informationsTemps.tm_min;

    return true;
}