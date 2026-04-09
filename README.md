# uPLC - Conversor Ladder a Arduino / Bloques a Arduino

<img width="935" height="391" alt="e_book_uPLC" src="https://github.com/user-attachments/assets/b2f5c9c5-4906-4d7f-973d-3da76ca0347b" />

[![Python](https://img.shields.io/badge/Python-3.10+-blue)](https://python.org)
[![License](https://img.shields.io/badge/Licencia-MIT-green)](#licencia)
[![Demo version LADDER en YouTube en YouTube](https://img.shields.io/badge/▶_Ver_demo-YouTube-red)](https://www.youtube.com/watch?v=C1CCBDz9oY0)
[![Demo version Blocks en YouTube](https://img.shields.io/badge/▶_Ver_demo-YouTube-red)](https://www.youtube.com/watch?v=49mqdL1b_lU)
[![Demo juegos con la version Blocks en YouTube](https://img.shields.io/badge/▶_Ver_demo-YouTube-red)](https://www.youtube.com/watch?v=15fIcUH5IJs)
[![Demo como implementar SubProgramas (Funciones) con la version Blocks en YouTube](https://img.shields.io/badge/▶_Ver_demo-YouTube-red)](https://www.youtube.com/watch?v=N7N2FZKEy5g)

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

## Tress modos, un mismo objetivo

| Modo | Para quién es | Cómo se programa |
|------|---------------|------------------|
| **🎮 BLOCKSv6** | Niños, principiantes, adultos sin experiencia previa | Arrastrás y encastrás bloques visuales |
| **⚡ LADDERv5.3** | Principiantes, Adultos sin experiencia previa, Técnicos, electricistas, veteranos de la industria | Dibujás contactos y bobinas como en un PLC |
| **⚡LADDERvPRO** | Técnicos, electricistas, veteranos de la industria | Dibujás contactos y bobinas como en un PLC |

Ambos generan código Arduino (.ino) listo para cargar en tu placa.

---

## 🆕 Novedades en la version LADDER v5.3:

## Curso Manual de uPLC
1. ✅ el nuevo manual que adjunto, inicia con un breve curso de programación ladder, y con ejemplos prácticos les enseño a usar cada modulo de función de uPLC.

<img width="303" height="429" alt="eBook_1" src="https://github.com/user-attachments/assets/08143343-571c-4278-baed-fc7b7bb8dfd4" />
<img width="305" height="431" alt="eBook_2" src="https://github.com/user-attachments/assets/0c611627-e288-4638-82e9-f22707b53d3d" />
<img width="305" height="431" alt="eBook_3" src="https://github.com/user-attachments/assets/ffd868cd-2083-4990-9dc0-f51d29bb30c0" />
<img width="305" height="431" alt="eBook_4" src="https://github.com/user-attachments/assets/a32f61e6-0acd-4aad-b13f-32941dbccb77" />

---

## 🆕 Novedades en la version Blocks v6:

## Curso Manual de uPLC
1. ✅ el nuevo manual que adjunto, inicia con un breve curso de programación blocks, y con ejemplos prácticos les enseño a usar cada modulo de función de uPLC.

<img width="305" height="431" alt="Block_1" src="https://github.com/user-attachments/assets/163d8f28-3eb7-4c0b-9e9c-27402a795d52" />
<img width="305" height="431" alt="Block_2" src="https://github.com/user-attachments/assets/038183b6-183c-4522-9e81-6c046aeded4c" />
<img width="305" height="431" alt="Block_3" src="https://github.com/user-attachments/assets/d90c5f19-7941-4396-b46e-11e682d7a935" />
<img width="305" height="431" alt="Block_4" src="https://github.com/user-attachments/assets/c7bd9ca5-df9d-4d34-8d19-816f4a06de51" />

---

### PROXIMA ACTUALIZACION DE uPLC
1. ✅ Soporte para hardware con Arduino NANO
2. ✅ Soporte para Hardware con ESP32
3. ✅ Dashboard nativo con conexión USB (ESP32-Arduino Nano) - WIFI (ESP32).

## Soporte Técnico

ETI Patagonia - prof.martintorres@educ.ar





![PCB1](https://github.com/user-attachments/assets/cdef1875-237e-40d4-a2ae-8b6ee202cb1a)

![PCB2](https://github.com/user-attachments/assets/c38c6cb8-3e8a-41b8-955d-9b668b87bc50)

![PCB3](https://github.com/user-attachments/assets/1df96635-5805-4548-b157-f8a4c84b3d90)

<img width="901" height="633" alt="simu_uPLC_v5" src="https://github.com/user-attachments/assets/ab5d77d6-26f9-4c23-9075-6391f31e70d1" />

<img width="1366" height="720" alt="Ctl_VENTILACION_SIMU" src="https://github.com/user-attachments/assets/27719060-fc7e-43a2-91ae-bb8316cdf97d" />

