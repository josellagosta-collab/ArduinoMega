# Lección 19 — Visualización de datos con Grafana

## 1. Objetivos

En la Lección 18 conseguimos almacenar las medidas del Arduino Mega en InfluxDB.

Nuestro sistema actual es:

```text
SENSOR
   │
   ▼
ARDUINO MEGA
   │
   ▼
ESP8266
   │
   ▼
Wi-Fi
   │
   ▼
INFLUXDB
```

Ahora añadiremos Grafana:

```text
SENSOR
   │
   ▼
ARDUINO MEGA
   │
   ▼
ESP8266
   │
   ▼
INFLUXDB
   │
   ▼
GRAFANA
   │
   ▼
DASHBOARD
```

Al finalizar esta lección seremos capaces de:

* Instalar Grafana en Windows 11.
* Acceder a la interfaz web de Grafana.
* Conectar Grafana con InfluxDB.
* Consultar los datos del Arduino.
* Crear un dashboard.
* Representar el valor del sensor mediante una gráfica temporal.
* Mostrar el último valor recibido.
* Crear un indicador tipo Gauge.
* Configurar la actualización automática del dashboard.

---

# 2. ¿Qué es Grafana?

Grafana es una aplicación especializada en visualizar y analizar datos.

InfluxDB y Grafana realizan trabajos diferentes.

InfluxDB:

```text
ALMACENA LOS DATOS
```

Grafana:

```text
VISUALIZA LOS DATOS
```

Por tanto:

```text
Arduino
   │
   ▼
InfluxDB
   │
   │ almacena
   ▼
datos históricos
   │
   │ consulta
   ▼
Grafana
   │
   ▼
gráficas
indicadores
paneles
```

---

# 3. Punto de partida

Antes de continuar debemos tener funcionando la Lección 18.

Nuestro Arduino está enviando aproximadamente cada 10 segundos:

```text
sensor valor=411,voltaje=2.01
```

a:

```text
InfluxDB
```

con la configuración:

```text
Servidor:
10.113.170.1

Puerto:
8086

Organization:
ArduinoCurso

Bucket:
arduino

Measurement:
sensor
```

y los fields:

```text
valor
voltaje
```

---

# 4. Comprobar InfluxDB

Antes de instalar Grafana abrimos:

```text
http://localhost:8086
```

Comprobamos que InfluxDB funciona.

En Data Explorer debemos poder localizar:

```text
Bucket
    arduino

Measurement
    sensor

Fields
    valor
    voltaje
```

Si los datos aparecen correctamente podemos continuar.

---

# 5. Descargar Grafana

Utilizaremos Grafana OSS para Windows.

Accedemos a la página oficial de descarga de Grafana.

Seleccionamos:

```text
Edition:
Grafana OSS

Platform:
Windows

Architecture:
64 Bit
```

Descargamos el instalador:

```text
Windows Installer
```

El archivo tendrá un nombre similar a:

```text
grafana_13.x.x_windows_amd64.msi
```

---

# 6. Instalar Grafana

Ejecutamos el archivo `.msi`.

Seguimos el asistente de instalación.

Podemos mantener las opciones predeterminadas.

Una vez terminada la instalación, Grafana quedará instalado en Windows.

---

# 7. Comprobar el servicio

Grafana puede ejecutarse como un servicio de Windows.

Pulsamos:

```text
Windows + R
```

escribimos:

```text
services.msc
```

y pulsamos ENTER.

Buscamos:

```text
Grafana
```

El servicio debe aparecer como:

```text
En ejecución
```

---

# 8. Acceder a Grafana

Abrimos el navegador.

Introducimos:

```text
http://localhost:3000
```

El puerto predeterminado de Grafana es:

```text
3000
```

Debería aparecer la pantalla de inicio de sesión.

---

# 9. Primer acceso

En una instalación nueva, utilizaremos las credenciales iniciales que indique Grafana.

Habitualmente:

```text
Usuario:
admin

Contraseña:
admin
```

Grafana puede solicitar inmediatamente que cambiemos la contraseña.

Establecemos una contraseña propia para el administrador.

---

# 10. Dos aplicaciones diferentes

Ahora tenemos dos servicios ejecutándose en nuestro ordenador:

```text
INFLUXDB

http://localhost:8086
```

y:

```text
GRAFANA

http://localhost:3000
```

Son aplicaciones independientes.

La arquitectura es:

```text
              WINDOWS 11
                  │
        ┌─────────┴─────────┐
        │                   │
        ▼                   ▼
     InfluxDB             Grafana
     :8086                 :3000
        │                   │
        └─────────►─────────┘
             consultas
```

