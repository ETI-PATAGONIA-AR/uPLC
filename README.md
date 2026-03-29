# uPLC - Conversor Ladder a Arduino

<img width="626" height="511" alt="uPLC" src="https://github.com/user-attachments/assets/b1a2672d-cf28-41fe-b1bf-485c729088b0" />

El campo de la automatización y control por instrumental, es un campo muy amplio y si bien, hasta hoy en día siguen
evolucionando con las nuevas innovaciones tecnológicas, los principios del control, son siempre los mismos. Los avances en
la tecnología software, nos han demostrado más de una vez, que los intérpretes de lenguaje son una estrategia para poder
tener las herramientas a la mano a un bajo coste y un resultado bastante satisfactorio.
Con la siguiente aplicacion y curso en pdf que sume a modo de manual y curso de programacion en LADDER, pretendo introducirlos en los principios básicos del control, mediante las lógicas de contactos y bloques de funciones que tiene nuestra aplicación uPLC.
uPLC es una herramienta de ingeniería desarrollada por ETI Patagonia diseñada para cerrar la brecha entre la programación 
industrial y la electrónica embebida. Esta aplicación permite a usuarios y estudiantes diseñar sistemas de control mediante 
Lógica de Contactos (Ladder) y convertirlos automáticamente en código ejecutable (.ino) para plataformas Arduino Nano (Proximamente daremos el link del hardware).
Esta versión optimiza el flujo de trabajo al automatizar la gestión de archivos y mejorar la precisión de las instrucciones analógicas,
permitiendo que un diseño visual se transforme en un proyecto de firmware completo en segundos.

## Introducción
Como ya mencioné en reiteradas ocasiones, el campo de la automatización y control, es un campo muy amplio al igual que el campo de la instrumentación. Este sistema de control de procesos, no tuvo su origen cuando aparecieron en el mercado los PLC. En si, no voy a
emplazarme hasta aquellas épocas para contarles con detalles cual fue su evolución, pero tratare de esforzarme y ser breve para crearles una noción básica. 
Esta es una ciencia que hace su aparición mucho antes de que el hombre descubriera la electricidad; si bien era bastante precaria, el ingenio del hombre, lo llevo a conocer y estudiar otras ciencias para aprender a emplearlas en sus automatismos (leyes de la física tales
como palancas, poleas, niveles y hasta presión y caudal).
La automatización, hasta hoy en día fue evolucionando con las nuevas innovaciones tecnológicas hasta tener lo que llamamos controladores lógicos programables de la era análoga-digital; pero hasta hace tan solo unas décadas atrás, el hombre implementa su ingenio nuevamente, y descubre que controlando el paso de la energía, se puede hacer automatismos con lógicas cableadas y contactos.
Los 1eros PLC, eran sencillamente eso, inmensos tableros llenos de relay y cables que estaban armados de tal manera que daban una secuencia de permisos y condiciones para funcionar. Si bien eran muy lentos en el diseño y armado, también tenía la contra de que si se
quería reformar su lógica de funcionamiento, había que arrancar prácticamente desde cero. A este tipo de sistemas, se los denomina: “Automatización con lógicas de contactos”.
Con la aparición de nuevos instrumentos y procesadores electrónicos, esas inmensas estructuras de relay, se fueron achicando y simplificando, hasta llegar a lo que hoy en día conocemos como: “Controladores Lógicos Programables”

## Por qué Arduino:
La selección de Arduino como núcleo de uPLC responde a una visión estratégica: convertir la complejidad industrial en accesibilidad universal. A diferencia de entornos cerrados o más complejos como CCS, PBP o ASM, Arduino ha derribado las barreras de entrada al
mundo de los microcontroladores.

## Elegimos esta plataforma por tres pilares clave:
- Escalabilidad y Costos: Hardware accesible que permite prototipar a bajo costo y escalar a soluciones industriales competitivas.
 Soporte Global: Una comunidad masiva y documentación inagotable que garantizan la sostenibilidad del proyecto a largo plazo.
- Reducción de la Brecha Digital: Es la herramienta que mejor comunica el mundo académico con el profesional.

Mi más sincero agradecimiento a Massimo Banzi, David Cuartielles, Tom Igoe, Gianluca Martino y David Mellis. Su visión no solo creó una placa, sino un lenguaje universal que hoy nos permite llevarte este interprete para la programación de un control lógico programable (PLC) a tu aula y cada escritorio mediante uPLC.

## El puente entre dos mundos

