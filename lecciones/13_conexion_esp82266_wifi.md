# Lección 13 — Conexión del ESP8266 a una red Wi-Fi

## 1. Objetivos

En esta práctica aprenderemos a conectar el módulo **ESP8266** a una red Wi-Fi utilizando comandos AT enviados desde el Arduino Mega 2560.

Al finalizar seremos capaces de:

* Configurar el ESP8266 como estación Wi-Fi.
* Buscar las redes Wi-Fi disponibles.
* Conectarnos a una red mediante su SSID y contraseña.
* Comprobar que la conexión se ha realizado correctamente.
* Consultar la dirección IP asignada al ESP8266.
* Entender el papel que tendrá el ESP8266 en nuestro proyecto IoT.

---

## 2. Material necesario

* Arduino Mega 2560 R3.
* Módulo ESP8266 ESP-01.
* Protoboard.
* Fuente estable de 3,3 V para el ESP8266.
* Resistencia de 1 kΩ.
* Resistencia de 2 kΩ.
* Cables Dupont.
* Cable USB.
* Ordenador con Visual Studio Code y PlatformIO.
* Una red Wi-Fi de 2,4 GHz.

> El ESP8266 trabaja con redes Wi-Fi de **2,4 GHz**.

---

## 3. Conexiones

Utilizaremos las mismas conexiones que comprobamos en la práctica anterior.

### Comunicación serie

| Arduino Mega | ESP8266                        |
| ------------ | ------------------------------ |
| D18 / TX1    | RX mediante divisor de tensión |
| D19 / RX1    | TX                             |
| GND          | GND                            |

La conexión del TX del Mega debe realizarse mediante el divisor:

```text
Mega D18 / TX1
      │
     1 kΩ
      │
      ├────────────── ESP8266 RX
      │
     2 kΩ
      │
     GND
```

De esta forma reducimos aproximadamente los 5 V del Mega a:

```text
5 × 2 / (1 + 2) = 3,33 V
```

### Alimentación

```text
Fuente 3,3 V ───────── VCC ESP8266
       3,3 V ───────── EN / CH_PD
       GND ─────────── GND ESP8266
                         │
                         └──── GND Arduino Mega
```

Es fundamental que exista una **masa común**.

---

# 4. Programa para enviar comandos AT

En nuestro ESP8266 hemos comprobado experimentalmente que la comunicación UART funciona a:

```text
9600 baudios
```

Utilizaremos:

* `Serial` para comunicar el Mega con el ordenador.
* `Serial1` para comunicar el Mega con el ESP8266.

Crea:

```text
ejemplos/13_conexion_wifi/main.cpp
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
    Serial.println("==============================");
    Serial.println(" ESP8266 - Conexion WiFi");
    Serial.println("==============================");
    Serial.println();
    Serial.println("Escribe comandos AT y pulsa ENTER");
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

---

# 5. Comprobar la comunicación

Abrimos el monitor serie de PlatformIO y escribimos:

```text
AT
```

El ESP8266 debe responder:

```text
OK
```

No continuaremos hasta obtener esta respuesta.

---

# 6. Comprobar el modo Wi-Fi

El ESP8266 puede funcionar de diferentes formas.

Los modos principales son:

| Valor | Modo         | Función                  |
| ----: | ------------ | ------------------------ |
|     1 | Station      | Se conecta a un router   |
|     2 | Access Point | Crea su propia red Wi-Fi |
|     3 | Station + AP | Realiza ambas funciones  |

Para nuestro proyecto queremos que el ESP8266 se conecte a una red existente.

Por tanto utilizaremos:

```text
Station
```

Consultamos el modo actual:

```text
AT+CWMODE?
```

Podemos recibir, por ejemplo:

```text
+CWMODE:1

OK
```

Si ya aparece `1`, el módulo está configurado como estación.

---

# 7. Configurar el modo Station

Si fuera necesario, escribimos:

```text
AT+CWMODE=1
```

La respuesta esperada es:

```text
OK
```

Ahora el ESP8266 funcionará como un dispositivo conectado a una red Wi-Fi, igual que un ordenador, teléfono o tablet.

Conceptualmente tendremos:

```text
                     ROUTER Wi-Fi
                         │
                      2,4 GHz
                         │
                         ▼
                    ESP8266
                         │
                       UART
                         │
                         ▼
                 Arduino Mega
