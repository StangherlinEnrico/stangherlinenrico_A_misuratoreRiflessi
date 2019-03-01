#include "pitches.h" // Libreria per il suono del cicalino
#include <LiquidCrystal.h> // Libreria per utilizzare il Display LCD

String opzioni[4] { "  Run Program", "   randomTime", "Promotion times", "                " };
int esecuzione = 0;

int pinButtonPrec = 9;
int pinButtonOk = 10;
int pinButtonNext = 11;
int randomTime = 0;

// VARIABILI LED
int pinRed = 8; // Pin rosso
int attesaLed = 0; // Variabile per salvare il tempo che la persona ha impiegato per premere il pulsante
int promozioneLed = 800;
// END

// VARIABILI CICALINO
int pinCicalino = 12; // Pin del cicalino
int attesaCic = 0; // Variabile per salvare il tempo che la persona ha impiegato per premere il pulsante
int promozioneCic = 1100;
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
    while(digitalRead(pinButtonPrec) == LOW and digitalRead(pinButtonOk) == LOW and digitalRead(pinButtonNext) == LOW){}
    if (digitalRead(pinButtonPrec) == HIGH)
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
    else if (digitalRead(pinButtonNext) == HIGH)
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
    else
      Ciclo = false;
    while(digitalRead(pinButtonPrec) == HIGH or digitalRead(pinButtonOk) == HIGH or digitalRead(pinButtonNext) == HIGH){}
  }
  return Pos;
}

void startProgram()
{
  
}

void modificaTmpRandom()
{
  
}

bool verificaCodice()
{
  return true;
}

void modificaCriteriPromozione()
{
  
}

void setup() {
  Serial.begin(9600); // Inizializzo il monitor seriale
  lcd.begin(16, 2); // Inizializzo il display LCD
  // ASSEGNO GLI INPUT E GLI OUTPUT
  pinMode(pinButtonPrec, INPUT);
  pinMode(pinButtonOk, INPUT);
  pinMode(pinButtonNext, INPUT);
  pinMode(pinRed, OUTPUT);
  pinMode(pinCicalino, OUTPUT);
  lcd.setCursor(0, 0);
  lcd.print("<    SELECT    >");
  lcd.setCursor(0, 1);
  lcd.print(opzioni[0]);
  esecuzione = sceltaFunzione();
}

void loop() {
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
  delay(3000);
  setup();
}
