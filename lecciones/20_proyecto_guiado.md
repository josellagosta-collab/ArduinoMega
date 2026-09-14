# Lección 20 — Proyecto IoT: control y monitorización

## 1. Introducción

En las lecciones anteriores hemos aprendido a trabajar por separado con los elementos principales de nuestro sistema.

Ya somos capaces de:

* Programar el **Arduino Mega 2560 R3**.
* Leer sensores.
* Controlar actuadores.
* Comunicar Arduino con un **ESP8266** mediante `Serial1`.
* Conectar el ESP8266 a una red Wi-Fi.
* Utilizar comandos AT.
* Crear comunicaciones mediante HTTP.
* Enviar medidas a **InfluxDB**.
* Visualizar los datos mediante **Grafana**.

En esta lección vamos a integrar estos conocimientos en un único proyecto.

Nuestro sistema tendrá dos funciones simultáneas:

```text
CONTROL

Navegador
    │
    │ Wi-Fi
    ▼
 ESP8266
    │
    ▼
Arduino Mega
    │
    ▼
   LED
```

y:

```text
MONITORIZACIÓN

Potenciómetro
      │
      ▼
Arduino Mega
      │
      ▼
 ESP8266
      │
      │ HTTP
      ▼
  InfluxDB
      │
      ▼
   Grafana
      │
      ▼
 Dashboard
```

---

# 2. Objetivos

Al finalizar esta lección seremos capaces de:

* Integrar diferentes tecnologías utilizadas durante el curso.
* Leer un sensor desde Arduino.
* Controlar un actuador.
* Utilizar el ESP8266 para comunicar Arduino con la red.
* Enviar medidas a InfluxDB.
* Visualizar las medidas mediante Grafana.
* Comprender la diferencia entre control y monitorización.
* Diseñar la arquitectura básica de un sistema IoT.

---

# 3. El proyecto

Construiremos un pequeño sistema IoT formado por:

```text
ENTRADA
Potenciómetro

SALIDA
LED

CONTROL
Página web

COMUNICACIÓN
ESP8266

BASE DE DATOS
InfluxDB

VISUALIZACIÓN
Grafana
```

El potenciómetro representará inicialmente nuestro sensor.

El LED representará un actuador.

Posteriormente podremos sustituirlos por otros componentes del kit.

---

# 4. Arquitectura completa

Nuestro sistema tendrá la siguiente estructura:

```text
                         RED Wi-Fi
                             │
              ┌──────────────┴──────────────┐
              │                             │
              ▼                             ▼
         NAVEGADOR                       WINDOWS 11
              │                             │
              │                             ├── InfluxDB
              │                             │
              │                             └── Grafana
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
         LED   POTENCIÓMETRO
```

Tenemos, por tanto, tres partes:

```text
CONTROL
    +
ADQUISICIÓN
    +
MONITORIZACIÓN
```

---

# 5. Material necesario

Utilizaremos:

* Arduino Mega 2560 R3.
* ESP8266.
* Protoboard.
* Potenciómetro.
* LED.
* Resistencia de aproximadamente `220 Ω`.
* Resistencias utilizadas para adaptar el nivel de tensión hacia el RX del ESP8266.
* Cables Dupont.
* Ordenador Windows 11.
* InfluxDB.
* Grafana.

---

# 6. Conexión del potenciómetro

Conectamos:

```text
Potenciómetro          Arduino Mega

Extremo 1  ─────────── 5 V

Central    ─────────── A0

Extremo 2  ─────────── GND
```

Arduino realizará:

```cpp
analogRead(A0);
```

y obtendrá valores entre:

```text
0 y 1023
```

---

# 7. Conexión del LED

Utilizaremos, por ejemplo:

```text
D7
```

La conexión será:

```text
Arduino D7
    │
    ▼
 resistencia
    │
    ▼
   LED
    │
    ▼
   GND
```

La resistencia limitará la corriente que circula por el LED.

---

# 8. Conexión del ESP8266

Mantendremos el montaje utilizado en las lecciones anteriores.

```text
ARDUINO MEGA                   ESP8266

TX1 D18 ── divisor tensión ──► RX

RX1 D19 ◄──────────────────── TX

GND ───────────────────────── GND
```

