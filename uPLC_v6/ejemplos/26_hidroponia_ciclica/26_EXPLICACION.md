# 26 - HIDROPONÍA CÍCLICA

## 1. ¿Qué hace?
Sistema de temporización cíclica para recirculación NFT en hidroponía.
Bomba ON 15 minutos, OFF 45 minutos, repite indefinidamente.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- Módulo relé o MOSFET
- Bomba de recirculación 12V
- Canaletas NFT y nutrientes

## 3. Conexiones de hardware

```
BOMBA DE RECIRCULACIÓN:
- PIN D3 (Arduino) → IN del relé/MOSFET
- Relé: COM → Fuente 12V, NO → Bomba (+) → Fuente 12V (-)
- GND compartido

LCD I2C:
- PIN A4 (Arduino) → SDA del LCD
- PIN A5 (Arduino) → SCL del LCD
- 5V y GND

ALIMENTACIÓN:
- Arduino con fuente 12V o USB
- Bomba con fuente independiente si consume >500mA

NOTA: Para demostración usa tiempos cortos (15s/45s).
Para producción cambiar a (900000ms/2700000ms) = 15min/45min.
```

## 4. ¿Cómo funciona?

```
// AL INICIAR
AL INICIAR:
  LCD → "HIDROPONIA NFT"
  LCD → "Temporizacion ciclica"
  LCD → "Sistema listo"
  ESPERAR 2000 ms
  LCD CLEAR
  inicioCiclo = millis()
  estadoBomba = FALSO
  dentroCicloON = FALSO

// PARA SIEMPRE
PARA SIEMPRE:
  
  // Calcular posición en el ciclo
  tiempoActual = millis()
  tiempoTranscurrido = tiempoActual - inicioCiclo
  tiempoTotalCiclo = TIEMPO_ON + TIEMPO_OFF
  tiempoEnCiclo = tiempoTranscurrido % tiempoTotalCiclo
  
  // ══ FASE ON: 15 min ══
  SI (tiempoEnCiclo < TIEMPO_ON)
    ENCENDER D3                          // Bomba ON
    estadoBomba = VERDADERO
    dentroCicloON = VERDADERO
    LCD → "ESTADO: BOMBA ON"
    LCD → "FASE: RECIRCULACION"
    segundosRestantes = (TIEMPO_ON - tiempoEnCiclo) / 1000
  SINO
    // ══ FASE OFF: 45 min ══
    APAGAR D3                            // Bomba OFF
    estadoBomba = FALSO
    dentroCicloON = FALSO
    LCD → "ESTADO: BOMBA OFF"
    LCD → "FASE: ESPERA"
    segundosRestantes = (TIEMPO_OFF - (tiempoEnCiclo - TIEMPO_ON)) / 1000
  
  // Mostrar tiempo restante
  LCD → "Sig. cambio en:"
  LCD número → segundosRestantes
  LCD → "s"
  
  // Mostrar progreso del ciclo
  LCD → "Ciclo:"
  porcentaje = (tiempoEnCiclo × 100) / tiempoTotalCiclo
  LCD número → porcentaje
  LCD → "%"
  
  // Indicador visual
  SI (estadoBomba)
    LCD → "*"
  SINO
    LCD → "-"
```

## 5. Bloques utilizados

```
CATEGORÍA: VARIABLES
- CREAR variable "inicioCiclo" (número)
- CREAR variable "estadoBomba" (lógico)
- CREAR variable "dentroCicloON" (lógico)
- ASIGNAR → Guardar tiempo inicial

CATEGORÍA: MATEMÁTICA
- OPERACIÓN → tiempoEnCiclo = tiempo % tiempoTotal
- OPERACIÓN → porcentaje = (tiempo × 100) / total
- OPERACIÓN → segundos = tiempo / 1000

CATEGORÍA: LÓGICA
- SI → Evaluar fase ON u OFF
- COMPARAR → Comparar con umbrales

CATEGORÍA: SALIDAS
- ENCENDER → Activar bomba (D3 = HIGH)
- APAGAR → Desactivar bomba (D3 = LOW)

CATEGORÍA: LCD
- LCD TEXTO → Mensajes de estado
- LCD NUMERO → Tiempo y porcentaje
```

## 6. Valores de referencia

```
TIEMPOS PARA DEMOSTRACIÓN:
- TIEMPO_ON = 15000 ms (15 segundos)
- TIEMPO_OFF = 45000 ms (45 segundos)
- Ciclo total = 60 segundos

TIEMPOS PARA PRODUCCIÓN HIDROPÓNICA:
- TIEMPO_ON = 900000 ms (15 minutos)
- TIEMPO_OFF = 2700000 ms (45 minutos)
- Ciclo total = 60 minutos

CÁLCULO DE PORCENTAJE:
- Fase ON: 0% a 25% del ciclo
- Fase OFF: 25% a 100% del ciclo

NOTA: En NFT típico: 5min ON / 25min OFF o según temperatura.
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Cambiar tiempos para otro ciclo
- Agregar LED indicador de fase
- Agregar botón para pause/resume

NIVEL INTERMEDIO:
- Agregar sensor de temperatura del agua
- Reducir ciclo si temperatura muy alta
- Mostrar litros aproximados bombeados

NIVEL AVANZADO:
- Múltiples bombas con fases diferentes
- Control de pH y conductividad
- Datalogger en SD card
- Alerta si bomba falla (sensor de flujo)
```

## 8. Tips de debug

```
PROBLEMA: Ciclo no empieza en 0
SOLUCIÓN: Iniciar "inicioCiclo = millis()" en setup()

PROBLEMA: Tiempos incorrectos
SOLUCIÓN: Verificar constantes en ms, 1min = 60000ms

PROBLEMA: Oscila entre ON y OFF
SOLUCIÓN: Verificar que "dentroCicloON" se asigne solo una vez

PROBLEMA: LCD muestra valores raros
SOLUCIÓN: Usar int() o cast para evitar decimales en posiciones
```
