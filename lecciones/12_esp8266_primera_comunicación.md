# Lección 12 — ESP8266: conexión y primeros comandos AT

## 1. Introducción

En la lección anterior aprendimos a utilizar los puertos serie hardware del Arduino Mega 2560.

Nuestro esquema era:

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
DISPOSITIVO EXTERNO
```

En esta lección sustituiremos el dispositivo externo por un:

```text
ESP8266
```

El ESP8266 permitirá posteriormente que nuestro Arduino se conecte mediante:

```text
Wi-Fi
```

Nuestro proyecto empieza a adoptar su arquitectura definitiva:

```text
SENSORES / ACTUADORES
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
       RED LOCAL
          │
          ▼
       INTERNET
```

Pero antes de intentar conectarnos a una red Wi-Fi debemos conseguir que Arduino y ESP8266 se comuniquen correctamente.

---

# 2. Objetivos

En esta lección aprenderemos a:

* Identificar el módulo ESP8266.
* Comprender para qué sirve.
* Identificar sus terminales.
* Comprender la diferencia entre lógica de 5 V y 3,3 V.
* Alimentar correctamente el ESP8266.
* Adaptar la señal TX del Arduino Mega.
* Conectar ESP8266 a `Serial1`.
* Crear un puente entre el ordenador y el ESP8266.
* Utilizar comandos AT.
* Comprobar que el módulo responde.
* Consultar información sobre su firmware.

---

# 3. ¿Qué es el ESP8266?

El ESP8266 es un circuito integrado desarrollado por Espressif que incorpora conectividad:

```text
Wi-Fi
```

y una pila de comunicaciones:

```text
TCP/IP
```

En nuestro kit encontramos el ESP8266 montado en un pequeño módulo denominado normalmente:

```text
ESP-01
```

o:

```text
ESP8266-01
```

Su función en nuestro proyecto será proporcionar conectividad Wi-Fi al Arduino Mega.

---

# 4. Arduino y ESP8266 tendrán funciones diferentes

Aunque el ESP8266 es también un microcontrolador programable, en nuestro proyecto comenzaremos utilizándolo como **módulo de comunicaciones**.

Tendremos:

```text
ARDUINO MEGA
     │
     │ controla
     ▼
Sensores y actuadores
```

y:

```text
ESP8266
     │
     │ proporciona
     ▼
    Wi-Fi
```

Ambos dispositivos se comunicarán mediante:

```text
UART
```

---

# 5. Arquitectura del sistema

El Arduino podrá enviar órdenes como:

```text
AT
```

al ESP8266.

El ESP8266 responderá:

```text
OK
```

Posteriormente Arduino podrá enviar órdenes como:

```text
Conéctate a esta red Wi-Fi
```

y el ESP8266 se encargará de realizar la conexión.

Conceptualmente:

```text
ARDUINO
   │
   │ comando AT
   ▼
ESP8266
   │
   │ ejecuta orden
   ▼
  Wi-Fi
```

---

# 6. El módulo ESP-01

El ESP-01 dispone de ocho terminales.

Los más habituales son:

```text
VCC
GND
TX
RX
EN / CH_PD
RST
GPIO0
GPIO2
```

Dependiendo de la serigrafía del módulo podremos encontrar:

```text
EN
```

o:

```text
CH_PD
```

Ambos nombres hacen referencia al pin de habilitación del chip.

---

# 7. Función de los terminales

| Terminal   | Función                                        |
| ---------- | ---------------------------------------------- |
| VCC        | Alimentación                                   |
| GND        | Masa                                           |
| TX         | Transmisión serie                              |
| RX         | Recepción serie                                |
| EN / CH_PD | Habilitación del ESP8266                       |
| RST        | Reset                                          |
| GPIO0      | Entrada/salida y selección de modo de arranque |
| GPIO2      | Entrada/salida                                 |

En esta primera práctica nos interesarán principalmente:

```text
VCC

GND

TX

RX