El divisor de tensión protege la entrada RX del ESP8266.

---

# 9. Comunicación serie

Nuestro ESP8266 ya ha sido probado experimentalmente.

Utilizaremos:

```cpp
Serial1.begin(9600);
```

Por tanto:

```text
USB / PC
Serial
9600 baudios
```

y:

```text
Mega ↔ ESP8266
Serial1
9600 baudios
```

---

# 10. Dos trabajos para el ESP8266

Hasta ahora hemos utilizado el ESP8266 para diferentes funciones.

Como servidor:

```text
Navegador
    │
    ▼
ESP8266
```

Como cliente:

```text
ESP8266
    │
    ▼
InfluxDB
```

Ahora queremos combinar ambos conceptos.

Esto introduce un problema:

> El ESP8266 debe atender órdenes y también iniciar conexiones hacia InfluxDB.

Por tanto, debemos organizar correctamente el funcionamiento del programa.

---

# 11. Estrategia de esta primera integración

Para no complicar innecesariamente el proyecto, utilizaremos una solución sencilla.

El Arduino realizará periódicamente:

```text
leer sensor
     ↓
enviar medida
     ↓
comprobar órdenes
     ↓
esperar
     ↓
repetir
```

No utilizaremos tareas simultáneas ni sistemas operativos.

Nuestro Arduino ejecutará las operaciones secuencialmente.

---

# 12. Control del LED

Definimos:

```cpp
const int LED = 7;
```

En `setup()`:

```cpp
pinMode(LED, OUTPUT);

digitalWrite(LED, LOW);
```

Para encender:

```cpp
digitalWrite(LED, HIGH);
```

Para apagar:

```cpp
digitalWrite(LED, LOW);
```

---

# 13. Lectura del sensor

Definimos:

```cpp
const int SENSOR = A0;
```

La lectura será:

```cpp
int valor = analogRead(SENSOR);
```

Calculamos también el voltaje:

```cpp
float voltaje =
    valor * 5.0 / 1023.0;
```

Por ejemplo:

```text
valor = 512
```

producirá aproximadamente:

```text
voltaje = 2.50 V
```

---

# 14. Datos para InfluxDB

Continuaremos utilizando:

```text
Organization:
ArduinoCurso
```

```text
Bucket:
arduino
```

```text
Measurement:
sensor
```

Enviaremos:

```text
sensor valor=512,voltaje=2.50
```

InfluxDB añadirá la información temporal correspondiente.

---

# 15. Añadir el estado del LED

Podemos mejorar los datos enviados.

Además de:

```text
valor
voltaje
```

podemos almacenar:

```text
led
```

Por ejemplo:

```text
sensor valor=512,voltaje=2.50,led=1
```

significa:

```text
ADC       = 512
Voltaje   = 2.50
LED       = encendido
```

Mientras que:

```text
sensor valor=512,voltaje=2.50,led=0
```

indica que el LED está apagado.

---

# 16. Configuración del programa

Comenzaremos con:

```cpp
#include <Arduino.h>

const int SENSOR = A0;
const int LED = 7;

const char* SSID = "NOMBRE_WIFI";
const char* PASSWORD = "CONTRASENA_WIFI";

const char* IP_INFLUX = "10.113.170.1";

const int PUERTO_INFLUX = 8086;

const char* ORGANIZACION = "ArduinoCurso";
const char* BUCKET = "arduino";

const char* TOKEN = "TU_TOKEN";
```

Cada alumno deberá adaptar:

```text
SSID
PASSWORD
IP_INFLUX
TOKEN
```

a su entorno.

---

# 17. Seguridad

No debemos publicar en GitHub:

```text
contraseña Wi-Fi
```

ni:

```text
token de InfluxDB
```

Antes de subir el programa al repositorio debemos sustituirlos por:

```cpp
const char* PASSWORD = "CONTRASENA_WIFI";
const char* TOKEN = "TU_TOKEN";
```

---

# 18. Envío de comandos AT

Reutilizamos la función:

```cpp
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
```

---

# 19. Conexión Wi-Fi

Utilizaremos:

```cpp
void conectarWiFi()
{
    enviarAT("AT", 1000);

    enviarAT("AT+CWMODE=1", 1000);

    String comandoWiFi =
        "AT+CWJAP=\"" +
        String(SSID) +
        "\",\"" +
        String(PASSWORD) +
        "\"";

    enviarAT(comandoWiFi, 8000);

    enviarAT("AT+CIPSERVER=0", 1000);

    enviarAT("AT+CIPMUX=0", 1000);

    enviarAT("AT+CIFSR", 1000);
}
```

Esta será inicialmente nuestra configuración para el envío a InfluxDB.

---

# 20. Función para enviar los datos

Crearemos:

```cpp
void enviarInflux(int valor, bool estadoLed)
```

La función recibirá:

```text
valor del sensor
+
estado del LED
```

Calcularemos:

```cpp
float voltaje =
    valor * 5.0 / 1023.0;
```

---

# 21. Construir Line Protocol

Crearemos:

```cpp
String datos =
    "sensor valor=" +
    String(valor) +
    ",voltaje=" +
    String(voltaje, 2) +
    ",led=" +
    String(estadoLed ? 1 : 0);
```

Por ejemplo:

```text
sensor valor=627,voltaje=3.06,led=1
```

---

# 22. Construir la petición HTTP

La ruta será:

```cpp
String ruta =
    "/api/v2/write?org=" +
    String(ORGANIZACION) +
    "&bucket=" +
    String(BUCKET) +
    "&precision=s";
```

La petición será:

```text
POST /api/v2/write?... HTTP/1.1
Host: 10.113.170.1:8086
Authorization: Token ...
Content-Type: text/plain
Content-Length: ...

sensor valor=627,voltaje=3.06,led=1
```

---

# 23. Primera fase del proyecto

Antes de integrar el control web comprobaremos:

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
InfluxDB
      │
      ▼
Grafana
```

pero ahora almacenando también:

```text
led
```

---

# 24. Programa de la primera fase

Crea:

```text
ejemplos/20_proyecto_iot/main.cpp
```

con el siguiente programa:

```cpp
#include <Arduino.h>

// ------------------------------------------------
// HARDWARE
// ------------------------------------------------

const int SENSOR = A0;
const int LED = 7;


// ------------------------------------------------
// WIFI
// ------------------------------------------------

const char* SSID = "NOMBRE_WIFI";
const char* PASSWORD = "CONTRASENA_WIFI";


// ------------------------------------------------
// INFLUXDB
// ------------------------------------------------

const char* IP_INFLUX = "10.113.170.1";

const int PUERTO_INFLUX = 8086;

const char* ORGANIZACION = "ArduinoCurso";

const char* BUCKET = "arduino";

const char* TOKEN = "TU_TOKEN";


// ------------------------------------------------
// ESTADO DEL SISTEMA
// ------------------------------------------------

bool estadoLed = false;


// ------------------------------------------------
// MOSTRAR RESPUESTA ESP8266
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
// ENVIAR COMANDO AT
// ------------------------------------------------

void enviarAT(String comando, unsigned long tiempoEspera)
{
    Serial.print(">> ");
    Serial.println(comando);

    Serial1.print(comando);
    Serial1.print("\r\n");

    mostrarRespuestaESP(tiempoEspera);
}


// ------------------------------------------------
// CONECTAR WIFI
// ------------------------------------------------

void conectarWiFi()
{
    Serial.println();
    Serial.println("==============================");
    Serial.println(" CONECTANDO AL WIFI");
    Serial.println("==============================");

    enviarAT("AT", 1000);

    enviarAT("AT+CWMODE=1", 1000);

    String comandoWiFi =
        "AT+CWJAP=\"" +
        String(SSID) +
        "\",\"" +
        String(PASSWORD) +
        "\"";

    enviarAT(comandoWiFi, 8000);

    enviarAT("AT+CIPSERVER=0", 1000);

    enviarAT("AT+CIPMUX=0", 1000);

    enviarAT("AT+CIFSR", 1000);
}


// ------------------------------------------------
// ENVIAR DATOS A INFLUXDB
// ------------------------------------------------

