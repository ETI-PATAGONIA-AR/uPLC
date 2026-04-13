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

// HIDROPONIA - TEMPORIZACIÓN CÍCLICA NFT
// D3: Bomba de recirculación
// Ciclo: 15 min ON / 45 min OFF
// (Tiempos reducidos para demostración: 15 seg ON / 45 seg OFF)

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

// === Salidas digitales ===
bool Q1=false,Q2=false,Q3=false,Q4=false,Q5=false;
uint8_t Q6=0;

// Tiempos en milisegundos
const unsigned long TIEMPO_ON = 15000;   // 15 segundos (cambiar a 15*60*1000 para minutos)
const unsigned long TIEMPO_OFF = 45000;  // 45 segundos (cambiar a 45*60*1000 para minutos)

unsigned long inicioCiclo = 0;
bool estadoBomba = false;
bool dentroCicloON = false;

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
    digitalWrite(3, LOW);
    lcd.setCursor(2,0); lcd.print("- HIDROPONIA NFT -");
    lcd.setCursor(0,1); lcd.print("Temporizacion ciclica");
    lcd.setCursor(0,2); lcd.print("Sistema listo");
    delay(2000);
    lcd.clear();
    inicioCiclo = millis();
    estadoBomba = false;
    dentroCicloON = false;
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
    unsigned long tiempoActual = millis();
    unsigned long tiempoTranscurrido = tiempoActual - inicioCiclo;
    unsigned long tiempoTotalCiclo = TIEMPO_ON + TIEMPO_OFF;
    unsigned long tiempoEnCiclo = tiempoTranscurrido % tiempoTotalCiclo;
    
    // Calcular tiempo restante
    int segundosRestantes;
    
    if (tiempoEnCiclo < TIEMPO_ON) {
      // Fase ON
      if (!dentroCicloON) {
        dentroCicloON = true;
      }
      digitalWrite(3, HIGH);
      estadoBomba = true;
      segundosRestantes = (TIEMPO_ON - tiempoEnCiclo) / 1000;
      lcd.setCursor(0,0); lcd.print("ESTADO: BOMBA ON     ");
      lcd.setCursor(0,1); lcd.print("FASE: RECIRCULACION  ");
    } else {
      // Fase OFF
      dentroCicloON = false;
      digitalWrite(3, LOW);
      estadoBomba = false;
      segundosRestantes = (TIEMPO_OFF - (tiempoEnCiclo - TIEMPO_ON)) / 1000;
      lcd.setCursor(0,0); lcd.print("ESTADO: BOMBA OFF    ");
      lcd.setCursor(0,1); lcd.print("FASE: ESPERA        ");
    }
    
    // Mostrar tiempo restante
    lcd.setCursor(0,2); lcd.print("Sig. cambio en:");
    lcd.setCursor(17,2); lcd.print(segundosRestantes);
    lcd.setCursor(19,2); lcd.print("s");
    
    // Mostrar progreso del ciclo
    lcd.setCursor(0,3); lcd.print("Ciclo:");
    int porcentaje = (tiempoEnCiclo * 100) / tiempoTotalCiclo;
    lcd.setCursor(7,3); lcd.print(porcentaje);
    lcd.setCursor(11,3); lcd.print("%");
    
    // Indicador visual
    if (estadoBomba) {
      lcd.setCursor(19,0); lcd.print("*");
    } else {
      lcd.setCursor(19,0); lcd.print("-");
    }
  delay(100);
}
