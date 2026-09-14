Claro. La **Lección 21** será el **proyecto final autónomo**, de forma que ya no demos a los alumnos un programa completo para copiar. Tendrán que diseñar su solución aplicando lo aprendido en las lecciones anteriores, documentarla y demostrar físicamente que funciona.

# Lección 21 — Proyecto final IoT

## 1. Introducción

A lo largo de las lecciones anteriores hemos aprendido progresivamente a utilizar el **Arduino Mega 2560 R3** y los componentes del kit.

También hemos añadido conectividad mediante el **ESP8266** y hemos construido una pequeña arquitectura IoT utilizando:

```text
Arduino Mega
      │
      ▼
   ESP8266
      │
      ▼
     Wi-Fi
      │
      ├──────────► Aplicación web
      │
      └──────────► InfluxDB
                        │
                        ▼
                     Grafana
```

En esta última lección no seguiremos un montaje completamente definido.

Cada grupo deberá **diseñar, construir, programar, documentar y demostrar su propio proyecto IoT**.

---

# 2. Objetivos

Al finalizar el proyecto el alumno deberá ser capaz de:

* Diseñar un sistema electrónico basado en Arduino.
* Seleccionar sensores y actuadores adecuados.
* Buscar y comprender la documentación técnica de los componentes.
* Realizar correctamente las conexiones.
* Programar el Arduino Mega.
* Utilizar el ESP8266.
* Conectar el proyecto a una red Wi-Fi.
* Crear una interfaz web de control.
* Enviar datos mediante la red.
* Almacenar medidas en InfluxDB.
* Crear un dashboard en Grafana.
* Diagnosticar problemas de hardware y software.
* Documentar técnicamente el proyecto.
* Demostrar el funcionamiento del montaje.

---

# 3. Organización

El proyecto se realizará:

```text
POR PAREJAS
```

Cada grupo desarrollará una solución diferente o introducirá suficientes modificaciones para que su proyecto pueda considerarse propio.

El profesor actuará principalmente como apoyo y supervisión.

---

# 4. Requisitos mínimos

El proyecto deberá utilizar obligatoriamente:

```text
Arduino Mega 2560 R3
```

y:

```text
ESP8266
```

Además deberá incorporar como mínimo:

```text
2 sensores o elementos de entrada
```

y:

```text
2 actuadores o elementos de salida
```

Por tanto, el mínimo será:

```text
             ┌── Entrada 1
             │
             ├── Entrada 2
             │
Arduino Mega ┤
             │
             ├── Salida 1
             │
             └── Salida 2
```

No es obligatorio limitarse a cuatro componentes.

---

# 5. Selección de componentes

Los alumnos podrán utilizar los componentes disponibles en el kit.

Se valorará especialmente la utilización de componentes que no hayan sido utilizados extensamente en las prácticas guiadas.

Por ejemplo:

```text
Sensores / entradas

LDR
Termistor
Pulsadores
Joystick
Sensor de sonido
Sensor de distancia
Potenciómetro
Receptor infrarrojo
```

y:

```text
Actuadores / salidas

LED
LED RGB
Zumbador
Servo
Motor
Relé
Display
Matriz LED
```

La selección dependerá del material disponible.

---

# 6. Investigación de los componentes

Antes de realizar las conexiones, el grupo deberá investigar cada componente seleccionado.

Para cada uno deberá determinar:

* Nombre.
* Función.
* Tensión de funcionamiento.
* Pines.
* Tipo de señal.
* Forma de conexión.
* Necesidad de resistencias u otros componentes.
* Librerías necesarias.
* Ejemplo básico de funcionamiento.

No se debe conectar un componente simplemente porque un esquema encontrado en Internet indique dónde colocar los cables.

El alumno deberá comprender **qué está conectando y por qué**.

---

# 7. Esquema del proyecto

Antes de montar el circuito deberá elaborarse un esquema.

Por ejemplo:

```text
                         ┌──── Sensor 1
                         │
                         ├──── Sensor 2
                         │
                    ARDUINO MEGA
                         │
                         ├──── Actuador 1
                         │
                         └──── Actuador 2
                         │
                      Serial1
                         │
                         ▼
                      ESP8266
                         │
                       Wi-Fi
                         │
              ┌──────────┴───────────┐
              │                      │
              ▼                      ▼
         CONTROL WEB              INFLUXDB
                                     │
                                     ▼
                                  GRAFANA
```

Este esquema deberá incluirse en la documentación.

---

# 8. Asignación de pines

Antes de programar se elaborará una tabla.

Ejemplo:

| Componente | Función           | Pin Arduino |
| ---------- | ----------------- | ----------- |
| Sensor 1   | Entrada analógica | A0          |
| Sensor 2   | Entrada digital   | D4          |
| Actuador 1 | Salida            | D7          |
| Actuador 2 | PWM               | D8          |
| ESP8266 TX | Comunicación      | RX1 / D19   |
| ESP8266 RX | Comunicación      | TX1 / D18   |

La tabla real dependerá del proyecto de cada grupo.

---

# 9. Pruebas individuales

No se debe construir todo el proyecto y después intentar hacerlo funcionar.

Cada componente deberá probarse individualmente.

El procedimiento recomendado será:

```text
Componente 1
    ↓
montar
    ↓
programar
    ↓
probar
    ↓
FUNCIONA
    ↓
Componente 2
    ↓
montar
    ↓
programar
    ↓
probar
```

Solo después se integrarán los componentes.

---

# 10. Programas de prueba

Para cada componente nuevo se deberá desarrollar un pequeño programa independiente.

Por ejemplo:

```text
pruebas/
│
├── prueba_sensor1.cpp
├── prueba_sensor2.cpp
├── prueba_actuador1.cpp
└── prueba_actuador2.cpp
```

Estos programas deberán conservarse.

Formarán parte de la entrega.

---

# 11. Integración con Arduino

Una vez comprobados individualmente los componentes se desarrollará el programa principal.

Una posible estructura será:

```cpp
#include <Arduino.h>

void setup()
{
    // Configuración
}

void loop()
{
    // Leer sensores

    // Procesar información

    // Controlar actuadores

    // Atender comunicaciones

    // Enviar datos
}
```

No se proporcionará un programa completo para copiar.

Cada grupo deberá desarrollar el suyo.

---

# 12. Uso de funciones

El programa deberá estar organizado mediante funciones.

Por ejemplo:

```cpp
void leerSensores()
{
}
```

```cpp
void controlarActuadores()
{
}
```

```cpp
void procesarWeb()
{
}
```

```cpp
void enviarInfluxDB()
{
}
```

Se evitará introducir todo el código dentro de:

```cpp
loop()
```

---

# 13. Comunicación con ESP8266

El ESP8266 estará conectado mediante:

```text
Arduino Mega               ESP8266

TX1 D18 ── adaptación ───► RX

RX1 D19 ◄──────────────── TX

GND ───────────────────── GND
```

Utilizaremos:

```cpp
Serial1.begin(9600);
```

si se mantiene la configuración utilizada durante las prácticas anteriores.

---

# 14. Conectividad Wi-Fi

El proyecto deberá conectarse a una red Wi-Fi.

El alumno deberá comprobar:

```text
ESP8266
   │
   ▼
red Wi-Fi
   │
   ▼
dirección IP
```

y demostrar que existe comunicación con los servicios necesarios.

---

# 15. Interfaz web

El proyecto deberá disponer de una interfaz web sencilla.

No se valorará principalmente el diseño gráfico.

Se valorará que sea:

* Clara.
* Funcional.
* Comprensible.
* Adecuada al proyecto.

Por ejemplo:

