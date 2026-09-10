# Lección 16 — Mostrar datos de un sensor en una página web

## 1. Objetivos

En la lección anterior aprendimos a controlar un LED desde una página web.

Ahora vamos a realizar el proceso contrario: enviar información desde Arduino hacia el navegador.

Al finalizar esta práctica seremos capaces de:

* Leer un sensor analógico desde Arduino.
* Mostrar su valor en una página web.
* Comprender el flujo sensor → Arduino → ESP8266 → navegador.
* Actualizar la página para visualizar nuevos valores.
* Combinar control y monitorización en un mismo sistema.
* Preparar el proyecto para futuras conexiones con InfluxDB y Grafana.

El resultado será:

```text
POTENCIÓMETRO
      │
      ▼
ARDUINO MEGA
      │
      │ UART
      ▼
   ESP8266
      │
      │ Wi-Fi
      ▼
   NAVEGADOR
```

---

## 2. Material necesario

Necesitamos:

* Arduino Mega 2560 R3.
* ESP8266 ESP-01.
* Fuente regulada de 3,3 V.
* Protoboard.
* Potenciómetro.
* LED.
* Resistencia de 220 Ω.
* Resistencia de 1 kΩ.
* Resistencia de 2 kΩ.
* Cables Dupont.
* Cable USB.
* Ordenador con Visual Studio Code y PlatformIO.
* Red Wi-Fi de 2,4 GHz.

---

# 3. Montaje del ESP8266

Conservamos exactamente el montaje utilizado en las lecciones anteriores.

## Comunicación UART

```text
Mega D18 / TX1
      │
     1 kΩ
      │
      ├────────────── ESP8266 RX
      │
     2 kΩ
      │
     GND


ESP8266 TX ────────── Mega D19 / RX1
```

La velocidad comprobada de nuestros módulos es:

```cpp
Serial1.begin(9600);
```

---

# 4. Conexión del LED

Mantendremos el LED de la práctica anterior:

```text
D8
 │
220 Ω
 │
LED
 │
GND
```

Esto nos permitirá seguir controlándolo desde la página web.

---

# 5. Conexión del potenciómetro

Conectaremos el potenciómetro al pin analógico `A0`.

```text
        POTENCIÓMETRO

5 V ───────── terminal exterior

A0  ───────── terminal central

GND ───────── terminal exterior
```

El terminal central es el cursor del potenciómetro.

Arduino leerá valores entre:

```text
0
```

y:

```text
1023
```

mediante:

```cpp
analogRead(A0);
```

---

# 6. ¿Qué vamos a mostrar?

La página web mostrará algo parecido a:

```text
+----------------------------------+
|                                  |
|       ARDUINO MEGA 2560          |
|                                  |
|       Control del LED            |
|                                  |
|       Estado: APAGADO            |
|                                  |
|    [ ENCENDER ] [ APAGAR ]       |
|                                  |
|    Valor del sensor: 537         |
|                                  |
|         [ ACTUALIZAR ]           |
|                                  |
+----------------------------------+
```

El número cambiará dependiendo de la posición del potenciómetro.

---

# 7. Flujo de información

En esta práctica tendremos dos direcciones de comunicación.

## Control

```text
Navegador
   │
   ▼
ESP8266
   │
   ▼
Arduino
   │
   ▼
LED
```

## Monitorización

```text
Potenciómetro
      │
      ▼
Arduino
      │
      ▼
ESP8266
      │
      ▼
Navegador
```

Nuestro sistema ya será bidireccional.

---

# 8. Leer el sensor

Definiremos:

```cpp
const int SENSOR = A0;
```

y leeremos:

```cpp
int valorSensor = analogRead(SENSOR);
```

Si el potenciómetro está aproximadamente en la mitad podemos obtener:

```text
512
```

Cerca de un extremo:

```text
0
```

y cerca del otro:

```text
1023
```

---

# 9. Convertir la lectura a voltaje