```

---

# 8. Buscar redes Wi-Fi

Ahora pediremos al ESP8266 que busque las redes Wi-Fi que tiene a su alcance.

Escribimos:

```text
AT+CWLAP
```

Después de unos segundos aparecerá una lista de redes.

Por ejemplo:

```text
+CWLAP:(3,"Aula_WiFi",-47,"aa:bb:cc:dd:ee:ff",6)
+CWLAP:(4,"RouterCasa",-61,"11:22:33:44:55:66",11)
+CWLAP:(3,"RedProfesores",-72,"77:88:99:aa:bb:cc",1)

OK
```

No es necesario comprender todavía todos los valores.

Nos interesa especialmente:

```text
"Aula_WiFi"
```

que corresponde al **SSID**, es decir, el nombre de la red.

También podemos observar valores como:

```text
-47
-61
-72
```

que indican aproximadamente la intensidad de la señal recibida.

Un valor más próximo a cero indica generalmente una señal más fuerte.

Por ejemplo:

```text
-40 dBm → señal muy buena

-60 dBm → señal correcta

-80 dBm → señal débil
```

---

# 9. Conectarnos a una red Wi-Fi

Supongamos que tenemos:

```text
SSID: Aula_WiFi

Contraseña: MiClave1234
```

Escribimos:

```text
AT+CWJAP="Aula_WiFi","MiClave1234"
```

Debemos sustituir estos datos por los de nuestra red real.

Después de unos segundos podemos recibir algo parecido a:

```text
WIFI CONNECTED
WIFI GOT IP

OK
```

Esto significa que el ESP8266 se ha asociado correctamente al punto de acceso y ha obtenido configuración IP.

---

# 10. No guardar contraseñas reales en GitHub

La contraseña de la red Wi-Fi es información privada.

Por tanto, nunca debemos publicar en nuestro repositorio algo como:

```cpp
const char* password = "MiContraseñaReal";
```

Si hacemos capturas de pantalla para la documentación, también debemos comprobar que no aparece la contraseña.

En esta práctica introduciremos las credenciales manualmente desde el monitor serie.

Más adelante aprenderemos una forma más adecuada de manejar las credenciales desde nuestros programas.

---

# 11. Comprobar la red a la que estamos conectados

Podemos consultar la conexión actual mediante:

```text
AT+CWJAP?
```

Una respuesta típica será similar a:

```text
+CWJAP:"Aula_WiFi","aa:bb:cc:dd:ee:ff",6,-52

OK
```

Esto nos permite comprobar que el ESP8266 continúa conectado.

---

# 12. Obtener la dirección IP

Ahora utilizaremos uno de los comandos más importantes de esta práctica:

```text
AT+CIFSR
```

Podemos obtener una respuesta parecida a:

```text
+CIFSR:STAIP,"192.168.1.37"
+CIFSR:STAMAC,"18:fe:34:xx:xx:xx"

OK
```

La información más importante es:

```text
192.168.1.37
```

Esta es la dirección IP que el router ha asignado al ESP8266.

Evidentemente, en cada red puede ser diferente.

---

# 13. ¿Qué acaba de ocurrir?

Antes teníamos:

```text
Arduino Mega
     │
     │ UART
     ▼
 ESP8266
```

Ahora tenemos:

```text
Arduino Mega
     │
     │ UART
     ▼
 ESP8266
     │
     │ Wi-Fi
     ▼
   Router
     │
     ▼
 Red local
