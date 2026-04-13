# 22 - ENTRADAS/SALIDAS CON PULLUP

## 1. ¿Qué hace?
Demuestra el uso de resistencias pull-up internas.
Cada entrada togglea una salida inversa.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- 6 botones
- 6 LEDs (opcional)

## 3. Conexiones de hardware

```
ENTRADAS (con PULLUP interno):
- D2 (I1) → Botón 1 → GND
- D4 (I2) → Botón 2 → GND
- D6 (I3) → Botón 3 → GND
- D8 (I4) → Botón 4 → GND
- D10 (I5) → Botón 5 → GND
- D12 (I6) → Botón 6 → GND

SALIDAS:
- D3 (Q1) → LED o carga
- D5 (Q2) → LED o carga
- D7 (Q3) → LED o carga
- D9 (Q4) → LED o carga
- D11 (Q5) → LED o carga
- D13 (Q6) → LED integrado

LCD I2C:
- A4 (SDA) y A5 (SCL)

NOTA: No necesita resistencias externas gracias a INPUT_PULLUP.
```

## 4. ¿Cómo funciona?

```
// AL INICIAR
AL INICIAR:
  // Configurar entradas con PULLUP interno
  pinMode(D2, INPUT_PULLUP)   // Sin resistencia externa
  pinMode(D4, INPUT_PULLUP)
  pinMode(D6, INPUT_PULLUP)
  pinMode(D8, INPUT_PULLUP)
  pinMode(D10, INPUT_PULLUP)
  pinMode(D12, INPUT_PULLUP)
  
  // Configurar salidas
  pinMode(D3, OUTPUT)
  pinMode(D5, OUTPUT)
  pinMode(D7, OUTPUT)
  pinMode(D9, OUTPUT)
  pinMode(D11, OUTPUT)
  pinMode(D13, OUTPUT)
  
  LCD → "ENTRADAS/SALIDAS"
  LCD → "Modo: PULLUP"
  LCD → "Presion=LOW(SALE)"
  LCD → "Suelta=HIGH(ENTRA)"
  ESPERAR 2000 ms
  LCD CLEAR

// PARA SIEMPRE
PARA SIEMPRE:
  
  // Mostrar entradas (1=presionado, 0=suelto)
  LCD fila 0 → "E:"
  LCD → (D2==LOW?"1":"0")
  LCD → (D4==LOW?"1":"0")
  LCD → (D6==LOW?"1":"0")
  LCD → (D8==LOW?"1":"0")
  LCD → (D10==LOW?"1":"0")
  LCD → (D12==LOW?"1":"0")
  
  // Mostrar salidas
  LCD fila 1 → "S:"
  LCD → (D3==HIGH?"1":"0")
  LCD → (D5==HIGH?"1":"0")
  LCD → (D7==HIGH?"1":"0")
  LCD → (D9==HIGH?"1":"0")
  LCD → (D11==HIGH?"1":"0")
  LCD → (D13==HIGH?"1":"0")
  
  // Nombres
  LCD fila 2 → "I1  I2  I3  I4  I5  I6"
  LCD fila 3 → "Q1  Q2  Q3  Q4  Q5  Q6"
  
  // Lógica: entrada presionada → salida ON
  ESCRIBIR_DIGITAL(D3, (D2==LOW)?HIGH:LOW)
  ESCRIBIR_DIGITAL(D5, (D4==LOW)?HIGH:LOW)
  ESCRIBIR_DIGITAL(D7, (D6==LOW)?HIGH:LOW)
  ESCRIBIR_DIGITAL(D9, (D8==LOW)?HIGH:LOW)
  ESCRIBIR_DIGITAL(D11, (D10==LOW)?HIGH:LOW)
  ESCRIBIR_DIGITAL(D13, (D12==LOW)?HIGH:LOW)
```

## 5. Bloques utilizados

```
CATEGORÍA: CONFIGURACIÓN
- pinMode(PIN, INPUT_PULLUP) → Habilitar pull-up interno

CATEGORÍA: ENTRADAS
- LEER_DIGITAL → Leer pines de entrada

CATEGORÍA: SALIDAS
- ESCRIBIR_DIGITAL → Controlar LEDs/salidas

CATEGORÍA: LÓGICA
- OPERADOR TERNARIO → (cond?a:b)
- COMPARAR → ==LOW, ==HIGH

CATEGORÍA: LCD
- LCD TEXTO → Mostrar estados
```

## 6. Valores de referencia

```
PULLUP INTERNO:
- Arduino tiene resistencias pull-up de ~20-50KΩ
- Se activan con pinMode(PIN, INPUT_PULLUP)
- Estado natural: HIGH (sin presionar)
- Al presionar: LOW

VENTAJAS:
- Ahorra componentes externos
- Conexión más simple
- Menos cableado

LÓGICA:
- Botón presionado = LOW
- Botón suelto = HIGH
- Salida = inverso de entrada
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Cambiar lógica (presionado = ON)
- Quitar LEDs y ver solo LCD

NIVEL INTERMEDIO:
- Cada botón enciende/apaga toggle
- Contador de pulsaciones

NIVEL AVANZADO:
- Combinación de botones para activar salida
- Código de seguridad
```

## 8. Tips de debug

```
PROBLEMA: Entrada siempre en 1
SOLUCIÓN: Verificar pinMode con INPUT_PULLUP

PROBLEMA: Entrada siempre en 0
SOLUCIÓN: Botón mal conectado, verificar a GND

PROBLEMA: Rebotes constantes
SOLUCIÓN: delay(10) no es suficiente, agregar filtrado
```
