# Lección 8 — Control de un LED RGB

## 1. Objetivos

En esta lección aprenderemos a:

* Comprender el funcionamiento de un LED RGB.
* Identificar sus cuatro terminales.
* Controlar tres salidas PWM simultáneamente.
* Generar los colores rojo, verde y azul.
* Obtener nuevos colores mediante la mezcla de los colores básicos.
* Crear una función para simplificar nuestros programas.
* Utilizar valores PWM entre 0 y 255 para controlar cada componente de color.

---

## 2. Material necesario

Necesitamos:

* Arduino Mega 2560 R3.
* Cable USB.
* Protoboard.
* 1 LED RGB.
* 3 resistencias de aproximadamente 220 Ω.
* Cables Dupont.

---

# 3. ¿Qué es un LED RGB?

Un LED RGB contiene realmente tres LED dentro del mismo encapsulado:

```text
R → Red   → Rojo

G → Green → Verde

B → Blue  → Azul
```

Por tanto, dentro del componente tenemos:

```text
        LED RGB
     ┌───────────┐
     │           │
     │   ROJO    │
     │   VERDE   │
     │   AZUL    │
     │           │
     └───────────┘
```

Controlando independientemente la intensidad de estos tres colores podemos obtener muchos colores diferentes.

---

# 4. Mezcla aditiva de colores

En iluminación se utiliza la mezcla de los colores:

```text
ROJO + VERDE + AZUL
```

conocida como:

```text
RGB
```

Algunas combinaciones sencillas son:

```text
ROJO + VERDE = AMARILLO
```

```text
ROJO + AZUL = MAGENTA
```

```text
VERDE + AZUL = CIAN
```

y:

```text
ROJO + VERDE + AZUL = BLANCO
```

Por tanto:

```text
              ROJO
             /    \
            /      \
     MAGENTA        AMARILLO
          /          \
         /            \
      AZUL ── CIAN ── VERDE
```

---

# 5. Terminales del LED RGB

El LED RGB incluido en el kit SunFounder es de **cátodo común**.

Tiene cuatro terminales.

El terminal más largo corresponde al terminal común:

```text
GND
```

Los otros tres corresponden a:

```text
R → Rojo
G → Verde
B → Azul
```

Observando el LED según la disposición utilizada por el fabricante, encontramos:

```text
R   GND   G   B
│    │    │   │
│    │    │   │
└────┴────┴───┘
     LED RGB
```

El terminal:

```text
GND
```

es normalmente el más largo.

---

# 6. Cátodo común

Nuestro LED es de:

```text
CÁTODO COMÚN
```

Esto significa que los tres LED internos comparten la conexión negativa.

Podemos representarlo de forma simplificada:

```text
     ROJO
D9 ──►|──┐
          │
     VERDE│
D10 ─►|───┤
          │
     AZUL │
D11 ─►|───┤
          │
          ▼
         GND
```

Por tanto, el terminal común del LED se conecta a:

```text
GND
```

---

# 7. ¿Por qué necesitamos tres resistencias?

Cada color del LED es realmente un LED independiente.

Por este motivo utilizaremos una resistencia para cada canal:

```text
D9  ── 220 Ω ── ROJO

D10 ── 220 Ω ── VERDE

D11 ── 220 Ω ── AZUL
```

Las resistencias limitan la corriente y protegen los LED y las salidas del Arduino.

---

# 8. Pines que utilizaremos

Utilizaremos tres pines PWM del Arduino Mega:

| Color | Pin Arduino |
| ----- | ----------: |
| Rojo  |          D9 |
| Verde |         D10 |
| Azul  |         D11 |

Los definiremos:

```cpp
const int LED_ROJO = 9;
const int LED_VERDE = 10;
const int LED_AZUL = 11;
```

Los tres pines permiten utilizar:

```cpp
analogWrite();
```

---

# 9. Conexiones

Realizaremos:

```text
D9 ─── 220 Ω ─── R

D10 ── 220 Ω ─── G

D11 ── 220 Ω ─── B

GND ───────────── GND del LED RGB
```

---

## Tabla de conexiones

| Arduino Mega | Componente                 |
| ------------ | -------------------------- |
| D9           | Resistencia 220 Ω → R      |
| D10          | Resistencia 220 Ω → G      |
| D11          | Resistencia 220 Ω → B      |
| GND          | Terminal común del LED RGB |

Es importante comprobar cuidadosamente los terminales antes de conectar la alimentación.

