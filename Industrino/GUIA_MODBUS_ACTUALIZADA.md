#==================================================================
# GUÍA COMPLETA DE MODBUS RS485 - uPLC v4
# ETI Patagonia - prof.martintorres@educ.ar
#==================================================================

# Guía de Uso de Modbus RS485 en uPLC v4

## 🎯 Qué es Modbus y Para Qué Sirve

Modbus RS485 permite que **varios Arduinos se comuniquen entre sí** a través de un cable de 2 hilos (A y B).

**Ejemplo práctico:**
- Arduino 1 (Master): Lee temperatura de un Arduino 2 y controla un ventilador
- Arduino 2 (Slave): Tiene un sensor de temperatura conectado
- Arduino 3 (Slave): Controla el ventilador basado en comandos del Master

## 📡 Hardware Necesario

### Conexiones en cada Arduino NANO

```
Arduino NANO    →    Módulo MAX485
──────────────────────────────────
D10 (RX)        →    RO (Receiver Out)
D11 (TX)        →    DI (Driver In)
D12 (DE/RE)     →    DE + RE (unidos)
5V              →    VCC
GND             →    GND
```

### Bus RS485 (conectar entre todos los dispositivos)

```
Master MAX485    →    Slave1 MAX485    →    Slave2 MAX485
     A          ─────→     A          ─────→     A
     B          ─────→     B          ─────→     B
    GND         ─────→    GND         ─────→    GND
     │                                             │
   120Ω                                          120Ω
  (solo en                                    (solo en
  extremos)                                   extremos)
```

**IMPORTANTE:** 
- Resistencias de 120Ω **SOLO en el primero y último dispositivo** del bus
- Cable par trenzado recomendado
- GND común entre todos los dispositivos

## 🔧 Roles: Master y Slave

### MASTER (Jefe)
- **Hace preguntas** a los Slaves
- **Envía comandos** a los Slaves
- **Controla** la comunicación
- **Solo puede haber UNO** en el bus

En uPLC v4, **tu Arduino es siempre el Master**.

### SLAVE (Empleado)
- **Responde** cuando el Master pregunta
- **Obedece** comandos del Master
- Tiene un **ID único** (2, 3, 4... hasta 10)
- **Puede haber VARIOS** en el bus

## 📊 Registros Modbus

### ¿Qué son?
Son "cajitas de memoria" donde se guardan números.

### Disponibles en uPLC v4
- **MB0, MB1, MB2... MB9** (10 registros)
- Cada uno guarda un número de **0 a 255**

### Ejemplo de uso
```
Arduino Master:
  MB0 = Temperatura leída del Slave 2
  MB1 = Humedad leída del Slave 3
  MB2 = Presión leída del Slave 4

Arduino Slave ID=2 (sensor):
  Su registro interno MB0 = 25 (temperatura actual)
```

## 🧩 Bloques Modbus en el Ladder

### 1. MB_SLAVE (Condición)

**¿Qué hace?** Pregunta: "¿El registro MB vale X?"

**Símbolo en el ladder:**
```
┌──────┐
│  MB  │
│  ==  │
│ MB0  │  ← Registro a comparar
│  50  │  ← Valor
└──────┘
```

**Configuración:**
- **Ref**: MB0 a MB9 (¿cuál registro verificar?)
- **Value**: 0 a 255 (¿con qué valor comparar?)

**Ejemplo:**
```
[MB_SLAVE:MB0=100] ──────> [COIL:Q1]
```
Se lee: "Si MB0 es igual a 100, entonces enciende Q1"

---

### 2. MB_READ (Salida - Leer de Slave)

**¿Qué hace?** Lee un dato de un Arduino Slave remoto.

**Símbolo en el ladder:**
```
┌────────┐
│   MB   │
│  READ  │
│  MB0   │  ← Dónde guardar lo leído
│  S:2   │  ← De qué Slave leer (ID=2)
└────────┘
```

