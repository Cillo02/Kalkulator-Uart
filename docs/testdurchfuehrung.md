# Testdurchführung

Die PC-Anwendung wurde auf einem MacBook mit Visual Studio Code entwickelt und mit dem C++-Compiler g++ kompiliert.

Der Mikrocontroller-Code wurde mit der Arduino IDE auf ein Arduino Uno Board übertragen.

Für den Test wurde der serielle Port /dev/cu.usbmodem1301 verwendet.

## Getestete Eingaben

- 34*72 = 2448
- 156+289 = 445
- 875-324 = 551
- 960/15 = 64
- 25/0 = Fehler: Ungueltige Eingabe

Die Kommunikation zwischen PC-Anwendung und Mikrocontroller wurde erfolgreich getestet. Die gesendeten und empfangenen Daten wurden zusätzlich in der Datei logs/communication_log.txt protokolliert.