Había una vez un electricista que toda su vida diseñó circuitos con relés, contactores y temporizadores mecánicos. Escuchaba el zumbido característico de las bobinas zumbando por suciedad, el tableteo cuando algo se pegaba, y sabía detectar el cable recalentado por el color del aislante e incluso, sus tester naturales (sus manos y olfato)... Esa era la vieja escuela; Montaba tableros con lógica cableada, probaba con multímetro y pinza amperométrica, y dormía tranquilo sabiendo que sus automatismos funcionaban sin bugs/errores, ni actualizaciones. Hoy, a sus 60 años, ve el mundo cambiar: los PLCs ahora se programan en ladder, pero también en bloques, en código... y él se quedó en el medio, sin puente hacia el otro lado.

Había una vez un nene de 10 años que jamás vio un relé, jamás olió un motor sobrecalentado o escucho el tableteo de un contactor, pero sí sabe desbloquear un celular antes que su abuelo. Juega, crea, comparte. Pero cuando quiere hacer un proyecto real -encender una luz, sensar la temperatura, mover un motor- el salto parece imposible: tiene que aprender programación, sintaxis, compilación... un mundo abstracto que no le conecta con lo tangible.

<img width="2851" height="976" alt="uPLC" src="https://github.com/user-attachments/assets/f7178b6f-e769-4e0a-9811-61ec0d319e87" />

**uPLCv6 Blocks & uPLCv5 Ladder** es ese puente.

No es solo un editor de bloques. Es una herramienta que busca acortar la brecha tecnológica entre quienes aprendieron con lógica de contactos y quienes nacieron con pantallas táctiles. Es un espacio donde un veterano de la industria puede entender a su nieto, y donde un niño puede mostrarle a su abuelo que "programar" no es tan distinto de "conectar cables".

---

## Dos modos, un mismo objetivo

| Modo | Para quién es | Cómo se programa |
|------|---------------|------------------|
| **🎮 Blocks** | Niños, principiantes, adultos sin experiencia previa | Arrastrás y encastrás bloques visuales |
| **⚡ Ladder** | Técnicos, electricistas, veteranos de la industria | Dibujás contactos y bobinas como en un PLC |

Ambos generan código Arduino (.ino) listo para cargar en tu placa.

[![Ver el video de la version LADDER en YouTube](https://img.youtube.com)](https://www.youtube.com/watch?v=C1CCBDz9oY0)

[![Ver el video de la version Blocks en YouTube](https://img.youtube.com)](https://www.youtube.com/watch?v=49mqdL1b_lU)

[![Ver un DEMO de juegos con la version Blocks en YouTube](https://img.youtube.com)](https://www.youtube.com/watch?v=15fIcUH5IJs)

![PCB1](https://github.com/user-attachments/assets/cdef1875-237e-40d4-a2ae-8b6ee202cb1a)

![PCB2](https://github.com/user-attachments/assets/c38c6cb8-3e8a-41b8-955d-9b668b87bc50)

![PCB3](https://github.com/user-attachments/assets/1df96635-5805-4548-b157-f8a4c84b3d90)

<img width="901" height="633" alt="simu_uPLC_v5" src="https://github.com/user-attachments/assets/ab5d77d6-26f9-4c23-9075-6391f31e70d1" />

<img width="1366" height="720" alt="Ctl_VENTILACION_SIMU" src="https://github.com/user-attachments/assets/27719060-fc7e-43a2-91ae-bb8316cdf97d" />

## 🆕 Novedades en la version LADDER v5.1:

## Curso Manual de uPLC
1. ✅ el nuevo manual que adjunto, inicia con un breve curso de programación ladder, y con ejemplos prácticos les enseño a usar cada modulo de función de uPLC.

<img width="303" height="429" alt="eBook_1" src="https://github.com/user-attachments/assets/08143343-571c-4278-baed-fc7b7bb8dfd4" />

<img width="305" height="431" alt="eBook_2" src="https://github.com/user-attachments/assets/0c611627-e288-4638-82e9-f22707b53d3d" />

<img width="305" height="431" alt="eBook_3" src="https://github.com/user-attachments/assets/ffd868cd-2083-4990-9dc0-f51d29bb30c0" />

<img width="305" height="431" alt="eBook_4" src="https://github.com/user-attachments/assets/a32f61e6-0acd-4aad-b13f-32941dbccb77" />

--- 

## 🆕 Novedades en la version BLOCKS v6:

### Nuevas Características
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


### PROXIMA ACTUALIZACION DE uPLC
1. ✅ Soporte para hardware con Arduino NANO
2. ✅ Soporte para Hardware con ESP32
3. ✅ Dashboard nativo con conexión USB (ESP32-Arduino Nano) - WIFI (ESP32).

## Soporte Técnico

ETI Patagonia - prof.martintorres@educ.ar

