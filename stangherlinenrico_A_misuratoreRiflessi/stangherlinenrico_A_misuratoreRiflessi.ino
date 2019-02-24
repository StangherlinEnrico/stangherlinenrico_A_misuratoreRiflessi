#include "pitches.h" // Libreria per il suono del cicalino
#include <LiquidCrystal.h> // Libreria per utilizzare il Display LCD

int pinButton = 2; // Variabile intera per pin del Pulsante
int randomTime = 0; // Tempo random per la partenza dl led e del cicalino

// VARIABILI RGB
int pinBlue = 3; // Pin blue
int pinGreen = 4; // Pin verde
int pinRed = 5; // Pin rosso
int attesaBlue = 0; // Variabile per salvare il tempo che la persona ha impiegato per premere il pulsante
// END

// VARIABILI CICALINO
int pinCicalino = 6; // Pin del cicalino
int attesaCic = 0; // Variabile per salvare il tempo che la persona ha impiegato per premere il pulsante
// END

// VARIABILI DISPLAY CLD
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); // Dico al programma dove sono situati i pin del display
// END

void allCompiler() // Funzione che contiene tutto il programma in poche righe
{
  while(digitalRead(pinButton) == LOW) {} // Attende fino a quando il pulsante non è premuto
  riflessiLed(); // Esegue la funzione riflessiLed
  riflessiCic(); // Esegue la funzione riflessiCic
  delay(1300); // Aspetta 1300 millisecondi
  if (attesaBlue <= 1000 and attesaCic <= 1200) // Verifica le condizioni per poter superare il test
    risultatiFinali(pinGreen); // Stampa le congratulazioni se l'esame è stato passato
  else // Altrimenti
    risultatiFinali(pinRed); // Stampa il fallimento se l'esame non è stato passato
  delay(50); // Aspetta 50 millisecondi
}

void generaRandom() // Funzione richiamata nel setup per creare la variabile randomTime
{
  lcd.print("MONITOR SERIALE"); // Stampo sul display LCD
  int nMin; int nMax; // Assegnazione di 2 variabili intere locali per salvare i valori inseriti dall'utente
  bool valenzaNumeri = true; // Variabile bool per il controllo dei dati inseriti
  while(valenzaNumeri) // Ciclo che prosegue fino a quando valenzaNumeri == true
  {
   Serial.println("Inserire numero minimo per la generazione del randomTime."); // Stampa nel monitor seriale
  while(Serial.available() == 0); // Attente senza fare niente fino a che non è stato dato un input da monitor seriale
  nMin = Serial.readString().toInt(); // Salva la stringa convertita a intero inserita dall'utente
  Serial.print("Ho ricevuto "); Serial.println(nMin); // Stampa nel monitor seriale
  Serial.println("Inserire numero massimo per la generazione del randomTime"); // Stampa nel monitor seriale
  while(Serial.available() == 0); // Attente senza fare niente fino a che non è stato dato un input da monitor seriale
  nMax = Serial.readString().toInt(); // Salva la stringa convertita a intero inserita dall'utente
  Serial.print("Ho ricevuto "); Serial.println(nMax); // Stampa nel monitor seriale
  if (nMin < nMax and nMin >= 0) // Varifica la condizione per creare un numero random
    valenzaNumeri = false; // Se condizione == vera --> pone valenzaNumeri = false
  else // Altrimenti
    Serial.println("Il numero minimo deve essere maggiore o uguale a 0 e minore del numero massimo."); // Stampa in monitor seriale e ricomincia il ciclo
  }
  randomTime = random(nMin, nMax); // Genera il numero randomTime

  lcd.clear(); // Scuota il display LCD
  Serial.println("Premere il pulsante per avviare il test."); Serial.print("\n"); // Stampa sul monitor seriale
  lcd.setCursor(0, 0); // Posizione il cursore del display alla posizione 0 della riga 0
  lcd.print(0); lcd.print(" millisec"); // Scrive sul display
  lcd.setCursor(0, 1); // Posizione il cursore del display alla posizione 0 della riga 1
  lcd.print(0); lcd.print(" millisec"); // Scrive sul display
}