---

# 10. Circuito completo

Podemos representar nuestro circuito como:

```text
             ARDUINO MEGA 2560

 D9 ───── 220 Ω ───────── ROJO
                              \
 D10 ──── 220 Ω ───────── VERDE ── LED RGB
                              /
 D11 ──── 220 Ω ───────── AZUL
                              │
                              │
                             GND
```

---

# 11. Primer programa: color rojo

Comenzaremos encendiendo solamente el LED rojo.

```cpp
#include <Arduino.h>

const int LED_ROJO = 9;
const int LED_VERDE = 10;
const int LED_AZUL = 11;

void setup()
{
    pinMode(LED_ROJO, OUTPUT);
    pinMode(LED_VERDE, OUTPUT);
    pinMode(LED_AZUL, OUTPUT);
}

void loop()
{
    analogWrite(LED_ROJO, 255);
    analogWrite(LED_VERDE, 0);
    analogWrite(LED_AZUL, 0);
}
```

Deberíamos obtener:

```text
ROJO = 255

VERDE = 0

AZUL = 0
```

Resultado:

```text
LED ROJO
```

---

# 12. Encender el color verde

Podemos modificar:

```cpp
analogWrite(LED_ROJO, 0);
analogWrite(LED_VERDE, 255);
analogWrite(LED_AZUL, 0);
```

Resultado:

```text
LED VERDE
```

---

# 13. Encender el color azul

Utilizamos:

```cpp
analogWrite(LED_ROJO, 0);
analogWrite(LED_VERDE, 0);
analogWrite(LED_AZUL, 255);
```

Resultado:

```text
LED AZUL
```

---

# 14. Mezclar colores

Ahora podemos activar varios canales simultáneamente.

Por ejemplo:

```cpp
analogWrite(LED_ROJO, 255);
analogWrite(LED_VERDE, 255);
analogWrite(LED_AZUL, 0);
```

Tenemos:

```text
ROJO + VERDE
```

y obtenemos aproximadamente:

```text
AMARILLO
```

---

## Magenta

Utilizamos:

```cpp
analogWrite(LED_ROJO, 255);
analogWrite(LED_VERDE, 0);
analogWrite(LED_AZUL, 255);
```

Resultado:

```text
ROJO + AZUL = MAGENTA
```

---

## Cian

Utilizamos:

```cpp
analogWrite(LED_ROJO, 0);
analogWrite(LED_VERDE, 255);
analogWrite(LED_AZUL, 255);
```

Resultado:

```text
VERDE + AZUL = CIAN
```

---

## Blanco

Activamos los tres canales:

```cpp
analogWrite(LED_ROJO, 255);
analogWrite(LED_VERDE, 255);
analogWrite(LED_AZUL, 255);
```

Resultado aproximado:

```text
BLANCO
```

---

## Apagado

Utilizamos:

```cpp
analogWrite(LED_ROJO, 0);
analogWrite(LED_VERDE, 0);
analogWrite(LED_AZUL, 0);
```

y el LED queda apagado.

---

# 15. Tabla básica de colores

Podemos utilizar inicialmente estos valores:

| Color    | Rojo | Verde | Azul |
| -------- | ---: | ----: | ---: |
| Apagado  |    0 |     0 |    0 |
| Rojo     |  255 |     0 |    0 |
| Verde    |    0 |   255 |    0 |
| Azul     |    0 |     0 |  255 |
| Amarillo |  255 |   255 |    0 |
| Magenta  |  255 |     0 |  255 |
| Cian     |    0 |   255 |  255 |
| Blanco   |  255 |   255 |  255 |

Observa que los tres valores siguen el orden:

```text
R, G, B
```

---

# 16. Crear una función para seleccionar colores

Estamos repitiendo continuamente:

```cpp
analogWrite(LED_ROJO, ...);
analogWrite(LED_VERDE, ...);
analogWrite(LED_AZUL, ...);
```

Podemos simplificar nuestro programa creando una función.

La llamaremos:

```cpp
color()
```

Su código será:

```cpp
void color(int rojo, int verde, int azul)
{
    analogWrite(LED_ROJO, rojo);
    analogWrite(LED_VERDE, verde);
    analogWrite(LED_AZUL, azul);
}
```

Ahora podremos escribir simplemente:

```cpp
color(255, 0, 0);
```

para obtener rojo.

O:

```cpp
color(0, 255, 0);
```

para obtener verde.

