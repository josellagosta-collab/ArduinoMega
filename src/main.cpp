#include <Arduino.h>

void setup()
{
    Serial.begin(9600);
    Serial1.begin(9600);

    Serial.println("Puente Serial <-> Serial1 iniciado");
}

void loop()
{
    if (Serial.available() > 0)
    {
        char dato = Serial.read();

        Serial1.write(dato);
    }

    if (Serial1.available() > 0)
    {
        char dato = Serial1.read();

        Serial.write(dato);
    }
}