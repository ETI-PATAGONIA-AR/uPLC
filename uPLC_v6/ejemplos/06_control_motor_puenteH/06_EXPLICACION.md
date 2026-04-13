# 06 - ROBOT 2 MOTORES CON PUENTE H

## 1. ¿Qué hace?
Controla un robot con 2 motores DC usando doble puente H L298N.
Permite avanzar, retroceder y girar usando botones.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- Driver L298N (doble puente H)
- 2 motores DC 12V
- Fuente de alimentación 12V
- 4 botones

## 3. Conexiones de hardware

```
L298N MOTOR IZQUIERDO:
- D4 (IN1) → IN1 del L298
- D7 (IN2) → IN2 del L298
- D5 (PWM) → ENA del L298

L298N MOTOR DERECHO:
- D8 (IN3) → IN3 del L298
- D9 (IN4) → IN4 del L298
- D6 (PWM) → ENB del L298

POTENCIÓMETRO:
- A0 → Centro del potenciómetro

BOTONES:
- I1=D2 → Adelante
- I2=D4 → Atrás
- I3=D5 → Girar izquierda
- I4=D6 → Girar derecha

LCD I2C:
- A4 (SDA) y A5 (SCL)
```

## 4. ¿Cómo funciona?

```
// VARIABLE GLOBAL
velocidad = 150

// SUBPROGRAMA: Avanzar
SUBPROGRAMA motor_adelante():
  ESCRIBIR_DIGITAL(D4, HIGH)
  ESCRIBIR_DIGITAL(D7, LOW)
  ESCRIBIR_DIGITAL(D8, HIGH)
  ESCRIBIR_DIGITAL(D9, LOW)
  analogWrite(D5, velocidad)
  analogWrite(D6, velocidad)
  LCD → "ADELANTE"

// SUBPROGRAMA: Retroceder
SUBPROGRAMA motor_atras():
  ESCRIBIR_DIGITAL(D4, LOW)
  ESCRIBIR_DIGITAL(D7, HIGH)
  ESCRIBIR_DIGITAL(D8, LOW)
  ESCRIBIR_DIGITAL(D9, HIGH)
  analogWrite(D5, velocidad)
  analogWrite(D6, velocidad)
  LCD → "ATRAS"

// SUBPROGRAMA: Girar izquierda
SUBPROGRAMA motor_girar_izq():
  ESCRIBIR_DIGITAL(D4, LOW)
  ESCRIBIR_DIGITAL(D7, HIGH)
  ESCRIBIR_DIGITAL(D8, HIGH)
  ESCRIBIR_DIGITAL(D9, LOW)
  LCD → "GIRAR IZQ"

// SUBPROGRAMA: Girar derecha
SUBPROGRAMA motor_girar_der():
  ESCRIBIR_DIGITAL(D4, HIGH)
  ESCRIBIR_DIGITAL(D7, LOW)
  ESCRIBIR_DIGITAL(D8, LOW)
  ESCRIBIR_DIGITAL(D9, HIGH)
  LCD → "GIRAR DER"

// SUBPROGRAMA: Parar
SUBPROGRAMA motor_parar():
  ESCRIBIR_DIGITAL(D4, LOW)
  ESCRIBIR_DIGITAL(D7, LOW)
  ESCRIBIR_DIGITAL(D8, LOW)
  ESCRIBIR_DIGITAL(D9, LOW)
  analogWrite(D5, 0)
  analogWrite(D6, 0)
  LCD → "PARADO"

// AL INICIAR
AL INICIAR:
  velocidad = 150
  LCD → "ROBOT 2 MOTORES"
  LCD → "I1=ADELANTE I2=ATRAS"
  LCD → "I3=IZQ  I4=DER"
  ESPERAR 2000 ms

// PARA SIEMPRE
PARA SIEMPRE:
  velocidad = LEER_ANALOGICO(A0) / 10
  LCD → "Vel:"
  LCD número → velocidad
  
  SI (D2 == HIGH)
    motor_adelante()
  SINO SI (D4 == HIGH)
    motor_atras()
  SINO SI (D5 == HIGH)
    motor_girar_izq()
  SINO SI (D6 == HIGH)
    motor_girar_der()
  SINO
    motor_parar()
```

## 5. Bloques utilizados

```
CATEGORÍA: SUBPROGRAMAS
- SUBPROGRAMA → Definir funciones reutilizables
- LLAMAR → Ejecutar subprograma

CATEGORÍA: ENTRADAS
- LEER_ANALOGICO → Potenciómetro velocidad (A0)
- LEER_DIGITAL → Botones de control (D2,D4,D5,D6)

CATEGORÍA: SALIDAS
- ESCRIBIR_DIGITAL → Controlar IN1-IN4 del L298
- analogWrite → Controlar velocidad PWM (D5,D6)

CATEGORÍA: LCD
- LCD TEXTO → Mostrar estado del robot
```

## 6. Valores de referencia

```
LÓGICA L298N:
- IN1=HIGH, IN2=LOW → Giro horario (adelante motor izq)
- IN1=LOW, IN2=HIGH → Giro antihorario (atrás motor izq)
- IN1=LOW, IN2=LOW → Parada

VELOCIDAD:
- 0-100 del potenciómetro → 0-255 PWM
- Velocidad inicial: 150

NOTA: Un motor gira al revés, invertir sus cables.
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Cambiar velocidad inicial
- Agregar botón de parada de emergencia

NIVEL INTERMEDIO:
- Control por infrarrojo
- Añadir sensor ultrasonido para evitar obstáculos
- Control de velocidad diferente por motor

NIVEL AVANZADO:
- Control por Bluetooth
- Seguidor de línea
- Navegación autónoma
```

## 8. Tips de debug

```
PROBLEMA: Robot no avanza recto
SOLUCIÓN: Ajustar velocidad de cada motor por separado

PROBLEMA: Un motor no gira
SOLUCIÓN: Verificar conexiones IN1/IN2, puede estar mal cableado

PROBLEMA: Motores vibran pero no giran
SOLUCIÓN: Voltaje insuficiente, verificar fuente
```
