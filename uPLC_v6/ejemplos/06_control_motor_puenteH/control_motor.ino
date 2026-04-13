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

// ROBOT 2 MOTORES CON PUENTE H L298 (DOBLE)
// MOTOR IZQUIERDO: IN1=D4, IN2=D7, ENA=D5(PWM)
// MOTOR DERECHO:   IN2=D8, IN3=D9, ENB=D6(PWM)

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

int velocidad = 0;

void motor_adelante() {
  digitalWrite(4, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  analogWrite(5, velocidad);
  analogWrite(6, velocidad);
  lcd.setCursor(0,1); lcd.print("ADELANTE    ");
}

void motor_atras() {
  digitalWrite(4, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  analogWrite(5, velocidad);
  analogWrite(6, velocidad);
  lcd.setCursor(0,1); lcd.print("ATRAS       ");
}

void motor_girar_izq() {
  digitalWrite(4, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  analogWrite(5, velocidad);
  analogWrite(6, velocidad);
  lcd.setCursor(0,1); lcd.print("GIRAR IZQ  ");
}

void motor_girar_der() {
  digitalWrite(4, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  analogWrite(5, velocidad);
  analogWrite(6, velocidad);
  lcd.setCursor(0,1); lcd.print("GIRAR DER  ");
}

void motor_parar() {
  digitalWrite(4, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  analogWrite(5, 0);
  analogWrite(6, 0);
  lcd.setCursor(0,1); lcd.print("PARADO      ");
}

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  // Entradas digitales
  pinMode(2,INPUT); pinMode(4,INPUT); pinMode(5,INPUT);
  pinMode(6,INPUT); pinMode(7,INPUT); pinMode(8,INPUT); pinMode(9,INPUT);
  // Salidas digitales
  pinMode(4,OUTPUT); pinMode(7,OUTPUT); pinMode(8,OUTPUT); pinMode(9,OUTPUT);
  pinMode(5,OUTPUT); pinMode(6,OUTPUT);
  // — Al iniciar —
  velocidad = 150;
  lcd.setCursor(3,0); lcd.print("- ROBOT 2 MOTORES -");
  lcd.setCursor(0,2); lcd.print("I1:ADELANTE I2:ATRAS");
  lcd.setCursor(0,3); lcd.print("I3:IZQ  I4:DER");
  delay(2000);
  lcd.clear();
}

void loop() {
  // === Leer entradas ===
  // (entradas leídas inline en cada bloque)
  // === Escribir salidas ===
  // — Para siempre —
    // Leer potenciometro para velocidad (A0 = 0-100%)
    velocidad = (analogRead(A0) / 10);
    lcd.setCursor(0,0); lcd.print("Vel:");
    lcd.setCursor(4,0); lcd.print(velocidad);
    lcd.setCursor(9,0); lcd.print("   ");
    
    // ADELANTE
    if ((digitalRead(2))) {
        motor_adelante();
    } else {
        // ATRAS
        if ((digitalRead(4))) {
            motor_atras();
        } else {
            // GIRAR IZQUIERDA
            if ((digitalRead(5))) {
                motor_girar_izq();
            } else {
                // GIRAR DERECHA
                if ((digitalRead(6))) {
                    motor_girar_der();
                } else {
                    motor_parar();
                }
            }
        }
    }
  delay(10);
}
