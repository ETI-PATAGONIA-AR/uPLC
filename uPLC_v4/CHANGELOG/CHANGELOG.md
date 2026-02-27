#==================================================================
# uPLC_v3/CHANGELOG.md - ETI Patagonia - prof.martintorres@educ.ar
#==================================================================

# Registro de Cambios - uPLC v3

## v3.1 - Modbus RS485 y Expansión de Salidas (2025-02-26)

### ✨ Nuevas Características

#### Comunicación Modbus RS485
- **Soporte completo para Modbus RTU**
  - Implementación usando SoftwareSerial en pines D10 (RX) y D11 (TX)
  - Librería ModbusMaster de Doc Walker integrada
  - Funciona como Modbus Master (ID=1)
  - Soporta lectura y escritura de registros

- **Nuevos bloques Modbus en el Ladder**
  - `MB_SLAVE`: Condición que evalúa el valor de un registro Modbus local
  - `MB_READ`: Lee un registro Holding (función 03) desde un dispositivo esclavo
  - `MB_WRITE`: Escribe un registro Single (función 06) a un dispositivo esclavo

- **10 Registros Modbus locales (MB0-MB9)**
  - Tipo: uint16_t (0-65535)
  - Pueden usarse como condiciones o valores
  - Se actualizan mediante comunicación RS485

#### Expansión de Salidas Digitales
- **2 nuevas salidas digitales**
  - Q6 en D12
  - Q7 en D13
  - Total: 7 salidas digitales (Q1-Q7)

#### Mejoras en el Display LCD
- Ahora muestra todas las 7 salidas (Q1-Q7)
- Formato mejorado con duty cycle PWM de 2 dígitos (00-99%)
- Visualización más clara de estados

### 🔧 Cambios Técnicos

#### Archivos Modificados

1. **config/pins.py**
   - Agregado `RS485_PINS` con configuración RX/TX
   - Agregadas salidas Q6 (D12) y Q7 (D13)

2. **config/constants.py**
   - Agregados tool IDs: `MB_READ`, `MB_WRITE`, `MB_SLAVE`
   - Actualizado `_OUTPUTS` para incluir Q5, Q6, Q7
   - Agregado `_MODBUS` con registros MB0-MB9
   - Nueva categoría en toolbox: "Modbus RS485"
   - Actualizado `VALID_REFS` para soportar registros Modbus
   - Agregado `_SLAVE_IDS` para IDs de esclavos (1-10)

3. **generator/sketch_builder.py**
   - Agregado import de `MB_READ`, `MB_WRITE`, `MB_SLAVE`
   - Actualizada función `_cond_expr()` para soportar `MB_SLAVE`
   - Agregadas librerías `#include <SoftwareSerial.h>` y `#include <ModbusMaster.h>`
   - Inicialización de RS485/Modbus en `setup()`
   - Nuevas variables globales: registros Modbus (MB0-MB9)
   - Actualizado estado de salidas: Q6 y Q7
   - Implementada lógica para `MB_READ` y `MB_WRITE`
   - Actualizada escritura de salidas para Q6 y Q7
   - Mejorado display LCD para mostrar 7 salidas

4. **assets/icons/Fun_MB.png**
   - Nuevo icono para bloques Modbus (temporal, basado en Fun_varMAP.png)

### 📚 Documentación Nueva

1. **MODBUS_GUIDE.md**
   - Guía completa de uso de Modbus RS485
   - Explicación del formato de frames Modbus
   - Ejemplos prácticos de aplicación
   - Sección de troubleshooting
   - Referencias y recursos adicionales

2. **README.md actualizado**
   - Sección de novedades v3.1
   - Pinout actualizado con RS485 y nuevas salidas
   - Ejemplos de uso de Modbus
   - Instrucciones de instalación de ModbusMaster
   - Formato actualizado del Display LCD

### 🔌 Nuevo Pinout Completo

