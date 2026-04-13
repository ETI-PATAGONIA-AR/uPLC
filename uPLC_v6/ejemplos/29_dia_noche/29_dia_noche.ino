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

// TEMPORIZADOR INTELIGENTE DÍA/NOCHE
// A0: LDR (sensor de luz)
// D3: Luz o bomba
// Modo día: funciona normalmente
// Modo noche: reduce actividad

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

const int UMBRAL_LUZ = 500;

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
  lcd.setCursor(1,0); lcd.print("- DÍA / NOCHE -");
  lcd.setCursor(0,1); lcd.print("A0: LDR (luz)");
  lcd.setCursor(0,2); lcd.print("D3: Salida");
  lcd.setCursor(0,3); lcd.print("Umbral: 500");
  delay(2500);
  lcd.clear();
}

void loop() {
  int luz = analogRead(A0);
  bool esDia = (luz > UMBRAL_LUZ);
  
  // Mostrar modo
  lcd.setCursor(0,0);
  if (esDia) {
    lcd.print("*** MODO DÍA ***       ");
  } else {
    lcd.print("*** MODO NOCHE ***     ");
  }
  
  // Mostrar valor LDR
  lcd.setCursor(0,1); lcd.print("Luz:");
  lcd.setCursor(5,1); lcd.print(luz);
  lcd.setCursor(10,1); lcd.print("    ");
  
  // Mostrar barra de luz
  lcd.setCursor(0,2); lcd.print("[");
  int barras = (luz / 51);
  for (int i=0; i<barras; i++) lcd.print("|");
  for (int i=barras; i<20; i++) lcd.print(" ");
  lcd.print("]");
  
  // Lógica según modo
  if (esDia) {
    // MODO DÍA: activo
    if (digitalRead(2)==HIGH) {
      digitalWrite(3, HIGH);
      lcd.setCursor(0,3); lcd.print("Salida: ON  (DÍA)  ");
    } else {
      digitalWrite(3, LOW);
      lcd.setCursor(0,3); lcd.print("Salida: OFF (DÍA)  ");
    }
  } else {
    // MODO NOCHE: reducido
    // Solo enciende si botón presionado Y espera 2 segundos
    static bool modoManual = false;
    static unsigned long tiempoNoche = 0;
    
    if (digitalRead(2)==HIGH && !modoManual) {
      modoManual = true;
      tiempoNoche = millis();
    }
    
    if (modoManual) {
      if (millis() - tiempoNoche > 2000) {
        digitalWrite(3, HIGH);
        lcd.setCursor(0,3); lcd.print("Salida: ON  (NOCHE)");
      } else {
        digitalWrite(3, LOW);
        lcd.setCursor(0,3); lcd.print("NOCHE: Espere...    ");
      }
    } else {
      digitalWrite(3, LOW);
      lcd.setCursor(0,3); lcd.print("Salida: OFF (NOCHE)");
    }
  }
  
  delay(100);
}
