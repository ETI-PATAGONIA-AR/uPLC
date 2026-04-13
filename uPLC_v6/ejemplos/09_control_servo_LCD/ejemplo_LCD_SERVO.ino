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
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
Servo servo3;

// === Salidas digitales ===
bool Q1=false,Q2=false,Q3=false,Q4=false,Q5=false;
uint8_t Q6=0;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  servo3.attach(3);
  // Entradas digitales
  pinMode(2,INPUT); pinMode(4,INPUT); pinMode(5,INPUT);
  pinMode(6,INPUT); pinMode(7,INPUT); pinMode(8,INPUT); pinMode(9,INPUT);
  // Salidas digitales
  pinMode(3,OUTPUT); pinMode(13,OUTPUT); pinMode(14,OUTPUT);
  pinMode(15,OUTPUT); pinMode(16,OUTPUT); pinMode(17,OUTPUT);
  // — Al iniciar —
    lcd.setCursor(0,0); lcd.print("- SERVO + LCD + POT -");
    lcd.setCursor(0,1); lcd.print("A0: Controla angulo");
    lcd.setCursor(0,2); lcd.print("I1: Centro (90)");
    lcd.setCursor(0,3); lcd.print("D3: Servo motor");
    delay(2000);
    lcd.clear();
    servo3.write(90);
}

void loop() {
  // === Leer entradas ===
  // (entradas leídas inline en cada bloque)
  // === Escribir salidas ===
  digitalWrite(13, 0); digitalWrite(14, 0);
  digitalWrite(15, 0); digitalWrite(16, 0);
  digitalWrite(17, 0);
  // — Para siempre —
    // Leer potenciometro y maps a 0-180 grados
    int angulo = (analogRead(A0) / 6);
    servo3.write(angulo);
    
    // Mostrar en LCD
    lcd.setCursor(0,0); lcd.print("Angulo: ");
    lcd.setCursor(8,0); lcd.print(angulo);
    lcd.setCursor(12,0); lcd.print("    ");
    
    // Barra de progreso
    lcd.setCursor(0,1); lcd.print("[");
    int pos = (angulo / 9);
    for (int i=0; i<pos; i++) lcd.print("=");
    for (int i=pos; i<20; i++) lcd.print(" ");
    lcd.print("]");
    
    // Si presiona I1, centrar servo
    if ((digitalRead(2))) {
        servo3.write(90);
        lcd.setCursor(0,2); lcd.print("CENTRADO!         ");
    } else {
        lcd.setCursor(0,2); lcd.print("                ");
    }
    
    // Mini joystick visual
    lcd.setCursor(0,3); lcd.print("POT:");
    int nivel = (analogRead(A0) / 51);
    if ((nivel < 7)) {
        lcd.print("*");
    }
    if ((nivel < 6)) {
        lcd.print("*");
    }
    if ((nivel < 5)) {
        lcd.print("*");
    }
    if ((nivel < 4)) {
        lcd.print("*");
    }
    if ((nivel < 3)) {
        lcd.print("*");
    }
    if ((nivel < 2)) {
        lcd.print("*");
    }
    if ((nivel < 1)) {
        lcd.print("*");
    }
    lcd.print("           ");
  delay(10);
}
