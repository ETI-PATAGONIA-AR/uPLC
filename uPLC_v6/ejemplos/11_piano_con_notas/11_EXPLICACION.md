# 11 - PIANO COMPLETO CON NOTAS

## 1. ¿Qué hace?
Piano de 7 notas (DO a SI) con melodía de introducción.
Más completo que el ejemplo 10, incluye todas las notas de la octava.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- Buzzer pasivo
- 7 botones

## 3. Conexiones de hardware

```
BUZZER:
- PIN D8 (Arduino) → Positivo del buzzer
- GND → Negativo del buzzer

BOTONES:
- I1=D2 → DO
- I2=D4 → RE
- I3=D5 → MI
- I4=D6 → FA
- I5=D7 → SOL
- I6=D8 → LA
- I7=D9 → SI
- Todos: Botón → 5V, Resistencia 10K → GND

LCD I2C:
- A4 (SDA) y A5 (SCL)
```

## 4. ¿Cómo funciona?

```
// MELODÍA DE INTRODUCCIÓN
INTRO():
  TONE(440, 500) ESPERAR 505 ms
  TONE(440, 500) ESPERAR 505 ms
  TONE(349, 350) ESPERAR 355 ms
  TONE(523, 150) ESPERAR 155 ms
  TONE(440, 500) ESPERAR 505 ms

// AL INICIAR
AL INICIAR:
  LCD INIT
  LCD BACKLIGHT
  LCD CLEAR
  LCD → "Mi 1er PIANO!"
  LCD → " I1=DO  I2=RE  I3=MI"
  LCD → " I4=FA  I5=SOL  I6=LA"
  LCD → " I7= SI"
  INTRO()                             // Melodía de bienvenida

// PARA SIEMPRE
PARA SIEMPRE:
  
  SI (D2 == HIGH)  TONE(8, 262, 200)
  SI (D4 == HIGH)  TONE(8, 294, 200)
  SI (D5 == HIGH)  TONE(8, 330, 200)
  SI (D6 == HIGH)  TONE(8, 349, 200)
  SI (D7 == HIGH)  TONE(8, 392, 200)
  SI (D8 == HIGH)  TONE(8, 440, 200)
  SI (D9 == HIGH)  TONE(8, 494, 200)
```

## 5. Bloques utilizados

```
CATEGORÍA: ENTRADAS
- LEER_DIGITAL → Leer 7 botones

CATEGORÍA: SALIDAS
- TONE → Generar notas musicales
- NO_TONE → Detener sonido

CATEGORÍA: FUNCIONES
- FUNCIÓN → Reproducir introducción

CATEGORÍA: LCD
- LCD TEXTO → Mostrar notas disponibles
```

## 6. Valores de referencia

```
ESCALA NATURAL (4ta octava):
- DO  = 262 Hz
- RE  = 294 Hz
- MI  = 330 Hz
- FA  = 349 Hz
- SOL = 392 Hz
- LA  = 440 Hz
- SI  = 494 Hz

INTRODUCCIÓN:
- Es fragmento reconocible para probar el buzzer
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Cambiar melodía de introducción
- Ajustar tempo

NIVEL INTERMEDIO:
- Agregar octava alta y baja
- Función para tocar melodías

NIVEL AVANZADO:
- Teclado matricial 4x3
- Grabar y reproducir
- Sintetizador con efectos
```

## 8. Tips de debug

```
PROBLEMA: Introducción no suena
SOLUCIÓN: Verificar delay suficiente entre tonos

PROBLEMA: Botón interfiere con buzzer
SOLUCIÓN: D8 es I7 y buzzer, evitar conflicto

PROBLEMA: Notas desafinadas
SOLUCIÓN: Verificar frecuencias exactas de cada nota
```