**Configuración:**
- **Ref**: MB0 a MB9 (¿dónde guardar el dato leído?)
- **Value**: 1 a 10 (¿de qué Slave leer? = ID del Slave)

**Ejemplo:**
```
[TON:T0=1000] ──────> [MB_READ:MB0, Slave=2]
```
Se lee: "Cada 1 segundo, lee el registro del Slave ID=2 y guárdalo en MB0"

**Código generado (CORRECTO):**
```cpp
if (_r0) {
  // Leer registro 0 del Slave ID=2
  uint8_t result = modbus_slave2.readHoldingRegisters(0, 1);
  if (result == modbus_slave2.ku8MBSuccess) {
    MB0 = modbus_slave2.getResponseBuffer(0);
  }
}
```

---

### 3. MB_WRITE (Salida - Escribir a Slave)

**¿Qué hace?** Envía un comando/dato a un Arduino Slave remoto.

**Símbolo en el ladder:**
```
┌────────┐
│   MB   │
│  WRIT  │
│   V0   │  ← Qué dato enviar
│  S:3   │  ← A qué Slave (ID=3)
└────────┘
```

**Configuración:**
- **Ref**: MB0-MB9, V0-V9, o un número (¿qué enviar?)
- **Value**: 1 a 10 (¿a qué Slave enviar? = ID del Slave)

**Ejemplo:**
```
[NO:I1] ──────> [SET_VAR:V0=100]
[NO:I1] ──────> [MB_WRITE:V0, Slave=3]
```
Se lee: "Cuando I1 está activo, envía el valor de V0 (=100) al Slave ID=3"

**Código generado (CORRECTO):**
```cpp
if (_r1) {
  // Escribir en registro 0 del Slave ID=3
  modbus_slave3.writeSingleRegister(0, V0);
}
```

## 🔄 Cómo Funciona Internamente

### Generación Automática de Objetos

**El generador de uPLC v4 es inteligente:**

1. Analiza tu programa
2. Detecta qué Slave IDs usás (ej: 2, 3, 5)
3. Crea **automáticamente** un objeto `ModbusMaster` para cada uno

**Ejemplo:**

Si tu programa usa:
- MB_READ de Slave 2
- MB_WRITE a Slave 3

El código generado incluirá:

```cpp
// Objetos Modbus Master (uno por cada slave usado)
ModbusMaster modbus_slave2;  // Para comunicarse con Slave ID=2
ModbusMaster modbus_slave3;  // Para comunicarse con Slave ID=3

void setup() {
  // ...
  
  // Inicializar cada objeto con su slave ID
  modbus_slave2.begin(2, rs485Serial);
  modbus_slave2.preTransmission(preTransmission);
  modbus_slave2.postTransmission(postTransmission);
  
  modbus_slave3.begin(3, rs485Serial);
  modbus_slave3.preTransmission(preTransmission);
  modbus_slave3.postTransmission(postTransmission);
}
```

### Control DE/RE Automático

El pin D12 controla la dirección del bus RS485:
- **HIGH** = Modo transmisión (enviar datos)
- **LOW** = Modo recepción (esperar respuesta)

Esto se maneja **automáticamente** con callbacks:

```cpp
void preTransmission() {
  digitalWrite(RS485_DE_PIN, HIGH);  // Modo transmisión
}

void postTransmission() {
  digitalWrite(RS485_DE_PIN, LOW);   // Modo recepción
}
```

### API de ModbusMaster

La librería usa esta sintaxis (2 argumentos):

```cpp
// ✅ LEER registro (address, quantity)
uint8_t result = modbus_slaveN.readHoldingRegisters(0, 1);

// ✅ ESCRIBIR registro (address, value)
modbus_slaveN.writeSingleRegister(0, valor);
```

**El slave ID ya está en el objeto, por eso no se pasa como parámetro.**

## 📋 Ejemplos Prácticos

### Ejemplo 1: Leer Temperatura Remota

**Objetivo:** Leer temperatura de un sensor remoto cada segundo.

