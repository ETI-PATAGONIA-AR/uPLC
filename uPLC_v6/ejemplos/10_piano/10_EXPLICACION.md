# 10 - PIANO BÁSICO

## 1. ¿Qué hace?
Piano simple con 5 notas musicales (DO a SOL) usando botones y buzzer.
Cada botón produce una nota diferente.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- Buzzer pasivo
- 5 botones

## 3. Conexiones de hardware

```
BUZZER:
- PIN D8 (Arduino) → Positivo del buzzer
- GND → Negativo del buzzer

BOTONES:
- I1=D2 → Nota DO
- I2=D4 → Nota RE
- I3=D5 → Nota MI
- I4=D6 → Nota FA
- I5=D7 → Nota SOL
- Todos: Botón → 5V, Resistencia 10K → GND

LCD I2C:
- A4 (SDA) y A5 (SCL)
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
  
  SI (D2 == HIGH)                    // DO
    TONE(8, 262, 200)
    ESPERAR 205 ms
  
  SI (D4 == HIGH)                    // RE
    TONE(8, 294, 200)
    ESPERAR 205 ms
  
  SI (D5 == HIGH)                    // MI
    TONE(8, 330, 200)
    ESPERAR 205 ms
  
  SI (D6 == HIGH)                    // FA
    TONE(8, 349, 200)
    ESPERAR 205 ms
  
  SI (D7 == HIGH)                    // SOL
    TONE(8, 392, 200)
    ESPERAR 205 ms
```

## 5. Bloques utilizados

```
CATEGORÍA: ENTRADAS
- LEER_DIGITAL → Leer botones (D2,D4,D5,D6,D7)

CATEGORÍA: SALIDAS
- TONE → Generar nota musical
- NO_TONE → Detener sonido

CATEGORÍA: LCD
- LCD TEXTO → (opcional) Mostrar nota
```

## 6. Valores de referencia

```
FRECUENCIAS (Hz):
- DO4 = 262
- RE4 = 294
- MI4 = 330
- FA4 = 349
- SOL4 = 392

DURACIÓN:
- 200ms de nota + 5ms de pausa = 205ms
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Agregar LA y SI para octava completa
- Cambiar duraciones

NIVEL INTERMEDIO:
- Agregar melodías pregrabadas
- Indicador visual de nota

NIVEL AVANZADO:
- Teclado completo 2 octavas
- Grabar melodía
- Reproducir melodías
```

## 8. Tips de debug

```
PROBLEMA: Sin sonido
SOLUCIÓN: Buzzer debe ser pasivo, verificar conexión

PROBLEMA: Nota incorrecta
SOLUCIÓN: Verificar frecuencias en tabla musical

PROBLEMA: Notas se cortan
SOLUCIÓN: delay(205) debe ser mayor que duración del tono
```
