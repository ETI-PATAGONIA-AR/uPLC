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

// TANQUE + CISTERNA CON LATCH (MEMORIA)
// Versión PRO con memoria de estado
// Evita oscilaciones cuando el nivel está en el medio
// D2: Boya cisterna (1 = hay agua)
// D4: Boya tanque nivel BAJO
// D6: Boya tanque nivel ALTO
// D3: Bomba

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

bool estadoBomba = false;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(2,INPUT);
  pinMode(4,INPUT);
  pinMode(6,INPUT);
  pinMode(3,OUTPUT);
  digitalWrite(3, LOW);
  estadoBomba = false;
  lcd.setCursor(1,0); lcd.print("- TANQUE PRO (LATCH) -");
  lcd.setCursor(0,1); lcd.print("Con memoria de estado");
  lcd.setCursor(0,2); lcd.print("Evita oscilaciones");
  delay(2500);
  lcd.clear();
}

void loop() {
  // SEGURIDAD 1: Sin agua en cisterna → PARAR
  if (digitalRead(2)==LOW) {
    estadoBomba = false;
    digitalWrite(3, LOW);
    lcd.setCursor(0,2); lcd.print("ALERTA: Sin cisterna!");
  }
  
  // SEGURIDAD 2: Tanque lleno → PARAR
  if (digitalRead(6)==HIGH) {
    estadoBomba = false;
    digitalWrite(3, LOW);
    lcd.setCursor(0,2); lcd.print("TANQUE LLENO         ");
  }
  
  // ARRANQUE: Tanque bajo + hay agua → ARRANCAR
  if (digitalRead(4)==HIGH && digitalRead(2)==HIGH) {
    estadoBomba = true;
  }
  
  // APLICAR ESTADO A SALIDA
  if (estadoBomba) {
    digitalWrite(3, HIGH);
    lcd.setCursor(0,2); lcd.print("BOMBA: TRABAJANDO    ");
  } else {
    digitalWrite(3, LOW);
    lcd.setCursor(0,2); lcd.print("BOMBA: DETENIDA      ");
  }
  
  // MOSTRAR ESTADOS EN LCD
  lcd.setCursor(0,0); lcd.print("Cis:");
  lcd.setCursor(4,0); lcd.print(digitalRead(2)==HIGH?"OK ":"ERR");
  lcd.setCursor(9,0); lcd.print("TqB:");
  lcd.setCursor(13,0); lcd.print(digitalRead(4)==HIGH?"SI ":"NO ");
  lcd.setCursor(17,0); lcd.print("TqA:");
  lcd.setCursor(21,0); lcd.print(digitalRead(6)==HIGH?"SI":"NO");
  
  lcd.setCursor(0,1); lcd.print("Estado memoria:");
  lcd.setCursor(14,1); lcd.print(estadoBomba?"ON ":"OFF");
  
  lcd.setCursor(0,3); lcd.print("Presion I1 para reset");
  if (digitalRead(2)==LOW) {
    lcd.setCursor(0,3); lcd.print("Agua cisterna = 0     ");
  }
  
  delay(100);
}
