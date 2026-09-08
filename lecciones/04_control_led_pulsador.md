# Lección 4 — Control de un LED mediante un pulsador

## 1. Objetivos

En esta lección aprenderemos a:

* Combinar una entrada y una salida digital.
* Leer el estado de un pulsador.
* Controlar un LED dependiendo del estado del pulsador.
* Utilizar `if` y `else` para controlar componentes.
* Comprender el modelo entrada → procesamiento → salida.
* Detectar una pulsación y cambiar el estado de un LED.
* Introducir el concepto de rebote de un pulsador.

---

## 2. Material necesario

Necesitamos:

* Arduino Mega 2560 R3.
* Cable USB.
* Protoboard.
* 1 LED.
* 1 resistencia de aproximadamente 220 Ω.
* 1 pulsador.
* Cables Dupont.

Utilizaremos los mismos pines de las lecciones anteriores:

| Componente | Pin |
| ---------- | --: |
| Pulsador   |  D7 |
| LED        |  D8 |

---

## 3. ¿Qué vamos a construir?

En la lección 2 utilizamos una salida:

```text
ARDUINO
   │
   │ salida
   ▼
  LED
```

En la lección 3 utilizamos una entrada:

```text
PULSADOR
   │
   │ entrada
   ▼
ARDUINO
```

Ahora combinaremos ambos circuitos:

```text
PULSADOR
   │
   │ entrada
   ▼
ARDUINO MEGA
   │
   │ procesa
   ▼
  LED
```

El funcionamiento será:

```text
Pulsador sin pulsar
        │
        ▼
    LED apagado


Pulsador pulsado
        │
        ▼
    LED encendido
```

---

## 4. Conexión del pulsador

Continuaremos utilizando la resistencia interna del Arduino mediante:

```cpp
INPUT_PULLUP
```

Por tanto, conectaremos el pulsador entre:

```text
D7 ── PULSADOR ── GND
```

No necesitamos una resistencia externa para el pulsador.

Con `INPUT_PULLUP` debemos recordar:

| Pulsador   | D7     |
| ---------- | ------ |
| Sin pulsar | `HIGH` |
| Pulsado    | `LOW`  |

---

## 5. Conexión del LED

Utilizaremos el mismo circuito de la lección 2:

```text
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

Debemos respetar la polaridad del LED:

```text
Ánodo (+)   → hacia D8
Cátodo (-)  → hacia GND
```

---

## 6. Circuito completo

Nuestro montaje tendrá dos partes:

```text
              ARDUINO MEGA 2560
              
                   ┌───────┐
                   │       │
              D7 ──┤       ├── D8
               │   │       │    │
               │   └───────┘    │
               │                220 Ω
               │                 │
           PULSADOR             LED
               │                 │
               │                 │
              GND               GND
```

Tenemos:

```text
ENTRADA                     SALIDA

Pulsador                     LED
   │                          ▲
   │                          │
   └──── D7 → ARDUINO → D8 ───┘
```

---

## 7. Tabla de conexiones

### Pulsador

| Arduino | Pulsador             |
| ------- | -------------------- |
| D7      | Un lado del pulsador |
| GND     | Lado opuesto         |

### LED

| Arduino / componente | Conectar a           |
| -------------------- | -------------------- |
| D8                   | Resistencia de 220 Ω |
| Resistencia          | Ánodo del LED        |
| Cátodo del LED       | GND                  |

Podemos utilizar cualquiera de los pines `GND` disponibles en el Arduino Mega.

---

## 8. Definir los pines

En el programa utilizaremos:

```cpp
const int PULSADOR = 7;
const int LED = 8;
```

De esta forma no tendremos que utilizar directamente los números `7` y `8` durante todo el programa.

Por ejemplo:

```cpp
digitalRead(PULSADOR);
```

es más fácil de interpretar que:

```cpp
digitalRead(7);
```

---

## 9. Configurar entrada y salida

En `setup()` configuramos ambos componentes:

```cpp
pinMode(PULSADOR, INPUT_PULLUP);
pinMode(LED, OUTPUT);
```

Tenemos por tanto:

```text
D7 → ENTRADA

D8 → SALIDA
```

---

## 10. Leer el pulsador

Dentro de `loop()` consultaremos continuamente el estado del pulsador:

```cpp
int estadoPulsador = digitalRead(PULSADOR);
```

La variable puede contener:

```text
HIGH → no pulsado

LOW  → pulsado
```

---

## 11. Tomar una decisión

Ahora utilizaremos:

```cpp
if
```

para decidir qué hacer.

Si el pulsador está presionado:

```cpp
if (estadoPulsador == LOW)
{
    digitalWrite(LED, HIGH);
}
```

encendemos el LED.

En caso contrario:

```cpp
else
{
    digitalWrite(LED, LOW);
}
```

lo apagamos.

---

## 12. Programa completo

Abrimos:

```text
src/main.cpp
```

y escribimos:

```cpp
#include <Arduino.h>

