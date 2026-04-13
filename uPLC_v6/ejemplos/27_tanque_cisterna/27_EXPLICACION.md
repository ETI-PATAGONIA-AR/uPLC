# 27 - TANQUE + CISTERNA

## 1. ¿Qué hace?
Control automático de bomba que llena un tanque elevado desde una
cisterna inferior, usando boyas para detectar niveles.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- 3 boyas/flotadores de nivel
- Módulo relé para bomba
- Bomba de agua 12V/220V

## 3. Conexiones de hardware

```
BOYAS (entrada digital con pull-down):
- BOYA CISTERNA: D2 → Signal, 10K a GND, 5V
- BOYA TANQUE BAJO: D4 → Signal, 10K a GND, 5V
- BOYA TANQUE ALTO: D6 → Signal, 10K a GND, 5V

BOMBA:
- PIN D3 (Arduino) → IN del relé
- Relé: COM → Fuente, NO → Bomba
- 10K resistor en Gate si usa MOSFET

LCD I2C:
- PIN A4 (Arduino) → SDA del LCD
- PIN A5 (Arduino) → SCL del LCD

SÍMBOLO:
- BOYA = Interruptor que cierra al subir el nivel
- Cuando flota arriba = 1 (HIGH)
- Cuando flota abajo = 0 (LOW)
```

## 4. ¿Cómo funciona?

```
// AL INICIAR
AL INICIAR:
  LCD → "TANQUE + CISTERNA"
  LCD → "D2=Boya cisterna"
  LCD → "D4=Tanque bajo"
  LCD → "D6=Tanque alto"
  ESPERAR 2000 ms
  LCD CLEAR

// PARA SIEMPRE
PARA SIEMPRE:
  
  // Mostrar estado de sensores
  LCD → "Cis:"
  SI (D2 == HIGH) LCD → "SI" SINO LCD → "NO"
  LCD → "TqB:"
  SI (D4 == HIGH) LCD → "SI" SINO LCD → "NO"
  LCD → "TqA:"
  SI (D6 == HIGH) LCD → "SI" SINO LCD → "NO"
  
  // Mostrar estado de bomba
  LCD → "Bomba:"
  SI (D3 == HIGH) LCD → "ON " SINO LCD → "OFF"
  
  // ══ SEGURIDAD: Sin agua en cisterna → PARAR ══
  SI (D2 == LOW)
    APAGAR D3                              // Bomba OFF
    LCD → "SIN AGUA CISTERNA!"
    LCD → "Bomba detenida"
  
  SINO
    // ══ Tanque lleno → PARAR ══
    SI (D6 == HIGH)
      APAGAR D3
      LCD → "TANQUE LLENO"
      LCD → "Bomba apagada"
    
    // ══ Tanque bajo + hay agua → LLENAR ══
    SINO SI (D4 == HIGH)
      ENCENDER D3
      LCD → "LLENANDO TANQUE"
      LCD → "Bomba encendida"
    
    // ══ Zona media → esperar ══
    SINO
      LCD → "ESPERANDO..."
```

## 5. Bloques utilizados

```
CATEGORÍA: ENTRADAS
- LEER_DIGITAL → Leer boyas (D2, D4, D6)

CATEGORÍA: LÓGICA
- SI → Evaluar nivel de cisterna
- SINO SI → Evaluar nivel alto tanque
- SINO SI → Evaluar nivel bajo tanque
- COMPARAR → D2==HIGH, D6==HIGH, D4==HIGH

CATEGORÍA: SALIDAS
- ENCENDER → Activar bomba (D3 = HIGH)
- APAGAR → Desactivar bomba (D3 = LOW)

CATEGORÍA: LCD
- LCD TEXTO → Mensajes de estado
- LCD MOSTRAR → Mostrar valores de sensores
```

## 6. Valores de referencia

```
ESTADOS DE LAS BOYAS:
- Cisterna vacía: D2=0, D4=0, D6=0 → BOMBA OFF
- Cisterna OK, tanque vacío: D2=1, D4=0, D6=0 → BOMBA ON
- Cisterna OK, tanque medio: D2=1, D4=1, D6=0 → BOMBA ON
- Cisterna OK, tanque lleno: D2=1, D4=1, D6=1 → BOMBA OFF
- Cisterna vacía (cualquiera): D2=0 → BOMBA OFF (seguridad)

LÓGICA DE SEGURIDAD:
1. Siempre verificar cisterna PRIMERO
2. Si no hay agua, NUNCA arrancar bomba
3. Solo arrancar si hay agua Y tanque no lleno Y tanque bajo

NOTA: Agregar válvula check para evitar retorno de agua.
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Agregar LED de estado
- Agregar botón de arranque manual
- Cambiar mensajes a español

NIVEL INTERMEDIO:
- Agregar histéresis con memoria (ver ejemplo 28)
- Usar sensor ultrasonido para nivel continuo
- Agregar timer de protección si bomba muy larga

NIVEL AVANZADO:
- Múltiples tanques en cascada
- Control de válvula de llenado
- Datalogger de consumo de agua
- Alerta por SMS si cisterna vacía
```

## 8. Tips de debug

```
PROBLEMA: Bomba no enciende nunca
SOLUCIÓN: Verificar D2 (cisterna), debe estar HIGH

PROBLEMA: Bomba no se apaga
SOLUCIÓN: Verificar D6 (nivel alto), debe estar HIGH

PROBLEMA: Lecturas erráticas
SOLUCIÓN: Agregar capacitores 100nF entre signal y GND de cada boya

PROBLEMA: Rebotes en boyas
SOLUCIÓN: Agregar delay(50) después de leer, o filtrar con contador
```
