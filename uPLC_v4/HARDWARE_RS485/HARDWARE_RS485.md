#==================================================================
# uPLC_v3/HARDWARE_RS485.md - ETI Patagonia - prof.martintorres@educ.ar
#==================================================================

# Guía de Instalación de Hardware RS485

Esta guía detalla cómo conectar correctamente el módulo RS485 al Arduino NANO para comunicación Modbus RTU.

## Módulos RS485 Compatibles

### MAX485 (Recomendado)
- Chip: Maxim MAX485
- Voltaje: 5V
- Velocidad: Hasta 2.5 Mbps
- Distancia: Hasta 1200m
- Costo: ~$1-2 USD

### Other Options:
- **XY-017**: MAX485 en PCB compacto
- **TTL to RS485**: Módulo con auto-dirección
- **MAX3485**: Versión mejorada con mejor protección ESD

## Esquema de Conexión

### Módulo MAX485 → Arduino NANO

```
┌─────────────────────────┐         ┌──────────────────────┐
│   Arduino NANO          │         │   Módulo MAX485      │
│                         │         │                      │
│  D10 (RX) ──────────────┼─────────┼──> RO (Receiver Out) │
│  D11 (TX) ──────────────┼─────────┼──> DI (Driver In)    │
│  D12 (opcional) ────────┼─────────┼──> DE (Driver Enable)│
│  D12 (opcional) ────────┼─────────┼──> RE (Rcv Enable)   │
│  GND ───────────────────┼─────────┼──> GND               │
│  5V ────────────────────┼─────────┼──> VCC               │
│                         │         │                      │
│                         │         │  A ─────────┐        │
│                         │         │  B ─────────┼────> Bus RS485
└─────────────────────────┘         └──────────────────────┘
```

### Notas sobre DE y RE:
1. **Conexión simplificada** (implementación actual):
   - DE y RE conectados juntos a GND o VCC
   - Modo siempre RX o siempre TX (half-duplex manual)
   - **Para uPLC v3: Conectar DE y RE a GND** (modo recepción por defecto)

2. **Conexión avanzada** (control automático):
   - DE y RE conectados a D12
   - Control por software de dirección (futuro)
   - Requiere modificación del código

## Esquema de Bus RS485

### Red Simple (2 dispositivos)

```
Master                    Slave
(Arduino 1)              (Arduino 2)
   │                        │
   │    A ←──────────────→ A
   │    B ←──────────────→ B
   │   GND ←────────────→ GND
   │                        │
  120Ω                    120Ω
  (R1)                    (R2)
```

**Resistencias de terminación (R1, R2):**
- Valor: 120Ω, 1/4W
- Ubicación: Solo en los extremos del bus
- Función: Eliminar reflexiones de señal

### Red con Múltiples Esclavos

```
Master          Slave1        Slave2        Slave3
(ID=1)          (ID=2)        (ID=3)        (ID=4)
   │               │             │             │
   │    A ←────────┼─────────────┼─────────────┤
   │    B ←────────┼─────────────┼─────────────┤
   │   GND ←───────┼─────────────┼─────────────┤
   │               │             │             │
  120Ω                                       120Ω
```

**Importante:**
- Distancia máxima: 1200m (sin repetidores)
- Máximo 32 dispositivos en el bus (con RS485 estándar)
- Usar cable par trenzado (twisted pair)
- Longitud de stubs (derivaciones) < 20cm

## Tipos de Cable

### Cable Recomendado: Par Trenzado (Twisted Pair)
```
Especificaciones:
- Impedancia: 120Ω
- Calibre: 22-24 AWG
- Trenzado: Mínimo 1 vuelta/cm
- Blindaje: Opcional (recomendado en ambientes ruidosos)
```

### Ejemplos de Cables:
1. **Cat5e/Cat6** (UTP): Funciona bien para distancias cortas (<50m)
2. **RS485 específico**: Mejor para aplicaciones industriales
3. **Cable telefónico**: Funciona pero no es ideal

### Identificación de Conductores:
```
Par trenzado típico:
  Cable A: Generalmente rojo, naranja o blanco
  Cable B: Generalmente negro, azul o verde
  GND:     Negro o malla de blindaje
```

## Polaridad RS485

### Conexión Correcta:
```
Device 1     →     Device 2
A (Data+)    ←──→  A (Data+)
B (Data-)    ←──→  B (Data-)
```

### ⚠️ Error Común: Polaridad Invertida
```
Device 1     →     Device 2
A (Data+)    ←──→  B (Data-)  ✗ INCORRECTO
B (Data-)    ←──→  A (Data+)  ✗ INCORRECTO
```

**Síntoma:** Comunicación errática o sin respuesta.

## Instalación Paso a Paso

### Paso 1: Preparar los Módulos
1. Soldar pines headers al módulo MAX485
2. Verificar conexiones con multímetro
3. Identificar pines A, B, GND, VCC, RO, DI, DE, RE

### Paso 2: Conectar al Arduino
```
MAX485        Arduino NANO
------        ------------
VCC     →     5V
GND     →     GND
RO      →     D10 (RX)
DI      →     D11 (TX)
DE      →     GND (o D12 si control automático)
RE      →     GND (o D12 si control automático)
```

### Paso 3: Instalar Resistencias de Terminación
```
En el PRIMER dispositivo del bus:
- Soldar resistencia 120Ω entre A y B

En el ÚLTIMO dispositivo del bus:
- Soldar resistencia 120Ω entre A y B
```

