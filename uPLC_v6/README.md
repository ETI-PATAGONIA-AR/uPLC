# uPLCv6 Blocks 🎮

## Modo Bloques 

<img width="1366" height="768" alt="uplc_v6_Bloques" src="https://github.com/user-attachments/assets/a8c417ce-14e6-4b73-891d-5cbf71faf683" />

https://github.com/user-attachments/assets/5e1c871c-59c6-4b07-917a-9a745d52c4ea

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

## Un proyecto para compartir

uPLCv6, al igual que ProfeAI (un profe particular con IA), nació en ETI Patagonia como herramienta pedagógica. Su idea es la integracion y empleo en escuelas primarias, secundarias, en escuelas de oficios técnicos, en cursos de capacitación, en el taller del técnico experimentado que quiere entender microcontroladores, en el aula del niño que quiere ir más allá del Minecraft.

Los ejemplos incluidos van desde lo más simple (LED parpadeando) hasta lo más divertido (juego de dados, piano, melodías). Cada uno es un peldaño.

**La meta no es que todos sean programadores. La meta es que nadie se quede afuera.**

---

## Contacto

**ETI Patagonia** - prof.martintorres@educ.ar