EN
```

---

# 8. Atención: el ESP8266 trabaja a 3,3 V

Esta es probablemente la parte más importante de la práctica.

Arduino Mega trabaja normalmente con:

```text
5 V
```

El ESP8266 trabaja con:

```text
3,3 V
```

Por tanto:

> **No debemos aplicar 5 V directamente a los terminales del ESP8266.**

Una conexión incorrecta puede dañar el módulo.

---

# 9. Dos problemas diferentes

Debemos distinguir dos cuestiones:

## Alimentación

El ESP8266 necesita aproximadamente:

```text
3,3 V
```

## Señales digitales

Su entrada:

```text
RX
```

también está diseñada para niveles lógicos de aproximadamente:

```text
3,3 V
```

Por tanto debemos solucionar:

```text
ALIMENTACIÓN
```

y:

```text
ADAPTACIÓN DE NIVELES LÓGICOS
```

---

# 10. No alimentar el ESP8266 desde el pin 3,3 V del Mega

Aunque Arduino Mega dispone de un pin:

```text
3.3V
```

no es la opción recomendable para alimentar directamente un ESP8266.

El módulo Wi-Fi puede demandar picos de corriente relativamente elevados durante la transmisión.

El pin de 3,3 V del Mega dispone de una capacidad de corriente limitada.

Por tanto utilizaremos una:

```text
FUENTE REGULADA DE 3,3 V
```

capaz de proporcionar suficiente corriente.

Una opción habitual es utilizar:

```text
módulo regulador 3,3 V
```

o:

```text
fuente externa estabilizada de 3,3 V
```

Para trabajar cómodamente con ESP8266 es recomendable disponer de una alimentación capaz de proporcionar varios cientos de miliamperios.

---

# 11. Masa común

Aunque utilicemos una alimentación externa para el ESP8266 debemos conectar:

```text
GND Arduino
```

con:

```text
GND ESP8266
```

y con:

```text
GND fuente 3,3 V
```

Todos deben compartir la misma referencia.

Tenemos:

```text
ARDUINO GND ────────┐
                    │
FUENTE GND ─────────┼──── GND común
                    │
ESP8266 GND ────────┘
```

---

# 12. Comunicación UART

En la lección anterior aprendimos:

```text
TX → RX

RX ← TX
```

Utilizaremos:

```text
Serial1
```

del Arduino Mega.

Recordemos:

```text
TX1 = D18

RX1 = D19
```

Por tanto, conceptualmente:

```text
ARDUINO MEGA                 ESP8266

TX1 D18 ───────────────────► RX

RX1 D19 ◄─────────────────── TX

GND ──────────────────────── GND
```

Pero existe un problema.

---

# 13. Problema con TX1 del Arduino

Cuando Arduino Mega transmite un nivel lógico alto por:

```text
TX1
```

puede utilizar aproximadamente:

```text
5 V
```

Pero el ESP8266 trabaja con:

```text
3,3 V
```

Por tanto no debemos conectar directamente:

```text
Mega TX1 → ESP RX
```

sin adaptar la tensión.

---

# 14. Divisor de tensión

Podemos utilizar dos resistencias para reducir aproximadamente:

```text
5 V
```

a:

```text
3,3 V
```

Por ejemplo:

```text
Arduino TX
    │
   1 kΩ
    │
    ├──────── ESP RX
    │
   2 kΩ
    │
   GND
```

El divisor produce aproximadamente:

```text
5 V × 2 / (1 + 2)
```

que resulta:

```text
≈ 3,33 V
```

Por tanto:

```text
5 V
 │
 ▼
DIVISOR
 │
 ▼
3,3 V
```

---

# 15. Conexión TX del Mega → RX del ESP8266

Realizaremos:

```text
D18 / TX1
     │
     ▼
    1 kΩ
     │
     ├──────────── ESP8266 RX
     │
     ▼
    2 kΩ
     │
     ▼
    GND
