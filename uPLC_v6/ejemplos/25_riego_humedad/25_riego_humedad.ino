// ================================================================
// uPLC v6 Junior — Sketch generado automáticamente
// ETI Patagonia - prof.martintorres@educ.ar
// ================================================================
// HARDWARE: Arduino UNO
// Entradas digitales : D2-D13 (libre asignación)
// Salidas digitales  : D2-D13 (libre asignación)
// PWM                : D3, D5, D6, D9, D10, D11
// ADC                : A0, A1, A2, A3  (A4=SDA A5=SCL reservados I2C)
// LCD I2C            : A4(SDA) A5=SCL addr 0x27
// Buzzer             : D8 (fijo)
// SoftSerial Radio   : RX=D10  TX=D11
// Motor L298         : IN1=D4  IN2=D7  ENA=D5(PWM)

// CONTROL DE RIEGO POR HUMEDAD
// A0: Sensor de humedad del suelo
// D3: Bomba o válvula de riego
// Umbral: A0 < 300 → regar, A0 >= 350 → cortar (histéresis)
// Histéresis evita oscilaciones cerca del umbral

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

// === Salidas digitales ===
bool Q1=false,Q2=false,Q3=false,Q4=false,Q5=false;
uint8_t Q6=0;

// Estados
bool regando = false;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  // Entradas digitales
  pinMode(2,INPUT); pinMode(4,INPUT); pinMode(5,INPUT);
  pinMode(6,INPUT); pinMode(7,INPUT); pinMode(8,INPUT); pinMode(9,INPUT);
  // Salidas digitales
  pinMode(3,OUTPUT);
  pinMode(13,OUTPUT); pinMode(14,OUTPUT); pinMode(15,OUTPUT);
  pinMode(16,OUTPUT); pinMode(17,OUTPUT);
  // — Al iniciar —
    digitalWrite(3, LOW);
    lcd.setCursor(2,1); lcd.print("- CONTROL DE RIEGO -");
    lcd.setCursor(0,2); lcd.print("Sensor: Humedad suelo");
    lcd.setCursor(0,3); lcd.print("Umbral: 30%");
    delay(2500);
    lcd.clear();
    regando = false;
}

void loop() {
  // === Leer entradas ===
  // (entradas leídas inline en cada bloque)
  // === Escribir salidas ===
  digitalWrite(13, Q1);
  digitalWrite(14, Q2);
  digitalWrite(15, Q3);
  digitalWrite(16, Q4);
  digitalWrite(17, Q5);
  analogWrite(3, Q6);
  // — Para siempre —
    // Leer sensor de humedad
    int humedad = (analogRead(A0) * 100) / 1023;
    int humedad_real = 100 - humedad;
    
    // Mostrar humedad en LCD
    lcd.setCursor(0,0); lcd.print("Humedad:");
    lcd.setCursor(10,0); lcd.print(humedad_real);
    lcd.setCursor(14,0); lcd.print("%   ");
    
    // Mostrar barra de humedad
    lcd.setCursor(0,1); lcd.print("[");
    int barras = (humedad_real / 5);
    for (int i=0; i<barras; i++) lcd.print("|");
    for (int i=barras; i<20; i++) lcd.print(" ");
    lcd.print("]");
    
    // Lógica con histéresis
    // Umbral bajo: 300 (enciende) = 30% de humedad
    // Umbral alto: 350 (apaga) = 35% de humedad
    if ((humedad_real < 30)) {
        // Seco → ENCENDER bomba
        digitalWrite(3, HIGH);
        regando = true;
        lcd.setCursor(0,2); lcd.print("REGANDO!          ");
        lcd.setCursor(0,3); lcd.print("Bomba ON          ");
    } else {
        if ((humedad_real > 35)) {
            // Húmedo → APAGAR bomba
            digitalWrite(3, LOW);
            regando = false;
            lcd.setCursor(0,2); lcd.print("ESPERANDO...      ");
            lcd.setCursor(0,3); lcd.print("Bomba OFF         ");
        } else {
            // Zona de histéresis → mantener estado
            if ((regando == true)) {
                lcd.setCursor(0,2); lcd.print("MANTENIENDO...    ");
                lcd.setCursor(0,3); lcd.print("Bomba ON          ");
            } else {
                lcd.setCursor(0,2); lcd.print("MANTENIENDO...    ");
                lcd.setCursor(0,3); lcd.print("Bomba OFF         ");
            }
        }
    }
  delay(100);
}
