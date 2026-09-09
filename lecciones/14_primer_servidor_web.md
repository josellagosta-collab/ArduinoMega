# Lección 14 — Primer servidor web con ESP8266

## 1. Objetivos

En la lección anterior conseguimos conectar el ESP8266 a una red Wi-Fi y obtener una dirección IP.

Ahora utilizaremos esa conexión para crear nuestro **primer servidor web**.

Al finalizar esta práctica seremos capaces de:

* Comprender qué es un cliente y un servidor.
* Comprender de forma básica qué son TCP y HTTP.
* Configurar el ESP8266 como servidor TCP.
* Utilizar el puerto 80.
* Acceder al ESP8266 desde un navegador.
* Observar una petición HTTP enviada por el navegador.
* Enviar una pequeña página HTML al navegador.
* Comprender cómo podremos utilizar posteriormente una página web para controlar Arduino.

---

# 2. Punto de partida

Partimos del montaje utilizado en las lecciones anteriores:

```text
ORDENADOR
    │
    │ USB
    ▼
Arduino Mega
    │
    │ Serial1
    │ 9600 baudios
    ▼
ESP8266
    │
    │ Wi-Fi
    ▼
  ROUTER
```

Ya hemos comprobado que:

```text
AT
```

responde:

```text
OK
```

y que el ESP8266 puede conectarse correctamente a nuestra red Wi-Fi.

---

# 3. ¿Qué es un servidor?

Hasta ahora nuestro ESP8266 simplemente se conectaba al router.

En esta práctica vamos a convertirlo en un **servidor**.

Un servidor es un dispositivo que espera peticiones procedentes de otros dispositivos.

Por ejemplo:

```text
NAVEGADOR
   │
   │ petición
   ▼
ESP8266
   │
   │ respuesta
   ▼
NAVEGADOR
```

El navegador será el **cliente**.

El ESP8266 será el **servidor**.

---

# 4. ¿Qué es TCP?

TCP es uno de los protocolos fundamentales utilizados en las redes informáticas.

Simplificando mucho, TCP permite establecer una comunicación entre dos dispositivos.

Necesitamos conocer:

```text
Dirección IP
+
Puerto
```

La dirección IP identifica el dispositivo.

El puerto identifica el servicio.

Por ejemplo:

```text
192.168.1.37:80
```

podemos interpretarlo como:

```text
192.168.1.37 → ESP8266

80 → servidor web
```

---

# 5. ¿Qué es HTTP?

HTTP es el protocolo utilizado habitualmente para intercambiar páginas y recursos web.

Cuando escribimos una dirección en un navegador:

```text
http://192.168.1.37
```

el navegador establece una conexión con el servidor y envía una petición HTTP.

Una petición simplificada podría comenzar así:

```text
GET / HTTP/1.1
```

`GET` significa que el navegador solicita un recurso.

`/` representa, en este caso, la página principal.

No necesitamos estudiar HTTP en profundidad todavía.

Lo importante es comprender:

```text
Navegador
    │
    │ GET /
    ▼
Servidor
    │
    │ HTML
    ▼
Navegador
```

---

# 6. Programa del Arduino Mega

Seguiremos utilizando el Mega como puente entre el ordenador y el ESP8266.

Crea:

```text
ejemplos/14_servidor_web/main.cpp
```

con el siguiente programa:

```cpp
#include <Arduino.h>

const unsigned long VELOCIDAD_ESP = 9600;

void setup()
{
    Serial.begin(9600);
    Serial1.begin(VELOCIDAD_ESP);

    delay(2000);

    Serial.println();
    Serial.println("===============================");
    Serial.println(" ESP8266 - Servidor web");
    Serial.println("===============================");
    Serial.println();
    Serial.println("Escribe comandos AT");
    Serial.println();
}

void loop()
{
    // Ordenador -> ESP8266
    if (Serial.available() > 0)
    {
        String comando = Serial.readStringUntil('\n');
        comando.trim();

        if (comando.length() > 0)
        {
            Serial.print(">> ");
            Serial.println(comando);

            Serial1.print(comando);
            Serial1.print("\r\n");
        }
    }

    // ESP8266 -> ordenador
    while (Serial1.available() > 0)
    {
        Serial.write(Serial1.read());
    }
}
```

