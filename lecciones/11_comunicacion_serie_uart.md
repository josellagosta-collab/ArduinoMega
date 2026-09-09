# Lección 11 — Comunicación serie UART con Arduino Mega

## 1. Introducción

Hasta ahora hemos utilizado el puerto serie principalmente para mostrar información en el ordenador:

```cpp
Serial.println("Hola");
```

En las próximas lecciones utilizaremos la comunicación serie para algo mucho más importante:

**hacer que Arduino Mega se comunique con otros dispositivos.**

Nuestro objetivo final será conectar un módulo:

```text
ESP8266
```

que proporcionará conectividad Wi-Fi a nuestro proyecto.

La arquitectura que queremos construir será:

```text
SENSORES
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
RED LOCAL / INTERNET
```

Antes de conectar el ESP8266 debemos comprender cómo funciona la comunicación serie UART.

---

# 2. Objetivos

En esta lección aprenderemos a:

* Comprender qué es una comunicación serie.
* Comprender el concepto de UART.
* Identificar los puertos serie del Arduino Mega 2560.
* Diferenciar `Serial`, `Serial1`, `Serial2` y `Serial3`.
* Comprender las señales TX y RX.
* Enviar información desde Arduino.
* Recibir información.
* Comunicar dos puertos serie.
* Crear un pequeño puente entre el ordenador y otro dispositivo.
* Preparar Arduino Mega para comunicarse posteriormente con un ESP8266.

---

# 3. ¿Qué significa comunicación serie?

Una comunicación serie envía la información de forma secuencial.

Podemos imaginar los datos:

```text
H O L A
```

transmitidos uno detrás de otro:

```text
H → O → L → A
```

Los bits también viajan uno después de otro:

```text
1 → 0 → 1 → 1 → 0 → 0 → 1 → ...
```

Por eso hablamos de:

```text
COMUNICACIÓN SERIE
```

---

# 4. ¿Qué es UART?

UART significa:

```text
Universal Asynchronous Receiver Transmitter
```

Podemos traducirlo como:

```text
Transmisor/Receptor Asíncrono Universal
```

Es un sistema muy utilizado para que dos dispositivos electrónicos intercambien información.

Por ejemplo:

```text
ARDUINO ←──── UART ────→ ESP8266
```

o:

```text
ARDUINO ←──── UART ────→ GPS
```

o:

```text
ARDUINO ←──── UART ────→ OTRO MICROCONTROLADOR
```

---

# 5. Las señales TX y RX

En una comunicación UART encontramos normalmente dos señales principales:

```text
TX
```

y:

```text
RX
```

TX significa:

```text
TRANSMIT
```

Es decir:

```text
TRANSMITIR
```

RX significa:

```text
RECEIVE
```

Es decir:

```text
RECIBIR
```

---

# 6. Las conexiones deben cruzarse

Si tenemos dos dispositivos:

```text
DISPOSITIVO A

TX
RX
```

y:

```text
DISPOSITIVO B

TX
RX
```

las conexiones se realizan cruzadas:

```text
DISPOSITIVO A              DISPOSITIVO B

TX ───────────────────────► RX

RX ◄─────────────────────── TX
```

Es decir:

```text
TX → RX

RX ← TX
```

Nunca debemos conectar normalmente:

```text
TX → TX
```

ni:

```text
RX → RX
```

---

# 7. También necesitamos una masa común

Para que dos dispositivos puedan comunicarse correctamente deben compartir normalmente:

```text
GND
```

Por tanto una comunicación UART básica tendrá:

```text
TX
RX
GND
```

Podemos representarlo:

```text
ARDUINO                    DISPOSITIVO

TX ───────────────────────► RX

RX ◄─────────────────────── TX

GND ─────────────────────── GND
```

---

# 8. Arduino Mega tiene varios puertos serie

Una gran ventaja del Arduino Mega 2560 es que dispone de **cuatro puertos serie hardware**.

Podemos utilizar:

```text
Serial

Serial1

Serial2

Serial3
```

Esto resulta especialmente útil para nuestro proyecto.

---

# 9. Puertos UART del Arduino Mega

Los puertos son:

| Puerto    |  RX |  TX |
| --------- | --: | --: |
| `Serial`  |  D0 |  D1 |
| `Serial1` | D19 | D18 |
| `Serial2` | D17 | D16 |
| `Serial3` | D15 | D14 |

Debemos observar que el orden que aparece físicamente en la placa puede ser:

```text
RX1 = 19
TX1 = 18
```

---

# 10. ¿Para qué utilizaremos cada puerto?

Durante nuestro proyecto utilizaremos principalmente:

```text
Serial
```

para comunicarnos con el ordenador mediante USB.

Y utilizaremos:

```text
Serial1
```

para comunicarnos con el ESP8266.

Por tanto tendremos:

```text
ORDENADOR
    │
    │ USB
    ▼
 Serial
    │
    ▼
ARDUINO MEGA
    │
    │ Serial1
    ▼
ESP8266
```

Esto nos permitirá observar en el ordenador lo que ocurre mientras Arduino se comunica con el módulo Wi-Fi.

---

# 11. Ventaja frente a otros Arduino

En algunas placas con un solo puerto serie puede ser necesario utilizar:

```text
SoftwareSerial
```

para crear un puerto adicional mediante software.

En nuestro caso no será necesario.

Arduino Mega dispone de varios UART físicos.

Por tanto utilizaremos:

```cpp
Serial1
```

para el ESP8266.

Esta es una solución más sencilla y fiable.

---

# 12. Velocidad de comunicación

Cuando iniciamos un puerto serie debemos indicar su velocidad.

Ya conocemos:

```cpp
Serial.begin(9600);
```

El número:

```text
9600
```

indica la velocidad de comunicación en:

```text
bits por segundo
```

También encontraremos velocidades como:

```text
19200
38400
57600
115200
```

Los dos dispositivos que se comunican deben utilizar una configuración compatible.

Si un dispositivo transmite a:

```text
9600
```

y el otro espera:

```text
115200
```

la comunicación no funcionará correctamente.

---

# 13. Primer programa

Comenzaremos utilizando simplemente el puerto USB.

```cpp
#include <Arduino.h>

void setup()
{
    Serial.begin(9600);

    Serial.println("Leccion 11");
    Serial.println("Comunicacion serie UART");
}

void loop()
{
    Serial.println("Arduino Mega funcionando");

    delay(1000);
}
```

Este funcionamiento ya lo conocemos.

Tenemos:

```text
ARDUINO
   │
   │ Serial
   ▼
ORDENADOR
```

---

# 14. Recibir información desde el ordenador

Hasta ahora Arduino enviaba información.

Ahora vamos a hacer lo contrario.

Queremos:

```text
ORDENADOR
    │
    ▼
ARDUINO
```

Para saber si existen datos disponibles podemos utilizar:

```cpp
Serial.available()
```

Si el resultado es mayor que cero significa que hemos recibido información.

---

# 15. Serial.read()

Podemos leer un carácter mediante:

```cpp
Serial.read();
```

Por ejemplo:

```cpp
char dato = Serial.read();
```

La variable:

```text
dato
```

contendrá el carácter recibido.

---

# 16. Programa de recepción

```cpp
#include <Arduino.h>

void setup()
{
    Serial.begin(9600);

    Serial.println("Escribe un caracter:");
}

void loop()
{
    if (Serial.available() > 0)
    {
        char dato = Serial.read();

        Serial.print("He recibido: ");
        Serial.println(dato);
    }
}
```

Abrimos el monitor serie.

Si escribimos:

```text
A
```

Arduino responderá:

```text
He recibido: A
```

---

# 17. Comunicación bidireccional

Ahora tenemos comunicación en los dos sentidos:

```text
ORDENADOR
    │
    │ enviar
    ▼
ARDUINO
    │
    │ responder
    ▼
ORDENADOR
```

Esto se denomina:

```text
COMUNICACIÓN BIDIRECCIONAL
```

---

# 18. Controlar un LED mediante el puerto serie

Podemos aplicar lo aprendido para controlar una salida.

Conectamos un LED como en las primeras prácticas:

```text
D8 → 220 Ω → LED → GND
```

Queremos utilizar:

```text
1 → encender

0 → apagar
```