**Hardware:**
- Master: Tu Arduino con uPLC v4
- Slave ID=2: Arduino con sensor de temperatura

**Programa Master (ladder):**

```
┌─────────────────────────────────────────────────────┐
│ // Rung 1: Timer de 1 segundo                       │
│ [TON:T0=1000] ──────> [TON:T0=1000]                 │
│                                                      │
│ // Rung 2: Cuando timer termina, leer temperatura  │
│ [T0] ──────> [MB_READ:MB0, Slave=2]                 │
│                                                      │
│ // Rung 3: Si hace calor, ventilador               │
│ [MB0 > 30] ──────> [COIL:Q1]                        │
└─────────────────────────────────────────────────────┘
```

**Qué hace:**
1. Timer T0 se repite cada 1000ms
2. Cuando termina, lee del Slave 2 y guarda en MB0
3. Si MB0 > 30, enciende ventilador Q1

---

### Ejemplo 2: Enviar Comando a Actuador

**Objetivo:** Controlar una válvula remota con un botón.

**Hardware:**
- Master: Tu Arduino
- Slave ID=3: Arduino con relé para válvula

**Programa Master (ladder):**

```
┌─────────────────────────────────────────────────────┐
│ // Rung 1: Si botón, abrir válvula                  │
│ [NO:I1] ──────> [SET_VAR:V0=1]                      │
│                                                      │
│ // Rung 2: Enviar comando al Slave                 │
│ [NO:I1] ──────> [MB_WRITE:V0, Slave=3]              │
│                                                      │
│ // Rung 3: Si no hay botón, cerrar válvula         │
│ [NC:I1] ──────> [SET_VAR:V0=0]                      │
│                                                      │
│ // Rung 4: Enviar comando de cerrar                │
│ [NC:I1] ──────> [MB_WRITE:V0, Slave=3]              │
└─────────────────────────────────────────────────────┘
```

**Qué hace:**
1. Si I1 activo → V0=1 → Enviar 1 al Slave 3 (abrir)
2. Si I1 inactivo → V0=0 → Enviar 0 al Slave 3 (cerrar)

---

### Ejemplo 3: Sistema Multizona

**Objetivo:** Leer temperaturas de 3 zonas y controlar ventilación general.

**Hardware:**
- Master: Tu Arduino
- Slave 2: Sensor zona 1
- Slave 3: Sensor zona 2
- Slave 4: Sensor zona 3

**Programa Master (ladder):**

```
┌─────────────────────────────────────────────────────┐
│ // Rung 1: Leer todas las zonas cada 500ms         │
│ [TON:T0=500] ──────> [TON:T0=500]                   │
│                                                      │
│ // Rung 2: Leer zona 1                             │
│ [T0] ──────> [MB_READ:MB0, Slave=2]                 │
│                                                      │
│ // Rung 3: Leer zona 2                             │
│ [T0] ──────> [MB_READ:MB1, Slave=3]                 │
│                                                      │
│ // Rung 4: Leer zona 3                             │
│ [T0] ──────> [MB_READ:MB2, Slave=4]                 │
│                                                      │
│ // Rung 5: Ventilador si CUALQUIER zona > 28°C     │
│ [MB0 > 28] ──────────────────> [COIL:Q1]            │
│                                                      │
│ [MB1 > 28] ──────────────────> ╯                    │
│                                                      │
│ [MB2 > 28] ──────────────────> ╯                    │
└─────────────────────────────────────────────────────┘
```

## 🛠️ Programación del Slave

El Slave debe ser programado por separado con código Arduino tradicional.

**Ejemplo de código Slave (Arduino IDE):**

