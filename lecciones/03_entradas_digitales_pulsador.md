# Lección 3 — Entradas digitales: uso de un pulsador

## 1. Objetivos

En esta lección aprenderemos a:

* Utilizar un pin digital como entrada.
* Conectar un pulsador al Arduino Mega 2560 R3.
* Leer el estado de una entrada mediante `digitalRead()`.
* Utilizar la resistencia interna `INPUT_PULLUP`.
* Comprender los estados `HIGH` y `LOW` en una entrada.
* Mostrar el estado del pulsador mediante el monitor serie.
* Utilizar una estructura `if` para tomar decisiones.

---

## 2. Material necesario

Necesitamos:

* Arduino Mega 2560 R3.
* Cable USB.
* Protoboard.
* 1 pulsador.
* 2 cables Dupont.

En esta práctica **no necesitaremos una resistencia externa**, ya que utilizaremos una resistencia interna del propio Arduino.

---

## 3. ¿Qué es una entrada digital?

En la lección anterior utilizamos Arduino para enviar una señal hacia un LED:

```text
Arduino
   │
   │ SALIDA
   ▼
  LED
```

Ahora realizaremos el proceso contrario.

El pulsador enviará información hacia Arduino:

```text
Pulsador
   │
   │ ENTRADA
   ▼
Arduino
```

Arduino podrá saber si el usuario:

```text
NO pulsa el botón

o

PULSA el botón
```

Esto nos permitirá posteriormente controlar otros componentes.

---

## 4. El pulsador

Un pulsador es un interruptor momentáneo.

Cuando no lo pulsamos, el circuito está abierto.

```text
SIN PULSAR

───────    ───────

Circuito abierto
```

Cuando lo pulsamos, sus contactos se unen:

```text
PULSADO

───────────────

Circuito cerrado
```

Cuando dejamos de presionarlo, vuelve automáticamente a su posición inicial.

---

## 5. Los cuatro terminales del pulsador

Los pulsadores incluidos habitualmente en los kits Arduino tienen cuatro terminales.

Internamente están conectados por parejas:

```text
A ───────── A


B ───────── B
```

Cuando pulsamos el botón se conectan ambos grupos:

```text
A ───────── A
│
│  PULSADO
│
B ───────── B
```

Por este motivo es importante colocar correctamente el pulsador en la protoboard.

Normalmente debe situarse atravesando la separación central.

---

## 6. Pin que utilizaremos

Utilizaremos el pin digital:

```text
D7
```

para leer el pulsador.

En nuestro programa lo identificaremos mediante:

```cpp
const int PULSADOR = 7;
```

---

## 7. ¿Qué es INPUT_PULLUP?

Una entrada digital necesita tener un estado eléctrico definido.

Si dejamos un pin de entrada sin conectar correctamente puede captar interferencias y cambiar aparentemente entre `HIGH` y `LOW`.

A este problema se le denomina **entrada flotante**.

Arduino permite evitarlo mediante una resistencia interna.

Configuraremos el pin mediante:

```cpp
pinMode(PULSADOR, INPUT_PULLUP);
```

`INPUT_PULLUP` activa una resistencia interna que mantiene normalmente la entrada en estado `HIGH`.

Por tanto:

```text
Pulsador SIN pulsar
        │
        ▼
      HIGH
```

Cuando pulsamos conectaremos el pin directamente a `GND`:

```text
Pulsador PULSADO
        │
        ▼
       LOW
```

Esto puede parecer inicialmente al revés de lo esperado, pero debemos recordarlo:

| Pulsador   | Valor leído |
| ---------- | ----------- |
| Sin pulsar | `HIGH`      |
| Pulsado    | `LOW`       |

---

## 8. Conexiones

El montaje es muy sencillo.

Conectaremos:

```text
Arduino Mega 2560

      D7
       │
       │
   ┌─────────┐
   │ PULSADOR│
   └─────────┘
       │
       │
      GND
```

### Tabla de conexiones

