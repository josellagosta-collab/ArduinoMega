# Lección 17 — Enviar datos por HTTP desde Arduino y ESP8266

## 1. Objetivos

En esta lección aprenderemos a enviar datos desde nuestro sistema hacia un servidor utilizando HTTP.

Al finalizar seremos capaces de:

* Comprender la diferencia entre servidor y cliente.
* Utilizar el ESP8266 como cliente TCP.
* Abrir una conexión TCP con un servidor.
* Construir una petición HTTP.
* Enviar datos desde Arduino hacia un servidor.
* Comprender la diferencia entre `GET` y `POST`.
* Preparar el sistema para enviar datos posteriormente a InfluxDB.

Nuestro nuevo flujo será:

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
   │ Wi-Fi
   ▼
SERVIDOR HTTP
```

---

## 2. Punto de partida

Hasta ahora nuestro ESP8266 funcionaba principalmente como servidor.

El navegador se conectaba a:

```text
ESP8266
```

y este respondía con una página web.

Ahora haremos lo contrario.

El ESP8266 iniciará una conexión hacia otro servidor.

Tendremos:

```text
ANTES

NAVEGADOR
    │
    ▼
ESP8266
```

y ahora:

```text
AHORA

ESP8266
    │
    ▼
SERVIDOR
```

---

## 3. ¿Qué es un cliente?

En una comunicación de red:

```text
CLIENTE
```

es normalmente el dispositivo que inicia la conexión.

```text
SERVIDOR
```

es el dispositivo que espera conexiones.

En esta práctica:

```text
ESP8266 → CLIENTE
```

y:

```text
ORDENADOR / SERVIDOR → SERVIDOR
```

---

## 4. Arquitectura de la práctica

Nuestro sistema será:

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
SERVIDOR HTTP
      │
      ▼
RECIBE EL VALOR
```

El dato que enviaremos será, por ejemplo:

```text
valor=537
```

---

## 5. ¿Qué es una petición HTTP?

Una petición HTTP es un mensaje enviado por un cliente a un servidor.

Por ejemplo:

```text
GET /dato?valor=537 HTTP/1.1
```

Esto significa:

```text
GET
```

queremos solicitar un recurso.

```text
/dato
```

es la ruta.

```text
valor=537
```

es un parámetro.

---

## 6. GET y POST

Los dos métodos más conocidos son:

```text
GET
POST
```

### GET

Suele utilizarse para solicitar información.

Ejemplo:

```text
GET /dato?valor=537 HTTP/1.1
```

El valor aparece en la URL.

### POST

Suele utilizarse para enviar datos al servidor.

Ejemplo conceptual:

```text
POST /dato HTTP/1.1

valor=537
```

En esta primera práctica utilizaremos `GET` porque es más sencillo de observar y comprender.

Más adelante, con InfluxDB, utilizaremos peticiones más adecuadas para escribir datos.

---

# 7. Necesitamos un servidor de prueba

Para comprobar el envío necesitaremos un servidor HTTP accesible desde la misma red.

Podemos utilizar:

```text
un ordenador
```

que ejecute un pequeño servidor web de pruebas.

Por ejemplo:

```text
PC servidor
IP: 192.168.1.50
Puerto: 8000
```

Nuestro ESP8266 se conectará a:

```text
192.168.1.50:8000
```

---

# 8. Abrir una conexión TCP

Para que el ESP8266 actúe como cliente utilizaremos:

```text
AT+CIPSTART
```

La estructura básica es:

```text
AT+CIPSTART="TCP","IP_SERVIDOR",PUERTO
```

Por ejemplo:

```text
AT+CIPSTART="TCP","192.168.1.50",8000
```

Si todo funciona correctamente podemos recibir:

```text
CONNECT

OK
```

---

# 9. Construir una petición HTTP

Queremos enviar:

```text
GET /dato?valor=537 HTTP/1.1
Host: 192.168.1.50
Connection: close
```

Debemos añadir:

```text
\r\n
```

al final de cada línea.

Y una línea vacía al final de las cabeceras.

En C++:

```cpp
String peticion = "";

peticion += "GET /dato?valor=537 HTTP/1.1\r\n";
peticion += "Host: 192.168.1.50\r\n";
peticion += "Connection: close\r\n";
peticion += "\r\n";
```

