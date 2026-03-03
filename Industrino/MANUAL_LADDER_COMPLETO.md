<img width="1024" height="1536" alt="PORTADA_uPLC_2" src="https://github.com/user-attachments/assets/a5245d4d-c2d7-447d-8f5d-fe7c6cc486db" />

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║     MANUAL COMPLETO DE PROGRAMACIÓN LADDER                       ║
║     "Aprendé a programar sin saber programar"                    ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
ÍNDICE
═══════════════════════════════════════════════════════════════════

PARTE 1 - CONCEPTOS BÁSICOS (páginas 1-20)
  1.1 ¿Qué es un PLC y para qué sirve?
  1.2 ¿Qué es un diagrama ladder?
  1.3 Elementos básicos del ladder
  1.4 Cómo "leer" un diagrama ladder

PARTE 2 - HERRAMIENTAS DISPONIBLES (páginas 21-40)
  2.1 Contactos (interruptores)
  2.2 Bobinas (salidas)
  2.3 Temporizadores
  2.4 Comparadores
  2.5 Variables y memoria

PARTE 3 - EJEMPLOS PRÁCTICOS (páginas 41-70)
  3.1 Encender una luz con un botón
  3.2 Dos botones, una luz (AND)
  3.3 Cualquier botón enciende (OR)
  3.4 Temporizador de escalera
  3.5 Control de temperatura
  3.6 Sistema de tanque de agua

PARTE 4 - COMUNICACIÓN MODBUS (páginas 71-90)
  4.1 ¿Qué es Modbus y para qué sirve?
  4.2 Leer datos de otro Arduino
  4.3 Enviar comandos a distancia
  4.4 Sistema distribuido completo

PARTE 5 - TIPS Y TRUCOS (páginas 91-100)
  5.1 Errores comunes y cómo solucionarlos
  5.2 Buenas prácticas de programación
  5.3 Cómo testear tu programa

═══════════════════════════════════════════════════════════════════
PARTE 1 - CONCEPTOS BÁSICOS
═══════════════════════════════════════════════════════════════════

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
1.1 ¿QUÉ ES UN PLC Y PARA QUÉ SIRVE?
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Imaginate que querés automatizar algo en tu casa o fábrica. Por ejemplo:

🏠 EN TU CASA:
  • Encender luces cuando detecta movimiento
  • Controlar la temperatura con un termostato
  • Abrir el portón con un control remoto
  • Regar el jardín automáticamente

🏭 EN UNA FÁBRICA:
  • Control de cintas transportadoras
  • Mezcladoras automáticas
  • Sistemas de llenado de botellas
  • Control de hornos y temperaturas

¿CÓMO SE HACÍA ANTES?
Antiguamente, para hacer esto necesitabas un electricista que conectara
un montón de cables, relés, temporizadores físicos, etc. Era:
  ❌ Caro (muchos componentes)
  ❌ Difícil de cambiar (había que recablear todo)
  ❌ Propenso a fallas (conexiones se aflojaban)

¿CÓMO SE HACE AHORA?
Con un PLC (Controlador Lógico Programable):
  ✅ Un solo dispositivo
  ✅ Se programa por software
  ✅ Fácil de modificar
  ✅ Más confiable

NUESTRO PLC:
Es un Arduino NANO (el cerebro) + uPLC v4 (el software para programarlo)

┌─────────────────────────────────────────────────────────┐
│                    ARDUINO NANO                         │
│                   (El "cerebro")                        │
│                                                         │
│  Entradas          ┌─────┐          Salidas            │
│  I1 ───────────────┤     ├───────────── Q1 (luz)       │
│  I2 (botón)────────┤ PLC ├───────────── Q2 (motor)     │
│  I3 (sensor)───────┤     ├───────────── Q3 (alarma)    │
│                    └─────┘                              │
└─────────────────────────────────────────────────────────┘

ANALOGÍA:
Un PLC es como tu cerebro:
  • Las ENTRADAS son tus sentidos (vista, oído, tacto)
  • Las SALIDAS son tus acciones (caminar, hablar)
  • El PROGRAMA es tu conocimiento (si hace frío → ponete un abrigo)

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
1.2 ¿QUÉ ES UN DIAGRAMA LADDER?
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

"Ladder" significa "escalera" en inglés. Se llama así porque parece
una escalera de lado.

EJEMPLO SIMPLE: "Si presiono el botón, se enciende la luz"

┌────────────────────────────────────────────────────────┐
│ ║                                                   ║   │
│ ║   [BOTÓN]────────────────────────────(LUZ)       ║   │
│ ║                                                   ║   │
└────────────────────────────────────────────────────────┘
  ↑                                                    ↑
Carril                                            Carril
izquierdo                                        derecho
(corriente)                                    (corriente)

¿CÓMO SE LEE?
De IZQUIERDA a DERECHA, como leer un libro.

1. La corriente sale del carril izquierdo (║)
2. Pasa por el BOTÓN (condición)
3. Si el botón está presionado → la corriente llega a la LUZ
4. La luz se enciende
5. La corriente vuelve al carril derecho (║)

ANALOGÍA DEL RÍO:
Imagina que la corriente es agua que fluye:
  • Los carriles son las orillas del río
  • El botón es una compuerta
  • La luz es una rueda de molino
  • Si abro la compuerta → el agua hace girar la rueda

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
1.3 ELEMENTOS BÁSICOS DEL LADDER
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