---

# 19. Programa

```cpp
#include <Arduino.h>

const int LED = 8;

void setup()
{
    Serial.begin(9600);

    pinMode(LED, OUTPUT);

    Serial.println("Control del LED");
    Serial.println("1 = encender");
    Serial.println("0 = apagar");
}

void loop()
{
    if (Serial.available() > 0)
    {
        char comando = Serial.read();

        if (comando == '1')
        {
            digitalWrite(LED, HIGH);
            Serial.println("LED encendido");
        }
        else if (comando == '0')
        {
            digitalWrite(LED, LOW);
            Serial.println("LED apagado");
        }
    }
}
```

Tenemos:

```text
USUARIO
   │
   ▼
MONITOR SERIE
   │
   ▼
ARDUINO
   │
   ▼
LED
```

---

# 20. Un paso hacia el proyecto final

Este ejercicio aparentemente sencillo representa ya el funcionamiento que tendremos más adelante.

Ahora tenemos:

```text
ORDENADOR
   │
   ▼
ARDUINO
   │
   ▼
LED
```

Más adelante tendremos:

```text
NAVEGADOR
   │
   │ Wi-Fi
   ▼
ESP8266
   │
   │ UART
   ▼
ARDUINO
   │
   ▼
LED
```

El origen del comando será diferente, pero Arduino seguirá recibiendo órdenes y controlando componentes.

---

# 21. Utilizar Serial1

Ahora vamos a preparar el segundo puerto serie.

Para inicializarlo utilizaremos:

```cpp
Serial1.begin(9600);
```

Podemos utilizar simultáneamente:

```cpp
Serial.begin(9600);
Serial1.begin(9600);
```

Tenemos entonces:

```text
Serial
   │
   ▼
Ordenador
```

y:

```text
Serial1
   │
   ▼
Dispositivo externo
```

---

# 22. Pines de Serial1

Recordemos:

```text
RX1 → D19

TX1 → D18
```

Por tanto:

```text
Arduino Mega

TX1 = D18
RX1 = D19
```

En las siguientes prácticas conectaremos aquí el ESP8266.

---

# 23. Probar Serial1 sin el ESP8266

Antes de conectar el módulo Wi-Fi podemos comprobar el funcionamiento del puerto.

Realizaremos una conexión temporal entre:

```text
TX1
```

y:

```text
RX1
```

Es decir:

```text
D18 ───────── D19
```

Esto se conoce como una prueba:

```text
LOOPBACK
```

o bucle de retorno.

---

# 24. ¿Qué hace un loopback?

Arduino enviará un dato por:

```text
TX1
```

El cable lo devolverá inmediatamente a:

```text
RX1
```

Por tanto:

```text
Serial1
   │
   ▼
TX1
   │
   │ cable
   ▼
RX1
   │
   ▼
Serial1
```

Esto nos permite comprobar que el puerto funciona.

---

# 25. Programa de prueba de Serial1

Conecta temporalmente:

```text
D18 ↔ D19
```

y carga:

```cpp
#include <Arduino.h>

void setup()
{
    Serial.begin(9600);
    Serial1.begin(9600);

    Serial.println("Prueba de Serial1");
}

void loop()
{
    Serial1.println("Hola desde Serial1");

    delay(100);

    if (Serial1.available() > 0)
    {
        String mensaje = Serial1.readStringUntil('\n');

        Serial.print("Recibido por Serial1: ");
        Serial.println(mensaje);
    }

    delay(1000);
}
```

El recorrido será:

```text
Arduino
   │
   ▼
Serial1
   │
   ▼
TX1 D18
   │
   │ cable
   ▼
RX1 D19
   │
   ▼
Serial1
   │
   ▼
Serial
   │
   ▼
Monitor serie
```

---

# 26. Resultado esperado

En el monitor serie deberíamos observar:

```text
Prueba de Serial1
Recibido por Serial1: Hola desde Serial1
Recibido por Serial1: Hola desde Serial1
Recibido por Serial1: Hola desde Serial1
...
```

Esto demuestra que:

```text
Serial1
```

puede transmitir y recibir correctamente.

Una vez terminada la prueba debemos retirar el puente entre D18 y D19.

