# UART-Kalkulator

## Projektbeschreibung

Bei diesem Projekt handelt es sich um einen einfachen UART-Kalkulator. Eine PC-Anwendung nimmt mathematische Ausdrücke vom Benutzer entgegen und sendet diese über eine serielle UART-Schnittstelle an einen Mikrocontroller. Der Mikrocontroller verarbeitet die Eingabe, berechnet das Ergebnis und sendet dieses anschließend zurück an die PC-Anwendung. Zusätzlich wird die Kommunikation in einer Protokolldatei gespeichert.

## Projektstruktur

- `pc_app`: enthält die C++-PC-Anwendung.
- `microcontroller/calculator_uart`: enthält den Arduino-Code für den Mikrocontroller.
- `logs`: enthält eine beispielhafte Protokolldatei der seriellen Kommunikation.
- `docs`: enthält zusätzliche Dokumentation zum Testprotokoll und Projektaufbau.
- `screenshots`: enthält Nachweise/Screenshots zur Projektstruktur und Testdurchführung.

## Verwendete Technologien

- C++
- Arduino IDE
- Arduino Uno
- UART/serielle Schnittstelle
- Git
- GitHub

## Kompilierung der PC-Anwendung auf dem MacBook

Die PC-Anwendung kann auf dem MacBook mit dem C++-Compiler `g++` kompiliert werden.

Beispiel:

```bash
cd pc_app
g++ main.cpp -o kalkulator
./kalkulator
ls /dev/cu.*

