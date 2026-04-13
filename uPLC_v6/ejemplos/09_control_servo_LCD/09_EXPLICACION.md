# 09 - CONTROL SERVO CON LCD

## 1. ¿Qué hace?
Controla un servomotor usando un potenciómetro y muestra el ángulo
en el LCD con barra visual. Incluye botón para centrar.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- Servomotor SG90
- Potenciómetro 10K

## 3. Conexiones de hardware

```
SERVOMOTOR:
- PIN D3 (Arduino) → Signal del servo
- 5V → VCC del servo
- GND → GND del servo

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
  LCD INIT
  LCD BACKLIGHT
  LCD CLEAR
  SERVO.attach(D3)
  LCD → "SERVO + LCD + POT"
  LCD → "A0: Controla angulo"
  LCD → "I1: Centro (90)"
  LCD → "D3: Servo motor"
  ESPERAR 2000 ms
  LCD CLEAR
  SERVO.write(90)                   // Centrar servo

// PARA SIEMPRE
PARA SIEMPRE:
  
  // Leer potenciómetro y convertir a ángulo
  angulo = LEER_ANALOGICO(A0) / 6    // 0-1023 → 0-170 ≈ 0-180
  
  // Mover servo
  SERVO.write(angulo)
  
  // Mostrar ángulo
  LCD → "Angulo: "
  LCD número → angulo
  
  // Barra de progreso
  LCD → "["
  pos = angulo / 9                   // Escalar a 20 caracteres
  PARA i=0 HASTA pos: LCD → "="
  PARA i=pos HASTA 20: LCD → " "
  LCD → "]"
  
  // Botón para centrar
  SI (D2 == HIGH)
    SERVO.write(90)
    LCD → "CENTRADO!"
  SINO
    LCD → "            "

// MOSTRAR JOYSTICK
LCD → "POT:"
nivel = LEER_ANALOGICO(A0) / 51      // 0-20
PARA i=0 HASTA nivel: LCD → "*"
```

## 5. Bloques utilizados

```
CATEGORÍA: ENTRADAS
- LEER_ANALOGICO → Leer potenciómetro (A0)
- LEER_DIGITAL → Leer botón (D2)

CATEGORÍA: MATEMÁTICA
- OPERACIÓN → angulo = ADC / 6

CATEGORÍA: SALIDAS
- SERVO.attach → Configurar pin de servo
- SERVO.write → Mover a ángulo

CATEGORÍA: LCD
- LCD TEXTO → Mensajes y barra visual
```

## 6. Valores de referencia

```
SERVO SG90:
- Ángulo mínimo: 0°
- Ángulo centro: 90°
- Ángulo máximo: 180°
- Ancho de pulso: 1ms a 2ms

POTENCIÓMETRO:
- Mínimo = 0 → 0°
- Centro = 512 → 85° ≈ 90°
- Máximo = 1023 → 170°

CÁLCULO:
- angulo = ADC / 6 → 1023/6 ≈ 170°
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Cambiar rango de ángulo (ej: 20° a 160°)
- Agregar límites de movimiento

NIVEL INTERMEDIO:
- Dos servos controlados por separado
- Botón para guardar posiciones

NIVEL AVANZADO:
- Brazo robótico con múltiples servos
- Secuencias pregrabadas
- Control por infrarrojo
```

## 8. Tips de debug

```
PROBLEMA: Servo vibra o tiembla
SOLUCIÓN: Verificar alimentación (5V estable), señal correcta

PROBLEMA: Servo no llega a 180°
SOLUCIÓN: Algunos servos mecánicamente limitados, ajustar ángulo máximo

PROBLEMA: Ángulo incorrecto
SOLUCIÓN: Calibrar con map(ADC, 0, 1023, 0, 180)
```
