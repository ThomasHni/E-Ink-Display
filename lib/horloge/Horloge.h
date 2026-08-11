#ifndef HORLOGE_H
#define HORLOGE_H

#include <Arduino.h>
#include <time.h>

class Horloge
{
  private:
    static constexpr size_t TAILLE_HEURE = 6;
    static constexpr size_t TAILLE_DATE  = 32;

    int minutePrecedente;

    bool   obtenirInformationsTemps(tm& informationsTemps);
    String formaterDate(const tm& informationsTemps);

  public:
    Horloge();

    void   initialiser();
    bool   synchroniser();
    bool   minuteChangee();
    String obtenirHeure();
    String obtenirDate();
};

#endif