En programación ladder tenemos SOLO DOS TIPOS de elementos:

┌─────────────────────────────────────────────────────────────┐
│  1. CONDICIONES (van a la IZQUIERDA)                        │
│     → Preguntas / Sensores / Interruptores                  │
│     → Deciden si pasa la corriente o no                     │
│                                                              │
│  2. ACCIONES (van a la DERECHA)                             │
│     → Salidas / Cosas que se ejecutan                       │
│     → Se activan si llega corriente                         │
└─────────────────────────────────────────────────────────────┘

EJEMPLO CON ANALOGÍA:

CONDICIÓN (Pregunta):
  "¿Está lloviendo?"
  
ACCIÓN (Respuesta):
  "Entonces llevá paraguas"

EN LADDER:
┌─────────────────────────────────────────────────────────┐
│ ║  [¿Está lloviendo?]──────────(Llevar paraguas)    ║  │
└─────────────────────────────────────────────────────────┘

TIPOS DE CONDICIONES:

1. CONTACTO NORMALMENTE ABIERTO (NO o NA)
   Símbolo: ─┤ ├─  (dos líneas paralelas)
   
   Significa: "Si está ACTIVADO, deja pasar"
   Ejemplo: Botón que al presionarlo cierra el circuito
   
   Analogía: Puerta cerrada que abro al presionar

2. CONTACTO NORMALMENTE CERRADO (NC)
   Símbolo: ─┤/├─  (dos líneas con diagonal)
   
   Significa: "Si está DESACTIVADO, deja pasar"
   Ejemplo: Sensor de seguridad (pasa si NO hay problema)
   
   Analogía: Puerta abierta que se cierra al presionar

TIPOS DE ACCIONES:

1. BOBINA (Salida simple)
   Símbolo: ─( )─  (círculo)
   
   Significa: "Enciende/apaga algo"
   Ejemplo: Un LED, motor, alarma
   
   Analogía: Un interruptor de luz

2. TEMPORIZADOR
   Símbolo: ─[TON]─  (caja con texto)
   
   Significa: "Espera X segundos y luego activa"
   Ejemplo: Luz de escalera que se apaga sola
   
   Analogía: Un reloj de arena

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
1.4 CÓMO "LEER" UN DIAGRAMA LADDER
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

REGLAS DE ORO:

1. Se lee de ARRIBA hacia ABAJO
2. Cada línea se lee de IZQUIERDA a DERECHA
3. Cada línea es una INSTRUCCIÓN completa (un "rung")

EJEMPLO COMPLETO:

┌────────────────────────────────────────────────────────┐
│ // Línea 1: Luz del pasillo                           │
│ ║  [Botón 1]──────────────────────(Luz 1)          ║  │
│                                                        │
│ // Línea 2: Ventilador                                │
│ ║  [Sensor calor]─────────────────(Ventilador)     ║  │
│                                                        │
│ // Línea 3: Alarma                                    │
│ ║  [Sensor puerta]────────────────(Sirena)         ║  │
└────────────────────────────────────────────────────────┘

CÓMO LEERLO EN VOZ ALTA:

Línea 1: "SI presiono Botón 1, ENTONCES enciende Luz 1"
Línea 2: "SI el Sensor detecta calor, ENTONCES enciende Ventilador"
Línea 3: "SI el Sensor detecta puerta abierta, ENTONCES activa Sirena"

IMPORTANTE:
Cada línea se ejecuta INDEPENDIENTE de las otras.
Es como tener 3 reglas que funcionan al mismo tiempo.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
EJERCICIO 1 - VERIFICA SI ENTENDISTE
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Mirá este diagrama:

┌────────────────────────────────────────────────────────┐
│ ║  [Interruptor]──────────────────(Lámpara)        ║  │
└────────────────────────────────────────────────────────┘

PREGUNTAS:
1. ¿Qué pasa si acciono el interruptor?
2. ¿Qué pasa si NO acciono el interruptor?
3. ¿Cuántas condiciones tiene este programa?
4. ¿Cuántas acciones tiene?

RESPUESTAS:
1. La lámpara se enciende
2. La lámpara permanece apagada
3. Una condición (el interruptor)
4. Una acción (la lámpara)

═══════════════════════════════════════════════════════════════════
PARTE 2 - HERRAMIENTAS DISPONIBLES
═══════════════════════════════════════════════════════════════════

En uPLC v4 tenemos estas herramientas (bloques) disponibles:

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
2.1 CONTACTOS (CONDICIONES)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

┌─────────────────────────────────────────────────────────┐
│ 📌 CONTACTO NA (Normalmente Abierto)                    │
│    Símbolo: ─┤ ├─                                       │
│    Nombre: NO en el programa                            │
│                                                          │
│    ¿Cuándo deja pasar?                                  │
│    → Cuando está ACTIVADO (presionado, detectado)       │
│                                                          │
│    Ejemplo de uso:                                      │
│    • Botón de timbre (al presionar suena)              │
│    • Sensor de presencia (detecta → enciende luz)      │
│    • Interruptor (encendido → funciona)                │
│                                                          │
│    En uPLC v4: Se llama "Contacto NA"                   │
│    Configuración: Elegir entrada (I1, I2, ... I7)       │
└─────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────┐
│ 📌 CONTACTO NC (Normalmente Cerrado)                    │
│    Símbolo: ─┤/├─                                       │
│    Nombre: NC en el programa                            │
│                                                          │
│    ¿Cuándo deja pasar?                                  │
│    → Cuando está DESACTIVADO (sin presionar, sin señal) │
│                                                          │
│    Ejemplo de uso:                                      │
│    • Sensor de seguridad (falla → alarma)              │
│    • Botón de emergencia (liberado → máquina para)     │
│    • Detector de humo (OK → continúa)                  │
│                                                          │
│    En uPLC v4: Se llama "Contacto NC"                   │
│    Configuración: Elegir entrada (I1, I2, ... I7)       │
└─────────────────────────────────────────────────────────┘

