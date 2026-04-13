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

// CONTROL TÉRMICO (INVERNADERO / GABINETE)
// A0: Sensor de temperatura (LM35 o similar)
// D3: Ventilador
// D5: Calefactor
// Histéresis para evitar oscilaciones

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

const int TEMP_MIN = 25;  // Por debajo: calefactor ON
const int TEMP_MAX = 30;  // Por arriba: ventilador ON
const int TEMP_ALERTA = 35; // Alerta alta

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(2,INPUT); pinMode(4,INPUT); pinMode(5,INPUT);
  pinMode(6,INPUT); pinMode(7,INPUT); pinMode(8,INPUT); pinMode(9,INPUT);
  pinMode(3,OUTPUT); pinMode(5,OUTPUT);
  pinMode(13,OUTPUT); pinMode(14,OUTPUT); pinMode(15,OUTPUT);
  pinMode(16,OUTPUT); pinMode(17,OUTPUT);
  digitalWrite(3, LOW); digitalWrite(5, LOW);
  lcd.setCursor(2,0); lcd.print("- CONTROL TERMICO -");
  lcd.setCursor(0,1); lcd.print("A0: Sensor temperatura");
  lcd.setCursor(0,2); lcd.print("D3: Ventilador");
  lcd.setCursor(0,3); lcd.print("D5: Calefactor");
  delay(2500);
  lcd.clear();
}

void loop() {
  // Leer temperatura (LM35: 10mV/°C, ADC: 0-1023 = 0-5V)
  int lectura = analogRead(A0);
  int temperatura = (lectura * 5.0 * 100.0) / 1023.0;
  
  // Mostrar temperatura
  lcd.setCursor(0,0); lcd.print("Temp: ");
  lcd.setCursor(7,0); lcd.print(temperatura);
  lcd.setCursor(9,0); lcd.print("°C");
  
  // Mostrar estado
  if (temperatura < TEMP_MIN) {
    // FRÍO - Calefactor ON
    digitalWrite(5, HIGH);
    digitalWrite(3, LOW);
    lcd.setCursor(0,1); lcd.print("*** FRIO ***");
    lcd.setCursor(0,2); lcd.print("Calefactor: ON       ");
    lcd.setCursor(0,3); lcd.print("Ventilador: OFF      ");
  } else {
    if (temperatura > TEMP_MAX) {
      // CALOR - Ventilador ON
      digitalWrite(3, HIGH);
      digitalWrite(5, LOW);
      lcd.setCursor(0,1); lcd.print("*** CALOR ***");
      lcd.setCursor(0,2); lcd.print("Calefactor: OFF      ");
      lcd.setCursor(0,3); lcd.print("Ventilador: ON       ");
      
      // Alerta si temperatura muy alta
      if (temperatura > TEMP_ALERTA) {
        lcd.setCursor(12,1); lcd.print("⚠");
        tone(8, 660, 100);
      } else {
        lcd.setCursor(12,1); lcd.print("  ");
      }
    } else {
      // TEMPERATURA OK
      digitalWrite(3, LOW);
      digitalWrite(5, LOW);
      lcd.setCursor(0,1); lcd.print("*** OK ***");
      lcd.setCursor(0,2); lcd.print("Calefactor: OFF      ");
      lcd.setCursor(0,3); lcd.print("Ventilador: OFF      ");
    }
  }
  
  // Barra de temperatura
  lcd.setCursor(0,1); lcd.print("[");
  int barras = temperatura / 3;
  if (barras > 20) barras = 20;
  for (int i=0; i<barras; i++) lcd.print("|");
  for (int i=barras; i<20; i++) lcd.print(" ");
  lcd.print("]");
  
  delay(200);
}
