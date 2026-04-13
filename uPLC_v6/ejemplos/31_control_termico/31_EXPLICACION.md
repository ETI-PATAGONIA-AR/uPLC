# 31 - CONTROL TÉRMICO

## 1. ¿Qué hace?
Control de temperatura para invernadero o gabinete electrónico.
Calefactor cuando hace frío, ventilador cuando hace calor.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- Sensor LM35 (o TMP36/DS18B20)
- Módulo relé para calefactor
- Módulo relé para ventilador
- Calefactor y/o ventilador

## 3. Conexiones de hardware

```
SENSOR LM35 (precisión 0.5°C):
- PIN A0 (Arduino) → Vout del LM35
- 5V → Vcc del LM35
- GND → GND del LM35
- Output: 10mV por °C (25°C = 250mV)

VENTILADOR:
- PIN D3 (Arduino) → IN del relé
- Relé: COM → Fuente, NO → Ventilador

CALEFACTOR:
- PIN D5 (Arduino) → IN del relé
- Relé: COM → Fuente, NO → Calefactor

LCD I2C:
- PIN A4 (Arduino) → SDA del LCD
- PIN A5 (Arduino) → SCL del LCD

NOTA: LM35 no necesita calibración, 0-100°C range.
```

## 4. ¿Cómo funciona?

```
// CONSTANTES
TEMP_MIN = 25      // Por debajo: calefactor ON
TEMP_MAX = 30      // Por arriba: ventilador ON
TEMP_ALERTA = 35   // Alerta temperatura alta

// AL INICIAR
AL INICIAR:
  LCD → "CONTROL TERMICO"
  LCD → "A0: Sensor temperatura"
  LCD → "D3: Ventilador"
  LCD → "D5: Calefactor"
  ESPERAR 2500 ms
  LCD CLEAR

// PARA SIEMPRE
PARA SIEMPRE:
  
  // Leer temperatura (LM35: 10mV/°C)
  lectura = LEER_ANALOGICO(A0)
  temperatura = (lectura × 5.0 × 100.0) / 1023.0
  
  // Mostrar temperatura
  LCD → "Temp: "
  LCD número → temperatura
  LCD → "°C"
  
  // ══ FRÍO: < 25°C → Calefactor ON ══
  SI (temperatura < TEMP_MIN)
    ENCENDER D5                  // Calefactor ON
    APAGAR D3                    // Ventilador OFF
    LCD → "*** FRIO ***"
    LCD → "Calefactor: ON"
    LCD → "Ventilador: OFF"
  
  // ══ CALOR: > 30°C → Ventilador ON ══
  SINO SI (temperatura > TEMP_MAX)
    APAGAR D5                    // Calefactor OFF
    ENCENDER D3                  // Ventilador ON
    LCD → "*** CALOR ***"
    LCD → "Calefactor: OFF"
    LCD → "Ventilador: ON"
    
    // Alerta si muy caliente
    SI (temperatura > TEMP_ALERTA)
      LCD → "⚠"
      TONE(8, 660, 100)
    SINO
      LCD → "  "
  
  // ══ OK: 25-30°C → Ambos OFF ══
  SINO
    APAGAR D3
    APAGAR D5
    LCD → "*** OK ***"
    LCD → "Calefactor: OFF"
    LCD → "Ventilador: OFF"
  
  // Barra visual de temperatura
  LCD → "["
  barras = temperatura / 3
  SI (barras > 20) barras = 20
  PARA i=0 HASTA barras: LCD → "|"
  PARA i=barras HASTA 20: LCD → " "
  LCD → "]"
```

## 5. Bloques utilizados

```
CATEGORÍA: ENTRADAS
- LEER_ANALOGICO → Leer sensor LM35 (A0)

CATEGORÍA: MATEMÁTICA
- OPERACIÓN → temperatura = lectura × 5 × 100 / 1023
- OPERACIÓN → barras = temperatura / 3

CATEGORÍA: LÓGICA
- SI → Evaluar frío
- SINO SI → Evaluar calor
- COMPARAR → Comparar con umbrales

CATEGORÍA: SALIDAS
- ENCENDER → Ventilador (D3) o Calefactor (D5)
- APAGAR → Apagar负载

CATEGORÍA: LCD
- LCD TEXTO → Mensajes de estado
- LCD NUMERO → Temperatura y barra
```

## 6. Valores de referencia

```
SENSOR LM35:
- 0°C = 0mV → ADC 0
- 25°C = 250mV → ADC ~51
- 30°C = 300mV → ADC ~61
- 35°C = 350mV → ADC ~71
- 100°C = 1000mV → ADC ~204

UMBRALES CONFIGURADOS:
- < 25°C: FRÍO → Calefactor ON
- 25-30°C: OK → Ambos OFF
- > 30°C: CALOR → Ventilador ON
- > 35°C: ALERTA → Sonido

PARA OTROS SENSORES:
- TMP36: offset -0.5V, diferente escala
- DS18B20: digital, no usa ADC

NOTA: Histéresis implícita (2°C entre umbrales).
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Cambiar umbrales según necesidad
- Agregar LED de estado
- Usar sensor diferente

NIVEL INTERMEDIO:
- Histéresis configurable
- Promedio de lecturas
- Modo nocturno (reducir temperatura objetivo)

NIVEL AVANZADO:
- Control PID para precisión
- Múltiples zonas
- Datalogger de temperatura
- Control por WiFi
```

## 8. Tips de debug

```
PROBLEMA: Temperatura incorrecta
SOLUCIÓN: Verificar conexiones LM35, medir con multimetro

PROBLEMA: Siempre muestra 0°C
SOLUCIÓN: LM35 requiere 5V, verificar Vcc

PROBLEMA: Oscila entre frío y calor
SOLUCIÓN: Aumentar histéresis (TEMP_MIN=23, TEMP_MAX=32)

PROBLEMA: Ambos encendidos
SOLUCIÓN: Estructura if-elseif correcta, no ambos en mismo if
```