---

# 11. Añadir InfluxDB a Grafana

Dentro de Grafana buscamos:

```text
Connections
```

Después:

```text
Add new connection
```

Buscamos:

```text
InfluxDB
```

Seleccionamos el datasource de InfluxDB.

Grafana incluye soporte para InfluxDB, por lo que no necesitamos instalar manualmente otro programa.

Seleccionamos:

```text
Add new data source
```

---

# 12. Nombre del datasource

Podemos utilizar:

```text
InfluxDB-Arduino
```

Este nombre nos permitirá identificar fácilmente la conexión.

---

# 13. URL de InfluxDB

Como Grafana e InfluxDB están instalados en el mismo ordenador podemos utilizar:

```text
http://localhost:8086
```

También podríamos utilizar:

```text
http://10.113.170.1:8086
```

pero en nuestro caso es más sencillo:

```text
http://localhost:8086
```

---

# 14. Seleccionar el producto

Seleccionamos:

```text
InfluxDB OSS 2.x
```

Nuestra instalación es:

```text
InfluxDB OSS 2.9.1
```

---

# 15. Seleccionar el lenguaje de consulta

Para esta instalación utilizaremos:

```text
Flux
```

Flux permite consultar directamente los buckets de InfluxDB 2.x.

---

# 16. Configuración de InfluxDB

En la sección de configuración introducimos:

```text
Organization:
ArduinoCurso
```

Después:

```text
Default Bucket:
arduino
```

Y finalmente:

```text
Token:
NUESTRO_TOKEN
```

Debemos utilizar un token que tenga permisos de lectura sobre el bucket:

```text
arduino
```

---

# 17. Resumen de configuración

Nuestra configuración será:

```text
Name:
InfluxDB-Arduino

URL:
http://localhost:8086

Product:
InfluxDB OSS 2.x

Query Language:
Flux

Organization:
ArduinoCurso

Default Bucket:
arduino

Token:
TOKEN_DE_INFLUXDB
```

---

# 18. Guardar y comprobar

Pulsamos:

```text
Save & test
```

Grafana intentará conectarse a InfluxDB.

Queremos obtener un mensaje indicando que la conexión funciona correctamente.

Si aparece un error no continuaremos hasta solucionarlo.

---

# 19. ¿Qué acabamos de conseguir?

Ahora tenemos:

```text
Arduino
   │
   ▼
ESP8266
   │
   ▼
InfluxDB
   │
   ▼
Grafana
```

Pero Grafana todavía no muestra nada.

Primero debemos decirle qué datos queremos consultar.

---

# 20. Primera consulta con Flux

Vamos a utilizar una consulta sencilla.

La estructura básica será:

```text
from(bucket: "arduino")
```

Esto significa:

> Obtener datos del bucket arduino.

Después indicaremos un intervalo temporal.

Por ejemplo:

```text
|> range(start: -1h)
```

Esto significa:

> Buscar datos de la última hora.

---

# 21. Seleccionar la measurement

Queremos solamente:

```text
sensor
```

Por tanto añadimos:

```text
|> filter(fn: (r) => r._measurement == "sensor")
```

---

# 22. Seleccionar el field

Queremos visualizar:

```text
valor
```

Añadimos:

```text
|> filter(fn: (r) => r._field == "valor")
```

La consulta completa será:

```text
from(bucket: "arduino")
    |> range(start: -1h)
    |> filter(fn: (r) => r._measurement == "sensor")
    |> filter(fn: (r) => r._field == "valor")
```

---

# 23. Probar la consulta

Podemos probar esta consulta desde:

```text
Explore
```

Seleccionamos:

```text
InfluxDB-Arduino
```

Introducimos:

```text
from(bucket: "arduino")
    |> range(start: -1h)
    |> filter(fn: (r) => r._measurement == "sensor")
    |> filter(fn: (r) => r._field == "valor")
```

Ejecutamos la consulta.

Si Arduino está enviando datos deberíamos empezar a ver puntos.

---

# 24. Crear nuestro primer dashboard

Ahora vamos a crear una pantalla donde podamos colocar varios indicadores.

Buscamos:

```text
Dashboards
```

Seleccionamos:

```text
New
```

y:

```text
New dashboard
```

Después:

```text
Add visualization
```

Seleccionamos:

```text
InfluxDB-Arduino
```

---

# 25. Panel 1 — Valor del sensor

Introducimos:

```text
from(bucket: "arduino")
    |> range(start: v.timeRangeStart, stop: v.timeRangeStop)
    |
```