---

# 27. Crear un puente entre dos puertos serie

Una de las herramientas más útiles para trabajar posteriormente con el ESP8266 será crear un puente:

```text
ORDENADOR
   │
   ▼
Serial
   │
   ▼
ARDUINO
   │
   ▼
Serial1
   │
   ▼
DISPOSITIVO
```

y también en sentido contrario:

```text
DISPOSITIVO
   │
   ▼
Serial1
   │
   ▼
ARDUINO
   │
   ▼
Serial
   │
   ▼
ORDENADOR
```

Arduino actuará como intermediario.

---

# 28. Programa puente serie

```cpp
#include <Arduino.h>

void setup()
{
    Serial.begin(9600);
    Serial1.begin(9600);

    Serial.println("Puente Serial <-> Serial1 iniciado");
}

void loop()
{
    if (Serial.available() > 0)
    {
        char dato = Serial.read();

        Serial1.write(dato);
    }

    if (Serial1.available() > 0)
    {
        char dato = Serial1.read();

        Serial.write(dato);
    }
}
```

Este pequeño programa será muy importante en la siguiente lección.

---

# 29. ¿Cómo funciona?

La primera parte:

```cpp
if (Serial.available() > 0)
{
    char dato = Serial.read();

    Serial1.write(dato);
}
```

realiza:

```text
ORDENADOR
   │
   ▼
Serial
   │
   ▼
Serial1
   │
   ▼
DISPOSITIVO
```

La segunda:

```cpp
if (Serial1.available() > 0)
{
    char dato = Serial1.read();

    Serial.write(dato);
}
```

realiza:

```text
DISPOSITIVO
   │
   ▼
Serial1
   │
   ▼
Serial
   │
   ▼
ORDENADOR
```

---

# 30. Serial.print() y Serial.write()

Hemos utilizado dos instrucciones que parecen similares:

```cpp
Serial.print();
```

y:

```cpp
Serial.write();
```

Para nuestras primeras prácticas podemos entenderlas de esta forma:

```text
print() → pensado principalmente para mostrar información

write() → envía directamente bytes o caracteres
```

En nuestro puente serie nos interesa copiar exactamente lo que llega de un puerto al otro, por lo que resulta natural utilizar:

```cpp
write()
```

---

# 31. Serial1 no aparece directamente en el monitor serie

Es importante comprender algo.

Cuando hacemos:

```cpp
Serial.println("Hola");
```

lo vemos en el monitor serie porque `Serial` está relacionado con la comunicación USB utilizada con el ordenador.

Pero:

```cpp
Serial1.println("Hola");
```

envía los datos por:

```text
TX1 → D18
```

No aparecerán automáticamente en el monitor serie.

Por eso utilizamos Arduino como puente:

```text
Serial1 → Serial → ordenador
```

---

# 32. Preparando el ESP8266

En la próxima lección sustituiremos el cable de loopback por el ESP8266.

La conexión conceptual será:

```text
ARDUINO MEGA             ESP8266

TX1 D18 ────────────────► RX

RX1 D19 ◄──────────────── TX

GND ───────────────────── GND
```

Pero antes de realizar esa conexión tendremos que estudiar algo muy importante:

```text
NIVELES DE TENSIÓN
```

Arduino Mega trabaja normalmente con señales lógicas de:

```text
5 V
```

mientras que el ESP8266 trabaja con:

```text
3,3 V
```

Por tanto **no conectaremos todavía directamente el ESP8266** hasta estudiar correctamente la adaptación de niveles.

---

# 33. Por qué hacemos esta lección antes de conectar Wi-Fi

Nuestro objetivo final puede representarse como:

```text
                         INTERNET
                            ▲
                            │
                           Wi-Fi
                            │
                        ESP8266
                            ▲
                            │
                           UART
                            │
                       ARDUINO MEGA
                       /     |      \
                      /      |       \
                     ▼       ▼        ▼
                  SENSOR   SENSOR   ACTUADOR
```

UART será el enlace entre:

```text
ARDUINO MEGA
```

y:

```text
ESP8266
```

Si no comprendemos esta comunicación será mucho más difícil localizar errores posteriormente.

---