EJEMPLO PRÁCTICO 1: Sistema de seguridad

Tengo una puerta con sensor magnético:
  • Si la puerta está CERRADA → sensor ACTIVADO
  • Si la puerta está ABIERTA → sensor DESACTIVADO

Quiero que suene alarma si alguien abre la puerta:

┌────────────────────────────────────────────────────────┐
│ ║  [Sensor puerta NC]─────────────(Alarma)         ║  │
└────────────────────────────────────────────────────────┘

¿Por qué NC (Normalmente Cerrado)?
Porque quiero que la alarma suene cuando el sensor se DESACTIVE
(cuando la puerta se abra).

Estado normal (puerta cerrada):
  Sensor → ACTIVADO → NC no deja pasar → Alarma apagada ✅

Estado anormal (puerta abierta):
  Sensor → DESACTIVADO → NC deja pasar → Alarma suena 🚨

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
2.2 BOBINAS (SALIDAS)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

┌─────────────────────────────────────────────────────────┐
│ 📌 BOBINA NORMAL                                         │
│    Símbolo: ─( )─                                       │
│    Nombre: COIL en el programa                          │
│                                                          │
│    ¿Qué hace?                                           │
│    → Enciende una salida si llega corriente             │
│    → La apaga si NO llega corriente                     │
│                                                          │
│    Ejemplo de uso:                                      │
│    • Encender un LED                                    │
│    • Activar un motor                                   │
│    • Sonar una alarma                                   │
│    • Abrir una válvula                                  │
│                                                          │
│    En uPLC v4: Se llama "Bobina"                        │
│    Configuración: Elegir salida (Q1-Q6)                 │
└─────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────┐
│ 📌 BOBINA NEGADA (NC)                                   │
│    Símbolo: ─(/))─                                      │
│    Nombre: COIL_NC en el programa                       │
│                                                          │
│    ¿Qué hace?                                           │
│    → APAGA una salida si llega corriente                │
│    → La ENCIENDE si NO llega corriente                  │
│                                                          │
│    Ejemplo de uso:                                      │
│    • Ventilador que se apaga al detectar temperatura OK │
│    • Luz de advertencia que se apaga si todo está bien  │
│                                                          │
│    En uPLC v4: Se llama "Bobina NC"                     │
│    Configuración: Elegir salida (Q1-Q6)                 │
└─────────────────────────────────────────────────────────┘

EJEMPLO PRÁCTICO 2: Luz con interruptor

Quiero que un botón encienda una luz:

┌────────────────────────────────────────────────────────┐
│ ║  [Botón I1]─────────────────────(Luz Q1)         ║  │
└────────────────────────────────────────────────────────┘

Explicación:
  • Botón sin presionar → No pasa corriente → Luz apagada
  • Botón presionado → Pasa corriente → Luz encendida

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
2.3 TEMPORIZADORES
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Los temporizadores son CRUCIALES en automatización.

┌─────────────────────────────────────────────────────────┐
│ 📌 TON (Timer ON-delay)                                 │
│    Símbolo: ─[TON]─                                     │
│                                                          │
│    ¿Qué hace?                                           │
│    → Espera X tiempo DESPUÉS de activarse               │
│    → Luego se "completa" el timer                       │
│                                                          │
│    Analogía del semáforo:                               │
│    Cuando el semáforo se pone rojo, espera 30 segundos  │
│    y luego cambia a verde.                              │
│                                                          │
│    Configuración:                                       │
│    • Ref: Nombre del timer (T0-T9)                      │
│    • Value: Tiempo en milisegundos                      │
│      - 1000 = 1 segundo                                 │
│      - 5000 = 5 segundos                                │
│      - 60000 = 1 minuto                                 │
└─────────────────────────────────────────────────────────┘

EJEMPLO PRÁCTICO 3: Luz de escalera

Quiero una luz que se encienda con un botón y se apague sola
después de 30 segundos.

┌────────────────────────────────────────────────────────┐
│ // Rung 1: Al presionar botón, iniciar timer          │
│ ║  [Botón I1]─────────────────────[TON:T0=30000]   ║  │
│                                                        │
│ // Rung 2: Luz encendida mientras timer no termine    │
│ ║  [Timer T0 NC]──────────────────(Luz Q1)         ║  │
└────────────────────────────────────────────────────────┘

¿Cómo funciona?
1. Presiono el botón → Inicia timer de 30 segundos
2. Mientras el timer no termine, T0 está desactivado
3. T0 NC (normalmente cerrado) deja pasar → Luz encendida
4. Después de 30 segundos, T0 se completa (se activa)
5. T0 NC ya no deja pasar → Luz se apaga