```

De esta forma protegemos la entrada RX del ESP8266.

También podría utilizarse un convertidor de niveles lógicos.

---

# 16. ESP8266 TX → Mega RX1

La salida TX del ESP8266 trabaja aproximadamente a:

```text
3,3 V
```

Este nivel puede ser interpretado como nivel alto por la entrada del ATmega2560.

Por tanto podremos realizar:

```text
ESP8266 TX ───────────── D19 / RX1
```

sin aplicar 5 V al ESP8266.

Si disponemos de un convertidor de niveles lógicos bidireccional también puede utilizarse para ambas señales.

---

# 17. Pin EN / CH_PD

Para que el ESP8266 funcione normalmente, el terminal:

```text
EN
```

o:

```text
CH_PD
```

debe mantenerse a nivel alto.

Lo conectaremos a:

```text
3,3 V
```

Nunca a 5 V.

Podemos utilizar:

```text
EN → 3,3 V
```

---

# 18. Pin RST

El terminal:

```text
RST
```

permite reiniciar el ESP8266.

Normalmente debe permanecer a nivel alto.

Si lo llevamos momentáneamente a:

```text
GND
```

el módulo se reinicia.

Conceptualmente:

```text
RST
 │
 ├── HIGH → funcionamiento normal
 │
 └── LOW  → reset
```

En esta primera práctica no necesitamos controlar el reset desde Arduino.

---

# 19. GPIO0 y modo de arranque

El terminal:

```text
GPIO0
```

tiene una función especial durante el arranque.

Entre otras cosas permite seleccionar el modo de programación del ESP8266.

En nuestro proyecto queremos que el módulo arranque normalmente ejecutando su firmware AT.

Por tanto no queremos iniciar accidentalmente el modo de programación.

En esta práctica utilizaremos el módulo en:

```text
MODO NORMAL
```

No modificaremos su firmware.

---

# 20. Esquema general

Nuestro montaje será conceptualmente:

```text
               FUENTE 3,3 V
                  │
          ┌───────┴───────┐
          │               │
          ▼               ▼
        ESP VCC          ESP EN


ARDUINO MEGA                       ESP8266
------------                       -------

D18 TX1
   │
   ▼
  1 kΩ
   │
   ├──────────────────────────────► RX
   │
  2 kΩ
   │
  GND


D19 RX1 ◄────────────────────────── TX


GND ─────────────────────────────── GND
```

Y:

```text
GND Arduino
     │
     ├──── GND ESP8266
     │
     └──── GND fuente 3,3 V
```

---

# 21. Tabla de conexiones

| ESP8266    | Conexión                                               |
| ---------- | ------------------------------------------------------ |
| VCC        | Fuente regulada 3,3 V                                  |
| GND        | GND común                                              |
| EN / CH_PD | 3,3 V                                                  |
| TX         | Arduino Mega D19 / RX1                                 |
| RX         | Arduino Mega D18 / TX1 mediante divisor de tensión     |
| RST        | Nivel alto / sin activar durante funcionamiento normal |
| GPIO0      | Configuración de arranque normal                       |
| GPIO2      | No utilizado en esta práctica                          |

---

# 22. Revisar antes de conectar

Antes de alimentar el circuito debemos comprobar:

* [ ] ESP8266 VCC está conectado a 3,3 V.
* [ ] ESP8266 EN está conectado a 3,3 V.
* [ ] ESP8266 no recibe 5 V.
* [ ] Arduino y ESP8266 comparten GND.
* [ ] TX y RX están cruzados.
* [ ] TX del Mega pasa por el divisor de tensión.
* [ ] No existen cortocircuitos.
* [ ] Hemos revisado dos veces el patillaje del ESP-01.

Solamente entonces conectaremos la alimentación.

---

# 23. El programa puente

Utilizaremos prácticamente el mismo programa desarrollado en la lección anterior.

Nuestro ordenador se comunicará con:

```text
Serial
```

Arduino copiará la información hacia:

```text
Serial1
```

y el ESP8266 responderá por el camino contrario.

Tenemos:

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
ESP8266
```

y:

```text
ESP8266
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

---

# 24. Velocidad del ESP8266

El ESP8266 con firmware AT puede estar configurado a diferentes velocidades UART.

Una velocidad muy habitual es:

```text
115200
```

aunque podemos encontrar módulos configurados a:

```text
9600
```

u otras velocidades.

Por tanto utilizaremos inicialmente:

```cpp
Serial1.begin(115200);
```

Mantendremos la comunicación con el ordenador a:

```cpp
Serial.begin(9600);
```

Los dos puertos pueden trabajar a velocidades diferentes.

---

# 25. Programa de prueba

Abrimos:

```text
src/main.cpp
```

y escribimos:

```cpp
#include <Arduino.h>

