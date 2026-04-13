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
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
// Servos (uno por pin PWM usado)
Servo _srv_3, _srv_5, _srv_6, _srv_9, _srv_10, _srv_11;

// === Variables ===
int V1=0, V2=0, V3=0;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  _srv_3.attach(3); _srv_5.attach(5); _srv_6.attach(6);
  _srv_9.attach(9); _srv_10.attach(10); _srv_11.attach(11);
  // — Al iniciar —
  lcd.clear();
  _srv_3.write(constrain(0,0,180));
  _srv_5.write(constrain(0,0,180));
  _srv_6.write(constrain(0,0,180));
}

void loop() {
  // — Para siempre —
  V1 = map(analogRead(A0), 0, 1023, 0, 180);
  V2 = map(analogRead(A1), 0, 1023, 0, 180);
  V3 = map(analogRead(A2), 0, 1023, 0, 180);
  _srv_3.write(constrain(V1,0,180));
  _srv_5.write(constrain(V2,0,180));
  _srv_6.write(constrain(V3,0,180));
  lcd.setCursor(0,0); lcd.print("ADC - Servo - Angulo");
  lcd.setCursor(0,1); lcd.print(" 0  -  N1");
  lcd.setCursor(0,2); lcd.print(" 1  -  N2");
  lcd.setCursor(0,3); lcd.print(" 2  -  N3");
  lcd.setCursor(16,1); lcd.print(map(analogRead(A0), 0, 1023, 0, 180));
  lcd.setCursor(16,2); lcd.print(map(analogRead(A1), 0, 1023, 0, 180));
  lcd.setCursor(16,3); lcd.print(map(analogRead(A2), 0, 1023, 0, 180));
  delay(900);
  lcd.clear();
  
}