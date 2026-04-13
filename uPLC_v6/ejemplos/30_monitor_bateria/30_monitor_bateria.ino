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

// MONITOR DE BATERÍA CON ALERTAS
// A0: Entrada de tensión de batería
// D3: LED de alerta / buzzer
// Estados: BAJO, OK, ALTO

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

const int VBAT_MIN = 300;  // ~10.5V
const int VBAT_OK = 500;   // ~12V
const int VBAT_MAX = 570;  // ~14V

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(2,INPUT); pinMode(4,INPUT); pinMode(5,INPUT);
  pinMode(6,INPUT); pinMode(7,INPUT); pinMode(8,INPUT); pinMode(9,INPUT);
  pinMode(3,OUTPUT);
  pinMode(13,OUTPUT); pinMode(14,OUTPUT); pinMode(15,OUTPUT);
  pinMode(16,OUTPUT); pinMode(17,OUTPUT);
  digitalWrite(3, LOW);
  lcd.setCursor(1,0); lcd.print("- MONITOR BATERÍA -");
  lcd.setCursor(0,1); lcd.print("A0: Tensión batería");
  lcd.setCursor(0,2); lcd.print("D3: Alerta");
  delay(2500);
  lcd.clear();
}

void loop() {
  int vbat = analogRead(A0);
  int voltaje = (vbat * 5) / 10;  // Convertir a deciVolts (x10)
  
  // Mostrar tensión
  lcd.setCursor(0,0); lcd.print("Vbat:");
  lcd.setCursor(6,0); lcd.print(voltaje/10);
  lcd.setCursor(8,0); lcd.print(".");
  lcd.setCursor(9,0); lcd.print(voltaje%10);
  lcd.setCursor(11,0); lcd.print("V      ");
  
  // Evaluar estado
  if (vbat < VBAT_MIN) {
    // BATERÍA BAJA - ALERTA CRÍTICA
    digitalWrite(3, HIGH);
    lcd.setCursor(0,1); lcd.print("⚠ ALERTA BAJA ⚠  ");
    lcd.setCursor(0,2); lcd.print("Cargar batería!   ");
    tone(8, 440, 200);
  } else {
    if (vbat < VBAT_OK) {
      // BATERÍA BAJA - PRECAUCIÓN
      digitalWrite(3, HIGH);
      delay(100);
      digitalWrite(3, LOW);
      delay(100);
      lcd.setCursor(0,1); lcd.print("- PRECAUCIÓN -     ");
      lcd.setCursor(0,2); lcd.print("Batería baja       ");
    } else {
      if (vbat > VBAT_MAX) {
        // BATERÍA ALTA - WARNING
        digitalWrite(3, HIGH);
        lcd.setCursor(0,1); lcd.print("⚠ ALERTA ALTA ⚠  ");
        lcd.setCursor(0,2); lcd.print("Sobretensión!      ");
        tone(8, 880, 100);
      } else {
        // BATERÍA OK
        digitalWrite(3, LOW);
        lcd.setCursor(0,1); lcd.print("✓ BATERÍA OK ✓    ");
        lcd.setCursor(0,2); lcd.print("Voltaje normal     ");
      }
    }
  }
  
  // Barra de estado
  lcd.setCursor(0,3); lcd.print("[");
  int barras = (vbat - VBAT_MIN) / 10;
  if (barras < 0) barras = 0;
  if (barras > 30) barras = 30;
  for (int i=0; i<barras; i++) lcd.print("|");
  for (int i=barras; i<30; i++) lcd.print(" ");
  lcd.print("]");
  
  delay(100);
}
