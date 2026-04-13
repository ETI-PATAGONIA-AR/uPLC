# 17 - JUEGO DE AZAR: DADOS

## 1. ¿Qué hace?
Simula el lanzamiento de dados al presionar un botón.
Genera un número aleatorio 1-6 y lo muestra en el LCD.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- Botón

## 3. Conexiones de hardware

```
BOTÓN:
- PIN D2 (Arduino) → Botón → 5V
- Resistencia 10K → GND

LCD I2C:
- PIN A4 (Arduino) → SDA del LCD
- PIN A5 (Arduino) → SCL del LCD
- 5V y GND

OPCIONAL: LED para animación
```

## 4. ¿Cómo funciona?

```
// AL INICIAR
AL INICIAR:
  LCD INIT
  LCD BACKLIGHT
  LCD CLEAR
  LCD → "Juego de Dados"
  LCD → "Presiona para lanzar"
  ESPERAR 2 segundos
  LCD CLEAR

// PARA SIEMPRE
PARA SIEMPRE:
  SI (D2 == HIGH)               // Botón presionado
    // Generar número aleatorio
    V0 = ALEATORIO(1, 6)        // Entre 1 y 6
    
    // Mostrar resultado
    LCD → "Dado: "
    LCD número → V0
    
    // Mostrar dado visual (ASCII art opcional)
    SEGÚN V0:
      1: LCD → "[   ] [ * ]"
      2: LCD → "[ * ] [ * ]"
      3: LCD → "[***]"
      ... etc
    
    ESPERAR 2500 ms
    LCD CLEAR
```

## 5. Bloques utilizados

```
CATEGORÍA: ENTRADAS
- LEER_DIGITAL → Leer botón (D2)

CATEGORÍA: MATEMÁTICA
- ALEATORIO → Generar número 1-6

CATEGORÍA: LÓGICA
- SI → Evaluar botón presionado
- SEGÚN → Mostrar según valor

CATEGORÍA: LCD
- LCD CLEAR → Limpiar pantalla
- LCD TEXTO → Mensajes
- LCD NUMERO → Mostrar dado
```

## 6. Desafíos propuestos

```
NIVEL BÁSICO:
- Agregar sonido al lanzar
- Cambiar tiempo de espera

NIVEL INTERMEDIO:
- Dos dados (suma de 2-12)
- Contador de victorias

NIVEL AVANZADO:
- Juego de Craps completo
- Dado visual con LEDs
- Estadísticas de lanzamientos
```

## 7. Tips de debug

```
PROBLEMA: Siempre sale el mismo número
SOLUCIÓN: En setup() agregar randomSeed(analogRead(0))

PROBLEMA: LCD se borra antes de ver resultado
SOLUCIÓN: delay(2500) suficiente para ver

PROBLEMA: Botón causa múltiples lanzamiento
SOLUCIÓN: Agregar anti-rebote o esperar a soltar
```