```text
+----------------------------------+
|       CONTROL DEL SISTEMA        |
+----------------------------------+
|                                  |
| Temperatura: 24 °C               |
| Luminosidad: 620                 |
|                                  |
| Luz                              |
| [ ENCENDER ] [ APAGAR ]          |
|                                  |
| Servo                            |
| [ IZQUIERDA ] [ CENTRO ] [DCHA.] |
|                                  |
+----------------------------------+
```

---

# 16. Control de actuadores

Desde la interfaz web deberá poder controlarse al menos **un actuador**.

Por ejemplo:

```text
Navegador
    │
    │ /luz/on
    ▼
ESP8266
    │
    ▼
Arduino
    │
    ▼
LED
```

También podrían utilizarse órdenes como:

```text
/servo/izquierda
```

```text
/servo/centro
```

```text
/servo/derecha
```

La elección dependerá del proyecto.

---

# 17. Monitorización mediante InfluxDB

El sistema deberá enviar como mínimo **dos variables** a InfluxDB.

Por ejemplo:

```text
temperatura
```

y:

```text
luminosidad
```

Otro proyecto podría almacenar:

```text
distancia
```

```text
estado_motor
```

etc.

---

# 18. Diseñar los datos

Los alumnos deberán decidir qué información quieren almacenar.

Por ejemplo:

```text
ambiente temperatura=24.6,luminosidad=627
```

Otro proyecto:

```text
robot distancia=37.5,motor=1
```

Deberán poder explicar:

```text
measurement
fields
values
```

utilizados.

---

# 19. InfluxDB

Se utilizará la arquitectura aprendida en la Lección 18:

```text
Arduino
   │
   ▼
ESP8266
   │
   │ HTTP POST
   ▼
InfluxDB
```

El alumno deberá comprobar que las escrituras producen correctamente:

```text
HTTP/1.1 204 No Content
```

y verificar que los datos aparecen en InfluxDB.

---

# 20. Grafana

Cada proyecto deberá disponer de su propio dashboard.

El dashboard deberá incluir como mínimo:

```text
1 gráfica temporal
```

```text
1 indicador Stat
```

```text
1 Gauge
```

Además se podrán añadir otros paneles.

---

# 21. Ejemplo de dashboard

Un proyecto ambiental podría tener:

```text
┌───────────────────────────────────────────┐
│          ESTACIÓN AMBIENTAL              │
├───────────────────────────────────────────┤
│                                           │
│       TEMPERATURA                         │
│       gráfica temporal                    │
│                                           │
├─────────────────────┬─────────────────────┤
│                     │                     │
│ Temperatura actual  │    Luminosidad      │
│                     │                     │
│      24.6 °C        │      GAUGE          │
│                     │                     │
├─────────────────────┴─────────────────────┤
│                                           │
│       HISTÓRICO DE LUMINOSIDAD            │
│                                           │
└───────────────────────────────────────────┘
```

---

# 22. Actualización

El dashboard deberá actualizarse automáticamente.

Por ejemplo:

```text
Refresh:
10s
```

El intervalo deberá guardar relación con la frecuencia con la que Arduino envía las medidas.

---

# 23. Control y monitorización

El proyecto deberá distinguir claramente entre:

```text
CONTROL
```

y:

```text
MONITORIZACIÓN
```

Control significa:

```text
Usuario
   ↓
orden
   ↓
Arduino
   ↓
actuador
```

Monitorización significa:

```text
sensor
   ↓
Arduino
   ↓
InfluxDB
   ↓
Grafana
   ↓
usuario
```

Un sistema IoT puede utilizar ambas simultáneamente.

---

# 24. Evitar `delay()` excesivos

En proyectos anteriores hemos utilizado:

```cpp
delay(10000);
```

porque facilitaba las primeras prácticas.

En el proyecto final intentaremos evitar pausas largas que impidan atender otras funciones.

Se recomienda utilizar:

```cpp
millis()
```

Por ejemplo:

```cpp
unsigned long ultimoEnvio = 0;

const unsigned long intervalo = 10000;

void loop()
{
    if (millis() - ultimoEnvio >= intervalo)
    {
        ultimoEnvio = millis();

        // enviar datos
    }

    // continuar atendiendo otras funciones
}
```

De esta manera Arduino puede continuar trabajando mientras espera el siguiente envío.

---

# 25. ¿Por qué es importante?

Con:

```cpp
delay(10000);
```

Arduino queda esperando durante 10 segundos.

En cambio:

```cpp
millis()
```

permite:

```text
leer sensores
+
atender órdenes web
+
controlar actuadores
+
comprobar comunicaciones
```

mientras transcurre el tiempo.

---

# 26. Gestión de errores

El proyecto deberá contemplar errores básicos.

Por ejemplo:

```text
ESP8266 no responde
```

```text
Wi-Fi no conecta
```

```text
InfluxDB no responde
```

```text
sensor devuelve un valor incorrecto
```

El monitor serie deberá proporcionar información útil.

Por ejemplo:

```text
Wi-Fi conectado

Sensor temperatura: 24.7

Enviando a InfluxDB...

HTTP 204

Dato almacenado
```

---

# 27. Monitor serie

Durante el desarrollo utilizaremos:

```cpp
Serial.begin(9600);
```

El monitor serie servirá como herramienta de diagnóstico.

El programa deberá mostrar información suficiente para comprender qué está haciendo.

---

# 28. No publicar credenciales

El repositorio GitHub no deberá contener:

```text
contraseñas Wi-Fi
```

ni:

```text
tokens de InfluxDB
```

Antes de realizar la entrega deberán sustituirse por:

```cpp
const char* SSID = "TU_WIFI";
const char* PASSWORD = "TU_PASSWORD";

const char* TOKEN = "TU_TOKEN";
```

---

# 29. Repositorio

Cada proyecto deberá tener una estructura ordenada.

Por ejemplo:

```text
ProyectoIoT/
│
├── README.md
│
├── docs/
│   └── proyecto.pdf
│
├── src/
│   └── main.cpp
│
└── pruebas/
    ├── sensor1.cpp
    ├── sensor2.cpp
    ├── actuador1.cpp
    └── actuador2.cpp
```

---

# 30. README

El archivo:

```text
README.md
```

deberá explicar brevemente:

* Nombre del proyecto.
* Objetivo.
* Componentes.
* Funcionamiento.
* Cómo realizar las conexiones.
* Cómo ejecutar el proyecto.

---

# 31. Documentación técnica

Se entregará un documento PDF.

Nombre recomendado:

```text
proyecto_final_iot.pdf
```

Deberá contener como mínimo:

1. Portada.
2. Objetivo.
3. Descripción del proyecto.
4. Arquitectura.
5. Lista de componentes.
6. Documentación de los componentes.
7. Esquema de conexiones.
8. Tabla de pines.
9. Explicación del programa.
10. Comunicación Wi-Fi.
11. Interfaz web.
12. InfluxDB.
13. Grafana.
14. Pruebas.
15. Problemas encontrados.
16. Soluciones aplicadas.
17. Conclusiones.

---

# 32. Capturas

El PDF deberá incluir capturas propias de:

* Montaje.
* Monitor serie.
* Interfaz web.
* Datos en InfluxDB.
* Dashboard de Grafana.

Las capturas deberán corresponder al proyecto realmente realizado.

---

# 33. Diagrama de arquitectura

El documento deberá incluir un diagrama propio.

Por ejemplo:

```text
                         USUARIO
                            │
                            ▼
                       NAVEGADOR
                            │
                          Wi-Fi
                            │
                            ▼
                         ESP8266
                            │
                         Serial1
                            │
                            ▼
                     ARDUINO MEGA
                     │          │
                 SENSORES   ACTUADORES
                     │
                     ▼
                  DATOS
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

No será suficiente copiar este ejemplo. Cada grupo deberá representar **su propio proyecto**.

---

# 34. Propuesta del proyecto

Antes de comenzar el montaje cada pareja presentará al profesor una propuesta breve indicando:

```text
Nombre del proyecto
```

```text
Objetivo
```

```text
Sensores
```

```text
Actuadores
```

```text
Datos que almacenará
```

```text
Funciones de la página web
```

El profesor deberá aprobar la propuesta antes de iniciar el desarrollo.

---

# 35. Ejemplo 1 — Estación ambiental

Una posibilidad sería:

```text
LDR ───────────────┐
                   │
Temperatura ───────┤
                   ▼
             Arduino Mega
                   │
                   ├────► LED
                   │
                   └────► Zumbador
                   │
                   ▼
                ESP8266
                   │
          ┌────────┴────────┐
          ▼                 ▼
        WEB              InfluxDB
                             │
                             ▼
                          Grafana
```

---

# 36. Ejemplo 2 — Aparcamiento inteligente

Otra posibilidad:

```text
Sensor distancia
       │
       ▼
Arduino Mega
   │       │
   ▼       ▼
 LED     Servo
   │
   ▼
ESP8266
   │
   ├────► Web
   │
   └────► InfluxDB
              │
              ▼
           Grafana
```

El servo podría representar una barrera.

---

# 37. Ejemplo 3 — Sistema de alarma

```text
Sensor
movimiento
    │
    ▼
Arduino Mega
   │       │
   ▼       ▼
 LED    Zumbador
   │
   ▼
ESP8266
   │
   ├────► Web
   │
   └────► InfluxDB
              │
              ▼
           Grafana
```

InfluxDB podría almacenar cuándo se producen las detecciones.

---

# 38. Originalidad

Los ejemplos anteriores son solamente orientativos.

Se valorará que el grupo adapte el proyecto a una idea propia.

No es necesario que el proyecto sea extremadamente complejo.

Es preferible:

```text
proyecto sencillo
+
bien diseñado
+
bien programado
+
bien documentado
+
funcionando
```

que un proyecto muy ambicioso que no funcione correctamente.

---

# 39. Desarrollo incremental

El proyecto deberá desarrollarse siguiendo este orden:

```text
1. Diseñar
      ↓
2. Investigar componentes
      ↓
3. Probar sensores
      ↓
4. Probar actuadores
      ↓
5. Integrar Arduino
      ↓
6. Añadir ESP8266
      ↓
7. Añadir control web
      ↓
8. Añadir InfluxDB
      ↓
9. Añadir Grafana
      ↓
10. Realizar pruebas finales
      ↓
11. Documentar
```

No se recomienda intentar desarrollar todo simultáneamente.

---

# 40. Uso de Internet y documentación

Los alumnos podrán consultar:

* Hojas de características.
* Documentación del fabricante.
* Ejemplos.
* Tutoriales.
* Foros técnicos.
* Documentación de Arduino.
* Documentación de las librerías utilizadas.

Deberán indicar en su documentación las principales fuentes utilizadas.

---

# 41. Uso de IA

Si se utilizan herramientas de IA como apoyo, el alumno seguirá siendo responsable del programa entregado.

Durante la demostración el profesor podrá preguntar:

```text
¿Qué hace esta función?
```

```text
¿Por qué utilizas este pin?
```

```text
¿Por qué necesitas esta resistencia?
```

```text
¿Qué significa este comando AT?
```

```text
¿Qué ocurre si InfluxDB está apagado?
```

```text
¿Por qué utilizas millis()?
```

El alumno deberá ser capaz de explicar su solución.

---

# 42. Comprobación presencial

El profesor pasará por los puestos y comprobará el proyecto físicamente.

No será suficiente presentar:

```text
PDF
+
capturas
+
código
```

El montaje deberá funcionar.

---

# 43. Demostración

Cada pareja deberá demostrar:

```text
1. Encendido del sistema.
```

```text
2. Lectura de los sensores.
```

```text
3. Funcionamiento de los actuadores.
```

```text
4. Conexión Wi-Fi.
```

```text
5. Control mediante navegador.
```

```text
6. Envío de datos a InfluxDB.
```

```text
7. Visualización mediante Grafana.
```

---

# 44. Prueba realizada por el profesor

Durante la demostración, el profesor podrá modificar una entrada física.

Por ejemplo:

```text
tapar un LDR
```

```text
acercar un objeto al sensor
```

```text
pulsar un botón
```

```text
modificar un potenciómetro
```

El sistema deberá reaccionar de acuerdo con las especificaciones del proyecto.

---

# 45. Modificación de un actuador

También se solicitará controlar algún elemento desde la interfaz web.

Por ejemplo:

```text
Navegador
    │
    ▼
