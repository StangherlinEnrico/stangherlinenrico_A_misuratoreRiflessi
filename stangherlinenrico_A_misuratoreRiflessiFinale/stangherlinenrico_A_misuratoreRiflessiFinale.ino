#include "pitches.h" // Libreria per il suono del cicalino
#include <LiquidCrystal.h> // Libreria per utilizzare il Display LCD

String opzioni[4] { "  Run Program", "   randomTime", "Promotion times", "                " }; // ARRAY UTILIZZATO PER STAMPARE IL MENU
int tmpRandom[4] { 3000, 4000, 5000, 6000 }; // ARRAY USATO PER STAMPARE I TEMPI RANDOM
int esecuzione = 0; // INT USATO PER SELEZIONARE L'AZIONE DAL MENU

int randomTime = random(3000, 6000); // Genera numero random base

// VARIABILI JOYSTICK
int varX = 0; // Controllo della x
int varY = 1; // Controllo della y
const int okClick = 12; // pin per il click del joystick
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

int sceltaFunzione() // Funzione che verifica quale programma si vuole far partire
{
  int Pos = 0; // Int usato per definire la posizione dell'array del menù
  bool Ciclo = true; // Bool per la scelta dal menù
  while(Ciclo) // Ciclo di scelta
  {
    while(digitalRead(okClick) == HIGH and analogRead(varX) >= 256 and analogRead(varX) <= 768){} // Bottone non premuto e joystick fermo
    if (analogRead(varX) < 256 and digitalRead(okClick) == HIGH) // Se il bottone non è premuto e il joystick va a sinistra
    {
      if (Pos == 0)
        Pos = 2; // Modifica la pos dell'array
      else
        Pos--; // Modifica la pos dell'array
      lcd.setCursor(0, 1); // Setta il cursore per la stampa
      lcd.print(opzioni[3]); // Stampa il vuoto
      lcd.setCursor(0, 1); // Setta il cursore
      lcd.print(opzioni[Pos]); // Stampa opzioni in posizione pos
    }
    else if (analogRead(varX) > 768 and digitalRead(okClick) == HIGH) // Se il bottone non è premuto e il joystick va a destra
    {
      if (Pos == 2)
        Pos = 0; // Modifica la pos dell'array
      else
        Pos++; // Modifica la pos dell'array
      lcd.setCursor(0, 1); // Setta il cursore per la stampa
      lcd.print(opzioni[3]); // Stampa il vuoto
      lcd.setCursor(0, 1); // Setta il cursore per la stampa
      lcd.print(opzioni[Pos]); // Stampa opzioni in posizione pos
    }
    else if (digitalRead(okClick) == LOW and analogRead(varX) > 256 and analogRead(varX) < 768) // Se il joystick è al centro e il pulsante premuto
      Ciclo = false; // Cambia il bool Ciclo per buttarmi fuori dal ciclo
    while(digitalRead(okClick) == LOW or analogRead(varX) <= 256 or analogRead(varX) >= 768){} // Attende mentre il joystick è premuto o spostato dal centro
  }
  return Pos; // Ritorna posizione
}

void startProgram() // Funzione per lo start del programma
{
  lcd.clear(); // Svuota il display
  lcd.setCursor(0, 0); // Setta il cursore
  lcd.print("TL:"); // Stampa
  lcd.setCursor(0, 1); // Setta il cursore
  lcd.print("TC:"); // Stampa
  delay(randomTime); // Aspetta un tempo random
  digitalWrite(pinBlue, HIGH); // Accende il led
  while(digitalRead(okClick) == HIGH) // Finché il pulsante non è premuto
  {
    attesaLed++; // Incrementa attesaLed
    delay(1); // Aspetta 1 millisec
    lcd.setCursor(4, 0); // Setta il cursore
    lcd.print(attesaLed); // Stampa
  }
  while(digitalRead(okClick) == LOW); // Aspetta mentre il pulsate è premuto
  digitalWrite(pinBlue, LOW); // Spegne il led
  delay(randomTime); // Aspetta un tempo random
  while(digitalRead(okClick) == HIGH) // Finché il pulsante non è premuto
  {
    attesaCic++; // Incrementa attesaCic
    tone(pinCicalino, NOTE_C6, 1); // Fa passare un millisecondo emettendo un suono
    lcd.setCursor(4, 1); // Setta il cursore
    lcd.print(attesaCic); // Stampa
  }
  while(digitalRead(okClick) == LOW); // Aspetta mentre il pulsate è premuto
  lcd.clear(); // Svuota il display
  lcd.setCursor(0, 0); // Setta il cursore
  lcd.print("L: "); lcd.print(attesaLed); lcd.print("|C: "); lcd.print(attesaCic); // Stampa
  lcd.setCursor(0, 1); // Setta il cursore
  if (attesaLed < promozioneLed and attesaCic < promozioneCic) // Se è promosso
  {
    digitalWrite(pinGreen, HIGH); // Accendi il led verde
    lcd.print("Congratulazioni!"); // Stampa
    delay(2500); // Aspetta due secondi e mezzo
    digitalWrite(pinGreen, LOW); // Spegni il led verde
  }
  else // Altrimenti
  {
    digitalWrite(pinRed, HIGH); // Accendi il led rosso
    lcd.print("   FALLIMENTO"); // Stampa
    delay(2500); // Aspetta due secondi e mezzo
    digitalWrite(pinRed, LOW); // Spegni il led rosso
  }
  attesaLed = attesaCic = 0; // Azzera i tempi di attesa
}