void enviarInflux(int valor, bool led)
{
    float voltaje =
        valor * 5.0 / 1023.0;


    String datos =
        "sensor valor=" +
        String(valor) +
        ",voltaje=" +
        String(voltaje, 2) +
        ",led=" +
        String(led ? 1 : 0);


    Serial.println();
    Serial.println("------------------------------");
    Serial.println("Datos para InfluxDB:");
    Serial.println(datos);


    String ruta =
        "/api/v2/write?org=" +
        String(ORGANIZACION) +
        "&bucket=" +
        String(BUCKET) +
        "&precision=s";


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


    String comandoConexion =
        "AT+CIPSTART=\"TCP\",\"" +
        String(IP_INFLUX) +
        "\"," +
        String(PUERTO_INFLUX);


    Serial.println("Conectando con InfluxDB...");

    enviarAT(
        comandoConexion,
        3000
    );


    Serial1.print("AT+CIPSEND=");
    Serial1.print(peticion.length());
    Serial1.print("\r\n");


    mostrarRespuestaESP(1500);


    Serial1.print(peticion);


    Serial.println();
    Serial.println("Respuesta InfluxDB:");

    mostrarRespuestaESP(4000);


    Serial.println();
    Serial.println("Envio terminado.");
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
    Serial.println(" LECCION 20 - PROYECTO IoT");
    Serial.println("==============================");


    conectarWiFi();
}


// ------------------------------------------------
// LOOP
// ------------------------------------------------

void loop()
{
    int valor =
        analogRead(SENSOR);


    Serial.println();
    Serial.print("Sensor: ");
    Serial.println(valor);


    Serial.print("LED: ");

    if (estadoLed)
    {
        Serial.println("ENCENDIDO");
    }
    else
    {
        Serial.println("APAGADO");
    }


    enviarInflux(
        valor,
        estadoLed
    );


    delay(10000);
}
```

---

# 25. Primera comprobación

Compila:

```text
PlatformIO → Build
```

Carga:

```text
PlatformIO → Upload
```

Abre:

```text
PlatformIO → Serial Monitor
```

a:

```text
9600 baudios
```

Debemos obtener algo parecido a:

```text
Sensor: 527
LED: APAGADO

Datos para InfluxDB:
sensor valor=527,voltaje=2.58,led=0
```

y posteriormente:

```text
SEND OK
```

y:

```text
HTTP/1.1 204 No Content
```

---

# 26. Comprobar InfluxDB

En Data Explorer tendremos ahora tres fields:

```text
valor
voltaje
led
```

Seleccionamos:

```text
led
```

Debería tener inicialmente:

```text
0
```

---

# 27. Prueba manual del actuador

Antes de integrar la página web comprobaremos el LED.

Modificamos temporalmente:

```cpp
bool estadoLed = false;
```

por:

```cpp
bool estadoLed = true;
```

y en `setup()` utilizamos temporalmente:

```cpp
digitalWrite(
    LED,
    estadoLed ? HIGH : LOW
);
```

El LED deberá encenderse.

InfluxDB deberá recibir:

```text
led=1
```

Después de comprobarlo recuperamos:

```cpp
bool estadoLed = false;
```

---

# 28. El problema del control web

Ahora debemos resolver una cuestión importante.

Para recibir conexiones del navegador utilizábamos:

```text
CIPSERVER
```

y:

```text
CIPMUX=1
```

Pero para nuestras conexiones sencillas hacia InfluxDB hemos estado utilizando:

```text
CIPMUX=0
```

Por tanto, no podemos limitar la integración a copiar y pegar los dos programas anteriores.

Debemos diseñar correctamente el funcionamiento.

---

# 29. Solución didáctica

En esta lección utilizaremos dos fases.

### Fase A

```text
Sensor
   ↓
Arduino
   ↓
InfluxDB
   ↓
Grafana
```

### Fase B

```text
Navegador
   ↓
ESP8266
   ↓
Arduino
   ↓
LED
```

Después estudiaremos cómo integrar ambas funciones.

Esto permite diagnosticar los problemas por separado antes de construir el sistema completo.

---

# 30. Activar temporalmente el servidor web

Para trabajar con el control utilizaremos:

```text
AT+CIPMUX=1
```

y:

```text
AT+CIPSERVER=1,80
```

El ESP8266 escuchará en:

```text
puerto 80
```

---

# 31. Órdenes de control

Utilizaremos dos rutas:

```text
/led/on
```

y:

```text
/led/off
```

Por ejemplo:

```text
GET /led/on HTTP/1.1
```

significará:

```text
ENCENDER LED
```

Mientras que:

```text
GET /led/off HTTP/1.1
```

significará:

```text
APAGAR LED
```

---

# 32. Página de control

Nuestra página tendrá:

```text
+------------------------------+
|      ARDUINO MEGA IoT        |
+------------------------------+

          LED

     [ ENCENDER ]

      [ APAGAR ]

