#==================================================================
# uPLC_v3/EJEMPLO_MODBUS.md - ETI Patagonia - prof.martintorres@educ.ar
#==================================================================

# Ejemplo Completo: Sistema de Control de Temperatura Distribuido

Este ejemplo muestra cómo usar Modbus RS485 para crear un sistema de control de temperatura distribuido con dos Arduino NANO.

## Arquitectura del Sistema

```
┌─────────────────────────────────────────────────────────────┐
│                                                             │
│  ARDUINO MASTER (ID=1)                                      │
│  ┌─────────────────────────────────────────────────────┐   │
│  │ • Lee temperatura del Slave cada 500ms               │   │
│  │ • Controla salida de calefacción local (Q1)         │   │
│  │ • Controla salida de enfriamiento remoto (Q2→Slave) │   │
│  │ • Monitorea alarma remota (MB1)                     │   │
│  └─────────────────────────────────────────────────────┘   │
│                          RS485                              │
│                           │                                 │
│  ┌─────────────────────────────────────────────────────┐   │
│  │ ARDUINO SLAVE (ID=2)                                │   │
│  │ • Mide temperatura local con sensor analógico       │   │
│  │ • Responde a solicitudes Modbus                     │   │
│  │ • Controla ventilador de enfriamiento               │   │
│  │ • Envía alarma si temperatura > 90°C                │   │
│  └─────────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────┘
```

## Hardware Requerido

### Para cada Arduino NANO:
- 1x Arduino NANO
- 1x Módulo RS485 (MAX485 o similar)
- 1x Display LCD I2C 20x4
- 1x Sensor de temperatura analógico (LM35, TMP36, etc.)
- 1x Relé 5V (para Q1)
- Resistencias, cables, breadboard

### Conexiones RS485:
```
Master Arduino:           Módulo RS485:          Slave Arduino:
D10 (RX) ────────────┐    
D11 (TX) ────────────┼──> DI/RO              
GND ─────────────────┼──> GND                 
5V ──────────────────┼──> VCC                 
                     │
                     └──> A/B Bus (cable par trenzado) ──> Módulo RS485 Slave
```

## Programa MASTER (uPLC v3)

### Rung 1: Leer temperatura del Slave cada 500ms
```
Diagrama Ladder:
[TON:T0=500] ───────> [MB_READ:MB0, Slave=2]

Explicación:
- Timer T0 ejecuta cada 500ms
- Lee registro 0 del esclavo ID=2
- Guarda el valor en MB0 (temperatura remota en °C)
```

### Rung 2: Controlar calefacción local
```
Diagrama Ladder:
[CMP_LT:MB0<20] ───────> [COIL:Q1]

Explicación:
- Si temperatura remota < 20°C
- Activa calefacción local (Q1)
```

### Rung 3: Enviar comando de enfriamiento al Slave
```
Diagrama Ladder:
[CMP_GT:MB0>30] ───────> [SET_VAR:V0=1]
                ───────> [MB_WRITE:V0, Slave=2]

Explicación:
- Si temperatura remota > 30°C
- Envía comando 1 al Slave
- El Slave activa su ventilador
```

### Rung 4: Apagar enfriamiento remoto
```
Diagrama Ladder:
[CMP_LT:MB0<28] ───────> [SET_VAR:V0=0]
                ───────> [MB_WRITE:V0, Slave=2]

Explicación:
- Si temperatura remota < 28°C (histéresis)
- Envía comando 0 al Slave
- El Slave apaga su ventilador
```

### Rung 5: Leer estado de alarma remota
```
Diagrama Ladder:
[TON:T1=1000] ───────> [MB_READ:MB1, Slave=2]

Explicación:
- Cada 1 segundo
- Lee registro 1 del Slave (estado de alarma)
```

### Rung 6: Indicar alarma remota
```
Diagrama Ladder:
[MB_SLAVE:MB1=1] ───────> [COIL:Q2]

Explicación:
- Si MB1 == 1 (alarma activa)
- Enciende LED/sirena local (Q2)
```

## Código Arduino SLAVE (Complemento)

El Slave debe programarse con un sketch que:
1. Lee sensor de temperatura analógico
2. Responde a solicitudes Modbus Read Holding Register (función 03)
3. Acepta comandos Modbus Write Single Register (función 06)
4. Controla ventilador según comando recibido

### Sketch Arduino SLAVE (ejemplo básico)