const int PULSADOR = 7;
const int LED = 8;

void setup()
{
    pinMode(PULSADOR, INPUT_PULLUP);
    pinMode(LED, OUTPUT);
}

void loop()
{
    int estadoPulsador = digitalRead(PULSADOR);

    if (estadoPulsador == LOW)
    {
        digitalWrite(LED, HIGH);
    }
    else
    {
        digitalWrite(LED, LOW);
    }
}
```

Compilamos utilizando:

```text
Build
```

y cargamos el programa mediante:

```text
Upload
```

---

## 13. Probar el circuito

Después de cargar el programa:

### Sin pulsar

El pulsador se encuentra en:

```text
HIGH
```

Arduino ejecuta:

```cpp
digitalWrite(LED, LOW);
```

y obtenemos:

```text
LED APAGADO
```

### Al pulsar

La entrada cambia a:

```text
LOW
```

Arduino ejecuta:

```cpp
digitalWrite(LED, HIGH);
```

y obtenemos:

```text
LED ENCENDIDO
```

Al soltar el pulsador, el LED vuelve a apagarse.

---

## 14. Funcionamiento completo

Podemos representar el programa mediante:

```text
        INICIO
          │
          ▼
Configurar D7 como entrada
          │
          ▼
Configurar D8 como salida
          │
          ▼
    Leer pulsador
          │
          ▼
    ¿D7 es LOW?
       ┌──┴──┐
       │     │
      SÍ     NO
       │     │
       ▼     ▼
 Encender   Apagar
    LED      LED
       │     │
       └──┬──┘
          │
          ▼
   Leer nuevamente
     el pulsador
```

Arduino realiza este proceso continuamente.

---

## 15. Entrada, procesamiento y salida

Esta práctica representa una estructura fundamental de los sistemas electrónicos:

```text
ENTRADA
   │
   ▼
PULSADOR
   │
   ▼
ARDUINO
   │
   │ PROCESAMIENTO
   ▼
¿Está pulsado?
   │
   ▼
SALIDA
   │
   ▼
  LED
```

Podemos resumirlo como:

```text
ENTRADA → PROCESAMIENTO → SALIDA
```

Este modelo aparecerá constantemente en las próximas lecciones.

Por ejemplo:

```text
Sensor de luz → Arduino → LED

Sensor de distancia → Arduino → Zumbador

Temperatura → Arduino → Pantalla

Página web → Arduino → Relé

Sensor → Arduino → InfluxDB
```

---

## 16. Añadir el monitor serie

Podemos utilizar el monitor serie para observar las decisiones que toma Arduino.

Modificamos el programa:

```cpp
#include <Arduino.h>

const int PULSADOR = 7;
const int LED = 8;

void setup()
{
    Serial.begin(9600);

    pinMode(PULSADOR, INPUT_PULLUP);
    pinMode(LED, OUTPUT);

    Serial.println("Control LED mediante pulsador");
}

void loop()
{
    int estadoPulsador = digitalRead(PULSADOR);

    if (estadoPulsador == LOW)
    {
        digitalWrite(LED, HIGH);

        Serial.println("Pulsador activado - LED encendido");
    }
    else
    {
        digitalWrite(LED, LOW);

        Serial.println("Pulsador libre - LED apagado");
    }

    delay(200);
}
```

En el monitor serie podremos observar:

```text
Pulsador libre - LED apagado
Pulsador libre - LED apagado
Pulsador activado - LED encendido
Pulsador activado - LED encendido
Pulsador libre - LED apagado
```

---

# Práctica

## Ejercicio 1 — Funcionamiento básico

Monta el circuito y carga el programa.

Comprueba:

```text
Sin pulsar → LED apagado

Pulsado    → LED encendido
```

Mantén pulsado el botón durante varios segundos y comprueba que el LED permanece encendido.

---

## Ejercicio 2 — Funcionamiento inverso

Modifica el programa para conseguir:

```text
Sin pulsar → LED encendido

Pulsado    → LED apagado
```

No debes modificar ninguna conexión física.

Solamente debes cambiar el programa.

---

## Ejercicio 3 — LED intermitente mientras pulsamos

Modifica el programa para conseguir:

```text
SIN PULSAR

LED apagado


PULSADO

LED encendido
     ↓
500 ms
     ↓
LED apagado
     ↓
500 ms
     ↓
repetir
```

Mientras mantengamos presionado el botón, el LED debe parpadear.

Al soltarlo debe quedar apagado.

---

## Ejercicio 4 — Dos destellos al pulsar

Intenta conseguir que, mientras el pulsador esté presionado, el LED realice:

```text
ON
 │
200 ms
 │
OFF
 │
200 ms
 │
ON
 │
200 ms
 │
OFF
 │
1000 ms
 │
repetir
```

---

# 17. Un comportamiento diferente: pulsar para cambiar

Hasta ahora el funcionamiento es:

```text
Mantengo pulsado → LED encendido

