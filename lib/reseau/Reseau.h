#ifndef RESEAU_H
#define RESEAU_H

#include <Arduino.h>
#include <WiFi.h>

class Reseau
{
  private:
    bool attendreConnexion() const;

  public:
    Reseau();

    bool   connecter();
    void   deconnecter();
    bool   estConnecte() const;
    String obtenirAdresseIp() const;
};

#endif