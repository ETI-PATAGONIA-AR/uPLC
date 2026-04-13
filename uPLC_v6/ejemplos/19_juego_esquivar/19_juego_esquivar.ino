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
// === Variables ===
int V0=0, V1=0, V2=0, V3=0, V4=0, V5=0;

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
    lcd.clear();
    lcd.setCursor(2,1); lcd.print("- JUEGO ESQUIVAR -");
    lcd.setCursor(0,2); lcd.print("I1=IZQ  I2=DER");
    lcd.setCursor(0,3); lcd.print("Presiona I1 para empezar");
    while (digitalRead(2)) { delay(10); }
    while (!digitalRead(2)) { delay(10); }
    V0 = 1;
    V1 = 0;
    V2 = 10;
    V3 = 0;
    V4 = 3;
    V5 = 0;
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
    lcd.setCursor(0,3); lcd.print(" ");
    if ((!digitalRead(2))) {
        V3 = (V3 - 1);
        if ((V3 < 0)) {
            V3 = 0;
        }
    }
    if ((!digitalRead(4))) {
        V3 = (V3 + 1);
        if ((V3 > 19)) {
            V3 = 19;
        }
    }
    V1 = (V1 + 1);
    if ((V1 > 5)) {
        V5 = (V5 + 1);
        V1 = 0;
        V2 = 10;
        if ((V5 == 5)) {
            V5 = 0;
            V0 = (V0 + 1);
            lcd.clear();
            lcd.setCursor(2,1); lcd.print("NIVEL=");
            lcd.setCursor(8,1); lcd.print(V0);
            lcd.setCursor(0,2); lcd.print("VIDAS=");
            lcd.setCursor(8,2); lcd.print(V4);
            delay(2000);
            lcd.clear();
        }
    }
    if (((V3 == V2) && (V1 > 4))) {
        V4 = (V4 - 1);
        V1 = 0;
        V2 = 10;
        if ((V4 == 0)) {
            lcd.clear();
            lcd.setCursor(2,1); lcd.print("** GAME OVER **");
            lcd.setCursor(0,2); lcd.print("Nivel:");
            lcd.setCursor(7,2); lcd.print(V0);
            while(1);
        } else {
            lcd.setCursor(0,0); lcd.print("OUCH! Vidas:");
            lcd.setCursor(14,0); lcd.print(V4);
            delay(1000);
            lcd.setCursor(0,0); lcd.print("                ");
        }
    }
    lcd.setCursor(V3,3); lcd.write(byte(219));
    lcd.setCursor(0,0); lcd.print("N");
    lcd.setCursor(1,0); lcd.print(V0);
    lcd.setCursor(4,0); lcd.print("P");
    lcd.setCursor(5,0); lcd.print(V5);
    lcd.setCursor(8,0); lcd.print("V");
    lcd.setCursor(9,0); lcd.print(V4);
    delay(100);
  delay(10);
}