┌─────────────────────────────────────────────────────────┐
│ 📌 TOFF (Timer OFF-delay)                               │
│    Símbolo: ─[TOFF]─                                    │
│                                                          │
│    ¿Qué hace?                                           │
│    → Espera X tiempo DESPUÉS de desactivarse            │
│    → Mantiene la salida activa durante ese tiempo       │
│                                                          │
│    Analogía del ventilador:                             │
│    Cuando apagás el aire acondicionado, el ventilador   │
│    sigue girando unos segundos para enfriar el sistema. │
│                                                          │
│    Configuración: Igual que TON                         │
└─────────────────────────────────────────────────────────┘

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
2.4 COMPARADORES Y ENTRADAS ANALÓGICAS
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Hasta ahora vimos entradas DIGITALES (ON/OFF, 0 o 1).
Pero también tenemos entradas ANALÓGICAS (valores variables 0-255).

¿QUÉ SON ENTRADAS ANALÓGICAS?
Son valores que pueden variar, como:
  • Temperatura (0°C a 100°C)
  • Nivel de luz (oscuro a brillante)
  • Presión
  • Velocidad

En nuestro Arduino:
  • A0 y A1 son entradas analógicas
  • Leen valores de 0 a 255

┌─────────────────────────────────────────────────────────┐
│ 📌 ADC (Entrada Analógica como condición)              │
│    Símbolo: ─[ADC]─                                     │
│                                                          │
│    ¿Qué hace?                                           │
│    → Pregunta "¿el sensor tiene algún valor?"           │
│    → Deja pasar si el valor es mayor a 0                │
│                                                          │
│    Ejemplo:                                             │
│    ¿Hay luz? (sensor de luz en A0)                      │
│    Si A0 > 0 → hay luz → deja pasar                     │
└─────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────┐
│ 📌 COMPARADORES (>, <, =)                               │
│    Símbolos: ─[>]─  ─[<]─  ─[=]─                       │
│                                                          │
│    ¿Qué hacen?                                          │
│    → Comparan un valor con otro                         │
│    → Dejan pasar si la comparación es verdadera         │
│                                                          │
│    Tipos:                                               │
│    • CMP_GT (Greater Than): Mayor que  >                │
│    • CMP_LT (Less Than): Menor que  <                   │
│    • CMP_EQ (Equal): Igual a  =                         │
│                                                          │
│    Configuración:                                       │
│    • Ref: Variable a comparar (A0, V0, MB0)             │
│    • Value: Valor de comparación (0-255)                │
└─────────────────────────────────────────────────────────┘

EJEMPLO PRÁCTICO 4: Control de temperatura

Tengo un sensor de temperatura conectado a A0.
Quiero encender un ventilador si hace más de 30°C.

Suponiendo que el sensor da:
  • 0 = 0°C
  • 255 = 100°C
  • Entonces: 30°C ≈ 77 en escala 0-255

┌────────────────────────────────────────────────────────┐
│ // Rung 1: Leer temperatura y guardar en variable     │
│ ║  [ADC:A0]───────────────────────[SET_VAR:V0]     ║  │
│                                                        │
│ // Rung 2: Si temperatura > 77, encender ventilador   │
│ ║  [V0 > 77]──────────────────────(Ventilador Q1)  ║  │
└────────────────────────────────────────────────────────┘

¿Cómo funciona?
1. Lee el valor de A0 (temperatura)
2. Lo guarda en V0 (una variable de memoria)
3. Compara V0 con 77
4. Si V0 > 77 → enciende ventilador

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
2.5 VARIABLES Y MEMORIA
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

A veces necesitamos "recordar" cosas entre un ciclo y otro.
Para eso usamos VARIABLES.

TIPOS DE VARIABLES:

┌─────────────────────────────────────────────────────────┐
│ 📌 MEMORIAS (M0-M9)                                     │
│    Tipo: Bits (0 o 1, ON/OFF)                          │
│                                                          │
│    ¿Para qué sirven?                                    │
│    → Recordar si algo pasó                              │
│    → Activar/desactivar modos                           │
│                                                          │
│    Ejemplo:                                             │
│    M0 = "Sistema activado"                              │
│    M1 = "Alarma disparada"                              │
│    M2 = "Puerta abierta alguna vez"                     │
└─────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────┐
│ 📌 VARIABLES (V0-V9)                                    │
│    Tipo: Números (0 a 255)                              │
│                                                          │
│    ¿Para qué sirven?                                    │
│    → Guardar valores numéricos                          │
│    → Hacer cálculos                                     │
│    → Almacenar lecturas de sensores                     │
│                                                          │
│    Ejemplo:                                             │
│    V0 = Temperatura actual                              │
│    V1 = Contador de piezas                              │
│    V2 = Nivel de tanque                                 │
└─────────────────────────────────────────────────────────┘

EJEMPLO PRÁCTICO 5: Contador de piezas

Quiero contar cuántas veces se presiona un botón.

PROBLEMA: ¿Cómo sumo 1 cada vez que se presiona?

SOLUCIÓN:
┌────────────────────────────────────────────────────────┐
│ // Rung 1: Leer botón                                 │
│ ║  [Botón I1]─────────────────────[SET_VAR:V0=??] ║  │
└────────────────────────────────────────────────────────┘

Ups, no podemos sumar directamente en Ladder básico.
Pero podemos usar trucos...

(Esto se verá en ejemplos avanzados)

═══════════════════════════════════════════════════════════════════
PARTE 3 - EJEMPLOS PRÁCTICOS
═══════════════════════════════════════════════════════════════════

Ahora viene lo divertido: ¡PROGRAMAR DE VERDAD!

