#define pinMotor 13
#define led1 11
void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(pinMotor, OUTPUT);
}

void loop() {

}

void serialEvent( ) {
  if (Serial.available() > 0 ) {
    char Dato = Serial.read();
    if (Dato == 'A') {
      digitalWrite(pinMotor, HIGH);
      analogWrite(led1, 255);
    }
    if (Dato == 'I') {
      digitalWrite(pinMotor, LOW);
      analogWrite(led1, 122);
    }
    if (Dato == 'E') {
      digitalWrite(pinMotor, LOW);
      analogWrite(led1, 0);
    }
    delay(500);
  }
}
