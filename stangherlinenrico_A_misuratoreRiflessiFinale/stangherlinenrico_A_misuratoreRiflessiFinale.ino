#include "pitches.h" // Libreria per il suono del cicalino
#include <LiquidCrystal.h> // Libreria per utilizzare il Display LCD

// INSERIRE LED RGB AL POSTO DEL LED NORMALE E FARE IN MODO CHE SI ACCENDA IL LED VERDE SE SI è PROMOSSI E QUELLO ROSSO PER IL VICEVERSA
// INSERIRE IL JOYSTICK E CONTROLLARE IL CLICK E LA DIREZIONE X

String opzioni[4] { "  Run Program", "   randomTime", "Promotion times", "                " };
int tmpRandom[4] { 3000, 4000, 5000, 6000 };
int esecuzione = 0;

int randomTime = random(3000, 6000); // Genera numero random base

// VARIABILI JOYSTICK
int varX = 0;
int varY = 1;
int okClick = 12;
// END

// VARIABILI LED
int pinRed = 8; // Pin Red
int pinGreen = 9; // Pin Green
int pinBlue = 10; // Pin Blue
int attesaLed = 0; // Variabile per salvare il tempo che la persona ha impiegato per premere il pulsante
int promozioneLed = 800; // Tempo base per la promozione Led
// END

// VARIABILI CICALINO
int pinCicalino = 11; // Pin del cicalino
int attesaCic = 0; // Variabile per salvare il tempo che la persona ha impiegato per premere il pulsante
int promozioneCic = 1100; // Tempo base per la promozione Cic
// END

// VARIABILI DISPLAY CLD
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Dico al programma dove sono situati i pin del display
// END

int sceltaFunzione()
{
  int Pos = 0;
  bool Ciclo = true;
  while(Ciclo)
  {
    while(digitalRead(okClick) == LOW and analogRead(varX) > 256 and analogRead(varX) < 768){}
    if (analogRead(varX) < 256)
    {
      if (Pos == 0)
        Pos = 2;
      else
        Pos--;
      lcd.setCursor(0, 1);
      lcd.print(opzioni[3]);
      lcd.setCursor(0, 1);
      lcd.print(opzioni[Pos]);
    }
    else if (analogRead(varX) > 768)
    {
      if (Pos == 2)
        Pos = 0;
      else
        Pos++;
      lcd.setCursor(0, 1);
      lcd.print(opzioni[3]);
      lcd.setCursor(0, 1);
      lcd.print(opzioni[Pos]);
    }
    else if (digitalRead(okClick) == HIGH)
      Ciclo = false;
    while(digitalRead(okClick) == HIGH or analogRead(varX) < 256 or analogRead(varX) > 768){}
  }
  return Pos;
}

void startProgram()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TL:");
  lcd.setCursor(0, 1);
  lcd.print("TC:");
  delay(randomTime);
  digitalWrite(pinBlue, HIGH);
  while(digitalRead(okClick) == LOW)
  {
    attesaLed++;
    delay(1);
    lcd.setCursor(4, 0);
    lcd.print(attesaLed);
  }
  while(digitalRead(okClick) == HIGH);
  digitalWrite(pinBlue, LOW);
  delay(randomTime);
  while(digitalRead(okClick) == LOW)
  {
    attesaCic++;
    tone(pinCicalino, NOTE_C6, 1);
    lcd.setCursor(4, 1);
    lcd.print(attesaCic);
  }
  while(digitalRead(okClick) == HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("L: "); lcd.print(attesaLed); lcd.print("|C: "); lcd.print(attesaCic);
  lcd.setCursor(0, 1);
  if (attesaLed < promozioneLed and attesaCic < promozioneCic)
  {
    lcd.print("Congratulazioni!");
    delay(5000);
  }
  else
  {
    lcd.print("   FALLIMENTO");
    delay(5000);
  }
  attesaLed = attesaCic = 0;
}

void modificaTmpRandom()
{
  
}

bool verificaCodice()
{
  
}

void modificaCriteriPromozione()
{
  
}

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2); // Inizializzo il display LCD
  // ASSEGNO GLI INPUT E GLI OUTPUT
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);
  pinMode(okClick, INPUT);
  digitalWrite(okClick, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("<    SELECT    >");
  lcd.setCursor(0, 1);
  lcd.print(opzioni[0]);
  esecuzione = sceltaFunzione();
}
void loop()
{
  if (esecuzione == 0)
    startProgram();
  else if (esecuzione == 1)
    modificaTmpRandom();
  else
  {
    bool codice = verificaCodice();
    if (codice)
      modificaCriteriPromozione();
  }
  while(digitalRead(okClick) == HIGH){}
  setup();
}
