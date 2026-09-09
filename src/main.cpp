#include <Arduino.h>

const unsigned long VELOCIDAD_ESP = 9600;

void setup()
{
    Serial.begin(9600);
    Serial1.begin(VELOCIDAD_ESP);

    delay(2000);

    Serial.println();
    Serial.println("Puente serie iniciado");
    Serial.print("ESP8266 a ");
    Serial.println(VELOCIDAD_ESP);
    Serial.println("Escribe AT y pulsa ENTER");
    Serial.println();
}

void loop()
{
    // Ordenador -> ESP8266
    if (Serial.available() > 0)
    {
        String comando = Serial.readStringUntil('\n');
        comando.trim();

        if (comando.length() > 0)
        {
            Serial.print("Enviando: ");
            Serial.println(comando);

            Serial1.print(comando);
            Serial1.print("\r\n");
        }
    }

    // ESP8266 -> ordenador
    while (Serial1.available() > 0)
    {
        Serial.write(Serial1.read());
    }
}