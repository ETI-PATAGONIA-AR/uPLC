# MANUAL COMPLETO DE PROGRAMACIÓN LADDER

## Aprendé a programar sin saber programar

![PORTADA_uPLC_2](https://github.com/user-attachments/assets/a5245d4d-c2d7-447d-8f5d-fe7c6cc486db)

---

# ÍNDICE

## Parte 1 – Conceptos Básicos (páginas 1–20)

1. ¿Qué es un PLC y para qué sirve?
2. ¿Qué es un diagrama Ladder?
3. Elementos básicos del Ladder
4. Cómo leer un diagrama Ladder

## Parte 2 – Herramientas Disponibles (páginas 21–40)

1. Contactos (interruptores)
2. Bobinas (salidas)
3. Temporizadores
4. Comparadores
5. Variables y memoria

## Parte 3 – Ejemplos Prácticos (páginas 41–70)

1. Encender una luz con un botón  
2. Dos botones, una luz (AND)  
3. Cualquier botón enciende (OR)  
4. Temporizador de escalera  
5. Control de temperatura  
6. Sistema de tanque de agua  

## Parte 4 – Comunicación Modbus (páginas 71–90)

1. ¿Qué es Modbus y para qué sirve?  
2. Leer datos de otro Arduino  
3. Enviar comandos a distancia  
4. Sistema distribuido completo  

## Parte 5 – Tips y Trucos (páginas 91–100)

1. Errores comunes  
2. Buenas prácticas  
3. Cómo testear tu programa  

---

# PARTE 1 – CONCEPTOS BÁSICOS

## 1.1 ¿QUÉ ES UN PLC Y PARA QUÉ SIRVE?

Un **PLC (Controlador Lógico Programable)** es un dispositivo electrónico diseñado para automatizar procesos.

### Ejemplos en casa

- Encender luces cuando detecta movimiento  
- Controlar la temperatura  
- Abrir un portón automático  
- Regar el jardín  

### Ejemplos en fábrica

- Cintas transportadoras  
- Sistemas de llenado  
- Control de hornos  
- Mezcladoras automáticas  

---

## Nuestro PLC

Arduino NANO + uPLC v4

```text
┌─────────────────────────────────────────────┐
│               ARDUINO NANO                 │
│                                             │
│  Entradas                     Salidas      │
│  I1 ───────────────┐          Q1 (Luz)     │
│  I2 (Botón)────────┼── PLC ── Q2 (Motor)   │
│  I3 (Sensor)───────┘          Q3 (Alarma)  │
└─────────────────────────────────────────────┘
```

---

## 1.2 ¿QUÉ ES UN DIAGRAMA LADDER?

"Ladder" significa **escalera**.

Ejemplo simple:

```text
║  [BOTÓN] ─────────────────── (LUZ)  ║
```

Se lee de **izquierda a derecha**:

1. La corriente sale del carril izquierdo  
2. Pasa por la condición  
3. Si la condición es verdadera, activa la salida  

---

## 1.3 ELEMENTOS BÁSICOS DEL LADDER

En Ladder hay dos tipos principales de elementos:

### 1️⃣ Condiciones (izquierda)

- Sensores  
- Interruptores  
- Comparaciones  

### 2️⃣ Acciones (derecha)

- Salidas  
- Temporizadores  
- Variables  

---

### Contacto Normalmente Abierto (NA)

Símbolo:

```text
─┤ ├─
```

Deja pasar corriente cuando está ACTIVADO.

---

### Contacto Normalmente Cerrado (NC)

Símbolo:

```text
─┤/├─
```

Deja pasar corriente cuando está DESACTIVADO.

---

### Bobina (Salida)

Símbolo:

```text
─( )─
```

Enciende o apaga una salida.

---

### Temporizador TON

Símbolo:

```text
─[TON]─
```

Espera un tiempo antes de activarse.

---

## 1.4 CÓMO LEER UN DIAGRAMA LADDER

### Reglas de oro

1. Se lee de arriba hacia abajo  
2. Cada línea es un “rung”  
3. Cada rung se lee de izquierda a derecha  

Ejemplo:

```text
// Línea 1
║  [Botón I1] ───────────── (Luz Q1)  ║

// Línea 2
║  [Sensor Calor] ───────── (Ventilador Q2)  ║

// Línea 3
║  [Sensor Puerta] ──────── (Sirena Q3)  ║
```

Lectura:

- Si presiono I1 → se enciende Q1  
- Si hay calor → se enciende Q2  
- Si se abre la puerta → suena Q3  

Cada línea funciona de manera independiente.

---

## Ejercicio 1

```text
║  [Interruptor] ─────────── (Lámpara)  ║
```

Preguntas:

1. ¿Qué pasa si acciono el interruptor?  
2. ¿Qué pasa si no lo acciono?  
3. ¿Cuántas condiciones hay?  
4. ¿Cuántas acciones hay?  

Respuestas:

1. La lámpara se enciende  
2. Permanece apagada  
3. Una condición  
4. Una acción  

---

# PARTE 2 – HERRAMIENTAS DISPONIBLES

En uPLC v4 contamos con diferentes bloques para construir la lógica del sistema.

---

## 2.1 CONTACTOS (CONDICIONES)

Los contactos son las condiciones que permiten o bloquean el paso de la corriente lógica.

---

### 📌 Contacto NA (Normalmente Abierto)

Símbolo:

```text
─┤ ├─
```

Deja pasar corriente cuando está ACTIVADO.

**Uso típico:**

- Botón pulsador
- Sensor de presencia
- Interruptor encendido

En uPLC v4:  
Seleccionar **Contacto NA** y asignar la entrada (I1–I7).

---

### 📌 Contacto NC (Normalmente Cerrado)

Símbolo:

```text
─┤/├─
```

Deja pasar corriente cuando está DESACTIVADO.

**Uso típico:**

- Botón de emergencia
- Sensor de seguridad
- Sistema de falla

En uPLC v4:  
Seleccionar **Contacto NC** y asignar la entrada correspondiente.

---

### Ejemplo práctico – Sistema de seguridad

Si una puerta se abre, debe sonar una alarma:

```text
║  [Sensor Puerta NC] ─────────── (Alarma Q1)  ║
```

- Puerta cerrada → sensor activado → no pasa corriente → alarma apagada  
- Puerta abierta → sensor desactivado → pasa corriente → alarma encendida  

---

## 2.2 BOBINAS (SALIDAS)

Las bobinas representan acciones.

---

### 📌 Bobina Normal

Símbolo:

```text
─( )─
```

Activa una salida cuando recibe corriente.

Ejemplos:

- LED
- Motor
- Bomba
- Sirena

En uPLC v4:  
Seleccionar **Bobina** y asignar salida (Q1–Q6).

---

### 📌 Bobina Negada

Símbolo:

```text
─(/)─
```

Funciona de forma inversa:

- Si recibe corriente → apaga la salida  
- Si no recibe corriente → la enciende  

---

### Ejemplo práctico – Botón y luz

```text
║  [I1] ─────────────── (Q1)  ║
```

- Botón presionado → Luz encendida  
- Botón suelto → Luz apagada  

---

## 2.3 TEMPORIZADORES

Los temporizadores permiten trabajar con tiempo.

---

### 📌 TON (Timer ON-Delay)

Símbolo:

```text
─[TON]─
```

Se activa después de un tiempo determinado.

Configuración:

- Ref: T0–T9  
- Valor en milisegundos  

Ejemplos:

- 1000 = 1 segundo  
- 5000 = 5 segundos  
- 60000 = 1 minuto  

---

### Ejemplo – Luz de escalera (30 segundos)

```text
// Rung 1: Iniciar temporizador
║  [I1] ───────────── [TON T0 = 30000]  ║

// Rung 2: Luz activa mientras timer no termine
║  [T0 NC] ─────────── (Q1)  ║
```

Funcionamiento:

1. Presiono botón → inicia timer  
2. Mientras el timer no termina → luz encendida  
3. Cuando termina → luz apagada  

---

### 📌 TOFF (Timer OFF-Delay)

Símbolo:

```text
─[TOFF]─
```

Mantiene activa la salida durante un tiempo después de desactivarse la condición.

---

## 2.4 COMPARADORES Y ENTRADAS ANALÓGICAS

Hasta ahora usamos entradas digitales (0 o 1).

Las entradas analógicas permiten valores variables (0–255).

En Arduino:

- A0  
- A1  

---

### 📌 ADC (Entrada Analógica)

Símbolo:

```text
─[ADC]─
```

Lee un valor analógico.

---

### 📌 Comparadores

Símbolos:

```text
─[>]─
─[<]─
─[=]─
```

Tipos:

- Mayor que (>)
- Menor que (<)
- Igual (=)

---

### Ejemplo – Control de temperatura

Sensor en A0.

Supongamos:

- 0 = 0°C  
- 255 = 100°C  
- 30°C ≈ 77  

```text
// Leer temperatura
║  [ADC A0] ─────────── [SET_VAR V0]  ║

// Comparar temperatura
║  [V0 > 77] ─────────── (Q1 Ventilador)  ║
```

Si la temperatura supera el valor configurado, se activa el ventilador.

---

## 2.5 VARIABLES Y MEMORIA

Las variables permiten almacenar información.

---

### 📌 Memorias (M0–M9)

Tipo: bits (0 o 1).

Ejemplos:

- M0 = Sistema activado  
- M1 = Alarma disparada  

---

### 📌 Variables Numéricas (V0–V9)

Tipo: 0–255.

Ejemplos:

- V0 = Temperatura  
- V1 = Contador  
- V2 = Nivel tanque  

---

### Nota importante

Las variables permiten realizar comparaciones, almacenar lecturas y estructurar programas más complejos.

---

# PARTE 3 – EJEMPLOS PRÁCTICOS

Ahora vamos a aplicar todo lo aprendido en proyectos reales.

---

## 3.1 PROYECTO 1 – UNA LUZ CON UN BOTÓN

### Objetivo

Cuando presiono un botón, se enciende un LED.  
Cuando lo suelto, se apaga.

### Hardware

- I1 = Botón
- Q1 = LED

### Diagrama Ladder

```text
║  [I1] ─────────────────── (Q1)  ║
```

### Funcionamiento

- I1 activado → Q1 encendido  
- I1 desactivado → Q1 apagado  

Este es el programa más básico posible.

---

## 3.2 PROYECTO 2 – DOS BOTONES (AND)

### Objetivo

El LED se enciende solo si ambos botones están presionados.

### Hardware

- I1 = Botón 1
- I2 = Botón 2
- Q1 = LED

### Diagrama Ladder

```text
║  [I1] ── [I2] ─────────── (Q1)  ║
```

### Lógica

Q1 = I1 AND I2

Tabla de verdad:

```text
I1   I2   Q1
0    0    0
0    1    0
1    0    0
1    1    1
```

Uso típico: sistemas de seguridad con doble confirmación.

---

## 3.3 PROYECTO 3 – CUALQUIER BOTÓN (OR)

### Objetivo

El LED se enciende si cualquiera de los dos botones está presionado.

### Hardware

- I1 = Botón 1
- I2 = Botón 2
- Q1 = LED

### Diagrama Ladder

```text
║  [I1] ─────────────── (Q1)  ║
║  [I2] ───────────────╯      ║
```

### Lógica

Q1 = I1 OR I2

Tabla de verdad:

```text
I1   I2   Q1
0    0    0
0    1    1
1    0    1
1    1    1
```

Uso típico: luces con múltiples interruptores.

---

## 3.4 PROYECTO 4 – LUZ DE ESCALERA AUTOMÁTICA

### Objetivo

Al presionar un botón, la luz permanece encendida 60 segundos y luego se apaga sola.

### Hardware

- I1 = Botón
- Q1 = Luz
- T0 = Timer 60.000 ms

### Diagrama Ladder

```text
// Rung 1
║  [I1] ───────────── [TON T0 = 60000]  ║

// Rung 2
║  [T0 NC] ─────────── (Q1)  ║
```

### Secuencia

- Presiono botón → inicia timer  
- Mientras el timer cuenta → luz encendida  
- Al finalizar → luz apagada  

---

## 3.5 PROYECTO 5 – CONTROL DE TEMPERATURA

### Objetivo

- Si temperatura > 25°C → Ventilador ON  
- Si temperatura < 20°C → Calefactor ON  
- Entre 20 y 25 → Todo apagado  

### Hardware

- A0 = Sensor temperatura
- Q1 = Ventilador
- Q2 = Calefactor
- V0 = Variable temperatura

### Conversión aproximada

- 20°C ≈ 51  
- 25°C ≈ 64  

### Diagrama Ladder

```text
// Leer temperatura
║  [ADC A0] ─────────── [SET_VAR V0]  ║

// Ventilador
║  [V0 > 64] ─────────── (Q1)  ║

// Calefactor
║  [V0 < 51] ─────────── (Q2)  ║
```

### Mejora recomendada

Agregar histéresis para evitar encendidos y apagados constantes.

---

## 3.6 PROYECTO 6 – TANQUE DE AGUA AUTOMÁTICO

### Objetivo

- Nivel bajo → Bomba ON  
- Nivel alto → Bomba OFF  
- Protección: máximo 5 minutos encendida  

### Hardware

- I1 = Nivel bajo
- I2 = Nivel alto
- Q1 = Bomba
- Q2 = Alarma
- T0 = 300000 ms

### Diagrama Ladder

```text
// Rung 1 – Control básico
║  [I1] ── [I2 NC] ───────── (Q1)  ║

// Rung 2 – Timer de protección
║  [Q1] ───────────── [TON T0 = 300000]  ║

// Rung 3 – Apagado forzado
║  [T0] ───────────── (Q1 NC)  ║

// Rung 4 – Activar alarma
║  [T0] ───────────── (Q2)  ║
```

### Funcionamiento

1. Si el tanque está vacío → bomba enciende  
2. Si se llena → bomba apaga  
3. Si permanece 5 minutos encendida → se apaga por seguridad y activa alarma  

Sistema protegido contra fallas.

---

# PARTE 4 – COMUNICACIÓN MODBUS (AVANZADO)

Esta sección es opcional y está orientada a sistemas distribuidos.

---

## 4.1 ¿QUÉ ES MODBUS?

Modbus es un protocolo de comunicación industrial que permite que varios dispositivos se comuniquen entre sí.

En nuestro caso:

- Un Arduino puede ser **Master**
- Otros Arduinos pueden ser **Slave**
- Se comunican mediante RS485

---

## 4.2 CONCEPTOS BÁSICOS

### Master

- Inicia la comunicación
- Hace preguntas
- Controla la red
- Solo puede haber uno

### Slave

- Responde cuando el Master pregunta
- Tiene un ID único (1, 2, 3…)
- Puede haber varios

---

### Registros Modbus

Cada dispositivo tiene registros de memoria:

- MB0
- MB1
- MB2
- ...
- MB9

Ejemplo:

- MB0 = Temperatura
- MB1 = Humedad
- MB2 = Nivel

---

## 4.3 EJEMPLO – LEER TEMPERATURA REMOTA

### Objetivo

El Master lee la temperatura de un Slave cada segundo y enciende un ventilador si hace calor.

### Hardware

- Master ID=1
- Slave ID=2
- RS485 entre ambos
- Q1 = Ventilador

---

### Diagrama Ladder (Master)

```text
// Timer 1 segundo
║  [TON T0 = 1000] ───────── [TON T0 = 1000]  ║

// Leer registro del Slave ID 2
║  [T0] ───────────── [MB_READ MB0, S:2]  ║

// Comparar valor leído
║  [MB0 > 80] ───────── (Q1)  ║
```

### Funcionamiento

1. Timer genera evento cada segundo  
2. Se lee MB0 del Slave ID=2  
3. Si MB0 > 80 → Ventilador ON  

---

# PARTE 5 – TIPS Y TRUCOS

---

## 5.1 ERRORES COMUNES

### ❌ No pasa nada al presionar el botón

Posibles causas:

- Botón mal conectado
- Pin incorrecto
- Sketch no cargado

Solución:

- Verificar conexiones
- Verificar asignación I1–I7
- Verificar carga del programa

---

### ❌ La salida no se enciende

Posibles causas:

- LED invertido
- Falta resistencia
- Pin incorrecto

Solución:

- Revisar polaridad
- Agregar resistencia de 220Ω
- Verificar Q1–Q6

---

### ❌ El temporizador no funciona

- Recordar que el valor es en milisegundos
- 1000 ms = 1 segundo
- Verificar uso correcto de T0 y T0 NC

---

## 5.2 BUENAS PRÁCTICAS

### Usar comentarios claros

Mal:

```text
║  [I1] ── [I2] ───── (Q1)  ║
```

Bien:

```text
// Ambos botones de seguridad activados
║  [I1] ── [I2] ───── (Q1 Motor)  ║
```

---

### Testear por etapas

1. Primero botón → luz  
2. Luego agregar timer  
3. Luego sensores  
4. Finalmente integrar todo  

---

### Guardar versiones

Ejemplo:

- proyecto_v1.uplc
- proyecto_v2.uplc
- proyecto_final.uplc

---

## 5.3 CÓMO TESTEAR TU PROGRAMA

### Paso 1 – Simulación mental

Leer el programa y verificar la lógica antes de cargarlo.

### Paso 2 – Revisar conexiones físicas

- Entradas conectadas correctamente
- Salidas con carga adecuada
- Sin cortocircuitos

### Paso 3 – Probar con LEDs antes de motores

Siempre probar primero con cargas pequeñas.

### Paso 4 – Usar Monitor Serial

Velocidad recomendada: 9600 bps.

---

# EJERCICIOS FINALES

## Ejercicio 1 – Semáforo

- Q1 = Rojo
- Q2 = Amarillo
- Q3 = Verde
- Secuencia automática con temporizadores

---

## Ejercicio 2 – Alarma de intruso

- I1 = Puerta
- I2 = Ventana
- Q1 = Sirena
- I3 = Desactivar alarma

---

## Ejercicio 3 – Riego automático

- I1 = Sensor humedad
- Q1 = Electroválvula
- Activar si humedad < valor configurado

---

## Ejercicio 4 – Control de parking

- I1 = Entrada
- I2 = Salida
- Variables para contar vehículos
- Mostrar espacios disponibles

---

# RECURSOS ADICIONALES

- MODBUS_GUIDE.md
- EJEMPLO_MODBUS.md
- HARDWARE_RS485.md
- MINI_CURSO_LADDER.md

---

# CONTACTO

ETI Patagonia  
prof.martintorres@educ.ar  
https://eti-patagonia-ar.github.io/ETI-Patagonia-ARG/

---

# FIN DEL MANUAL
