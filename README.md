# uPLC - Conversor Ladder a Arduino

<img width="626" height="511" alt="IndustrINO_uPLCv4" src="https://github.com/user-attachments/assets/497bd976-d728-4444-b14b-db134e2aeea2" />

uPLC es una herramienta de ingeniería desarrollada por ETI Patagonia diseñada para cerrar la brecha entre la programación 
industrial y la electrónica embebida. Esta aplicación permite a usuarios y estudiantes diseñar sistemas de control mediante 
Lógica de Contactos (Ladder) y convertirlos automáticamente en código ejecutable (.ino) para plataformas Arduino Nano (Proximamente daremos el link del hardware).
Esta versión 3.0 optimiza el flujo de trabajo al automatizar la gestión de archivos y mejorar la precisión de las instrucciones analógicas,
permitiendo que un diseño visual se transforme en un proyecto de firmware completo en segundos.

<img width="1366" height="720" alt="uPLC_v3" src="https://github.com/user-attachments/assets/5ea9ebd1-25c3-435a-9b89-0e9a143f8035" />

[![Ver el video de la version 3 en YouTube](https://img.youtube.com)](https://www.youtube.com/watch?v=C1CCBDz9oY0)

<img width="813" height="571" alt="SIM_uPLC_v3" src="https://github.com/user-attachments/assets/32f0911d-ae4e-486d-a6f3-76e01a7e884b" />

<img width="1366" height="720" alt="Ctl_VENTILACION_SIMU" src="https://github.com/user-attachments/assets/27719060-fc7e-43a2-91ae-bb8316cdf97d" />


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



## Soporte Técnico

ETI Patagonia - prof.martintorres@educ.ar

