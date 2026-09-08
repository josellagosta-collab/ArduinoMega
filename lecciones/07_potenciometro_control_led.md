# Lección 7 — Control del brillo de un LED con un potenciómetro

## 1. Objetivos

En esta lección aprenderemos a:

* Leer una entrada analógica con `analogRead()`.
* Utilizar un potenciómetro como dispositivo de entrada.
* Recordar el rango de lectura analógica del Arduino Mega.
* Convertir valores entre diferentes escalas.
* Utilizar la función `map()`.
* Controlar el brillo de un LED mediante PWM.
* Integrar una entrada analógica con una salida PWM.

---

## 2. Material necesario

Necesitamos:

* Arduino Mega 2560 R3.
* Cable USB.
* Protoboard.
* 1 potenciómetro.
* 1 LED.
* 1 resistencia de aproximadamente 220 Ω.
* Cables Dupont.

---

## 3. ¿Qué vamos a construir?

Hasta ahora hemos trabajado por separado con entradas y salidas.

En esta práctica construiremos:

```text
POTENCIÓMETRO
      │
      │ entrada analógica
      ▼
ARDUINO MEGA
      │
      │ procesamiento
      ▼
    PWM D9
      │
      ▼
     LED
```

El objetivo será:

```text
Girar hacia un lado
        │
        ▼
LED con poco brillo


Girar progresivamente
        │
        ▼
Aumenta el brillo


Girar al máximo
        │
        ▼
LED con brillo máximo
```

---

## 4. El potenciómetro

Un potenciómetro es una resistencia variable.

Normalmente dispone de tres terminales:

```text
Terminal 1
    │
    │
Terminal central
    │
    │
Terminal 3
```

Los terminales exteriores se conectarán a:

```text
5V
```

y:

```text
GND
```

El terminal central proporciona una tensión variable.

Dependiendo de la posición del mando tendremos un valor entre aproximadamente:

```text
0 V
```

y:

```text
5 V
```

---

## 5. Conexión del potenciómetro

Utilizaremos la entrada analógica:

```text
A0
```

Las conexiones serán:

| Potenciómetro     | Arduino Mega |
| ----------------- | ------------ |
| Terminal exterior | 5V           |
| Terminal central  | A0           |
| Terminal exterior | GND          |

El montaje puede representarse así:

```text
          POTENCIÓMETRO

5V ─────────┐
            │
         ┌──┴──┐
         │     │
         │  ◉  │
         │     │
         └──┬──┘
            │
            ├──────── A0
            │
GND ────────┘
```

Si intercambiamos los dos terminales exteriores, el potenciómetro funcionará igualmente, pero el sentido de giro quedará invertido.

---

## 6. Conexión del LED

Utilizaremos nuevamente el pin PWM:

```text
D9
```

El circuito será:

```text
D9
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

---

## 7. Circuito completo

Nuestro sistema queda:

```text
             ARDUINO MEGA 2560

          5V
           │
           ▼
     POTENCIÓMETRO
           │
           ├──────── A0
           │
          GND


          D9
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

---

## 8. Leer el potenciómetro

Para leer una entrada analógica utilizamos:

```cpp
analogRead();
```

Por ejemplo:

```cpp
int valorPotenciometro = analogRead(A0);
```

Arduino Mega convierte la tensión de entrada en un valor numérico.

El rango es:

```text
0 ───────────────────── 1023
│                         │
0 V                     5 V aprox.
```

Por tanto:

```text
Potenciómetro al mínimo
        ↓
Valor cercano a 0
```

```text
Potenciómetro a la mitad
        ↓
Valor cercano a 512
```

```text
Potenciómetro al máximo
        ↓
Valor cercano a 1023
```

---

## 9. Primer problema: los rangos son diferentes

La entrada analógica nos proporciona:

```text
0 - 1023
```

Pero `analogWrite()` utiliza:

```text
0 - 255
```

Por tanto no podemos utilizar directamente el mismo valor.

Tenemos:

```text
analogRead()

0 ────────────────── 1023
```

y necesitamos:

```text
analogWrite()

0 ─────────────────── 255
```

Tenemos que convertir un rango en otro.

---

## 10. La función map()

Arduino dispone de la función:

```cpp
map();
```

que permite convertir un valor de un rango a otro.

Utilizaremos:

```cpp
int brillo = map(valorPotenciometro, 0, 1023, 0, 255);
```

