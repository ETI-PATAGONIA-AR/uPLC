# 30 - MONITOR DE BATERÍA

## 1. ¿Qué hace?
Monitor de tensión de batería con alertas visuales y sonoras.
Detecta estados: BAJA, OK, ALTA y alerta al usuario.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- 2 resistencias de 10K para divisor
- LED o buzzer para alertas
- Batería a monitorear

## 3. Conexiones de hardware

```
DIVISOR DE TENSIÓN (para batería 12V):
- Borne (+) → R1 (10K) → A0 → R2 (10K) → GND
- Borne (-) → GND
- Tensión en A0 = (Vbat × R2) / (R1 + R2)
- Para 12V: A0 ≈ 2.5V → ADC ≈ 512
- Para 14V: A0 ≈ 2.9V → ADC ≈ 590

ALERTA:
- PIN D3 (Arduino) → LED/Buzzer
- Resistencia 220Ω si usa LED directo

LCD I2C:
- PIN A4 (Arduino) → SDA del LCD
- PIN A5 (Arduino) → SCL del LCD

NOTA: Usar divisor R1=10K, R2=10K para 0-20V range.
```

## 4. ¿Cómo funciona?

```
// CONSTANTES
VBAT_MIN = 300    // ~10.5V - Baja crítica
VBAT_OK = 500     // ~12V - Normal
VBAT_MAX = 570    // ~14V - Alta (sobrecarga)

// AL INICIAR
AL INICIAR:
  LCD → "MONITOR BATERIA"
  LCD → "A0: Tension bateria"
  LCD → "D3: Alerta"
  ESPERAR 2500 ms
  LCD CLEAR

// PARA SIEMPRE
PARA SIEMPRE:
  
  // Leer tensión
  vbat = LEER_ANALOGICO(A0)
  voltaje = (vbat × 5) / 10    // Convertir a deciVolts (×10)
  
  // Mostrar tensión
  LCD → "Vbat:"
  LCD número → voltaje/10     // Parte entera
  LCD → "."
  LCD número → voltaje%10     // Parte decimal
  LCD → "V"
  
  // ══ EVALUAR ESTADO ══
  SI (vbat < VBAT_MIN)
    // BATERÍA BAJA - CRÍTICO
    ENCENDER D3
    LCD → "⚠ ALERTA BAJA ⚠"
    LCD → "Cargar bateria!"
    TONE(8, 440, 200)         // Pitido grave
  
  SINO SI (vbat < VBAT_OK)
    // BATERÍA BAJA - PRECAUCIÓN
    ENCENDER D3
    ESPERAR 100 ms
    APAGAR D3
    ESPERAR 100 ms
    LCD → "- PRECAUCION -"
    LCD → "Bateria baja"
  
  SINO SI (vbat > VBAT_MAX)
    // SOBRETENSIÓN
    ENCENDER D3
    LCD → "⚠ ALERTA ALTA ⚠"
    LCD → "Sobretension!"
    TONE(8, 880, 100)         // Pitido agudo
  
  SINO
    // BATERÍA OK
    APAGAR D3
    LCD → "✓ BATERIA OK ✓"
    LCD → "Voltaje normal"
  
  // Barra de estado
  LCD → "["
  barras = (vbat - VBAT_MIN) / 10
  SI (barras < 0) barras = 0
  SI (barras > 30) barras = 30
  PARA i=0 HASTA barras: LCD → "|"
  PARA i=barras HASTA 30: LCD → " "
  LCD → "]"
```

## 5. Bloques utilizados

```
CATEGORÍA: ENTRADAS
- LEER_ANALOGICO → Leer tensión (A0)

CATEGORÍA: MATEMÁTICA
- OPERACIÓN → voltaje = (vbat × 5) / 10
- OPERACIÓN → deciVolts = voltaje × 10

CATEGORÍA: LÓGICA
- SI → Evaluar estado de batería
- SINO SI → Evaluar siguiente condición
- COMPARAR → Comparar con umbrales

CATEGORÍA: SALIDAS
- ENCENDER/APAGAR → LED alerta (D3)

CATEGORÍA: LCD
- LCD TEXTO → Mensajes de estado
- LCD NUMERO → Voltaje y barra

CATEGORÍA: SONIDO
- TONE → Generar pitidos de alerta
```

## 6. Valores de referencia

```
PARA BATERÍA 12V con divisor 10K-10K:
- ADC 0 = 0V
- ADC 300 ≈ 10.5V → VBAT_MIN (descarga profunda)
- ADC 500 ≈ 12V → VBAT_OK (carga completa)
- ADC 570 ≈ 14V → VBAT_MAX (sobrecarga)
- ADC 682 ≈ 16.6V → Máximo sin dañar Arduino

PARA BATERÍA 24V usar: R1=22K, R2=10K
- ADC 500 ≈ 24V

PARA BATERÍA 6V usar: R1=4.7K, R2=10K
- ADC 512 ≈ 6.6V

ALERTAS:
- Baja crítica: Pitido grave continuo
- Baja precaución: Parpadeo lento
- OK: Sin alerta
- Alta: Pitido agudo
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Cambiar umbrales para otra batería
- Agregar más LEDs de estado
- Mostrar porcentaje de carga

NIVEL INTERMEDIO:
- Histéresis para umbrales
- Promedio de lecturas
- Tiempo en cada estado

NIVEL AVANZADO:
- Datalogger de tensión
- Estimador de tiempo restante
- Control de cargador
- Display OLED gráfico
```

## 8. Tips de debug

```
PROBLEMA: Voltaje incorrecto
SOLUCIÓN: Verificar divisor, medir con multimetro

PROBLEMA: Alertas constantes
SOLUCIÓN: Verificar umbrales según batería real

PROBLEMA: ADC inestable
SOLUCIÓN: Capacitor 100nF en A0, promediar 10 lecturas
```
