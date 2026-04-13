// ================================================================
// uPLC v6 Junior — Sketch generado automáticamente
// ETI Patagonia - prof.martintorres@educ.ar
// ================================================================
// HARDWARE: Arduino UNO
// Entradas digitales : D2-D13 (libre asignación)
// Salidas digitales  : D2-D13 (libre asignación)
// PWM                : D3, D5, D6, D9, D10, D11
// ADC                : A0, A1, A2, A3  (A4=SDA A5=SCL reservados I2C)
// LCD I2C            : A4(SDA) A5(SCL) addr 0x27
// Buzzer             : D8 (fijo)
// SoftSerial Radio   : RX=D10  TX=D11
// Motor L298         : IN1=D4  IN2=D7  ENA=D5(PWM)

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);


void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  // Entradas digitales
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  // Salidas digitales
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
  // — Al iniciar —
  lcd.clear();
  lcd.setCursor(0,0); lcd.print("- ENTRADAS/SALIDAS -");
  lcd.setCursor(0,1); lcd.print("Modo: PULLUP");
  lcd.setCursor(0,2); lcd.print("Presion=LOW(SALE)");
  lcd.setCursor(0,3); lcd.print("Suelta=HIGH(ENTRA)");
}

void loop() {
  // — Para siempre —
  lcd.setCursor(0,0); lcd.print("E:");
  if (((digitalRead(2) == 0))) {
    digitalWrite(3, HIGH);
  } else {
    digitalWrite(3, LOW);
  }
  if (((digitalRead(4) == 0))) {
    digitalWrite(5, HIGH);
  } else {
    digitalWrite(5, LOW);
  }
  if (((digitalRead(6) == 0))) {
    digitalWrite(7, HIGH);
  } else {
    digitalWrite(7, LOW);
  }
  if (((digitalRead(8) == 0))) {
    digitalWrite(9, HIGH);
  } else {
    digitalWrite(9, LOW);
  }
  if (((digitalRead(10) == 0))) {
    digitalWrite(11, HIGH);
  } else {
    digitalWrite(11, LOW);
  }
  if (((digitalRead(12) == 0))) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
  delay(10);
}
