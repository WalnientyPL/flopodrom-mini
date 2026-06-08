# 💾 6-Channel Floppy Disk Drive Orchestra (Arduino Uno)

Projekt muzycznego instrumentu elektro-mechanicznego opartego na **6 stacjach dyskietek 3.5"** sterowanych za pomocą mikrokontrolera **Arduino Uno**. Układ pozwala na generowanie 8-bitowych dźwięków (polifonia do 6 głosów) poprzez precyzyjne kontrolowanie częstotliwości pracy wbudowanych silników krokowych przesuwających głowice stacji.

---

## 🛠️ Stanowisko sprzętowe (Hardware)
Projekt widoczny na załączonej dokumentacji fotograficznej składa się z:
* **Jednostka sterująca:** Arduino Uno (R3) podłączone do PC za pomocą kabla USB (interfejs szeregowy).
* **Układ wykonawczy:** 6 zdemontowanych stacji dyskietek floppy 3.5" z odsłoniętym mechanizmem głowicy.
* **Zasilanie:** Zasilacz laboratoryjny DC ustawiony na napięcie **5.0V** o wysokiej wydajności prądowej, zasilający magistralę zasilania wszystkich stacji równolegle.

---

## 🔌 Schemat Podłączenia i Pinout (Arduino Uno)

Wszystkie stacje dyskietek wymagają **wspólnej masy (GND)** połączonej z pinem GND Arduino oraz minusem (-) zasilacza laboratoryjnego. Aby aktywować stacje, należy w każdej z nich zewrzeć **Pin 12 (Drive Select B) z Pinem 11 (GND)** na złączu krawędziowym.

| Nr kanału | Sygnał stacji | Pin Arduino Uno |
| :---: | :--- | :---: |
| **Stacja 1** | Pin 18 (DIR) <br> Pin 20 (STEP) | **Pin 2** <br> **Pin 3** |
| **Stacja 2** | Pin 18 (DIR) <br> Pin 20 (STEP) | **Pin 4** <br> **Pin 5** |
| **Stacja 3** | Pin 18 (DIR) <br> Pin 20 (STEP) | **Pin 6** <br> **Pin 7** |
| **Stacja 4** | Pin 18 (DIR) <br> Pin 20 (STEP) | **Pin 8** <br> **Pin 9** |
| **Stacja 5** | Pin 18 (DIR) <br> Pin 20 (STEP) | **Pin 10** <br> **Pin 11** |
| **Stacja 6** | Pin 18 (DIR) <br> Pin 20 (STEP) | **Pin 12** <br> **Pin 13** |

---

## 💻 Jak to działa?

1. **Ochrona sprzętu (Auto-Reverse):** Głowica stacji dyskietek ma ograniczony zakres ruchu (ok. 80 kroków). Kod wgrany na Arduino śledzi pozycję każdej głowicy. Po osiągnięciu skrajnej wartości automatycznie odwraca stan pinu `DIRECTION`, zapobiegając uderzaniu mechanizmu o ścianki obudowy i tłumiąc niepożądane zgrzyty.
2. **Protokół Serial:** Arduino stale nasłuchuje strumienia danych z komputera przez port COM. Oczekuje paczek 3-bajtowych: `[Numer_Stacji (0-5)] [Starszy_Bajt_Częstotliwości] [Młodszy_Bajt_Częstotliwości]`. Wysłanie częstotliwości `0` wycisza dany kanał.

---

## 🚀 Instrukcja uruchomienia

### 1. Przygotowanie Arduino
* Otwórz plik `src/floppy_orchestra/floppy_orchestra.ino` w Arduino IDE.
* Wybierz płytkę **Arduino Uno** oraz właściwy port COM.
* Wgraj program. Po uruchomieniu stacja nr 1 powinna wydać krótki dźwięk testowy (nutka A4).

### 2. Odtwarzanie utworów (PC Client)
Aby przesłać pliki muzyczne MIDI do urządzenia, możesz użyć:
* Gotowych programów takich jak **MoppyDesk** (wymaga konfiguracji programowej pod odpowiedni port COM).
* Własnego skryptu w języku Python (wykorzystującego biblioteki `mido` do parsowania plików `.mid` oraz `pyserial` do transmisji danych na Arduino).

---
## 📄 Licencja
Projekt udostępniany na licencji MIT. Dorzuć swoje utwory i baw się dobrze!
