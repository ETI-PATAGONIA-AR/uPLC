# uPLC v5 - Conversor Ladder a Arduino

## 🆕 Novedades v4.1 - Modbus RS485

### Nuevas Características
1. ✅ **Comunicación Modbus RS485**: Protocolo industrial estándar
2. ✅ **7 Salidas Digitales**: Q1-Q7 (antes solo Q1-Q5)
3. ✅ **10 Registros Modbus**: MB0-MB9 para comunicación
4. ✅ **Nuevos Bloques Ladder**:
   - **MB_SLAVE**: Condición sobre registro Modbus
   - **MB_READ**: Leer registro de dispositivo esclavo
   - **MB_WRITE**: Escribir registro a dispositivo esclavo
5. ✅ **Compatible con PLCs industriales**: Protocolo Modbus RTU estándar

## Ejemplo BASICO de un Controlador de VENTILACION con las version uPLCv4:

<img width="1366" height="720" alt="Ctl_VENTILACIO_LADDER" src="https://github.com/user-attachments/assets/27ba6333-7e4a-4d81-baa9-891243cf9284" />

<img width="1366" height="720" alt="Ctl_VENTILACION_SKETCH" src="https://github.com/user-attachments/assets/00ec18d3-3525-4b8a-9d84-1773de58de85" />

<img width="1366" height="720" alt="Ctl_VENTILACION_SIMU" src="https://github.com/user-attachments/assets/580d02bf-c426-4891-b340-2c4c16039f11" />

### Correcciones Anteriores (v3.0)
1. ✅ **PWM corregido**: Ahora genera correctamente `analogWrite(pin, valor)` en lugar de solo asignar la variable
2. ✅ **SET_VAR con ADC**: Cuando se usa ADC seguido de SET_VAR sin valor explícito, automáticamente toma la referencia del ADC
3. ✅ **AND/OR**: Funcionando correctamente

### Nuevas Funcionalidades
1. ✅ **Creación de carpetas**: Al guardar un proyecto, se crea una carpeta con el nombre del proyecto
2. ✅ **Archivos generados**: 
   - `proyecto.uplc` (archivo Ladder)
   - `proyecto.ino` (sketch Arduino listo para cargar)
3. ✅ **Display LCD I2C 20x4**: Soporte integrado para mostrar estados en tiempo real
   - Dirección I2C: 0x27
   - Conectado en A4 (SDA) y A5 (SCL)
   - Muestra entradas digitales (I1-I7)
   - Muestra salidas digitales (Q1-Q5)
   - Muestra valores analógicos (A0, A1)
   - Muestra duty cycle del PWM (0-100%)

## Formato del Display LCD
```
Línea 0: I1 2 3 4 5 6 7 A0XXX
Línea 1:  X X X X X X X A1XXX
Línea 2: Q1 2 3 4 5 6 7 PWMXX
Línea 3:  X X X X X X X
```
Donde X = 0 o 1 (estado digital), PWM = 00-99% (duty cycle)

## Instalación de Dependencias (Recuerden que deben de tener instalado Python 3.10)

### Python (PC)
```bash
pip install -r requirements.txt
```

### Arduino IDE
Instalar las siguientes librerías desde el Library Manager:

1. **LiquidCrystal I2C** (para display LCD):
   - Ir a: Sketch → Include Library → Manage Libraries
   - Buscar: "LiquidCrystal I2C" by Frank de Brabander
   - Instalar

2. **ModbusMaster** 🆕 (para comunicación RS485):
   - Ir a: Sketch → Include Library → Manage Libraries
   - Buscar: "ModbusMaster" by Doc Walker
   - Instalar
   - O descargar desde: https://github.com/4-20ma/ModbusMaster

## Uso

1. **Ejecutar el programa**:
   ```
   run_uPLCv3.bat
   ```

2. **Crear tu programa Ladder**:
   - Usar los botones de la toolbox para agregar contactos, bobinas, funciones, etc.
   - Guardar el proyecto (se creará una carpeta con el nombre del proyecto)

3. **Cargar al Arduino**:
   - Abrir el archivo `.ino` generado en la carpeta del proyecto
   - Conectar el Arduino NANO
   - Seleccionar puerto COM correcto
   - Subir el sketch

4. **Conectar el Display LCD (opcional)**:
   - LCD SDA → Arduino A4
   - LCD SCL → Arduino A5
   - LCD VCC → Arduino 5V
   - LCD GND → Arduino GND

