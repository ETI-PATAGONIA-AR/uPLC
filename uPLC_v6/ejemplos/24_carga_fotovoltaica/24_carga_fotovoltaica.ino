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

// CARGA FOTOVOLTAICA - CONTROL DE MOSFET
// A0: Entrada de tensión de batería (divisor de tensión)
// D3: Salida MOSFET/PWM para control de carga
// Rangos ADC:
//   A0 < 500  → Batería baja (~12V) → Carga 100%
//   A0 < 570  → Batería media (~13V) → Carga 50%
//   A0 >= 570 → Batería alta (~14V) → Carga 0%

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
  pinMode(3,OUTPUT);
  pinMode(13,OUTPUT); pinMode(14,OUTPUT); pinMode(15,OUTPUT);
  pinMode(16,OUTPUT); pinMode(17,OUTPUT);
  // — Al iniciar —
    lcd.setCursor(2,1); lcd.print("- CARGA FOTOVOLTAICA -");
    lcd.setCursor(0,2); lcd.print("Control de carga por PWM");
    delay(2500);
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
    // Mostrar valor ADC
    int lectura = analogRead(A0);
    lcd.setCursor(0,0); lcd.print("ADC:");
    lcd.setCursor(5,0); lcd.print(lectura);
    lcd.setCursor(10,0); lcd.print("    ");
    
    // BATERÍA BAJA: A0 < 500 → 100% (siempre ON)
    if ((lectura < 500)) {
        digitalWrite(3, HIGH);
        lcd.setCursor(0,1); lcd.print("PWM 100% - CARGA ON ");
        lcd.setCursor(0,2); lcd.print("Bateria BAJA        ");
        delay(500);
    } else {
        // BATERÍA MEDIA: A0 < 570 → 50% (PWM trucho)
        if ((lectura < 570)) {
            digitalWrite(3, HIGH);
            lcd.setCursor(0,1); lcd.print("PWM 50%             ");
            lcd.setCursor(0,2); lcd.print("Bateria MEDIA        ");
            delay(200);
            digitalWrite(3, LOW);
            delay(200);
        } else {
            // BATERÍA ALTA: A0 >= 570 → 0% (siempre OFF)
            digitalWrite(3, LOW);
            lcd.setCursor(0,1); lcd.print("PWM 0%  - CARGA OFF ");
            lcd.setCursor(0,2); lcd.print("Bateria ALTA         ");
            delay(500);
        }
    }
    
    // Mostrar estado en fila 3
    lcd.setCursor(0,3); lcd.print("V:");
    lcd.setCursor(3,3); lcd.print((lectura * 5) / 102.3);
    lcd.setCursor(8,3); lcd.print("V   ");
  delay(10);
}
