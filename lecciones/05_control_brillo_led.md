# Lección 5 — PWM: control del brillo de un LED

## 1. Objetivos

En esta lección aprenderemos a:

* Comprender qué es una señal PWM.
* Identificar los pines PWM del Arduino Mega 2560 R3.
* Utilizar `analogWrite()`.
* Controlar el brillo de un LED.
* Trabajar con valores entre 0 y 255.
* Crear un efecto de aumento y disminución progresiva del brillo.
* Utilizar un bucle `for`.

---

## 2. Material necesario

Necesitamos:

* Arduino Mega 2560 R3.
* Cable USB.
* Protoboard.
* 1 LED.
* 1 resistencia de aproximadamente 220 Ω.
* Cables Dupont.

En esta práctica no utilizaremos el pulsador.

---

# 3. Salidas digitales

Hasta ahora hemos utilizado una salida digital.

Podíamos hacer:

```cpp
digitalWrite(LED, HIGH);
```

o:

```cpp
digitalWrite(LED, LOW);
```

Por tanto solamente teníamos dos posibilidades:

```text
HIGH → encendido

LOW  → apagado
```

Podemos representarlo como:

```text
LED

100 % ──────────┐
                │
                │
                └────────── 0 %

       ON             OFF
```

Pero ¿qué ocurre si queremos que el LED ilumine solamente al 50 %?

Necesitamos otro sistema.

---

# 4. PWM

PWM significa:

```text
Pulse Width Modulation
```

o:

```text
Modulación por ancho de pulso
```

Arduino utiliza PWM para simular diferentes niveles de salida.

La salida continúa siendo digital:

```text
HIGH / LOW
```

pero Arduino cambia muy rápidamente entre ambos estados.

Por ejemplo:

```text
HIGH ────┐    ┌────┐    ┌────
         │    │    │    │
LOW      └────┘    └────┘
```

El cambio ocurre tan rápidamente que nuestros ojos no perciben el parpadeo.

Observamos una intensidad luminosa determinada.

---

# 5. Ciclo de trabajo

Una señal PWM puede permanecer más o menos tiempo en `HIGH`.

Por ejemplo:

```text
25 %

HIGH ─┐      ┌─
      │      │
LOW   └──────┘
```

El LED iluminará poco.

Con aproximadamente un 50 %:

```text
50 %

HIGH ────┐    ┌────
         │    │
LOW      └────┘
```

El LED tendrá un brillo intermedio.

Con un porcentaje elevado:

```text
75 %

HIGH ──────┐  ┌──────
           │  │
LOW        └──┘
```

el LED tendrá mayor brillo.

A este porcentaje se le denomina **ciclo de trabajo** o *duty cycle*.

---

# 6. Pines PWM del Arduino Mega

No debemos utilizar cualquier pin para generar PWM mediante `analogWrite()`.

En el Arduino Mega 2560 R3, los pines PWM están identificados en la placa mediante el símbolo:

```text
~
```

Por ejemplo:

```text
~2
~3
~4
...
~9
...
```

En esta práctica utilizaremos:

```text
D9
```

Por tanto definiremos:

```cpp
const int LED = 9;
```

---

# 7. Conexiones

Utilizaremos el mismo circuito básico de las prácticas anteriores, pero ahora conectaremos el LED a **D9**.

```text
Arduino Mega

      D9
       │
       ▼
     220 Ω
       │
       ▼
     Ánodo
      LED
     Cátodo
       │
       ▼
      GND
```

---

## Tabla de conexiones

| Arduino / componente | Conectar a           |
| -------------------- | -------------------- |
| D9                   | Resistencia de 220 Ω |
| Resistencia          | Ánodo del LED        |
| Cátodo del LED       | GND                  |

Debemos comprobar nuevamente la polaridad:

```text
Pata larga  → Ánodo

Pata corta  → Cátodo
```

---

# 8. analogWrite()

Para generar PWM utilizaremos:

```cpp
analogWrite();
```

Su estructura es:

```cpp
analogWrite(pin, valor);
```

El valor puede encontrarse entre:

```text
0 y 255
```

Por ejemplo:

```cpp
analogWrite(LED, 0);
```

produce:

```text
LED apagado
```

Mientras que:

```cpp
analogWrite(LED, 255);
```

produce aproximadamente:

```text
LED con brillo máximo
```

---

# 9. Valores intermedios

Podemos utilizar cualquier valor entre 0 y 255.

Por ejemplo:

```cpp
analogWrite(LED, 64);
```

produce un brillo bajo.

```cpp
analogWrite(LED, 128);
```

produce aproximadamente un nivel intermedio.

```cpp
analogWrite(LED, 192);
```

produce un brillo elevado.

Podemos resumirlo:

| Valor | PWM aproximado | Resultado     |
| ----: | -------------: | ------------- |
|     0 |            0 % | Apagado       |
|    64 |           25 % | Brillo bajo   |
|   128 |           50 % | Brillo medio  |
|   192 |           75 % | Brillo alto   |
|   255 |          100 % | Brillo máximo |

---

# 10. Primer programa PWM

Abrimos:

```text
src/main.cpp
```

y escribimos:

```cpp
#include <Arduino.h>

const int LED = 9;

void setup()
{
    pinMode(LED, OUTPUT);
}

void loop()
{
    analogWrite(LED, 64);
    delay(2000);

    analogWrite(LED, 128);
    delay(2000);

    analogWrite(LED, 192);
    delay(2000);

    analogWrite(LED, 255);
    delay(2000);

    analogWrite(LED, 0);
    delay(2000);
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

---

# 11. Observar el resultado

El LED realizará aproximadamente esta secuencia:

```text
Brillo 25 %
     │
     │ 2 segundos
     ▼
Brillo 50 %
     │
     │ 2 segundos
     ▼
Brillo 75 %
     │
     │ 2 segundos
     ▼
Brillo 100 %
     │
     │ 2 segundos
     ▼
Apagado
     │
     │ 2 segundos
     ▼
   repetir
```

Observa que ahora el LED no está simplemente:

```text
ON / OFF
```

sino que podemos controlar su intensidad.

---

# 12. Mostrar el valor por el monitor serie

Podemos combinar PWM con lo aprendido sobre el puerto serie:

```cpp
#include <Arduino.h>

const int LED = 9;

void setup()
{
    Serial.begin(9600);

    pinMode(LED, OUTPUT);
}

void loop()
{
    Serial.println("PWM = 64");
    analogWrite(LED, 64);
    delay(2000);

    Serial.println("PWM = 128");
    analogWrite(LED, 128);
    delay(2000);

    Serial.println("PWM = 192");
    analogWrite(LED, 192);
    delay(2000);

    Serial.println("PWM = 255");
    analogWrite(LED, 255);
    delay(2000);

    Serial.println("PWM = 0");
    analogWrite(LED, 0);
    delay(2000);
}
```

El monitor serie mostrará:

```text
PWM = 64
PWM = 128
PWM = 192
PWM = 255
PWM = 0
...
```

---

# 13. Crear un aumento progresivo

Podemos conseguir un efecto más interesante aumentando poco a poco el valor PWM.

Por ejemplo:

```text
0
↓
1
↓
2
↓
3
↓
4
↓
...
↓
255
```

Podríamos escribir cientos de instrucciones, pero evidentemente no sería práctico.

Para ello utilizaremos un **bucle**.

---

# 14. El bucle for

Un bucle `for` permite repetir instrucciones un determinado número de veces.

Por ejemplo:

```cpp
for (int brillo = 0; brillo <= 255; brillo++)
{
    analogWrite(LED, brillo);

    delay(10);
}
```

La variable:

```cpp
brillo
```

comienza con:

```text
0
```

y va aumentando:

```text
0
1
2
3
4
5
...
255
```

En cada vuelta ejecutamos:

```cpp
analogWrite(LED, brillo);
```

Por tanto el LED aumenta progresivamente su intensidad.

---

# 15. Comprender el for

Esta instrucción:

```cpp
for (int brillo = 0; brillo <= 255; brillo++)
```

contiene tres partes:

```text
for ( INICIO ; CONDICIÓN ; CAMBIO )
```

En nuestro caso:

```text
int brillo = 0
```

crea la variable y comienza en 0.

Después:

```text
brillo <= 255
```

indica que el bucle continuará mientras el valor no supere 255.

Finalmente:

```text
brillo++
```

significa:

```text
brillo = brillo + 1
```

---

# 16. Programa de aumento progresivo

Podemos realizar:

```cpp
#include <Arduino.h>

