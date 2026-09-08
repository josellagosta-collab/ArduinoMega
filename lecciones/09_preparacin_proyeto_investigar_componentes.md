# Lección 9 — Preparación del proyecto de investigación de componentes

## 1. Introducción

Durante las lecciones anteriores hemos aprendido progresivamente a utilizar diferentes elementos del Arduino Mega 2560 R3 y varios componentes del kit.

Hasta ahora las prácticas han proporcionado:

* Explicación del componente.
* Esquema de conexión.
* Tabla de conexiones.
* Explicación del funcionamiento.
* Programa.
* Pruebas.
* Ejercicios.

En la próxima lección cambiaremos la forma de trabajar.

En lugar de recibir toda esta información, **seréis vosotros quienes tendréis que investigarla y elaborarla**.

El objetivo será aprender a enfrentarse a un componente electrónico desconocido utilizando su documentación técnica y otras fuentes de información.

---

# 2. Componentes utilizados hasta ahora

Durante las prácticas anteriores hemos trabajado con:

* Arduino Mega 2560 R3.
* Protoboard.
* Resistencias.
* LED.
* Pulsador.
* Potenciómetro.
* LED RGB.

Estos componentes **no podrán elegirse como componentes principales del trabajo de investigación**, aunque podrán utilizarse como elementos auxiliares en los montajes.

---

# 3. Componentes disponibles para investigar

El kit dispone de numerosos componentes que todavía no hemos utilizado.

Entre los componentes que pueden seleccionarse se encuentran:

| Componente                             | Tipo / aplicación             |
| -------------------------------------- | ----------------------------- |
| Fotoresistencia LDR                    | Sensor de luz                 |
| Termistor                              | Sensor de temperatura         |
| Sensor de temperatura LM35             | Temperatura                   |
| Sensor de inclinación                  | Detección de inclinación      |
| Fotorruptor                            | Detección óptica              |
| Sensor PIR                             | Detección de movimiento       |
| Sensor ultrasónico HC-SR04             | Medición de distancia         |
| Joystick                               | Entrada analógica/digital     |
| Zumbador activo                        | Generación de sonido          |
| Zumbador pasivo                        | Generación de tonos           |
| Servomotor                             | Movimiento                    |
| Motor DC                               | Movimiento                    |
| Motor paso a paso                      | Movimiento controlado         |
| Driver ULN2003                         | Control del motor paso a paso |
| Relé                                   | Control de cargas             |
| Display de 7 segmentos                 | Visualización numérica        |
| Display de 7 segmentos de 4 dígitos    | Visualización numérica        |
| Matriz LED 8×8                         | Visualización                 |
| LCD 1602                               | Visualización de texto        |
| Registro de desplazamiento 74HC595     | Expansión de salidas          |
| Receptor infrarrojo                    | Recepción de señales IR       |
| Mando a distancia IR                   | Control remoto                |
| Sensor de sonido / micrófono           | Detección de sonido           |
| Sensor de nivel de agua                | Detección de agua             |
| Teclado matricial                      | Entrada de datos              |
| RFID RC522, si está incluido en el kit | Identificación mediante RFID  |

> **Importante:** antes de elegir un componente se debe comprobar físicamente que se encuentra disponible en el kit entregado.

No todos los kits o revisiones contienen necesariamente exactamente los mismos componentes.

---

# 4. Preparación de la Lección 10

En la Lección 10 realizaréis un pequeño proyecto de investigación técnica.

Cada alumno o grupo deberá seleccionar:

**un mínimo de 4 componentes diferentes que no hayamos utilizado en las lecciones anteriores.**

Los cuatro componentes deben estar disponibles físicamente en el kit.

No se trata simplemente de copiar un programa encontrado en Internet.

Para cada componente será necesario:

```text
IDENTIFICAR
     ↓
INVESTIGAR
     ↓
COMPRENDER
     ↓
CONECTAR
     ↓
PROGRAMAR
     ↓
PROBAR
     ↓
DOCUMENTAR
     ↓
DEMOSTRAR
```

---

# 5. Identificación del componente

El primer paso será identificar correctamente cada componente.

No debemos conectar un componente al Arduino si desconocemos qué es o cómo funciona.

Para cada componente tendremos que determinar como mínimo:

* Nombre.
* Modelo o referencia, cuando sea posible.
* Fabricante, cuando pueda identificarse.
* Función.
* Tipo de dispositivo.
* Número y función de sus terminales.
* Tensión de funcionamiento.
* Tipo de señal utilizada.

---

# 6. Buscar información en Internet

Para cada componente deberéis realizar vuestra propia investigación.