El ADC del Arduino Mega utiliza 10 bits.

Por tanto:

```text
2^10 = 1024 valores
```

que corresponden aproximadamente al rango:

```text
0 V → 5 V
```

Podemos calcular una tensión aproximada mediante:

```cpp
float voltaje = valorSensor * 5.0 / 1023.0;
```

Por ejemplo:

```text
valor ADC = 512
```

produce aproximadamente:

```text
2,50 V
```

Mostraremos tanto el valor ADC como el voltaje.

---

# 10. Programa completo

Crea:

```text
ejemplos/16_sensor_web/main.cpp
```

con el siguiente programa.

```cpp
#include <Arduino.h>

const int LED = 8;
const int SENSOR = A0;

const char* SSID = "NOMBRE_WIFI";
const char* PASSWORD = "CONTRASENA_WIFI";

bool estadoLED = false;


// ------------------------------------------------
// Enviar comando AT
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
    int valorSensor = analogRead(SENSOR);

    float voltaje =
        valorSensor * 5.0 / 1023.0;


    String html = "";

    html += "<!DOCTYPE html>";
    html += "<html>";

    html += "<head>";

    html += "<meta charset='UTF-8'>";

    html +=
        "<meta name='viewport' "
        "content='width=device-width, initial-scale=1'>";

    html += "<title>Arduino Mega</title>";


    html += "<style>";

    html +=
        "body{"
        "font-family:Arial;"
        "text-align:center;"
        "margin-top:40px;"
        "}";

    html +=
        "button{"
        "font-size:20px;"
        "padding:15px 25px;"
        "margin:10px;"
        "}";

    html +=
        ".on{"
        "background:#28a745;"
        "color:white;"
        "}";

    html +=
        ".off{"
        "background:#dc3545;"
        "color:white;"
        "}";

    html +=
        ".actualizar{"
        "background:#007bff;"
        "color:white;"
        "}";

    html +=
        ".dato{"
        "font-size:28px;"
        "font-weight:bold;"
        "}";

    html += "</style>";

    html += "</head>";


    html += "<body>";

    html += "<h1>Arduino Mega 2560</h1>";

    html += "<h2>Control y monitorizacion</h2>";


    html += "<h3>Estado del LED</h3>";

    html += "<p>";

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
    html +=
        "<button class='on'>"
        "ENCENDER"
        "</button>";
    html += "</a>";


    html += "<a href='/led/off'>";
    html +=
        "<button class='off'>"
        "APAGAR"
        "</button>";
    html += "</a>";


    html += "<hr>";


    html += "<h3>Sensor analogico A0</h3>";

    html += "<p>Valor ADC:</p>";

    html += "<p class='dato'>";
    html += String(valorSensor);
    html += "</p>";


    html += "<p>Voltaje:</p>";

    html += "<p class='dato'>";
    html += String(voltaje, 2);
    html += " V";
    html += "</p>";


    html += "<a href='/'>";
    html +=
        "<button class='actualizar'>"
        "ACTUALIZAR"
        "</button>";
    html += "</a>";


    html += "</body>";
    html += "</html>";


    String respuesta = "";

    respuesta += "HTTP/1.1 200 OK\r\n";
    respuesta +=
        "Content-Type: text/html; charset=UTF-8\r\n";

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
// Procesar petición
// ------------------------------------------------

void procesarPeticion(String peticion)
{
    Serial.println();
    Serial.println("Peticion recibida:");
    Serial.println(peticion);


    int inicioIPD =
        peticion.indexOf("+IPD,");

    if (inicioIPD == -1)
    {
        return;
    }


    int posicionComa =
        peticion.indexOf(
            ',',
            inicioIPD + 5
        );

    if (posicionComa == -1)
    {
        return;
    }


    int conexion =
        peticion.substring(
            inicioIPD + 5,
            posicionComa
        ).toInt();


    if (
        peticion.indexOf(
            "GET /led/on"
        ) >= 0
    )
    {
        digitalWrite(
            LED,
            HIGH
        );

        estadoLED = true;

        Serial.println(
            "LED ENCENDIDO"
        );
    }


    if (
        peticion.indexOf(
            "GET /led/off"
        ) >= 0
    )
    {
        digitalWrite(
            LED,
            LOW
        );

        estadoLED = false;

        Serial.println(
            "LED APAGADO"
        );
    }


    enviarPagina(conexion);
}


// ------------------------------------------------
// Configurar ESP8266
// ------------------------------------------------

void configurarESP()
{
    Serial.println();
    Serial.println(
        "Configurando ESP8266..."
    );
    Serial.println();


    enviarAT(
        "AT",
        1000
    );


    enviarAT(
        "AT+CWMODE=1",
        1000
    );


    String conexionWiFi =
        "AT+CWJAP=\"" +
        String(SSID) +
        "\",\"" +
        String(PASSWORD) +
        "\"";


    enviarAT(
        conexionWiFi,
        8000
    );


    enviarAT(
        "AT+CIPMUX=1",
        1000
    );


    enviarAT(
        "AT+CIPSERVER=1,80",
        1000
    );


    enviarAT(
        "AT+CIFSR",
        1000
    );


    Serial.println();
    Serial.println(
        "Servidor preparado."
    );
}


// ------------------------------------------------
// SETUP
// ------------------------------------------------

void setup()
{
    Serial.begin(9600);

    Serial1.begin(9600);


    pinMode(
        LED,
        OUTPUT
    );


    digitalWrite(
        LED,
        LOW
    );


    delay(2000);


    Serial.println();
    Serial.println(
        "=============================="
    );
    Serial.println(
        " MONITORIZACION WEB"
    );
    Serial.println(
        "=============================="
    );


    configurarESP();
}


// ------------------------------------------------
// LOOP
// ------------------------------------------------

void loop()
{
    if (Serial1.available())
    {
        String datos =
            Serial1.readString();

        procesarPeticion(datos);
    }
}
```

