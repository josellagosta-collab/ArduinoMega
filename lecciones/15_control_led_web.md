# Lección 15 — Control de un LED desde una página web

## 1. Objetivos

En la lección anterior creamos manualmente un servidor web utilizando el ESP8266.

Ahora vamos a automatizar el proceso desde el Arduino Mega 2560.

Al finalizar esta práctica seremos capaces de:

* Inicializar el ESP8266 automáticamente desde Arduino.
* Crear un servidor web en el puerto 80.
* Detectar peticiones HTTP procedentes de un navegador.
* Interpretar diferentes direcciones URL.
* Encender y apagar un LED desde una página web.
* Generar una página HTML desde Arduino.
* Comprender el funcionamiento básico de un sistema IoT.

El resultado será:

```text
TELÉFONO / ORDENADOR
        │
        │ Wi-Fi
        ▼
     ROUTER
        │
        ▼
     ESP8266
        │
        │ UART
        ▼
  ARDUINO MEGA
        │
        ▼
       LED
```

---

## 2. Material necesario

Necesitamos:

* Arduino Mega 2560 R3.
* ESP8266 ESP-01.
* Fuente regulada de 3,3 V para el ESP8266.
* Protoboard.
* LED.
* Resistencia de 220 Ω.
* Resistencia de 1 kΩ.
* Resistencia de 2 kΩ.
* Cables Dupont.
* Cable USB.
* Ordenador con Visual Studio Code y PlatformIO.
* Red Wi-Fi de 2,4 GHz.

---

# 3. Conexión del ESP8266

Conservamos exactamente el montaje que ya hemos comprobado.

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

La comunicación con nuestro ESP8266 funciona a:

```text
9600 baudios
```

Por tanto utilizaremos:

```cpp
Serial1.begin(9600);
```

---

# 4. Conexión del LED

Utilizaremos un LED externo conectado al pin digital `8`.

La conexión será:

```text
Arduino Mega

D8
 │
 ▼
220 Ω
 │
 ▼
LED
 │
 ▼
GND
```

Recordamos que:

* La pata larga del LED es normalmente el ánodo.
* La pata corta es el cátodo.
* Utilizamos una resistencia para limitar la corriente.

---

# 5. ¿Qué vamos a construir?

Queremos que al escribir la dirección IP del ESP8266 en un navegador aparezca una página similar a:

```text
+-----------------------------------+
|                                   |
|        CONTROL DEL LED            |
|                                   |
|        Estado: APAGADO            |
|                                   |
|     [ ENCENDER ]  [ APAGAR ]      |
|                                   |
+-----------------------------------+
```

Al pulsar:

```text
ENCENDER
```

el navegador solicitará:

```text
/led/on
```

Al pulsar:

```text
APAGAR
```

solicitará:

```text
/led/off
```

Arduino analizará esas peticiones y actuará sobre el pin D8.

---

# 6. Funcionamiento completo

El proceso será:

```text
1. Usuario pulsa ENCENDER
             │
             ▼
2. Navegador solicita /led/on
             │
             ▼
3. ESP8266 recibe la petición
             │
             ▼
4. ESP8266 la envía al Mega por UART
             │
             ▼
5. Mega detecta GET /led/on
             │
             ▼
6. digitalWrite(LED, HIGH)
             │
             ▼
7. LED encendido
             │
             ▼
8. Mega genera página HTML
             │
             ▼
9. ESP8266 la envía al navegador
```

Aquí aparece por primera vez un concepto fundamental de IoT:

```text
INTERFAZ → RED → PROCESAMIENTO → ACTUADOR
```

---

# 7. Las peticiones HTTP

Cuando pulsamos el botón de encendido, el navegador enviará algo parecido a:

```text
GET /led/on HTTP/1.1
```

Cuando pulsamos apagar:

```text
GET /led/off HTTP/1.1
```

Y cuando simplemente accedemos a la dirección IP:

```text
GET / HTTP/1.1
```

Arduino solamente necesita buscar determinadas partes de esas cadenas.

Por ejemplo:

```cpp
peticion.indexOf("GET /led/on") >= 0
```

significa:

> Buscar `GET /led/on` dentro de la petición recibida.

---

# 8. Preparar las credenciales Wi-Fi

