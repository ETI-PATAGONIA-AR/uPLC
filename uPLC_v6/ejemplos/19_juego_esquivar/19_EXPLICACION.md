# 19 - JUEGO ESQUIVAR

## 1. ¿Qué hace?
Juego tipo Space Invaders simple. Controlas un personaje en la
fila inferior y esquivas objetos que caen. Cada 5 objetos = nuevo nivel.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- 2 botones (izquierda/derecha)

## 3. Conexiones de hardware

```
BOTONES:
- I1=D2 → Girar izquierda
- I2=D4 → Girar derecha
- Botones → 5V, Resistencia 10K → GND

LCD I2C:
- A4 (SDA) y A5 (SCL)
```

## 4. ¿Cómo funciona?

```
// VARIABLES
jugando = 1
nivel = 0
jugadorX = 10
objetoX = 10
objetoY = 0
objetoViene = 0
contador = 0
velocidad = 3
vidas = 3

// AL INICIAR
AL INICIAR:
  LCD → "JUEGO ESQUIVAR"
  LCD → "I1=IZQ  I2=DER"
  LCD → "Presiona I1 para empezar"
  
  ESPERAR a que presione I1
  nivel = 1
  jugadorX = 10
  objetoX = 10
  objetoY = 0
  vidas = 3

// PARA SIEMPRE
PARA SIEMPRE:
  
  // Mover jugador
  SI (D2 == LOW)                    // Izquierda
    jugadorX = jugadorX - 1
    SI (jugadorX < 0) jugadorX = 0
  
  SI (D4 == LOW)                    // Derecha
    jugadorX = jugadorX + 1
    SI (jugadorX > 19) jugadorX = 19
  
  // Mover objeto
  objetoY = objetoY + 1
  
  // Cada 5 objetos, subir nivel
  SI (objetoY > 5)
    contador = contador + 1
    objetoY = 0
    objetoX = 10
    SI (contador == 5)
      contador = 0
      nivel = nivel + 1
      LCD → "NIVEL=" + nivel
      LCD → "VIDAS=" + vidas
      ESPERAR 2000 ms
  
  // Colisión
  SI (jugadorX == objetoX) Y (objetoY > 4)
    vidas = vidas - 1
    objetoY = 0
    SI (vidas == 0)
      LCD → "GAME OVER"
      LCD → "Nivel:" + nivel
      MIENTRAS(1)
    LCD → "OUCH! Vidas:" + vidas
    ESPERAR 1000 ms
  
  // Dibujar
  LCD → "N" + nivel + "P" + contador + "V" + vidas
  LCD fila 3, columna jugadorX → "█"
  
  ESPERAR 100 ms
```

## 5. Bloques utilizados

```
CATEGORÍA: VARIABLES
- CREAR → nivel, jugadorX, vidas, etc.
- ASIGNAR → Modificar posiciones

CATEGORÍA: ENTRADAS
- LEER_DIGITAL → Botones izquierda/derecha

CATEGORÍA: MATEMÁTICA
- OPERACIÓN → Incrementar contadores
- COMPARAR → Detectar colisiones

CATEGORÍA: LÓGICA
- SI → Evaluar colisiones y niveles
- Y → Combinar condiciones

CATEGORÍA: LCD
- LCD TEXTO → Interfaz del juego
```

## 6. Valores de referencia

```
PARÁMETROS DEL JUEGO:
- Ancho LCD: 20 columnas
- Posición inicial jugador: columna 10
- Velocidad objeto: 1 posición cada 100ms
- Nivel: sube cada 5 objetos
- Vidas iniciales: 3

COLISIÓN:
- Ocurre cuando jugadorX == objetoX Y objetoY > 4
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Cambiar velocidad de juego
- Ajustar número de vidas

NIVEL INTERMEDIO:
- Agregar puntuación por objetos esquivados
- Velocidad aumenta con nivel

NIVEL AVANZADO:
- Múltiples objetos simultáneos
- Disparos para destruir objetos
- Pantalla de inicio y game over
```

## 8. Tips de debug

```
PROBLEMA: Jugador se sale de pantalla
SOLUCIÓN: Verificar límites 0-19

PROBLEMA: Colisión no funciona
SOLUCIÓN: Revisar condiciones Y (and)

PROBLEMA: LCD lento
SOLUCIÓN: Minimizar prints, delay(100) es adecuado
```
