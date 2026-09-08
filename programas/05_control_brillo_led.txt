#include <Arduino.h>

const int LED = 9;

void setup()
{
    pinMode(LED, OUTPUT);
}

void loop()
{
    for (int brillo = 0; brillo <= 255; brillo++)
    {
        analogWrite(LED, brillo);
        delay(10);
    }

    for (int brillo = 255; brillo >= 0; brillo--)
    {
        analogWrite(LED, brillo);
        delay(10);
    }
}