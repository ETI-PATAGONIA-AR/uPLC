// ================================================================
// uPLC v6 Junior — Sketch generado automáticamente
// ETI Patagonia - prof.martintorres@educ.ar
// ================================================================
// HARDWARE: Arduino NANO
// I1=D2 I2=D4 I3=D5 I4=D6 I5=D7 I6=D8 I7=D9
// Q1=D13 Q2=D14 Q3=D15 Q4=D16 Q5=D17 Q6=D3(PWM)
// A0=A6  A1=A7  | LCD I2C: A4(SDA) A5(SCL) addr 0x27
// Buzzer=D8(I7) | SoftSerial: RX=D10 TX=D11

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

// === Salidas digitales ===
bool Q1=false,Q2=false,Q3=false,Q4=false,Q5=false;
uint8_t Q6=0;
// === Variables ===
int V0=0;
// === Timers ===
unsigned long _T0_start=0; bool _T0_done=false,_T0_en=true,_T0_prev=false;
unsigned long _T1_start=0; bool _T1_done=false,_T1_en=true,_T1_prev=false;

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
    V0 = (int)map(analogRead(A6), 0, 1023, 0, 100);
    lcd.setCursor(0,0); lcd.print("Luz:");
    lcd.setCursor(6,0); lcd.print(V0);
    if (((V0 < 40))) {
        // TOFF T0
        if (_T0_en) { _T0_done=true; _T0_prev=true; }
        else if (_T0_prev) { _T0_prev=false; _T0_start=millis(); }
        else { _T0_done=(millis()-_T0_start<(unsigned long)(5000)); }
        if (_T0_done) {
            Q1 = true;
        }
    }
    if (((V0 >= 40))) {
        // TOFF T1
        if (_T1_en) { _T1_done=true; _T1_prev=true; }
        else if (_T1_prev) { _T1_prev=false; _T1_start=millis(); }
        else { _T1_done=(millis()-_T1_start<(unsigned long)(10000)); }
        if (_T1_done) {
            Q1 = true;
        }
    }
    delay(100);
  delay(10);
}