## Pinout Arduino NANO

### Entradas Digitales
- I1 → D2
- I2 → D4
- I3 → D5
- I4 → D6
- I5 → D7
- I6 → D8
- I7 → D9

### Salidas Digitales
- Q1 → D14 (A0)
- Q2 → D15 (A1)
- Q3 → D16 (A2)
- Q4 → D17 (A3)
- Q5 → D3 (PWM)
- Q6 → D12 🆕
- Q7 → D13 🆕

### Comunicación RS485 🆕
- RX → D10 (RS485)
- TX → D11 (RS485)

### Entradas Analógicas
- A0 → A6 (mapeado 0-255)
- A1 → A7 (mapeado 0-255)

### Display LCD I2C
- SDA → A4
- SCL → A5

## Estructura del Proyecto Generado
```
nombre_proyecto/
  ├── nombre_proyecto.uplc  (archivo Ladder - para editar en uPLC)
  └── nombre_proyecto.ino   (sketch Arduino - para cargar al NANO)
```

## Funciones Disponibles

### Contactos
- NO (Normalmente Abierto)
- NC (Normalmente Cerrado)

### Bobinas
- COIL (Bobina normal)
- COIL_NC (Bobina negada)

### Funciones Especiales
- ADC: Leer entrada analógica (A0, A1)
- PWM: Salida PWM en Q5
- SET_VAR: Guardar valor en variable (V0-V9)
- CMP_GT: Comparador Mayor que (>)
- CMP_LT: Comparador Menor que (<)
- CMP_EQ: Comparador Igual a (==)
- TON: Temporizador ON-delay
- TOFF: Temporizador OFF-delay

### Funciones Modbus RS485 🆕
- MB_SLAVE: Condición sobre registro Modbus (MB0-MB9)
- MB_READ: Leer registro desde esclavo Modbus
- MB_WRITE: Escribir registro a esclavo Modbus

### Funciones Booleanas
- AND_A/AND_B: Unión AND entre ramas
- OR_A/OR_B: Unión OR entre ramas

## Ejemplo de Uso - PWM con ADC

**Rung 1**: Leer A0 y guardar en V0
- Contacto: ADC (A0)
- Salida: SET_VAR (V0)

**Rung 2**: Si V0 > 128, activar PWM con valor V0
- Contacto: CMP_GT (V0 > 128)
- Salida: PWM (Q5, valor: V0)

El código generado será:
```cpp
// [1] Rung 1
bool _r0 = ((A0 > 0));
if (_r0) V0 = A0;  // ← AUTO-ASIGNA A0 a V0

// [2] Rung 2
bool _r1 = ((V0 > 128));
if (_r1) analogWrite(3, V0);  // ← USA analogWrite CORRECTAMENTE
else Q5 = 0;
```

## 🔌 Comunicación Modbus RS485

El uPLC v3.1 incluye soporte completo para Modbus RTU, permitiendo comunicación con dispositivos industriales.

### Ejemplo 1: Leer Sensor Remoto
```
Rung 1: Leer temperatura del esclavo ID=5, guardar en MB0
[TON:T0=1000] ───> [MB_READ:MB0, Slave=5]

Rung 2: Si temperatura > 80°C, activar alarma
[MB_SLAVE:MB0=80] ───> [COIL:Q1]
```

### Ejemplo 2: Controlar Actuador Remoto
```
Rung 1: Si sensor activado, enviar comando al esclavo ID=3
[NO:I1] ───> [SET_VAR:V0=100]
[NO:I1] ───> [MB_WRITE:V0, Slave=3]
```

### Ejemplo 3: Monitoreo Distribuido
```
Rung 1: Leer estado de otro PLC (esclavo ID=2)
[TON:T1=500] ───> [MB_READ:MB1, Slave=2]

Rung 2: Si recibe alarma (MB1==1), activar sirena local
[MB_SLAVE:MB1=1] ───> [COIL:Q2]
```

### Diseño del HARDWARE:

[![Demo en YouTube](https://img.shields.io/badge/▶_Ver_Diseño_Hardware-YouTube-red)](https://www.youtube.com/watch?v=sfueLWmS17k)


**📖 Ver [MODBUS_GUIDE.md](MODBUS_GUIDE.md) para documentación completa**

## Soporte Técnico

ETI Patagonia - prof.martintorres@educ.ar

https://eti-patagonia-ar.github.io/ETI-Patagonia-ARG/
