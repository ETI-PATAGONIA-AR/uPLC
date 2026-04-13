# 24 - CARGA FOTOVOLTAICA

## 1. ¿Qué hace?
Controla la carga de una batería según la tensión del panel solar, 
protegiendo de sobrecarga y descarga profunda.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- MOSFET tipo N (IRLZ44N o similar)
- 2 resistencias de 10K ohm para divisor de tensión

## 3. Conexiones de hardware

```
DIVISOR DE TENSIÓN:
- Panel Solar (+) → Resistencia R1 (10K) → Punto medio → PIN A0
- Punto medio → Resistencia R2 (10K) → GND
- Fórmula: Vpanel = (Vleido × (R1+R2)) / R2

CONTROL MOSFET:
- PIN D3 (Arduino) → Gate del MOSFET
- Source del MOSFET → GND
- Drain del MOSFET → Borne positivo de la carga
- Borne negativo de la carga → Borne positivo de la batería
- Borne negativo de la batería → GND
- Resistor de 10K entre Gate y GND (mantiene apagado al reset)

LCD I2C:
- PIN A4 (Arduino) → SDA del LCD
- PIN A5 (Arduino) → SCL del LCD
- 5V y GND

NOTA: Usar MOSFET tipo N que soporte la corriente de la carga.
```

## 4. ¿Cómo funciona?

```
// AL INICIAR
AL INICIAR:
  LCD → "CARGA FOTOVOLTAICA"
  LCD → "Control de carga por PWM"
  ESPERAR 2500 ms
  LCD CLEAR

// PARA SIEMPRE (ciclo principal)
PARA SIEMPRE:
  
  // Leer tensión del panel
  V0 = LEER_ANALOGICO(A0)
  
  // Mostrar valor ADC
  LCD → "ADC:"
  LCD número → V0
  
  // ══ BATERÍA BAJA: A0 < 500 → CARGA 100% ══
  SI (V0 < 500)
    ENCENDER D3
    LCD → "PWM 100% - CARGA ON"
    LCD → "Bateria BAJA"
    ESPERAR 500 ms
  
  // ══ BATERÍA MEDIA: 500 <= A0 < 570 → CARGA 50% ══
  SINO SI (V0 < 570)
    ENCENDER D3
    LCD → "PWM 50%"
    LCD → "Bateria MEDIA"
    ESPERAR 200 ms
    APAGAR D3
    ESPERAR 200 ms
  
  // ══ BATERÍA ALTA: A0 >= 570 → CARGA 0% ══
  SINO
    APAGAR D3
    LCD → "PWM 0% - CARGA OFF"
    LCD → "Bateria ALTA"
    ESPERAR 500 ms
```

## 5. Bloques utilizados

```
CATEGORÍA: ENTRADAS
- LEER_ANALOGICO → Leer valor del divisor (A0), devuelve 0-1023

CATEGORÍA: LÓGICA
- SI → Evaluar condición de batería baja (V0 < 500)
- SINO SI → Evaluar condición de batería media (V0 < 570)
- COMPARAR → Comparar valores (operador <, >, ==)

CATEGORÍA: SALIDAS
- ENCENDER → Activar MOSFET (D3 = HIGH)
- APAGAR → Desactivar MOSFET (D3 = LOW)

CATEGORÍA: LCD
- LCD CLEAR → Limpiar pantalla
- LCD TEXTO → Mostrar mensajes en posición específica
- LCD NUMERO → Mostrar valor numérico en posición específica

CATEGORÍA: TIEMPO
- ESPERAR_ms → Generar PWM manual (ON 200ms / OFF 200ms = 50%)
```

## 6. Valores de referencia

```
CON DIVISOR 10K-10K:
- ADC 0     = 0V en A0   = 0V en panel
- ADC 512   = 2.5V       = 5V en panel
- ADC 600   = 2.9V       = 5.8V en panel
- ADC 682   = 3.3V       = 6.6V en panel
- ADC 1023  = 5V         = 10V en panel

UMBRALES PARA BATERÍA 12V:
- 500 (ADC) ≈ 12V → Carga al 100%
- 570 (ADC) ≈ 14V → Corte de carga

PARA BATERÍA 24V usar divisor diferente.
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Cambiar los umbrales para otra batería
- Agregar LED que parpadee cuando carga
- Mostrar voltaje real en lugar de ADC

NIVEL INTERMEDIO:
- Agregar histéresis (diferencia carga/corte)
- Implementar PWM real con analogWrite()
- Agregar sensor de corriente ACS712

NIVEL AVANZADO:
- Pantalla OLED para gráfico de carga
- Datalogger en SD card
- Control por Bluetooth
- MPPT (Maximum Power Point Tracking)
```

## 8. Tips de调试

```
PROBLEMA: Siempre muestra "Bateria ALTA"
SOLUCIÓN: Verificar conexiones del divisor, probar A0 con potenciómetro

PROBLEMA: MOSFET no conmuta
SOLUCIÓN: Resistor 10K entre Gate y GND, verificar que sea tipo N

PROBLEMA: Valores erráticos
SOLUCIÓN: Capacitor 100nF en A0 a GND, filtrar con promedio
```
