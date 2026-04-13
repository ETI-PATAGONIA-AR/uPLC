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

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);


// === Cara LCD — cols 0-2 / filas 0-1 (pestañea cada 4 s) ===
byte _chr_eye_open[8]    = {0x0E,0x1F,0x15,0x1F,0x0E,0x00,0x00,0x00};
byte _chr_eye_closed[8]  = {0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x00};
byte _chr_mouth_happy[8] = {0x00,0x11,0x0A,0x04,0x00,0x00,0x00,0x00};
byte _chr_mouth_sad[8]   = {0x00,0x04,0x0A,0x11,0x00,0x00,0x00,0x00};
byte _chr_mouth_surp[8]  = {0x0E,0x11,0x11,0x11,0x0E,0x00,0x00,0x00};
uint8_t       _face_state  = 0;   // 0=feliz  1=triste  2=sorprendida
uint8_t       _prev_face   = 255;
unsigned long _blink_timer = 0;
bool          _is_blinking = false;

void drawFace() {
  byte eye   = _is_blinking ? 1 : 0;
  byte mouth = (_face_state==0)?2:(_face_state==1)?3:4;
  lcd.setCursor(0,0); lcd.write(eye); lcd.print(" "); lcd.write(eye);
  lcd.setCursor(0,1); lcd.print(" "); lcd.write(mouth); lcd.print(" ");
}
void actualizarFace() {
  if(_face_state!=_prev_face){ _prev_face=_face_state; drawFace(); }
}

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.createChar(0,_chr_eye_open);  lcd.createChar(1,_chr_eye_closed);
  lcd.createChar(2,_chr_mouth_happy); lcd.createChar(3,_chr_mouth_sad); lcd.createChar(4,_chr_mouth_surp);
  drawFace();
  _blink_timer = millis();
  // Entradas digitales
  pinMode(2, INPUT);
  pinMode(4, INPUT);
  pinMode(6, INPUT);
  pinMode(8, INPUT);
  pinMode(10, INPUT);
  pinMode(12, INPUT);
  // Salidas digitales
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
  // — Al iniciar —
  lcd.clear();
}

void loop() {
  // === Animación cara LCD (pestañeo) ===
  { unsigned long _nf=millis();
    if(!_is_blinking && (_nf-_blink_timer>=4000UL)){ _is_blinking=true;  _blink_timer=_nf;      drawFace(); }
    else if(_is_blinking && (_nf-_blink_timer>=200UL)){ _is_blinking=false; _blink_timer=millis(); drawFace(); }
    if(_face_state!=_prev_face){ _prev_face=_face_state; drawFace(); } }
  // — Para siempre —
  if (digitalRead(2)) {
    digitalWrite(3, HIGH);
    _face_state = 0; actualizarFace();
    delay(900);
  } else {
    digitalWrite(3, LOW);
    _face_state = 1; actualizarFace();
    delay(900);
  }
  if (digitalRead(4)) {
    digitalWrite(5, HIGH);
    _face_state = 0; actualizarFace();
    delay(900);
  } else {
    digitalWrite(5, LOW);
    _face_state = 1; actualizarFace();
    delay(900);
  }
  if (digitalRead(6)) {
    digitalWrite(7, HIGH);
    _face_state = 0; actualizarFace();
    delay(900);
  } else {
    digitalWrite(7, LOW);
    _face_state = 1; actualizarFace();
    delay(900);
  }
  if (digitalRead(8)) {
    digitalWrite(9, HIGH);
    _face_state = 0; actualizarFace();
    delay(900);
  } else {
    digitalWrite(9, LOW);
    _face_state = 1; actualizarFace();
    delay(900);
  }
  if (digitalRead(10)) {
    digitalWrite(11, HIGH);
    _face_state = 0; actualizarFace();
    delay(900);
  } else {
    digitalWrite(11, LOW);
    _face_state = 1; actualizarFace();
    delay(900);
  }
  if (digitalRead(12)) {
    digitalWrite(13, HIGH);
    _face_state = 2; actualizarFace();
    delay(900);
  } else {
    digitalWrite(13, LOW);
    _face_state = 1; actualizarFace();
    delay(900);
  }
  delay(10);
}
