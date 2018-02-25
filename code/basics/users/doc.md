# user system
## v0.2 [21.1.18]
managed to fix the system w/o too much troble, simply forgot to reset file
pointer (userData) after counting the lines in the lines in the file. fixed
that by resetting the file pointer.

### added
test scenario, you can now enter an "uid", and the system decides
wheter to grant you access or not

logfiles
## v0.1 [21.1.18]
erste versuche an einem file-basiertem usersystem

### grundidee:
jeder user ist durch eine zeile in einer textdatei repräsentiert.
as system liest diese datei ein und speichert die gesamte liste ein. nach
etwaigen manipulationen wird die externe textdatei neu geschrieben. durch
händische modifikation der textdatei können neue user hinzugefügt / alte
user entfernt werden

### probleme:
unerwartetes verhalten beim einlesen, geplante lösung: neu schreiben
