# Lección 10 — Proyecto de investigación de componentes

## 1. Introducción

En las primeras lecciones hemos aprendido a utilizar Arduino Mega 2560 R3 mediante prácticas guiadas.

Hemos trabajado con:

* Salidas digitales.
* Entradas digitales.
* PWM.
* Entradas analógicas.
* Pulsadores.
* Potenciómetros.
* LED.
* LED RGB.
* Monitor serie.

Hasta ahora se proporcionaban las conexiones, explicaciones y programas necesarios.

En esta actividad cambiaremos la forma de trabajar.

**A partir de ahora seréis vosotros quienes deberéis investigar cómo funciona un componente desconocido, descubrir cómo se conecta al Arduino Mega, desarrollar el programa necesario y comprobar experimentalmente su funcionamiento.**

---

# 2. Objetivos

Los objetivos de esta actividad son:

* Aprender a identificar componentes electrónicos.
* Buscar documentación técnica fiable.
* Localizar y consultar datasheets.
* Interpretar un patillaje.
* Determinar la tensión de funcionamiento de un componente.
* Diseñar conexiones con Arduino Mega 2560 R3.
* Buscar e instalar librerías cuando sean necesarias.
* Desarrollar programas en C++ utilizando PlatformIO.
* Comprobar experimentalmente los programas desarrollados.
* Detectar y solucionar errores.
* Documentar correctamente un proyecto.
* Explicar y defender el trabajo realizado.

---

# 3. El reto

Cada alumno o grupo deberá seleccionar:

> **Un mínimo de cuatro componentes del kit que no hayan sido utilizados en las prácticas anteriores.**

Para cada componente será necesario:

```text
INVESTIGAR
     ↓
COMPRENDER
     ↓
DISEÑAR
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

No se proporcionará el programa ni el esquema de conexión.

Descubrir cómo utilizar cada componente forma parte de la actividad.

---

# 4. Componentes que no pueden elegirse

Ya hemos trabajado con:

* LED.
* Pulsador.
* Potenciómetro.
* LED RGB.

Por tanto, estos elementos no pueden contabilizarse entre los cuatro componentes investigados.

Sí pueden utilizarse como elementos auxiliares.

Por ejemplo, podemos utilizar un LED para indicar que un sensor ha detectado algo.

---

# 5. Selección de los cuatro componentes

Cada grupo deberá seleccionar cuatro componentes diferentes entre los disponibles físicamente en su kit.

Se recomienda seleccionar componentes variados.

Por ejemplo:

```text
COMPONENTE 1 → SENSOR

COMPONENTE 2 → ACTUADOR

COMPONENTE 3 → VISUALIZACIÓN

COMPONENTE 4 → CONTROL / COMUNICACIÓN
```

No es obligatorio seguir exactamente esta distribución, pero se valorará trabajar con dispositivos que presenten problemas diferentes.

Antes de comenzar los montajes, anotaremos nuestra selección:

| Nº | Componente | Tipo | Función |
| -: | ---------- | ---- | ------- |
|  1 |            |      |         |
|  2 |            |      |         |
|  3 |            |      |         |
|  4 |            |      |         |

---

# 6. Primera fase — Identificación

Para cada componente debemos determinar:

* Nombre.
* Modelo o referencia.
* Fabricante, si puede identificarse.
* Función.
* Tipo de componente.
* Número de terminales.
* Tensión de funcionamiento.
* Tipo de señal o comunicación utilizada.

No conectaremos todavía el componente.

Primero debemos saber qué tenemos entre las manos.

---

# 7. Segunda fase — Investigación

Buscaremos información técnica en Internet.

Podemos consultar:

* Web del fabricante.
* Tutoriales oficiales de SunFounder.
* Documentación de Arduino.
* Datasheets.
* Documentación oficial de librerías.
* Documentación técnica de otros fabricantes.
* Tutoriales técnicos fiables.

Debemos comparar la información encontrada y comprobar que corresponde exactamente al componente que tenemos.

---

# 8. El datasheet

Siempre que sea posible debemos localizar el:

```text
DATASHEET
```

del componente.

No es necesario comprender todas sus páginas.

Debemos localizar la información necesaria para utilizarlo correctamente.

Por ejemplo:

```text
Tensión de alimentación

Patillaje

Características eléctricas

