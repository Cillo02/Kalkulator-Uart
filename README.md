# UART-Kalkulator

## Projektbeschreibung

Bei diesem Projekt handelt es sich um einen einfachen UART-Kalkulator. Eine PC-Anwendung nimmt mathematische Ausdruecke vom Benutzer entgegen und sendet diese ueber eine serielle UART-Schnittstelle an einen Mikrocontroller. Der Mikrocontroller verarbeitet die Eingabe, berechnet das Ergebnis und sendet dieses anschliessend zurueck an die PC-Anwendung. Zusaetzlich wird die Kommunikation in einer Protokolldatei gespeichert.

## Projektstruktur

- `pc_app`: enthaelt die C++-PC-Anwendung.
- `microcontroller/calculator_uart`: enthaelt den Arduino-Code fuer den Mikrocontroller.
- `logs`: enthaelt eine beispielhafte Protokolldatei der seriellen Kommunikation.
- `docs`: enthaelt die Testdokumentation.
- `screenshots`: enthaelt Nachweise/Screenshots zur Projektstruktur und Testdurchfuehrung.

## Verwendete Technologien

- C++
- Arduino IDE
- Arduino Uno
- UART/serielle Schnittstelle
- Git
- GitHub

## Kompilierung und Ausfuehrung der PC-Anwendung

Die PC-Anwendung kann auf dem MacBook mit dem C++-Compiler `g++` kompiliert werden.

Zuerst kann der serielle Port gesucht werden:

```bash
ls /dev/cu.*
```

Danach wird die PC-Anwendung erstellt und gestartet:

```bash
cd pc_app
g++ main.cpp -o kalkulator
./kalkulator
```

Beim Start fragt das Programm nach dem seriellen Port, zum Beispiel `/dev/cu.usbmodem1301`.

## Mikrocontroller

Der Mikrocontroller-Code befindet sich in `microcontroller/calculator_uart/calculator_uart.ino`.
Die Datei wird mit der Arduino IDE geoeffnet und auf ein Arduino-Uno-Board uebertragen. In der Arduino IDE muessen das korrekte Board und der korrekte serielle Port ausgewaehlt werden.

## Testeingaben

Folgende Eingaben wurden getestet:

- `34*72` ergibt `2448`
- `156+289` ergibt `445`
- `875-324` ergibt `551`
- `960/15` ergibt `64`
- `25/0` ergibt `Fehler: Division durch 0`
- `12&4` ergibt `Fehler: Ungueltige Eingabe`
- `100+` ergibt `Fehler: Ungueltige Eingabe`
- `abc+5` ergibt `Fehler: Ungueltige Eingabe`

Die gesendeten und empfangenen Nachrichten werden in `logs/communication_log.txt` protokolliert.