Podemos interpretarlo como:

```text
Entrada                Salida

0      ───────────────→ 0

512    ───────────────→ aprox. 127

1023   ───────────────→ 255
```

---

## 11. Estructura de map()

La función tiene esta estructura:

```cpp
map(valor, minimoEntrada, maximoEntrada, minimoSalida, maximoSalida);
```

En nuestro caso:

```cpp
map(valorPotenciometro, 0, 1023, 0, 255);
```

significa:

```text
Convierte:

0 - 1023

en:

0 - 255
```

---

## 12. Definir los pines

Utilizaremos:

```cpp
const int POTENCIOMETRO = A0;
const int LED = 9;
```

Así nuestro programa será más fácil de interpretar.

---

## 13. Programa básico

Abrimos:

```text
src/main.cpp
```

y escribimos:

```cpp
#include <Arduino.h>

const int POTENCIOMETRO = A0;
const int LED = 9;

void setup()
{
    pinMode(LED, OUTPUT);
}

void loop()
{
    int valorPotenciometro = analogRead(POTENCIOMETRO);

    int brillo = map(valorPotenciometro, 0, 1023, 0, 255);

    analogWrite(LED, brillo);
}
```

Compilamos con:

```text
Build
```

y cargamos mediante:

```text
Upload
```

---

## 14. Probar el funcionamiento

Giramos lentamente el potenciómetro.

Deberíamos observar:

```text
Potenciómetro mínimo
        │
        ▼
LED apagado o casi apagado
```

```text
Potenciómetro intermedio
        │
        ▼
LED con brillo medio
```

```text
Potenciómetro máximo
        │
        ▼
LED con brillo máximo
```

Ahora estamos controlando físicamente una salida mediante una entrada.

---

## 15. Añadir el monitor serie

Es muy útil observar qué valores está leyendo Arduino.

Modificamos el programa:

```cpp
#include <Arduino.h>

const int POTENCIOMETRO = A0;
const int LED = 9;

void setup()
{
    Serial.begin(9600);

    pinMode(LED, OUTPUT);
}

void loop()
{
    int valorPotenciometro = analogRead(POTENCIOMETRO);

    int brillo = map(valorPotenciometro, 0, 1023, 0, 255);

    analogWrite(LED, brillo);

    Serial.print("Potenciometro: ");
    Serial.print(valorPotenciometro);

    Serial.print("  PWM: ");
    Serial.println(brillo);

    delay(100);
}
```

En el monitor serie veremos algo parecido a:

```text
Potenciometro: 15   PWM: 3
Potenciometro: 240  PWM: 59
Potenciometro: 511  PWM: 127
Potenciometro: 780  PWM: 194
Potenciometro: 1021 PWM: 254
```

---

## 16. Funcionamiento completo

El proceso es:

```text
Girar potenciómetro
        │
        ▼
Cambiar tensión
        │
        ▼
analogRead(A0)
        │
        ▼
valor entre 0 y 1023
        │
        ▼
map()
        │
        ▼
valor entre 0 y 255
        │
        ▼
analogWrite(D9)
        │
        ▼
Cambiar brillo del LED
```

---

# Práctica

## Ejercicio 1 — Comprobar los valores

Abre el monitor serie y gira lentamente el potenciómetro.

Anota aproximadamente los valores obtenidos en:

```text
Mínimo

Mitad

Máximo
```

Comprueba si se acercan a:

```text
0

512

1023
```

---

## Ejercicio 2 — Comprobar el PWM

Observa simultáneamente:

```text
valorPotenciometro
```

y:

```text
brillo
```

Comprueba que aproximadamente:

```text
Potenciómetro = 0
PWM = 0
```

```text
Potenciómetro = 512
PWM = 127
```

```text
Potenciómetro = 1023
PWM = 255
```

---

## Ejercicio 3 — Invertir el funcionamiento

Modifica el programa para conseguir:

```text
Potenciómetro mínimo
        ↓
LED con brillo máximo
```

y:

```text
Potenciómetro máximo
        ↓
LED apagado
```

Puedes conseguirlo cambiando:

```cpp
map(valorPotenciometro, 0, 1023, 0, 255);
```

por:

```cpp
map(valorPotenciometro, 0, 1023, 255, 0);
```

---

## Ejercicio 4 — Limitar el brillo