---

# 10. Enviar la petición

Primero debemos indicar cuántos bytes enviaremos.

Utilizamos:

```text
AT+CIPSEND
```

por ejemplo:

```text
AT+CIPSEND=78
```

La longitud real la calcularemos mediante:

```cpp
peticion.length()
```

---

# 11. Programa base

Crea:

```text
ejemplos/17_envio_http/main.cpp
```

con el siguiente programa.

```cpp
#include <Arduino.h>

const int SENSOR = A0;

const char* SSID = "NOMBRE_WIFI";
const char* PASSWORD = "CONTRASENA_WIFI";

const char* IP_SERVIDOR = "192.168.1.50";
const int PUERTO_SERVIDOR = 8000;


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
// Conectar ESP8266 al Wi-Fi
// ------------------------------------------------

void conectarWiFi()
{
    enviarAT("AT", 1000);

    enviarAT(
        "AT+CWMODE=1",
        1000
    );

    String conexion =
        "AT+CWJAP=\"" +
        String(SSID) +
        "\",\"" +
        String(PASSWORD) +
        "\"";

    enviarAT(
        conexion,
        8000
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


// ------------------------------------------------
// Enviar dato mediante HTTP
// ------------------------------------------------

void enviarDatoHTTP(int valor)
{
    Serial.println();
    Serial.println("Enviando dato al servidor...");


    String comandoConexion =
        "AT+CIPSTART=\"TCP\",\"" +
        String(IP_SERVIDOR) +
        "\"," +
        String(PUERTO_SERVIDOR);


    enviarAT(
        comandoConexion,
        3000
    );


    String peticion = "";

    peticion += "GET /dato?valor=";
    peticion += String(valor);
    peticion += " HTTP/1.1\r\n";

    peticion += "Host: ";
    peticion += IP_SERVIDOR;
    peticion += "\r\n";

    peticion += "Connection: close\r\n";
    peticion += "\r\n";


    Serial.println("Peticion HTTP:");
    Serial.println(peticion);


    Serial1.print("AT+CIPSEND=");
    Serial1.print(peticion.length());
    Serial1.print("\r\n");


    delay(1000);


    Serial1.print(peticion);


    delay(2000);


    while (Serial1.available())
    {
        Serial.write(Serial1.read());
    }


    enviarAT(
        "AT+CIPCLOSE",
        1000
    );
}


// ------------------------------------------------
// SETUP
// ------------------------------------------------

void setup()
{
    Serial.begin(9600);

    Serial1.begin(9600);

    delay(2000);


    Serial.println();
    Serial.println("===============================");
    Serial.println(" ENVIO HTTP DESDE ARDUINO");
    Serial.println("===============================");
    Serial.println();


    conectarWiFi();
}


// ------------------------------------------------
// LOOP
// ------------------------------------------------

void loop()
{
    int valor =
        analogRead(SENSOR);


    Serial.print("Valor sensor: ");
    Serial.println(valor);


    enviarDatoHTTP(valor);


    delay(10000);
}
```

---

# 12. ¿Qué hace el programa?

Cada diez segundos realiza:

```text
leer sensor
    │
    ▼
abrir conexión TCP
    │
    ▼
crear petición HTTP
    │
    ▼
enviar petición
    │
    ▼
cerrar conexión
```

Por tanto:

```text
A0
 │
 ▼
Arduino
 │
 ▼
ESP8266
 │
 ▼
Servidor
```

---

# 13. Primera prueba sin sensor real

Podemos empezar enviando un valor fijo.

Sustituye:

```cpp
int valor =
    analogRead(SENSOR);
```

por:

```cpp
int valor = 123;
```

El ESP8266 enviará:

```text
GET /dato?valor=123 HTTP/1.1
```

Esto permite comprobar primero la red sin preocuparnos todavía por el sensor.

---

# 14. Comprobar la conexión TCP

En el monitor serie deberíamos ver algo parecido a:

```text
AT+CIPSTART="TCP","192.168.1.50",8000

CONNECT
OK
```

Después:

```text
AT+CIPSEND=...
```

y finalmente:

```text
SEND OK
```

---

# 15. ¿Qué significa SEND OK?

Cuando aparece:

```text
SEND OK
```

significa que el ESP8266 ha transmitido los datos por la conexión TCP.