+------------------------------+
```

Los botones enviarán órdenes al ESP8266.

---

# 33. HTML básico

Podemos utilizar:

```html
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Arduino Mega IoT</title>
</head>

<body>

    <h1>Arduino Mega IoT</h1>

    <h2>Control del LED</h2>

    <a href="/led/on">
        <button>ENCENDER</button>
    </a>

    <a href="/led/off">
        <button>APAGAR</button>
    </a>

</body>
</html>
```

---

# 34. Control desde Arduino

Cuando Arduino detecte:

```text
/led/on
```

ejecutará:

```cpp
estadoLed = true;

digitalWrite(
    LED,
    HIGH
);
```

Cuando detecte:

```text
/led/off
```

ejecutará:

```cpp
estadoLed = false;

digitalWrite(
    LED,
    LOW
);
```

---

# 35. Monitorización y control

El objetivo final será conseguir:

```text
              NAVEGADOR
                  │
                  │ orden
                  ▼
               ESP8266
                  │
                  ▼
            ARDUINO MEGA
              │       │
              ▼       ▼
             LED    SENSOR
                      │
                      ▼
                   ESP8266
                      │
                      ▼
                   InfluxDB
                      │
                      ▼
                    Grafana
```

---

# 36. Dashboard

Nuestro dashboard de la Lección 19 ya dispone de:

```text
Valor del sensor
```

```text
Voltaje del sensor
```

```text
Valor actual
```

```text
Nivel del sensor
```

```text
Voltaje actual
```

Ahora añadiremos:

```text
Estado del LED
```

---

# 37. Panel para el LED

En Grafana añadimos una nueva visualización.

Consulta:

```flux
from(bucket: "arduino")
    |> range(start: v.timeRangeStart, stop: v.timeRangeStop)
    |> filter(fn: (r) => r._measurement == "sensor")
    |> filter(fn: (r) => r._field == "led")
    |> last()
```

Seleccionamos:

```text
Stat
```

Título:

```text
Estado del LED
```

---

# 38. Interpretación

Obtendremos:

```text
0
```

cuando esté apagado.

Y:

```text
1
```

cuando esté encendido.

Podemos configurar Grafana posteriormente para mostrar:

```text
0 → APAGADO
1 → ENCENDIDO
```

---

# 39. Histórico del actuador

También podemos crear una gráfica temporal:

```flux
from(bucket: "arduino")
    |> range(start: v.timeRangeStart, stop: v.timeRangeStop)
    |> filter(fn: (r) => r._measurement == "sensor")
    |> filter(fn: (r) => r._field == "led")
```

Así podremos saber:

```text
cuándo se encendió
```

y:

```text
cuándo se apagó
```

el actuador.

---

# 40. Importancia del histórico

En un sistema real no solamente interesa conocer:

```text
¿Está encendido ahora?
```

También puede interesarnos:

```text
¿A qué hora se encendió?
```

```text
¿Cuánto tiempo estuvo encendido?
```

```text
¿Qué valor tenía el sensor cuando se encendió?
```

Por eso almacenamos los estados en InfluxDB.

---

# 41. Práctica de integración

El alumno deberá conseguir que el sistema tenga:

**Una entrada:**

```text
potenciómetro
```

**Una salida:**

```text
LED
```

**Comunicación:**

```text
ESP8266
```

**Almacenamiento:**

```text
InfluxDB
```

**Visualización:**

```text
Grafana
```

**Control:**

```text
navegador web
```

---

# 42. Ampliación

Una vez conseguido el funcionamiento básico se puede sustituir:

```text
potenciómetro
```

por un sensor real del kit.

Por ejemplo:

```text
sensor de luz
```

o:

```text
sensor de temperatura
```

También podemos sustituir:

```text
LED
```

por otro actuador.

Por ejemplo:

```text
servo
```

```text
zumbador
```

```text
relé
```

si el kit dispone del componente adecuado.

---

# 43. Ejemplo de sistema real

Podríamos construir:

```text
SENSOR DE LUZ
      │
      ▼
