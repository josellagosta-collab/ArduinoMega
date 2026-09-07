# Preparar Visual Studio Code para programar Arduino Mega 2560 R3 con PlatformIO

En esta guía vamos a preparar **Visual Studio Code** para programar una placa **Arduino Mega 2560 R3** utilizando la extensión **PlatformIO IDE**.

En nuestro caso, Windows ha detectado la placa conectada mediante USB en:

```text
COM7
```

---

## 1. Instalar Visual Studio Code

Si todavía no tenemos instalado Visual Studio Code, debemos instalarlo en Windows.

Una vez instalado, abrimos:

```text
Visual Studio Code
```

---

## 2. Instalar PlatformIO IDE

En Visual Studio Code:

1. Pulsamos el icono **Extensions** situado en la barra lateral izquierda.
2. También podemos abrirlo mediante:

```text
Ctrl + Shift + X
```

3. En el buscador escribimos:

```text
PlatformIO IDE
```

4. Seleccionamos la extensión **PlatformIO IDE**.
5. Pulsamos **Install**.

PlatformIO instalará automáticamente las herramientas necesarias para trabajar con diferentes placas y microcontroladores.

Cuando termine la instalación es recomendable reiniciar Visual Studio Code.

---

## 3. Abrir PlatformIO

Después de instalar la extensión aparecerá el icono de **PlatformIO** en la barra lateral de Visual Studio Code.

También podemos acceder mediante:

```text
PlatformIO: Home
```

desde la paleta de comandos:

```text
Ctrl + Shift + P
```

---

## 4. Crear un nuevo proyecto

Desde **PlatformIO Home** seleccionamos:

```text
New Project
```

Configuramos el proyecto de la siguiente manera:

```text
Name: prueba_mega
Board: Arduino Mega or Mega 2560 ATmega2560 (Mega 2560)
Framework: Arduino
```

En **Location** podemos dejar activada la ubicación predeterminada de PlatformIO o seleccionar nuestra carpeta de proyectos.

Finalmente pulsamos:

```text
Finish
```

PlatformIO descargará e instalará automáticamente las herramientas necesarias para trabajar con el Arduino Mega.

La primera vez este proceso puede tardar unos minutos.

---

## 5. Estructura del proyecto

PlatformIO creará una estructura similar a esta:

```text
prueba_mega/
│
├── include/
├── lib/
├── src/
│   └── main.cpp
│
├── test/
│
└── platformio.ini
```

Los dos archivos más importantes son:

```text
src/main.cpp
platformio.ini
```

El programa Arduino se escribirá normalmente en:

```text
src/main.cpp
```

---

## 6. Configurar Arduino Mega 2560 R3

Abrimos el archivo:

```text
platformio.ini
```

Para una placa **Arduino Mega 2560 R3** debe contener:

```ini
[env:megaatmega2560]
platform = atmelavr
board = megaatmega2560
framework = arduino
```

Como Windows ha detectado nuestra placa en **COM7**, podemos indicar también el puerto:

```ini
[env:megaatmega2560]
platform = atmelavr
board = megaatmega2560
framework = arduino

upload_port = COM7
monitor_port = COM7
monitor_speed = 9600
```

De esta forma PlatformIO utilizará COM7 para cargar los programas y para abrir posteriormente el monitor serie.

---

## 7. Crear el primer programa

Abrimos:

```text
src/main.cpp
```

y sustituimos su contenido por:

```cpp
#include <Arduino.h>

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);

    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}
```

Este programa utiliza el LED integrado en la placa.

El LED permanecerá:

```text
1 segundo encendido
1 segundo apagado
```

repitiendo continuamente el proceso.

---

## 8. Compilar el programa

Antes de enviarlo al Arduino podemos comprobar que el código compila correctamente.

En la barra inferior de PlatformIO pulsamos:

```text
✓ Build
```

También podemos utilizar la paleta de comandos:

```text
Ctrl + Shift + P
```

y ejecutar:

```text
PlatformIO: Build
```

Si todo funciona correctamente aparecerá al final:

```text
SUCCESS
```

---

## 9. Cargar el programa en el Arduino Mega

Conectamos el **Arduino Mega 2560 R3** mediante USB.

En nuestro caso Windows lo ha detectado como:

```text
COM7
```

Pulsamos el botón:

```text
→ Upload
```

de la barra inferior de PlatformIO.

También podemos ejecutar:

```text
PlatformIO: Upload
```

PlatformIO realizará automáticamente:

```text
Compilar
   ↓
Localizar Arduino Mega
   ↓
Abrir COM7
   ↓
Transferir programa
   ↓
Reiniciar Arduino
```

Si todo funciona correctamente veremos:

```text
SUCCESS
```

El LED integrado del Arduino Mega debería comenzar a parpadear cada segundo.

---

## 10. Probar el puerto serie

También podemos comprobar la comunicación entre el Arduino Mega y el ordenador mediante el puerto serie.

Modificamos `src/main.cpp`:

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

Cargamos nuevamente el programa mediante:

```text
Upload
```

---

## 11. Abrir el monitor serie

Después de cargar el programa abrimos:

```text
PlatformIO: Serial Monitor
```

También podemos utilizar el icono correspondiente de la barra inferior de PlatformIO.

La velocidad debe coincidir con:

```cpp
Serial.begin(9600);
```

Por eso hemos configurado en `platformio.ini`:

```ini
monitor_speed = 9600
```

En pantalla deberíamos observar:

```text
Arduino Mega 2560 R3
Conexion serie funcionando correctamente
Arduino funcionando...
Arduino funcionando...
Arduino funcionando...
```

Si aparecen estos mensajes, la comunicación entre **Visual Studio Code, PlatformIO y el Arduino Mega 2560 R3** funciona correctamente.

---

## 12. Configuración final del proyecto

Nuestro archivo `platformio.ini` puede quedar definitivamente así:

```ini
[env:megaatmega2560]
platform = atmelavr
board = megaatmega2560
framework = arduino

upload_port = COM7
monitor_port = COM7
monitor_speed = 9600
```

Y la estructura básica de trabajo será:

```text
Arduino Mega 2560 R3
        │
       USB
        │
        ▼
      COM7
        │
        ▼
Visual Studio Code
        │
        ▼
PlatformIO IDE
        │
        ▼
src/main.cpp
```

---

## 13. Configuración utilizada

| Elemento           | Configuración        |
| ------------------ | -------------------- |
| Placa              | Arduino Mega 2560 R3 |
| Microcontrolador   | ATmega2560           |
| IDE                | Visual Studio Code   |
| Extensión          | PlatformIO IDE       |
| Plataforma         | atmelavr             |
| Board PlatformIO   | megaatmega2560       |
| Framework          | Arduino              |
| Puerto USB         | COM7                 |
| Monitor serie      | 9600 baudios         |
| Programa principal | `src/main.cpp`       |

Con esta configuración el entorno queda preparado para comenzar a realizar las prácticas y proyectos con el **Arduino Mega 2560 R3**.
