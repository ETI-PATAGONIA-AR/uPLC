# 15 - MEDIDOR DE LUZ

## 1. ¿Qué hace?
Mide la intensidad de luz ambiental usando un LDR y la muestra
en el LCD con una barra visual.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- LDR (fotorresistencia) 10K
- Resistencia 10K

## 3. Conexiones de hardware

```
LDR:
- PIN A6 (Arduino) → LDR → Resistencia 10K → GND
- 5V → LDR (el otro extremo)
- Más luz = menor resistencia = mayor ADC

LCD I2C:
- PIN A4 (Arduino) → SDA del LCD
- PIN A5 (Arduino) → SCL del LCD
- 5V y GND
```

## 4. ¿Cómo funciona?

```
// AL INICIAR
AL INICIAR:
  LCD INIT
  LCD BACKLIGHT
  LCD CLEAR

// PARA SIEMPRE
PARA SIEMPRE:
  // Leer sensor de luz
  V0 = LEER_ANALOGICO(A6)
  
  // Mostrar valor
  LCD → "Luz:"
  LCD número → V0
  
  // Dibujar barra visual
  LCD → "["
  barras = V0 / 51              // Escalar a 20 caracteres
  PARA i=0 HASTA barras: LCD → "|"
  PARA i=barras HASTA 20: LCD → " "
  LCD → "]"
  
  ESPERAR 900 ms
  LCD CLEAR
```

## 5. Bloques utilizados

```
CATEGORÍA: ENTRADAS
- LEER_ANALOGICO → Leer LDR (A6)

CATEGORÍA: MATEMÁTICA
- OPERACIÓN → barras = V0 / 51

CATEGORÍA: LCD
- LCD CLEAR → Limpiar pantalla
- LCD TEXTO → Mensaje y barra
- LCD NUMERO → Valor
```

## 6. Valores de referencia

```
LDR:
- Oscuridad total: ADC ~ 0-10
- Habitación oscura: ADC ~ 100-200
- Habitación iluminada: ADC ~ 300-500
- Luz solar directa: ADC ~ 800-1023

BARRA VISUAL:
- 0 bars = Oscuridad
- 10 bars = Habitación normal
- 20 bars = Luz máxima
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Cambiar escala de la barra
- Mostrar en porcentaje (%)

NIVEL INTERMEDIO:
- Indicadores de día/noche
- Gráfico histórico

NIVEL AVANZADO:
- Luxómetro calibrado
- Datalogger de luz
- Alerta por exceso de luz
```

## 8. Tips de debug

```
PROBLEMA: LCD se borra constantemente
SOLUCIÓN: Actualizar solo partes del LCD, no hacer clear

PROBLEMA: Barra siempre en 0
SOLUCIÓN: Verificar conexiones del LDR

PROBLEMA: Valor máximo siempre
SOLUCIÓN: Tapar LDR con mano para probar
```