No significa necesariamente que el servidor los haya procesado correctamente.

Por tanto debemos comprobar también el servidor.

---

# 16. Respuesta del servidor

Un servidor HTTP puede responder:

```text
HTTP/1.1 200 OK
```

Esto significa que la petición ha sido procesada correctamente.

También podríamos recibir:

```text
404 Not Found
```

si la ruta no existe.

O:

```text
500 Internal Server Error
```

si existe algún problema en el servidor.

---

# 17. ¿Qué es un código HTTP?

Los servidores utilizan códigos numéricos.

Algunos ejemplos:

| Código | Significado           |
| -----: | --------------------- |
|    200 | Correcto              |
|    201 | Creado                |
|    400 | Petición incorrecta   |
|    401 | No autorizado         |
|    404 | Recurso no encontrado |
|    500 | Error del servidor    |

No es necesario memorizarlos todos.

Debemos aprender principalmente a interpretar:

```text
200
```

como una respuesta correcta.

---

# 18. Práctica 1 — Enviar un valor fijo

Configura:

```cpp
int valor = 123;
```

Comprueba:

* Que el ESP8266 abre la conexión.
* Que aparece `CONNECT`.
* Que aparece `SEND OK`.
* Que el servidor recibe `valor=123`.

---

# 19. Práctica 2 — Enviar el potenciómetro

Recupera:

```cpp
int valor =
    analogRead(SENSOR);
```

Gira el potenciómetro.

Comprueba que el servidor recibe diferentes valores.

Por ejemplo:

```text
valor=124

valor=526

valor=817
```

---

# 20. Enviar más de un dato

Podemos enviar varios parámetros:

```text
/dato?valor=537&voltaje=2.62
```

En Arduino:

```cpp
int valor = analogRead(SENSOR);

float voltaje =
    valor * 5.0 / 1023.0;
```

Y:

```cpp
peticion += "GET /dato?valor=";
peticion += String(valor);

peticion += "&voltaje=";
peticion += String(voltaje, 2);
```

El resultado será parecido a:

```text
GET /dato?valor=537&voltaje=2.62 HTTP/1.1
```

---

# 21. Estructura clave-valor

Esta forma:

```text
valor=537
```

representa:

```text
CLAVE = VALOR
```

Otro ejemplo:

```text
temperatura=24.6
```

Otro:

```text
distancia=37
```

Y podemos combinar:

```text
temperatura=24.6&humedad=51
```

Este concepto aparecerá constantemente en sistemas IoT.

---

# 22. Práctica 3 — Dos valores

Envía:

```text
valor ADC
```

y:

```text
voltaje
```

al servidor.

Debe llegar algo parecido a:

```text
/dato?valor=512&voltaje=2.50
```

---

# 23. Periodicidad de envío

Actualmente tenemos:

```cpp
delay(10000);
```

Por tanto enviamos un dato aproximadamente cada:

```text
10 segundos
```

Podemos cambiarlo por:

```cpp
delay(5000);
```

para enviar cada 5 segundos.

No es recomendable enviar continuamente sin pausas.

---

# 24. Problema de usar delay()

Mientras Arduino ejecuta:

```cpp
delay(10000);
```

no puede realizar otras tareas durante esos 10 segundos.

En sistemas más avanzados utilizaremos:

```cpp
millis()
```

para realizar tareas periódicas sin detener el programa.

Lo veremos más adelante.

---

# 25. Práctica 4 — Cambiar frecuencia

Prueba:

```text
2 segundos
5 segundos
10 segundos
30 segundos
```

y observa cómo cambia la frecuencia con la que el servidor recibe datos.

---

# 26. Detectar errores

Nuestro programa actual envía comandos y espera un tiempo fijo.

No comprueba realmente:

```text
OK
CONNECT
>
SEND OK
```

En una solución más robusta deberíamos esperar y verificar esas respuestas.

Por ejemplo:

```text
Enviar CIPSTART
      │
      ▼
¿CONNECT?
      │
    SÍ│NO
      │
      ▼
 continuar
```

Más adelante podremos mejorar esta gestión.

---

# 27. ¿Por qué usamos CIPMUX=0?

En esta práctica utilizamos:

```text
AT+CIPMUX=0
```

