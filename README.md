# uPLC - Conversor Ladder a Arduino

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

<img width="1366" height="720" alt="uPLC_v3" src="https://github.com/user-attachments/assets/5ea9ebd1-25c3-435a-9b89-0e9a143f8035" />

[![Ver el video de la version 3 en YouTube](https://img.youtube.com)](https://www.youtube.com/watch?v=C1CCBDz9oY0)

<img width="813" height="571" alt="SIM_uPLC_v3" src="https://github.com/user-attachments/assets/32f0911d-ae4e-486d-a6f3-76e01a7e884b" />

<img width="1366" height="720" alt="Ctl_VENTILACION_SIMU" src="https://github.com/user-attachments/assets/27719060-fc7e-43a2-91ae-bb8316cdf97d" />

<img width="626" height="511" alt="IndustrINO_uPLCv4" src="https://github.com/user-attachments/assets/497bd976-d728-4444-b14b-db134e2aeea2" />

## 🆕 Novedades en la version v4.1: Se suman Modbus RS485 - Q6 

### Nuevas Características
1. ✅ **Comunicación Modbus RS485**: Protocolo industrial estándar
2. ✅ **6 Salidas Digitales**: Q1-Q6 (antes solo Q1-Q5)
3. ✅ **10 Registros Modbus**: MB0-MB9 para comunicación
4. ✅ **Nuevos Bloques Ladder**:
   - **MB_SLAVE**: Condición sobre registro Modbus
   - **MB_READ**: Leer registro de dispositivo esclavo
   - **MB_WRITE**: Escribir registro a dispositivo esclavo
5. ✅ **Compatible con PLCs industriales**: Protocolo Modbus RTU estándar

### Correcciones Anteriores (v3.0)
1. ✅ **PWM corregido**: Ahora genera correctamente `analogWrite(pin, valor)` en lugar de solo asignar la variable
2. ✅ **SET_VAR con ADC**: Cuando se usa ADC seguido de SET_VAR sin valor explícito, automáticamente toma la referencia del ADC
3. ✅ **AND/OR**: Funcionando correctamente

### Nuevas Funcionalidades
1. ✅ **Creación de carpetas**: Al guardar un proyecto, se crea una carpeta con el nombre del proyecto
2. ✅ **Archivos generados**: 
   - `proyecto.uplc` (archivo Ladder)
   - `proyecto.ino` (sketch Arduino listo para cargar)
3. ✅ **Display LCD I2C 20x4**: Soporte integrado para mostrar estados en tiempo real
   - Dirección I2C: 0x27
   - Conectado en A4 (SDA) y A5 (SCL)
   - Muestra entradas digitales (I1-I7)
   - Muestra salidas digitales (Q1-Q6)
   - Muestra valores analógicos (A0, A1)
   - Muestra duty cycle del PWM (0-100%)

## Formato del Display LCD
```
Línea 0: I1 2 3 4 5 6 7 A0XXX
Línea 1:  X X X X X X X A1XXX
Línea 2: Q1 2 3 4 5 6 7 PWMXX
Línea 3:  X X X X X X X
```
Donde X = 0 o 1 (estado digital), PWM = 00-99% (duty cycle)

<img width="1024" height="1536" alt="PORTADA_uPLC_2" src="https://github.com/user-attachments/assets/78f7095e-adbc-41ea-992a-87022e382025" />

## Soporte Técnico

ETI Patagonia - prof.martintorres@educ.ar

