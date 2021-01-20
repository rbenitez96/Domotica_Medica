#include <LiquidCrystal.h>
#include <TimerOne.h>
#include <DHT.h>

#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);   // Initialize DHT library

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

#define ritmocardiaco 2
#define PInicio 3
int verificando = 0;
int contador = 0;
int PorMin = 0;
int tiemposec = 0;
int verificar = 0;

float Temp = 0;

void setup() {
  dht.begin();
  lcd.begin(20, 4);
  Serial.begin(9600);          // For Serial Monitor
  pinMode(ritmocardiaco, INPUT);
  pinMode(PInicio, INPUT_PULLUP);
  Timer1.initialize(400000);
  Timer1.attachInterrupt(timerIsr);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pulsometro");
  lcd.setCursor(0, 1);
  lcd.print("Aplasta el boton");
  lcd.setCursor(0, 2);
  lcd.print("para iniciar");
}

void loop() {
  if (digitalRead(PInicio) == LOW) {
    lcd.setCursor(0, 0);
    lcd.print("Espere    ");
    lcd.setCursor(0, 1);
    lcd.print("Midiendo pulsos   ");
    lcd.setCursor(0, 2);
    lcd.print("Seg   ");
    lcd.setCursor(7, 2);
    lcd.print("Pulso ");
    lcd.setCursor(15, 2);
    lcd.print("Total P");
    lcd.setCursor(0, 3);
    lcd.print("             ");
    verificar = 1;
  }
  if (verificar == 1) {
    //Temp += dht.readTemperature();
    if (digitalRead(ritmocardiaco) == HIGH) {
      contador += 1;
      PorMin = contador * 2;
      verificando = 1;
      lcd.setCursor(9, 3); lcd.print(PorMin); lcd.print("   ");
      lcd.setCursor(17, 3);
      lcd.print("    ");
      lcd.setCursor(13, 3); lcd.write(1); delay(100);
      lcd.setCursor(13, 3); lcd.write(2); delay(100);
    }
    if (digitalRead(ritmocardiaco) == LOW && verificando == 1) {
      verificando = 0;
    }
    if (tiemposec >= 15) {
      PorMin = (contador * 4) * 4;
      contador = 0;
      tiemposec = 0;
      Temp = dht.readTemperature();
      //Temp /= 15;
      //Serial.print("Temperatura: ");
      //Serial.println(String(Temp));
      //verificar = 0;
      //Serial.print("Pulso por minuto: ");
      //Serial.println(String(PorMin));
      Serial.println(String(PorMin)+","+String(Temp));
      //Temp = 0;
      lcd.setCursor(17, 3);
      lcd.print(PorMin);
      lcd.print("   ");
      if (PorMin >= 90) {
        lcd.setCursor(0, 0);
        lcd.print("Paciente Estresado");
      } else {
        lcd.setCursor(0, 0);
        lcd.print("Paciente Normal");
      }
    }
  }


  delay(500);
}

void timerIsr() {
  if (verificar == 1) {
    tiemposec += 1;
    lcd.setCursor(1, 3);
    lcd.print(tiemposec);
    lcd.print("  ");
  }
}
