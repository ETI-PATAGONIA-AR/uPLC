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
int V0=0, V1=0;

void controlar_servo();
void toggle_pwm();

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  _srv_3.attach(3); _srv_5.attach(5); _srv_6.attach(6);
  _srv_9.attach(9); _srv_10.attach(10); _srv_11.attach(11);
  // Entradas digitales
  pinMode(2, INPUT);
  // Pines PWM
  pinMode(5, OUTPUT);
  // — Al iniciar —
  lcd.setCursor(2,0); lcd.print("- SUBPROGRAMAS -");
  lcd.setCursor(0,1); lcd.print("I1: Toggle PWM D5");
  lcd.setCursor(0,2); lcd.print("A0: Servo D3");
  lcd.setCursor(0,3); lcd.print("A1: Velocidad PWM");
}

void loop() {
  // — Para siempre —
  controlar_servo();
  toggle_pwm();
  delay(10);
}

void controlar_servo() {
  _srv_3.write(constrain(map(analogRead(A0), 0, 1023, 0, 180),0,180));
  lcd.setCursor(0,1); lcd.print("SERVO: D3        ");
  lcd.setCursor(0,2); lcd.print("Ang:");
  lcd.setCursor(5,2); lcd.print(map(analogRead(A0), 0, 1023, 0, 180));
}

void toggle_pwm() {
  if (((((!digitalRead(2))) && ((V0 == 0))))) {
    if (((V1 == 0))) {
      V1 = 1;
    } else {
      V1 = 0;
    }
  }
  if (((V1 == 1))) {
    analogWrite(5, (uint8_t)constrain(map(map(analogRead(A1), 0, 1023, 0, 100),0,100,0,255),0,255));
    lcd.setCursor(0,1); lcd.print("PWM D5: ON       ");
    lcd.setCursor(0,3); lcd.print("Valor:");
    lcd.setCursor(7,3); lcd.print(analogRead(A1));
  }
  analogWrite(5, (uint8_t)constrain(map(0,0,100,0,255),0,255));
  lcd.setCursor(0,1); lcd.print("PWM D5: OFF      ");
}
