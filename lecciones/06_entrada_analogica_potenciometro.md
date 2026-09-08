# Lección 6 — Entradas analógicas: el potenciómetro

## 1. Objetivos

En esta lección aprenderemos a:

* Comprender la diferencia entre una entrada digital y una entrada analógica.
* Conectar un potenciómetro al Arduino Mega 2560 R3.
* Utilizar las entradas analógicas del Arduino.
* Leer valores mediante `analogRead()`.
* Comprender el rango de valores entre `0` y `1023`.
* Mostrar medidas mediante el monitor serie.
* Relacionar el valor leído con una tensión entre 0 V y 5 V.

---

## 2. Material necesario

Necesitamos:

* Arduino Mega 2560 R3.
* Cable USB.
* Protoboard.
* 1 potenciómetro.
* Cables Dupont.

En esta práctica no necesitamos resistencias adicionales.

---

# 3. Entradas digitales y analógicas

Hasta ahora hemos trabajado con entradas digitales.

Por ejemplo, el pulsador de la lección 3 solamente podía tener dos estados:

```text
HIGH
LOW
```

Es decir:

```text
0
1
```

Podemos representarlo como:

```text
ENTRADA DIGITAL

        ┌──────────── HIGH
        │
────────┘

Solamente dos estados
```

Sin embargo, muchos sensores pueden producir numerosos valores diferentes.

Por ejemplo:

* Temperatura.
* Intensidad luminosa.
* Humedad.
* Presión.
* Posición de un mando.
* Nivel de sonido.

Para trabajar con este tipo de señales utilizaremos las **entradas analógicas**.

---

# 4. El potenciómetro

Un potenciómetro es una resistencia cuyo valor podemos modificar girando un mando.

Tiene normalmente **tres terminales**:

```text
     POTENCIÓMETRO

     ┌───────────┐
     │           │
     │     ▲     │
     │     │     │
     └──┬──┴──┬──┘
        │  │  │
        │  │  │
        1  2  3
```

Los dos terminales exteriores corresponden a los extremos de la resistencia.

El terminal central es el **cursor**.

Al girar el mando, el cursor cambia de posición.

---

# 5. Utilizar el potenciómetro como divisor de tensión

Conectaremos los extremos del potenciómetro a:

```text
5V
```

y:

```text
GND
```

El terminal central proporcionará una tensión que cambiará aproximadamente entre:

```text
0 V
```

y:

```text
5 V
```

dependiendo de la posición del mando.

Podemos representarlo así:

```text
        5V
         │
         │
     ┌────────┐
     │        │
     │  POT   │
     │        │
     └───┬────┘
         │
         ├────────── A0
         │
        GND
```

---

# 6. Las entradas analógicas del Arduino Mega

Arduino Mega 2560 dispone de varias entradas analógicas.

Están identificadas como:

```text
A0
A1
A2
A3
...
```

En esta práctica utilizaremos:

```text
A0
```

En el programa podemos definirla como:

```cpp
const int POTENCIOMETRO = A0;
```

---

# 7. Conexiones

Conectaremos los tres terminales del potenciómetro de la siguiente manera:

| Potenciómetro     | Arduino Mega |
| ----------------- | ------------ |
| Terminal exterior | 5V           |
| Terminal central  | A0           |
| Terminal exterior | GND          |

El circuito será:

```text
Arduino Mega

5V ─────────────┐
                │
          ┌───────────┐
          │           │
          │    POT    │
          │           │
          └──┬─────┬──┘
             │     │
             │     └──────── GND
             │
             └────────────── A0
```

---

## 8. Importante: los dos extremos pueden intercambiarse

Podemos intercambiar los terminales exteriores del potenciómetro:

```text
5V ↔ GND
```

El circuito seguirá funcionando.

La única diferencia será el sentido de giro.

Por ejemplo:

```text
Montaje 1:

Girar derecha → aumenta el valor
```

pero si intercambiamos los extremos:

```text
Montaje 2:

Girar derecha → disminuye el valor
```

Esto no supone ningún problema.

