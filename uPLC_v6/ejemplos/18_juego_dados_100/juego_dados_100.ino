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
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

// === Salidas digitales ===
bool Q1=false,Q2=false,Q3=false,Q4=false,Q5=false;
uint8_t Q6=0;
// === Variables ===
int V0=0, V1=0, V2=0, V3=0, V9=0;
// === Juego ===
int _score=0; int _lives=3;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  // Entradas digitales
  pinMode(2,INPUT); pinMode(4,INPUT); pinMode(5,INPUT);
  pinMode(6,INPUT); pinMode(7,INPUT); pinMode(8,INPUT); pinMode(9,INPUT);
  // Salidas digitales
  pinMode(13,OUTPUT); pinMode(14,OUTPUT); pinMode(15,OUTPUT);
  pinMode(16,OUTPUT); pinMode(17,OUTPUT); pinMode(3,OUTPUT);
  // — Al iniciar —
    lcd.clear();
    _score = 0;
    _lives = 3;
    V0 = 0;
    V1 = 0;
    V2 = 0;
    V3 = 0;
    V9 = 0;
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
    // Pantalla inicial
    lcd.setCursor(0,0); lcd.print("- Juguemos al 100! -");
    lcd.setCursor(0,1); lcd.print("Tira los dados!");
    lcd.setCursor(0,2); lcd.print("PUNTOS:");
    lcd.setCursor(8,2); lcd.print(_score);
    lcd.setCursor(13,2); lcd.print(" VIDAS:");
    lcd.setCursor(20,2); lcd.print(_lives);
    
    // Esperar boton I1 para tirar
    while (!digitalRead(2)) { delay(10); }
    while (digitalRead(2)) { delay(10); }
    
    // Tirar 3 dados
    V1 = random(1, 7);
    V2 = random(1, 7);
    V3 = random(1, 7);
    
    // Mostrar dados
    lcd.clear();
    lcd.setCursor(0,0); lcd.print("D1:");
    lcd.setCursor(3,0); lcd.print(V1);
    lcd.setCursor(7,0); lcd.print("D2:");
    lcd.setCursor(10,0); lcd.print(V2);
    lcd.setCursor(14,0); lcd.print("D3:");
    lcd.setCursor(17,0); lcd.print(V3);
    
    delay(1500);
    
    // Dado 1: si NO es 6, sumar puntos
    if ((V1 != 6)) {
        _score = (_score + V1);
    } else {
        _lives = (_lives - 1);
    }
    
    // Dado 2: si NO es 6, sumar puntos
    if ((V2 != 6)) {
        _score = (_score + V2);
    } else {
        _lives = (_lives - 1);
    }
    
    // Dado 3: si NO es 6, sumar puntos
    if ((V3 != 6)) {
        _score = (_score + V3);
    } else {
        _lives = (_lives - 1);
    }
    
    // Verificar si perdeu todas las vidas
    if ((_lives <= 0)) {
        lcd.clear();
        lcd.setCursor(2,1); lcd.print("** PERDISTE! **");
        lcd.setCursor(0,2); lcd.print("Puntos:");
        lcd.setCursor(8,2); lcd.print(_score);
        while(1);
    }
    
    // Verificar si sumo mas de 130 (pierde)
    if ((_score > 130)) {
        lcd.clear();
        lcd.setCursor(2,1); lcd.print("** PERDISTE! **");
        lcd.setCursor(0,2); lcd.print("Te pasaste de 130!");
        lcd.setCursor(0,3); lcd.print("Puntos:");
        lcd.setCursor(8,3); lcd.print(_score);
        while(1);
    }
    
    // Verificar si gano (100 a 130)
    if ((((_score >= 100)) && ((_score <= 130)))) {
        lcd.clear();
        lcd.setCursor(2,1); lcd.print("** GANASTE! **");
        lcd.setCursor(0,2); lcd.print("Puntos:");
        lcd.setCursor(8,2); lcd.print(_score);
        while(1);
    }
    
    delay(1000);
  delay(10);
}