Suelto → LED apagado
```

Pero podemos querer algo diferente:

```text
Primera pulsación → LED encendido

Segunda pulsación → LED apagado

Tercera pulsación → LED encendido

Cuarta pulsación → LED apagado
```

Es decir, cada pulsación cambia el estado del LED.

Para conseguirlo Arduino necesita **recordar** el estado anterior.

---

## 18. Una variable para recordar el estado

Podemos crear:

```cpp
bool estadoLED = false;
```

Una variable de tipo `bool` solamente puede tener dos estados:

```text
true
false
```

Podemos utilizarlos como:

```text
false → LED apagado

true  → LED encendido
```

Para cambiar de un estado al contrario podemos utilizar:

```cpp
estadoLED = !estadoLED;
```

El símbolo:

```text
!
```

significa negación.

Por tanto:

```text
false → true

true → false
```

---

## 19. Detectar una pulsación

No debemos cambiar el estado continuamente mientras el usuario mantiene presionado el botón.

Queremos detectar únicamente el momento en que pasa de:

```text
HIGH → LOW
```

Es decir:

```text
       AQUÍ
         ↓
HIGH ─────┐
          │
          └──────── LOW
```

Para ello necesitamos recordar también el estado anterior del pulsador:

```cpp
int estadoAnterior = HIGH;
```

Después podemos comprobar:

```cpp
if (estadoAnterior == HIGH && estadoActual == LOW)
```

Esto significa:

```text
Antes estaba libre

Y

Ahora está pulsado
```

Por tanto, acabamos de detectar una nueva pulsación.

---

## 20. Programa pulsar para encender y apagar

Podemos realizarlo de la siguiente manera:

```cpp
#include <Arduino.h>

const int PULSADOR = 7;
const int LED = 8;

bool estadoLED = false;
int estadoAnterior = HIGH;

void setup()
{
    pinMode(PULSADOR, INPUT_PULLUP);
    pinMode(LED, OUTPUT);
}

void loop()
{
    int estadoActual = digitalRead(PULSADOR);

    if (estadoAnterior == HIGH && estadoActual == LOW)
    {
        estadoLED = !estadoLED;

        digitalWrite(LED, estadoLED);

        delay(50);
    }

    estadoAnterior = estadoActual;
}
```

Ahora el funcionamiento debe ser:

```text
PULSACIÓN 1
    │
    ▼
LED ON

PULSACIÓN 2
    │
    ▼
LED OFF

PULSACIÓN 3
    │
    ▼
LED ON

PULSACIÓN 4
    │
    ▼
LED OFF
```

---

## 21. ¿Por qué aparece delay(50)?

En este programa encontramos:

```cpp
delay(50);
```

No lo utilizamos para controlar el LED.

Lo utilizamos para reducir los efectos del **rebote mecánico del pulsador**.

Cuando pulsamos físicamente un botón, sus contactos pueden producir rápidamente varios cambios:

```text
HIGH ──────┐
           └─┐ ┌─┐
             │ │ │
             └─┘ └──── LOW
```

Arduino trabaja suficientemente rápido como para detectar algunos de esos cambios como varias pulsaciones.

La pequeña espera:

```cpp
delay(50);
```

ayuda a evitar este problema en prácticas sencillas.

Este procedimiento se denomina **antirrebote** o *debouncing*.

---

# Práctica de ampliación

## Ejercicio 5 — Pulsador como interruptor

Carga el programa anterior.

Comprueba que:

```text
Pulsar y soltar → LED encendido

Pulsar y soltar → LED apagado

Pulsar y soltar → LED encendido
```

Observa que ahora no es necesario mantener el pulsador presionado.

---

## Ejercicio 6 — Añadir mensajes

Añade comunicación serie para que cada vez que cambie el LED aparezca:

```text
LED ENCENDIDO
```

o:

```text
LED APAGADO
```

No queremos mensajes continuos.

Debe aparecer **un único mensaje por cada pulsación**.

---

## 22. Lo que hemos aprendido

En esta lección hemos combinado por primera vez:

```text
ENTRADA + PROCESAMIENTO + SALIDA
```

Nuestro circuito es:

```text
PULSADOR
   │
   ▼
  D7
   │
   ▼
ARDUINO MEGA
   │
   ▼
  D8
   │
   ▼
  LED
```

Hemos utilizado conjuntamente:

```cpp
pinMode()
digitalRead()
digitalWrite()
if
else
```

También hemos introducido:

```cpp
bool
```

y el concepto de detectar un **cambio de estado**.

Esta última idea será especialmente importante más adelante cuando trabajemos con sensores, comunicaciones y aplicaciones web.

En la siguiente lección aprenderemos que las salidas no tienen por qué limitarse únicamente a:

```text
ENCENDIDO / APAGADO
```

Utilizaremos una salida **PWM** para controlar gradualmente la intensidad luminosa de un LED.
