# 29 - TEMPORIZADOR DÍA/NOCHE

## 1. ¿Qué hace?
Sistema inteligente que detecta si es de día o noche usando un LDR
(sensor de luz) y ajusta el comportamiento según el período.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- LDR (fotorresistencia) 10K
- Botón o sensor
- Carga a controlar (luz, bomba, válvula)

## 3. Conexiones de hardware

```
SENSOR LDR (divisor de tensión):
- PIN A0 (Arduino) → Un extremo del LDR
- LDR → Resistencia 10K → GND
- Fórmula: Luz = ADC leido
- Más luz = menor resistencia = mayor voltaje = mayor ADC

BOTÓN:
- PIN D2 (Arduino) → Botón → 5V
- Resistencia 10K → GND

SALIDA:
- PIN D3 (Arduino) → Carga a controlar
- Usar relé o MOSFET según potencia

LCD I2C:
- PIN A4 (Arduino) → SDA del LCD
- PIN A5 (Arduino) → SCL del LCD

NOTA: LDR tiene respuesta lenta, buena para ciclo día/noche.
```

## 4. ¿Cómo funciona?

```
// CONSTANTES
UMBRAL_LUZ = 500

// AL INICIAR
AL INICIAR:
  LCD → "DIA / NOCHE"
  LCD → "A0: LDR (luz)"
  LCD → "D3: Salida"
  LCD → "Umbral: 500"
  ESPERAR 2500 ms
  LCD CLEAR

// PARA SIEMPRE
PARA SIEMPRE:
  
  // Leer sensor de luz
  luz = LEER_ANALOGICO(A0)
  
  // Determinar período
  SI (luz > UMBRAL_LUZ)
    esDia = VERDADERO
  SINO
    esDia = FALSO
  
  // Mostrar modo
  SI (esDia)
    LCD → "*** MODO DIA ***"
  SINO
    LCD → "*** MODO NOCHE ***"
  
  // Mostrar valor y barra
  LCD → "Luz:"
  LCD número → luz
  LCD → "["
  barras = luz / 51
  PARA i=0 HASTA barras: LCD → "|"
  PARA i=barras HASTA 20: LCD → " "
  LCD → "]"
  
  // ══ MODO DÍA: Funcionamiento normal ══
  SI (esDia)
    SI (D2 == HIGH)           // Botón presionado
      ENCENDER D3
      LCD → "Salida: ON (DIA)"
    SINO
      APAGAR D3
      LCD → "Salida: OFF (DIA)"
  
  // ══ MODO NOCHE: Retraso de 2 segundos ══
  SINO
    SI (D2 == HIGH) Y (modoManual == FALSO)
      modoManual = VERDADERO
      tiempoNoche = millis()
    
    SI (modoManual == VERDADERO)
      SI ((millis() - tiempoNoche) > 2000)
        ENCENDER D3
        LCD → "Salida: ON (NOCHE)"
      SINO
        APAGAR D3
        LCD → "NOCHE: Espere..."
    SINO
      APAGAR D3
      LCD → "Salida: OFF (NOCHE)"
```

## 5. Bloques utilizados

```
CATEGORÍA: ENTRADAS
- LEER_ANALOGICO → Leer LDR (A0)
- LEER_DIGITAL → Leer botón (D2)

CATEGORÍA: VARIABLES
- CREAR variable "esDia" (lógico)
- CREAR variable "modoManual" (lógico)
- CREAR variable "tiempoNoche" (número)

CATEGORÍA: MATEMÁTICA
- OPERACIÓN → barras = luz / 51
- OPERACIÓN → tiempoTranscurrido = millis() - inicio

CATEGORÍA: LÓGICA
- SI → Evaluar día/noche
- COMPARAR → Comparar con umbral
- Y → Combinar condiciones

CATEGORÍA: SALIDAS
- ENCENDER/APAGAR → Controlar carga (D3)
```

## 6. Valores de referencia

```
LECTURAS DEL LDR:
- Oscuridad total: ADC ~ 0-50 (resistencia muy alta)
- Habitación iluminada: ADC ~ 300-500
- Luz solar directa: ADC ~ 800-1023

UMBRAL CONFIGURADO:
- 500: Divide día/noche
- Ajustar según tu ubicación y época del año

COMPORTAMIENTO:
- DÍA: Responde inmediatamente al botón
- NOCHE: Retraso de 2 segundos (seguridad, filtro de falsos)

NOTA: En invierno el umbral debe ser menor.
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Cambiar el umbral según necesidad
- Agregar LED que indique modo
- Agregar zumbador en modo noche

NIVEL INTERMEDIO:
- Agregar timer de apagado automático
- Historial de cambios día/noche
- Ajustar umbral automáticamente

NIVEL AVANZADO:
- Amanecer/anochecer gradual (PWM)
- Predicción de día siguiente
- Integrar con Weather API
- Control de cortinas/sombreadores
```

## 8. Tips de debug

```
PROBLEMA: Siempre dice "DÍA"
SOLUCIÓN: LDR necesita luz, verificar divisor resistivo

PROBLEMA: Siempre dice "NOCHE"
SOLUCIÓN: Tapar LDR con dedo, debe bajar valor

PROBLEMA: Oscila entre día/noche
SOLUCIÓN: Agregar histéresis (umbral sube y baja diferente)

PROBLEMA: Retraso no funciona
SOLUCIÓN: Verificar variable "tiempoNoche" se inicializa
```
