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
  if (digitalRead(Taster_2) == HIGH)
  {
    lampe = false;
    digitalWrite(iG_out, LOW);
  }
  else if (digitalRead(Taster_1) == HIGH)
  {
    lampe = true;
  }

  if (lampe)
  {
    digitalWrite(iG_out, HIGH);
  }
  else
  {
    digitalWrite(iG_out, LOW);
  }
}
