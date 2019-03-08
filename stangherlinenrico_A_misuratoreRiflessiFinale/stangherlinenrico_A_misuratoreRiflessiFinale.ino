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
const int okClick = 12;
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
    while(digitalRead(okClick) == HIGH and analogRead(varX) >= 256 and analogRead(varX) <= 768){}
    if (analogRead(varX) < 256 and digitalRead(okClick) == HIGH)
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
    else if (analogRead(varX) > 768 and digitalRead(okClick) == HIGH)
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
    else if (digitalRead(okClick) == LOW and analogRead(varX) > 256 and analogRead(varX) < 768)
      Ciclo = false;
    while(digitalRead(okClick) == LOW or analogRead(varX) <= 256 or analogRead(varX) >= 768){}
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
  while(digitalRead(okClick) == HIGH)
  {
    attesaLed++;
    delay(1);
    lcd.setCursor(4, 0);
    lcd.print(attesaLed);
  }
  while(digitalRead(okClick) == LOW);
  digitalWrite(pinBlue, LOW);
  delay(randomTime);
  while(digitalRead(okClick) == HIGH)
  {
    attesaCic++;
    tone(pinCicalino, NOTE_C6, 1);
    lcd.setCursor(4, 1);
    lcd.print(attesaCic);
  }
  while(digitalRead(okClick) == LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("L: "); lcd.print(attesaLed); lcd.print("|C: "); lcd.print(attesaCic);
  lcd.setCursor(0, 1);
  if (attesaLed < promozioneLed and attesaCic < promozioneCic)
  {
    digitalWrite(pinGreen, HIGH);
    lcd.print("Congratulazioni!");
    delay(2500);
    digitalWrite(pinGreen, LOW);
  }
  else
  {
    digitalWrite(pinRed, HIGH);
    lcd.print("   FALLIMENTO");
    delay(2500);
    digitalWrite(pinRed, LOW);
  }
  attesaLed = attesaCic = 0;
}

void modificaTmpRandom()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("< TEMPO MINIMO >");
  lcd.setCursor(0, 1);
  lcd.print("      "); lcd.print(tmpRandom[0]);
  int nMin = 0; int nMax = 0; int Pos = 0; int Pos2 = 0;
  bool valenzaNumeri = true;
  while(valenzaNumeri)
  {
    while(digitalRead(okClick) == HIGH and analogRead(varX) >= 256 and analogRead(varX) <= 768){}
    if (analogRead(varX) < 256 and digitalRead(okClick) == HIGH)
    {
      if (Pos == 0)
        Pos = 2;
      else
        Pos--;
      lcd.setCursor(0, 1);
      lcd.print(opzioni[3]);
      lcd.setCursor(0, 1);
      lcd.print("      "); lcd.print(tmpRandom[Pos]);
    }
    else if (analogRead(varX) > 768 and digitalRead(okClick) == HIGH)
    {
      if (Pos == 2)
        Pos = 0;
      else
        Pos++;
      lcd.setCursor(0, 1);
      lcd.print(opzioni[3]);
      lcd.setCursor(0, 1);
      lcd.print("      "); lcd.print(tmpRandom[Pos]);
    }
    else if (digitalRead(okClick) == LOW)
    {
      nMin = tmpRandom[Pos];
      valenzaNumeri = false;
    }
    while(digitalRead(okClick) == LOW or analogRead(varX) <= 256 or analogRead(varX) >= 768){}
  }
  valenzaNumeri = true;
  if (Pos == 2)
    nMax = tmpRandom[3];
  else
  {
    Pos2 = (Pos + 1);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("<NUMERO MASSIMO>");
    lcd.setCursor(0, 1);
    lcd.print("      "); lcd.print(tmpRandom[(Pos + 1)]);
    while(valenzaNumeri)
    {
      while(digitalRead(okClick) == HIGH and analogRead(varX) >= 256 and analogRead(varX) <= 768){}
      if (analogRead(varX) < 256 and digitalRead(okClick) == HIGH)
      {
        if (Pos2 == (Pos + 1))
          Pos2 = 3;
        else
          Pos2--;
        lcd.setCursor(0, 1);
        lcd.print(opzioni[3]);
        lcd.setCursor(0, 1);
        lcd.print("      "); lcd.print(tmpRandom[Pos2]);
      }
      else if (analogRead(varX) > 768 and digitalRead(okClick) == HIGH)
      {
        if (Pos2 == 3)
          Pos2 = (Pos + 1);
        else
          Pos2++;
        lcd.setCursor(0, 1);
        lcd.print(opzioni[3]);
        lcd.setCursor(0, 1);
        lcd.print("      "); lcd.print(tmpRandom[Pos2]);
      }
      else if (digitalRead(okClick) == LOW)
      {
        nMax = tmpRandom[Pos2];
        valenzaNumeri = false;
      }
      while(digitalRead(okClick) == LOW or analogRead(varX) <= 256 or analogRead(varX) >= 768){}
    }
  }
  randomTime = random(nMin, nMax);
}