---

# 17. Programa completo de cambio de colores

Abrimos:

```text
src/main.cpp
```

y escribimos:

```cpp
#include <Arduino.h>

const int LED_ROJO = 9;
const int LED_VERDE = 10;
const int LED_AZUL = 11;

void color(int rojo, int verde, int azul)
{
    analogWrite(LED_ROJO, rojo);
    analogWrite(LED_VERDE, verde);
    analogWrite(LED_AZUL, azul);
}

void setup()
{
    pinMode(LED_ROJO, OUTPUT);
    pinMode(LED_VERDE, OUTPUT);
    pinMode(LED_AZUL, OUTPUT);
}

void loop()
{
    // Rojo
    color(255, 0, 0);
    delay(1000);

    // Verde
    color(0, 255, 0);
    delay(1000);

    // Azul
    color(0, 0, 255);
    delay(1000);

    // Amarillo
    color(255, 255, 0);
    delay(1000);

    // Magenta
    color(255, 0, 255);
    delay(1000);

    // Cian
    color(0, 255, 255);
    delay(1000);

    // Blanco
    color(255, 255, 255);
    delay(1000);

    // Apagado
    color(0, 0, 0);
    delay(1000);
}
```

Compilamos mediante:

```text
Build
```

y cargamos mediante:

```text
Upload
```

El LED irá cambiando de color aproximadamente cada segundo.

---

# 18. ¿Cómo funciona la función color()?

Cuando escribimos:

```cpp
color(255, 0, 255);
```

los parámetros reciben:

```text
rojo  = 255

verde = 0

azul  = 255
```

La función ejecuta:

```cpp
analogWrite(LED_ROJO, 255);
analogWrite(LED_VERDE, 0);
analogWrite(LED_AZUL, 255);
```

Resultado:

```text
MAGENTA
```

Por tanto podemos pensar en:

```text
color(R, G, B)
```

---

# 19. No solamente podemos utilizar 0 y 255

Como estamos utilizando PWM, cada canal admite valores entre:

```text
0 y 255
```

Por ejemplo:

```cpp
color(255, 100, 0);
```

mezcla:

```text
Rojo  → 255

Verde → 100

Azul  → 0
```

y puede producir un tono anaranjado.

Podemos probar:

```cpp
color(255, 50, 0);
```

```cpp
color(150, 0, 255);
```

```cpp
color(0, 100, 255);
```

```cpp
color(100, 255, 50);
```

Cada combinación genera un color diferente.

---

# 20. RGB y los colores utilizados en informática

El sistema que estamos utilizando es el mismo concepto de representación RGB que encontramos en:

```text
Monitores

Televisores

Pantallas de teléfonos

Diseño web

Programas gráficos
```

Por ejemplo, un color puede representarse mediante:

```text
RGB(255, 0, 0)
```

que significa:

```text
Rojo = 255
Verde = 0
Azul = 0
```

Resultado:

```text
ROJO
```

Otro ejemplo:

```text
RGB(255, 255, 0)
```

produce amarillo.

Nuestro Arduino utiliza exactamente estos tres valores para controlar el LED.

---

# 21. Utilizar el monitor serie

Podemos indicar qué color estamos mostrando.

Por ejemplo:

```cpp
Serial.println("ROJO");
color(255, 0, 0);
delay(1000);
```

Después:

```cpp
Serial.println("VERDE");
color(0, 255, 0);
delay(1000);
```

Para ello debemos añadir en `setup()`:

```cpp
Serial.begin(9600);
```

---

# 22. Programa con monitor serie

Podemos utilizar:

```cpp
#include <Arduino.h>

const int LED_ROJO = 9;
const int LED_VERDE = 10;
const int LED_AZUL = 11;

void color(int rojo, int verde, int azul)
{
    analogWrite(LED_ROJO, rojo);
    analogWrite(LED_VERDE, verde);
    analogWrite(LED_AZUL, azul);
}

void setup()
{
    Serial.begin(9600);

    pinMode(LED_ROJO, OUTPUT);
    pinMode(LED_VERDE, OUTPUT);
    pinMode(LED_AZUL, OUTPUT);

    Serial.println("Prueba LED RGB");
}

void loop()
{
    Serial.println("ROJO");
    color(255, 0, 0);
    delay(1000);

    Serial.println("VERDE");
    color(0, 255, 0);
    delay(1000);

    Serial.println("AZUL");
    color(0, 0, 255);
    delay(1000);

    Serial.println("AMARILLO");
    color(255, 255, 0);
    delay(1000);

    Serial.println("MAGENTA");
    color(255, 0, 255);
    delay(1000);

    Serial.println("CIAN");
    color(0, 255, 255);
    delay(1000);

    Serial.println("BLANCO");
    color(255, 255, 255);
    delay(1000);

    Serial.println("APAGADO");
    color(0, 0, 0);
    delay(1000);
}
```

