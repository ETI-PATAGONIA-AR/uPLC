# 08 - CONTROL DE VARIOS SERVOS

## 1. ¿Qué hace?
Controla múltiples servomotores usando potenciómetros.
Cada potenciómetro controla un servo.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- 2-3 servomotores SG90
- 2-3 potenciómetros 10K

## 3. Conexiones de hardware

```
SERVOMOTOR 1:
- PIN D3 (Q6) → Signal del servo
- 5V → VCC del servo
- GND → GND del servo

SERVOMOTOR 2:
- PIN D5 → Signal del servo (configurar como salida)

SERVOMOTOR 3:
- PIN D6 → Signal del servo (configurar como salida)

POTENCIÓMETRO 1:
- A0 → Centro del potenciómetro
- 5V y GND en extremos

POTENCIÓMETRO 2:
- A1 → Centro del potenciómetro

LCD I2C:
- A4 (SDA) y A5 (SCL)
```

## 4. ¿Cómo funciona?

```
// AL INICIAR
AL INICIAR:
  LCD INIT
  LCD → "Control de Servos"
  ESPERAR 2 segundos
  LCD CLEAR

// PARA SIEMPRE
PARA SIEMPRE:
  // Leer potenciómetros
  valor1 = LEER_ANALOGICO(A0)
  valor2 = LEER_ANALOGICO(A1)
  
  // Convertir a ángulo (0-180°)
  angulo1 = (valor1 × 180) / 1023
  angulo2 = (valor2 × 180) / 1023
  
  // Mover servos
  SERVO1 → angulo1
  SERVO2 → angulo2
  
  // Mostrar en LCD
  LCD → "S1:"
  LCD número → angulo1
  LCD → "°"
  LCD → "S2:"
  LCD número → angulo2
  LCD → "°"
  
  ESPERAR 100 ms
```

## 5. Bloques utilizados

```
CATEGORÍA: ENTRADAS
- LEER_ANALOGICO → Leer potenciómetros (A0, A1)

CATEGORÍA: MATEMÁTICA
- OPERACIÓN → angulo = (valor × 180) / 1023

CATEGORÍA: SALIDAS
- SERVO_WRITE → Mover servo a ángulo

CATEGORÍA: LCD
- LCD TEXTO → Mostrar ángulos
```

## 6. Valores de referencia

```
SERVO SG90:
- Ángulo: 0° a 180°
- Control: Ancho de pulso 1ms a 2ms
- Frecuencia: 50Hz (20ms período)

POTENCIÓMETRO:
- Mínimo: 0 → 0°
- Centro: 511 → 90°
- Máximo: 1023 → 180°
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Usar solo un servo
- Cambiar velocidad de actualización

NIVEL INTERMEDIO:
- Límites de movimiento (ej: 30° a 150°)
- Botón para centrar servo

NIVEL AVANZADO:
- Control de brazo robótico
- Secuencias pregrabadas
- Sensor de posición
```

## 8. Tips de debug

```
PROBLEMA: Servo no se mueve
SOLUCIÓN: Verificar alimentación (5V), los servos consumen mucho

PROBLEMA: Servo vibra
SOLUCIÓN: Señal incorrecta, verificar conexión de signal

PROBLEMA: Ángulo incorrecto
SOLUCIÓN: Calibrar valores mínimos y máximos
```
