# 04 - TERMÓMETRO LM35

## 1. ¿Qué hace?
Lee la temperatura ambiente usando el sensor LM35 y la muestra
en el LCD cada segundo.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- Sensor de temperatura LM35

## 3. Conexiones de hardware

```
SENSOR LM35:
- PIN A6 (Arduino) → Vout del LM35
- 5V → Vcc del LM35
- GND → GND del LM35

LCD I2C:
- PIN A4 (Arduino) → SDA del LCD
- PIN A5 (Arduino) → SCL del LCD
- 5V y GND

NOTA: LM35 entrega 10mV por cada grado Celsius.
```

## 4. ¿Cómo funciona?

```
// AL INICIAR
AL INICIAR:
  LCD INIT
  LCD CLEAR

// PARA SIEMPRE
PARA SIEMPRE:
  // Leer temperatura
  lectura = LEER_ANALOGICO(A6)
  temperatura = (lectura × 5.0 × 100.0) / 1023.0
  
  // Mostrar en LCD
  LCD CLEAR
  LCD → "Temperatura="
  LCD número → temperatura
  LCD → "°C"
  
  ESPERAR 900 ms
```

## 5. Bloques utilizados

```
CATEGORÍA: ENTRADAS
- LEER_ANALOGICO → Leer sensor LM35 (A6)

CATEGORÍA: MATEMÁTICA
- OPERACIÓN → temperatura = lectura × 5 × 100 / 1023

CATEGORÍA: LCD
- LCD CLEAR → Limpiar pantalla
- LCD TEXTO → Mensaje
- LCD NUMERO → Temperatura
```

## 6. Valores de referencia

```
SENSOR LM35:
- 0°C = 0mV → ADC 0
- 25°C = 250mV → ADC ~51
- 100°C = 1000mV → ADC ~204

PRECISIÓN: ±0.5°C
RANGO: 0°C a 100°C (extendible a -55°C con LM35C)
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Mostrar temperatura en Fahrenheit
- Cambiar posición en LCD

NIVEL INTERMEDIO:
- Termostato con histéresis
- Mín/Máx con memoria

NIVEL AVANZADO:
- Datalogger de temperatura
- Alarmas por temperatura
- Promedio de lecturas
```

## 8. Tips de debug

```
PROBLEMA: Temperatura incorrecta
SOLUCIÓN: Verificar conexiones 5V/GND/Vout del LM35

PROBLEMA: Siempre 0°C
SOLUCIÓN: LM35 requiere 5V, verificar Vcc

PROBLEMA: Valor fluctuante
SOLUCIÓN: Agregar capacitor 100nF entre Vout y GND
```