Observa que seguimos utilizando:

```cpp
Serial1.begin(9600);
```

porque experimentalmente hemos comprobado que nuestros ESP8266 utilizan **9600 baudios** para los comandos AT.

---

# 7. Comprobar la comunicación

Empezamos siempre comprobando:

```text
AT
```

Respuesta esperada:

```text
OK
```

Si no obtenemos `OK`, no continuaremos.

---

# 8. Comprobar la conexión Wi-Fi

Ejecutamos:

```text
AT+CWJAP?
```

Debemos comprobar que el ESP8266 está conectado a nuestra red.

También podemos ejecutar:

```text
AT+CIFSR
```

Por ejemplo:

```text
+CIFSR:STAIP,"192.168.1.37"
```

Debemos apuntar esta dirección.

La utilizaremos posteriormente desde el navegador.

---

# 9. Activar múltiples conexiones

Para crear un servidor TCP mediante comandos AT debemos activar el modo de múltiples conexiones.

Ejecutamos:

```text
AT+CIPMUX=1
```

Respuesta esperada:

```text
OK
```

Podemos comprobarlo mediante:

```text
AT+CIPMUX?
```

Esperamos:

```text
+CIPMUX:1

OK
```

El ESP8266 puede asignar diferentes identificadores a las conexiones TCP que recibe.

Por ejemplo:

```text
0
1
2
3
4
```

Estos identificadores serán importantes posteriormente.

---

# 10. Crear el servidor TCP

Ahora llega uno de los comandos más importantes de la práctica.

Ejecutamos:

```text
AT+CIPSERVER=1,80
```

donde:

```text
1  → crear servidor

80 → puerto
```

La respuesta esperada es:

```text
OK
```

Acabamos de crear un servidor TCP que escucha en el **puerto 80**.

Nuestro sistema ahora es:

```text
             RED Wi-Fi

ORDENADOR                  ESP8266
    │                         │
    │                         │
Navegador ───── TCP ─────────►│
                              │
                         Puerto 80
```

---

# 11. Comprobar la dirección IP

Volvemos a ejecutar:

```text
AT+CIFSR
```

Supongamos que obtenemos:

```text
+CIFSR:STAIP,"192.168.1.37"
```

Entonces desde un ordenador conectado a **la misma red Wi-Fi** abrimos un navegador.

Introducimos:

```text
http://192.168.1.37
```

Sustituiremos esa dirección por la IP real de nuestro ESP8266.

---

# 12. Observar la conexión del navegador

Al acceder desde el navegador deberían comenzar a aparecer datos en nuestro monitor serie.

Podemos observar algo parecido a:

```text
0,CONNECT
```

Esto significa que un cliente ha establecido una conexión con nuestro servidor.

El número:

```text
0
```

es el identificador de esa conexión.

También aparecerá una línea similar a:

```text
+IPD,0,xxx:GET / HTTP/1.1
```

Por ejemplo:

```text
+IPD,0,421:GET / HTTP/1.1
Host: 192.168.1.37
...
```

No necesitamos comprender todavía toda la petición.

Nos interesa especialmente:

```text
GET /
```

Esto demuestra que el navegador está solicitando la página principal.

---

# 13. Interpretar +IPD

Cuando el ESP8266 recibe información desde una conexión TCP puede enviarla al Mega utilizando una indicación similar a:

```text
+IPD,0,421:
```

Podemos interpretarla de forma simplificada como:

```text
+IPD
 │
 └── Han llegado datos

0
 │
 └── Conexión número 0

421
 │
 └── Número de bytes recibidos
```

Después aparecen los datos enviados por el navegador.

Por tanto:

```text
+IPD,0,421:GET / HTTP/1.1
```

significa aproximadamente:

> Han llegado datos por la conexión 0 y comienzan con una petición HTTP GET.

---

# 14. Enviar información al navegador

Hasta ahora el navegador ha enviado una petición al ESP8266.

Ahora tenemos que responder.

Para enviar información utilizaremos:

```text
AT+CIPSEND
```

La estructura en modo de múltiples conexiones es:

```text
AT+CIPSEND=ID,LONGITUD
```

Por ejemplo:

```text
AT+CIPSEND=0,4
```

significa:

```text
0 → conexión número 0

4 → vamos a enviar 4 bytes
```

El ESP8266 responderá con:

```text
>
```

Esto significa:

> Estoy preparado para recibir los datos que quieres transmitir.

---

# 15. Primera prueba de transmisión

Antes de enviar HTML vamos a realizar una prueba sencilla.

Con el navegador conectado y suponiendo que tenemos:

```text
0,CONNECT
```

escribimos:

```text
AT+CIPSEND=0,4
```

El ESP8266 debe responder:

```text
>
```

Ahora debemos enviar exactamente cuatro caracteres:

```text
HOLA
```

Si todo funciona correctamente aparecerá:

```text
SEND OK
```

Hemos realizado nuestra primera transmisión TCP.

---

# 16. Enviar una página HTML

Ahora vamos a enviar algo que el navegador pueda interpretar como una página web.

Una página HTML extremadamente sencilla puede ser:

```html
<h1>Arduino Mega</h1>
```

Pero un navegador espera una respuesta HTTP. Una respuesta mínima puede tener esta estructura:

```text
HTTP/1.1 200 OK
Content-Type: text/html
Connection: close

<h1>Arduino Mega</h1>
```

Las líneas vacías son importantes porque separan las cabeceras HTTP del contenido HTML.

---

# 17. Problema de la longitud

`AT+CIPSEND` necesita conocer cuántos bytes vamos a enviar.

Por ejemplo:

```text
AT+CIPSEND=0,4
```

indica que enviaremos exactamente cuatro bytes.

Esto es incómodo si queremos escribir una página web completa manualmente.

Por ese motivo, en esta primera práctica utilizaremos mensajes muy pequeños.

Posteriormente será el programa de Arduino el que calculará automáticamente la longitud mediante:

```cpp
respuesta.length()
```

y construirá la respuesta HTTP.

---

# 18. ¿Por qué no hacemos todavía toda la página automáticamente?

Podríamos escribir ya un programa que hiciera todo el proceso.

Pero primero necesitamos comprender qué está ocurriendo.

La secuencia real es:

```text
1. Navegador conecta
          │
          ▼
2. ESP8266 recibe conexión
          │
          ▼
3. Navegador envía GET /
          │
          ▼
4. ESP8266 envía +IPD
          │
          ▼
5. Arduino analiza petición
          │
          ▼
6. Arduino prepara HTML
          │
          ▼
7. AT+CIPSEND
          │
          ▼
8. ESP8266 envía HTML
          │
          ▼
9. Navegador muestra página
```

Comprender esta secuencia será fundamental cuando controlemos dispositivos reales.

---

# 19. Cerrar una conexión

Cuando terminemos de responder al navegador podemos cerrar una conexión.

Por ejemplo:

```text
AT+CIPCLOSE=0
```

El `0` corresponde al identificador de conexión.

Podemos recibir:

```text
0,CLOSED
```

---

# 20. Detener el servidor

Para detener el servidor podemos utilizar:

```text
AT+CIPSERVER=0
```

Después el ESP8266 dejará de aceptar nuevas conexiones TCP en el puerto 80.

Para volver a iniciarlo:

```text
AT+CIPSERVER=1,80
```

---

# 21. Secuencia completa de comandos

La secuencia que debemos dominar en esta práctica es:

```text
AT
```

```text
AT+CWJAP?
```

```text
AT+CIFSR
```

```text
AT+CIPMUX=1
```

```text
AT+CIPSERVER=1,80
```

Después abrimos desde el navegador:

```text
http://IP_DEL_ESP8266
```

Observaremos:

```text
0,CONNECT
```

y una petición parecida a:

```text
+IPD,0,...:GET / HTTP/1.1
```

Para transmitir:

```text
AT+CIPSEND=0,longitud
```

y finalmente podemos cerrar:

```text
AT+CIPCLOSE=0
```

---

# 22. Práctica 1 — Crear el servidor

Realiza los siguientes pasos:

1. Conecta el ESP8266 a la red Wi-Fi.
2. Obtén su dirección IP.
3. Activa múltiples conexiones.
4. Crea un servidor TCP en el puerto 80.
5. Accede desde un navegador.
6. Comprueba que aparece `CONNECT`.
7. Localiza la petición `GET /`.
8. Identifica el número de conexión.

Documenta los resultados obtenidos.

---

# 23. Práctica 2 — Analizar la petición HTTP

Copia en tu documentación la petición recibida desde el navegador.

Localiza:

```text
GET /
```

y:

```text
Host:
```

Responde:

* ¿Qué dispositivo actúa como cliente?
* ¿Qué dispositivo actúa como servidor?
* ¿Cuál es la dirección IP del servidor?
* ¿Qué puerto estamos utilizando?
* ¿Qué identificador ha recibido la conexión?

---

# 24. Práctica 3 — Enviar datos

Con una conexión activa prueba:

```text
AT+CIPSEND=0,4
```

y después:

```text
HOLA
```

Comprueba si aparece:

```text
SEND OK
```

Si el identificador de conexión no es `0`, sustituye el número por el identificador real.

---

# 25. Problemas frecuentes

## `AT+CIPSERVER=1,80` devuelve ERROR

Comprueba primero:

```text
AT+CIPMUX?
```

Debe aparecer:

```text
+CIPMUX:1
```

El servidor necesita el modo de múltiples conexiones.

---

## El navegador no conecta

Comprueba:

```text
AT+CIFSR
```

y verifica que estás utilizando la IP correcta.

El ordenador y el ESP8266 deben poder comunicarse a través de la misma red local.

Algunas redes de centros educativos o redes de invitados utilizan **aislamiento de clientes**, lo que puede impedir que dos dispositivos Wi-Fi se comuniquen directamente aunque ambos tengan conexión a Internet.

---

## Aparece CONNECT pero no veo una página

Eso es normal en esta fase.

Hemos creado un servidor TCP, pero todavía necesitamos responder correctamente a la petición HTTP.

---

## Aparecen varias conexiones

Los navegadores modernos pueden realizar más de una petición.

Por ejemplo, además de:

```text
GET /
```

pueden solicitar otros recursos.

Por eso debemos prestar atención al identificador:

```text
0,CONNECT
1,CONNECT
```

---

## `AT+CIPSEND` devuelve ERROR

Comprueba que:

* Existe una conexión activa.
* Estás utilizando su identificador correcto.
* Has indicado correctamente el número de bytes.
* El servidor sigue funcionando.

---

# 26. Lo que hemos conseguido

Al terminar esta práctica tendremos:

```text
┌─────────────┐
│ NAVEGADOR   │
│   Cliente   │
└──────┬──────┘
       │
       │ HTTP
       │ TCP/IP
       │ Wi-Fi
       ▼
┌─────────────┐
│   ESP8266   │
│ Servidor TCP│
└──────┬──────┘
       │
       │ UART 9600
       ▼
┌─────────────┐
│Arduino Mega │
└─────────────┘
```

Por primera vez, un navegador de nuestra red puede establecer una comunicación con nuestro proyecto Arduino.

---

# 27. Preparación para la siguiente lección

Todavía estamos introduciendo manualmente comandos como:

```text
AT+CIPSERVER=1,80
```

o:

```text
AT+CIPSEND=0,4
```

Esto no sería práctico en un dispositivo real.

El siguiente paso será conseguir que **Arduino haga todo este trabajo automáticamente**.

El programa deberá ser capaz de:

```text
recibir GET
      │
      ▼
interpretar petición
      │
      ▼
generar HTML
      │
      ▼
calcular longitud
      │
      ▼
AT+CIPSEND
      │
      ▼
enviar página
```

Después podremos incorporar botones:

```text
┌─────────────────────────────┐
│       ARDUINO MEGA          │
│                             │
│        [ LED ON ]           │
│                             │
│        [ LED OFF ]          │
│                             │
└─────────────────────────────┘
```

y esos botones podrán controlar físicamente componentes conectados al Arduino Mega.

Ese será el siguiente paso hacia nuestro **sistema IoT controlado desde una aplicación web**.
