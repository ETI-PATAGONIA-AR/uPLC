# 02 - BOTÓN Y LED

## 1. ¿Qué hace?
Enciende un LED mientras se presiona un botón.
Aprende a usar entradas digitales.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LED
- Resistencia 220Ω
- Pulsador o botón NA (normalmente abierto)
- Resistencia 10KΩ (pull-down)

## 3. Conexiones de hardware

```
BOTÓN:
- PIN D2 (Arduino) → Un terminal del botón
- 5V → Otro terminal del botón
- Resistencia 10K → PIN D2 y GND

LED:
- PIN D13 → Resistencia 220Ω → LED (+) → GND
```

## 4. ¿Cómo funciona?

```
// AL INICIAR
AL INICIAR:
  Q1 = FALSO

// PARA SIEMPRE
PARA SIEMPRE:
  SI (D2 == HIGH)              // Botón presionado
    Q1 = VERDADERO              // Encender LED
  SINO
    Q1 = FALSO                  // Apagar LED
```

## 5. Bloques utilizados

```
CATEGORÍA: ENTRADAS
- LEER_DIGITAL → Leer botón (D2)

CATEGORÍA: LÓGICA
- SI → Evaluar estado del botón
- SINO → Caso contrario

CATEGORÍA: SALIDAS
- ASIGNAR → Controlar Q1
```

## 6. Desafíos propuestos

```
NIVEL BÁSICO:
- Invertir lógica (LED apagado mientras presiona)
- Usar LED interno D13

NIVEL INTERMEDIO:
- Toggle (presionar enciende, presionar apaga)
- Contador de veces presionado

NIVEL AVANZADO:
- Anti-rebote por software
- Múltiples botones y LEDs
```

## 7. Tips de debug

```
PROBLEMA: LED parpadea sin presionar
SOLUCIÓN: Agregar resistencia pull-down de 10K

PROBLEMA: Rebotes (enciende/apaga rápidamente)
SOLUCIÓN: Agregar delay(50) o anti-rebote por código
```
