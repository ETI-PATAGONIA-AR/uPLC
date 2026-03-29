
## ⚡ Modo Ladder: el lenguaje del técnico

<img width="1366" height="976" alt="uplc_v6_Ladder" src="https://github.com/user-attachments/assets/01e3e565-b5f3-4215-a3d9-85c30149e720" />

Si venís del mundo de los PLCs, del Autómata programable o de los tableros con lógica cableada, el modo Ladder te va a resultar familiar. Acá no se usan bloques, se dibuja.

Es la misma lógica que usabas en los painéis de relés, pero ahora se convierte automáticamente en código Arduino. Y lo mejor: si ya sabés ladder, no tenés que aprender nada nuevo para empezar a programar microcontroladores.

### Elementos disponibles en Ladder

| Elemento | Descripción |
|----------|-------------|
| **NO (Contacto Normally Open)** | Se activa cuando la entrada está en HIGH |
| **NC (Contacto Normally Closed)** | Se activa cuando la entrada está en LOW |
| **COIL (Bobina)** | Activa una salida cuando hay continuidad |
| **COIL_NC (Bobina negada)** | Desactiva la salida |
| **COIL_RM (Registro de memoria)** | Guarda el estado (como un relay auxiliar) |
| **TON (Timer ON-Delay)** | Temporizador que enclava al activar |
| **TOF (Timer OFF-Delay)** | Temporizador que desactiva con retardo |
| **CTU (Contador ascendente)** | Cuenta impulsos hacia arriba |
| **CTD (Contador descendente)** | Cuenta impulsos hacia abajo |
| **CTR (Reset contador)** | Reinicia el contador a cero |
| **CMP_GT, CMP_LT, CMP_EQ** | Comparadores: mayor, menor, igual |
| **FUN_AND, FUN_OR, FUN_NOT** | Funciones booleanas |
| **ADD, SUB, MUL, DIV** | Operaciones matemáticas |
| **SET_VAR** | Guardar valor en variable |
| **ADC** | Leer entrada analógica |
| **PWM** | Salida con modulación por ancho de pulso |
| **MB_SLAVE, MB_READ, MB_WRITE** | Comunicación Modbus RS485 |
| **PID** | Controlador proporcional-integral-derivativo |

### Hardware Compatible (Ladder)

- 7 Entradas digitales: I1 a I7
- 5 Salidas digitales: Q1, Q2, Q4, Q5, Q6
- 1 Salida PWM: Q3
- 2 Entradas analógicas: A0, A1
- Display LCD I2C 20x4 (dirección 0x27)
- Comunicación Modbus RTU (RS485)
- 10 Registros Modbus: MB0 a MB9

El display LCD muestra en tiempo real el estado de todas las entradas, salidas y valores analógicos.

---

## Un proyecto para compartir

uPLCv6, al igual que ProfeAI (un profe particular con IA), nació en ETI Patagonia como herramienta pedagógica. Su idea es la integracion y empleo en escuelas primarias, secundarias, en escuelas de oficios técnicos, en cursos de capacitación, en el taller del técnico experimentado que quiere entender microcontroladores, en el aula del niño que quiere ir más allá del Minecraft.

Los ejemplos incluidos van desde lo más simple (LED parpadeando) hasta lo más divertido (juego de dados, piano, melodías). Cada uno es un peldaño.

**La meta no es que todos sean programadores. La meta es que nadie se quede afuera.**

---

## Contacto

**ETI Patagonia** - prof.martintorres@educ.ar