Modifica el programa para que el LED nunca alcance el brillo máximo.

Por ejemplo, convierte:

```text
0 - 1023
```

en:

```text
0 - 150
```

Utiliza:

```cpp
map(valorPotenciometro, 0, 1023, 0, 150);
```

Observa la diferencia.

---

## Ejercicio 5 — Encendido a partir de un valor

Modifica el programa para que el LED solamente se encienda cuando el potenciómetro supere aproximadamente la mitad de su recorrido.

Puedes utilizar:

```cpp
if (valorPotenciometro > 512)
{
    digitalWrite(LED, HIGH);
}
else
{
    digitalWrite(LED, LOW);
}
```

En este ejercicio no utilizamos PWM.

El sistema se comportará como:

```text
0 ────────── 512 ────────── 1023
│              │               │
LED OFF        │            LED ON
```

---

# 17. Ejercicio de ampliación — Tres niveles de brillo

Podemos dividir la lectura del potenciómetro en tres zonas.

Por ejemplo:

```text
0 - 340
      ↓
Brillo bajo

341 - 680
      ↓
Brillo medio

681 - 1023
      ↓
Brillo alto
```

Podemos hacerlo mediante:

```cpp
if
```

```cpp
else if
```

y:

```cpp
else
```

Una posible solución sería:

```cpp
#include <Arduino.h>

const int POTENCIOMETRO = A0;
const int LED = 9;

void setup()
{
    pinMode(LED, OUTPUT);
}

void loop()
{
    int valor = analogRead(POTENCIOMETRO);

    if (valor < 341)
    {
        analogWrite(LED, 50);
    }
    else if (valor < 681)
    {
        analogWrite(LED, 150);
    }
    else
    {
        analogWrite(LED, 255);
    }
}
```

Esto introduce una nueva estructura:

```cpp
else if
```

que permite comprobar varias condiciones.

---

## 18. ¿Por qué utilizamos int?

Una lectura analógica puede alcanzar:

```text
1023
```

Por tanto necesitamos una variable capaz de almacenar ese valor.

Utilizamos:

```cpp
int valorPotenciometro;
```

También almacenamos el valor PWM en:

```cpp
int brillo;
```

En estas prácticas `int` es suficiente para ambos valores.

---

## 19. Entrada analógica y salida PWM

Es importante no confundir ambos conceptos.

### Entrada analógica

Utilizamos:

```cpp
analogRead();
```

para **medir** una tensión.

Por ejemplo:

```text
A0
```

Resultado:

```text
0 - 1023
```

### Salida PWM

Utilizamos:

```cpp
analogWrite();
```

para controlar una salida PWM.

Por ejemplo:

```text
D9
```

Valor utilizado:

```text
0 - 255
```

Por tanto:

```text
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
analogWrite()
```

---

## 20. Un sistema de control sencillo

Esta práctica ya representa un pequeño sistema de control:

```text
USUARIO
   │
   ▼
POTENCIÓMETRO
   │
   ▼
ENTRADA ANALÓGICA A0
   │
   ▼
ARDUINO MEGA
   │
   ▼
PROGRAMA
   │
   ▼
PWM D9
   │
   ▼
LED
```

El usuario modifica una entrada.

Arduino mide esa entrada.

El programa procesa el valor.

Finalmente Arduino modifica una salida.

Este mismo esquema aparecerá posteriormente con otros dispositivos:

```text
Sensor de luz → Arduino → LED
```

```text
Temperatura → Arduino → ventilador
```

```text
Sensor → Arduino → pantalla
```

y posteriormente:

```text
Sensor → Arduino → ESP8266 → InfluxDB
```

---

## 21. Lo que hemos aprendido

En esta lección hemos integrado:

```cpp
analogRead()
```

con:

```cpp
analogWrite()
```

y hemos introducido:

```cpp
map()
```

para convertir valores entre diferentes escalas.

Debemos recordar:

```text
analogRead()

0 - 1023
```

y:

```text
analogWrite()

0 - 255
```

Nuestro sistema es ahora:

```text
POTENCIÓMETRO
      │
      ▼
    A0
      │
      ▼
ARDUINO MEGA
      │
      ▼
     map()
      │
      ▼
   PWM D9
      │
      ▼
     LED
```

En las próximas lecciones comenzaremos a utilizar componentes más específicos del kit y sustituiremos progresivamente el potenciómetro por **sensores reales**.
