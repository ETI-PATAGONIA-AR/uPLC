# 23 - SUBPROGRAMAS

## 1. ¿Qué hace?
Demuestra el uso de subprogramas (funciones) para modularizar código.
Control de servo + toggle PWM en subprogramas separados.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- Servomotor SG90
- Potenciómetro 10K
- LED o carga PWM

## 3. Conexiones de hardware

```
SERVOMOTOR:
- D3 → Signal del servo
- 5V y GND

POTENCIÓMETROS:
- A0 → Control de ángulo del servo
- A1 → Control de velocidad PWM

BOTÓN:
- I1=D2 → Toggle para PWM

SALIDA PWM:
- D5 → LED o MOSFET para PWM

LCD I2C:
- A4 (SDA) y A5 (SCL)
```

## 4. ¿Cómo funciona?

```
// VARIABLES GLOBALES
estadoPWM = 0
ultimoEstadoBoton = 0

// ══ SUBPROGRAMA: Controlar Servo ══
SUBPROGRAMA controlar_servo():
  angulo = LEER_ANALOGICO(A0) / 6    // 0-1023 → 0-170
  SERVO.write(angulo)
  LCD → "SERVO: D3"
  LCD → "Ang:" + angulo

// ══ SUBPROGRAMA: Toggle PWM ══
SUBPROGRAMA toggle_pwm():
  // Detectar presión de botón (solo una vez)
  SI (D2 == LOW) Y (ultimoEstadoBoton == 0)
    estadoPWM = SI(estadoPWM==0) ENTONCES 1 SINO 0
    ultimoEstadoBoton = 1
  
  SI (D2 == HIGH)
    ultimoEstadoBoton = 0
  
  // Control PWM si está activo
  SI (estadoPWM == 1)
    valorPWM = LEER_ANALOGICO(A1) / 4    // 0-1023 → 0-255
    analogWrite(D5, valorPWM)
    LCD → "PWM D5: ON"
    LCD → "Valor:" + valorPWM
  SINO
    analogWrite(D5, 0)
    LCD → "PWM D5: OFF"
    LCD → "              "

// AL INICIAR
AL INICIAR:
  LCD INIT
  LCD BACKLIGHT
  LCD CLEAR
  SERVO.attach(D3)
  SERVO.write(90)                    // Centrar
  LCD → "SUBPROGRAMAS"
  LCD → "I1: Toggle PWM D5"
  LCD → "A0: Servo D3"
  LCD → "A1: Velocidad PWM"
  ESPERAR 2500 ms
  LCD CLEAR
  estadoPWM = 0
  ultimoEstadoBoton = 0

// PARA SIEMPRE
PARA SIEMPRE:
  controlar_servo()                   // Llamar subprograma 1
  toggle_pwm()                       // Llamar subprograma 2
  ESPERAR 10 ms
```

## 5. Bloques utilizados

```
CATEGORÍA: SUBPROGRAMAS
- SUBPROGRAMA → Definir función con nombre
- LLAMAR → Ejecutar subprograma en loop

CATEGORÍA: VARIABLES
- CREAR → estadoPWM, ultimoEstadoBoton
- ASIGNAR → Modificar valores

CATEGORÍA: ENTRADAS
- LEER_ANALOGICO → Potenciómetros (A0, A1)
- LEER_DIGITAL → Botón (D2)

CATEGORÍA: SALIDAS
- SERVO.write → Mover servo
- analogWrite → Control PWM

CATEGORÍA: LCD
- LCD TEXTO → Mostrar estados
```

## 6. Ventajas de subprogramas

```
MODULARIDAD:
- Código organizado en bloques
- Fácil de entender
- Reutilizable

DEPURACIÓN:
- Aislar problemas por función
- Testear individualmente

MANTENIMIENTO:
- Cambios locales no afectan resto
- Código más limpio
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Agregar más funciones
- Cambiar pins

NIVEL INTERMEDIO:
- Subprograma para leer sensores
- Subprograma para mostrar LCD

NIVEL AVANZADO:
- Pasar parámetros a funciones
- Retornar valores
- Bibliotecas propias
```

## 8. Tips de debug

```
PROBLEMA: Toggle no funciona
SOLUCIÓN: Variable ultimoEstadoBoton necesaria para anti-rebote

PROBLEMA: Variables no mantienen valor
SOLUCIÓN: Deben ser globales, no locales

PROBLEMA: LCD saturado
SOLUCIÓN: Solo mostrar función activa, no ambas
```
