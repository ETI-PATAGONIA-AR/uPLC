# 18 - JUEGO DEL 100 (DADOS)

## 1. ¿Qué hace?
Juego de dados donde lanzas 3 dados. Si sacas 6, pierdes una vida.
Debes sumar exactamente entre 100 y 130 puntos para ganar.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- 1 botón

## 3. Conexiones de hardware

```
BOTÓN:
- I1=D2 → Botón para lanzar → 5V
- Resistencia 10K → GND

LCD I2C:
- A4 (SDA) y A5 (SCL)
```

## 4. ¿Cómo funciona?

```
// VARIABLES
score = 0
lives = 3

// AL INICIAR
AL INICIAR:
  score = 0
  lives = 3
  LCD → "Juguemos al 100!"
  LCD → "Tira los dados!"
  LCD → "PUNTOS:" + score
  LCD → "VIDAS:" + lives

// PARA SIEMPRE
PARA SIEMPRE:
  
  LCD → "Juguemos al 100!"
  LCD → "Tira los dados!"
  LCD → "PUNTOS:" + score
  LCD → "VIDAS:" + lives
  
  // Esperar botón
  MIENTRAS (D2 == LOW) esperar
  MIENTRAS (D2 == HIGH) esperar
  
  // Lanzar 3 dados
  D1 = ALEATORIO(1, 7)      // 1-6
  D2_ = ALEATORIO(1, 7)
  D3 = ALEATORIO(1, 7)
  
  // Mostrar dados
  LCD CLEAR
  LCD → "D1:" + D1 + " D2:" + D2_ + " D3:" + D3
  ESPERAR 1500 ms
  
  // Si no es 6, sumar puntos; si es 6, perder vida
  SI (D1 != 6) score = score + D1
  SINO lives = lives - 1
  
  SI (D2_ != 6) score = score + D2_
  SINO lives = lives - 1
  
  SI (D3 != 6) score = score + D3
  SINO lives = lives - 1
  
  // Verificar fin del juego
  SI (lives <= 0)
    LCD → "PERDISTE!"
    LCD → "Puntos:" + score
    MIENTRAS(1)            // Fin del juego
  
  SI (score > 130)
    LCD → "PERDISTE!"
    LCD → "Te pasaste de 130!"
    MIENTRAS(1)
  
  SI (score >= 100) Y (score <= 130)
    LCD → "GANASTE!"
    LCD → "Puntos:" + score
    MIENTRAS(1)
```

## 5. Bloques utilizados

```
CATEGORÍA: VARIABLES
- CREAR → score, lives
- ASIGNAR → Modificar valores

CATEGORÍA: ENTRADAS
- LEER_DIGITAL → Botón lanzar (D2)

CATEGORÍA: MATEMÁTICA
- ALEATORIO → Generar 1-6
- OPERACIÓN → Sumar puntos

CATEGORÍA: LÓGICA
- SI → Evaluar condiciones de juego
- Y → Combinar condiciones
- != → Diferente de

CATEGORÍA: LCD
- LCD TEXTO → Interfaz del juego
```

## 6. Valores de referencia

```
REGLAS DEL JUEGO:
- Lanzar 3 dados por turno
- Cada dado que NO sea 6 suma sus puntos
- Cada 6 = perder 1 vida
- 3 vidas iniciales
- Ganar: sumar entre 100 y 130 puntos
- Perder: quedarse sin vidas o pasar de 130

EJEMPLO:
- Dados: 3, 5, 2 → Suman 10 puntos (ningún 6)
- Dados: 6, 4, 1 → Pierdes 1 vida, sumas 5 puntos
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Cambiar objetivo (ej: 50-80 puntos)
- Cambiar número de vidas

NIVEL INTERMEDIO:
- Agregar dados con más caras
- Opción de plantar puntos

NIVEL AVANZADO:
- Juego para 2 jugadores
- Historial de partidas
- Dificultad variable
```

## 8. Tips de debug

```
PROBLEMA: Siempre saca 6
SOLUCIÓN: randomSeed(analogRead(0)) para aleatoriedad real

PROBLEMA: No detecta botón
SOLUCIÓN: Esperar a que suelte (mientras D2==HIGH)

PROBLEMA: Juego trabado
SOLUCIÓN: Revisar while(1) de fin de juego
```
