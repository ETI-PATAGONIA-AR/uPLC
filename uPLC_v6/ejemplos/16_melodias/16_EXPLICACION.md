# 16 - MELODÍAS

## 1. ¿Qué hace?
Reproduce melodías predefinidas usando el buzzer cuando se presiona
un botón. Incluye "Cumpleaños" y melodías de Mario Bros.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- Buzzer pasivo
- Botón

## 3. Conexiones de hardware

```
BUZZER:
- PIN D8 (Arduino) → Positivo del buzzer
- GND → Negativo del buzzer

BOTÓN:
- PIN D2 (Arduino) → Botón → 5V
- Resistencia 10K → GND

LCD I2C:
- PIN A4 (Arduino) → SDA del LCD
- PIN A5 (Arduino) → SCL del LCD
- 5V y GND
```

## 4. ¿Cómo funciona?

```
// VARIABLES
int bday[] = {262,262,294,262,349,330,0,-1};
int mario[] = {659,659,0,659,0,523,659,784,0,392,-1};

// FUNCIÓN: Reproducir melodía
FUNCIÓN playMelody(melodia):
  PARA i=0 HASTA fin de melodía:
    SI (nota[i] == 0)
      NO_TONE(8)                 // Silencio
    SINO
      TONE(8, nota[i], 180)      // Reproducir nota
    ESPERAR 240 ms

// AL INICIAR
AL INICIAR:
  LCD INIT
  LCD CLEAR

// PARA SIEMPRE
PARA SIEMPRE:
  SI (D2 == HIGH)               // Botón presionado
    playMelody("birthday")
```

## 5. Bloques utilizados

```
CATEGORÍA: ENTRADAS
- LEER_DIGITAL → Leer botón (D2)

CATEGORÍA: FUNCIONES
- FUNCIÓN → Reproducir melodía
- PARÁMETRO → Nombre de melodía

CATEGORÍA: SONIDO
- TONE → Generar tono (frecuencia, duración)
- NO_TONE → Detener tono

CATEGORÍA: LCD
- LCD TEXTO → Mensaje (opcional)
```

## 6. Valores de referencia

```
FRECUENCIAS MUSICALES (Hz):
- DO4 = 262, RE4 = 294, MI4 = 330
- FA4 = 349, SOL4 = 392, LA4 = 440
- SI4 = 494, DO5 = 523, RE5 = 587
- MI5 = 659, FA5 = 698, SOL5 = 784

DURACIONES:
- Nota 0 = Silencio
- -1 = Fin de melodía
- Duración típica: 180-250ms
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Cambiar melodía por defecto
- Ajustar velocidad de reproducción

NIVEL INTERMEDIO:
- Seleccionar melodía con botones
- Agregar melodías nuevas

NIVEL AVANZADO:
- Teclado musical
- Grabar melodía
- Secuencia de luces con melodía
```

## 8. Tips de debug

```
PROBLEMA: Sin sonido
SOLUCIÓN: Buzzer debe ser PASIVO (2 pines), no zumbador

PROBLEMA: Melodía incorrecta
SOLUCIÓN: Verificar array de frecuencias

PROBLEMA: Notas cortadas
SOLUCIÓN: Ajustar delay entre notas
```
