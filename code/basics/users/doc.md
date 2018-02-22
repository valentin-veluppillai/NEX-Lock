# user system
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