Vamos a hacer 6 proyectos completos, desde el más simple al más
complejo.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
3.1 PROYECTO 1: UNA LUZ CON UN BOTÓN
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

OBJETIVO:
  Cuando presiono un botón, se enciende un LED.
  Cuando lo suelto, se apaga.

HARDWARE:
  • Entrada I1 = Botón pulsador
  • Salida Q1 = LED

DIAGRAMA LADDER:

┌────────────────────────────────────────────────────────┐
│ // Si presiono el botón, enciende el LED              │
│ ║  [I1]───────────────────────────(Q1)             ║  │
└────────────────────────────────────────────────────────┘

PASOS EN uPLC v4:

1. Abrir uPLC v4 (run_uPLCv4.bat)
2. Clic en "+ Agregar Rung"
3. Seleccionar "Contacto NA" en el toolbox
4. Hacer clic en la primera celda del rung
5. Clic derecho sobre el contacto → "Asignar Ref" → Elegir I1
6. Seleccionar "Bobina" en el toolbox
7. Hacer clic en la zona de salida (derecha)
8. Clic derecho sobre la bobina → "Asignar Ref" → Elegir Q1
9. Guardar (Ctrl+S)
10. Generar sketch (Ctrl+G)
11. Copiar código y cargar al Arduino

PROBARLO:
  • Presionar botón físico en pin D2
  • El LED en pin D13 debería encenderse
  • Soltar botón → LED se apaga

¡FELICITACIONES! ¡Tu primer programa ladder!

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
3.2 PROYECTO 2: DOS BOTONES, UNA LUZ (AND)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

OBJETIVO:
  Necesito presionar DOS botones AL MISMO TIEMPO para que
  se encienda el LED.

HARDWARE:
  • Entrada I1 = Botón 1
  • Entrada I2 = Botón 2
  • Salida Q1 = LED

DIAGRAMA LADDER:

┌────────────────────────────────────────────────────────┐
│ // Ambos botones presionados → LED encendido          │
│ ║  [I1]──[I2]─────────────────────(Q1)             ║  │
└────────────────────────────────────────────────────────┘

LÓGICA:
  • Si I1=1 Y I2=1 → Q1=1 (LED encendido)
  • Cualquier otro caso → Q1=0 (LED apagado)

TABLA DE VERDAD:
┌─────┬─────┬──────┐
│ I1  │ I2  │  Q1  │
├─────┼─────┼──────┤
│  0  │  0  │  0   │
│  0  │  1  │  0   │
│  1  │  0  │  0   │
│  1  │  1  │  1   │ ← Solo enciende aquí
└─────┴─────┴──────┘

ANALOGÍA:
Es como una caja fuerte con dos llaves.
Necesitas AMBAS llaves para abrirla.

USO REAL:
  • Máquinas peligrosas (requieren dos manos para activar)
  • Puertas de seguridad (llave + código)
  • Sistemas críticos (doble confirmación)

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
3.3 PROYECTO 3: CUALQUIER BOTÓN ENCIENDE (OR)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

OBJETIVO:
  Con que presione CUALQUIERA de los dos botones, se enciende
  el LED.

HARDWARE:
  • Entrada I1 = Botón 1
  • Entrada I2 = Botón 2
  • Salida Q1 = LED

DIAGRAMA LADDER:

┌────────────────────────────────────────────────────────┐
│ // Rama 1: Botón 1                                     │
│ ║  [I1]───────────────────────────(Q1)             ║  │
│ ║                                                   ║  │
│ // Rama 2: Botón 2 (en paralelo)                      │
│ ║  [I2]───────────────────────────╯                ║  │
└────────────────────────────────────────────────────────┘

En uPLC v4:
1. Crear primer rung con I1 → Q1
2. Clic derecho sobre el rung → "Agregar rama"
3. Poner I2 en la nueva rama
4. ¡Listo!

LÓGICA:
  • Si I1=1 O I2=1 → Q1=1
  • Solo si ambos están apagados → Q1=0

TABLA DE VERDAD:
┌─────┬─────┬──────┐
│ I1  │ I2  │  Q1  │
├─────┼─────┼──────┤
│  0  │  0  │  0   │ ← Solo apaga aquí
│  0  │  1  │  1   │
│  1  │  0  │  1   │
│  1  │  1  │  1   │
└─────┴─────┴──────┘

ANALOGÍA:
Es como tener dos interruptores de luz en una escalera.
Desde arriba O desde abajo, podés encender la luz.

USO REAL:
  • Luces con múltiples interruptores
  • Múltiples botones de parada de emergencia
  • Sensores redundantes

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
3.4 PROYECTO 4: LUZ DE ESCALERA AUTOMÁTICA
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

OBJETIVO:
  Al presionar un botón, la luz se enciende y se queda prendida
  durante 1 minuto. Luego se apaga sola.

HARDWARE:
  • Entrada I1 = Botón pulsador
  • Salida Q1 = Luz
  • Timer T0 = Temporizador de 60 segundos

DIAGRAMA LADDER:

┌────────────────────────────────────────────────────────┐
│ // Rung 1: Botón inicia timer de 60 segundos          │
│ ║  [I1]───────────────────────────[TON:T0=60000]   ║  │
│                                                        │
│ // Rung 2: Luz encendida mientras timer no termine    │
│ ║  [T0 NC]────────────────────────(Q1)             ║  │
└────────────────────────────────────────────────────────┘