Podéis utilizar:

* Página web del fabricante.
* Documentación de SunFounder.
* Datasheets.
* Documentación técnica.
* Tutoriales técnicos fiables.
* Documentación de Arduino.
* Documentación de librerías.
* Otros recursos técnicos de Internet.

Siempre que sea posible debe utilizarse como fuente principal la documentación del **fabricante del componente**.

---

# 7. Localizar la hoja de características

Para cada componente deberéis intentar localizar su:

```text
DATASHEET
```

u hoja de características.

Un datasheet es el documento técnico donde el fabricante describe las características de un componente.

Dependiendo del dispositivo puede proporcionar información como:

```text
Tensión de funcionamiento

Corriente

Patillaje

Características eléctricas

Protocolos

Temporización

Dimensiones

Límites máximos

Forma de utilización
```

No es necesario comprender todo el datasheet.

Debéis localizar y comprender **la información necesaria para utilizar correctamente el componente con el Arduino Mega 2560 R3**.

---

# 8. Guardar las fuentes utilizadas

El PDF debe indicar las fuentes utilizadas durante la investigación.

Como mínimo se incluirá:

* Fabricante o autor.
* Nombre del documento o página.
* Dirección de Internet.
* Fecha de consulta.

Cuando exista un datasheet oficial deberá incluirse su referencia.

No es suficiente indicar:

```text
Google
```

como fuente.

Google es un buscador, no la fuente de la información.

---

# 9. Investigar el patillaje

Antes de conectar el componente debemos conocer su **pinout** o patillaje.

Por ejemplo, un dispositivo podría disponer de:

```text
VCC → Alimentación

GND → Masa

OUT → Salida
```

Otro podría utilizar:

```text
VCC
GND
TRIGGER
ECHO
```

y otro:

```text
VCC
GND
SDA
SCL
```

Cada componente es diferente.

El trabajo debe explicar claramente la función de cada terminal utilizado.

---

# 10. Determinar cómo se conecta al Arduino

Una vez estudiado el componente deberéis diseñar la conexión con el Arduino Mega.

El PDF debe incluir una **tabla de conexiones**.

Por ejemplo:

| Componente | Arduino Mega |
| ---------- | ------------ |
| VCC        | 5V           |
| GND        | GND          |
| Señal      | D7           |

Esta tabla es solamente un ejemplo.

Las conexiones reales dependerán del componente seleccionado.

---

# 11. Atención a las tensiones

Antes de conectar cualquier dispositivo debemos comprobar su tensión de funcionamiento.

Podemos encontrar componentes que trabajen con:

```text
5 V
```

pero también dispositivos diseñados para:

```text
3,3 V
```

No debemos asumir que cualquier componente puede conectarse directamente a 5 V.

Una conexión incorrecta puede dañar:

* El componente.
* El Arduino.
* El puerto USB del ordenador.

Por tanto, **la tensión de funcionamiento debe investigarse antes de realizar el montaje**.

---

# 12. Diseñar el montaje

Después de investigar el componente se realizará el montaje utilizando:

* Arduino Mega 2560 R3.
* Protoboard.
* Cables.
* Resistencias cuando sean necesarias.
* Componentes auxiliares necesarios.

Antes de alimentar el circuito se debe revisar:

```text
Alimentación
     ↓
GND
     ↓
Patillaje
     ↓
Conexiones
     ↓
Programa
```

---

# 13. Desarrollar el programa

Cada componente deberá disponer de **al menos un programa desarrollado por el alumno o grupo** que demuestre su funcionamiento.

El programa debe estar correctamente:

* Estructurado.
* Indentado.
* Comentado cuando sea necesario.
* Compilado mediante PlatformIO.
* Probado físicamente con Arduino Mega.

Los programas se realizarán en:

```text
C++
```

utilizando el framework Arduino y PlatformIO.

---

# 14. Uso de librerías

Algunos componentes pueden necesitar una librería.

En ese caso se deberá investigar:

* Qué librería se utiliza.
* Quién la desarrolla.
* Para qué sirve.
* Cómo se instala con PlatformIO.
* Qué funciones principales estamos utilizando.

No será suficiente escribir:

```text
He instalado una librería para que funcione.
```

Debemos saber qué librería estamos utilizando.

---

# 15. No copiar programas sin comprenderlos

Podéis consultar ejemplos y programas disponibles en Internet.

Sin embargo, el programa presentado debe ser comprendido por el alumno.

El profesor podrá preguntar durante la demostración:

```text
¿Qué hace esta instrucción?

¿Por qué has utilizado este pin?

¿Qué devuelve esta función?

¿Por qué necesitas esta resistencia?

¿Qué ocurriría si cambias este valor?

¿Qué librería estás utilizando?
```

