# 07 - CONTROL VELOCIDAD MOTOR DC

## 1. ¿Qué hace?
Controla la velocidad de un motor DC usando PWM.
Usa potenciómetro para ajustar velocidad y botón para on/off.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- Motor DC 12V
- Módulo MOSFET o transistor
- Potenciómetro 10K
- Fuente de alimentación

## 3. Conexiones de hardware

```
MOTOR DC:
- PIN D3 (Arduino/PWM) → Gate MOSFET
- Drain MOSFET → Motor (+) → Fuente 12V
- Source MOSFET → GND
- Motor (-) → Fuente 12V

POTENCIÓMETRO:
- A0 → Centro del potenciómetro
- 5V y GND en extremos

BOTÓN:
- I1=D2 → Botón → 5V
- Resistencia 10K → GND

LCD I2C:
- A4 (SDA) y A5 (SCL)
```

## 4. ¿Cómo funciona?

```
// AL INICIAR
AL INICIAR:
  LCD → "CONTROL VELOCIDAD"
  LCD → "A0: Potenciometro"
  LCD → "I1: Encender/Apagar"
  LCD → "D3(PWM): Motor DC"
  ESPERAR 2000 ms
  LCD CLEAR

// PARA SIEMPRE
PARA SIEMPRE:
  
  // Leer potenciómetro (0-1023)
  velocidad = LEER_ANALOGICO(A0) / 10    // Convertir a 0-100%
  
  // Mostrar velocidad en LCD
  LCD → "Velocidad:"
  LCD número → velocidad
  LCD → "%"
  
  // Control del motor
  SI (D2 == HIGH)                        // Botón presionado
    // PWM: convertir 0-100% a 0-255
    pwm = (velocidad × 255) / 100
    analogWrite(D3, pwm)
    LCD → "MOTOR: ON"
  SINO
    analogWrite(D3, 0)                    // Motor apagado
    LCD → "MOTOR: OFF"
```

## 5. Bloques utilizados

```
CATEGORÍA: ENTRADAS
- LEER_ANALOGICO → Leer potenciómetro (A0)
- LEER_DIGITAL → Leer botón (D2)

CATEGORÍA: MATEMÁTICA
- OPERACIÓN → velocidad = ADC / 10
- OPERACIÓN → pwm = (vel × 255) / 100

CATEGORÍA: LÓGICA
- SI → Evaluar botón
- COMPARAR → Comparar estados

CATEGORÍA: SALIDAS
- analogWrite → Control PWM motor (D3)

CATEGORÍA: LCD
- LCD TEXTO → Mensajes de estado
```

## 6. Valores de referencia

```
POTENCIÓMETRO:
- Mínimo = 0 → Velocidad 0%
- Centro = 512 → Velocidad 50%
- Máximo = 1023 → Velocidad 100%

PWM:
- 0 = Motor apagado
- 127 = Media velocidad
- 255 = Velocidad máxima

NOTA: El botón activa/desactiva el motor, el potenciómetro ajusta velocidad.
```

## 7. Desafíos propíos

```
NIVEL BÁSICO:
- Agregar LED indicador de estado
- Cambiar pin PWM (D5, D6, D9)

NIVEL INTERMEDIO:
- Botón para invertir giro
- Indicador de velocidad con barras

NIVEL AVANZADO:
- Control de dirección con puente H
- Aceleración gradual
- Tacómetro para retroalimentación
```

## 8. Tips de debug

```
PROBLEMA: Motor no gira
SOLUCIÓN: Verificar MOSFET/transistor, motor consume mucha corriente

PROBLEMA: Motor gira sin presionar botón
SOLUCIÓN: Revisar lógica del if, verificar botón

PROBLEMA: Motor con zumbido
SOLUCIÓN: Frecuencia PWM muy baja, aumentar delay
```
