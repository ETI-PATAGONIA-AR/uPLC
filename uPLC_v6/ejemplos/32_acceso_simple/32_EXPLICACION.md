# 32 - SISTEMA DE ACCESO SIMPLE

## 1. ¿Qué hace?
Sistema de cerradura electrónica con apertura por botón y timer
automático. Incluye sonido de confirmación y simulación con potenciómetro.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- Botón o keypad numérico
- Módulo relé o solenoide para cerradura
- Buzzer para sonidos

## 3. Conexiones de hardware

```
BOTÓN DE APERTURA:
- PIN D2 (Arduino) → Botón → 5V
- Resistencia 10K → GND
- O: Botón libre (N.O.)

CERRADURA:
- PIN D3 (Arduino) → IN del relé
- Relé: COM → Fuente, NO → Cerradura/solenoide
- Diodo 1N4007 en paralelo con solenoide (protección)

BUZZER:
- PIN D8 (Arduino) → Buzzer → GND
- O: Buzzer pasivo (genera tonos)

LCD I2C:
- PIN A4 (Arduino) → SDA del LCD
- PIN A5 (Arduino) → SCL del LCD

SIMULACIÓN (opcional):
- PIN A0 → Potenciómetro 10K (para probar sin botón físico)
```

## 4. ¿Cómo funciona?

```
// VARIABLES GLOBALES
puertaAbierta = FALSO
tiempoApertura = 0
TIEMPO_ABIERTO = 5000 ms (5 segundos)

// AL INICIAR
AL INICIAR:
  LCD → "SISTEMA DE ACCESO"
  LCD → "D2: Boton apertura"
  LCD → "D3: Cerradura"
  LCD → "Tono: Buzzer"
  ESPERAR 2000 ms
  LCD CLEAR
  puertaAbierta = FALSO

// PARA SIEMPRE
PARA SIEMPRE:
  
  // ══ SI PUERTA ABIERTA ══
  SI (puertaAbierta == VERDADERO)
    LCD → "*** PUERTA ABIERTA ***"
    
    segundosRestantes = (TIEMPO_ABIERTO - (millis() - tiempoApertura)) / 1000
    LCD → "Tiempo: "
    LCD número → segundosRestantes
    LCD → "s"
    
    // Verificar si terminó tiempo
    SI ((millis() - tiempoApertura) > TIEMPO_ABIERTO)
      puertaAbierta = FALSO
      APAGAR D3
      LCD → "PUERTA CERRADA"
  
  // ══ SI PUERTA CERRADA ══
  SINO
    LCD → "- CERRADO -"
    LCD → "Presione D2 para abrir"
  
  // ══ DETECTAR BOTÓN (anti-rebote) ══
  SI (D2 == HIGH) Y (ultimoEstado == FALSO) Y (puertaAbierta == FALSO)
    // ABRIR PUERTA
    puertaAbierta = VERDADERO
    tiempoApertura = millis()
    ENCENDER D3
    TONE(8, 880, 200)              // Primer pitido
    ESPERAR 100 ms
    TONE(8, 1320, 200)             // Segundo pitido
  
  ultimoEstado = (D2 == HIGH)
  
  // Indicador cerradura
  SI (D3 == HIGH)
    LCD → "CERRADURA: ABIERTA"
  SINO
    LCD → "CERRADURA: CERRADA"
  
  // ══ SIMULACIÓN CON POTENCIÓMETRO ══
  pot = LEER_ANALOGICO(A0)
  SI (pot > 900) Y (puertaAbierta == FALSO)
    puertaAbierta = VERDADERO
    tiempoApertura = millis()
    ENCENDER D3
    TONE(8, 660, 150)
```

## 5. Bloques utilizados

```
CATEGORÍA: VARIABLES
- CREAR variable "puertaAbierta" (lógico)
- CREAR variable "tiempoApertura" (número)
- CREAR variable "ultimoEstado" (lógico)
- ASIGNAR → Modificar estados

CATEGORÍA: ENTRADAS
- LEER_DIGITAL → Leer botón (D2)
- LEER_ANALOGICO → Leer potenciómetro (A0)

CATEGORÍA: MATEMÁTICA
- OPERACIÓN → segundos = tiempoRestante / 1000

CATEGORÍA: LÓGICA
- SI → Evaluar botón y timer
- Y → Combinar condiciones anti-rebote
- COMPARAR → Comparar estados

CATEGORÍA: SALIDAS
- ENCENDER/APAGAR → Cerradura (D3)

CATEGORÍA: LCD
- LCD TEXTO → Mensajes de estado

CATEGORÍA: SONIDO
- TONE → Generar pitidos de apertura
```

## 6. Valores de referencia

```
TIEMPOS:
- TIEMPO_ABIERTO = 5000ms (5 segundos)
- Cambiar según necesidad (ej: 10000 para puerta garaje)

TONOS:
- 880 Hz + 1320 Hz = Apertura exitosa
- 660 Hz = Apertura por potenciómetro
- Frecuencia más alta = más agudo

ANTI-REBOTE:
- Variable "ultimoEstado" memoriza estado anterior
- Solo reacciona cuando cambia de LOW→HIGH

SIMULACIÓN:
- Potenciómetro > 900 = misma acción que botón
- Útil para probar sin cableado
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Cambiar tiempo de apertura
- Diferentes tonos para diferentes eventos
- Agregar LED indicador

NIVEL INTERMEDIO:
- Código numérico con keypad
- Contador de intentos fallidos
- Registro de accesos

NIVEL AVANZADO:
- Teclado matricial 4x4
- RFID/NFC para abrir
- Registro en SD card
- Alerta por SMS
- Acceso con huella digital
```

## 8. Tips de debug

```
PROBLEMA: Puerta no abre
SOLUCIÓN: Verificar botón, probar potenciómetro (>900)

PROBLEMA: Puerta no cierra
SOLUCIÓN: Verificar timer, revisar variable "puertaAbierta"

PROBLEMA: Múltiples aperturas
SOLUCIÓN: Condición anti-rebote (ultimoEstado)

PROBLEMA: Sin sonido
SOLUCIÓN: Buzzer debe ser pasivo (2 pines), no zumbador
```
