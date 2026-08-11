#include "ClientMeteo.h"

#include <ArduinoJson.h>
#include <HTTPClient.h>

#include "Configuration.h"

ClientMeteo::ClientMeteo()
{
}

String ClientMeteo::construireUrl() const
{
    String url = URL_METEO;

    url += "?latitude=";
    url += String(LATITUDE_METEO, PRECISION_COORDONNEES);

    url += "&longitude=";
    url += String(LONGITUDE_METEO, PRECISION_COORDONNEES);

    url += "&current=temperature_2m,weather_code";
    url += "&daily=temperature_2m_max,temperature_2m_min";
    url += "&timezone=Europe%2FParis";

    return url;
}
bool ClientMeteo::effectuerRequete(String& reponse)
{
    HTTPClient clientHttp;

    if(!clientHttp.begin(construireUrl()))
        return false;

    const int codeHttp = clientHttp.GET();

    if(codeHttp != HTTP_CODE_OK)
    {
        clientHttp.end();
        return false;
    }

    reponse = clientHttp.getString();
    clientHttp.end();

    return true;
}

bool ClientMeteo::analyserReponse(const String& reponse, DonneesMeteo& donnees)
{
    JsonDocument document;

    const DeserializationError erreur = deserializeJson(document, reponse);

    if(erreur)
        return false;

    donnees.temperatureActuelle = document["current"]["temperature_2m"];

    donnees.codeMeteo = document["current"]["weather_code"];

    donnees.temperatureMaximale = document["daily"]["temperature_2m_max"][0];

    donnees.temperatureMinimale = document["daily"]["temperature_2m_min"][0];

    donnees.condition = convertirCondition(donnees.codeMeteo);

    return true;
}

bool ClientMeteo::recuperer(DonneesMeteo& donnees)
{
    String reponse;

    if(!effectuerRequete(reponse))
        return false;

    return analyserReponse(reponse, donnees);
}

String ClientMeteo::convertirCondition(uint8_t code) const
{
    if(code == CODE_CIEL_DEGAGE)
        return "Ciel degage";

    if(code <= CODE_NUAGEUX_MAX)
        return "Nuageux";

    if(code <= CODE_BROUILLARD_MAX)
        return "Brouillard";

    if(code <= CODE_BRUINE_MAX)
        return "Bruine";

    if(code <= CODE_PLUIE_MAX)
        return "Pluie";

    if(code <= CODE_NEIGE_MAX)
        return "Neige";

    if(code <= CODE_AVERSES_MAX)
        return "Averses";

    if(code <= CODE_AVERSES_NEIGE_MAX)
        return "Averses de neige";

    return "Orage";
}