#include <Arduino.h>

// PINS
int Taster_1 = 0;         // Pin 0, Eingangspin: Erkennt Tastendruck auf Taster 1. Wird high, wenn Taster gedrueckt
int Taster_2 = 1;         // Pin 1, Eingangspin: Erkennt Tastendruck auf Taster 2. Wird high, wenn Taster gedruckt.
int iG_out = 3;           // Pin 3, Ausgangspin: Pr¨agt einen Gatestrom in den Triac ein, wenn auf high.
int U_null = 6;           // Pin 6, Eingangspin: Messung des Spannungsnulldurchgangs, wird zum Zeitpunkt des Spannungsnulldurchgangs high.
int U_null_interrupt = 9; // Pin 9, Interruptf¨ahiger Pin: Messung des Spannungsnulldurchgangs, wird zum Zeitpunkt des Spannungsnulldurchgangs high
int LED_1 = 14;           // Pin 14, Ausgangspin: Kann die Led1 an- und ausschalten. Led leuchtet, wenn Pin auf high.
int LED_2 = 15;           // Pin 15, Ausgangspin: Kann die Led2 an- und ausschalten. Led leuchtet, wenn Pin auf high.

bool lampe = false;
int U_null_je_blink = 50; //Anzahl der Nulldurchgänge zwischen Änderung des Lampenzustandes (Blinkdauer)
bool U_null_trans = false; //Flag, die false gesetzt wird, wenn U_null Low ist, also kurz vor dem Spannungsnulldurchgang
int U_null_count = 0;     // Zähler für Spannungsnulldurchgänge 

void setup()
{
  // Pins initialisieren
  pinMode(Taster_1, INPUT);
  pinMode(Taster_2, INPUT);
  pinMode(iG_out, OUTPUT);
  pinMode(U_null, INPUT);
  pinMode(U_null_interrupt, INPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
}

void loop()
{
  if (digitalRead(U_null) == LOW) // U_null wird low, Spannungsnulldurchgang steht bevor
  {
    U_null_trans = true;
  }

  if (digitalRead(U_null) == HIGH && U_null_trans) //Wenn U_null zuvor LOW war und nun HIGH ist, ist der Spannungsnulldurchgang passiert
  {
    U_null_count++;         //Spannungsnulldurchgangzähler hochzählen
    U_null_trans = false;   //Flag zurücksetzen
  }

  if (U_null_count >= U_null_je_blink) //Wenn angegebene Anzahl Spannungsnulldurchg. pro Blink erreicht sind
  {
    lampe = !lampe;                   //Lampenzustand ändern (blinken)
    U_null_count = 0;                 //Nulldurchgangszähler zurücksetzen
  }

  if (lampe)                          //Handling des Triac-Inputs je nach bool lampe
  {
    digitalWrite(iG_out, HIGH);
  }
  else
  {
    digitalWrite(iG_out, LOW);
  }
}
