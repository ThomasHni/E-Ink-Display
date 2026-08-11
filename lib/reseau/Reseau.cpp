#include "Reseau.h"

#include "Configuration.h"
#include "Secrets.h"

Reseau::Reseau()
{
}

bool Reseau::connecter()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(NOM_RESEAU_WIFI, MOT_DE_PASSE_WIFI);

    return attendreConnexion();
}

bool Reseau::attendreConnexion() const
{
    uint8_t tentative = 0;

    while(!estConnecte() && tentative < NOMBRE_TENTATIVES_WIFI)
    {
        delay(DELAI_CONNEXION_WIFI_MS);
        tentative++;
    }

    return estConnecte();
}

bool Reseau::estConnecte() const
{
    return WiFi.status() == WL_CONNECTED;
}

String Reseau::obtenirAdresseIp() const
{
    return WiFi.localIP().toString();
}

void Reseau::deconnecter()
{
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
}