[ ENCENDER ]
    │
    ▼
ESP8266
    │
    ▼
Arduino
    │
    ▼
actuador
```

El profesor comprobará físicamente que la acción se produce.

---

# 46. Comprobación de InfluxDB

El alumno deberá mostrar los datos almacenados.

Deberá identificar:

```text
Bucket
```

```text
Measurement
```

```text
Fields
```

y explicar qué representa cada uno.

---

# 47. Comprobación de Grafana

El dashboard deberá mostrar datos reales del montaje.

Durante la demostración se modificará un sensor.

Después de unos segundos el cambio deberá aparecer en Grafana:

```text
Mundo físico
     ↓
Sensor
     ↓
Arduino
     ↓
ESP8266
     ↓
InfluxDB
     ↓
Grafana
```

---

# 48. Criterios de valoración

Se valorarán especialmente:

| Apartado                   | Peso |
| -------------------------- | ---: |
| Diseño y planteamiento     | 10 % |
| Montaje y conexiones       | 15 % |
| Programación               | 20 % |
| Comunicación Wi-Fi y web   | 15 % |
| InfluxDB                   | 10 % |
| Grafana                    | 10 % |
| Documentación              | 10 % |
| Demostración y explicación | 10 % |

**Total: 100 %**

---

# 49. Condición fundamental

Un proyecto perfectamente documentado pero cuyo montaje no funcione durante la comprobación no podrá obtener la máxima valoración.

De la misma manera, un montaje funcionando pero cuyo funcionamiento los autores no sean capaces de explicar se considerará incompleto.

El objetivo es demostrar:

```text
SABER HACER
+
SABER EXPLICAR
```

---

# 50. Entrega final

Cada pareja entregará:

```text
proyecto_final_iot.pdf
```

junto con:

```text
README.md
```

y:

```text
programas .cpp
```

incluyendo los pequeños programas de prueba utilizados durante el desarrollo.

Las credenciales reales deberán eliminarse del código antes de la entrega.

---

# 51. Resultado final del curso

Al finalizar el proyecto habremos recorrido una progresión completa:

```text
Arduino Mega
      ↓
Entradas y salidas
      ↓
Sensores y actuadores
      ↓
Programación
      ↓
ESP8266
      ↓
Wi-Fi
      ↓
HTTP
      ↓
Aplicación web
      ↓
InfluxDB
      ↓
Grafana
      ↓
PROYECTO IoT
```

El resultado ya no es simplemente un circuito Arduino.

Es un pequeño sistema conectado capaz de:

```text
SENSORIZAR
     +
PROCESAR
     +
CONTROLAR
     +
COMUNICAR
     +
ALMACENAR
     +
VISUALIZAR
```

información del mundo físico.

# 52. Reto final

El objetivo no es reproducir exactamente una práctica anterior.

Cada grupo deberá demostrar que es capaz de utilizar lo aprendido para resolver **un problema nuevo**.

La pregunta que debe guiar el proyecto será:

> **¿Qué sistema útil podemos construir con nuestro Arduino Mega, los componentes disponibles y las tecnologías que hemos aprendido?**

A partir de ese momento, el diseño, las decisiones técnicas y la implementación estarán en manos del grupo.