EXPLICACIÓN DETALLADA:

Rung 1:
  • Cuando presiono I1, arranca el timer T0
  • El timer está configurado para 60000 milisegundos (60 segundos)
  • Una vez iniciado, empieza a contar

Rung 2:
  • T0 NC significa "Timer 0 Normalmente Cerrado"
  • Mientras el timer NO haya terminado, T0 NC deja pasar corriente
  • Por lo tanto, Q1 está encendida
  • Cuando el timer llega a 60 segundos, T0 se activa
  • T0 NC ya no deja pasar → Q1 se apaga

SECUENCIA TEMPORAL:

t=0s:    Presiono botón → Timer inicia → Luz ON
t=10s:   Timer contando → Luz ON
t=30s:   Timer contando → Luz ON
t=59s:   Timer contando → Luz ON
t=60s:   Timer termina → Luz OFF

¿QUÉ PASA SI VUELVO A PRESIONAR EL BOTÓN?
  → El timer se reinicia y vuelve a contar desde cero
  → La luz permanece encendida

USO REAL:
  • Luces de escaleras en edificios
  • Baños públicos
  • Pasillos
  • Garajes

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
3.5 PROYECTO 5: CONTROL DE TEMPERATURA
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

OBJETIVO:
  Controlar la temperatura de una habitación:
  • Si temperatura > 25°C → Encender ventilador
  • Si temperatura < 20°C → Encender calefactor
  • Entre 20-25°C → Todo apagado

HARDWARE:
  • A0 = Sensor de temperatura (LM35)
  • Q1 = Ventilador
  • Q2 = Calefactor
  • V0 = Variable para guardar temperatura

CONVERSIÓN:
Si usamos sensor LM35:
  • 0-255 en A0 representa 0-100°C
  • Entonces:
    - 20°C ≈ 51 (20 * 255/100)
    - 25°C ≈ 64 (25 * 255/100)

DIAGRAMA LADDER:

┌────────────────────────────────────────────────────────┐
│ // Rung 1: Leer temperatura                           │
│ ║  [ADC:A0]───────────────────────[SET_VAR:V0]     ║  │
│                                                        │
│ // Rung 2: Si hace calor, ventilador                  │
│ ║  [V0 > 64]──────────────────────(Q1 Ventilador)  ║  │
│                                                        │
│ // Rung 3: Si hace frío, calefactor                   │
│ ║  [V0 < 51]──────────────────────(Q2 Calefactor)  ║  │
└────────────────────────────────────────────────────────┘

COMPORTAMIENTO:

Temperatura = 15°C (V0 = 38):
  ✅ V0 < 51 → Q2 ON (calefactor)
  ❌ V0 > 64 → Q1 OFF (ventilador apagado)

Temperatura = 22°C (V0 = 56):
  ❌ V0 < 51 → Q2 OFF
  ❌ V0 > 64 → Q1 OFF
  → Todo apagado (zona de confort)

Temperatura = 30°C (V0 = 77):
  ❌ V0 < 51 → Q2 OFF
  ✅ V0 > 64 → Q1 ON (ventilador)

MEJORA: Agregar HISTÉRESIS
Para evitar que el sistema se encienda y apague constantemente,
podemos agregar un "margen":

Ventilador:
  • Encender si temperatura > 26°C
  • Apagar si temperatura < 24°C

Esto evita el "efecto rebote" donde el ventilador se prende y
apaga muy rápido.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
3.6 PROYECTO 6: TANQUE DE AGUA AUTOMÁTICO
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

OBJETIVO:
  Sistema de llenado automático de tanque:
  • Sensor nivel bajo → Bomba ON
  • Sensor nivel alto → Bomba OFF
  • Protección: Bomba max 5 minutos ON (evita quemar motor si hay fuga)

HARDWARE:
  • I1 = Sensor nivel bajo (flotante inferior)
  • I2 = Sensor nivel alto (flotante superior)
  • Q1 = Bomba de agua
  • T0 = Timer de protección (5 minutos = 300000 ms)
  • M0 = Memoria "bomba activada alguna vez"

DIAGRAMA LADDER:

┌────────────────────────────────────────────────────────┐
│ // Rung 1: Nivel bajo y NO nivel alto → Bomba ON     │
│ ║  [I1 bajo]──[I2 alto NC]────────(Q1 Bomba)       ║  │
│                                                        │
│ // Rung 2: Si bomba encendida, arrancar timer        │
│ ║  [Q1]───────────────────────────[TON:T0=300000]  ║  │
│                                                        │
│ // Rung 3: Si timer termina, apagar bomba (protección)│
│ ║  [T0]───────────────────────────(Q1 NC)          ║  │
│                                                        │
│ // Rung 4: Si timer termina, activar alarma           │
│ ║  [T0]───────────────────────────(Q2 Alarma)      ║  │
└────────────────────────────────────────────────────────┘

EXPLICACIÓN:

Rung 1 - Lógica básica:
  • I1 = Sensor nivel bajo (se activa cuando falta agua)
  • I2 NC = Sensor nivel alto negado (se activa cuando NO está lleno)
  • Condición: Falta agua Y no está lleno → Bomba ON

Rung 2 - Timer de protección:
  • Si Q1 está encendida, arranca timer de 5 minutos
  • Si la bomba sigue 5 minutos prendida → Hay un problema

Rung 3 - Apagado forzado:
  • Si T0 termina (5 minutos), forzar Q1 OFF
  • Esto protege el motor de quemarse

