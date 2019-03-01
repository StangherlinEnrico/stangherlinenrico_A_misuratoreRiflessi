#include "pitches.h" // Libreria per il suono del cicalino
#include <LiquidCrystal.h> // Libreria per utilizzare il Display LCD

String opzioni[4] { "  Run Program", "   randomTime", "Promotion times", "                " };
int tmpRandom[4] { 3000, 4000, 5000, 6000 };
int esecuzione = 0;

int pinButtonPrec = 9;
int pinButtonOk = 10;
int pinButtonNext = 11;
int randomTime = random(3000, 6000);

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
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("< TEMPO MINIMO >");
  lcd.setCursor(0, 1);
  lcd.print("      "); lcd.print(tmpRandom[0]);
  int nMin = 0; int nMax = 0; int Pos = 0; int Pos2 = 0;
  bool valenzaNumeri = true;
  while(valenzaNumeri)
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
      lcd.print("      "); lcd.print(tmpRandom[Pos]);
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
      lcd.print("      "); lcd.print(tmpRandom[Pos]);
    }
    else
    {
      nMin = tmpRandom[Pos];
      valenzaNumeri = false;
    }
    while(digitalRead(pinButtonPrec) == HIGH or digitalRead(pinButtonOk) == HIGH or digitalRead(pinButtonNext) == HIGH){}
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
      while(digitalRead(pinButtonPrec) == LOW and digitalRead(pinButtonOk) == LOW and digitalRead(pinButtonNext) == LOW){}
      if (digitalRead(pinButtonPrec) == HIGH)
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
      else if (digitalRead(pinButtonNext) == HIGH)
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
      else
      {
        nMax = tmpRandom[Pos2];
        valenzaNumeri = false;
      }
      while(digitalRead(pinButtonPrec) == HIGH or digitalRead(pinButtonOk) == HIGH or digitalRead(pinButtonNext) == HIGH){}
    }
  }
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
      while(digitalRead(pinButtonPrec) == LOW and digitalRead(pinButtonOk) == LOW and digitalRead(pinButtonNext) == LOW){}
      if (digitalRead(pinButtonPrec) == HIGH)
      {
        if (num == 0)
          num = 9;
        else
          num--;
        lcd.setCursor(i, 1);
        lcd.print(num);
      }
      else if (digitalRead(pinButtonNext) == HIGH)
      {
        if (num == 9)
          num = 0;
        else
          num++;
        lcd.setCursor(i, 1);
        lcd.print(num);
      }
      else
      {
        if (i == 6)
          codice = num;
        else
          codice += num;
        ciclo = false;
      }
      while(digitalRead(pinButtonPrec) == HIGH or digitalRead(pinButtonNext) == HIGH or digitalRead(pinButtonOk) == HIGH){}
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
    lcd.setCursor(0, 1);
    lcd.print("   Ok to exit");
    while(digitalRead(pinButtonOk) == LOW);
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
      while(digitalRead(pinButtonPrec) == LOW and digitalRead(pinButtonOk) == LOW and digitalRead(pinButtonNext) == LOW){}
      if (digitalRead(pinButtonPrec) == HIGH)
      {
        if (num == 0)
          num = 9;
        else
          num--;
        lcd.setCursor(i, 1);
        lcd.print(num);
      }
      else if (digitalRead(pinButtonNext) == HIGH)
      {
        if (num == 9)
          num = 0;
        else
          num++;
        lcd.setCursor(i, 1);
        lcd.print(num);
      }
      else
      {
        if (i == 6)
          blu = num;
        else
          blu += num;
        ciclo = false;
      }
      while(digitalRead(pinButtonPrec) == HIGH or digitalRead(pinButtonNext) == HIGH or digitalRead(pinButtonOk) == HIGH){}
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
      while(digitalRead(pinButtonPrec) == LOW and digitalRead(pinButtonOk) == LOW and digitalRead(pinButtonNext) == LOW){}
      if (digitalRead(pinButtonPrec) == HIGH)
      {
        if (num == 0)
          num = 9;
        else
          num--;
        lcd.setCursor(i, 1);
        lcd.print(num);
      }
      else if (digitalRead(pinButtonNext) == HIGH)
      {
        if (num == 9)
          num = 0;
        else
          num++;
        lcd.setCursor(i, 1);
        lcd.print(num);
      }
      else
      {
        if (i == 6)
          cic = num;
        else
          cic += num;
        ciclo = false;
      }
      while(digitalRead(pinButtonPrec) == HIGH or digitalRead(pinButtonNext) == HIGH or digitalRead(pinButtonOk) == HIGH){}
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

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Data changed");
  lcd.setCursor(0, 1);
  lcd.print("   Ok to exit");
  while(digitalRead(pinButtonOk) == LOW){}
  
  // FARE IN MODO DA FAR INSERIRE UNA CIFRA ALLA VOLTA
  // DARE AL MASSIMO 4 CIFRE PER I MILLISECONDI
  // SE SI VUOLE FARE MILLISEC MA CON MENO DI 4 CIFRE METTERE 0 DAVANTI A TUTTO
  // PROVARE A METTERE DEI NUMERI BASE --> Es. 0800 -- 1000
}

void setup() {
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
  setup();
}
