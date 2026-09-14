# Lección 18 — Guardar datos de Arduino en InfluxDB

## 1. Objetivos

En la lección anterior conseguimos enviar datos desde Arduino Mega hasta un servidor HTTP.

Ahora vamos a almacenar esos datos en una base de datos pensada específicamente para medidas que cambian con el tiempo.

Al finalizar esta práctica seremos capaces de:

* Comprender qué es InfluxDB.
* Comprender qué es una serie temporal.
* Crear una organización y un bucket.
* Generar un token de acceso.
* Comprender el Line Protocol de InfluxDB.
* Enviar una medida desde Arduino/ESP8266.
* Comprobar que la medida queda almacenada.
* Preparar los datos para visualizarlos posteriormente con Grafana.

Nuestro objetivo será:

```text
SENSOR
   │
   ▼
ARDUINO MEGA
   │
   │ UART
   ▼
ESP8266
   │
   │ Wi-Fi / HTTP
   ▼
INFLUXDB
   │
   ▼
DATO ALMACENADO
```

---

## 2. ¿Qué es InfluxDB?

InfluxDB es una base de datos especializada en datos de series temporales.

Una serie temporal es una colección de valores asociados a un instante de tiempo.

Por ejemplo:

```text
10:00 → 22,4 °C
10:05 → 22,8 °C
10:10 → 23,1 °C
10:15 → 23,5 °C
```

Este tipo de información aparece continuamente en sistemas IoT.

Por ejemplo:

```text
temperatura
humedad
distancia
consumo
presión
luminosidad
velocidad
```

---

## 3. Diferencia respecto a una base de datos tradicional

En una base de datos convencional podríamos almacenar:

```text
Alumno
Nombre
Curso
Edad
```

En nuestro proyecto queremos almacenar principalmente:

```text
qué hemos medido
+
cuánto vale
+
cuándo se ha medido
```

Por ejemplo:

```text
sensor = potenciometro
valor = 411
hora = 10:23:15
```

InfluxDB está especialmente preparado para este tipo de datos.

---

## 4. Arquitectura de la práctica

En la lección anterior teníamos:

```text
ARDUINO
   │
   ▼
ESP8266
   │
   ▼
servidor.py
   │
   ▼
Windows 11
```

Ahora sustituiremos el servidor de prueba por:

```text
InfluxDB
```

La arquitectura será:

```text
POTENCIÓMETRO
      │
      ▼
ARDUINO MEGA
      │
      ▼
ESP8266
      │
      │ Wi-Fi
      ▼
WINDOWS 11
      │
      ▼
INFLUXDB
      │
      ▼
BUCKET
```

---

## 5. Conceptos importantes de InfluxDB

Antes de empezar debemos conocer cuatro conceptos:

```text
Organization
Bucket
Token
Measurement
```

---

## 6. Organization

Una organización agrupa usuarios, buckets y recursos.

Podemos crear una organización llamada:

```text
ArduinoCurso
```

o:

```text
SMXArduino
```

---

## 7. Bucket

Un bucket es el lugar donde almacenaremos nuestras medidas.

Para este curso podemos crear:

```text
arduino
```

Dentro de este bucket guardaremos datos como:

```text
potenciometro
temperatura
distancia
luz
```

---

## 8. Token

InfluxDB utiliza tokens para autorizar el acceso.

Un token funciona como una credencial.

Por ejemplo:

```text
TOKEN = abcdef123456...
```

Este token permitirá escribir datos en nuestro bucket.

> No debemos publicar tokens reales en GitHub.

---

## 9. Measurement

Una measurement es una categoría de datos.

Por ejemplo:

```text
sensor
```

Puede contener diferentes campos:

```text
valor
voltaje
```

Por ejemplo:

```text
sensor valor=411
```

---

# 10. Line Protocol

InfluxDB utiliza un formato denominado:

```text
Line Protocol
```

Es una línea de texto.

Por ejemplo:

```text
sensor valor=411
```

Esto significa:

```text
measurement = sensor
field       = valor
value       = 411
```

---

## 11. Añadir más campos

Podemos enviar:

```text
sensor valor=411,voltaje=2.01
```

Tenemos:

```text
measurement: sensor
valor:       411
voltaje:     2.01
```

---

## 12. Añadir etiquetas

También podemos añadir tags.

Por ejemplo:

```text
sensor,ubicacion=aula valor=411
```

Aquí tenemos:

```text
measurement = sensor
tag          = ubicacion=aula
field        = valor=411
```

Los tags son útiles para clasificar los datos.

---

# 13. Preparar InfluxDB en Windows

Debemos tener InfluxDB instalado y funcionando en el ordenador.

Supongamos que se ejecuta en:

```text
http://10.113.170.1:8086
```

La IP será la IP real de nuestro ordenador Windows.

El puerto habitual de InfluxDB es:

```text
8086
```

---

# 14. Crear la organización

Desde la interfaz web de InfluxDB creamos una organización.

Por ejemplo:

```text
ArduinoCurso
```

Anota exactamente el nombre utilizado.

---

# 15. Crear el bucket

Creamos un bucket llamado:

```text
arduino
```

Este será el destino de nuestras medidas.

---

# 16. Crear un token

Creamos un token con permiso para escribir en el bucket.

Guardaremos temporalmente:

```text
TOKEN
```

en un lugar seguro.

No debe aparecer en:

```text
GitHub
capturas públicas
documentación entregada
```

---

# 17. Endpoint de escritura

InfluxDB permite escribir datos mediante HTTP.

La ruta utilizada será similar a:

```text
/api/v2/write
```

y necesitaremos indicar:

```text
org
bucket
precision
```

Por ejemplo:

```text
/api/v2/write?org=ArduinoCurso&bucket=arduino&precision=s
```

---

# 18. Método HTTP

En la Lección 17 utilizábamos:

```text
GET
```

Ahora utilizaremos:

```text
POST
```

porque queremos enviar datos al servidor.

La estructura será:

```text
POST /api/v2/write?... HTTP/1.1
Host: IP_INFLUXDB:8086
Authorization: Token TOKEN
Content-Type: text/plain
Content-Length: ...

sensor valor=411
```

---

# 19. Diferencia entre GET y POST

## GET

```text
GET /dato?valor=411
```

El dato aparece en la URL.

## POST

```text
POST /api/v2/write
```

y el dato aparece en el cuerpo:

```text
sensor valor=411
```

InfluxDB utiliza este segundo enfoque para escribir medidas.

---

# 20. Primera prueba manual

Antes de utilizar Arduino conviene probar InfluxDB desde Windows.

Podemos usar PowerShell.

Por ejemplo:

```powershell
curl.exe -X POST "http://localhost:8086/api/v2/write?org=ArduinoCurso&bucket=arduino&precision=s" ^
  -H "Authorization: Token TU_TOKEN" ^
  -H "Content-Type: text/plain" ^
  --data-raw "sensor valor=123"
```

En PowerShell puede resultar más cómodo escribirlo en una sola línea:

```powershell
curl.exe -X POST "http://localhost:8086/api/v2/write?org=ArduinoCurso&bucket=arduino&precision=s" -H "Authorization: Token TU_TOKEN" -H "Content-Type: text/plain" --data-raw "sensor valor=123"
```

Si no aparece un error, la escritura puede haberse realizado correctamente.

---

# 21. Comprobar la medida

Desde la interfaz de InfluxDB abrimos el explorador de datos.

Buscamos:

```text
bucket: arduino
```

y:

```text
measurement: sensor
```

Deberíamos encontrar:

```text
valor = 123
```

Si aparece, ya sabemos que InfluxDB está preparado.

---

# 22. Programa Arduino

Ahora vamos a modificar el flujo de la lección anterior.

Crea:

```text
ejemplos/18_influxdb/main.cpp
```

---

# 23. Configuración inicial

Usaremos:

```cpp
#include <Arduino.h>

const int SENSOR = A0;

const char* SSID = "NOMBRE_WIFI";
const char* PASSWORD = "CONTRASENA_WIFI";

const char* IP_INFLUX = "10.113.170.1";
const int PUERTO_INFLUX = 8086;

const char* ORGANIZACION = "ArduinoCurso";
const char* BUCKET = "arduino";
const char* TOKEN = "TU_TOKEN";
```

Debemos sustituir los valores por los reales.

---

# 24. Enviar comandos AT

Reutilizaremos:

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

# 25. Conectar al Wi-Fi

Utilizamos:

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

---

# 26. Construir el Line Protocol

Leeremos:

```cpp
int valor = analogRead(SENSOR);
```

y calcularemos:

```cpp
float voltaje =
    valor * 5.0 / 1023.0;
```

Después construiremos:

```cpp
String datos =
    "sensor valor=" +
    String(valor) +
    ",voltaje=" +
    String(voltaje, 2);
```

Por ejemplo:

```text
sensor valor=411,voltaje=2.01
```

---

# 27. Construir la petición POST

Crearemos:

```cpp
String ruta =
    "/api/v2/write?org=" +
    String(ORGANIZACION) +
    "&bucket=" +
    String(BUCKET) +
    "&precision=s";
```

Después:

```cpp
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
```

---

# 28. Función para enviar a InfluxDB

```cpp
void enviarInflux(int valor)
{
    float voltaje =
        valor * 5.0 / 1023.0;


    String datos =
        "sensor valor=" +
        String(valor) +
        ",voltaje=" +
        String(voltaje, 2);


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


    enviarAT(
        comandoConexion,
        3000
    );


    Serial1.print("AT+CIPSEND=");
    Serial1.print(peticion.length());
    Serial1.print("\r\n");


    delay(1000);


    Serial1.print(peticion);


    delay(3000);


    while (Serial1.available())
    {
        Serial.write(
            Serial1.read()
        );
    }
}
```

---

# 29. Programa completo

```cpp
#include <Arduino.h>

const int SENSOR = A0;

const char* SSID = "NOMBRE_WIFI";
const char* PASSWORD = "CONTRASENA_WIFI";

const char* IP_INFLUX = "10.113.170.1";
const int PUERTO_INFLUX = 8086;

const char* ORGANIZACION = "ArduinoCurso";
const char* BUCKET = "arduino";
const char* TOKEN = "TU_TOKEN";


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
            Serial.write(
                Serial1.read()
            );
        }
    }
}


void conectarWiFi()
{
    enviarAT(
        "AT",
        1000
    );

    enviarAT(
        "AT+CWMODE=1",
        1000
    );


    String comandoWiFi =
        "AT+CWJAP=\"" +
        String(SSID) +
        "\",\"" +
        String(PASSWORD) +
        "\"";


    enviarAT(
        comandoWiFi,
        8000
    );


    enviarAT(
        "AT+CIPSERVER=0",
        1000
    );


    enviarAT(
        "AT+CIPMUX=0",
        1000
    );


    enviarAT(
        "AT+CIFSR",
        1000
    );
}


void enviarInflux(int valor)
{
    float voltaje =
        valor * 5.0 / 1023.0;


    String datos =
        "sensor valor=" +
        String(valor) +
        ",voltaje=" +
        String(voltaje, 2);


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


    Serial.println();
    Serial.println("Datos:");
    Serial.println(datos);


    String comandoConexion =
        "AT+CIPSTART=\"TCP\",\"" +
        String(IP_INFLUX) +
        "\"," +
        String(PUERTO_INFLUX);


    enviarAT(
        comandoConexion,
        3000
    );


    Serial1.print("AT+CIPSEND=");
    Serial1.print(peticion.length());
    Serial1.print("\r\n");


    delay(1000);


    Serial1.print(peticion);


    delay(3000);


    while (Serial1.available())
    {
        Serial.write(
            Serial1.read()
        );
    }


    Serial.println();
    Serial.println("Medida enviada.");
}


void setup()
{
    Serial.begin(9600);

    Serial1.begin(9600);


    delay(2000);


    Serial.println();
    Serial.println("==============================");
    Serial.println(" ARDUINO -> INFLUXDB");
    Serial.println("==============================");


    conectarWiFi();
}


void loop()
{
    int valor =
        analogRead(SENSOR);


    Serial.print("Sensor: ");
    Serial.println(valor);


    enviarInflux(valor);


    delay(10000);
}
```

---

# 30. Resultado esperado

Cada 10 segundos Arduino generará algo parecido a:

```text
sensor valor=411,voltaje=2.01
```

y lo enviará a:

```text
InfluxDB
```

---

# 31. Respuesta correcta de InfluxDB

Cuando una escritura se realiza correctamente, InfluxDB suele devolver un código HTTP de éxito sin contenido.

Debemos buscar algo parecido a:

```text
HTTP/1.1 204 No Content
```

El código:

```text
204
```

significa que la escritura se ha realizado correctamente y no hay contenido adicional que devolver.

---

# 32. Comprobar los datos

Desde InfluxDB debemos localizar:

```text
bucket = arduino
```

Después:

```text
measurement = sensor
```

Y podremos observar campos:

```text
valor
voltaje
```