```

Nuestro proyecto Arduino acaba de adquirir **conectividad de red**.

Este es un paso fundamental hacia un sistema IoT.

---

# 14. Comprobar todos los parámetros

Realiza ahora, en orden, los siguientes comandos:

```text
AT
```

```text
AT+CWMODE?
```

```text
AT+CWLAP
```

```text
AT+CWJAP?
```

```text
AT+CIFSR
```

Guarda las respuestas obtenidas.

---

# 15. Desconectarse de la red

Podemos desconectar voluntariamente el ESP8266 mediante:

```text
AT+CWQAP
```

Después podemos comprobar:

```text
AT+CWJAP?
```

y volver a conectarnos mediante:

```text
AT+CWJAP="SSID","CONTRASEÑA"
```

---

# 16. Primera práctica

Realiza el proceso completo:

1. Comprueba la comunicación mediante `AT`.
2. Consulta el modo mediante `AT+CWMODE?`.
3. Configura Station mediante `AT+CWMODE=1`.
4. Busca redes mediante `AT+CWLAP`.
5. Identifica la red que vas a utilizar.
6. Anota su intensidad de señal.
7. Conéctate mediante `AT+CWJAP`.
8. Comprueba la conexión mediante `AT+CWJAP?`.
9. Obtén la dirección IP mediante `AT+CIFSR`.

Documenta los resultados.

---

# 17. Segunda práctica — Comparar señales Wi-Fi

Ejecuta:

```text
AT+CWLAP
```

Selecciona al menos tres redes y anota:

| SSID  | Intensidad |
| ----- | ---------: |
| Red 1 |            |
| Red 2 |            |
| Red 3 |            |

Indica cuál tiene la señal más fuerte y cuál la más débil.

---

# 18. Tercera práctica — Desconexión y reconexión

Ejecuta:

```text
AT+CWQAP
```

Comprueba que el ESP8266 se ha desconectado.

Después vuelve a conectarlo:

```text
AT+CWJAP="SSID","CONTRASEÑA"
```

Finalmente comprueba la dirección IP:

```text
AT+CIFSR
```

---

# 19. Problemas frecuentes

## `AT+CWLAP` no muestra redes

Comprueba:

* Que el ESP8266 está en modo Station.
* Que existen redes de 2,4 GHz próximas.
* Que la alimentación de 3,3 V es estable.
* Que la antena del ESP8266 no está tapada por elementos metálicos.

---

## `AT+CWJAP` devuelve ERROR o FAIL

Comprueba:

* El nombre exacto del SSID.
* La contraseña.
* Mayúsculas y minúsculas.
* Que la red sea compatible con 2,4 GHz.
* Que la señal tenga suficiente intensidad.

---

## Aparece `WIFI DISCONNECT`

El ESP8266 ha perdido la conexión.

Puede deberse a:

* Señal débil.
* Alimentación inestable.
* Reinicio del router.
* Contraseña incorrecta.
* Problemas de cobertura.

---

## No responde a ningún comando

En nuestro montaje debemos recordar que hemos determinado experimentalmente:

```cpp
Serial1.begin(9600);
```

Además debemos comprobar:

```text
Mega TX1 D18 → divisor → ESP RX

ESP TX → Mega RX1 D19

GND Mega → GND fuente → GND ESP8266
```

---

# 20. Resultado esperado

Al finalizar la práctica debemos ser capaces de ejecutar:

```text
AT+CIFSR
```

y obtener una dirección similar a:

```text
+CIFSR:STAIP,"192.168.1.37"
```

Esto demuestra que:

```text
Arduino Mega
      │
      ▼
   ESP8266
      │
      ▼
    Wi-Fi
      │
      ▼
    Router
      │
      ▼
   Red local
```

funciona correctamente.

---

# 21. Relación con el proyecto final

Nuestro objetivo final será construir aproximadamente esta arquitectura:

```text
Sensores
   │
   ▼
Arduino Mega
   │
   │ UART
   ▼
ESP8266
   │
   │ Wi-Fi
   ▼
┌─────────────────────────────┐
│            RED              │
├─────────────────────────────┤
│                             │
│  Aplicación web             │
│       │                     │
│       └── Control Arduino   │
│                             │
│  InfluxDB                   │
│       │                     │
│       └── Datos sensores    │
│                             │
│  Grafana                    │
│       │                     │
│       └── Dashboard         │
│                             │
└─────────────────────────────┘
```

En esta lección hemos conseguido el elemento que faltaba:

**Arduino ya puede disponer de conectividad Wi-Fi mediante el ESP8266.**

En la siguiente práctica utilizaremos esa conexión para comenzar a trabajar con **TCP/IP y crear las bases de nuestro primer servidor web controlado desde Arduino**.