bool verificaCodice()
{
  int num = 0; String codice = "";
  bool ciclo = true;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SECRET CODE-1234");
  lcd.setCursor(0, 1);
  lcd.print("      "); lcd.print("0000");

  for (int i = 6; i < 10; i++)
  {
    num = 0;
    while(ciclo)
    {
      while(digitalRead(okClick) == HIGH and analogRead(varY) >= 256 and analogRead(varY) <= 768){}
      if (analogRead(varY) < 256 and digitalRead(okClick) == HIGH)
      {
        if (num == 0)
          num = 9;
        else
          num--;
        lcd.setCursor(i, 1);
        lcd.print(num);
      }
      else if (analogRead(varY) > 768 and digitalRead(okClick) == HIGH)
      {
        if (num == 9)
          num = 0;
        else
          num++;
        lcd.setCursor(i, 1);
        lcd.print(num);
      }
      else if (digitalRead(okClick) == LOW)
      {
        if (i == 6)
          codice = num;
        else
          codice += num;
        ciclo = false;
      }
      while(digitalRead(okClick) == LOW or analogRead(varY) <= 256 or analogRead(varY) >= 768){}
    }
    ciclo = true;
  }
  if (codice == "1234")
    return true;
  else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" CODICE ERRATO!");
    delay(2500);
    return false;
  }
}

void modificaCriteriPromozione()
{
  int num = 0; String blu = ""; String cic = "";
  bool ciclo = true;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ledTimePromotion");
  lcd.setCursor(0, 1);
  lcd.print("      "); lcd.print("0800");

  for (int i = 6; i < 10; i++)
  {
    if (i == 7)
      num = 8;
    else
      num = 0;
    while(ciclo)
    {
      while(digitalRead(okClick) == HIGH and analogRead(varY) >= 256 and analogRead(varY) <= 768){}
      if (analogRead(varY) < 256 and digitalRead(okClick) == HIGH)
      {
        if (num == 0)
          num = 9;
        else
          num--;
        lcd.setCursor(i, 1);
        lcd.print(num);
      }
      else if (analogRead(varY) > 768 and digitalRead(okClick) == HIGH)
      {
        if (num == 9)
          num = 0;
        else
          num++;
        lcd.setCursor(i, 1);
        lcd.print(num);
      }
      else if (digitalRead(okClick) == LOW)
      {
        if (i == 6)
          blu = num;
        else
          blu += num;
        ciclo = false;
      }
      while(digitalRead(okClick) == LOW or analogRead(varY) <= 256 or analogRead(varY) >= 768){}
    }
    ciclo = true;
  }
  if (blu == "0000")
  {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("ERROR!");
    lcd.setCursor(0, 1);
    lcd.print(" ledProm <= 800");
    delay(1200);
  }
  for (int i = 0; i < 4; i++)
    if (blu[0] == "0")
      blu.remove(0, 1);

  num = 0;
  ciclo = true;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ledCicaPromotion");
  lcd.setCursor(0, 1);
  lcd.print("      "); lcd.print("1100");

  for (int i = 6; i < 10; i++)
  {
    if (i == 6 or i == 7)
      num = 1;
    else
      num = 0;
    while(ciclo)
    {
      while(digitalRead(okClick) == HIGH and analogRead(varY) >= 256 and analogRead(varY) <= 768){}
      if (analogRead(varY) < 256 and digitalRead(okClick) == HIGH)
      {
        if (num == 0)
          num = 9;
        else
          num--;
        lcd.setCursor(i, 1);
        lcd.print(num);
      }
      else if (analogRead(varY) > 768 and digitalRead(okClick) == HIGH)
      {
        if (num == 9)
          num = 0;
        else
          num++;
        lcd.setCursor(i, 1);
        lcd.print(num);
      }
      else if (digitalRead(okClick) == LOW)
      {
        if (i == 6)
          cic = num;
        else
          cic += num;
        ciclo = false;
      }
      while(digitalRead(okClick) == LOW or analogRead(varY) <= 256 or analogRead(varY) >= 768){}
    }
    ciclo = true;
  }
  if (cic == "0000")
  {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("ERROR!");
    lcd.setCursor(0, 1);
    lcd.print(" cicProm < 1100");
    delay(1200);
  }
  for (int i = 0; i < 4; i++)
    if (cic[0] == "0")
      cic.remove(0, 1);

  promozioneLed = atol(blu.c_str());
  promozioneCic = atol(cic.c_str());
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Data changed");
  delay(2500);
}

void setup()
{
  lcd.begin(16, 2); // Inizializzo il display LCD
  // ASSEGNO GLI INPUT E GLI OUTPUT
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);
  pinMode(okClick, INPUT);
  pinMode(varX, INPUT);
  pinMode(varY, INPUT);
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
  setup();
}
