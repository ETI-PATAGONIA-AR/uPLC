#==================================================================
# uPLC_v3/MODBUS_GUIDE.md - ETI Patagonia - prof.martintorres@educ.ar
#==================================================================

# Guía de uso de Modbus RS485 en uPLC v3

## Descripción General

El uPLC v3 ahora incluye soporte completo para comunicación Modbus RTU sobre RS485, permitiendo comunicación con otros dispositivos industriales como PLCs, sensores, y actuadores compatibles con Modbus.

## Hardware

### Conexiones RS485
- **RX** → D10 (SoftwareSerial)
- **TX** → D11 (SoftwareSerial)

### Nuevas Salidas
- **Q6** → D12 (salida digital)
- **Q7** → D13 (salida digital)

## Configuración del Sistema

El Arduino NANO funciona como **Modbus Master** por defecto con ID=1.

### Registros Modbus Disponibles

El sistema incluye 10 registros Modbus locales (MB0-MB9) que pueden ser:
- **Leídos** desde dispositivos esclavos
- **Escritos** hacia dispositivos esclavos
- **Usados como condiciones** en la lógica ladder (MB_SLAVE)

## Bloques Modbus en el Ladder

### 1. MB_SLAVE (Condición)
**Descripción**: Evalúa el valor de un registro Modbus local.

**Uso**: 
- **Ref**: MB0 a MB9 (registro a evaluar)
- **Value**: Valor de comparación (0-255)

**Ejemplo**: Si MB0 == 100, entonces activar Q1

```
[MB_SLAVE:MB0=100] ────────> [COIL:Q1]
```

### 2. MB_READ (Salida)
**Descripción**: Lee un registro Holding (función 03) desde un dispositivo esclavo.

**Uso**:
- **Ref**: MB0 a MB9 (registro local donde guardar el valor leído)
- **Value**: ID del dispositivo esclavo (1-10)

**Ejemplo**: Leer registro del esclavo ID=2 y guardarlo en MB0

```
[NO:I1] ────────> [MB_READ:MB0, Slave=2]
```

### 3. MB_WRITE (Salida)
**Descripción**: Escribe un registro Single (función 06) a un dispositivo esclavo.

**Uso**:
- **Ref**: MB0 a MB9, V0 a V9, o valor constante (dato a enviar)
- **Value**: ID del dispositivo esclavo (1-10)

**Ejemplo**: Escribir el valor de V5 al esclavo ID=3

```
[NO:I2] ────────> [MB_WRITE:V5, Slave=3]
```

## Formato del Frame Modbus

### Lectura (Request):
```
Byte 1: ID Esclavo     (ej: 01)
Byte 2: Función        (03 = Read Holding Registers)
Byte 3: Dirección (H)  (00)
Byte 4: Dirección (L)  (00)
Byte 5: Cantidad (H)   (00)
Byte 6: Cantidad (L)   (01)
Byte 7: CRC (L)        (calculado)
Byte 8: CRC (H)        (calculado)
```

### Respuesta (Response):
```
Byte 1: ID Esclavo     (01)
Byte 2: Función        (03)
Byte 3: Cantidad Bytes (02)
Byte 4: Dato (H)       (00)
Byte 5: Dato (L)       (FA = 250 decimal)
Byte 6: CRC (L)        (39)
Byte 7: CRC (H)        (93)
```

## Ejemplos de Aplicación

### Ejemplo 1: Leer sensor de temperatura remoto
```
Rung 1: Leer temperatura cada 1 segundo
[TON:T0=1000] ───> [MB_READ:MB0, Slave=5]

Rung 2: Si temperatura > 80°C, activar alarma
[MB_SLAVE:MB0] [CMP_GT:MB0>80] ───> [COIL:Q1]
```

### Ejemplo 2: Controlar válvula remota
```
Rung 1: Si nivel alto, cerrar válvula remota
[NO:I1] ───> [SET_VAR:V0=1]
[NO:I1] ───> [MB_WRITE:V0, Slave=3]

Rung 2: Si nivel bajo, abrir válvula remota
[NC:I1] ───> [SET_VAR:V0=0]
[NC:I1] ───> [MB_WRITE:V0, Slave=3]
```

### Ejemplo 3: Sincronización entre PLCs
```
Rung 1: Enviar estado de proceso al PLC principal
[NO:M0] ───> [MB_WRITE:M0, Slave=1]

Rung 2: Recibir comandos del PLC principal
[TON:T1=500] ───> [MB_READ:MB1, Slave=1]
[MB_SLAVE:MB1=1] ───> [COIL:Q2]
```

## Librería Requerida

La librería **ModbusMaster** de Doc Walker debe estar instalada en el Arduino IDE:

```
Sketch > Include Library > Manage Libraries > Buscar "ModbusMaster"
```

O instalar manualmente desde:
https://github.com/4-20ma/ModbusMaster

## Notas Importantes

1. **CRC Automático**: La librería ModbusMaster calcula automáticamente el CRC.
2. **Timeout**: Si un esclavo no responde, el registro local no se actualiza.
3. **Baudrate**: Por defecto 9600 bps, modificar en setup() si es necesario.
4. **Direccionamiento**: Los registros Modbus comienzan en dirección 0.
5. **Valores**: Los registros MB son de 16 bits (0-65535), pero se mapean a 8 bits (0-255) para compatibilidad con Variables V.

## Troubleshooting

### El esclavo no responde
- Verificar cableado RS485 (A, B, GND)
- Verificar que el ID del esclavo es correcto
- Verificar baudrate coincidente
- Verificar resistencia de terminación en el bus RS485

### Lecturas incorrectas
- Verificar polaridad del bus RS485
- Reducir longitud del cable o agregar terminación
- Verificar que no hay interferencia electromagnética

### Display muestra valores erróneos
- Los registros MB se actualizan solo cuando hay comunicación exitosa
- Verificar en Serial Monitor (9600 bps) los mensajes de debug

## Recursos Adicionales

- [Protocolo Modbus RTU](https://www.modbustools.com/modbus.html)
- [ModbusMaster Library](https://github.com/4-20ma/ModbusMaster)
- [RS485 Basics](https://www.ti.com/lit/an/slyt324/slyt324.pdf)