| Arduino | Pulsador                  |
| ------- | ------------------------- |
| D7      | Un lado del pulsador      |
| GND     | Lado opuesto del pulsador |

No debemos conectar el pulsador a `5V` en este montaje.

Estamos utilizando:

```cpp
INPUT_PULLUP
```

por lo que solamente necesitamos conectar el pulsador entre:

```text
D7 ↔ PULSADOR ↔ GND
```

---

## 9. Montaje en la protoboard

Colocamos el pulsador atravesando la separación central de la protoboard.

De forma simplificada:

```text
          separación
              │
              ▼

A B C D E     F G H I J

        ┌───────┐
────────┤       ├────────
        │ BOTÓN │
────────┤       ├────────
        └───────┘
```

Conectamos un lado a:

```text
D7
```

y el lado opuesto a:

```text
GND
```

---

## 10. Primer programa

Abrimos:

```text
src/main.cpp
```

y escribimos:

```cpp
#include <Arduino.h>

const int PULSADOR = 7;

void setup()
{
    Serial.begin(9600);

    pinMode(PULSADOR, INPUT_PULLUP);

    Serial.println("Prueba del pulsador");
}

void loop()
{
    int estado = digitalRead(PULSADOR);

    Serial.println(estado);

    delay(200);
}
```

Compilamos y cargamos el programa.

---

## 11. Leer una entrada digital

La instrucción:

```cpp
digitalRead(PULSADOR);
```

consulta el estado eléctrico del pin.

El resultado solamente puede ser:

```text
HIGH
```

o:

```text
LOW
```

En nuestro programa guardamos ese resultado en una variable:

```cpp
int estado = digitalRead(PULSADOR);
```

La variable `estado` contiene, por tanto, el estado actual del pulsador.

---

## 12. Probar el programa

Abrimos el monitor serie.

Sin tocar el pulsador deberíamos observar:

```text
1
1
1
1
1
1
```

Ahora mantenemos pulsado el botón.

Deberíamos observar:

```text
0
0
0
0
0
```

Esto ocurre porque:

```text
SIN PULSAR → HIGH → 1

PULSADO    → LOW  → 0
```

---

## 13. Mostrar mensajes más claros

Los valores `0` y `1` no son demasiado descriptivos.

Podemos hacer que Arduino muestre:

```text
Pulsador libre
```

o:

```text
Pulsador pulsado
```

Para ello necesitamos que Arduino tome una decisión.

---

## 14. La estructura if

La estructura:

```cpp
if
```

permite ejecutar determinadas instrucciones solamente cuando se cumple una condición.

Su estructura básica es:

```cpp
if (condicion)
{
    // instrucciones
}
```

Por ejemplo:

```cpp
if (estado == LOW)
{
    Serial.println("Pulsador pulsado");
}
```

significa:

```text
¿estado es LOW?
       │
       ├── SÍ ──→ Mostrar "Pulsador pulsado"
       │
       └── NO ──→ No ejecutar esa instrucción
```

---

## 15. Utilizar if y else

También podemos indicar qué debe ocurrir cuando la condición no se cumple.

Utilizamos:

```cpp
if (estado == LOW)
{
    Serial.println("Pulsador pulsado");
}
else
{
    Serial.println("Pulsador libre");
}
```

Podemos interpretar el programa como:

```text
Leer pulsador
      │
      ▼
¿Está pulsado?
      │
   ┌──┴──┐
   │     │
  SÍ     NO
   │     │
   ▼     ▼
Pulsado Libre
```

---

## 16. Programa completo

Nuestro programa queda:

```cpp
#include <Arduino.h>

const int PULSADOR = 7;

void setup()
{
    Serial.begin(9600);

    pinMode(PULSADOR, INPUT_PULLUP);

    Serial.println("Prueba del pulsador");
}

void loop()
{
    int estado = digitalRead(PULSADOR);

    if (estado == LOW)
    {
        Serial.println("Pulsador pulsado");
    }
    else
    {
        Serial.println("Pulsador libre");
    }

    delay(200);
}
```

