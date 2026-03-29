# uPLCv6 Blocks 🎮

## El puente entre dos mundos

Había una vez un electricista que toda su vida diseñó circuitos con relés, contactores y temporizadores mecánicos. Escuchaba el zumbido característico de las bobinas zumbando por suciedad, el tableteo cuando algo se pegaba, y sabía detectar el cable recalentado por el color del aislante e incluso, sus tester naturales (sus manos y olfato)... Esa era la vieja escuela; Montaba tableros con lógica cableada, probaba con multímetro y pinza amperométrica, y dormía tranquilo sabiendo que sus automatismos funcionaban sin bugs/errores, ni actualizaciones. Hoy, a sus 60 años, ve el mundo cambiar: los PLCs ahora se programan en ladder, pero también en bloques, en código... y él se quedó en el medio, sin puente hacia el otro lado.

Había una vez un nene de 10 años que jamás vio un relé, jamás olió un motor sobrecalentado o escucho el tableteo de un contactor, pero sí sabe desbloquear un celular antes que su abuelo. Juega, crea, comparte. Pero cuando quiere hacer un proyecto real -encender una luz, sensar la temperatura, mover un motor- el salto parece imposible: tiene que aprender programación, sintaxis, compilación... un mundo abstracto que no le conecta con lo tangible.

**uPLCv6 Blocks & Ladder** es ese puente.

No es solo un editor de bloques. Es una herramienta que busca acortar la brecha tecnológica entre quienes aprendieron con lógica de contactos y quienes nacieron con pantallas táctiles. Es un espacio donde un veterano de la industria puede entender a su nieto, y donde un niño puede mostrarle a su abuelo que "programar" no es tan distinto de "conectar cables".

---

## Dos modos, un mismo objetivo

| Modo | Para quién es | Cómo se programa |
|------|---------------|------------------|
| **🎮 Blocks** | Niños, principiantes, adultos sin experiencia previa | Arrastrás y encastrás bloques visuales |
| **⚡ Ladder** | Técnicos, electricistas, veteranos de la industria | Dibujás contactos y bobinas como en un PLC |

Ambos generan código Arduino (.ino) listo para cargar en tu placa.

Puedes ver un video de uPLC Blocks en: https://youtu.be/49mqdL1b_lU

---

## Modo Bloques 

<img width="1366" height="768" alt="uplc_v6_Bloques" src="https://github.com/user-attachments/assets/a8c417ce-14e6-4b73-891d-5cbf71faf683" />

# Por qué bloques?

Los bloques no son una simplificación child's play. Son una traducción visual de conceptos que en un ladder se dibujan y en C++ se escriben:

- Un contacto NC se convierte en "botón NO presionado"
- Una bobina se convierte en "encender Q1"
- Un temporizador TON se convierte en "Timer T0 completado"
- Una memoria M se convierte en "memoria M0"

Pero además, los bloques permiten ir mucho más allá de la lógica cableada tradicional. Un niño puede hacer un piano, un juego, un termómetro con caras. Un adulto puede conectar un sensor de distancia, un motor, una lógica de bombas con sensores de niveles en tanque y cisterna para un edificio, ver estados de sensores en un display LCD. **Ambos hablan el mismo idioma: el bloque.**

---

## Lo que podés hacer con cada categoría

### 🟡 Inicio
Acá empieza todo. Acá definís qué pasa cuando encendés el sistema ("al iniciar") y qué se repite siempre ("para siempre"). Es como el pulsador con auto enclavamiento para encender una maquina, el void setup y el loop de Arduino, pero con palabras que se entienden.

### 🔧 Funciones
Acá aprendés algo fundamental: el concepto de "subrutina", de código reutilizable. "Llamar" a una función y "retornar" cuando termina. Es el mismo concepto que en un PLC se llama GOSUB. Pero ahora lo ves, lo encastrás, lo entendés.

### 🔷 Control
Los caminos del programa. Acá están los "si... entonces", los "si... sino", los bucles "repetir N veces", "mientras...", "para...". Acá el programa decide, bifurca, itera. Es la lógica misma.

### 🟢 Lógica
Las operaciones booleanas: Y, O, NO, comparaciones. Acá decis cuándo se enciende algo, cuándo se apaga, cuándo el programa va por un camino u otro.

### 📦 Variables y 🧮 Matemática
Donde guardás valores (V0 a V9) y hacés cuentas (sumar, restar, multiplicar, mapear rangos,azar). Acá el programa "recuerda" y "calcula".

### 🔘 Entradas
Los ojos del sistema: botones, sensores, el mundo físico. Botones I1 a I7, entradas analógicas A0 y A1.

### 💡 Salidas
Las manos del sistema: luces, reles, actuadores. Salidas Q1 a Q5, control PWM.

### ⏱ Tiempo y ⏳ Timers
Esperar, medir tiempo, temporizadores que encienden o apagan con retardo. El tiempo es clave en todo automatismo.

### 🔢 Contadores
Contar cosas: impulsos, eventos, partes. Contadores ascendentes, descendentes, con límite.

### 🖥 LCD
La pantalla donde el sistema te habla. Escribir texto, mostrar números, mostrar caras (feliz, triste, sorprendida). Un niño puede hacer que su proyecto "exprese" emociones.

### 🎵 Sonido
El buzzer para hacer beeps, tonos, notas musicales, melodías predefinidas. Un piano con botones, una alarma, una canción de cumpleaños.

### ⚙️ Motores
Control de motor DC (con puente H), servo, PWM. Mover cosas reales.

### 🌡 Sensores
LM35 (temperatura), fotoresistencia (luz), HC-SR04 (distancia), joystick, sensor de lluvia, sensor de obstáculos. Todo lo que el entorno pueda aportar como información.

### 📻 Serial/Radio
Comunicación: enviar y recibir datos por USB o por radio (SoftwareSerial). El sistema hablando con el exterior.

### 🎮 Juego
Esto es lo más lindo: sprites, movimiento, colisiones, puntuación, vidas. Un niño puede construir su propio juego en el LCD y sentir que creó algo suyo.

### 📌 Pines
Control directo de pines para cuando necesitás algo específico.

---



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
