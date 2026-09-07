#include <Arduino.h>

void setup()
{
    Serial.begin(9600);

    Serial.println("Arduino Mega 2560 R3");
    Serial.println("Conexion serie funcionando correctamente");
}

void loop()
{
    Serial.println("Arduino funcionando...");

    delay(1000);
}