Rung 4 - Alarma:
  • Si T0 termina, hay un problema (fuga, sensor roto, etc)
  • Activar alarma Q2

SECUENCIA NORMAL:

1. Tanque vacío:
   I1=1 (bajo), I2=0 (no alto) → Bomba ON

2. Llenando:
   I1=1, I2=0 → Bomba ON

3. Nivel medio:
   I1=0, I2=0 → Bomba OFF (rung 1 no se cumple)

4. Tanque lleno:
   I1=0, I2=1 → Bomba OFF

SECUENCIA ANORMAL (Fuga):

1. Bomba ON por 5 minutos seguidos
2. Timer T0 termina
3. Bomba OFF forzado (Rung 3)
4. Alarma ON (Rung 4)
5. Usuario debe revisar el sistema

═══════════════════════════════════════════════════════════════════
PARTE 4 - COMUNICACIÓN MODBUS (AVANZADO)
═══════════════════════════════════════════════════════════════════

Esta parte es OPCIONAL y más avanzada.
Si recién estás empezando, podés saltearla.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
4.1 ¿QUÉ ES MODBUS Y PARA QUÉ SIRVE?
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

ANALOGÍA SIMPLE:
Imaginate que tenés varios Arduinos separados que necesitan
"hablarse entre sí".

Sin Modbus:
  Cada Arduino está solo, no puede saber qué está pasando en el otro.

Con Modbus:
  Todos los Arduinos están conectados por un "teléfono" (cable RS485)
  y pueden preguntarse cosas:
  
  Arduino 1: "¿Cuál es tu temperatura?"
  Arduino 2: "25 grados"
  Arduino 1: "OK, voy a encender el ventilador"

EJEMPLO REAL:
Tenés un sistema de climatización con:
  • Arduino 1 (Master): Controla el ventilador
  • Arduino 2 (Slave): Lee temperatura del living
  • Arduino 3 (Slave): Lee temperatura del dormitorio
  • Arduino 4 (Slave): Lee temperatura del baño

El Master pregunta a cada Slave su temperatura y decide
qué hacer.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
4.2 CONCEPTOS BÁSICOS MODBUS
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

ROLES:

MASTER (Jefe):
  • Hace las preguntas
  • Envía comandos
  • Controla la comunicación
  • Solo puede haber UNO

SLAVE (Empleado):
  • Responde cuando le preguntan
  • Obedece comandos
  • Tiene un ID único (1, 2, 3, ...)
  • Puede haber VARIOS

REGISTROS:
Son como "cajitas de memoria" donde guardás datos.
Cada Arduino tiene 10 registros: MB0, MB1, ... MB9

Ejemplo:
  Arduino Slave ID=2:
    MB0 = Temperatura (ej: 25)
    MB1 = Humedad (ej: 60)
    MB2 = Luz (ej: 128)

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
4.3 EJEMPLO MODBUS: LEER TEMPERATURA REMOTA
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

OBJETIVO:
  Arduino Master lee la temperatura de un Arduino Slave cada
  segundo y enciende un ventilador si hace calor.

HARDWARE:
  • Arduino Master (ID=1) con ventilador en Q1
  • Arduino Slave (ID=2) con sensor temperatura
  • Cable RS485 conectando ambos

DIAGRAMA LADDER (MASTER):

┌────────────────────────────────────────────────────────┐
│ // Rung 1: Timer para leer cada 1 segundo             │
│ ║  [TON:T0=1000]──────────────────[TON:T0=1000]   ║  │
│                                                        │
│ // Rung 2: Cuando timer termina, leer Slave ID=2     │
│ ║  [T0]───────────────────────────[MB_READ:MB0,S:2]║  │
│                                                        │
│ // Rung 3: Si temperatura > 80, ventilador            │
│ ║  [MB0 > 80]─────────────────────(Q1)             ║  │
└────────────────────────────────────────────────────────┘

EXPLICACIÓN:

Rung 1:
  • Timer que se repite cada 1 segundo
  • Es como un reloj que "tic-tac" cada segundo

Rung 2:
  • Cuando el timer termina (T0 se activa)
  • Ejecuta MB_READ:
    - Lee del Slave ID=2
    - Guarda el valor en MB0 (registro local del Master)

Rung 3:
  • Compara MB0 con 80
  • Si MB0 > 80 → Ventilador ON

CÓDIGO SLAVE (COMPLEMENTO):
El Slave debe tener un sketch que:
1. Lee el sensor de temperatura
2. Guarda el valor en su registro MB0
3. Responde cuando el Master pregunta

(Ver archivo Modbus_Slave_Temperatura.ino en los ejemplos)

═══════════════════════════════════════════════════════════════════
PARTE 5 - TIPS Y TRUCOS
═══════════════════════════════════════════════════════════════════

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
5.1 ERRORES COMUNES
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

❌ ERROR 1: "No pasa nada cuando presiono el botón"

POSIBLES CAUSAS:
  • Botón mal conectado
  • Pin incorrecto en el código
  • No cargaste el sketch al Arduino

SOLUCIÓN:
  1. Verificar conexión física del botón
  2. Verificar que usaste el pin correcto (I1=D2, I2=D4, etc)
  3. Verificar que cargaste el sketch (ver luz del Arduino parpadeando)

❌ ERROR 2: "La salida no se enciende"

POSIBLES CAUSAS:
  • LED conectado al revés (ánodo/cátodo)
  • Pin incorrecto
  • Falta resistencia limitadora en el LED