Nuestro programa necesitará conocer el nombre y la contraseña de la red.

Utilizaremos:

```cpp
const char* SSID = "NOMBRE_WIFI";
const char* PASSWORD = "CONTRASENA_WIFI";
```

Debemos sustituirlos por los datos reales.

Por ejemplo:

```cpp
const char* SSID = "AulaArduino";
const char* PASSWORD = "clave1234";
```

## Importante

No debemos subir contraseñas reales a GitHub.

Antes de realizar:

```text
git add .
git commit
git push
```

debemos sustituirlas nuevamente por:

```cpp
"NOMBRE_WIFI"
```

y:

```cpp
"CONTRASENA_WIFI"
```

---

# 9. Primer programa completo

Crea:

```text
ejemplos/15_control_led_web/main.cpp
```

Utilizaremos inicialmente este programa:

```cpp
#include <Arduino.h>

const int LED = 8;

const char* SSID = "NOMBRE_WIFI";
const char* PASSWORD = "CONTRASENA_WIFI";

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
```

---

# 10. Primera ejecución

Antes de cargar el programa debemos introducir temporalmente nuestras credenciales:

```cpp
const char* SSID = "MI_RED";
const char* PASSWORD = "MI_CONTRASENA";
```

Compilamos:

```text
PlatformIO → Build
```

Después:

```text
PlatformIO → Upload
```

Abrimos:

```text
PlatformIO → Serial Monitor
```

a:

```text
9600 baudios
```

---

# 11. Inicialización automática

Ahora ya no tenemos que escribir manualmente todos los comandos AT.

Arduino ejecutará automáticamente:

```text
AT
```

después:

```text
AT+CWMODE=1
```

después:

```text
AT+CWJAP="SSID","PASSWORD"
```

después:

```text
AT+CIPMUX=1
```

y finalmente:

```text
AT+CIPSERVER=1,80
```

También ejecutará:

```text
AT+CIFSR
```

para mostrarnos la dirección IP.

---

# 12. Localizar la dirección IP

En el monitor serie debemos localizar una respuesta similar a:

```text
+CIFSR:STAIP,"192.168.1.37"
```

Nuestra dirección será diferente.

Supongamos:

```text
192.168.1.37
```

Desde un ordenador o teléfono conectado a la misma red escribimos en el navegador:

```text
http://192.168.1.37
```

---

# 13. Primera página web

Deberíamos visualizar aproximadamente:

```text
Arduino Mega 2560

Control del LED

Estado: APAGADO


[ ENCENDER ]     [ APAGAR ]
```

El LED inicialmente estará apagado porque en `setup()` ejecutamos:

```cpp
digitalWrite(LED, LOW);
```

---

# 14. Encender el LED

Pulsamos:

```text
ENCENDER
```

El navegador solicitará:

```text
/led/on
```

Arduino recibirá una petición que contendrá:

```text
GET /led/on HTTP/1.1
```

Nuestro programa detectará:

```cpp
if (peticion.indexOf("GET /led/on") >= 0)
```

y ejecutará:

```cpp
digitalWrite(LED, HIGH);
```

También guardará:

```cpp
estadoLED = true;
```

El LED debe encenderse.

---

# 15. Apagar el LED

Ahora pulsamos:

```text
APAGAR
```

El navegador solicitará:

```text
/led/off
```

Arduino detectará:

```cpp
if (peticion.indexOf("GET /led/off") >= 0)
```

y ejecutará:

```cpp
digitalWrite(LED, LOW);
```

Además:

```cpp
estadoLED = false;
```

El LED debe apagarse.

---

# 16. ¿Para qué necesitamos `estadoLED`?

Tenemos esta variable:

```cpp
bool estadoLED = false;
```

Puede contener:

```text
false → LED apagado

true → LED encendido
```

Cuando encendemos:

```cpp
estadoLED = true;
```

Cuando apagamos:

```cpp
estadoLED = false;
```

Gracias a esto la página puede mostrar:

```text
Estado: ENCENDIDO
```

o:

```text
Estado: APAGADO
```

---

# 17. Cómo funcionan los botones HTML

El botón de encendido está asociado a:

```html
<a href='/led/on'>
```

Por tanto, al pulsarlo el navegador solicita:

```text
http://IP_DEL_ESP/led/on
```