```cpp
//==================================================================
// Sistema Slave - Sensor de Temperatura con Modbus
// ETI Patagonia - prof.martintorres@educ.ar
//==================================================================

#include <ModbusRtu.h>  // Librería Modbus Slave

// Configuración Modbus
#define SLAVE_ID 2
Modbus slave(SLAVE_ID, 0, 0); // ID=2, RS485, pin DE (no usado)

// Pines
#define TEMP_SENSOR A6  // Sensor de temperatura
#define FAN_OUTPUT  12  // Ventilador (Q1)

// Registros Modbus
uint16_t modbusRegs[10]; // MB0-MB9

void setup() {
  pinMode(FAN_OUTPUT, OUTPUT);
  
  // Inicializar Modbus Slave a 9600 bps
  slave.begin(9600);
  
  // Configurar timer para muestreo
  // (actualizar cada 100ms)
}

void loop() {
  // Leer temperatura (LM35: 10mV/°C)
  int rawTemp = analogRead(TEMP_SENSOR);
  int tempC = map(rawTemp, 0, 1023, 0, 100);
  
  // Actualizar registro MB0 con temperatura
  modbusRegs[0] = tempC;
  
  // Actualizar registro MB1 con estado de alarma
  modbusRegs[1] = (tempC > 90) ? 1 : 0;
  
  // Controlar ventilador según MB2 (comando del Master)
  if (modbusRegs[2] == 1) {
    digitalWrite(FAN_OUTPUT, HIGH);
  } else {
    digitalWrite(FAN_OUTPUT, LOW);
  }
  
  // Procesar comunicación Modbus
  slave.poll(modbusRegs, 10);
  
  delay(100);
}
```

## Formato de Registros Modbus

### MASTER → SLAVE:
```
Registro MB2 (dirección 2):
  0 = Apagar ventilador
  1 = Encender ventilador
```

### SLAVE → MASTER:
```
Registro MB0 (dirección 0):
  Temperatura en °C (0-100)

Registro MB1 (dirección 1):
  0 = Normal
  1 = Alarma (temperatura > 90°C)
```

## Monitoreo en Display LCD

### MASTER:
```
I1 2 3 4 5 6 7 A0000
 0 0 0 0 0 0 0 A1000
Q1 2 3 4 5 6 7 PWM00
 1 1 0 0 0 0 0

Q1 = 1: Calefacción ON
Q2 = 1: Alarma remota activa
```

### SLAVE:
```
I1 2 3 4 5 6 7 A0078
 0 0 0 0 0 0 0 A1000
Q1 2 3 4 5 6 7 PWM00
 1 0 0 0 0 0 0

A0 = 78: Temperatura local 78°C
Q1 = 1: Ventilador ON (comando remoto)
```

## Troubleshooting

### El Master no puede leer del Slave
1. Verificar conexiones RS485 (A-A, B-B, GND común)
2. Verificar IDs: Master=1, Slave=2
3. Verificar baudrate coincidente (9600)
4. Verificar que el Slave está correctamente alimentado
5. Agregar resistencia de terminación (120Ω) en los extremos del bus

### Lecturas erráticas
1. Usar cable par trenzado para RS485
2. Mantener cable corto (<100m sin repetidor)
3. Alejar cable RS485 de fuentes de ruido (motores, relés)
4. Verificar conexión de GND común entre dispositivos

### Timeout en comunicación
1. Aumentar delay entre lecturas (de 500ms a 1000ms)
2. Verificar que el Slave responde correctamente
3. Reducir número de lecturas por ciclo

## Extensiones del Sistema

### Agregar más Slaves:
- Slave ID=3: Monitoreo de humedad
- Slave ID=4: Control de iluminación
- Slave ID=5: Medición de consumo eléctrico

### Agregar más funciones:
- Control PID de temperatura
- Registro de datos históricos en SD
- Envío de datos a servidor web
- Control remoto por WiFi/Ethernet

## Referencias

- [ModbusRtu Library](https://github.com/smarmengol/Modbus-Master-Slave-for-Arduino)
- [Modbus Protocol](https://www.modbus.org/)
- [RS485 Tutorial](https://www.ti.com/lit/an/slyt324/slyt324.pdf)

## Contacto

ETI Patagonia - prof.martintorres@educ.ar
https://eti-patagonia-ar.github.io/ETI-Patagonia-ARG/
