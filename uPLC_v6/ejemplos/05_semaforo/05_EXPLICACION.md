# 05 - SEMÁFORO

## 1. ¿Qué hace?
Simula un semáforo de intersection con secuencias para
peatones y vehículos.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- 6 LEDs (2 rojos, 2 amarillos, 2 verdes)
- 6 resistencias 220Ω
- LCD 20x4 I2C (opcional)

## 3. Conexiones de hardware

```
SEMÁFORO VEHÍCULOS (ejemplo):
- D13 (Q1) → Resistencia 220Ω → LED Rojo
- D14 (Q2) → Resistencia 220Ω → LED Amarillo
- D15 (Q3) → Resistencia 220Ω → LED Verde

SEMÁFORO PEATONES (ejemplo):
- D16 (Q4) → Resistencia 220Ω → LED Rojo peatón
- D17 (Q5) → Resistencia 220Ω → LED Verde peatón

NOTA: Asignar según necesidad en el programa.
```

## 4. ¿Cómo funciona?

```
// SECUENCIA SEMÁFORO
AL INICIAR:
  LCD → "SEMAFORO"
  ESPERAR 2 segundos

PARA SIEMPRE:
  // Vehículos: VERDE, Peatones: ROJO
  Q1 = FALSO   // Rojo OFF
  Q2 = FALSO   // Amarillo OFF
  Q3 = VERDADERO // Verde ON
  Q4 = VERDADERO // Peatonal Rojo ON
  Q5 = FALSO   // Peatonal Verde OFF
  ESPERAR 5 segundos

  // Vehículos: AMARILLO
  Q3 = FALSO
  Q2 = VERDADERO
  ESPERAR 2 segundos

  // Vehículos: ROJO, Peatones: VERDE
  Q2 = FALSO
  Q1 = VERDADERO
  Q4 = FALSO
  Q5 = VERDADERO
  ESPERAR 5 segundos

  // Vehículos: ROJO + AMARILLO
  Q2 = VERDADERO
  ESPERAR 2 segundos
```

## 5. Bloques utilizados

```
CATEGORÍA: SALIDAS
- ASIGNAR → Controlar LEDs (Q1-Q5)

CATEGORÍA: TIEMPO
- ESPERAR_ms → Secuencias temporales

CATEGORÍA: LCD
- LCD TEXTO → Mostrar estado (opcional)
```

## 6. Desafíos propuestos

```
NIVEL BÁSICO:
- Cambiar tiempos de secuencia
- Solo 3 LEDs (simple)

NIVEL INTERMEDIO:
- Botón para paso de peatón
- Parpadeo de amarillo

NIVEL AVANZADO:
- Sensor de vehículos
- Temporizador adaptativo
- Modo nocturno (solo amarillo parpadeando)
```

## 7. Tips de debug

```
PROBLEMA: LEDs no corresponden a colores
SOLUCIÓN: Verificar cableado y asignación de Q

PROBLEMA: Secuencia muy rápida
SOLUCIÓN: Aumentar tiempos de espera

PROBLEMA: LCD se borra constantemente
SOLUCIÓN: No usar LCD CLEAR dentro del loop
```