---

# 11. Primera prueba

Antes de cargar el programa sustituimos:

```cpp
const char* SSID = "NOMBRE_WIFI";
const char* PASSWORD = "CONTRASENA_WIFI";
```

por nuestras credenciales reales.

Compilamos:

```text
PlatformIO → Build
```

y cargamos:

```text
PlatformIO → Upload
```

Abrimos el monitor serie a:

```text
9600 baudios
```

---

# 12. Comprobar la dirección IP

Durante la inicialización Arduino ejecutará:

```text
AT+CIFSR
```

Debemos localizar:

```text
+CIFSR:STAIP,"192.168.1.xxx"
```

Por ejemplo:

```text
+CIFSR:STAIP,"192.168.1.37"
```

Abrimos:

```text
http://192.168.1.37
```

desde un dispositivo conectado a la misma red.

---

# 13. Comprobar el sensor

La página debe mostrar:

```text
Sensor analógico A0

Valor ADC:

537

Voltaje:

2.62 V
```

Giramos el potenciómetro.

El valor de la página todavía no cambia automáticamente.

Pulsamos:

```text
ACTUALIZAR
```

La página vuelve a solicitar:

```text
/
```

Arduino realiza otra lectura:

```cpp
analogRead(SENSOR);
```

y genera una página nueva.

---

# 14. ¿Por qué cambia el valor?

Cada vez que el navegador solicita una página se ejecuta:

```cpp
enviarPagina(conexion);
```

Dentro de esa función tenemos:

```cpp
int valorSensor = analogRead(SENSOR);
```

Por tanto:

```text
petición HTTP
      │
      ▼
leer sensor
      │
      ▼
generar HTML
      │
      ▼
enviar HTML
```

El dato mostrado no está almacenado previamente.

Es una lectura realizada en ese momento.

---

# 15. Controlar el LED y observar el sensor

Nuestra página contiene ahora dos funciones independientes.