SOLUCIÓN:
  1. Verificar polaridad del LED (pata larga = +)
  2. Verificar pin correcto (Q1=D13, Q2=D14, etc)
  3. Agregar resistencia de 220Ω en serie con el LED

❌ ERROR 3: "El timer no funciona"

POSIBLES CAUSAS:
  • Tiempo en milisegundos mal calculado
  • Referencia al timer incorrecta

SOLUCIÓN:
  • Recordar: 1000 ms = 1 segundo
  • Verificar que usás T0 NC cuando querés que algo esté activo
    MIENTRAS el timer no termine

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
5.2 BUENAS PRÁCTICAS
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

✅ COMENTARIOS CLAROS:
Siempre poné comentarios en cada rung explicando qué hace.

Mal:
┌────────────────────────────────────────────────────────┐
│ ║  [I1]──[I2]─────────────────────(Q1)             ║  │
└────────────────────────────────────────────────────────┘

Bien:
┌────────────────────────────────────────────────────────┐
│ // Ambos botones de seguridad → Motor ON              │
│ ║  [I1]──[I2]─────────────────────(Q1 Motor)       ║  │
└────────────────────────────────────────────────────────┘

✅ NOMBRES DESCRIPTIVOS:
Usá nombres que describan qué es cada cosa.

En vez de: I1, I2, Q1
Mejor:    Botón Start, Botón Stop, Motor Bomba

(Esto se hace en los comentarios, ya que el programa usa I1, Q1, etc)

✅ TESTEAR DE A POCO:
No hagas todo el programa de una.
Probá cada parte por separado:

1. Primero: botón → luz
2. Después: agregar timer
3. Después: agregar sensores
4. Al final: integrar todo

✅ GUARDAR VERSIONES:
Guardá el proyecto con números de versión:
  • mi_proyecto_v1.uplc
  • mi_proyecto_v2.uplc
  • mi_proyecto_v3.uplc

Así si algo sale mal, podés volver atrás.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
5.3 CÓMO TESTEAR TU PROGRAMA
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

PASO 1: SIMULACIÓN MENTAL
Antes de cargar al Arduino, "ejecutá" el programa en tu cabeza:

"Si presiono I1... entonces pasa corriente... entonces se activa Q1"

PASO 2: VERIFICAR CONEXIONES
Con el Arduino SIN ALIMENTAR:
  • Verificar que cada entrada esté conectada
  • Verificar que cada salida esté conectada
  • Verificar polaridad de LEDs
  • Verificar que no haya cortos

PASO 3: PROBAR SIN CARGA
Primero probá con LEDs (carga pequeña) antes de conectar motores.

PASO 4: MONITOREAR CON EL LCD
El display LCD muestra en tiempo real:
  • Estados de entradas (I1-I7)
  • Estados de salidas (Q1-Q6)
  • Valores analógicos (A0, A1)

Usalo para verificar que todo funciona como esperás.

PASO 5: USAR EL MONITOR SERIAL
Abrí el Monitor Serial (Tools → Serial Monitor) a 9600 bps.
Podés agregar mensajes de debug en el código si hace falta.

═══════════════════════════════════════════════════════════════════
EJERCICIOS FINALES
═══════════════════════════════════════════════════════════════════

EJERCICIO 1: Semáforo Simple
  Objetivo: Hacer un semáforo que alterne rojo-amarillo-verde
  Hardware: Q1=Rojo, Q2=Amarillo, Q3=Verde
  Tiempos: Rojo 30s, Amarillo 3s, Verde 27s

EJERCICIO 2: Alarma de Intruso
  Objetivo: Si se abre una puerta O una ventana, suena alarma
  Hardware: I1=Sensor puerta, I2=Sensor ventana, Q1=Sirena
  Extra: Agregar botón I3 para desactivar alarma

EJERCICIO 3: Riego Automático
  Objetivo: Regar el jardín todos los días a las 6AM por 15 minutos
  Hardware: Q1=Electroválvula, I1=Sensor humedad tierra
  Lógica: Si humedad < 30% → regar

EJERCICIO 4: Control de Parking
  Objetivo: Contar autos que entran/salen, mostrar espacios disponibles
  Hardware: I1=Sensor entrada, I2=Sensor salida, Variables para contar

═══════════════════════════════════════════════════════════════════
RECURSOS ADICIONALES
═══════════════════════════════════════════════════════════════════

📚 Documentación:
  • MODBUS_GUIDE.md - Guía completa de Modbus
  • EJEMPLO_MODBUS.md - Ejemplos prácticos
  • HARDWARE_RS485.md - Conexiones físicas

💻 Ejemplos en la carpeta /ejemplos:
  • Prueba1 a Prueba9 - Ejemplos básicos
  • Modbus_Master_Temperatura - Ejemplo Modbus completo

🎓 Mini Curso:
  • Ver archivo MINI_CURSO_LADDER.md para lecciones paso a paso

═══════════════════════════════════════════════════════════════════
CONTACTO Y SOPORTE
═══════════════════════════════════════════════════════════════════

ETI Patagonia
prof.martintorres@educ.ar
https://eti-patagonia-ar.github.io/ETI-Patagonia-ARG/

¡Que disfrutes programando en Ladder!

═══════════════════════════════════════════════════════════════════
FIN DEL MANUAL
═══════════════════════════════════════════════════════════════════
