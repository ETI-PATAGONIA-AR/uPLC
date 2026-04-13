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
#include <Servo.h>

// Servos (uno por pin PWM usado)
Servo _srv_3, _srv_5, _srv_6, _srv_9, _srv_10, _srv_11;

// === Salidas digitales ===
bool Q1=false,Q2=false,Q3=false,Q4=false,Q5=false;
uint8_t Q6=0;

void setup() {
  _srv_3.attach(3); _srv_5.attach(5); _srv_6.attach(6);
  _srv_9.attach(9); _srv_10.attach(10); _srv_11.attach(11);
  // Entradas digitales
  pinMode(2,INPUT); pinMode(4,INPUT); pinMode(5,INPUT);
  pinMode(6,INPUT); pinMode(7,INPUT); pinMode(8,INPUT); pinMode(9,INPUT);
  // Salidas digitales
  pinMode(13,OUTPUT); pinMode(14,OUTPUT); pinMode(15,OUTPUT);
  pinMode(16,OUTPUT); pinMode(17,OUTPUT); pinMode(3,OUTPUT);
  // — Al iniciar —
    _srv_3.write(constrain(90,0,180));
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
    if (digitalRead(2)) {
        _srv_3.write(constrain(0,0,180));
    } else {
        _srv_3.write(constrain(90,0,180));
    }
    if (digitalRead(4)) {
        _srv_3.write(constrain(180,0,180));
    } else {
        _srv_3.write(constrain(90,0,180));
    }
  delay(10);
}
