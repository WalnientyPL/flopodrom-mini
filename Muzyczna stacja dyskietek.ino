// --- KONFIGURACJA PINÓW ---
// Każda stacja potrzebuje 2 pinów: DIRECTION (kierunek) i STEP (krok)
const int dirPins[6]  = {2, 4, 6, 8, 10, 12};
const int stepPins[6] = {3, 5, 7, 9, 11, 13};

// --- ZMIENNE SILNIKÓW ---
unsigned long currentPeriod[6] = {0, 0, 0, 0, 0, 0}; // Okres fali w mikrosekundach dla każdej stacji
unsigned long lastStepTime[6]  = {0, 0, 0, 0, 0, 0};
int positions[6]               = {0, 0, 0, 0, 0, 0}; // Aktualna pozycja głowicy (0-75)
int directions[6]              = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};

const int MAX_POSITION = 75; // Bezpieczny limit kroków dla stacji 3.5"

void setup() {
  Serial.begin(9600); // Inicjalizacja komunikacji z PC
  
  // Ustawienie pinów jako wyjścia
  for (int i = 0; i < 6; i++) {
    pinMode(dirPins[i], OUTPUT);
    pinMode(stepPins[i], OUTPUT);
    digitalWrite(dirPins[i], directions[i]);
    digitalWrite(stepPins[i], HIGH);
  }
  
  // TEST SPRZĘTU: Krótki dźwięk startowy na pierwszej stacji (Nutka A4 - 440Hz)
  // Okres dla 440Hz = 1000000 / 440 = 2272 mikrosekundy (półokres = 1136)
  playNote(0, 440);
  delay(300);
  playNote(0, 0); // Wyłączenie dźwięku
}

void loop() {
  unsigned long currentMicros = micros();
  
  // 1. GENEROWANIE DŹWIĘKU (Niezależnie dla wszystkich 6 stacji)
  for (int i = 0; i < 6; i++) {
    if (currentPeriod[i] > 0) {
      if (currentMicros - lastStepTime[i] >= currentPeriod[i]) {
        lastStepTime[i] = currentMicros;
        
        // Wykonaj krok (impuls LOW -> HIGH)
        digitalWrite(stepPins[i], LOW);
        delayMicroseconds(10); 
        digitalWrite(stepPins[i], HIGH);
        
        // Automatyczna zmiana kierunku, by nie uszkodzić stacji
        if (directions[i] == HIGH) {
          positions[i]++;
          if (positions[i] >= MAX_POSITION) {
            directions[i] = LOW;
            digitalWrite(dirPins[i], LOW);
          }
        } else {
          positions[i]--;
          if (positions[i] <= 0) {
            directions[i] = HIGH;
            digitalWrite(dirPins[i], HIGH);
          }
        }
      }
    }
  }
  
  // 2. ODBIERANIE NUT Z PC (Format: [ID_Stacji][Częstotliwość_Mnożnik_10])
  // Prosty protokół: wysłanie 3 bajtów steruje stacją
  if (Serial.available() >= 3) {
    int drive = Serial.read();
    unsigned int freq = (Serial.read() << 8) | Serial.read();
    if (drive >= 0 && drive < 6) {
      playNote(drive, freq);
    }
  }
}

// Funkcja ustawiająca odpowiednią częstotliwość dla danej stacji
void playNote(int drive, unsigned int frequency) {
  if (frequency == 0) {
    currentPeriod[drive] = 0; // Cisza
  } else {
    // Okres w mikrosekundach dla połowy fali
    currentPeriod[drive] = 1000000 / frequency / 2; 
  }
}