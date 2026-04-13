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

// TANQUE + CISTERNA - CONTROL DE BOMBA
// D2: Boya cisterna (1 = hay agua)
// D4: Boya tanque nivel BAJO
// D6: Boya tanque nivel ALTO
// D3: Bomba

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  // Entradas digitales
  pinMode(2,INPUT);
  pinMode(4,INPUT);
  pinMode(6,INPUT);
  // Salidas digitales
  pinMode(3,OUTPUT);
  pinMode(13,OUTPUT);
  // — Al iniciar —
    digitalWrite(3, LOW);
    lcd.setCursor(2,0); lcd.print("- TANQUE + CISTERNA -");
    lcd.setCursor(0,1); lcd.print("D2=Boya cisterna");
    lcd.setCursor(0,2); lcd.print("D4=Tanque bajo");
    lcd.setCursor(0,3); lcd.print("D6=Tanque alto");
    delay(2000);
    lcd.clear();
}

void loop() {
  // — Para siempre —
    // Mostrar estado de sensores
    lcd.setCursor(0,0); lcd.print("Cis:");
    lcd.setCursor(4,0); lcd.print((digitalRead(2)==HIGH)?"SI":"NO");
    lcd.setCursor(8,0); lcd.print("TqB:");
    lcd.setCursor(13,0); lcd.print((digitalRead(4)==HIGH)?"SI":"NO");
    lcd.setCursor(17,0); lcd.print("TqA:");
    lcd.setCursor(21,0); lcd.print((digitalRead(6)==HIGH)?"SI":"NO");
    
    // Mostrar estado de bomba
    lcd.setCursor(0,1); lcd.print("Bomba:");
    if (digitalRead(3)==HIGH) {
      lcd.setCursor(7,1); lcd.print("ON ");
    } else {
      lcd.setCursor(7,1); lcd.print("OFF");
    }
    
    // SEGURIDAD: Si NO hay agua en cisterna, NO arrancar
    if (digitalRead(2)==LOW) {
        digitalWrite(3, LOW);
        lcd.setCursor(0,2); lcd.print("SIN AGUA CISTERNA!");
        lcd.setCursor(0,3); lcd.print("Bomba detenida       ");
    } else {
        // Si tanque ALTO, apagar bomba
        if (digitalRead(6)==HIGH) {
            digitalWrite(3, LOW);
            lcd.setCursor(0,2); lcd.print("TANQUE LLENO        ");
            lcd.setCursor(0,3); lcd.print("Bomba apagada        ");
        } else {
            // Si tanque BAJO y hay agua en cisterna, encender bomba
            if (digitalRead(4)==HIGH) {
                digitalWrite(3, HIGH);
                lcd.setCursor(0,2); lcd.print("LLENANDO TANQUE     ");
                lcd.setCursor(0,3); lcd.print("Bomba encendida      ");
            } else {
                lcd.setCursor(0,2); lcd.print("ESPERANDO...        ");
                lcd.setCursor(0,3); lcd.print("                      ");
            }
        }
    }
  delay(100);
}
