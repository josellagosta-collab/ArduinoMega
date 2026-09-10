#include <Arduino.h>

const int LED = 8;

const char* SSID = "Pixel 7";
const char* PASSWORD = "Alquife+1";

bool estadoLED = false;


// ------------------------------------------------
// Enviar un comando AT
// ------------------------------------------------

void enviarAT(String comando, unsigned long espera)
{
    Serial.print(">> ");
    Serial.println(comando);

    Serial1.print(comando);
    Serial1.print("\r\n");

    unsigned long inicio = millis();

    while (millis() - inicio < espera)
    {
        while (Serial1.available())
        {
            Serial.write(Serial1.read());
        }
    }
}


// ------------------------------------------------
// Enviar página HTML
// ------------------------------------------------

void enviarPagina(int conexion)
{
    String html = "";

    html += "<!DOCTYPE html>";
    html += "<html>";
    html += "<head>";
    html += "<meta charset='UTF-8'>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    html += "<title>Arduino Mega</title>";

    html += "<style>";
    html += "body{font-family:Arial;text-align:center;margin-top:50px;}";
    html += "button{font-size:22px;padding:15px 30px;margin:10px;}";
    html += ".on{background:#28a745;color:white;}";
    html += ".off{background:#dc3545;color:white;}";
    html += "</style>";

    html += "</head>";

    html += "<body>";

    html += "<h1>Arduino Mega 2560</h1>";
    html += "<h2>Control del LED</h2>";

    html += "<p>Estado: ";

    if (estadoLED)
    {
        html += "<strong>ENCENDIDO</strong>";
    }
    else
    {
        html += "<strong>APAGADO</strong>";
    }

    html += "</p>";

    html += "<a href='/led/on'>";
    html += "<button class='on'>ENCENDER</button>";
    html += "</a>";

    html += "<a href='/led/off'>";
    html += "<button class='off'>APAGAR</button>";
    html += "</a>";

    html += "</body>";
    html += "</html>";


    String respuesta = "";

    respuesta += "HTTP/1.1 200 OK\r\n";
    respuesta += "Content-Type: text/html; charset=UTF-8\r\n";
    respuesta += "Connection: close\r\n";
    respuesta += "\r\n";
    respuesta += html;


    Serial1.print("AT+CIPSEND=");
    Serial1.print(conexion);
    Serial1.print(",");
    Serial1.print(respuesta.length());
    Serial1.print("\r\n");

    delay(500);

    Serial1.print(respuesta);

    delay(500);

    Serial1.print("AT+CIPCLOSE=");
    Serial1.print(conexion);
    Serial1.print("\r\n");
}


// ------------------------------------------------
// Procesar petición HTTP
// ------------------------------------------------

void procesarPeticion(String peticion)
{
    Serial.println();
    Serial.println("Peticion recibida:");
    Serial.println(peticion);


    int inicioIPD = peticion.indexOf("+IPD,");

    if (inicioIPD == -1)
    {
        return;
    }


    int posicionComa = peticion.indexOf(',', inicioIPD + 5);

    if (posicionComa == -1)
    {
        return;
    }


    int conexion = peticion.substring(
        inicioIPD + 5,
        posicionComa
    ).toInt();


    if (peticion.indexOf("GET /led/on") >= 0)
    {
        digitalWrite(LED, HIGH);

        estadoLED = true;

        Serial.println("LED ENCENDIDO");
    }


    if (peticion.indexOf("GET /led/off") >= 0)
    {
        digitalWrite(LED, LOW);

        estadoLED = false;

        Serial.println("LED APAGADO");
    }


    enviarPagina(conexion);
}


// ------------------------------------------------
// Configurar ESP8266
// ------------------------------------------------

void configurarESP()
{
    Serial.println();
    Serial.println("Configurando ESP8266...");
    Serial.println();


    enviarAT("AT", 1000);

    enviarAT("AT+CWMODE=1", 1000);


    String conexionWiFi =
        "AT+CWJAP=\"" +
        String(SSID) +
        "\",\"" +
        String(PASSWORD) +
        "\"";

    enviarAT(conexionWiFi, 8000);


    enviarAT("AT+CIPMUX=1", 1000);

    enviarAT("AT+CIPSERVER=1,80", 1000);

    enviarAT("AT+CIFSR", 1000);


    Serial.println();
    Serial.println("Servidor preparado.");
    Serial.println();
}


// ------------------------------------------------
// SETUP
// ------------------------------------------------

void setup()
{
    Serial.begin(9600);

    Serial1.begin(9600);


    pinMode(LED, OUTPUT);

    digitalWrite(LED, LOW);


    delay(2000);


    Serial.println();
    Serial.println("==============================");
    Serial.println(" CONTROL WEB - ARDUINO MEGA");
    Serial.println("==============================");


    configurarESP();
}


// ------------------------------------------------
// LOOP
// ------------------------------------------------

void loop()
{
    if (Serial1.available())
    {
        String datos = Serial1.readString();

        procesarPeticion(datos);
    }
}