# Lección 2 — Salidas digitales: control de un LED

## 1. Objetivos

En esta lección aprenderemos a:

* Utilizar una salida digital del Arduino Mega 2560 R3.
* Montar un circuito sencillo en una protoboard.
* Conectar correctamente un LED.
* Comprender para qué sirve una resistencia.
* Configurar un pin mediante `pinMode()`.
* Activar y desactivar una salida mediante `digitalWrite()`.
* Crear un programa que haga parpadear un LED.

---

## 2. Material necesario

Necesitamos los siguientes componentes del kit:

* Arduino Mega 2560 R3.
* Cable USB.
* Protoboard.
* 1 LED.
* 1 resistencia de aproximadamente **220 Ω**.
* Cables Dupont.

---

## 3. El LED

Un LED es un diodo emisor de luz.

A diferencia de una bombilla convencional, el LED tiene **polaridad**, por lo que debemos conectarlo en la dirección correcta.

Normalmente podemos distinguir sus terminales de la siguiente manera:

```text
Pata larga  → Ánodo (+)
Pata corta  → Cátodo (-)
```

También podemos observar el encapsulado del LED:

```text
       LED
      _____
     /     \
    |       |
     \_____/
       │ │
       │ │
       │ └──── Cátodo (-)
       │
       └────── Ánodo (+)
```

El ánodo se conectará hacia la salida del Arduino.

El cátodo se conectará hacia `GND`.

---

## 4. ¿Por qué necesitamos una resistencia?

No debemos conectar directamente un LED entre una salida del Arduino y `GND`.

Debemos colocar una resistencia para limitar la corriente que circula por el LED.

En esta práctica utilizaremos aproximadamente:

```text
220 Ω
```

También puede utilizarse una resistencia cercana, por ejemplo:

```text
220 Ω
330 Ω
```

La resistencia protege tanto el LED como la salida del microcontrolador.

---

## 5. La protoboard

La protoboard permite construir circuitos electrónicos sin necesidad de soldar.

Los agujeros están conectados eléctricamente en grupos.

En la zona central suelen estar conectados de esta forma:

```text
A ─┐
B  │
C  ├── conectados
D  │
E ─┘

     separación

F ─┐
G  │
H  ├── conectados
I  │
J ─┘
```

Es importante recordar que introducir dos componentes en la protoboard no significa necesariamente que estén conectados.

Deben encontrarse en puntos que estén unidos internamente.

---

## 6. Primera salida digital

Arduino Mega 2560 dispone de numerosos pines digitales.

Para esta práctica utilizaremos:

```text
Pin digital 8
```

Lo denominaremos en el programa:

```cpp
const int LED = 8;
```

Esto hace que el código sea más fácil de leer.

---

## 7. Conexiones

Realizaremos el siguiente circuito:

```text
Arduino Mega 2560

        D8
         │
         │
      220 Ω
         │
         │
      Ánodo
        LED
      Cátodo
         │
         │
        GND
```

### Tabla de conexiones

| Arduino / componente | Conectar a           |
| -------------------- | -------------------- |
| Pin D8               | Resistencia de 220 Ω |
| Resistencia          | Ánodo del LED        |
| Cátodo del LED       | GND                  |

La resistencia puede colocarse también después del LED:

```text
D8 ── LED ── 220 Ω ── GND
```

El resultado eléctrico es equivalente.

---

## 8. Comprobar el montaje

Antes de conectar la alimentación debemos comprobar:

1. Que el LED está correctamente orientado.
2. Que existe una resistencia en serie con el LED.
3. Que el circuito termina en `GND`.
4. Que estamos utilizando el pin `D8`.

Nuestro circuito debe seguir el recorrido:

```text
D8
 ↓
Resistencia
 ↓
LED
 ↓
GND
```

---

## 9. Configurar una salida

Para utilizar un pin como salida debemos configurarlo.

Utilizamos:

```cpp
pinMode(LED, OUTPUT);
```

Esta configuración debe realizarse en:

```cpp
setup()
```

porque solamente necesitamos hacerla una vez cuando arranca Arduino.

---

## 10. Encender el LED

Para activar una salida digital utilizamos:

```cpp
digitalWrite(LED, HIGH);
```

`HIGH` significa que la salida está activada.

En nuestro montaje esto provoca que circule corriente:

```text
D8
 │
 │ HIGH
 ▼
Resistencia
 │
 ▼
LED  → ENCENDIDO
 │
 ▼
GND
```

---

## 11. Apagar el LED

Para desactivar la salida utilizamos:

```cpp
digitalWrite(LED, LOW);
```

El LED se apagará.

Por tanto:

| Instrucción                | Estado del LED |
| -------------------------- | -------------- |
| `digitalWrite(LED, HIGH);` | Encendido      |
| `digitalWrite(LED, LOW);`  | Apagado        |

---

## 12. Programa

Abrimos:

```text
src/main.cpp
```

y escribimos:

```cpp
#include <Arduino.h>

const int LED = 8;

void setup()
{
    pinMode(LED, OUTPUT);
}

void loop()
{
    digitalWrite(LED, HIGH);
    delay(1000);

    digitalWrite(LED, LOW);
    delay(1000);
}
```

---

## 13. Compilar y cargar

Con Arduino conectado mediante USB realizamos:

```text
Build
```

Si no existen errores aparecerá:

```text
SUCCESS
```

Después realizamos:

```text
Upload
```

PlatformIO enviará el programa al Arduino Mega.

El LED debería comenzar a parpadear.

---

## 14. Funcionamiento del programa

Al arrancar Arduino se ejecuta:

```cpp
pinMode(LED, OUTPUT);
```

y el pin 8 queda configurado como salida.

Después comienza `loop()`.

Primero:

```cpp
digitalWrite(LED, HIGH);
```

enciende el LED.

A continuación:

```cpp
delay(1000);
```

mantiene el programa detenido durante un segundo.

Después:

```cpp
digitalWrite(LED, LOW);
```

apaga el LED.

Finalmente:

```cpp
delay(1000);
```

espera otro segundo.

Cuando `loop()` termina vuelve automáticamente al principio.

El resultado es:

```text
LED encendido
     │
     │ 1 segundo
     ▼
LED apagado
     │
     │ 1 segundo
     ▼
LED encendido
     │
     │
     ▼
    ...
```

---

# Práctica

## Ejercicio 1 — Parpadeo rápido

Modifica el programa para que el LED permanezca:

```text
500 ms encendido
500 ms apagado
```

Comprueba físicamente el resultado.

---

## Ejercicio 2 — Diferentes tiempos

Modifica el programa para conseguir:

```text
Encendido → 2 segundos

Apagado   → 0,5 segundos
```

Piensa qué valores debes utilizar en las dos llamadas a `delay()`.

---

## Ejercicio 3 — Destello corto

Realiza un programa que produzca:

```text
LED encendido → 100 ms
LED apagado   → 1000 ms
```

El resultado debe ser un pequeño destello cada segundo aproximadamente.

---

## Ejercicio 4 — Dos destellos

Intenta conseguir esta secuencia:

```text
ENCENDIDO
   ↓
200 ms
   ↓
APAGADO
   ↓
200 ms
   ↓
ENCENDIDO
   ↓
200 ms
   ↓
APAGADO
   ↓
1000 ms
   ↓
repetir
```

El LED debe realizar dos destellos rápidos y después una pausa.

---

## 15. Añadir información al monitor serie

Podemos combinar lo aprendido en la primera lección con el control del LED.

Por ejemplo:

```cpp
#include <Arduino.h>

const int LED = 8;

void setup()
{
    Serial.begin(9600);

    pinMode(LED, OUTPUT);

    Serial.println("Control de LED iniciado");
}

void loop()
{
    digitalWrite(LED, HIGH);
    Serial.println("LED encendido");

    delay(1000);

    digitalWrite(LED, LOW);
    Serial.println("LED apagado");

    delay(1000);
}
```

Si abrimos el monitor serie observaremos:

```text
Control de LED iniciado
LED encendido
LED apagado
LED encendido
LED apagado
...
```

De esta forma podemos utilizar el monitor serie para conocer lo que está haciendo nuestro programa.

Esta técnica será especialmente útil cuando trabajemos con sensores.

---

## 16. Si el LED no funciona

Si el LED no se enciende debemos comprobar, por este orden:

### 1. Polaridad del LED

Comprueba que:

```text
Ánodo   → hacia D8
Cátodo  → hacia GND
```

Si está invertido, dale la vuelta.

### 2. Resistencia

Comprueba que la resistencia está conectada **en serie** con el LED.

### 3. GND

Comprueba que el circuito realmente termina conectado a un pin `GND` del Arduino.

### 4. Pin utilizado

El circuito debe estar conectado a:

```text
D8
```

porque nuestro programa utiliza:

```cpp
const int LED = 8;
```

### 5. Programa cargado

Comprueba que PlatformIO ha terminado la carga mostrando:

```text
SUCCESS
```

---

## 17. Lo que hemos aprendido

En esta lección hemos utilizado nuestras primeras instrucciones para controlar hardware:

```cpp
pinMode()
digitalWrite()
delay()
```

También hemos aprendido los estados digitales:

```text
HIGH
LOW
```

y hemos construido nuestro primer circuito:

```text
Arduino
   │
   ▼
Salida digital D8
   │
   ▼
Resistencia
   │
   ▼
LED
   │
   ▼
GND
```

Podemos resumir el funcionamiento como:

```text
PROGRAMA
   │
   ▼
ARDUINO
   │
   ▼
PIN DIGITAL
   │
   ▼
LED
```

En la siguiente lección realizaremos el proceso contrario: utilizaremos un **pulsador como entrada digital** para que Arduino pueda recibir información del exterior.