El alumno debe ser capaz de explicar su programa.

---

# 16. Documentación de cada componente

Para **cada uno de los cuatro componentes** se elaborará una pequeña lección similar a las realizadas durante este curso.

Cada lección deberá incluir como mínimo:

## 1. Nombre del componente

Identificación clara del dispositivo.

## 2. Objetivo

Qué queremos aprender o conseguir.

## 3. Material necesario

Componentes necesarios para realizar la práctica.

## 4. Descripción

Explicación sencilla del funcionamiento del dispositivo.

## 5. Características técnicas

Incluir únicamente las características relevantes para nuestra práctica.

Por ejemplo:

```text
Tensión

Tipo de señal

Rango de medida

Número de terminales

Protocolo
```

cuando corresponda.

## 6. Patillaje

Explicación de los terminales utilizados.

## 7. Conexiones

Debe incluir una tabla clara de conexiones entre el componente y el Arduino Mega.

## 8. Esquema o representación del montaje

Debe permitir comprender cómo se ha conectado el circuito.

## 9. Programa

Código utilizado para realizar la práctica.

## 10. Explicación del programa

Explicar las instrucciones más importantes.

## 11. Funcionamiento esperado

Explicar qué debe ocurrir cuando ejecutemos el programa.

## 12. Pruebas realizadas

Describir las pruebas efectuadas físicamente.

## 13. Problemas encontrados

Indicar los problemas que hayan aparecido y cómo se han solucionado.

## 14. Fuentes

Documentación y páginas utilizadas durante la investigación.

---

# 17. No queremos cuatro prácticas idénticas

Siempre que sea posible deben elegirse componentes de diferentes tipos.

Por ejemplo, una selección interesante podría ser:

```text
Sensor de distancia
        +
Servomotor
        +
Pantalla LCD
        +
Zumbador
```

Otra posibilidad:

```text
Sensor PIR
        +
Matriz LED
        +
Joystick
        +
Motor paso a paso
```

Esto permitirá trabajar diferentes tipos de dispositivos:

```text
SENSORES
ACTUADORES
MOTORES
VISUALIZACIÓN
COMUNICACIONES
```

---

# 18. Se valorará la integración de componentes

Aunque solamente es obligatorio realizar una práctica individual para cada componente, se valorará positivamente que posteriormente se combinen varios componentes.

Por ejemplo:

```text
HC-SR04
   │
   ▼
ARDUINO
   │
   ▼
BUZZER
```

El zumbador podría aumentar la frecuencia cuando disminuya la distancia.

Otro ejemplo:

```text
SENSOR PIR
     │
     ▼
  ARDUINO
     │
     ├────→ LED
     │
     └────→ BUZZER
```

Otro:

```text
SENSOR
   │
   ▼
ARDUINO
   │
   ▼
LCD 1602
   │
   ▼
Mostrar medida
```

Estas ampliaciones no sustituyen la documentación individual de los cuatro componentes.

---

# 19. Entrega

Cada alumno o grupo deberá entregar:

```text
1 PDF
+
programas .cpp
```

El PDF contendrá las cuatro lecciones elaboradas.

Una posible estructura será:

```text
TRABAJO_COMPONENTES.pdf

├── Componente 1
│
├── Componente 2
│
├── Componente 3
│
├── Componente 4
│
└── Fuentes
```

Además se entregarán los programas correspondientes:

```text
componente1.cpp

componente2.cpp

componente3.cpp

componente4.cpp
```

Si se han realizado programas adicionales también deberán entregarse.

---

# 20. Los programas deben funcionar

No se evaluará únicamente la documentación.

Los circuitos descritos deben haberse construido y probado realmente.

El profesor pasará por los puestos de trabajo para comprobar los montajes.

Cada grupo deberá tener preparados:

```text
Arduino Mega
     +
Protoboard
     +
Componente
     +
Circuito montado
     +
Programa cargado
```

El montaje deberá funcionar de acuerdo con lo descrito en el PDF.

---

# 21. Demostración práctica

Para cada componente el alumno deberá ser capaz de realizar una breve demostración.

El proceso será aproximadamente:

```text
Mostrar componente
       ↓
Explicar qué es
       ↓
Explicar conexiones
       ↓
Mostrar programa
       ↓
Ejecutarlo
       ↓
Comprobar funcionamiento
```

El profesor podrá solicitar pequeñas modificaciones.

Por ejemplo:

```text
Cambiar un tiempo

Cambiar un límite

Mostrar otro valor

Modificar un pin

Cambiar una condición
```

