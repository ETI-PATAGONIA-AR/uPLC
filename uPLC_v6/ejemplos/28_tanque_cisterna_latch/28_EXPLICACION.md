# 28 - TANQUE + CISTERNA CON LATCH

## 1. ¿Qué hace?
Versión PRO del control de tanque con memoria de estado (latch).
Evita oscilaciones cuando el nivel está entre las boyas.
Una vez que arranca, la bomba sigue hasta tanque lleno.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LCD 20x4 I2C
- 3 boyas/flotadores de nivel
- Módulo relé para bomba
- Bomba de agua

## 3. Conexiones de hardware

```
BOYAS:
- BOYA CISTERNA: D2 → Signal, 10K a GND, 5V
- BOYA TANQUE BAJO: D4 → Signal, 10K a GND, 5V
- BOYA TANQUE ALTO: D6 → Signal, 10K a GND, 5V

BOMBA:
- PIN D3 (Arduino) → IN del relé
- Relé: COM → Fuente, NO → Bomba

LCD I2C:
- PIN A4 (Arduino) → SDA del LCD
- PIN A5 (Arduino) → SCL del LCD

CONCEPTO LATCH:
- Una vez que la variable estadoBomba = true
- Se mantiene así hasta que algo la cambie
- No oscila entre ON y OFF
```

## 4. ¿Cómo funciona?

```
// VARIABLES GLOBALES
estadoBomba = FALSO

// AL INICIAR
AL INICIAR:
  LCD → "TANQUE PRO (LATCH)"
  LCD → "Con memoria de estado"
  LCD → "Evita oscilaciones"
  ESPERAR 2500 ms
  LCD CLEAR
  estadoBomba = FALSO
  APAGAR D3

// PARA SIEMPRE
PARA SIEMPRE:
  
  // ══ SEGURIDAD 1: Sin agua → PARAR ══
  SI (D2 == LOW)
    estadoBomba = FALSO              // Forzar apagado
    APAGAR D3
    LCD → "ALERTA: Sin cisterna!"
  
  // ══ SEGURIDAD 2: Tanque lleno → PARAR ══
  SI (D6 == HIGH)
    estadoBomba = FALSO              // Forzar apagado
    APAGAR D3
    LCD → "TANQUE LLENO"
  
  // ══ ARRANQUE: Tanque bajo + hay agua → ARRANCAR ══
  SI (D4 == HIGH) Y (D2 == HIGH)
    estadoBomba = VERDADERO         // ¡Memoria!
  
  // ══ APLICAR ESTADO A SALIDA ══
  SI (estadoBomba == VERDADERO)
    ENCENDER D3
    LCD → "BOMBA: TRABAJANDO"
  SINO
    APAGAR D3
    LCD → "BOMBA: DETENIDA"
  
  // Mostrar memoria
  LCD → "Cis:"
  SI (D2==HIGH) LCD → "OK " SINO LCD → "ERR"
  LCD → "TqB:"
  SI (D4==HIGH) LCD → "SI " SINO LCD → "NO "
  LCD → "TqA:"
  SI (D6==HIGH) LCD → "SI" SINO LCD → "NO"
  
  LCD → "Estado memoria:"
  SI (estadoBomba) LCD → "ON " SINO LCD → "OFF"
```

## 5. Bloques utilizados

```
CATEGORÍA: VARIABLES
- CREAR variable "estadoBomba" (lógico)
- ASIGNAR → Modificar estado

CATEGORÍA: ENTRADAS
- LEER_DIGITAL → Leer boyas (D2, D4, D6)

CATEGORÍA: LÓGICA
- SI → Evaluar cada condición
- Y → Combinar condiciones (D4==HIGH Y D2==HIGH)
- COMPARAR → Comparar con HIGH/LOW

CATEGORÍA: SALIDAS
- ENCENDER → Activar bomba
- APAGAR → Desactivar bomba

CATEGORÍA: LCD
- LCD TEXTO → Mensajes de estado
```

## 6. Valores de referencia

```
DIFERENCIA CON EJEMPLO 27 (sin latch):
- Ejemplo 27: Si D4 pasa de 0→1→0 (olas), bomba oscila
- Ejemplo 28: D4=1 una vez → bomba ON hasta D6=1

FLUJO DE ESTADO:
1. Cisterna OK (D2=1), Tanque bajo (D4=1) → estadoBomba=TRUE
2. Tanque medio (D4=0), pero estadoBomba=TRUE → BOMBA ON
3. Tanque alto (D6=1) → estadoBomba=FALSE → BOMBA OFF

ESTADOS POSIBLES:
- Espera: cisterna OK, tanque alto, bomba OFF
- Llenando: cisterna OK, tanque bajo, bomba ON
- Seguridad: cisterna vacía, bomba OFF
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Agregar timer máximo de bombeo
- Agregar LED de estado de memoria
- Agregar botón reset manual

NIVEL INTERMEDIO:
- Agregar contador de arranques
- Agregar sensor de flujo para detectar falla
- Implementar doble seguridad (2 sensores bajo)

NIVEL AVANZADO:
- Válvulas motorizadas de 3 vías
- Control de velocidad de bomba según nivel
- Datalogger de consumo
- Alertas por radio/Bluetooth
```

## 8. Tips de debug

```
PROBLEMA: Bomba no arranque
VERIFICAR: D2 debe estar HIGH (hay agua), D4 debe estar HIGH

PROBLEMA: Bomba no para
VERIFICAR: D6 debe estar HIGH (tanque lleno)

PROBLEMA: Variable no mantiene valor
VERIFICAR: variable debe ser global, no local

PROBLEMA: Oscila igual
SOLUCIÓN: Agregar contador de confirmaciones antes de cambiar estado
```
