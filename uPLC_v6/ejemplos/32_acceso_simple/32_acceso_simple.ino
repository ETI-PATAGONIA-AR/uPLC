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

// SISTEMA DE ACCESO SIMPLE (CERRADURA/TIMBRE)
// D2: Botón de apertura
// D3: Cerradura/relé
// LCD: Muestra estado
// Buzzer: Sonido al abrir

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

bool puertaAbierta = false;
unsigned long tiempoApertura = 0;
const unsigned long TIEMPO_ABIERTO = 5000; // 5 segundos

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
  lcd.setCursor(2,0); lcd.print("- SISTEMA DE ACCESO -");
  lcd.setCursor(0,1); lcd.print("D2: Boton apertura");
  lcd.setCursor(0,2); lcd.print("D3: Cerradura");
  lcd.setCursor(0,3); lcd.print("Tono: Buzzer");
  delay(2000);
  lcd.clear();
  puertaAbierta = false;
}

void loop() {
  // Mostrar estado
  lcd.setCursor(0,0);
  if (puertaAbierta) {
    lcd.print("*** PUERTA ABIERTA ***");
    unsigned long segundosRestantes = (TIEMPO_ABIERTO - (millis() - tiempoApertura)) / 1000;
    lcd.setCursor(0,1); lcd.print("Tiempo: ");
    lcd.setCursor(8,1); lcd.print(segundosRestantes);
    lcd.setCursor(10,1); lcd.print("s");
    
    // Verificar si pasó el tiempo
    if (millis() - tiempoApertura > TIEMPO_ABIERTO) {
      puertaAbierta = false;
      digitalWrite(3, LOW);
      lcd.setCursor(0,2); lcd.print("PUERTA CERRADA      ");
      lcd.setCursor(0,3); lcd.print("                    ");
    }
  } else {
    lcd.print("    - CERRADO -        ");
    lcd.setCursor(0,1); lcd.print("Presione D2 para abrir");
    lcd.setCursor(0,2); lcd.print("                    ");
    lcd.setCursor(0,3); lcd.print("                    ");
  }
  
  // Detectar botón (con anti-rebote simple)
  static bool ultimoEstadoBoton = false;
  if (digitalRead(2)==HIGH && !ultimoEstadoBoton && !puertaAbierta) {
    // Abrir puerta
    puertaAbierta = true;
    tiempoApertura = millis();
    digitalWrite(3, HIGH);
    tone(8, 880, 200);
    delay(100);
    tone(8, 1320, 200);
  }
  ultimoEstadoBoton = (digitalRead(2)==HIGH);
  
  // Indicadores en LCD
  lcd.setCursor(0,2);
  if (digitalRead(3)==HIGH) {
    lcd.print("CERRADURA: ABIERTA  ");
  } else {
    lcd.print("CERRADURA: CERRADA ");
  }
  
  // Simular con potenciómetro (alternativa)
  int pot = analogRead(A0);
  if (pot > 900 && !puertaAbierta) {
    puertaAbierta = true;
    tiempoApertura = millis();
    digitalWrite(3, HIGH);
    tone(8, 660, 150);
  }
  
  delay(50);
}
