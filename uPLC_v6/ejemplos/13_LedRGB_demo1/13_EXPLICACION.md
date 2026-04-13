# 13 - LED RGB DEMO

## 1. ¿Qué hace?
Controla un LED RGB mostrando diferentes colores en secuencia.
Demuestra el uso de PWM para mezclar colores.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- LED RGB de ánodo común o cátodo común
- 3 resistencias 220Ω

## 3. Conexiones de hardware

```
LED RGB (cátodo común):
- PIN D5 → Resistencia 220Ω → Rojo (R)
- PIN D6 → Resistencia 220Ω → Verde (G)
- PIN D9 → Resistencia 220Ω → Azul (B)
- GND → Cátodo común del LED

LED RGB (ánodo común):
- 5V → Ánodo común
- PIN D5 → R + Resistencia 220Ω
- PIN D6 → G + Resistencia 220Ω
- PIN D9 → B + Resistencia 220Ω

LCD I2C:
- A4 (SDA) y A5 (SCL)
```

## 4. ¿Cómo funciona?

```
// MAPEO: 0-100% → 0-255 PWM
mapear(valor):
  R = constrain(map(valor, 0, 100, 0, 255), 0, 255)
  return R

// AL INICIAR
AL INICIAR:
  LCD INIT
  LCD BACKLIGHT
  LCD CLEAR
  // Iniciar con blanco
  analogWrite(D5, 255)
  analogWrite(D6, 255)
  analogWrite(D9, 255)

// PARA SIEMPRE
PARA SIEMPRE:
  
  LCD → "ROJO"
  analogWrite(D5, 255)    // Rojo al máximo
  analogWrite(D6, 0)      // Verde apagado
  analogWrite(D9, 0)      // Azul apagado
  ESPERAR 1000 ms
  
  LCD → "VERDE"
  analogWrite(D5, 0)
  analogWrite(D6, 255)
  analogWrite(D9, 0)
  ESPERAR 1000 ms
  
  LCD → "AZUL"
  analogWrite(D5, 0)
  analogWrite(D6, 0)
  analogWrite(D9, 255)
  ESPERAR 1000 ms
  
  LCD → "CIAN"
  analogWrite(D5, 0)
  analogWrite(D6, 255)
  analogWrite(D9, 255)
  ESPERAR 1000 ms
  
  LCD → "MAGENTA"
  analogWrite(D5, 255)
  analogWrite(D6, 0)
  analogWrite(D9, 255)
  ESPERAR 1000 ms
  
  LCD → "AMARILLO"
  analogWrite(D5, 255)
  analogWrite(D6, 255)
  analogWrite(D9, 0)
  ESPERAR 1000 ms
  
  LCD → "BLANCO"
  analogWrite(D5, 255)
  analogWrite(D6, 255)
  analogWrite(D9, 255)
  ESPERAR 1000 ms
  
  LCD → "APAGADO"
  analogWrite(D5, 0)
  analogWrite(D6, 0)
  analogWrite(D9, 0)
  ESPERAR 500 ms
```

## 5. Bloques utilizados

```
CATEGORÍA: SALIDAS
- analogWrite → Control PWM de cada color (D5,D6,D9)

CATEGORÍA: MATEMÁTICA
- map() → Escalar valores
- constrain() → Limitar rango

CATEGORÍA: TIEMPO
- ESPERAR_ms → Pausas entre colores

CATEGORÍA: LCD
- LCD TEXTO → Mostrar color actual
```

## 6. Valores de referencia

```
COLORES Y VALORES RGB:
- ROJO     = (255, 0, 0)
- VERDE    = (0, 255, 0)
- AZUL     = (0, 0, 255)
- CIAN     = (0, 255, 255)
- MAGENTA  = (255, 0, 255)
- AMARILLO = (255, 255, 0)
- BLANCO   = (255, 255, 255)
- NEGRO    = (0, 0, 0)

NOTA: Para ánodo común, invertir valores (255-valor).
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Cambiar velocidad de transición
- Agregar más colores

NIVEL INTERMEDIO:
- Fade suave entre colores
- Control con potenciómetros (mezcla manual)

NIVEL AVANZADO:
- Arcoíris con transición gradual
- Control por infrarrojo
- Luz ambiental que sigue música
```

## 8. Tips de debug

```
PROBLEMA: Color incorrecto
SOLUCIÓN: Verificar si LED es ánodo o cátodo común

PROBLEMA: LED siempre apagado
SOLUCIÓN: Resistencias necesarias, verificar conexiones

PROBLEMA: Un color no funciona
SOLUCIÓN: Verificar pin PWM correspondiente (D5=R, D6=G, D9=B)
```