### Paso 4: Cablear el Bus
1. Usar cable par trenzado
2. Mantener cables lo más cortos posible
3. Evitar bucles o vueltas innecesarias
4. Conectar A con A, B con B en todos los dispositivos
5. Conectar GND común entre todos los dispositivos

### Paso 5: Verificar Instalación
1. Medir continuidad entre A de todos los dispositivos
2. Medir continuidad entre B de todos los dispositivos
3. Medir resistencia entre A y B (debe ser ~60Ω con terminaciones)
4. Verificar que no hay cortos entre A-GND o B-GND

## Prueba de Comunicación

### Test Básico con Serial Monitor

1. Cargar el sketch al Master
2. Cargar el sketch al Slave
3. Abrir Serial Monitor a 9600 bps
4. Observar mensajes de comunicación

### Comandos de Debug (agregar al código):

```cpp
void loop() {
  // ... código normal ...
  
  // Debug: Imprimir valor leído
  Serial.print("MB0: ");
  Serial.println(MB0);
  
  delay(100);
}
```

## Troubleshooting Hardware

### Sin Comunicación

#### Verificar:
1. **Alimentación**
   - VCC: 5V ± 0.25V
   - GND común entre todos los dispositivos

2. **Conexiones**
   - RO → D10 (SoftwareSerial RX)
   - DI → D11 (SoftwareSerial TX)
   - A conectado a todos los A
   - B conectado a todos los B

3. **Polaridad**
   - A debe ir a A (no a B)
   - B debe ir a B (no a A)

4. **Terminación**
   - 120Ω solo en los extremos
   - NO en dispositivos intermedios

### Comunicación Errática

#### Posibles Causas:
1. **Ruido electromagnético**
   - Alejar cables RS485 de cables de potencia
   - Usar cable blindado
   - Conectar blindaje a GND en un solo punto

2. **Cables muy largos**
   - Reducir velocidad a 9600 bps
   - Reducir longitud del cable
   - Usar repetidores RS485 si necesario

3. **Terminación incorrecta**
   - Verificar resistencias de 120Ω
   - Solo en los extremos del bus
   - NO en dispositivos intermedios

4. **Múltiples grounds**
   - Conectar GND común solo en un punto
   - Evitar loops de tierra

### Lecturas Incorrectas

#### Verificar:
1. **IDs de dispositivos**
   - Master: ID=1
   - Slaves: ID=2, 3, 4, etc. (únicos)

2. **Baudrate coincidente**
   - Todos los dispositivos a 9600 bps
   - Verificar cristal del Arduino (16 MHz)

3. **Timeout suficiente**
   - Aumentar delay entre lecturas
   - Mínimo 100ms entre transacciones

## Mediciones con Multímetro

### Voltajes Típicos

```
Modo Idle (sin transmisión):
  A: +2.5V a +5V
  B: 0V a +2.5V
  Diferencial (A-B): +2V a +3V

Modo Transmisión:
  A: Oscila entre 0V y 5V
  B: Oscila entre 0V y 5V
  Diferencial: Oscila entre -5V y +5V
```

### Resistencias

```
Entre A y B (sin terminación): >10kΩ
Entre A y B (con terminación en extremos): ~60Ω
Entre A y GND: >10kΩ
Entre B y GND: >10kΩ
```

## Mejoras Avanzadas

### 1. Control Automático DE/RE
Modificar código para controlar pin D12:
```cpp
#define DE_RE_PIN 12

void setup() {
  pinMode(DE_RE_PIN, OUTPUT);
  digitalWrite(DE_RE_PIN, LOW); // Modo RX por defecto
}

// Antes de transmitir
digitalWrite(DE_RE_PIN, HIGH);
delay(1);
// ... enviar datos ...
delay(1);
digitalWrite(DE_RE_PIN, LOW);
```

### 2. Indicador LED de Actividad
```cpp
#define LED_TX 13

void loop() {
  digitalWrite(LED_TX, HIGH);
  // ... transmitir ...
  digitalWrite(LED_TX, LOW);
}
```

### 3. Aislamiento Galvánico
Para ambientes industriales ruidosos:
- Usar módulos RS485 con aislamiento óptico
- Alimentación aislada para cada dispositivo
- Ejemplo: ADAM-4520 (aislador RS485)

## Herramientas Útiles

### Software:
- **Modbus Poll** (Windows): Simulador Master
- **Modbus Slave** (Windows): Simulador Slave
- **QModMaster** (Linux/Windows): Cliente Modbus gratuito

### Hardware:
- **Analizador USB-RS485**: Para debugging
- **Osciloscopio**: Para verificar señales
- **Multímetro**: Para verificar voltajes y resistencias

## Proveedores Recomendados

### Argentina:
- ElectroMercado: Módulos MAX485
- DigiKey Argentina: Componentes originales
- MercadoLibre: Módulos compatibles

### Internacional:
- AliExpress: Módulos económicos
- Mouser/DigiKey: Componentes originales
- Amazon: Envío rápido

## Referencias Técnicas

- [MAX485 Datasheet](https://datasheets.maximintegrated.com/en/ds/MAX1487-MAX491.pdf)
- [RS485 Application Note](https://www.ti.com/lit/an/slyt324/slyt324.pdf)
- [Modbus Protocol](https://www.modbus.org/docs/Modbus_Application_Protocol_V1_1b3.pdf)

## Contacto

ETI Patagonia - prof.martintorres@educ.ar
https://eti-patagonia-ar.github.io/ETI-Patagonia-ARG/