# Práctica

## Ejercicio 1 — Recibir caracteres

Realiza un programa que reciba caracteres por el monitor serie.

Arduino debe responder:

```text
Has escrito: X
```

donde `X` sea el carácter introducido.

---

## Ejercicio 2 — Controlar un LED

Utiliza:

```text
1 → LED encendido

0 → LED apagado
```

Comprueba el funcionamiento desde el monitor serie.

---

## Ejercicio 3 — Nuevos comandos

Amplía el programa utilizando:

```text
E → encender

A → apagar
```

Debe funcionar tanto en mayúsculas como en minúsculas:

```text
E
e
A
a
```

---

## Ejercicio 4 — Probar Serial1

Realiza el puente temporal:

```text
D18 ↔ D19
```

y comprueba mediante el programa de loopback que los mensajes transmitidos por `Serial1` vuelven correctamente.

Retira posteriormente el cable.

---

## Ejercicio 5 — Identificar los puertos

Completa:

| Puerto  | RX | TX | Uso previsto |
| ------- | -: | -: | ------------ |
| Serial  |    |    |              |
| Serial1 |    |    |              |
| Serial2 |    |    |              |
| Serial3 |    |    |              |

---

# 34. Ejercicio de ampliación — Comandos de texto

Hasta ahora hemos utilizado caracteres:

```text
1

0

E

A
```

Pero posteriormente podremos enviar órdenes más completas:

```text
LED_ON

LED_OFF

SERVO_90

LEER_TEMP
```

Conceptualmente tendremos:

```text
ESP8266
   │
   │ "LED_ON"
   ▼
ARDUINO
   │
   ▼
INTERPRETAR COMANDO
   │
   ▼
ENCENDER LED
```

Esta será una de las bases de nuestro sistema IoT.

---

# 35. Protocolo de comunicación

Cuando dos dispositivos intercambian información debemos decidir cómo interpretar los mensajes.

Por ejemplo:

```text
LED_ON
```

podría significar:

```text
Encender LED
```

y:

```text
LED_OFF
```

podría significar:

```text
Apagar LED
```

También podemos imaginar:

```text
TEMP?
```

como petición:

```text
Dime la temperatura
```

y Arduino podría responder:

```text
TEMP:23.4
```

Estamos comenzando a definir un pequeño:

```text
PROTOCOLO DE COMUNICACIÓN
```

entre Arduino y el futuro ESP8266.

---

# 36. Nuestro futuro protocolo

Más adelante podremos utilizar mensajes como:

```text
ESP8266 → ARDUINO

LED_ON
LED_OFF
RGB:255,0,0
SERVO:90
TEMP?
DIST?
```

y respuestas como:

```text
ARDUINO → ESP8266

OK
TEMP:24.6
DIST:37
LIGHT:620
```

No implementaremos todavía todo este protocolo.

Lo construiremos progresivamente.

---

# 37. Lo que hemos aprendido

En esta lección hemos aprendido que Arduino Mega dispone de varios puertos serie:

```text
Serial
Serial1
Serial2
Serial3
```

Utilizaremos principalmente:

```text
Serial → ordenador

Serial1 → ESP8266
```

Recordemos:

```text
Serial1

RX1 → D19

TX1 → D18
```

También hemos aprendido la regla:

```text
TX ─────► RX

RX ◄───── TX
```

y la necesidad de compartir:

```text
GND
```

Nuestro proyecto comienza ahora a adoptar su arquitectura definitiva:

```text
ORDENADOR
    │
    │ USB
    ▼
 Serial
    │
    ▼
ARDUINO MEGA
    │
    │ Serial1 / UART
    ▼
ESP8266
    │
    │ Wi-Fi
    ▼
RED
```

En la próxima lección conectaremos por primera vez el **ESP8266**.

Antes estudiaremos cuidadosamente:

```text
3,3 V frente a 5 V
```

la alimentación del módulo, su patillaje y la comunicación serie.

El primer objetivo será conseguir que:

```text
ARDUINO MEGA
      │
      ▼
   ESP8266
      │
      ▼
RESPONDA A COMANDOS
```

y comprobar que ambos dispositivos pueden comunicarse correctamente.
