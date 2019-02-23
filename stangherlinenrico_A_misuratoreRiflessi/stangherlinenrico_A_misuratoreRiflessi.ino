#include "pitches.h"

int pinButton = 2;
int delayRestart = 5000;

// VARIABILI RGB
int pinBlue = 3;
int pinGreen = 4;
int pinRed = 5;
int delayBlue = random(1500);
int attesaBlue = 0;
// END

// VARIABILI CICALINO
int pinCicalino = 6;
int melodia = NOTE_B5;
int delayCic = random(1500);
int attesaCic = 0;
// END

void riflessiLed()
{
  delay(delayBlue);
  digitalWrite(pinBlue, HIGH);
  while(digitalRead(pinButton) == LOW)
  {
    attesaBlue++;
    delay(1);
  }
  digitalWrite(pinBlue, LOW);
}

void riflessiCic()
{
  delay(delayCic);
  while(digitalRead(pinButton) == LOW)
  {
    attesaCic++;
    tone(pinCicalino, melodia, 1);
  }
  while(digitalRead(pinButton) == HIGH) {}
}

void setup() {
  Serial.begin(9600);
  pinMode(pinButton, INPUT);
  pinMode(pinBlue, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinRed, OUTPUT);
}

void loop() {
  while(digitalRead(pinButton) == LOW) {}
  riflessiLed();
  riflessiCic();
  Serial.println("Stampa dei risultati. Premere nuovamente per uscire");
  while(digitalRead(pinButton) == LOW) {}
}
