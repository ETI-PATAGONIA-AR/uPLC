# 20 - TIMER LUZ CREPUSCULAR

## 1. ¿Qué hace?
Enciende luces al anochecer con retardos configurables.
Combina sensor de luz con temporizadores.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- LDR (fotorresistencia) 10K
- Resistencia 10K
- Módulo relé para luces

## 3. Conexiones de hardware

```
LDR (divisor de tensión):
- PIN A6 (Arduino) → LDR → Resistencia 10K → GND
- 5V → LDR

RELE LUZ:
- PIN D13 (Q1) → IN del relé
- Relé: COM → Fuente, NO → Luz

LCD I2C:
- A4 (SDA) y A5 (SCL)
```

## 4. ¿Cómo funciona?

```
// CONSTANTES
UMBRAL_LUZ = 40              // Por debajo = oscuro
TIEMPO_ON = 5000 ms          // Retraso al encender
TIEMPO_OFF = 10000 ms        // Retraso al apagar

// TIMERS
T0_start = 0
T0_done = FALSO
T0_en = VERDADERO

T1_start = 0
T1_done = FALSO
T1_en = VERDADERO

// AL INICIAR
AL INICIAR:
  LCD CLEAR

// PARA SIEMPRE
PARA SIEMPRE:
  
  // Leer luz (0-1023 → 0-100%)
  luz = map(LEER_ANALOGICO(A6), 0, 1023, 0, 100)
  LCD → "Luz:" + luz
  
  // ══ OSCURO: luz < 40 ══
  SI (luz < 40)
    // Iniciar timer de 5 segundos
    SI (T0_en)
      T0_done = VERDADERO          // Timer completado
      T0_prev = VERDADERO
    SINO SI (T0_prev)
      T0_prev = FALSO
      T0_start = millis()         // Iniciar conteo
    SINO
      T0_done = (millis() - T0_start < 5000)
    
    SI (T0_done)
      ENCENDER Q1                  // Luz ON
  
  // ══ CLARO: luz >= 40 ══
  SI (luz >= 40)
    // Iniciar timer de 10 segundos
    SI (T1_en)
      T1_done = VERDADERO
      T1_prev = VERDADERO
    SINO SI (T1_prev)
      T1_prev = FALSO
      T1_start = millis()
    SINO
      T1_done = (millis() - T1_start < 10000)
    
    SI (T1_done)
      APAGAR Q1                    // Luz OFF
```

## 5. Bloques utilizados

```
CATEGORÍA: ENTRADAS
- LEER_ANALOGICO → Leer LDR (A6)

CATEGORÍA: VARIABLES
- CREAR → Timers con memoria
- ASIGNAR → Control de estados

CATEGORÍA: MATEMÁTICA
- map() → Escalar valor
- OPERACIÓN → millis() - inicio

CATEGORÍA: LÓGICA
- SI → Evaluar luz
- COMPARAR → <, >=

CATEGORÍA: SALIDAS
- ENCENDER/APAGAR → Control relé (Q1)
```

## 6. Valores de referencia

```
LECTURAS LDR:
- Oscuro: 0-40% → Luz OFF, timer 5s
- Claro: 40-100% → Luz ON, timer 10s

RETARDOS:
- Encendido: 5 segundos de oscuridad antes de encender
- Apagado: 10 segundos de claridad antes de apagar

NOTA: Evita que nubes pasajeras enciendan/apaguen luces.
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Cambiar umbrales de luz
- Ajustar tiempos de retardo

NIVEL INTERMEDIO:
- Histéresis configurable
- Indicador visual de estado

NIVEL AVANZADO:
- Diferentes retardos según hora
- Datalogger de ciclos
- Control por Bluetooth
```

## 8. Tips de debug

```
PROBLEMA: Luz oscila
SOLUCIÓN: Aumentar diferencia entre timer ON y OFF

PROBLEMA: Timer no funciona
SOLUCIÓN: Verificar variable global para mantener estado

PROBLEMA: Luz siempre encendida
SOLUCIÓN: Revisar lógica de timer y comparaciones
```