---

# 9. analogRead()

Para leer una entrada analógica utilizamos:

```cpp
analogRead();
```

Por ejemplo:

```cpp
analogRead(A0);
```

Arduino convertirá la tensión existente en el pin A0 en un número.

El Arduino Mega utiliza normalmente un conversor analógico-digital de **10 bits**.

Por ello podemos obtener valores desde:

```text
0
```

hasta:

```text
1023
```

---

# 10. Relación entre tensión y valor leído

Aproximadamente:

| Tensión | Valor `analogRead()` |
| ------: | -------------------: |
|     0 V |                    0 |
|  1,25 V |                  256 |
|   2,5 V |                  512 |
|  3,75 V |                  768 |
|     5 V |                 1023 |

Por tanto:

```text
0 V                          5 V
│                             │
▼                             ▼
0 ───────────────────────── 1023
```

Cuando giramos el potenciómetro estamos modificando la tensión que llega a A0.

Arduino convierte esa tensión en un número.

---

# 11. Primer programa

Abrimos:

```text
src/main.cpp
```

y escribimos:

```cpp
#include <Arduino.h>

const int POTENCIOMETRO = A0;

void setup()
{
    Serial.begin(9600);

    Serial.println("Lectura del potenciometro");
}

void loop()
{
    int valor = analogRead(POTENCIOMETRO);

    Serial.println(valor);

    delay(200);
}
```

Compilamos:

```text
Build
```

y cargamos el programa:

```text
Upload
```

---

# 12. Probar el potenciómetro

Abrimos el monitor serie.

Al girar el potenciómetro deberíamos observar valores similares a:

```text
12
48
126
245
391
512
648
782
914
1008
1023
```

Si giramos en sentido contrario:

```text
1023
945
812
650
512
386
220
85
0
```

Los valores exactos pueden variar ligeramente.

Esto es normal.

---

# 13. ¿Qué está ocurriendo?

El proceso es:

```text
GIRAR POTENCIÓMETRO
        │
        ▼
CAMBIA LA TENSIÓN
        │
        ▼
       A0
        │
        ▼
CONVERSOR ANALÓGICO-DIGITAL
        │
        ▼
   VALOR 0 - 1023
        │
        ▼
PROGRAMA ARDUINO
        │
        ▼
 MONITOR SERIE
```

Tenemos por tanto nuestro primer sistema de medida analógica.

---

# 14. Guardar la lectura en una variable

En nuestro programa utilizamos:

```cpp
int valor = analogRead(POTENCIOMETRO);
```

Primero:

```cpp
analogRead(POTENCIOMETRO)
```

lee la entrada.

Después almacenamos el resultado en:

```cpp
valor
```

Por ejemplo:

```text
valor = 0

valor = 327

valor = 512

valor = 845

valor = 1023
```

---

# 15. Mostrar un texto junto al valor

Podemos mejorar la información del monitor serie utilizando:

```cpp
Serial.print();
```

y:

```cpp
Serial.println();
```

Por ejemplo:

```cpp
Serial.print("Valor del potenciometro: ");
Serial.println(valor);
```

El resultado será:

```text
Valor del potenciometro: 135
Valor del potenciometro: 268
Valor del potenciometro: 512
Valor del potenciometro: 789
```

---

# 16. Diferencia entre print() y println()

La instrucción:

```cpp
Serial.print();
```

no realiza un salto de línea.

Mientras que:

```cpp
Serial.println();
```

sí lo realiza.

Por ejemplo:

```cpp
Serial.print("Valor: ");
Serial.println(valor);
```

produce:

```text
Valor: 512
```

Pero:

```cpp
Serial.println("Valor: ");
Serial.println(valor);
```

produciría:

```text
Valor:
512
```

---

# 17. Programa mejorado

Podemos utilizar:

```cpp
#include <Arduino.h>

const int POTENCIOMETRO = A0;

void setup()
{
    Serial.begin(9600);

    Serial.println("Lectura analogica");
    Serial.println("----------------");
}

void loop()
{
    int valor = analogRead(POTENCIOMETRO);

    Serial.print("Valor: ");
    Serial.println(valor);

    delay(200);
}
```