Arduino Mega
      │
      ├──────────────► LED
      │
      ▼
   ESP8266
      │
      ▼
   InfluxDB
      │
      ▼
    Grafana
```

Desde el navegador podríamos encender o apagar la iluminación.

Grafana mostraría la evolución de la luminosidad.

---

# 44. Otro ejemplo

También podríamos crear:

```text
SENSOR TEMPERATURA
        │
        ▼
    Arduino Mega
        │
        ├──────────► ventilador/actuador
        │
        ▼
      ESP8266
        │
        ▼
      InfluxDB
        │
        ▼
       Grafana
```

Esto se aproxima mucho más a un sistema IoT real.

---

# 45. Documentación

El alumno deberá documentar:

* Esquema del sistema.
* Componentes utilizados.
* Conexiones.
* Programa Arduino.
* Comunicación con ESP8266.
* Formato de los datos enviados.
* Configuración de InfluxDB.
* Dashboard de Grafana.
* Página web de control.
* Pruebas realizadas.

---

# 46. Entrega

Se entregará un documento:

```text
leccion20_proyecto_iot.pdf
```

También deberán entregarse los programas utilizados.

El PDF deberá incluir capturas del sistema funcionando.

---

# 47. Comprobación presencial

La documentación no será suficiente para superar la práctica.

El profesor comprobará físicamente el montaje.

El alumno deberá demostrar:

```text
1. El sensor funciona.
2. Arduino lee correctamente el sensor.
3. El ESP8266 está conectado al Wi-Fi.
4. InfluxDB recibe las medidas.
5. Grafana muestra los datos.
6. El LED puede controlarse.
7. El estado del LED queda registrado.
```

---

# 48. Prueba final

El alumno modificará físicamente el potenciómetro.

Deberá observar:

```text
Potenciómetro
     ↓
Arduino
     ↓
InfluxDB
     ↓
Grafana
```

Después utilizará el navegador para cambiar el estado del LED.

Deberá observar:

```text
Navegador
     ↓
ESP8266
     ↓
Arduino
     ↓
LED
```

y posteriormente:

```text
estado LED
     ↓
InfluxDB
     ↓
Grafana
```

---

# 49. Lo que hemos conseguido

Nuestro Arduino ya no es simplemente una placa que ejecuta un programa local.

Forma parte de un sistema conectado:

```text
              INTERNET / RED
                    │
                    ▼
                ESP8266
                    │
                    ▼
             ARDUINO MEGA
               │       │
               ▼       ▼
            SENSOR   ACTUADOR
               │
               ▼
            InfluxDB
               │
               ▼
             Grafana
```

Hemos integrado:

```text
ELECTRÓNICA
+
PROGRAMACIÓN
+
COMUNICACIONES
+
SERVICIOS WEB
+
BASES DE DATOS
+
VISUALIZACIÓN
```

---

# 50. Conclusión

En esta lección hemos comenzado a integrar todos los conocimientos adquiridos durante el curso.

El sistema es capaz de:

```text
MEDIR
```

```text
CONTROLAR
```

```text
COMUNICAR
```

```text
ALMACENAR
```

```text
VISUALIZAR
```

Esta arquitectura constituye la base de muchos sistemas IoT reales.

---

# 51. Preparación para el proyecto final

En la siguiente actividad los grupos tendrán mayor autonomía.

Cada grupo deberá seleccionar:

* Uno o varios sensores.
* Uno o varios actuadores.
* Las variables que almacenará.
* La página web de control.
* La estructura de InfluxDB.
* El dashboard de Grafana.

El objetivo será diseñar una solución propia partiendo de la arquitectura aprendida:

```text
SENSORES
    │
    ▼
ARDUINO MEGA
    │
    ▼
ESP8266
    │
    ├────────► CONTROL WEB
    │
    └────────► INFLUXDB
                    │
                    ▼
                 GRAFANA
                    │
                    ▼
                DASHBOARD
```

El alumno deberá ser capaz de justificar tanto las conexiones físicas como las decisiones tomadas en el programa.