const int LED = 9;

void setup()
{
    pinMode(LED, OUTPUT);
}

void loop()
{
    for (int brillo = 0; brillo <= 255; brillo++)
    {
        analogWrite(LED, brillo);

        delay(10);
    }

    delay(1000);

    analogWrite(LED, 0);

    delay(1000);
}
```

El LED irá aumentando lentamente su brillo.

Cuando llegue al máximo se apagará y comenzará de nuevo.

---

# 17. Aumentar y disminuir el brillo

Ahora podemos crear un efecto más suave:

```text
APAGADO
   │
   ▼
Aumentar brillo
   │
   ▼
MÁXIMO
   │
   ▼
Disminuir brillo
   │
   ▼
APAGADO
   │
   ▼
repetir
```

Para aumentar utilizamos:

```cpp
for (int brillo = 0; brillo <= 255; brillo++)
```

Para disminuir podemos utilizar:

```cpp
for (int brillo = 255; brillo >= 0; brillo--)
```

En este segundo caso:

```text
255
254
253
252
...
1
0
```

---

# 18. Programa efecto Fade

Nuestro programa completo será:

```cpp
#include <Arduino.h>

const int LED = 9;

void setup()
{
    pinMode(LED, OUTPUT);
}

void loop()
{
    for (int brillo = 0; brillo <= 255; brillo++)
    {
        analogWrite(LED, brillo);

        delay(10);
    }

    for (int brillo = 255; brillo >= 0; brillo--)
    {
        analogWrite(LED, brillo);

        delay(10);
    }
}
```

El LED aumentará y disminuirá suavemente su intensidad de forma continua.

Este efecto suele denominarse:

```text
Fade
```

---

# 19. ¿Cuánto tarda el efecto?

Tenemos aproximadamente:

```text
256 pasos
```

y esperamos:

```text
10 ms
```

en cada paso.

Por tanto:

```text
256 × 10 ms = 2560 ms
```

aproximadamente:

```text
2,56 segundos
```

para pasar del mínimo al máximo.

Otros 2,56 segundos aproximadamente para volver al mínimo.

---

# 20. Cambiar la velocidad

Podemos modificar:

```cpp
delay(10);
```

Si utilizamos:

```cpp
delay(5);
```

el cambio será más rápido.

Si utilizamos:

```cpp
delay(20);
```

será más lento.

Por tanto:

```text
delay pequeño → transición rápida

delay grande  → transición lenta
```

---

# Práctica

## Ejercicio 1 — Diferentes intensidades

Realiza un programa que mantenga:

```text
Brillo 25 %  → 2 segundos

Brillo 50 %  → 2 segundos

Brillo 100 % → 2 segundos

