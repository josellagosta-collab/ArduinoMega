#include <Arduino.h>

const int POTENCIOMETRO = A0;

void setup()
{
    Serial.begin(9600);

    Serial.println("Lectura del potenciometro");
}

void loop()
{
    int valor = analogRead(POTENCIOMETRO);

    float voltaje = valor * 5.0 / 1023.0;

    Serial.print("ADC: ");
    Serial.print(valor);

    Serial.print("   Voltaje: ");
    Serial.print(voltaje);

    Serial.println(" V");

    delay(200);
}