El botón de apagado utiliza:

```html
<a href='/led/off'>
```

y genera:

```text
http://IP_DEL_ESP/led/off
```

No necesitamos JavaScript.

Estamos utilizando únicamente:

```text
HTML
+
HTTP
```

---

# 18. Generación automática de la página

La función:

```cpp
void enviarPagina(int conexion)
```

construye una página HTML dentro de una variable:

```cpp
String html;
```

Posteriormente construimos la respuesta HTTP:

```cpp
String respuesta;
```

que contiene:

```text
HTTP/1.1 200 OK
Content-Type: text/html
Connection: close

PÁGINA HTML
```

---

# 19. Calcular automáticamente la longitud

En la lección anterior tuvimos que contar manualmente los caracteres.

Ahora Arduino lo hace:

```cpp
respuesta.length()
```

Por ejemplo, si la respuesta tiene 487 bytes, Arduino generará automáticamente:

```text
AT+CIPSEND=0,487
```

Esto permite enviar páginas mucho mayores.

---

# 20. Identificador de conexión

Recordemos que podemos recibir:

```text
+IPD,0,...
```

o:

```text
+IPD,1,...
```

El número representa la conexión utilizada por el navegador.

Nuestro programa extrae automáticamente ese número:

```cpp
int conexion = peticion.substring(
    inicioIPD + 5,
    posicionComa
).toInt();
```

Después puede utilizarlo en:

```text
AT+CIPSEND
```

y:

```text
AT+CIPCLOSE
```

---

# 21. Cierre de la conexión

Después de enviar la página ejecutamos:

```text
AT+CIPCLOSE=ID
```

Por ejemplo:

```text
AT+CIPCLOSE=0
```

El navegador puede abrir posteriormente una nueva conexión cuando pulse otro botón.

---

# 22. Monitorización del sistema

Mientras utilizamos la página web debemos observar el monitor serie.

Al pulsar ENCENDER podremos ver algo parecido a:

```text
Peticion recibida:

+IPD,0,...:GET /led/on HTTP/1.1
...

LED ENCENDIDO
```

Al pulsar APAGAR:

```text
Peticion recibida:

+IPD,0,...:GET /led/off HTTP/1.1
...

LED APAGADO
```

Esto nos permite observar simultáneamente:

```text
WEB
 │
 ▼
HTTP
 │
 ▼
ESP8266
 │
 ▼
UART
 │
 ▼
ARDUINO
 │
 ▼
LED
```

---

# 23. Práctica 1 — Control básico

Comprueba:

1. Que el ESP8266 se conecta automáticamente al Wi-Fi.
2. Que obtiene una dirección IP.
3. Que puedes abrir la página desde el navegador.
4. Que aparece el botón `ENCENDER`.
5. Que aparece el botón `APAGAR`.
6. Que `ENCENDER` enciende físicamente el LED.
7. Que `APAGAR` apaga físicamente el LED.
8. Que la página muestra correctamente el estado.

No continúes hasta que los ocho puntos funcionen.

---

# 24. Práctica 2 — Control desde un teléfono

Conecta un teléfono móvil a la misma red Wi-Fi.

Abre el navegador.

Introduce:

```text
http://IP_DEL_ESP8266
```

Comprueba que puedes controlar el LED desde el teléfono.

Ahora tenemos literalmente un dispositivo físico controlado mediante Wi-Fi.

---

# 25. Práctica 3 — Cambiar el LED de pin

Modifica:

```cpp
const int LED = 8;
```

para utilizar otro pin digital.

Por ejemplo:

```cpp
const int LED = 7;
```

Modifica físicamente el circuito para que coincida con el programa.

Comprueba nuevamente el funcionamiento.

---

# 26. Práctica 4 — Añadir un segundo LED

Añade otro LED al circuito.

Por ejemplo:

```text
LED 1 → D8

LED 2 → D9
```

Crea cuatro acciones:

```text
/led1/on

/led1/off

/led2/on

/led2/off
```

La página podría mostrar:

```text
CONTROL DE SALIDAS


LED 1

[ ENCENDER ] [ APAGAR ]


LED 2

[ ENCENDER ] [ APAGAR ]
```

Esta ampliación debe ser realizada por el alumno modificando el programa original.