Apagado      → 2 segundos
```

y repita continuamente la secuencia.

---

## Ejercicio 2 — Efecto Fade

Carga el programa de aumento y disminución progresiva.

Comprueba que el LED cambia suavemente entre:

```text
0 → 255 → 0
```

---

## Ejercicio 3 — Cambiar la velocidad

Prueba sucesivamente:

```cpp
delay(2);
```

```cpp
delay(10);
```

```cpp
delay(30);
```

Observa cómo cambia la velocidad del efecto.

---

## Ejercicio 4 — Cambiar los pasos

No es obligatorio incrementar el valor de uno en uno.

Podemos utilizar:

```cpp
brillo += 5
```

Por ejemplo:

```cpp
for (int brillo = 0; brillo <= 255; brillo += 5)
{
    analogWrite(LED, brillo);

    delay(50);
}
```

Comprueba la diferencia.

---

# 21. Ejercicio de ampliación — Control mediante el monitor serie

Hasta ahora el programa decide automáticamente el brillo.

Como ampliación podemos permitir que el usuario escriba un valor desde el ordenador.

Queremos conseguir:

```text
Ordenador
   │
   │ 0 - 255
   ▼
Puerto serie
   │
   ▼
Arduino
   │
   ▼
PWM
   │
   ▼
LED
```

Podemos utilizar:

```cpp
#include <Arduino.h>

const int LED = 9;

void setup()
{
    Serial.begin(9600);

    pinMode(LED, OUTPUT);

    Serial.println("Introduce un valor entre 0 y 255:");
}

void loop()
{
    if (Serial.available() > 0)
    {
        int brillo = Serial.parseInt();

        if (brillo >= 0 && brillo <= 255)
        {
            analogWrite(LED, brillo);

            Serial.print("Nuevo valor PWM: ");
            Serial.println(brillo);
        }
    }
}
```

Desde el monitor serie podemos escribir:

```text
0
```

para apagar el LED.

Después:

```text
128
```

para obtener aproximadamente la mitad de intensidad.

Finalmente:

```text
255
```

para obtener el máximo.

Estamos empezando a realizar **control remoto del Arduino**:

```text
USUARIO
   │
   ▼
ORDENADOR
   │
   ▼
ARDUINO
   │
   ▼
LED
```

Más adelante sustituiremos el monitor serie por una **página web**.

---

# 22. PWM no es una salida analógica real

Es importante comprender que:

```cpp
analogWrite()
```

no significa necesariamente que Arduino genere una tensión analógica continua.

El pin continúa cambiando entre dos estados digitales:

```text
0 V

y

5 V
```

Lo que cambia es el porcentaje de tiempo que permanece en cada estado.

Por ejemplo:

```text
PWM bajo

5 V  ─┐       ┌─
      │       │
0 V   └───────┘


PWM medio

5 V  ────┐    ┌────
         │    │
0 V      └────┘


PWM alto

5 V  ───────┐ ┌───────
            │ │
0 V         └─┘
```

El LED responde a esta señal mostrando diferentes niveles aparentes de brillo.

---

# 23. Lo que hemos aprendido

En esta lección hemos pasado del control digital:

```text
APAGADO / ENCENDIDO
```

a un control gradual:

```text
0 ─────────────────────────── 255
│                              │
apagado                  brillo máximo
```

Hemos aprendido a utilizar:

```cpp
analogWrite()
```

y hemos introducido:

```cpp
for
```

También hemos utilizado:

```cpp
brillo++
```

y:

```cpp
brillo--
```

para aumentar y disminuir variables.

Nuestro sistema actual es:

```text
PROGRAMA
   │
   ▼
ARDUINO MEGA
   │
   ▼
PWM D9
   │
   ▼
LED
   │
   ▼
BRILLO VARIABLE
```

Hasta ahora el valor PWM lo decide nuestro programa.

En la siguiente lección introduciremos nuestro primer **sensor analógico: el potenciómetro**.

Podremos girarlo con la mano y obtener valores numéricos:

```text
POTENCIÓMETRO
      │
      ▼
ENTRADA ANALÓGICA
      │
      ▼
ARDUINO
```

Posteriormente combinaremos ambos conceptos:

```text
POTENCIÓMETRO
      │
      ▼
ARDUINO
      │
      ▼
PWM
      │
      ▼
LED
```

de forma que podremos **regular manualmente el brillo del LED girando el potenciómetro**.
