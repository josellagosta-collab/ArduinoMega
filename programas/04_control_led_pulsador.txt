#include <Arduino.h>

const int PULSADOR = 7;
const int LED = 8;
const unsigned long ANTIRREBOTE_MS = 50;

bool ledEncendido = false; // Memoria del estado del LED.
int ultimaLectura = HIGH;
int estadoEstable = HIGH;
unsigned long ultimoCambio = 0;

void setup()
{
    pinMode(PULSADOR, INPUT_PULLUP);
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
}

void loop()
{
    int lectura = digitalRead(PULSADOR);
    unsigned long ahora = millis();

    // Esperamos a que la lectura se mantenga estable durante 50 ms.
    if (lectura != ultimaLectura)
    {
        ultimoCambio = ahora;
        ultimaLectura = lectura;
    }

    if (ahora - ultimoCambio >= ANTIRREBOTE_MS && lectura != estadoEstable)
    {
        estadoEstable = lectura;

        // Con INPUT_PULLUP, LOW indica una pulsacion.
        // Solo cambiamos al pulsar, no al soltar ni al mantener pulsado.
        if (estadoEstable == LOW)
        {
            ledEncendido = !ledEncendido;
            digitalWrite(LED, ledEncendido ? HIGH : LOW);
        }
    }
}
