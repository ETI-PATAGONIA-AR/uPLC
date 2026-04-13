// ================================================================
// uPLC v6 Junior — Sketch generado automáticamente
// ETI Patagonia - prof.martintorres@educ.ar
// ================================================================
// HARDWARE: Arduino NANO
// I1=D2 I2=D4 I3=D5 I4=D6 I5=D7 I6=D8 I7=D9
// Q1=D13 Q2=D14 Q3=D15 Q4=D16 Q5=D17 Q6=D3(PWM)
// A0=A6  A1=A7  | LCD I2C: A4(SDA) A5=SCL addr 0x27
// Buzzer=D8(I7) | SoftSerial: RX=D10 TX=D11

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

// === Salidas digitales ===
bool Q1=false,Q2=false,Q3=false,Q4=false,Q5=false;
uint8_t Q6=0;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  // Entradas digitales
  pinMode(2,INPUT); pinMode(4,INPUT); pinMode(5,INPUT);
  pinMode(6,INPUT); pinMode(7,INPUT); pinMode(8,INPUT); pinMode(9,INPUT);
  // Salidas digitales
  pinMode(13,OUTPUT); pinMode(14,OUTPUT); pinMode(15,OUTPUT);
  pinMode(16,OUTPUT); pinMode(17,OUTPUT); pinMode(3,OUTPUT);
  // — Al iniciar —
    lcd.setCursor(0,0); lcd.print("- CONTROL VELOCIDAD -");
    lcd.setCursor(0,1); lcd.print("A0: Potenciometro");
    lcd.setCursor(0,2); lcd.print("I1: Encender/Apagar");
    lcd.setCursor(0,3); lcd.print("D3(PWM): Motor DC");
    delay(2000);
    lcd.clear();
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
    // Leer potenciometro (A0) y maps a 0-100%
    int velocidad = (analogRead(A0) / 10);
    
    // Mostrar velocidad en LCD
    lcd.setCursor(0,0); lcd.print("Velocidad:");
    lcd.setCursor(11,0); lcd.print(velocidad);
    lcd.setCursor(14,0); lcd.print("%");
    
    // Si presiona I1, encender motor
    if ((digitalRead(2))) {
        analogWrite(3, (velocidad * 255) / 100);
        lcd.setCursor(0,1); lcd.print("MOTOR: ON      ");
    } else {
        analogWrite(3, 0);
        lcd.setCursor(0,1); lcd.print("MOTOR: OFF     ");
    }
  delay(10);
}