void setup()
{
    Serial.begin(9600);
    Serial1.begin(115200);

    delay(1000);

    Serial.println();
    Serial.println("================================");
    Serial.println("  Arduino Mega <-> ESP8266");
    Serial.println("================================");
    Serial.println();
    Serial.println("Puente serie iniciado");
    Serial.println("Escribe comandos AT");
    Serial.println();
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

Cargamos el programa en Arduino Mega.

---

# 26. Abrir el monitor serie

Abrimos:

```text
PlatformIO → Serial Monitor
```

La velocidad del monitor será:

```text
9600
```

porque corresponde a:

```cpp
Serial.begin(9600);
```

Recordemos que el ESP8266 trabaja independientemente mediante:

```cpp
Serial1.begin(115200);
```

---

# 27. Final de línea

Los comandos AT normalmente deben terminar correctamente.

Configuraremos el monitor serie para enviar:

```text
CR + LF
```

es decir:

```text
Carriage Return + Line Feed
```

Conceptualmente:

```text
AT + Enter
```

debe llegar al ESP8266 como una línea completa.

---

# 28. Nuestro primer comando AT

Escribimos:

```text
AT
```

Si todo funciona correctamente el ESP8266 debería responder:

```text
OK
```

Tenemos:

```text
ORDENADOR
   │
   │ AT
   ▼
ARDUINO
   │
   │ AT
   ▼
ESP8266
   │
   │ OK
   ▼
ARDUINO
   │
   │ OK
   ▼
ORDENADOR
```

Este será nuestro primer gran objetivo.

---

# 29. ¿Qué significa AT?

Los comandos AT son instrucciones de texto que permiten controlar el módulo.

Por ejemplo:

```text
AT
```

sirve para comprobar si el módulo responde.

Podemos considerarlo equivalente a preguntar:

```text
¿Estás ahí?
```

El ESP8266 responde:

```text
OK
```

---

# 30. Segundo comando: consultar firmware

Escribimos:

```text
AT+GMR
```

Este comando solicita información sobre la versión del firmware.

La respuesta dependerá del módulo.

Podemos recibir información referente a:

```text
AT version

SDK version

Firmware version
```

Los valores concretos pueden ser diferentes entre módulos.

No debemos preocuparnos si no coinciden exactamente con los de otro grupo.

---

# 31. Reiniciar el módulo

Podemos utilizar:

```text
AT+RST
```

Este comando reinicia el ESP8266.

Después del reinicio aparecerán diferentes mensajes.

Finalmente deberíamos recibir algo similar a:

```text
ready
```

Esto indica que el módulo ha terminado de arrancar.

---

# 32. No confundir reset de Arduino y reset del ESP8266

Tenemos dos dispositivos:

```text
ARDUINO MEGA
```

y:

```text
ESP8266
```

Cada uno tiene su propio microcontrolador.

Por tanto:

```text
Reset Arduino
```

y:

```text
Reset ESP8266
```

son operaciones diferentes.

Cuando escribimos:

```text
AT+RST
```

estamos reiniciando:

```text
ESP8266
```

no Arduino Mega.

---

# 33. Desactivar el eco

Podemos encontrar que el ESP8266 devuelve también los comandos que escribimos.

Esto se denomina:

```text
ECHO
```

Podemos desactivarlo mediante:

```text
ATE0
```

Y volverlo a activar:

```text
ATE1
```

Para nuestras futuras comunicaciones suele resultar más cómodo trabajar sin eco.

---

# 34. Primer conjunto de comandos

En esta práctica probaremos:

| Comando  | Función                      |
| -------- | ---------------------------- |
| `AT`     | Comprobar comunicación       |
| `AT+GMR` | Mostrar versión del firmware |
| `AT+RST` | Reiniciar ESP8266            |
| `ATE0`   | Desactivar eco               |
| `ATE1`   | Activar eco                  |

---

# 35. ¿Qué ocurre si AT no responde?

Si escribimos:

```text
AT
```

y no obtenemos:

```text
OK
```

no debemos modificar inmediatamente el programa.

Seguiremos un procedimiento ordenado.

---

# 36. Primera comprobación — alimentación

Debemos comprobar:

```text
VCC → 3,3 V
```

```text
EN → 3,3 V
```

```text
GND común
```

Una alimentación insuficiente puede provocar:

* Reinicios.
* Respuestas incompletas.
* Caracteres extraños.
* Funcionamiento intermitente.
* Fallos al activar Wi-Fi.

---

# 37. Segunda comprobación — TX y RX

Comprobaremos:

```text
Mega TX1 D18 → divisor → ESP RX
```

y:

```text
ESP TX → Mega RX1 D19
```

Recordemos:

```text
TX → RX

RX ← TX
```

---

# 38. Tercera comprobación — velocidad

Si seguimos sin obtener respuesta, el ESP8266 podría utilizar otra velocidad.

Podemos probar:

```cpp
Serial1.begin(9600);
```

Después:

```cpp
Serial1.begin(57600);
```

o:

```cpp
Serial1.begin(115200);
```

Una velocidad incorrecta suele producir:

```text
caracteres extraños
```

o ausencia de respuestas válidas.

---

# 39. Programa para probar diferentes velocidades

Podemos modificar manualmente:

```cpp
Serial1.begin(115200);
```

y realizar varias pruebas.

Por ejemplo:

```text
115200
```

si no funciona:

```text
9600
```

y posteriormente otras velocidades si fuera necesario.

No debemos cambiar simultáneamente varias cosas del circuito.

Seguiremos:

```text
CAMBIAR UNA COSA
       ↓
PROBAR
       ↓
ANOTAR RESULTADO
```

---

# 40. Cuarta comprobación — final de línea

Si el módulo parece recibir datos pero no ejecuta los comandos debemos comprobar que estamos enviando:

```text
CR + LF
```

Los comandos necesitan un final de línea adecuado.

---

# 41. Quinta comprobación — reset

Podemos reiniciar el ESP8266.

Si disponemos de acceso al terminal:

```text
RST
```

podemos llevarlo brevemente a:

```text
GND
```

y liberarlo.

También podemos apagar y volver a alimentar el módulo.

Después esperaremos a que termine de arrancar.

---

# 42. Diagnóstico sistemático

Si no funciona seguiremos este orden:

```text
1. ALIMENTACIÓN
       ↓
2. GND COMÚN
       ↓
3. TX / RX
       ↓
4. DIVISOR DE TENSIÓN
       ↓
5. EN
       ↓
6. VELOCIDAD UART
       ↓
7. CR + LF
       ↓
8. RESET
```

No cambiaremos conexiones al azar.

---

# Práctica

## Ejercicio 1 — Identificar el módulo

Observa físicamente el ESP8266.

Realiza un dibujo o fotografía e identifica:

```text
VCC

GND

TX

RX

EN / CH_PD

RST

GPIO0

GPIO2
```

Añádelo a tus apuntes.

---

## Ejercicio 2 — Revisar las tensiones

Completa:

| Elemento             | Tensión |
| -------------------- | ------: |
| Lógica Arduino Mega  |         |
| Alimentación ESP8266 |         |
| Señal RX ESP8266     |         |

Explica por qué no debemos conectar directamente:

```text
Mega TX → ESP RX
```

---

## Ejercicio 3 — Calcular el divisor

Tenemos:

```text
R1 = 1 kΩ

R2 = 2 kΩ
```

y:

```text
Vin = 5 V
```

Calcula aproximadamente:

```text
Vout
```

utilizando:

```text
Vout = Vin × R2 / (R1 + R2)
```

Comprueba que obtenemos aproximadamente:

```text
3,3 V
```

---

## Ejercicio 4 — Comprobar comunicación

Construye el circuito.

Carga el programa puente.

Escribe:

```text
AT
```

Debes obtener:

```text
OK
```

No continúes con los siguientes ejercicios hasta conseguir una comunicación estable.

---

## Ejercicio 5 — Consultar el firmware

Ejecuta:

```text
AT+GMR
```

Copia en tus apuntes la información obtenida.

Compara los resultados con los de otro grupo.

¿Todos los módulos tienen exactamente la misma versión?

---

## Ejercicio 6 — Reiniciar

Ejecuta:

```text
AT+RST
```

Observa los mensajes generados durante el arranque.

Identifica cuándo el módulo está nuevamente preparado.

---

## Ejercicio 7 — Eco

Ejecuta:

```text
ATE0
```

Después:

```text
AT
```

Observa el resultado.

Activa de nuevo el eco mediante:

```text
ATE1
```

y compara.

---

# 43. Investigación

Busca documentación sobre los siguientes comandos:

```text
AT

AT+GMR

AT+RST

ATE0

ATE1
```

Para cada uno indica:

| Comando | Función | Respuesta esperada |
| ------- | ------- | ------------------ |
| AT      |         |                    |
| AT+GMR  |         |                    |
| AT+RST  |         |                    |
| ATE0    |         |                    |
| ATE1    |         |                    |

---

# 44. Todavía no nos conectamos al Wi-Fi

Es importante no avanzar demasiado rápido.

En esta lección queremos únicamente demostrar:

```text
ARDUINO MEGA
      │
      │ UART
      ▼
   ESP8266
      │
      ▼
RESPONDE A AT
```

Si conseguimos:

```text
AT
```

y recibimos:

```text
OK
```

la práctica ha alcanzado su objetivo principal.

---

# 45. ¿Por qué separar las prácticas?

Si intentáramos hacer directamente:

```text
Arduino
   +
ESP8266
   +
Wi-Fi
   +
Internet
   +
Servidor web
```

y algo fallase, tendríamos muchos lugares donde buscar el problema.

En cambio trabajaremos progresivamente:

```text
PASO 1
UART
   ↓
PASO 2
ESP8266 responde
   ↓
PASO 3
Wi-Fi
   ↓
PASO 4
Dirección IP
   ↓
PASO 5
TCP/IP
   ↓
PASO 6
Servidor web
```

Así podremos localizar los errores mucho más fácilmente.

---

# 46. Relación con nuestro proyecto final

Al terminar esta práctica tendremos:

```text
ORDENADOR
     │
     │ USB
     ▼
  ARDUINO
     │
     │ UART
     ▼
  ESP8266
```

En la siguiente práctica añadiremos:

```text
       ESP8266
          │
          │ Wi-Fi
          ▼
       ROUTER
          │
          ▼
      RED LOCAL
```

Después podremos evolucionar hacia:

```text
NAVEGADOR
    │
    │ Wi-Fi
    ▼
ESP8266
    │
    ▼
ARDUINO
    │
    ▼
ACTUADORES
```

y posteriormente:

```text
SENSORES
    │
    ▼
ARDUINO
    │
    ▼
ESP8266
    │
    ▼
INFLUXDB
    │
    ▼
GRAFANA
```

---

# 47. Lo que hemos aprendido

En esta lección hemos incorporado el primer componente fundamental de nuestro proyecto IoT:

```text
ESP8266
```

Hemos aprendido que:

```text
Arduino Mega → lógica de 5 V
```

mientras que:

```text
ESP8266 → lógica y alimentación de 3,3 V
```

Por esta razón debemos adaptar la señal:

```text
Mega TX1
    │
    ▼
DIVISOR DE TENSIÓN
    │
    ▼
ESP RX
```

También hemos utilizado:

```text
Serial  → ordenador

Serial1 → ESP8266
```

y hemos creado:

```text
ORDENADOR
      │
      ▼
ARDUINO MEGA
      │
      ▼
ESP8266
```

Finalmente hemos comenzado a utilizar comandos:

```text
AT
AT+GMR
AT+RST
ATE0
ATE1
```

El resultado fundamental de esta lección debe ser:

```text
AT
 │
 ▼
ESP8266
 │
 ▼
OK
```

Cuando consigamos una respuesta `OK` estable, estaremos preparados para la siguiente etapa.

**En la Lección 13 conectaremos el ESP8266 a una red Wi-Fi, consultaremos las redes disponibles, configuraremos el modo estación y obtendremos su dirección IP.**