Tipo de señal

Rangos de funcionamiento

Temporización

Protocolos de comunicación
```

Debemos aprender a localizar información útil dentro de documentación técnica real.

---

# 9. Registrar las fuentes

Debemos guardar las fuentes utilizadas desde el comienzo.

Para cada fuente anotaremos:

| Dato               | Información |
| ------------------ | ----------- |
| Fabricante / autor |             |
| Documento / página |             |
| Dirección web      |             |
| Fecha de consulta  |             |

No dejaremos esta tarea para el último momento.

---

# 10. Tercera fase — Estudiar el patillaje

Debemos identificar correctamente los terminales.

Por ejemplo, podemos encontrar nombres como:

```text
VCC
GND
OUT
IN
SDA
SCL
TRIG
ECHO
TX
RX
```

Debemos averiguar qué significa cada terminal utilizado.

En el PDF tendremos que explicar su función.

---

# 11. Cuarta fase — Diseñar las conexiones

Una vez comprendido el componente diseñaremos su conexión con Arduino Mega 2560 R3.

Para cada componente tendremos que crear una tabla similar a:

| Componente | Arduino Mega | Función      |
| ---------- | ------------ | ------------ |
| VCC        | ...          | Alimentación |
| GND        | GND          | Masa         |
| ...        | ...          | ...          |

Los valores reales dependerán del componente investigado.

---

# 12. Comprobar la alimentación

Antes de conectar físicamente el componente debemos responder:

**¿Con qué tensión funciona?**

Especialmente debemos comprobar si trabaja a:

```text
5 V
```

o:

```text
3,3 V
```

También debemos investigar si sus señales son compatibles directamente con Arduino Mega.

> **Nunca debemos conectar un componente desconocido simplemente probando conexiones al azar.**

Una conexión incorrecta puede dañar el componente o la placa.

---

# 13. Quinta fase — Realizar el montaje

Cuando conozcamos:

```text
ALIMENTACIÓN
     +
PATILLAJE
     +
CONEXIONES
```

podremos construir el circuito.

Antes de conectar el USB realizaremos una última revisión.

Comprobaremos:

```text
¿VCC es correcto?

¿GND está correctamente conectado?

¿Los terminales están identificados?

¿Las resistencias necesarias están colocadas?

¿Los pines coinciden con nuestra tabla?

¿Existen cortocircuitos?
```

Solamente entonces alimentaremos el circuito.

---

# 14. Sexta fase — Desarrollar el programa

Crearemos un programa que permita demostrar claramente el funcionamiento del componente.

No queremos simplemente:

```text
COMPILAR
```

Queremos:

```text
COMPILAR
    ↓
CARGAR
    ↓
PROBAR
    ↓
COMPROBAR
    ↓
CORREGIR
```

El programa deberá estar escrito en C++ utilizando PlatformIO y el framework Arduino.

---

# 15. El programa debe demostrar algo

Cada práctica debe tener un objetivo claramente comprobable.

Por ejemplo, dependiendo del componente investigado, el programa podría:

* Obtener una medida.
* Detectar un evento.
* Producir movimiento.
* Generar sonido.
* Mostrar información.
* Recibir órdenes.
* Controlar una salida.
* Realizar una secuencia.

No es suficiente que el programa compile.

Debemos poder demostrar que el componente está funcionando.

---

# 16. Uso del monitor serie

Cuando resulte útil podemos utilizar:

```cpp
Serial.begin(9600);
```

y el monitor serie para observar:

* Medidas.
* Estados.
* Eventos.
* Errores.
* Resultados.

Por ejemplo, conceptualmente:

```text
SENSOR
   │
   ▼
ARDUINO
   │
   ▼
MONITOR SERIE
   │
   ▼