---

# Práctica

## Ejercicio 1 — Colores básicos

Comprueba que puedes producir:

```text
ROJO

VERDE

AZUL
```

utilizando:

```cpp
color();
```

---

## Ejercicio 2 — Colores secundarios

Genera:

```text
AMARILLO

MAGENTA

CIAN
```

sin consultar el programa anterior.

Recuerda:

```text
Rojo + Verde

Rojo + Azul

Verde + Azul
```

---

## Ejercicio 3 — Crear nuevos colores

Experimenta con diferentes valores.

Por ejemplo:

```cpp
color(255, 50, 0);
```

```cpp
color(255, 100, 0);
```

```cpp
color(150, 0, 255);
```

```cpp
color(0, 100, 255);
```

Observa los colores obtenidos.

---

## Ejercicio 4 — Semáforo

Utiliza el LED RGB para simular un semáforo.

La secuencia debe ser:

```text
ROJO
 │
 │ 5 segundos
 ▼
VERDE
 │
 │ 5 segundos
 ▼
AMARILLO
 │
 │ 2 segundos
 ▼
ROJO
```

y debe repetirse continuamente.

Intenta realizarlo utilizando:

```cpp
color();
```

---

# 23. Ejercicio de ampliación — Control desde el monitor serie

Podemos controlar el LED escribiendo comandos desde el ordenador.

Queremos conseguir:

```text
Usuario escribe:

R
 │
 ▼
LED rojo


Usuario escribe:

V
 │
 ▼
LED verde


Usuario escribe:

A
 │
 ▼
LED azul
```

Un posible programa es:

```cpp
#include <Arduino.h>

const int LED_ROJO = 9;
const int LED_VERDE = 10;
const int LED_AZUL = 11;

void color(int rojo, int verde, int azul)
{
    analogWrite(LED_ROJO, rojo);
    analogWrite(LED_VERDE, verde);
    analogWrite(LED_AZUL, azul);
}

void setup()
{
    Serial.begin(9600);

    pinMode(LED_ROJO, OUTPUT);
    pinMode(LED_VERDE, OUTPUT);
    pinMode(LED_AZUL, OUTPUT);

    color(0, 0, 0);

    Serial.println("Control LED RGB");
    Serial.println("R = rojo");
    Serial.println("V = verde");
    Serial.println("A = azul");
    Serial.println("B = blanco");
    Serial.println("X = apagar");
}

void loop()
{
    if (Serial.available() > 0)
    {
        char comando = Serial.read();

        if (comando == 'R' || comando == 'r')
        {
            color(255, 0, 0);
            Serial.println("ROJO");
        }
        else if (comando == 'V' || comando == 'v')
        {
            color(0, 255, 0);
            Serial.println("VERDE");
        }
        else if (comando == 'A' || comando == 'a')
        {
            color(0, 0, 255);
            Serial.println("AZUL");
        }
        else if (comando == 'B' || comando == 'b')
        {
            color(255, 255, 255);
            Serial.println("BLANCO");
        }
        else if (comando == 'X' || comando == 'x')
        {
            color(0, 0, 0);
            Serial.println("APAGADO");
        }
    }
}
```

Ahora el ordenador puede controlar una salida física del Arduino.

Nuestro sistema empieza a tener esta estructura:

```text
USUARIO
   │
   ▼
MONITOR SERIE
   │
   ▼
COMANDO
   │
   ▼
ARDUINO
   │
   ▼
LED RGB
```

Este concepto será muy importante más adelante.

En el proyecto final sustituiremos:

```text
MONITOR SERIE
```

por:

```text
PÁGINA WEB
```

y podremos hacer algo parecido a:

```text
┌─────────────────────────┐
│      CONTROL RGB        │
│                         │
│ [ ROJO ]    [ VERDE ]   │
│                         │
│ [ AZUL ]    [ BLANCO ]  │
│                         │
│       [ APAGAR ]        │
└─────────────────────────┘
```

Los botones enviarán órdenes al sistema a través de Wi-Fi.

