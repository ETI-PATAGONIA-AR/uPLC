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

// SISTEMA INTEGRADO - MÓDULO AGRÍCOLA COMPLETO
// Combina: Riego + Tanque + Día/Noche
// A0: Sensor de humedad
// D2: Botón manual
// D3: Bomba de riego
// D4: Válvula tanque
// D5: Luz auxiliar

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

// Estados
bool modoAutomatico = true;
bool bombaRiego = false;
bool valvulaTanque = false;
bool luzAux = false;

// Configuración
const int HUMEDAD_MIN = 30;
const int LUZ_DIA = 500;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(2,INPUT); pinMode(4,INPUT); pinMode(5,INPUT);
  pinMode(6,INPUT); pinMode(7,INPUT); pinMode(8,INPUT); pinMode(9,INPUT);
  pinMode(3,OUTPUT); pinMode(4,OUTPUT); pinMode(5,OUTPUT);
  pinMode(13,OUTPUT); pinMode(14,OUTPUT); pinMode(15,OUTPUT);
  pinMode(16,OUTPUT); pinMode(17,OUTPUT);
  digitalWrite(3, LOW); digitalWrite(4, LOW); digitalWrite(5, LOW);
  lcd.setCursor(0,0); lcd.print("- SISTEMA INTEGRADO -");
  lcd.setCursor(0,1); lcd.print("Agricola Completo");
  lcd.setCursor(0,2); lcd.print("Riego+Tanque+Luz");
  delay(2500);
  lcd.clear();
}

void loop() {
  // Leer sensores
  int humedad = 100 - (analogRead(A0) * 100 / 1023);
  int luz = analogRead(A1);
  bool esDia = (luz > LUZ_DIA);
  
  // Modo automático o manual
  if (digitalRead(2)==HIGH) {
    modoAutomatico = !modoAutomatico;
    delay(300);
  }
  
  // Mostrar modo
  lcd.setCursor(0,0);
  if (modoAutomatico) {
    lcd.print("AUTO:");
  } else {
    lcd.print("MANUAL:");
  }
  lcd.setCursor(16,0); lcd.print(esDia?"DIA":"NOCHE");
  
  // RIEGO: Si está seco y es día, regar
  if (modoAutomatico) {
    if (humedad < HUMEDAD_MIN && esDia) {
      bombaRiego = true;
      lcd.setCursor(0,1); lcd.print("RIEGO: ON ");
    } else {
      bombaRiego = false;
      lcd.setCursor(0,1); lcd.print("RIEGO: OFF");
    }
  } else {
    // Modo manual
    if (digitalRead(4)==HIGH) {
      bombaRiego = true;
      lcd.setCursor(0,1); lcd.print("RIEGO: ON ");
    } else {
      bombaRiego = false;
      lcd.setCursor(0,1); lcd.print("RIEGO: OFF");
    }
  }
  
  // TANQUE: Si está seco, abrir válvula
  int nivelTanque = analogRead(A2) * 100 / 1023;
  if (nivelTanque < 30) {
    valvulaTanque = true;
    lcd.setCursor(10,1); lcd.print("TANQUE:FILL");
  } else {
    if (nivelTanque > 80) {
      valvulaTanque = false;
      lcd.setCursor(10,1); lcd.print("TANQUE:FULL");
    } else {
      lcd.setCursor(10,1); lcd.print("TANQUE:    ");
    }
  }
  
  // LUZ: Encender de noche
  if (!esDia) {
    luzAux = true;
    lcd.setCursor(0,2); lcd.print("LUZ: ON ");
  } else {
    luzAux = false;
    lcd.setCursor(0,2); lcd.print("LUZ: OFF");
  }
  
  // Mostrar valores
  lcd.setCursor(0,3); lcd.print("Hum:");
  lcd.setCursor(4,3); lcd.print(humedad);
  lcd.setCursor(8,3); lcd.print("%");
  lcd.setCursor(12,3); lcd.print("Niv:");
  lcd.setCursor(16,3); lcd.print(nivelTanque);
  lcd.setCursor(19,3); lcd.print("%");
  
  // Aplicar salidas
  digitalWrite(3, bombaRiego?HIGH:LOW);
  digitalWrite(4, valvulaTanque?HIGH:LOW);
  digitalWrite(5, luzAux?HIGH:LOW);
  
  delay(100);
}
