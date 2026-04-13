# 21 - ALARMA DE DISTANCIA

## 1. ¿Qué hace?
Usa sensor ultrasónico para medir distancia. Enciende alarma
cuando algo está demasiado cerca.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- Sensor ultrasonido HC-SR04
- LED o buzzer para alarma

## 3. Conexiones de hardware

```
HC-SR04:
- PIN D2 (Arduino) → TRIG del sensor
- PIN D4 (Arduino) → ECHO del sensor
- 5V → VCC del sensor
- GND → GND del sensor

ALARMA:
- PIN D13 (Q1) → LED/Buzzer

LCD I2C:
- A4 (SDA) y A5 (SCL)
```

## 4. ¿Cómo funciona?

```
// FUNCIÓN: Leer distancia ultrasónica
FUNCIÓN leerDistancia(trig, echo):
  ESCRIBIR_DIGITAL(trig, LOW)
  ESPERAR 2 microsegundos
  ESCRIBIR_DIGITAL(trig, HIGH)
  ESPERAR 10 microsegundos
  ESCRIBIR_DIGITAL(trig, LOW)
  
  duracion = pulseIn(echo, HIGH, 30000)
  distancia = duracion / 58         // Convertir a cm
  RETORNAR distancia

// AL INICIAR
AL INICIAR:
  LCD CLEAR

// PARA SIEMPRE
PARA SIEMPRE:
  
  // Leer distancia
  distancia = leerDistancia(D2, D4)
  
  LCD → "Dist:" + distancia
  
  // Alarma si muy cerca
  SI (distancia < 20)
    ENCENDER Q1                    // Alarma ON
  SINO
    APAGAR Q1                      // Alarma OFF
  
  ESPERAR 500 ms
```

## 5. Bloques utilizados

```
CATEGORÍA: FUNCIONES
- FUNCIÓN → Leer distancia
- RETORNAR → Devolver valor

CATEGORÍA: ENTRADAS
- ESCRIBIR_DIGITAL → Trigger del sensor
- pulseIn → Leer eco

CATEGORÍA: MATEMÁTICA
- OPERACIÓN → distancia = duracion / 58

CATEGORÍA: LÓGICA
- SI → Comparar con umbral
- < → Menor que

CATEGORÍA: SALIDAS
- ENCENDER/APAGAR → Alarma (Q1)

CATEGORÍA: LCD
- LCD TEXTO → Mostrar distancia
```

## 6. Valores de referencia

```
HC-SR04:
- Rango: 2cm a 400cm
- Precisión: ±3mm
- Ángulo: 15°

FÓRMULA:
- duracion / 58 = distancia en cm
- duracion / 148 = distancia en pulgadas

UMBRAL:
- < 20cm = Alarma encendida
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Cambiar distancia de activación
- Agregar buzzer

NIVEL INTERMEDIO:
- Diferentes tonos según distancia
- Histéresis

NIVEL AVANZADO:
- Radar 360° con servo
- Seguimiento de objeto
- Registro de eventos
```

## 8. Tips de debug

```
PROBLEMA: Distancia siempre 0
SOLUCIÓN: Verificar conexiones ECHO/TRIG

PROBLEMA: Distancia errática
SOLUCIÓN: pulseIn timeout puede ser muy corto

PROBLEMA: Sensor no responde
SOLUCIÓN: 5V suficiente, verificar GND común
```