---

# 27. Práctica 5 — Utilizar el LED RGB

Podemos recuperar el LED RGB utilizado en la Lección 8.

Recordemos:

```text
Rojo  → D9

Verde → D10

Azul  → D11
```

Podríamos crear:

```text
/rojo

/verde

/azul

/apagar
```

y una página:

```text
CONTROL RGB


[ ROJO ]

[ VERDE ]

[ AZUL ]

[ APAGAR ]
```

Esta práctica permite integrar conocimientos de:

```text
Lección 8
+
Lección 11
+
Lección 12
+
Lección 13
+
Lección 14
+
Lección 15
```

---

# 28. Problemas frecuentes

## El ESP8266 no responde

Recordemos que nuestros módulos han sido comprobados a:

```cpp
Serial1.begin(9600);
```

No debemos cambiar arbitrariamente esta velocidad.

---

## El ESP8266 no conecta al Wi-Fi

Comprobar:

* SSID.
* Contraseña.
* Red de 2,4 GHz.
* Cobertura.
* Alimentación estable de 3,3 V.

---

## La página no aparece

Comprobar la IP:

```text
AT+CIFSR
```

El dispositivo desde el que accedemos debe poder comunicarse con el ESP8266.

---

## La página aparece pero el LED no funciona

Comprobar:

```text
D8
 │
220 Ω
 │
LED
 │
GND
```

También debemos observar el monitor serie para comprobar si aparece:

```text
LED ENCENDIDO
```

o:

```text
LED APAGADO
```

---

## El navegador se queda esperando

El manejo de comandos AT mediante retardos es suficiente para esta primera práctica, pero no es todavía una implementación robusta.

Estamos utilizando este sistema para comprender el funcionamiento.

Más adelante podremos mejorar:

* Gestión de tiempos.
* Recepción de respuestas AT.
* Detección de `OK`.
* Detección de `>`.
* Tratamiento de errores.
* Estados de comunicación.

---

# 29. Arquitectura conseguida

Nuestro proyecto ha evolucionado considerablemente.

Inicialmente teníamos:

```text
Arduino → LED
```

Después:

```text
Potenciómetro → Arduino → LED
```

Ahora tenemos:

```text
┌─────────────────┐
│     USUARIO     │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│    NAVEGADOR    │
└────────┬────────┘
         │
         │ HTTP
         ▼
┌─────────────────┐
│      Wi-Fi      │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│     ESP8266     │
└────────┬────────┘
         │
         │ UART
         ▼
┌─────────────────┐
│  ARDUINO MEGA   │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│       LED       │
└─────────────────┘
```

El usuario ya puede controlar físicamente un actuador desde otro dispositivo conectado a la red.

Esto constituye un **sistema IoT básico**.

---

# 30. Lo que hemos aprendido

En esta lección hemos utilizado conjuntamente:

```text
digitalWrite()
```

para controlar una salida,

```text
Serial1
```

para comunicarnos con el ESP8266,

```text
Wi-Fi
```

para conectar nuestro proyecto a la red,

```text
TCP
```

para transportar información,

```text
HTTP
```

para realizar las peticiones,

y:

```text
HTML
```

para crear la interfaz del usuario.

Por tanto:

```text
Arduino
+
ESP8266
+
Wi-Fi
+
TCP/IP
+
HTTP
+
HTML
```

trabajan conjuntamente.

---

# 31. Preparación para la siguiente lección

Hasta ahora la comunicación principal ha seguido esta dirección:

```text
USUARIO
   │
   ▼
PÁGINA WEB
   │
   ▼
ARDUINO
   │
   ▼
ACTUADOR
```

Pero un sistema IoT también debe ser capaz de realizar el recorrido contrario:

```text
SENSOR
   │
   ▼
ARDUINO
   │
   ▼
ESP8266
   │
   ▼
RED
   │
   ▼
USUARIO
```

En la siguiente lección incorporaremos un **sensor** y mostraremos su valor en nuestra página web.

Pasaremos de:

```text
CONTROL REMOTO
```

a:

```text
CONTROL
+
MONITORIZACIÓN
```

Este será el siguiente paso hacia el objetivo final de enviar datos a **InfluxDB** y representarlos posteriormente mediante **Grafana**.