VALORES
```

El monitor serie será una herramienta especialmente útil para depurar los programas.

---

# 17. Librerías

Algunos componentes podrán manejarse directamente mediante instrucciones de Arduino.

Otros necesitarán una librería.

Si utilizamos una librería debemos indicar en nuestra documentación:

* Nombre de la librería.
* Autor o proyecto responsable.
* Para qué sirve.
* Cómo se ha instalado.
* Qué funciones utilizamos.

Si la instalamos mediante PlatformIO, debemos conservar también la configuración correspondiente.

---

# 18. Código encontrado en Internet

Está permitido consultar programas y ejemplos existentes.

Forma parte del proceso de investigación.

Sin embargo:

> **No está permitido presentar código que el alumno no comprenda.**

Si utilizamos código encontrado en una fuente externa:

1. Debemos citar la fuente.
2. Debemos adaptarlo a nuestro montaje.
3. Debemos comprenderlo.
4. Debemos ser capaces de modificarlo.

Durante la demostración el profesor podrá preguntar sobre cualquier parte del programa.

---

# 19. Séptima fase — Pruebas

Una vez que el programa funcione debemos realizar diferentes pruebas.

No debemos conformarnos con:

```text
Ha funcionado una vez.
```

Debemos comprobar que el comportamiento es repetible.

En el PDF incluiremos una pequeña tabla:

| Prueba | Resultado esperado | Resultado obtenido |
| ------ | ------------------ | ------------------ |
| 1      |                    |                    |
| 2      |                    |                    |
| 3      |                    |                    |

Las pruebas dependerán del componente utilizado.

---

# 20. Octava fase — Crear una lección

Para cada uno de los cuatro componentes elaboraremos una **pequeña lección didáctica**.

Debemos imaginar que nuestro documento servirá para que otro compañero pueda aprender a utilizar ese componente.

La estructura será similar a las lecciones 1 a 8 de este curso.

---

# 21. Estructura obligatoria de cada lección

Cada componente deberá contener como mínimo:

## 1. Título

Nombre claro de la práctica.

## 2. Objetivos

Qué aprenderemos.

## 3. Material necesario

Componentes utilizados.

## 4. Descripción del componente

Qué es y para qué sirve.

## 5. Características técnicas

Datos relevantes obtenidos de la documentación.

## 6. Patillaje

Identificación y función de sus terminales.

## 7. Funcionamiento

Explicación sencilla de cómo trabaja.

## 8. Conexiones

Tabla de conexiones con Arduino Mega.

## 9. Esquema del montaje

Representación que permita reproducir el circuito.

## 10. Programa

Código utilizado.

## 11. Explicación del programa

Explicación de las instrucciones importantes.

## 12. Funcionamiento esperado

Qué debe hacer el montaje.

## 13. Pruebas realizadas

Comprobaciones experimentales.

## 14. Problemas encontrados

Errores y soluciones.

## 15. Fuentes

Datasheets y páginas consultadas.

---

# 22. Fotografías del montaje

La documentación deberá incluir fotografías propias del montaje realizado.

Las fotografías deben permitir comprobar:

* Arduino utilizado.
* Componente.
* Protoboard cuando corresponda.
* Cableado.
* Montaje terminado.

No utilizaremos una fotografía encontrada en Internet para sustituir la fotografía de nuestro montaje real.

---

# 23. El PDF

Al finalizar se entregará **un único PDF** que incluya las cuatro lecciones.

Una posible estructura será:

```text
PORTADA

ÍNDICE

COMPONENTE 1
    ├── Investigación
    ├── Características
    ├── Conexiones
    ├── Programa
    └── Pruebas

COMPONENTE 2
    ├── Investigación
    ├── Características
    ├── Conexiones
    ├── Programa
    └── Pruebas

COMPONENTE 3
    ├── Investigación
    ├── Características
    ├── Conexiones
    ├── Programa
    └── Pruebas

COMPONENTE 4
    ├── Investigación
    ├── Características
    ├── Conexiones
    ├── Programa
    └── Pruebas

CONCLUSIONES

FUENTES
```

---

# 24. Programas que deben entregarse

Además del PDF se entregarán todos los programas utilizados.

Como mínimo:

```text
componente_1.cpp

componente_2.cpp

componente_3.cpp

componente_4.cpp
```

Si una práctica necesita varios programas deberán entregarse todos.

Por ejemplo:

```text
componente_1/
│
├── prueba_inicial.cpp
├── lectura.cpp
└── practica_final.cpp
```

---

# 25. Organización recomendada

Podemos organizar el trabajo:

```text
leccion10/
│
├── pdf/
│   └── investigacion_componentes.pdf
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

Debemos conservar ordenadamente nuestro trabajo durante todo el proyecto.

---

# 26. Demostración práctica obligatoria

La entrega del PDF y de los programas **no es suficiente**.

