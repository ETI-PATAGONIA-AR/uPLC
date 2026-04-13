# 03 - CONTADOR EN LCD

## 1. ¿Qué hace?
Muestra un contador que incrementa cada segundo en el LCD.
Aprende a usar variables y el display.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- (Opcional) Pantalla LCD 16x2

## 3. Conexiones de hardware

```
LCD I2C:
- PIN A4 (Arduino) → SDA del LCD
- PIN A5 (Arduino) → SCL del LCD
- 5V → VCC del LCD
- GND → GND del LCD

DIRECCIÓN I2C: 0x27 (común) o 0x3F
```

## 4. ¿Cómo funciona?

```
// VARIABLES
contador = 0

// AL INICIAR
AL INICIAR:
  LCD INIT
  LCD CLEAR
  LCD → "Contador iniciado"

// PARA SIEMPRE
PARA SIEMPRE:
  LCD → "Numero: "
  LCD número → contador
  contador = contador + 1
  SI (contador > 9999)
    contador = 0
  ESPERAR 1000 ms
```

## 5. Bloques utilizados

```
CATEGORÍA: VARIABLES
- CREAR variable "contador"
- ASIGNAR → Incrementar valor

CATEGORÍA: MATEMÁTICA
- OPERACIÓN → contador + 1

CATEGORÍA: LCD
- LCD CLEAR → Limpiar pantalla
- LCD TEXTO → Mostrar mensaje
- LCD NUMERO → Mostrar valor

CATEGORÍA: LÓGICA
- SI → Reiniciar contador
```

## 6. Desafíos propuestos

```
NIVEL BÁSICO:
- Cambiar velocidad de conteo
- Mostrar contador en otra posición

NIVEL INTERMEDIO:
- Contador de pulsaciones de botón
- Contador regresivo

NIVEL AVANZADO:
- Cronómetro con Start/Stop
- Contador de eventos con timestamp
```

## 7. Tips de debug

```
PROBLEMA: LCD no muestra nada
SOLUCIÓN: Verificar conexiones I2C, dirección correcta (0x27)

PROBLEMA: Texto se superpone
SOLUCIÓN: Usar LCD CLEAR antes de cada mensaje
```