El objetivo es comprobar que el alumno comprende realmente el trabajo realizado.

---

# 22. Coherencia entre documentación y montaje

Un aspecto especialmente importante será que exista correspondencia entre:

```text
PDF
 │
 ▼
TABLA DE CONEXIONES
 │
 ▼
PROGRAMA
 │
 ▼
MONTAJE REAL
```

Si el PDF indica:

```text
Señal → D8
```

pero el montaje utiliza:

```text
Señal → D10
```

la documentación será incorrecta.

Lo mismo ocurre con el programa.

Los tres elementos deben coincidir:

```text
DOCUMENTACIÓN = PROGRAMA = MONTAJE
```

---

# 23. Organización recomendada de los archivos

Podéis organizar vuestro trabajo de la siguiente forma:

```text
leccion10/
│
├── documentacion/
│   └── trabajo_componentes.pdf
│
├── componente1/
│   └── main.cpp
│
├── componente2/
│   └── main.cpp
│
├── componente3/
│   └── main.cpp
│
└── componente4/
    └── main.cpp
```

Si realizáis una práctica final combinando varios componentes:

```text
leccion10/
│
├── proyecto_integracion/
│   └── main.cpp
```

---

# 24. Criterios de evaluación

Se valorarán especialmente los siguientes aspectos:

| Aspecto        | Qué se comprobará                                   |
| -------------- | --------------------------------------------------- |
| Investigación  | Calidad y fiabilidad de las fuentes                 |
| Datasheet      | Localización y utilización de documentación técnica |
| Comprensión    | Capacidad para explicar el componente               |
| Conexiones     | Montaje correcto y justificado                      |
| Código         | Programa propio, ordenado y comprensible            |
| Funcionamiento | El montaje funciona realmente                       |
| Documentación  | PDF claro y completo                                |
| Coherencia     | PDF, programa y montaje coinciden                   |
| Autonomía      | Capacidad para investigar y resolver problemas      |
| Demostración   | Capacidad para explicar y modificar la práctica     |

---

# 25. Errores que debemos evitar

No se considerará un trabajo completo si únicamente se ha:

```text
Buscado un tutorial
       ↓
Copiado el circuito
       ↓
Copiado el programa
       ↓
Entregado
```

El objetivo de la actividad es realizar:

```text
INVESTIGACIÓN
      +
COMPRENSIÓN
      +
MONTAJE
      +
PROGRAMACIÓN
      +
PRUEBA
      +
DOCUMENTACIÓN
```

---

# 26. Relación con el proyecto final

Esta actividad tiene además otro objetivo.

Hasta ahora hemos utilizado componentes siguiendo unas instrucciones preparadas previamente.

A partir de este momento debemos ser capaces de incorporar por nuestra cuenta nuevos dispositivos a un proyecto.

Esta capacidad será necesaria cuando lleguemos a:

```text
ARDUINO MEGA
      │
      ▼
   ESP8266
      │
      ▼
     Wi-Fi
```

y posteriormente:

```text
SENSORES
    │
    ▼
ARDUINO MEGA
    │
    ▼
ESP8266
    │
    ├────→ PÁGINA WEB
    │
    └────→ INFLUXDB
                 │
                 ▼
              GRAFANA
```

Los sensores y actuadores utilizados en ese proyecto podrán ser algunos de los que investiguéis en esta actividad.

---

# 27. Preparación para la Lección 10

Antes de comenzar la próxima lección cada alumno o grupo deberá:

1. Revisar los componentes disponibles en su kit.
2. Seleccionar al menos cuatro componentes no utilizados anteriormente.
3. Identificar correctamente cada componente.
4. Localizar información técnica sobre ellos.
5. Buscar, siempre que sea posible, sus datasheets.
6. Comprobar su tensión de funcionamiento.
7. Investigar su patillaje.
8. Determinar cómo pueden conectarse al Arduino Mega 2560 R3.
9. Planificar una pequeña práctica para cada componente.

**No conectaremos un componente desconocido al Arduino hasta haber investigado previamente su alimentación y su patillaje.**

En la Lección 10 comenzará el trabajo autónomo:

```text
4 COMPONENTES
      │
      ▼
INVESTIGACIÓN
      │
      ▼
DATASHEETS
      │
      ▼
DISEÑO
      │
      ▼
MONTAJE
      │
      ▼
PROGRAMACIÓN
      │
      ▼
PRUEBAS
      │
      ▼
DOCUMENTACIÓN
      │
      ▼
PDF + .CPP
      │
      ▼
DEMOSTRACIÓN AL PROFESOR
```