El profesor pasará por los puestos de trabajo para comprobar personalmente el funcionamiento de los cuatro montajes.

Para cada componente tendremos que demostrar:

```text
DOCUMENTACIÓN
      │
      ▼
CONEXIONES
      │
      ▼
PROGRAMA
      │
      ▼
MONTAJE REAL
      │
      ▼
FUNCIONAMIENTO
```

El montaje debe funcionar de acuerdo con las especificaciones descritas en el PDF.

---

# 27. Defensa del montaje

Durante la comprobación el profesor podrá realizar preguntas como:

```text
¿Qué hace este componente?

¿Dónde encontraste su datasheet?

¿Con qué tensión trabaja?

¿Qué función tiene este terminal?

¿Por qué lo has conectado a este pin?

¿Qué hace esta parte del programa?

¿Qué valor devuelve el sensor?

¿Qué librería estás utilizando?

¿Por qué necesitas esta resistencia?
```

También podrá solicitar una pequeña modificación del programa para comprobar su comprensión.

---

# 28. Coherencia del trabajo

Se comprobará especialmente que coincidan:

```text
        PDF
         │
         ▼
TABLA DE CONEXIONES
         │
         ▼
       CÓDIGO
         │
         ▼
    MONTAJE REAL
```

No debe ocurrir, por ejemplo, que el PDF indique:

```text
Señal → D7
```

el programa utilice:

```cpp
const int SENSOR = 8;
```

y físicamente el dispositivo esté conectado a:

```text
D10
```

Todo debe corresponderse.

---

# 29. Integración de componentes

Una vez terminadas las cuatro prácticas individuales, se propone como **ampliación** combinar dos o más de los componentes investigados.

Por ejemplo:

```text
SENSOR
   │
   ▼
ARDUINO
   │
   ▼
ACTUADOR
```

Podemos crear sistemas como:

```text
DISTANCIA → ARDUINO → SONIDO
```

```text
MOVIMIENTO → ARDUINO → DISPLAY
```

```text
TEMPERATURA → ARDUINO → LCD
```

```text
JOYSTICK → ARDUINO → SERVOMOTOR
```

La combinación concreta dependerá de los componentes seleccionados.

---

# 30. Qué se evaluará

La actividad se evaluará en cuatro grandes bloques:

```text
INVESTIGACIÓN
      +
DOCUMENTACIÓN
      +
PROGRAMACIÓN
      +
FUNCIONAMIENTO REAL
```

No se trata solamente de entregar un documento.

---

# 31. Rúbrica de evaluación

La actividad se calificará sobre **10 puntos**.

| Apartado                              | Puntuación |
| ------------------------------------- | ---------: |
| Investigación y fuentes técnicas      |        1,5 |
| Documentación de los componentes      |        2,0 |
| Conexiones y esquemas                 |        1,5 |
| Programas desarrollados               |        2,0 |
| Funcionamiento de los montajes reales |        2,0 |
| Defensa y comprensión del trabajo     |        1,0 |
| **TOTAL**                             |     **10** |

---

# 32. Investigación y fuentes — 1,5 puntos

Se valorará:

* Identificación correcta de los componentes.
* Uso de documentación fiable.
* Localización de datasheets cuando existan.
* Correcta identificación de características técnicas.
* Referencias a las fuentes utilizadas.

---

# 33. Documentación — 2 puntos

Se valorará que las cuatro lecciones sean:

* Claras.
* Ordenadas.
* Técnicamente correctas.
* Comprensibles.
* Suficientemente completas para reproducir las prácticas.

También se valorarán las fotografías propias y las pruebas realizadas.

---

# 34. Conexiones y esquemas — 1,5 puntos

Se comprobará:

* Patillaje correctamente identificado.
* Alimentación correcta.
* Tabla de conexiones.
* Esquema comprensible.
* Correspondencia entre esquema y montaje real.

---

# 35. Programación — 2 puntos

Los programas deberán:

* Compilar correctamente.
* Estar correctamente estructurados.
* Utilizar nombres de variables comprensibles.
* Incluir comentarios cuando sean necesarios.
* Controlar correctamente el componente.
* Corresponderse con el montaje documentado.

También se valorará que el alumno pueda explicar y modificar el código.

---

# 36. Funcionamiento real — 2 puntos

El profesor comprobará físicamente los montajes.