void modificaTmpRandom() // Funzione per la modifica dei tempi random
{
  lcd.clear(); // Svuota il display
  lcd.setCursor(0, 0); // Setta il cursore
  lcd.print("< TEMPO MINIMO >"); // Stampa
  lcd.setCursor(0, 1); // Setta il cursore
  lcd.print("      "); lcd.print(tmpRandom[0]); // Stampa
  int nMin = 0; int nMax = 0; int Pos = 0; int Pos2 = 0; // Variabili per l'appoggio
  bool valenzaNumeri = true; // Bool per il ciclo
  while(valenzaNumeri) // Ciclo per la scelta del minore -- STESSO METODO USATO PER LA SCELTA DELL'AZIONE
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
  valenzaNumeri = true; // Cambia la bool in true
  if (Pos == 2) // Se la posizione è uguale a 2
    nMax = tmpRandom[3]; // il massimo tempo random è tmpRandom[3]
  else Altrimenti -- STESSO METODO USATO PER LA SCELTA DEL NUMERO MINORE DEL RANDOM
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
  randomTime = random(nMin, nMax); // Genera il numero random
}

bool verificaCodice() // Funzione per la verifica del codice segreto per la modifica dei criteri di promozione
{
  int num = 0; String codice = ""; // Veriabili
  bool ciclo = true; // Bool
  lcd.clear(); // Svuota display
  lcd.setCursor(0, 0); // Setta il cursore
  lcd.print("SECRET CODE-1234"); // Stampa
  lcd.setCursor(0, 1); // Setta il cursore
  lcd.print("      "); lcd.print("0000"); // Stampa

  for (int i = 6; i < 10; i++) // Ciclo for per la selezione della colonna del display
  {
    num = 0; // Azzera numero
    while(ciclo) // While per la selezione del numero specifico -- METODO SIMILE A QUELLO USATO PER IL RANDOM E LA SCELTA DELL'AZIONE
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
    ciclo = true; // Rimette il ciclo a true
  }
  if (codice == "1234") // Se il codice è 1234
    return true; // Ritorna vero
  else // Atrimenti
  {
    lcd.clear(); // Svuota il display
    lcd.setCursor(0, 0); // Setta il cursore
    lcd.print(" CODICE ERRATO!"); // Stampa
    delay(2500); // Aspetta due secondi e mezzo
    return false; // Ritorna falso
  }
}

void modificaCriteriPromozione() // Funzione per la modifica dei criteri di promozione -- METODO SIMILE ALLA VERICA DEL CODICE SEGRETO
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
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(pinRed, HIGH);
    digitalWrite(pinBlue, HIGH);
    delay(300);
    digitalWrite(pinRed, LOW);
    digitalWrite(pinBlue, LOW);
    delay(300);
  }
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
  lcd.setCursor(0, 0); // Setta il cursore
  lcd.print("<    SELECT    >"); // Stampa
  lcd.setCursor(0, 1); // Setta il cursore
  lcd.print(opzioni[0]); // Stampa
  esecuzione = sceltaFunzione(); // Richiama la funzione sceltaFunzione e assegna il return a esecuzione
}
void loop()
{
  if (esecuzione == 0) // Se esecuzione è uguale a 0
    startProgram(); // Avvia il programma
  else if (esecuzione == 1) // Se esecuzione è uguale a 1
    modificaTmpRandom(); // Modifica i tempi random per l'accensione
  else // Altrimenti
  {
    bool codice = verificaCodice(); // Verifica la veriticità del codice e assegna il return a codice
    if (codice) // Se codice è uguale a vero
      modificaCriteriPromozione(); // Fai modificare i criteri di promozione richiamando la funzione modificaCriteriPromozione
  }
  setup(); // Fai ricominciare il programma
}