---

# 18. Convertir la lectura en tensión

Sabemos que aproximadamente:

```text
0    → 0 V

1023 → 5 V
```

Podemos calcular la tensión mediante:

```cpp
float voltaje = valor * 5.0 / 1023.0;
```

Utilizamos una variable:

```cpp
float
```

porque el resultado puede contener decimales.

Por ejemplo:

```text
0.00 V
1.26 V
2.51 V
3.78 V
4.95 V
```

---

# 19. Programa para medir la tensión

Podemos realizar:

```cpp
#include <Arduino.h>

const int POTENCIOMETRO = A0;

void setup()
{
    Serial.begin(9600);

    Serial.println("Medida del potenciometro");
}

void loop()
{
    int valor = analogRead(POTENCIOMETRO);

    float voltaje = valor * 5.0 / 1023.0;

    Serial.print("ADC: ");
    Serial.print(valor);

    Serial.print("   Voltaje: ");
    Serial.print(voltaje);

    Serial.println(" V");

    delay(200);
}
```

En el monitor serie veremos:

```text
ADC: 102   Voltaje: 0.50 V
ADC: 256   Voltaje: 1.25 V
ADC: 511   Voltaje: 2.50 V
ADC: 768   Voltaje: 3.75 V
ADC: 1023  Voltaje: 5.00 V
```

---

# 20. ¿Qué es el ADC?

ADC significa:

```text
Analog to Digital Converter
```

es decir:

```text
Conversor Analógico-Digital
```

Su función es convertir una tensión eléctrica en un número que pueda utilizar nuestro programa.

Podemos representarlo así:

```text
TENSIÓN
0 - 5 V
   │
   ▼
┌─────────┐
│   ADC   │
└────┬────┘
     │
     ▼
NÚMERO
0 - 1023
```

En el Arduino Mega el ADC utilizado en estas prácticas tiene una resolución de:

```text
10 bits
```

Con 10 bits podemos representar:

```text
2¹⁰ = 1024 valores
```

desde:

```text
0
```

hasta:

```text
1023
```

---

# 21. Resolución aproximada

Si dividimos:

```text
5 V
```

entre:

```text
1024 niveles
```

obtenemos aproximadamente:

```text
0,00488 V
```

es decir:

```text
4,88 mV
```

por cada nivel.

Por ejemplo:

```text
ADC = 1   → aproximadamente 0,0049 V

ADC = 100 → aproximadamente 0,49 V

ADC = 512 → aproximadamente 2,50 V
```

Para nuestras prácticas no necesitaremos realizar normalmente estos cálculos manualmente.

---

# 22. Utilizar condiciones con una entrada analógica

También podemos tomar decisiones dependiendo del valor del potenciómetro.

Por ejemplo:

```cpp
if (valor < 512)
{
    Serial.println("Zona baja");
}
else
{
    Serial.println("Zona alta");
}
```

Estamos dividiendo el recorrido aproximadamente en dos zonas:

```text
0                     512                    1023
│                      │                       │
├──────────────────────┼───────────────────────┤
      ZONA BAJA                 ZONA ALTA
```

---

# 23. Programa con dos zonas

Podemos probar:

```cpp
#include <Arduino.h>

const int POTENCIOMETRO = A0;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    int valor = analogRead(POTENCIOMETRO);

    Serial.print("Valor: ");
    Serial.print(valor);

    if (valor < 512)
    {
        Serial.println(" - ZONA BAJA");
    }
    else
    {
        Serial.println(" - ZONA ALTA");
    }

    delay(200);
}
```

Al girar el potenciómetro veremos:

```text
Valor: 245 - ZONA BAJA
Valor: 387 - ZONA BAJA
Valor: 508 - ZONA BAJA
Valor: 527 - ZONA ALTA
Valor: 782 - ZONA ALTA
```

---

# 24. Dividir la entrada en tres zonas

También podemos establecer:

```text
0 ─────── 340 ─────── 680 ─────── 1023
│           │           │            │
   BAJO         MEDIO          ALTO
```

Para ello utilizamos:

```cpp
if (valor < 340)
{
    Serial.println("BAJO");
}
else if (valor < 680)
{
    Serial.println("MEDIO");
}
else
{
    Serial.println("ALTO");
}
```

Aparece una nueva estructura:

```cpp
else if
```

que permite comprobar varias condiciones.

---

# 25. Programa con tres zonas

```cpp
#include <Arduino.h>

const int POTENCIOMETRO = A0;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    int valor = analogRead(POTENCIOMETRO);

    Serial.print("Valor: ");
    Serial.print(valor);

    if (valor < 340)
    {
        Serial.println(" - BAJO");
    }
    else if (valor < 680)
    {
        Serial.println(" - MEDIO");
    }
    else
    {
        Serial.println(" - ALTO");
    }

    delay(200);
}
```

---

# Práctica

## Ejercicio 1 — Leer el potenciómetro

Monta el circuito y carga el programa básico.

Gira lentamente el potenciómetro desde un extremo hasta el otro.

Anota aproximadamente:

```text
Valor mínimo: __________

Valor central: _________

Valor máximo: __________
```

---

## Ejercicio 2 — Medir la tensión

Utiliza el programa que calcula el voltaje.

Comprueba qué valor aparece aproximadamente cuando el potenciómetro está:

```text
Al mínimo

En el centro

Al máximo
```

Los resultados deberían estar próximos a:

```text
0 V

2,5 V

5 V
```

---

## Ejercicio 3 — Dos zonas

Realiza un programa que muestre:

```text
APAGADO
```

si el valor es inferior a:

```text
512
```

y:

```text
ACTIVADO
```

si el valor es igual o superior a 512.

---

## Ejercicio 4 — Tres zonas

Divide el recorrido del potenciómetro en:

```text
BAJO

MEDIO

ALTO
```

utilizando los límites:

```text
340

680
```

---

## Ejercicio 5 — Cinco zonas

Como ampliación, divide los valores:

```text
0 - 1023
```

en cinco zonas.

El monitor serie debe mostrar:

```text
MUY BAJO

BAJO

MEDIO

ALTO

MUY ALTO
```

---

# 26. Entrada digital frente a entrada analógica

Ya podemos comparar los dos tipos de entradas que conocemos.

## Entrada digital

Por ejemplo, un pulsador:

```text
PULSADOR
   │
   ▼
D7
   │
   ▼
HIGH / LOW
```

Solamente tenemos dos estados.

---

## Entrada analógica

Por ejemplo, un potenciómetro:

```text
POTENCIÓMETRO
      │
      ▼
     A0
      │
      ▼
   0 - 1023
```

Tenemos más de mil niveles diferentes.

---

# 27. Lo que hemos aprendido

En esta lección hemos aprendido a utilizar:

```cpp
analogRead()
```

También hemos utilizado por primera vez una entrada:

```text
A0
```

y hemos trabajado con valores:

```text
0 - 1023
```

Nuestro sistema es:

```text
POTENCIÓMETRO
      │
      ▼
 TENSIÓN 0-5 V
      │
      ▼
     A0
      │
      ▼
     ADC
      │
      ▼
  0 - 1023
      │
      ▼
   PROGRAMA
      │
      ▼
MONITOR SERIE
```

También hemos introducido:

```cpp
float
```

para trabajar con números decimales y:

```cpp
else if
```

para tomar decisiones entre varias posibilidades.

En la siguiente lección combinaremos lo aprendido en las lecciones 5 y 6:

```text
POTENCIÓMETRO
      │
      ▼
 analogRead()
      │
      ▼
  0 - 1023
      │
      ▼
   ARDUINO
      │
      ▼
  0 - 255
      │
      ▼
 analogWrite()
      │
      ▼
     PWM
      │
      ▼
     LED
```

De esta forma podremos **regular directamente el brillo de un LED girando el potenciómetro**.