Para obtener la puntuación completa:

> **Los cuatro componentes deben funcionar correctamente según lo descrito en el PDF.**

No será suficiente mostrar fotografías o vídeos del circuito funcionando anteriormente.

El profesor debe poder comprobar el funcionamiento real durante la práctica.

---

# 37. Defensa — 1 punto

Se valorará que el alumno pueda explicar:

* Qué hace el componente.
* Cómo funciona.
* Cómo se conecta.
* Qué hace el programa.
* Qué problemas ha encontrado.
* Cómo los ha solucionado.

El objetivo es comprobar que el trabajo ha sido comprendido.

---

# 38. Condición importante de evaluación

El objetivo principal de esta actividad es aprender a trabajar con hardware real.

Por este motivo:

> **Un componente que solamente aparezca documentado pero cuyo funcionamiento no pueda demostrarse físicamente no se considerará una práctica completamente realizada.**

La documentación y el montaje forman parte del mismo trabajo:

```text
INVESTIGAR
    ↓
DOCUMENTAR
    ↓
CONSTRUIR
    ↓
PROGRAMAR
    ↓
DEMOSTRAR
```

---

# 39. Uso de IA

Las herramientas de inteligencia artificial pueden utilizarse como ayuda para:

* Comprender documentación.
* Buscar posibles errores.
* Explicar conceptos.
* Ayudar a interpretar código.
* Proponer formas de realizar pruebas.

Pero no sustituyen la investigación ni la comprensión del trabajo.

Si utilizamos una herramienta de IA para generar código, **somos responsables de comprobarlo, entenderlo, corregirlo y probarlo físicamente**.

Durante la demostración no importa quién haya propuesto inicialmente una instrucción.

El alumno debe ser capaz de explicar por qué está en su programa.

---

# 40. Lista de comprobación antes de entregar

Antes de entregar comprobaremos:

* [ ] He seleccionado al menos cuatro componentes nuevos.
* [ ] He identificado correctamente cada componente.
* [ ] He buscado documentación técnica.
* [ ] He localizado los datasheets cuando estaban disponibles.
* [ ] He comprobado las tensiones de funcionamiento.
* [ ] He documentado los patillajes.
* [ ] He realizado las tablas de conexiones.
* [ ] He realizado los montajes físicos.
* [ ] He desarrollado los programas.
* [ ] Todos los programas compilan.
* [ ] He probado físicamente los cuatro componentes.
* [ ] He documentado las pruebas.
* [ ] He incluido fotografías propias.
* [ ] He indicado las fuentes utilizadas.
* [ ] He generado el PDF.
* [ ] He incluido todos los archivos `.cpp`.
* [ ] Puedo explicar los programas.
* [ ] Puedo demostrar al profesor los cuatro montajes.

---

# 41. Resultado final

Al terminar esta actividad habremos pasado de seguir prácticas completamente guiadas a ser capaces de trabajar autónomamente con nuevos dispositivos.

El proceso aprendido será:

```text
NUEVO COMPONENTE
       │
       ▼
   IDENTIFICAR
       │
       ▼
BUSCAR DATASHEET
       │
       ▼
ESTUDIAR PATILLAJE
       │
       ▼
DISEÑAR CONEXIONES
       │
       ▼
    PROGRAMAR
       │
       ▼
      PROBAR
       │
       ▼
    CORREGIR
       │
       ▼
   DOCUMENTAR
       │
       ▼
    DEMOSTRAR
```

Esta metodología será necesaria para los siguientes pasos del curso.

Cuando incorporemos nuevos dispositivos ya no necesitaremos disponer siempre de una práctica completamente resuelta.

Seremos capaces de investigar cómo integrarlos en nuestros propios proyectos con Arduino Mega 2560 R3.

Y más adelante podremos utilizar los sensores y actuadores investigados dentro de sistemas más completos:

```text
SENSORES Y ACTUADORES
         │
         ▼
   ARDUINO MEGA
         │
         ▼
      ESP8266
         │
         ▼
        Wi-Fi
       /     \
      ▼       ▼
 PÁGINA WEB  INFLUXDB
                 │
                 ▼
              GRAFANA
```

El objetivo final ya no será simplemente **programar Arduino**, sino ser capaces de diseñar y desarrollar un pequeño sistema IoT completo.