```
Entradas Digitales:
  I1 → D2,  I2 → D4,  I3 → D5,  I4 → D6
  I5 → D7,  I6 → D8,  I7 → D9

Salidas Digitales:
  Q1 → D14 (A0)    Q2 → D15 (A1)
  Q3 → D16 (A2)    Q4 → D17 (A3)
  Q5 → D3  (PWM)   Q6 → D12
  Q7 → D13

Comunicación RS485:
  RX → D10         TX → D11

Entradas Analógicas:
  A0 → A6          A1 → A7

Display LCD I2C:
  SDA → A4         SCL → A5
```

### 📦 Dependencias Nuevas

**Arduino IDE:**
- ModbusMaster by Doc Walker (https://github.com/4-20ma/ModbusMaster)

**Python:** (sin cambios)
- PyQt5>=5.15
- Pillow>=10.0
- pyserial>=3.5

### 🎯 Casos de Uso

1. **Monitoreo de sensores remotos**
   - Leer sensores Modbus (temperatura, presión, etc.)
   - Almacenar valores en registros MB0-MB9
   - Tomar decisiones basadas en valores leídos

2. **Control de actuadores remotos**
   - Enviar comandos a válvulas, motores, etc.
   - Sincronización entre múltiples PLCs
   - Control distribuido

3. **Integración industrial**
   - Compatible con cualquier dispositivo Modbus RTU
   - Comunicación estándar de la industria
   - Protocolo probado y confiable

### ⚠️ Notas de Compatibilidad

- **Retrocompatible**: Los proyectos v3.0 funcionarán en v3.1
- **Hardware**: Requiere módulo RS485 para comunicación Modbus
- **Baudrate**: Por defecto 9600 bps (modificable en código)
- **IDs de esclavos**: Soporta dispositivos con ID 1-10

### 🐛 Issues Conocidos

- El icono Fun_MB.png es temporal (copia de Fun_varMAP.png)
- Los registros Modbus son de 16 bits pero se mapean a 8 bits para compatibilidad
- El timeout de Modbus puede causar delays en el loop() si el esclavo no responde

### 🚀 Próximas Mejoras Sugeridas

- [ ] Agregar modo Modbus Slave
- [ ] Soportar más funciones Modbus (04, 05, 15, 16)
- [ ] Crear iconos específicos para bloques Modbus
- [ ] Agregar configuración de baudrate en la interfaz
- [ ] Implementar timeout configurable
- [ ] Agregar soporte para múltiples esclavos en un solo rung

---

## v3.0 - Primera Versión Estable (2025-02-25)

### ✅ Correcciones de Bugs
1. PWM corregido: Ahora genera correctamente `analogWrite(pin, valor)`
2. SET_VAR con ADC: Auto-asignación de referencia ADC cuando no hay valor explícito
3. AND/OR: Funcionamiento correcto de junctions

### ✨ Nuevas Funcionalidades
1. Creación automática de carpetas por proyecto
2. Generación de archivos `.uplc` y `.ino`
3. Soporte para Display LCD I2C 20x4
   - Dirección I2C: 0x27
   - Visualización de entradas, salidas y analógicos
   - Duty cycle del PWM

### 📦 Estructura del Proyecto
```
uPLC_v3/
  ├── config/
  │   ├── constants.py
  │   └── pins.py
  ├── core/
  │   └── model.py
  ├── generator/
  │   └── sketch_builder.py
  ├── gui/
  │   ├── canvas.py
  │   ├── main_window.py
  │   ├── sketch_dialog.py
  │   └── toolbox.py
  ├── project/
  │   └── project_io.py
  ├── assets/
  │   └── icons/
  ├── ejemplos/
  ├── main.py
  ├── requirements.txt
  └── run_uPLCv3.bat
```

---

## Contacto

ETI Patagonia - prof.martintorres@educ.ar
https://eti-patagonia-ar.github.io/ETI-Patagonia-ARG/