---

# 24. Ejercicio de ampliación — Potenciómetro y un canal RGB

Podemos recuperar el potenciómetro de la lección anterior.

Conectamos:

```text
Potenciómetro → A0
```

y utilizamos su valor para controlar solamente el componente rojo.

```cpp
#include <Arduino.h>

const int POTENCIOMETRO = A0;

const int LED_ROJO = 9;
const int LED_VERDE = 10;
const int LED_AZUL = 11;

void setup()
{
    pinMode(LED_ROJO, OUTPUT);
    pinMode(LED_VERDE, OUTPUT);
    pinMode(LED_AZUL, OUTPUT);
}

void loop()
{
    int valor = analogRead(POTENCIOMETRO);

    int intensidad = map(valor, 0, 1023, 0, 255);

    analogWrite(LED_ROJO, intensidad);
    analogWrite(LED_VERDE, 0);
    analogWrite(LED_AZUL, 0);
}
```

Ahora podemos regular la intensidad del color rojo mediante el potenciómetro.

Tenemos:

```text
POTENCIÓMETRO
      │
      ▼
     A0
      │
      ▼
 analogRead()
      │
      ▼
   0 - 1023
      │
      ▼
    map()
      │
      ▼
    0 - 255
      │
      ▼
     PWM
      │
      ▼
LED RGB - ROJO
```

Aquí estamos reutilizando conceptos de varias lecciones anteriores.

---

# 25. Si los colores no coinciden

Si al ejecutar:

```cpp
color(255, 0, 0);
```

no obtenemos rojo, probablemente hemos identificado incorrectamente los terminales del LED RGB.

Debemos revisar el montaje.

En el LED del kit, el terminal más largo corresponde al común y debe estar conectado a:

```text
GND
```

Después debemos comprobar individualmente los tres canales.

Podemos probar:

```cpp
color(255, 0, 0);
```

Después:

```cpp
color(0, 255, 0);
```

Y finalmente:

```cpp
color(0, 0, 255);
```

Si los colores aparecen intercambiados, debemos revisar qué terminal del LED hemos conectado a D9, D10 y D11.

---

# 26. Si el LED permanece apagado

Debemos comprobar:

1. Que el terminal común está conectado a `GND`.
2. Que estamos utilizando tres pines PWM.
3. Que las resistencias están correctamente conectadas.
4. Que el LED está correctamente colocado en la protoboard.
5. Que PlatformIO ha cargado correctamente el programa.

La configuración debe ser:

```text
R → D9

G → D10

B → D11

Común → GND
```

---

# 27. Entrada, procesamiento y salida

Aunque en esta práctica no utilizamos inicialmente ningún sensor, Arduino ya está procesando tres señales independientes:

```text
                  ┌── PWM ROJO
                  │
PROGRAMA → ARDUINO├── PWM VERDE
                  │
                  └── PWM AZUL
```

Estas señales terminan combinándose:

```text
PWM ROJO ──┐
           │
PWM VERDE ─┼──→ LED RGB ──→ COLOR
           │
PWM AZUL ──┘
```

---

# 28. Lo que hemos aprendido

En esta lección hemos pasado de controlar un único LED:

```text
Arduino → LED
```

a controlar tres canales:

```text
           ┌── ROJO
           │
Arduino ───┼── VERDE
           │
           └── AZUL
```

Hemos reutilizado:

```cpp
pinMode()
analogWrite()
delay()
```

y hemos creado nuestra primera función específica:

```cpp
void color(int rojo, int verde, int azul)
```

Ahora podemos seleccionar fácilmente un color mediante:

```cpp
color(255, 0, 0);
```

```cpp
color(0, 255, 0);
```

```cpp
color(0, 0, 255);
```

o combinar intensidades:

```cpp
color(255, 100, 20);
```

También hemos comprobado que los valores RGB utilizados por Arduino siguen la misma idea que encontramos habitualmente en informática:

```text
RGB(R, G, B)
```

Nuestro sistema ha evolucionado hasta:

```text
PROGRAMA
   │
   ▼
ARDUINO MEGA
   │
   ├──── PWM D9  → ROJO
   │
   ├──── PWM D10 → VERDE
   │
   └──── PWM D11 → AZUL
                   │
                   ▼
                 COLOR
```

En la siguiente lección podemos introducir un **zumbador (buzzer)** y comenzar a trabajar con sonido, tonos y frecuencias.