```cpp
#include <ModbusRTUSlave.h>

#define SLAVE_ID 2
#define RS485_DE_PIN 12

uint16_t modbusRegs[10];  // Registros Modbus

ModbusRTUSlave modbus(Serial1, RS485_DE_PIN);

void setup() {
  pinMode(RS485_DE_PIN, OUTPUT);
  pinMode(A6, INPUT);  // Sensor temperatura
  
  Serial1.begin(9600);
  modbus.begin(SLAVE_ID, 9600);
  modbus.configureHoldingRegisters(modbusRegs, 10);
}

void loop() {
  // Leer sensor y actualizar registro 0
  int temp = analogRead(A6);
  modbusRegs[0] = map(temp, 0, 1023, 0, 100);  // 0-100°C
  
  // Procesar comunicación Modbus
  modbus.poll();
  
  delay(50);
}
```

**Librería Slave requerida:**
- ModbusRTUSlave by CMB-solutions
- https://github.com/CMB27/ModbusRTUSlave

## 📚 Librerías Necesarias

### Para el MASTER (uPLC v4):

**ModbusMaster by 4-20ma (Doc Walker)**

Instalación:
```
Arduino IDE > Tools > Manage Libraries > Buscar "ModbusMaster"
Instalar: ModbusMaster by Doc Walker
```

O desde: https://github.com/4-20ma/ModbusMaster

### Para los SLAVES:

**ModbusRTUSlave by CMB-solutions**

Desde: https://github.com/CMB27/ModbusRTUSlave

## ⚠️ Troubleshooting

### 1. Error de compilación: "ModbusMaster.h: No such file"

**Solución:** Instalar librería ModbusMaster desde Library Manager.

### 2. No hay comunicación

**Verificar:**
- ✅ Cableado A-A, B-B entre todos los dispositivos
- ✅ GND común
- ✅ Resistencias 120Ω en los extremos
- ✅ IDs de slaves correctos y únicos
- ✅ Baudrate 9600 en todos

### 3. Lecturas erráticas

**Soluciones:**
- Usar cable par trenzado
- Verificar polaridad (A con A, B con B)
- Reducir longitud del cable
- Agregar resistencias de terminación
- Separar de fuentes de ruido eléctrico

### 4. Timeout constante

**Verificar:**
- Slave está alimentado y funcionando
- Slave está ejecutando código correcto
- Slave tiene el ID configurado correctamente
- No hay conflicto de IDs (dos slaves con mismo ID)

### 5. Solo funciona con un slave

**Causa probable:** Todos los slaves tienen el mismo ID.

**Solución:** Cada slave debe tener un ID ÚNICO (2, 3, 4...).

## 🎓 Tips y Buenas Prácticas

### 1. Timing
- No leas Modbus cada ciclo (muy rápido)
- Usa timers: cada 100-1000ms es suficiente
- Ejemplo: `[TON:T0=500] → [MB_READ:MB0, Slave=2]`

### 2. Orden de Comunicación
```
1. Leer todos los slaves
2. Procesar lógica
3. Escribir comandos a slaves
```

### 3. Manejo de Errores
- Si un slave no responde, el registro no se actualiza
- Usar la última lectura válida
- Considerar timeout como falla

### 4. Documentación
- Anotar qué Slave tiene qué ID
- Documentar qué representa cada registro
- Ejemplo:
  ```
  Slave 2 = Sensor temperatura sala principal
  Slave 3 = Controlador ventilador
  Slave 4 = Sensor humedad
  ```

### 5. Testing
1. Probar cada Slave por separado primero
2. Verificar con multímetro las señales RS485
3. Usar Serial Monitor para debug
4. Agregar LEDs indicadores de actividad

## 📖 Recursos Adicionales

- **EJEMPLO_MODBUS.md** - Sistema completo paso a paso
- **HARDWARE_RS485.md** - Instalación física detallada
- **Modbus_Master_Temperatura/** - Ejemplo funcional completo
- **BUG_MODBUS_CORREGIDO.txt** - Explicación técnica de la API

## 📞 Contacto

ETI Patagonia
prof.martintorres@educ.ar
https://eti-patagonia-ar.github.io/ETI-Patagonia-ARG/

═══════════════════════════════════════════════════════════════════
