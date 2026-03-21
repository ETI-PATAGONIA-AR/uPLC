# uPLC v3 - Conversor Ladder a Arduino (DEMO GRATUITA)

<img width="1366" height="720" alt="uPLC_v3" src="https://github.com/user-attachments/assets/5ea9ebd1-25c3-435a-9b89-0e9a143f8035" />


uPLC v3 es una herramienta de ingeniería desarrollada por ETI Patagonia diseñada para cerrar la brecha entre la programación 
industrial y la electrónica embebida. Esta aplicación permite a usuarios y estudiantes diseñar sistemas de control mediante 
Lógica de Contactos (Ladder) y convertirlos automáticamente en código ejecutable (.ino) para plataformas Arduino Nano (Proximamente daremos el link del hardware).
Esta versión 3.0 optimiza el flujo de trabajo al automatizar la gestión de archivos y mejorar la precisión de las instrucciones analógicas,
permitiendo que un diseño visual se transforme en un proyecto de firmware completo en segundos.

[![Ver el video en YouTube](https://img.youtube.com)](https://www.youtube.com/watch?v=C1CCBDz9oY0)



## Novedades de esta versión

### Correcciones de Bugs
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
   - Muestra salidas digitales (Q1-Q5)
   - Muestra valores analógicos (A0, A1)
   - Muestra duty cycle del PWM (0-100%)

## Formato del Display LCD
```
I1 2 3 4 5 6 7 A0XXX
 X X X X X X X A1XXX
Q1 2 3 4 5    PWMXXX
 X X X X X 
```

## Instalación de Dependencias (Recuerden que deben de tener instalado Python 3.10)

### Python (PC)
```bash
pip install -r requirements.txt
```

### Arduino IDE
Para usar el Display LCD I2C, instalar la librería desde el Library Manager:
1. Abrir Arduino IDE
2. Ir a: Sketch → Include Library → Manage Libraries
3. Buscar: "LiquidCrystal I2C" by Frank de Brabander
4. Instalar

## Uso

1. **Ejecutar el programa**:
   ```
   run_uPLCv3.bat
   ```

2. **Crear tu programa Ladder**:
   - Usar los botones de la toolbox para agregar contactos, bobinas, funciones, etc.
   - Guardar el proyecto (se creará una carpeta con el nombre del proyecto)

3. **Cargar al Arduino**:
   - Abrir el archivo `.ino` generado en la carpeta del proyecto
   - Conectar el Arduino NANO
   - Seleccionar puerto COM correcto
   - Subir el sketch

4. **Conectar el Display LCD (opcional)**:
   - LCD SDA → Arduino A4
   - LCD SCL → Arduino A5
   - LCD VCC → Arduino 5V
   - LCD GND → Arduino GND

## Pinout Arduino NANO

### Entradas Digitales
- I1 → D2
- I2 → D4
- I3 → D5
- I4 → D6
- I5 → D7
- I6 → D8
- I7 → D9

### Salidas Digitales
- Q1 → D14 (A0)
- Q2 → D15 (A1)
- Q3 → D16 (A2)
- Q4 → D17 (A3)
- Q5 → D3 (PWM)

### Entradas Analógicas
- A0 → A6 (mapeado 0-255)
- A1 → A7 (mapeado 0-255)

### Display LCD I2C
- SDA → A4
- SCL → A5

## Estructura del Proyecto Generado
```
nombre_proyecto/
  ├── nombre_proyecto.uplc  (archivo Ladder - para editar en uPLC)
  └── nombre_proyecto.ino   (sketch Arduino - para cargar al NANO)
```

## Funciones Disponibles

### Contactos
- NO (Normalmente Abierto)
- NC (Normalmente Cerrado)

### Bobinas
- COIL (Bobina normal)
- COIL_NC (Bobina negada)

### Funciones Especiales
- ADC: Leer entrada analógica (A0, A1)
- PWM: Salida PWM en Q5
- SET_VAR: Guardar valor en variable (V0-V9)
- CMP_GT: Comparador Mayor que (>)
- CMP_LT: Comparador Menor que (<)
- CMP_EQ: Comparador Igual a (==)
- TON: Temporizador ON-delay
- TOFF: Temporizador OFF-delay

### Funcioneles Booleanas
- AND_A/AND_B: Unión AND entre ramas
- OR_A/OR_B: Unión OR entre ramas

## Ejemplo de Uso - PWM con ADC

**Rung 1**: Leer A0 y guardar en V0
- Contacto: ADC (A0)
- Salida: SET_VAR (V0)

**Rung 2**: Si V0 > 128, activar PWM con valor V0
- Contacto: CMP_GT (V0 > 128)
- Salida: PWM (Q5, valor: V0)

El código generado será:
```cpp
// [1] Rung 1
bool _r0 = ((A0 > 0));
if (_r0) V0 = A0;  // ← AUTO-ASIGNA A0 a V0

// [2] Rung 2
bool _r1 = ((V0 > 128));
if (_r1) analogWrite(3, V0);  // ← USA analogWrite CORRECTAMENTE
else Q5 = 0;
```

<img width="813" height="571" alt="SIM_uPLC_v3" src="https://github.com/user-attachments/assets/32f0911d-ae4e-486d-a6f3-76e01a7e884b" />

## Soporte Técnico

ETI Patagonia - prof.martintorres@educ.ar

