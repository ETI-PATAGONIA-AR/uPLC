# 25 - RIEGO POR HUMEDAD

## 1. ¿Qué hace?
Control automático de riego según la humedad del suelo con histéresis
para evitar que la bomba oscile cerca del umbral.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- Sensor de humedad del suelo (higrómetro)
- Módulo relé o MOSFET para bomba
- Bomba de agua 12V

## 3. Conexiones de hardware

```
SENSOR DE HUMEDAD:
- PIN A0 (Arduino) → Signal del sensor
- 3.3V o 5V → VCC del sensor
- GND → GND del sensor

BOMBA DE RIEGO:
- PIN D3 (Arduino) → IN del relé/MOSFET
- Relé: COM → Fuente 12V, NO → Bomba (+) → Fuente 12V (-)
- GND compartido

LCD I2C:
- PIN A4 (Arduino) → SDA del LCD
- PIN A5 (Arduino) → SCL del LCD
- 5V y GND

NOTA: Sensor capacitivo es más durable que resistivo.
```

## 4. ¿Cómo funciona?

```
// AL INICIAR
AL INICIAR:
  LCD → "CONTROL DE RIEGO"
  LCD → "Sensor: Humedad suelo"
  LCD → "Umbral: 30%"
  ESPERAR 2500 ms
  LCD CLEAR
  regando = FALSO

// PARA SIEMPRE (ciclo principal)
PARA SIEMPRE:
  
  // Leer y convertir humedad
  humedad_raw = LEER_ANALOGICO(A0)
  humedad = (humedad_raw × 100) / 1023
  humedad_real = 100 - humedad
  
  // Mostrar en LCD
  LCD → "Humedad:"
  LCD número → humedad_real
  LCD → "%"
  
  // Dibujar barra visual
  LCD → "["
  barras = humedad_real / 5
  PARA i=0 HASTA barras: LCD → "|"
  PARA i=barras HASTA 20: LCD → " "
  LCD → "]"
  
  // ══ Lógica con histéresis ══
  SI (humedad_real < 30)          // Umbral bajo
    ENCENDER D3                    // Regar
    regando = VERDADERO
    LCD → "REGANDO!"
    LCD → "Bomba ON"
  
  SINO SI (humedad_real > 35)      // Umbral alto
    APAGAR D3                      // Cortar
    regando = FALSO
    LCD → "ESPERANDO..."
    LCD → "Bomba OFF"
  
  SINO                               // Zona muerta
    SI (regando == VERDADERO)
      LCD → "MANTENIENDO..."
      LCD → "Bomba ON"              // Mantener estado
    SINO
      LCD → "MANTENIENDO..."
      LCD → "Bomba OFF"
```

## 5. Bloques utilizados

```
CATEGORÍA: ENTRADAS
- LEER_ANALOGICO → Leer sensor (A0), devuelve 0-1023

CATEGORÍA: MATEMÁTICA
- OPERACIÓN → humedad_real = 100 - (valor × 100 / 1023)

CATEGORÍA: LÓGICA
- SI → Evaluar humedad baja (< 30%)
- SINO SI → Evaluar humedad alta (> 35%)
- COMPARAR → Comparar valores (operador <, >, ==)

CATEGORÍA: VARIABLES
- ASIGNAR → Guardar estado "regando"

CATEGORÍA: SALIDAS
- ENCENDER → Activar bomba (D3 = HIGH)
- APAGAR → Desactivar bomba (D3 = LOW)

CATEGORÍA: LCD
- LCD CLEAR → Limpiar pantalla
- LCD TEXTO → Mensajes en posición
- LCD NUMERO → Valor numérico
```

## 6. Valores de referencia

```
SENSOR DE HUMEDAD:
- Seco (en aire): ADC ~ 0-100, humedad_real ~ 0-10%
- Húmedo (tierra húmeda): ADC ~ 300-500, humedad_real ~ 30-50%
- Sumergido (en agua): ADC ~ 800-1023, humedad_real ~ 80-100%

UMBRALES CONFIGURADOS:
- Umbral bajo (enciende): 30% → Regar
- Umbral alto (apaga): 35% → Cortar
- Histéresis: 5% para evitar oscilaciones

NOTA: Cada sensor es diferente. Calibrar umbrales según tu suelo.
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Cambiar umbrales para otra planta
- Agregar LED que parpadee mientras riega
- Mostrar mensajes en español más claros

NIVEL INTERMEDIO:
- Agregar botón manual para activar riego
- Usar sensor capacitivo más preciso
- Implementar múltiples zonas de riego

NIVEL AVANZADO:
- Datalogger de humedad en SD card
- Control por WiFi/Bluetooth
- Predicción de riego según historial
- Integrar con sensor de lluvia (no regar si llueve)
```

## 8. Tips de debug

```
PROBLEMA: Siempre marca 0% o 100%
SOLUCIÓN: Verificar conexiones del sensor, probar con potenciómetro

PROBLEMA: Valores erráticos
SOLUCIÓN: Agregar capacitor 100nF en A0 a GND, usar promedio de lecturas

PROBLEMA: Bomba no enciende
SOLUCIÓN: Verificar módulo relé, probar D3 directamente con LED

PROBLEMA: Histéresis no funciona
SOLUCIÓN: Verificar que la variable "regando" se mantenga entre ciclos
```