porque solamente necesitamos una conexión TCP cada vez.

Tenemos:

```text
ESP8266
   │
   ▼
UN SERVIDOR
```

En cambio, en la lección del servidor web utilizábamos:

```text
AT+CIPMUX=1
```

porque el ESP8266 podía recibir diferentes conexiones.

---

# 28. Comparar servidor y cliente

## ESP8266 como servidor

```text
Navegador
   │
   ▼
ESP8266
```

El ESP espera conexiones.

## ESP8266 como cliente

```text
ESP8266
   │
   ▼
Servidor
```

El ESP inicia la conexión.

Nuestro proyecto necesita comprender ambos roles.

---

# 29. Práctica 5 — Utilizar otro sensor

Sustituye el potenciómetro por uno de los sensores investigados en la Lección 10.

Por ejemplo:

```text
temperatura
```

La petición podría ser:

```text
/dato?temperatura=24.6
```

Otro ejemplo:

```text
/distancia?cm=37
```

Debes adaptar el programa a la medida real.

---

# 30. ¿Qué necesitamos todavía?

Nuestro sistema actual puede enviar:

```text
valor=537
```

a un servidor.

Pero el servidor debe decidir qué hacer con ese dato.

Podría:

```text
mostrarlo
```

o:

```text
guardarlo en un fichero
```

o:

```text
insertarlo en una base de datos
```

Nosotros queremos hacer esto último.

---

# 31. Series temporales

Nuestros datos tienen una característica importante.

No solamente queremos almacenar:

```text
temperatura = 24.6
```

También queremos saber:

```text
CUÁNDO
```

se produjo esa medida.

Por ejemplo:

```text
09:00 → 22.4 °C
09:05 → 22.8 °C
09:10 → 23.1 °C
09:15 → 23.5 °C
```

Este tipo de datos se denomina:

```text
SERIE TEMPORAL
```

---

# 32. InfluxDB

InfluxDB es una base de datos especialmente diseñada para almacenar datos que cambian con el tiempo.

Por ejemplo:

```text
temperatura
humedad
presión
consumo
velocidad
distancia
```

Nuestro futuro sistema será:

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
HTTP
   │
   ▼
INFLUXDB
```

---

# 33. Grafana

Después utilizaremos Grafana para representar los datos almacenados.

Tendremos:

```text
InfluxDB
   │
   ▼
Grafana
   │
   ▼
DASHBOARD
```

Con gráficas como:

```text
Temperatura

25 │            ●
24 │       ●  ●
23 │    ●
22 │ ●
   └────────────────
     tiempo
```

---

# 34. Arquitectura hacia la que avanzamos

Nuestro proyecto final será:

```text
              SENSOR
                │
                ▼
         ARDUINO MEGA
                │
              UART
                │
                ▼
            ESP8266
                │
              Wi-Fi
                │
                ▼
              HTTP
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

---

# 35. Lo que hemos aprendido

En esta lección hemos aprendido a cambiar el papel del ESP8266.

Antes:

```text
ESP8266 = SERVIDOR
```

Ahora:

```text
ESP8266 = CLIENTE
```

Hemos utilizado:

```text
AT+CIPSTART
```

para abrir una conexión TCP.

```text
AT+CIPSEND
```

para transmitir información.

Y hemos construido nuestra primera petición:

```text
GET /dato?valor=537 HTTP/1.1
```

Nuestro Arduino ya puede:

```text
LEER SENSOR
      │
      ▼
CREAR DATO
      │
      ▼
ENVIAR POR Wi-Fi
      │
      ▼
SERVIDOR
```

---

# 36. Preparación para la siguiente lección

En la siguiente lección comenzaremos ya a trabajar directamente con:

```text
InfluxDB
```

Aprenderemos:

* Qué es una base de datos de series temporales.
* Cómo crear un bucket.
* Qué es una organización.
* Qué es un token.
* Cómo se representan los datos en Line Protocol.
* Cómo enviar una primera medida desde Arduino/ESP8266.

Nuestro primer objetivo será conseguir:

```text
ARDUINO
   │
   ▼
ESP8266
   │
   ▼
INFLUXDB
   │
   ▼
DATO ALMACENADO
```

Una vez conseguido, estaremos preparados para crear posteriormente nuestro primer dashboard con **Grafana**.
