# 12 - LUCES AUTOMÁTICAS

## 1. ¿Qué hace?
Enciende luces automáticamente cuando la luz ambiental es baja.
Similar a las luces de patio o calle.

## 2. ¿Qué necesitás?
- Arduino UNO/NANO
- LDR (fotorresistencia) 10K
- Resistencia 10K
- Módulo relé o MOSFET
- Luz a controlar (LED, bombilla)

## 3. Conexiones de hardware

```
LDR (divisor de tensión):
- PIN A6 (Arduino) → LDR → Resistencia 10K → GND
- 5V → LDR (el otro extremo)
- Más luz = menor resistencia = mayor voltaje en A6

RELÉ:
- PIN D13 (Q1) → IN del relé
- Relé: COM → Fuente, NO → Luz

LCD I2C (opcional):
- A4 (SDA) y A5 (SCL)
```

## 4. ¿Cómo funciona?

```
// CONSTANTES
UMBRAL = 128

// AL INICIAR
AL INICIAR:
  Q1 = FALSO
  V0 = 0

// PARA SIEMPRE
PARA SIEMPRE:
  // Leer sensor de luz
  V0 = LEER_ANALOGICO(A6)
  
  // Comparar con umbral
  SI (V0 < 128)                  // Oscuro
    Q1 = VERDADERO                // Encender luz
  SINO
    Q1 = FALSO                    // Apagar luz
```

## 5. Bloques utilizados

```
CATEGORÍA: ENTRADAS
- LEER_ANALOGICO → Leer LDR (A6)

CATEGORÍA: LÓGICA
- SI → Comparar con umbral
- SINO → Caso contrario
- COMPARAR → Operador <

CATEGORÍA: SALIDAS
- ASIGNAR → Controlar Q1 (luz)
```

## 6. Valores de referencia

```
LDR:
- Luz brillante: ADC ~ 800-1023
- Habitación normal: ADC ~ 300-500
- Oscuro: ADC ~ 0-100

UMBRAL:
- 128: Umbral típico (ajustar según ubicación)
- Valor menor = más sensible (enciende con más luz)
- Valor mayor = menos sensible (solo en oscuridad)

NOTA: Calibrar según la zona donde se instale.
```

## 7. Desafíos propuestos

```
NIVEL BÁSICO:
- Cambiar umbral para otra condición
- Agregar histeresis

NIVEL INTERMEDIO:
- Agregar botón manual/automático
- Fade gradual con PWM

NIVEL AVANZADO:
- Despertador con amanecer gradual
- Control por tiempo + luz
- Datalogger de horas de encendido
```

## 8. Tips de debug

```
PROBLEMA: Luz enciende con poca oscuridad
SOLUCIÓN: Aumentar umbral (>128)

PROBLEMA: Luz no enciende nunca
SOLUCIÓN: Verificar LDR y divisor resistivo

PROBLEMA: Oscila (parpadea)
SOLUCIÓN: Agregar histéresis (encendido 100, apagado 200)
```