con diferentes registros.

---

# 33. Girar el potenciómetro

Ahora gira el potenciómetro durante aproximadamente un minuto.

InfluxDB debería almacenar una secuencia similar a:

```text
411
427
503
621
802
994
...
```

Cada valor tendrá asociada una marca temporal.

---

# 34. Práctica 1 — Comprobar la escritura

Debemos conseguir:

```text
Arduino
   │
   ▼
InfluxDB
   │
   ▼
204 No Content
```

y verificar que aparece el dato en el bucket.

---

# 35. Práctica 2 — Dos campos

Comprueba que se almacenan:

```text
valor
```

y:

```text
voltaje
```

Visualiza ambos campos desde InfluxDB.

---

# 36. Práctica 3 — Añadir un tag

Modifica:

```cpp
String datos =
    "sensor valor=" +
    String(valor);
```

por:

```cpp
String datos =
    "sensor,ubicacion=aula valor=" +
    String(valor);
```

Ahora cada medida tendrá:

```text
ubicacion = aula
```

como etiqueta.

---

# 37. Práctica 4 — Identificar dispositivos

Imagina que tenemos varios Arduino.

Podemos enviar:

```text
sensor,dispositivo=mega01 valor=411
```

y otro grupo:

```text
sensor,dispositivo=mega02 valor=526
```

InfluxDB podrá diferenciar sus medidas.

---

# 38. Práctica 5 — Sustituir el potenciómetro

Utiliza uno de los sensores estudiados en la Lección 10.

Por ejemplo:

```text
temperatura
```

El Line Protocol podría ser:

```text
temperatura,aula=1 valor=24.6
```

Otro ejemplo:

```text
distancia,aula=1 cm=37
```

---

# 39. Problemas frecuentes

## `CONNECT FAIL`

Comprueba:

* IP del ordenador.
* Puerto 8086.
* Firewall de Windows.
* Que InfluxDB esté ejecutándose.

---

## `401 Unauthorized`

Normalmente significa:

```text
TOKEN INCORRECTO
```

o sin permisos suficientes.

---

## `404 Not Found`

Comprueba la ruta:

```text
/api/v2/write
```

y los parámetros:

```text
org
bucket
```

---

## `400 Bad Request`

Puede indicar un problema en:

```text
Line Protocol
```

por ejemplo:

```text
sensor valor=
```

sin un valor válido.

---

## No aparece ningún dato

Comprueba:

```text
Organization
Bucket
Token
Measurement
```

y revisa la respuesta HTTP.

---

# 40. Seguridad de las credenciales

Ahora tenemos tres datos sensibles:

```text
PASSWORD Wi-Fi
TOKEN InfluxDB
```

No debemos publicarlos en GitHub.

Antes de hacer:

```text
git push
```

debemos sustituirlos por:

```cpp
const char* PASSWORD = "CONTRASENA_WIFI";
const char* TOKEN = "TU_TOKEN";
```

---

# 41. Arquitectura conseguida

Nuestro sistema es ahora:

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
    HTTP POST
      │
      ▼
   INFLUXDB
      │
      ▼
SERIE TEMPORAL
```

Ya no estamos simplemente mostrando una medida.

Ahora estamos construyendo un **histórico de datos**.

---

# 42. Datos actuales frente a históricos

En la Lección 16 solamente veíamos:

```text
Valor actual = 411
```

Ahora podemos conocer:

```text
10:00 → 355
10:10 → 411
10:20 → 526
10:30 → 732
```

Esto permite estudiar tendencias.

---

# 43. Lo que hemos aprendido

En esta lección hemos unido:

```text
Arduino
+
ESP8266
+
HTTP
+
InfluxDB
```

Hemos aprendido:

```text
Line Protocol
```

y conceptos como:

```text
Organization
Bucket
Token
Measurement
Field
Tag
```

Nuestro sistema ya realiza:

```text
MEDIR
  ↓
TRANSMITIR
  ↓
ALMACENAR
```

---

# 44. Preparación para la siguiente lección

Tenemos datos almacenados.

Ahora queremos convertirlos en información visual.

En la siguiente lección utilizaremos:

```text
Grafana
```

para crear un dashboard.

La arquitectura final será:

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
INFLUXDB
   │
   ▼
GRAFANA
   │
   ▼
DASHBOARD
```

Crearemos gráficas que permitan observar la evolución de nuestros sensores a lo largo del tiempo.
