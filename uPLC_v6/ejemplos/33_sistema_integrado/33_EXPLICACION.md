# 33 - SISTEMA INTEGRADO AGRÍCOLA

## 1. ¿Qué hace?
Combina los sistemas de riego, tanque y luz en un solo sistema
integrado con modo automático y manual. Ideal para huerta doméstica.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- Sensor de humedad del suelo
- Sensor de luz (LDR)
- Sensor de nivel (potenciómetro)
- Módulo relé o MOSFET para bomba
- Módulo relé para válvula
- Bomba, válvula, luz LED
- Botón para cambiar modo

## 3. Conexiones de hardware

```
SENSORES:
- A0: Sensor de humedad suelo
- A1: LDR (sensor de luz)
- A2: Potenciómetro (nivel tanque)
- D2: Botón cambio modo

ACTUADORES:
- D3: Bomba de riego
- D4: Válvula de tanque
- D5: Luz auxiliar LED

LCD I2C:
- PIN A4 (Arduino) → SDA del LCD
- PIN A5 (Arduino) → SCL del LCD

NOTA: Este ejemplo usa 3 entradas ADC y 3 salidas digitales.
```

## 4. ¿Cómo funciona?

```
// VARIABLES GLOBALES
modoAutomatico = VERDADERO
bombaRiego = FALSO
valvulaTanque = FALSO
luzAux = FALSO

// CONSTANTES
HUMEDAD_MIN = 30     // Por debajo: regar
LUZ_DIA = 500        // Umbral LDR

// AL INICIAR
AL INICIAR:
  LCD → "SISTEMA INTEGRADO"
  LCD → "Agricola Completo"
  LCD → "Riego+Tanque+Luz"
  ESPERAR 2500 ms
  LCD CLEAR

// PARA SIEMPRE
PARA SIEMPRE:
  
  // Leer sensores
  humedad = 100 - (LEER_ANALOGICO(A0) × 100 / 1023)
  luz = LEER_ANALOGICO(A1)
  nivelTanque = LEER_ANALOGICO(A2) × 100 / 1023
  
  SI (luz > LUZ_DIA)
    esDia = VERDADERO
  SINO
    esDia = FALSO
  
  // Cambio de modo con botón
  SI (D2 == HIGH)
    modoAutomatico = NO modoAutomatico
    ESPERAR 300 ms
  
  // Mostrar modo
  SI (modoAutomatico)
    LCD → "AUTO:"
  SINO
    LCD → "MANUAL:"
  LCD → (esDia ? "DIA" : "NOCHE")
  
  // ══ RIEGO ══
  SI (modoAutomatico)
    SI (humedad < HUMEDAD_MIN) Y (esDia)
      bombaRiego = VERDADERO
      LCD → "RIEGO: ON "
    SINO
      bombaRiego = FALSO
      LCD → "RIEGO: OFF"
  SINO
    // Modo manual: D4 controla bomba
    SI (D4 == HIGH)
      bombaRiego = VERDADERO
      LCD → "RIEGO: ON "
    SINO
      bombaRiego = FALSO
      LCD → "RIEGO: OFF"
  
  // ══ TANQUE ══
  SI (nivelTanque < 30)
    valvulaTanque = VERDADERO
    LCD → "TANQUE:FILL"
  SINO SI (nivelTanque > 80)
    valvulaTanque = FALSO
    LCD → "TANQUE:FULL"
  SINO
    LCD → "TANQUE:    "
  
  // ══ LUZ ══
  SI (NO esDia)
    luzAux = VERDADERO
    LCD → "LUZ: ON "
  SINO
    luzAux = FALSO
    LCD → "LUZ: OFF"
  
  // Mostrar valores
  LCD → "Hum:"
  LCD número → humedad
  LCD → "%"
  LCD → "Niv:"
  LCD número → nivelTanque
  LCD → "%"
  
  // Aplicar salidas
  ESCRIBIR_DIGITAL(D3, bombaRiego)
  ESCRIBIR_DIGITAL(D4, valvulaTanque)
  ESCRIBIR_DIGITAL(D5, luzAux)
```

## 5. Bloques utilizados

```
CATEGORÍA: ENTRADAS
- LEER_ANALOGICO → Sensores (A0, A1, A2)
- LEER_DIGITAL → Botón modo (D2)

CATEGORÍA: VARIABLES
- CREAR variables de estado
- ASIGNAR → Modificar según lógica

CATEGORÍA: MATEMÁTICA
- OPERACIÓN → Convertir ADC a porcentaje
- OPERACIÓN → Escala 0-100

CATEGORÍA: LÓGICA
- SI/SINO SI → Evaluar sensores y modo
- Y → Combinar condiciones (humedad Y día)
- NO → Invertir modo

CATEGORÍA: SALIDAS
- ESCRIBIR_DIGITAL → Controlar D3, D4, D5

CATEGORÍA: LCD
- LCD TEXTO → Mensajes de estado
- LCD NUMERO → Valores de sensores
```

## 6. Valores de referencia

```
SENSORES:
- A0 (Humedad): 0-100% según sensor
- A1 (Luz): >500 = día, <500 = noche
- A2 (Nivel): 0-100% del potenciómetro

ACTUADORES:
- D3 (Bomba): ON si seco Y día
- D4 (Válvula): ON si nivel < 30%
- D5 (Luz): ON si es noche

LÓGICA DE RIEGO:
- Solo riega de día (evita evaporación nocturna)
- Solo riega si está seco

LÓGICA DE TANQUE:
- Llenar si < 30%
- Detener si > 80%
- Mantener entre 30-80%

NOTA: En producción, usar sensores reales, no potenciómetro.
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Ajustar umbrales según plantas
- Agregar LEDs indicadores
- Cambiar sensores por reales

NIVEL INTERMEDIO:
- Agregar sensor de lluvia
- Temporizadores por hora
- Historial en LCD

NIVEL AVANZADO:
- Integrar con Weather API
- Datalogger completo
- Control por teléfono
- Riego por goteo con electroválvulas
- Fertirriego automático
```

## 8. Tips de debug

```
PROBLEMA: Riego de noche
SOLUCIÓN: Verificar esDia = (luz > 500)

PROBLEMA: Sistema no cambia modo
SOLUCIÓN: delay(300) evita rebotes del botón

PROBLEMA: Valores erráticos
SOLUCIÓN: Agregar filtros/promedio en sensores

PROBLEMA: Válvula no cierra
SOLUCIÓN: Verificar lógica de nivel, umbrales 30/80
```
