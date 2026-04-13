# 01 - PARPADEO LED

## 1. ¿Qué hace?
Enciende y apaga un LED cada 1 segundo de forma continua.
Es el programa más básico para aprender Arduino.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LED (cualquier color)
- Resistencia 220Ω o 330Ω

## 3. Conexiones de hardware

```
LED:
- PIN D13 (Arduino) → Resistencia 220Ω → Anodo (+) LED
- Cátodo (-) LED → GND

NOTA: D13 tiene LED integrado en la placa (L en many Arduino).
```

## 4. ¿Cómo funciona?

```
// AL INICIAR
AL INICIAR:
  Q1 = FALSO                    // Asegurar LED apagado

// PARA SIEMPRE
PARA SIEMPRE:
  Q1 = VERDADERO                // Encender LED
  ESPERAR 1000 ms               // Esperar 1 segundo
  Q1 = FALSO                    // Apagar LED
  ESPERAR 1000 ms               // Esperar 1 segundo
```

## 5. Bloques utilizados

```
CATEGORÍA: SALIDAS
- ASIGNAR → Q1 = VERDADERO (encender)
- ASIGNAR → Q1 = FALSO (apagar)

CATEGORÍA: TIEMPO
- ESPERAR_ms → Pausas de 1000ms
```

## 6. Desafíos propuestos

```
NIVEL BÁSICO:
- Cambiar velocidad de parpadeo
- Usar otro PIN (D14, D15, etc.)

NIVEL INTERMEDIO:
- Parpadeo rápido (SOS en Morse)
- Fade in/out con PWM

NIVEL AVANZADO:
- Múltiples LEDs en secuencia
- Código Morse automático
```

## 7. Tips de debug

```
PROBLEMA: LED no enciende
SOLUCIÓN: Verificar polaridad del LED, resistencia obligatoria

PROBLEMA: LED siempre encendido
SOLUCIÓN: Revisar lógica de asignación en loop()
```