## Control

```text
ENCENDER
APAGAR
```

actúan sobre:

```text
D8
```

## Monitorización

```text
Valor ADC
Voltaje
```

proceden de:

```text
A0
```

Podemos modificar el potenciómetro y simultáneamente controlar el LED.

---

# 16. ¿Qué significa monitorizar?

Monitorizar significa observar el estado o las medidas de un sistema.

Ejemplos:

```text
Temperatura
Humedad
Distancia
Luz
Presión
Velocidad
Nivel de agua
Consumo
```

Nuestro potenciómetro representa de momento un sensor genérico.

Más adelante podremos sustituir:

```cpp
analogRead(A0);
```

por la lectura de cualquier sensor real.

---

# 17. Separar medida y unidad

En nuestro ejemplo mostramos:

```text
Valor ADC: 537
```

y:

```text
Voltaje: 2.62 V
```

Este concepto será importante cuando enviemos datos a una base de datos.

Un sistema de monitorización debe conocer:

```text
variable
+
valor
+
unidad
```

Por ejemplo:

```text
temperatura = 24.6 °C
```

o:

```text
distancia = 37 cm
```

---

# 18. Práctica 1 — Potenciómetro

Comprueba:

1. Que la página web funciona.
2. Que el LED puede encenderse.
3. Que el LED puede apagarse.
4. Que aparece el valor ADC.
5. Que aparece el voltaje.
6. Que el valor cambia al girar el potenciómetro.
7. Que el botón `ACTUALIZAR` muestra una lectura nueva.

No continúes hasta que funcione correctamente.

---

# 19. Práctica 2 — Tres zonas del sensor

Divide el rango del potenciómetro en tres zonas:

```text
0 - 340
341 - 680
681 - 1023
```

La página debe mostrar además:

```text
Nivel: BAJO
```

o:

```text
Nivel: MEDIO
```

o:

```text
Nivel: ALTO
```

Puedes utilizar:

```cpp
if
```

```cpp
else if
```

```cpp
else
```

---

# 20. Práctica 3 — Control automático del LED

Modifica el programa para que el LED se encienda automáticamente cuando:

```text
valorSensor > 700
```

y se apague cuando:

```text
valorSensor <= 700
```

La arquitectura será:

```text
SENSOR
   │
   ▼
ARDUINO
   │
   ├────────► LED
   │
   └────────► PÁGINA WEB
```

Ahora el sistema empieza a tomar decisiones por sí mismo.

---

# 21. Práctica 4 — Cambiar de sensor

Sustituye el potenciómetro por otro sensor analógico del kit.

Por ejemplo:

```text
LDR
```

o:

```text
termistor
```

si ya conoces su funcionamiento.

Debes modificar:

* El circuito.
* El código.
* El título de la página.
* La unidad mostrada.
* La explicación de la lectura.

---

# 22. Práctica 5 — Mostrar dos sensores

Como ampliación, conecta dos entradas analógicas:

```text
A0 → sensor 1

A1 → sensor 2
```

La página podría mostrar:

```text
SENSOR 1

Valor: 537


SENSOR 2

Valor: 812
```

Esto nos acerca mucho más a un sistema real de adquisición de datos.

---

# 23. Actualización automática de la página

Hasta ahora el usuario pulsa:

```text
ACTUALIZAR
```

Podemos pedir al navegador que actualice automáticamente la página.

Añade dentro de `<head>`:

```html
<meta http-equiv='refresh' content='5'>
```

Esto significa:

> Volver a solicitar la página cada 5 segundos.

Podemos construirlo en Arduino mediante:

```cpp
html +=
    "<meta http-equiv='refresh' content='5'>";
```

La página se actualizará automáticamente cada cinco segundos.

---

# 24. ¿Es esta la mejor forma de actualizar datos?

No.

Actualizar toda la página continuamente es sencillo y didáctico, pero no es la forma más eficiente.

En sistemas web más avanzados podemos utilizar:

```text
JavaScript
AJAX
Fetch API
WebSocket
```

para actualizar únicamente los datos necesarios.

Pero para nuestro nivel actual, la actualización completa es suficiente.

---

# 25. Problemas frecuentes

## El valor siempre es 0

Comprueba:

```text
Potenciómetro exterior → 5 V

Potenciómetro centro → A0

Potenciómetro exterior → GND
```

---

## El valor siempre es 1023

Comprueba que:

```text
A0
```

no esté conectado directamente a 5 V.

---

## El valor cambia de forma extraña

Comprueba:

* Las conexiones.
* Los cables.
* La protoboard.
* Que el terminal central esté realmente conectado a A0.

---

## La página deja de responder

El programa actual utiliza:

```cpp
delay()
```

y:

```cpp
Serial1.readString()
```

para simplificar la práctica.

No es todavía un servidor profesional.

Más adelante mejoraremos la gestión de comunicaciones.

---

# 26. Arquitectura del sistema

Nuestro sistema completo es ahora:

```text
                    USUARIO
                       │
                       ▼
                  NAVEGADOR
                       │
                       │ HTTP
                       ▼
                    Wi-Fi
                       │
                       ▼
                   ESP8266
                       │
                       │ UART
                       ▼
                ARDUINO MEGA
                  │       │
                  │       │
                  ▼       ▼
                 LED    SENSOR
```

La comunicación es bidireccional.

---

# 27. Concepto de telemetría

Cuando un dispositivo envía medidas a través de una red hablamos frecuentemente de:

```text
TELEMETRÍA
```

Nuestro sistema ya es capaz de producir telemetría sencilla:

```text
Sensor
   │
   ▼
Arduino
   │
   ▼
Wi-Fi
   │
   ▼
Navegador
```

Actualmente los datos solamente se muestran.

Todavía no los almacenamos.

---

# 28. El siguiente problema

Supongamos que nuestro sensor genera:

```text
10:00 → 2.31 V

10:01 → 2.35 V

10:02 → 2.42 V

10:03 → 2.39 V
```

Nuestra página solamente muestra el valor actual.

Cuando aparece:

```text
2.39 V
```

hemos perdido los valores anteriores.

Para poder estudiar cómo cambia una magnitud con el tiempo necesitamos almacenarla.

Necesitamos algo parecido a:

```text
FECHA/HORA        VALOR

10:00             2.31
10:01             2.35
10:02             2.42
10:03             2.39
```

Aquí aparece nuestro siguiente componente:

```text
InfluxDB
```

---

# 29. Camino hacia InfluxDB y Grafana

El proyecto final irá evolucionando hacia:

```text
SENSOR
   │
   ▼
ARDUINO MEGA
   │
   ▼
ESP8266
   │
   ▼
Wi-Fi
   │
   ▼
INFLUXDB
   │
   ▼
GRAFANA
```

InfluxDB almacenará las medidas.

Grafana permitirá visualizar:

```text
gráficas
paneles
indicadores
histórico
```

---

# 30. Lo que hemos aprendido

En esta lección hemos unido:

```text
analogRead()
```

con:

```text
HTML
```

y:

```text
HTTP
```

a través del:

```text
ESP8266
```

Nuestro proyecto ya puede:

```text
LEER
+
PROCESAR
+
CONTROLAR
+
COMUNICAR
```

datos a través de una red.

---

# 31. Preparación para la siguiente lección

En la siguiente lección comenzaremos a separar la página web del almacenamiento de datos.

El objetivo será entender cómo podemos enviar una medida utilizando una petición de red.

Pasaremos de:

```text
SENSOR
   │
   ▼
PÁGINA WEB
```

a:

```text
SENSOR
   │
   ▼
SERVIDOR
   │
   ▼
BASE DE DATOS
```

Este será el primer paso para conectar nuestro proyecto con **InfluxDB** y posteriormente crear un dashboard con **Grafana**.
