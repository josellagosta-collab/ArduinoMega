#include <Arduino.h>

// ------------------------------------------------
// CONFIGURACIÓN DEL SENSOR
// ------------------------------------------------

const int SENSOR = A0;


// ------------------------------------------------
// CONFIGURACIÓN WIFI
// ------------------------------------------------

const char* SSID = "Pixel 7";
const char* PASSWORD = "Alquife+1";


// ------------------------------------------------
// CONFIGURACIÓN INFLUXDB
// ------------------------------------------------

// IP del ordenador Windows 11 donde se ejecuta InfluxDB
const char* IP_INFLUX = "10.113.170.1";

// Puerto por defecto de InfluxDB
const int PUERTO_INFLUX = 8086;

// Nombre de la organización
const char* ORGANIZACION = "ArduinoCurso";

// Nombre del bucket
const char* BUCKET = "arduino";

// Token con permisos de escritura
const char* TOKEN = "lMUwGrWtDpo0hbHe9fZWIichyTgCQXvh-AYm_gPWyl3ntdJt4mRuqDOnXhLXc1gpu6YACuCKZjR8CQHPwwDxfQ==";


// ------------------------------------------------
// ENVIAR COMANDO AT
// ------------------------------------------------

void enviarAT(String comando, unsigned long tiempoEspera)
{
    Serial.print(">> ");
    Serial.println(comando);

    Serial1.print(comando);
    Serial1.print("\r\n");

    unsigned long inicio = millis();

    while (millis() - inicio < tiempoEspera)
    {
        while (Serial1.available())
        {
            Serial.write(Serial1.read());
        }
    }
}


// ------------------------------------------------
// MOSTRAR RESPUESTA DEL ESP8266
// ------------------------------------------------

void mostrarRespuestaESP(unsigned long tiempo)
{
    unsigned long inicio = millis();

    while (millis() - inicio < tiempo)
    {
        while (Serial1.available())
        {
            Serial.write(Serial1.read());
        }
    }
}


// ------------------------------------------------
// CONECTAR EL ESP8266 AL WIFI
// ------------------------------------------------

void conectarWiFi()
{
    Serial.println();
    Serial.println("==============================");
    Serial.println(" CONFIGURANDO ESP8266");
    Serial.println("==============================");
    Serial.println();

    // Comprobar comunicación con el ESP8266
    enviarAT("AT", 1000);

    // Configurar como estación Wi-Fi
    enviarAT("AT+CWMODE=1", 1000);

    // Construir comando de conexión Wi-Fi
    String comandoWiFi =
        "AT+CWJAP=\"" +
        String(SSID) +
        "\",\"" +
        String(PASSWORD) +
        "\"";

    // Conectar a la red
    enviarAT(comandoWiFi, 8000);

    // Desactivar servidor de prácticas anteriores
    enviarAT("AT+CIPSERVER=0", 1000);

    // Utilizar una única conexión TCP
    enviarAT("AT+CIPMUX=0", 1000);

    // Mostrar dirección IP
    enviarAT("AT+CIFSR", 1000);

    Serial.println();
    Serial.println("ESP8266 preparado.");
    Serial.println();
}


// ------------------------------------------------
// ENVIAR MEDIDA A INFLUXDB
// ------------------------------------------------

void enviarInflux(int valor)
{
    // Calcular voltaje aproximado
    float voltaje =
        valor * 5.0 / 1023.0;


    // --------------------------------------------
    // Crear Line Protocol
    // --------------------------------------------

    String datos =
        "sensor valor=" +
        String(valor) +
        ",voltaje=" +
        String(voltaje, 2);


    Serial.println();
    Serial.println("--------------------------------");
    Serial.println("Datos que se enviaran:");
    Serial.println(datos);
    Serial.println("--------------------------------");


    // --------------------------------------------
    // Crear la ruta de escritura de InfluxDB
    // --------------------------------------------

    String ruta =
        "/api/v2/write?org=" +
        String(ORGANIZACION) +
        "&bucket=" +
        String(BUCKET) +
        "&precision=s";


    // --------------------------------------------
    // Crear la petición HTTP POST
    // --------------------------------------------

    String peticion = "";

    peticion += "POST ";
    peticion += ruta;
    peticion += " HTTP/1.1\r\n";

    peticion += "Host: ";
    peticion += IP_INFLUX;
    peticion += ":";
    peticion += String(PUERTO_INFLUX);
    peticion += "\r\n";

    peticion += "Authorization: Token ";
    peticion += TOKEN;
    peticion += "\r\n";

    peticion += "Content-Type: text/plain\r\n";

    peticion += "Content-Length: ";
    peticion += String(datos.length());
    peticion += "\r\n";

    peticion += "Connection: close\r\n";

    peticion += "\r\n";

    peticion += datos;


    // --------------------------------------------
    // Abrir conexión TCP con InfluxDB
    // --------------------------------------------

    String comandoConexion =
        "AT+CIPSTART=\"TCP\",\"" +
        String(IP_INFLUX) +
        "\"," +
        String(PUERTO_INFLUX);


    Serial.println();
    Serial.println("Abriendo conexion con InfluxDB...");
    Serial.print(">> ");
    Serial.println(comandoConexion);

    Serial1.print(comandoConexion);
    Serial1.print("\r\n");

    mostrarRespuestaESP(3000);


    // --------------------------------------------
    // Indicar cuantos bytes enviaremos
    // --------------------------------------------

    Serial.println();
    Serial.print("Longitud de la peticion: ");
    Serial.println(peticion.length());

    Serial1.print("AT+CIPSEND=");
    Serial1.print(peticion.length());
    Serial1.print("\r\n");

    mostrarRespuestaESP(1500);


    // --------------------------------------------
    // Enviar petición HTTP
    // --------------------------------------------

    Serial.println();
    Serial.println("Enviando peticion HTTP...");

    Serial1.print(peticion);


    // --------------------------------------------
    // Mostrar respuesta de InfluxDB
    // --------------------------------------------

    Serial.println();
    Serial.println("Respuesta de InfluxDB:");

    mostrarRespuestaESP(4000);


    /*
        No enviamos AT+CIPCLOSE.

        En la petición HTTP hemos incluido:

        Connection: close

        InfluxDB cerrará la conexión después
        de responder.
    */


    Serial.println();
    Serial.println("Envio finalizado.");
    Serial.println();
}


// ------------------------------------------------
// SETUP
// ------------------------------------------------

void setup()
{
    // PC <-> Arduino Mega
    Serial.begin(9600);

    // Arduino Mega <-> ESP8266
    Serial1.begin(9600);

    delay(2000);


    Serial.println();
    Serial.println("==============================");
    Serial.println(" LECCION 18 - INFLUXDB");
    Serial.println("==============================");
    Serial.println();


    // Conectar al Wi-Fi
    conectarWiFi();
}


// ------------------------------------------------
// LOOP
// ------------------------------------------------

void loop()
{
    // Leer sensor conectado a A0
    int valor = analogRead(SENSOR);


    Serial.println();
    Serial.print("Valor sensor: ");
    Serial.println(valor);


    // Enviar a InfluxDB
    enviarInflux(valor);


    // Esperar 10 segundos
    delay(10000);
}