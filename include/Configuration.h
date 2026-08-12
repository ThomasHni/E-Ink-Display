#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <Arduino.h>

constexpr uint32_t VITESSE_SERIE = 115200;

constexpr uint32_t DELAI_CONNEXION_WIFI_MS = 500;
constexpr uint8_t  NOMBRE_TENTATIVES_WIFI  = 20;

constexpr uint32_t DELAI_SYNCHRONISATION_NTP_MS = 500;
constexpr uint8_t  NOMBRE_TENTATIVES_NTP        = 20;

constexpr char SERVEUR_NTP_PRINCIPAL[]  = "pool.ntp.org";
constexpr char SERVEUR_NTP_SECONDAIRE[] = "time.nist.gov";

constexpr char FUSEAU_HORAIRE[] = "CET-1CEST,M3.5.0,M10.5.0/3";

constexpr float LATITUDE_METEO  = 44.0088F;
constexpr float LONGITUDE_METEO = 4.8728F;

constexpr char URL_METEO[] = "https://api.open-meteo.com/v1/forecast";

constexpr uint32_t DELAI_ACTUALISATION_METEO_MS = 30UL * 60UL * 1000UL;

constexpr char VERSION_APPLICATION[] = "V1.1.0";

#endif