void riflessiLed() // Funzione usata per salvare i riflessi dall'accensione del led
{
  while(digitalRead(pinButton) == HIGH) {} // Attente fino a quando il pulsante non è premuto prima di eseguire
  delay(randomTime); // Aspetta il tempo randomTime
  digitalWrite(pinBlue, HIGH); // Accende il led
  while(digitalRead(pinButton) == LOW) // Fino a quando il pulsante non è premuto esegue il ciclo
  {
    lcd.setCursor(0, 0); // Si posizione sulla posizione 0 della riga 0 del display
    lcd.print(attesaBlue); lcd.print(" millisec"); // Stampa la variabile attesaBlue e millisec
    attesaBlue++; // Incrementa la variabile attesaBlue di 1
    delay(1); // Aspetta un millisecondo
  }
  digitalWrite(pinBlue, LOW); // Al termine spegne il led blue
}

void riflessiCic() // Funzione usata per salvare i riflessi dall'accensione del cicalino
{
  while(digitalRead(pinButton) == HIGH) {} // Attente fino a quando il pulsante non è premuto prima di eseguire
  delay(randomTime); // Aspetta il tempo randomTime
  while(digitalRead(pinButton) == LOW) // Fino a quando il pulsante non è premuto esegue il ciclo
  {
    lcd.setCursor(0, 1); // Si posizione sulla posizione 0 della riga 1 del display
    lcd.print(attesaCic); lcd.print(" millisec"); // Stampa la variabile attesaCic e millisec
    attesaCic++; // Incrementa la variabile attesaCic di 1
    tone(pinCicalino, NOTE_C6, 1); // Per la durata di 1 millisecondo fa eseguire al cicalino il suono NOTE_C6
  }
  while(digitalRead(pinButton) == HIGH) {} // Attente fino a quando il pulsante non è premuto prima di eseguire
}

void risultatiFinali(int led) // Funzione usata per stampare i risultati finali sia su display che su monitor
{
    digitalWrite(led, HIGH); // Accende il led dato da condizione nella funzione
    lcd.clear(); // Scuota il display
    lcd.setCursor(0, 0); // Posiziona il cursore alla posizione 0 della riga 0
    if (led == 4) // Se il led è quello verde
      lcd.print("CONGRATULAZIONI!"); // Stampa CONGRATULAZIONI!
    else // Altrimenti
      lcd.print("FALLIMENTO!"); //Stampa FALLIMENTO!
    lcd.setCursor(0, 1); // Posiziona il cursore alla posizione 0 della riga 1
    lcd.print("Punteggi Monitor"); // Stampa
    String Frase = "  Visivo: "; Frase += attesaBlue; Frase += " millisecondi"; Frase += "\n  Uditivo: "; Frase += attesaCic; Frase += " millisecondi"; // Crea una frase
    Serial.print("I risultati sono:\n"); Serial.println(Frase); Serial.print("Premere nuovamente il pulsante per riavviare.\n"); Serial.println(""); // Stampa nel monitor seriale 
    while(digitalRead(pinButton) == LOW) {} // Attende fino a quando il pulsante non è premuto
    digitalWrite(led, LOW); // Spegne il led
}

void setup() {
  Serial.begin(9600); // Inizializzo il monitor seriale
  lcd.begin(16, 2); // Inizializzo il display LCD
  // ASSEGNO GLI INPUT E GLI OUTPUT
  pinMode(pinButton, INPUT);
  pinMode(pinBlue, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinRed, OUTPUT);
  pinMode(pinCicalino, OUTPUT);
  
  generaRandom();
}

void loop() {
  allCompiler(); // Richiama la funzione allCompiler
  setup(); // Richiama il setup
}