---

## 17. ¿Qué significa ==?

Debemos prestar atención a esta instrucción:

```cpp
estado == LOW
```

Los dos símbolos:

```text
==
```

significan **comparación**.

Estamos preguntando:

```text
¿estado es igual a LOW?
```

No debemos confundir:

```cpp
=
```

con:

```cpp
==
```

`=` se utiliza para asignar un valor:

```cpp
int numero = 5;
```

`==` se utiliza para comparar:

```cpp
if (numero == 5)
```

Esta diferencia será muy importante en nuestros programas.

---

# Práctica

## Ejercicio 1 — Comprobar HIGH y LOW

Carga el primer programa y observa el monitor serie.

Comprueba que:

```text
Sin pulsar → 1
Pulsado    → 0
```

Explica por qué ocurre esto.

---

## Ejercicio 2 — Cambiar los mensajes

Modifica el programa para que muestre:

```text
BOTON LIBRE
```

cuando no esté pulsado y:

```text
BOTON ACTIVADO
```

cuando lo pulses.

---

## Ejercicio 3 — Contador de tiempo

Cambia:

```cpp
delay(200);
```

por:

```cpp
delay(1000);
```

Observa la diferencia.

Después prueba:

```cpp
delay(50);
```

Comprueba cómo afecta el tiempo a la cantidad de mensajes mostrados en el monitor serie.

---

## Ejercicio 4 — Mostrar solamente cuando se pulsa

Modifica el programa para que solamente aparezca un mensaje cuando el botón esté pulsado.

El programa debe utilizar:

```cpp
if (estado == LOW)
{
    Serial.println("Pulsador pulsado");
}
```

sin utilizar `else`.

---

## 18. Un problema que encontraremos: el rebote

Un pulsador es un dispositivo mecánico.

Cuando lo presionamos, sus contactos no cambian siempre de estado de forma perfectamente limpia.

Durante unos pocos milisegundos pueden producirse pequeños cambios:

```text
HIGH ─────────┐
              │
              └─┐ ┌─┐
                │ │ │
                └─┘ └──────── LOW
```

Este fenómeno se denomina **rebote del pulsador** o *bouncing*.

En esta práctica no representa un problema importante porque simplemente estamos mostrando su estado.

Sin embargo, cuando queramos contar exactamente una pulsación tendremos que tenerlo en cuenta.

Lo veremos más adelante.

---

## 19. Entrada, procesamiento y salida

Con esta práctica podemos empezar a comprender una idea fundamental de los sistemas electrónicos programables:

```text
ENTRADA
   │
   ▼
Pulsador
   │
   ▼
Arduino
   │
   │ procesa
   ▼
Programa
   │
   ▼
SALIDA
   │
   ▼
Monitor serie
```

Arduino recibe información del mundo exterior mediante una **entrada**, ejecuta nuestro programa y genera una **salida**.

Este concepto será la base de prácticamente todas las prácticas siguientes.

---

## 20. Lo que hemos aprendido

En esta lección hemos introducido:

```cpp
pinMode(PULSADOR, INPUT_PULLUP);
```

para configurar una entrada digital.

Hemos utilizado:

```cpp
digitalRead(PULSADOR);
```

para leerla.

Y hemos aprendido a tomar decisiones mediante:

```cpp
if
else
```

También debemos recordar especialmente:

```text
Con INPUT_PULLUP:

SIN PULSAR → HIGH
PULSADO    → LOW
```

Nuestro sistema actual es:

```text
PULSADOR
   │
   │ entrada
   ▼
ARDUINO MEGA
   │
   │ programa
   ▼
MONITOR SERIE
```

En la siguiente lección combinaremos lo aprendido en las lecciones 2 y 3:

```text
PULSADOR
   │
   ▼
ARDUINO
   │
   ▼
LED
```

El pulsador dejará de ser únicamente una entrada que observamos en el monitor serie y comenzará a **controlar físicamente un dispositivo de salida**.
