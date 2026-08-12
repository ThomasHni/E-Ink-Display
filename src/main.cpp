#include <Arduino.h>
#include "Application.h"

Application application;

void setup()
{
    application.initialiser();
}

void loop()
{
    application.executer();
}