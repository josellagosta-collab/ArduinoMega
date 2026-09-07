# Lección 1 — Primer programa con Arduino Mega 2560 R3

## 1. Objetivos

En esta primera lección aprenderemos a:

* Reconocer la placa Arduino Mega 2560 R3.
* Crear un programa básico para Arduino.
* Comprender las funciones `setup()` y `loop()`.
* Compilar y cargar un programa utilizando PlatformIO.
* Utilizar el puerto serie.
* Visualizar mensajes enviados por Arduino mediante el monitor serie.

---

## 2. Material necesario

Para esta práctica solamente necesitamos:

* Arduino Mega 2560 R3.
* Cable USB.
* Ordenador con Visual Studio Code.
* Extensión PlatformIO IDE.

No necesitamos ningún componente electrónico adicional.

---

## 3. Arduino Mega 2560 R3

Arduino Mega 2560 R3 es una placa basada en el microcontrolador **ATmega2560**.

Dispone de numerosos pines de entrada y salida, lo que permite conectar sensores, pulsadores, LED, motores, pantallas y muchos otros dispositivos.

Durante las próximas lecciones iremos utilizando diferentes componentes del kit.

En esta primera práctica únicamente utilizaremos la propia placa.

---

## 4. Estructura básica de un programa Arduino

Un programa Arduino contiene normalmente dos funciones principales:

```cpp
void setup()
{

}

void loop()
{

}
```

### `setup()`

La función:

```cpp
setup()
```

se ejecuta **una sola vez** cuando Arduino arranca o cuando se reinicia.

Se utiliza principalmente para realizar configuraciones iniciales.

Por ejemplo:

```cpp
Serial.begin(9600);
```

configura la comunicación serie.

---

### `loop()`

La función:

```cpp
loop()
```

se ejecuta continuamente mientras Arduino esté funcionando.

Cuando llega al final de la función vuelve automáticamente al principio.

Podemos imaginar su funcionamiento así:

```text
Encender Arduino
       │
       ▼
    setup()
       │
       │ una vez
       ▼
    loop()
       │
       ▼
    loop()
       │
       ▼
    loop()
       │
       ▼
      ...
```

---

## 5. Nuestro primer programa

Vamos a realizar un programa que envíe mensajes desde Arduino al ordenador.

En PlatformIO abrimos:

```text
src/main.cpp
```

y escribimos:

```cpp
#include <Arduino.h>

void setup()
{
    Serial.begin(9600);

    Serial.println("Arduino Mega 2560 R3");
    Serial.println("Conexion serie funcionando correctamente");
}

void loop()
{
    Serial.println("Arduino funcionando...");

    delay(1000);
}
```

---

## 6. La librería Arduino

La primera línea del programa es:

```cpp
#include <Arduino.h>
```

Cuando trabajamos con PlatformIO debemos incluir esta línea para utilizar las funciones habituales del framework Arduino.

Gracias a ella podemos utilizar instrucciones como:

```cpp
Serial.begin()
Serial.println()
delay()
digitalWrite()
digitalRead()
```

En las próximas lecciones iremos conociendo estas funciones.

---

## 7. Configuración del puerto serie

La instrucción:

```cpp
Serial.begin(9600);
```

inicia la comunicación serie entre Arduino y el ordenador.

El número:

```text
9600
```

indica la velocidad de comunicación.

Esta velocidad se expresa en **baudios**.

El ordenador y Arduino deben utilizar la misma velocidad.

---

## 8. Enviar información al ordenador

Para enviar texto utilizamos:

```cpp
Serial.println();
```

Por ejemplo:

```cpp
Serial.println("Hola");
```

envía el texto:

```text
Hola
```

al ordenador.

`println()` añade automáticamente un salto de línea después del texto.

---

## 9. La función delay()

En nuestro programa encontramos:

```cpp
delay(1000);
```

`delay()` detiene temporalmente la ejecución del programa.

El tiempo se expresa en **milisegundos**.

Por tanto:

```text
1000 ms = 1 segundo
```

Algunos ejemplos:

| Instrucción    |       Tiempo |
| -------------- | -----------: |
| `delay(100);`  | 0,1 segundos |
| `delay(500);`  | 0,5 segundos |
| `delay(1000);` |    1 segundo |
| `delay(2000);` |   2 segundos |

---

## 10. Configuración de PlatformIO

El archivo:

```text
platformio.ini
```

debe estar configurado para nuestra placa Arduino Mega 2560 R3.

Podemos utilizar:

```ini
[env:megaatmega2560]
platform = atmelavr
board = megaatmega2560
framework = arduino

upload_port = COM7
monitor_port = COM7
monitor_speed = 9600
```

En nuestro ordenador Arduino está conectado actualmente al:

```text
COM7
```

Si Windows asigna otro puerto en el futuro tendremos que modificar `upload_port` y `monitor_port`.

---

## 11. Compilar el programa

Antes de transferir el programa podemos comprobar que no contiene errores.

Desde PlatformIO pulsamos:

```text
Build
```

Si el programa es correcto aparecerá:

```text
SUCCESS
```

Si existe algún error tendremos que corregirlo antes de continuar.

---

## 12. Cargar el programa

Conectamos Arduino Mega al ordenador mediante USB.

Después pulsamos:

```text
Upload
```

PlatformIO compilará el programa y lo transferirá al microcontrolador.

Si todo funciona correctamente aparecerá:

```text
SUCCESS
```

Arduino comenzará inmediatamente a ejecutar el programa.

---

## 13. Abrir el monitor serie

Abrimos:

```text
PlatformIO: Serial Monitor
```

La velocidad configurada debe ser:

```text
9600
```

En pantalla veremos algo parecido a:

```text
Arduino Mega 2560 R3
Conexion serie funcionando correctamente
Arduino funcionando...
Arduino funcionando...
Arduino funcionando...
Arduino funcionando...
```

El mensaje:

```text
Arduino funcionando...
```

aparecerá aproximadamente una vez por segundo.

---

## 14. ¿Qué está ocurriendo?

Cuando encendemos Arduino se ejecuta:

```cpp
setup()
```

Por tanto, solamente una vez aparecen:

```text
Arduino Mega 2560 R3
Conexion serie funcionando correctamente
```

Después Arduino entra en:

```cpp
loop()
```

Dentro encontramos:

```cpp
Serial.println("Arduino funcionando...");
delay(1000);
```

Arduino envía el mensaje, espera un segundo y vuelve a comenzar `loop()`.

El proceso continúa indefinidamente:

```text
Enviar mensaje
     │
     ▼
Esperar 1 segundo
     │
     ▼
Enviar mensaje
     │
     ▼
Esperar 1 segundo
     │
     ▼
     ...
```

---

# Práctica

## Ejercicio 1 — Cambiar el mensaje

Modifica el programa para que muestre:

```text
Mi primer programa con Arduino
```

Comprueba el resultado utilizando el monitor serie.

---

## Ejercicio 2 — Modificar el tiempo

Cambia:

```cpp
delay(1000);
```

por:

```cpp
delay(2000);
```

Observa qué ocurre.

Después prueba:

```cpp
delay(500);
```

---

## Ejercicio 3 — Crear un contador

Modifica el programa para obtener:

```text
Contador: 1
Contador: 2
Contador: 3
Contador: 4
...
```

Para ello podemos crear una variable:

```cpp
int contador = 0;
```

incrementarla mediante:

```cpp
contador++;
```

y mostrarla utilizando:

```cpp
Serial.println(contador);
```

Intenta construir el programa antes de consultar una posible solución.

---

## 15. Lo que hemos aprendido

Después de completar esta lección debemos saber identificar y utilizar:

```cpp
#include <Arduino.h>

void setup()

void loop()

Serial.begin()

Serial.println()

delay()
```

También debemos saber realizar el proceso:

```text
Escribir programa
       ↓
Compilar
       ↓
Cargar en Arduino
       ↓
Ejecutar
       ↓
Observar el monitor serie
```

En la siguiente lección comenzaremos a utilizar los componentes electrónicos del kit conectando nuestro primer **LED externo al Arduino Mega 2560 R3**.
