# Aufgabenstellung SEWorms

Ziel des Übungsbeispiels in Softwareengineering ist die Umsetzung eines größeren Softwareprojektes um die theoretischen Konzepte: Vorgehensmodelle, Versionierung und Design Prinzipien (Entwurfsmuster) in der parktischen Umsetzen zu erlernen. Und eigentlich selbst ein größeres Softfareprojekt mit Hilfe der objektorientierten Programmierung gesehen und umgesetzt zu haben. Das diesjährige Projekt ist vom Spiel Worms inspiriert.

# Inhaltsverzeichnis
- [Aufgabenstellung SEWorms](#aufgabenstellung-seworms)
- [Inhaltsverzeichnis](#inhaltsverzeichnis)
- [SEWorms](#seworms)
- [Allgemeine Hinweise](#allgemeine-hinweise)
- [Spielfeld](#spielfeld)
  - [Kartenelemente](#kartenelemente)
      - [Erde ('E')](#erde-e)
      - [Wasser ('W')](#wasser-w)
      - [Luft (' ')](#luft--)
    - [Kiste ('#')](#kiste-)
    - [Wurm ('~'/'*')](#wurm-)
  - [Konfigurations Dateien](#konfigurations-dateien)
    - [Beispiel für eine gültige Initialisierungsdatei](#beispiel-für-eine-gültige-initialisierungsdatei)
    - [Beispiel für eine gültige Mapdatei](#beispiel-für-eine-gültige-mapdatei)
- [Size in WIDTHxHEIGHT](#size-in-widthxheight)
- [Waffen](#waffen)
      - [Pistole](#pistole)
      - [Raketenwerfer](#raketenwerfer)
      - [Teleporter](#teleporter)
      - [Flammenwerfer](#flammenwerfer)
      - [Baseballschläger](#baseballschläger)
      - [Luftangriff](#luftangriff)
- [Benutzereingabe](#benutzereingabe)
  - [Eingabeaufforderung](#eingabeaufforderung)
  - [Befehle](#befehle)
    - [move [left/right] [0..3]](#move-leftright-03)
    - [choose [weapon]](#choose-weapon)
    - [action [direction]](#action-direction)
    - [action [col] [row]](#action-col-row)
    - [action [col]](#action-col)
    - [action](#action)
    - [action idle](#action-idle)
    - [map](#map)
    - [state](#state)
    - [help](#help)
    - [quit](#quit)
- [Regeln und Spielablauf](#regeln-und-spielablauf)
  - [Schwerkraft](#schwerkraft)
  - [Spielbeginn](#spielbeginn)
    - [Wahl der Wurmnamen und Wurmposition](#wahl-der-wurmnamen-und-wurmposition)
  - [Spielablauf](#spielablauf)
    - [Einsammeln der Kisten](#einsammeln-der-kisten)
      - [Wahl der Kistenposition und Inhalte](#wahl-der-kistenposition-und-inhalte)
    - [Feuern der Waffen](#feuern-der-waffen)
    - [Todesursachen und deren Ausgabe](#todesursachen-und-deren-ausgabe)
  - [Spielende](#spielende)
  - [Fehlermeldungen mit Rückgabewerten](#fehlermeldungen-mit-rückgabewerten)
- [Erlaubte Bibliotheken](#erlaubte-bibliotheken)
- [Referenzen](#referenzen)

# SEWorms

In SEWorms (SEworms) kontrolliert jeder Spieler ein Team von mehreren Würmern. Diese sind mehr oder weniger stark bewaffnet. Ziel des Spieles ist es sämtliche Gegner des gegnerischen Teams auszuschalten. Das Spiel läuft hierbei rundenbasiert auf einer als vertikaler Querschnitt angelegten Karte.

# Allgemeine Hinweise

*   Das Koordinatensystem beginnt bei 0x0, welches dem Feld links oben entspricht.
*   Am Spielfeld entspricht die row-Achse die Nummer der Zeile und die col-Achse die Nummer der Spalte. Koordinaten (4,2) kennzeichnen das Feld in Zeile 4 und Spalte 2.
* Eckige Klammern (zuerst öffnend, dann schließend) inklusive eingeschlossenem Text deuten eine Textersetzung an (Beispiel: "[weapon]" wird durch "bazooka" ersetzt).

# Spielfeld

## Kartenelemente

Kartenelemente haben unterschiedliche Eigenschaften:

#### Erde ('E')

Würmer können sich nicht durch Erdfelder bewegen, aber auf Erdfeldern stehen und auf Erdfeldern klettern welche sich maximal auf gleicher Höhe wie sie selbst befinden. Für Erdfelder in SEworms sind keine Überlegungen zur Schwerkraft relevant - sie können auch in der Luft und auf Wasser "liegen". Erdfelder können durch Waffen (außer Baseballschläger) zerstört werden und sind durch ein 'E' symbolisiert.

#### Wasser ('W')

Würmer können sich nicht über Wasserfelder bewegen. Stehen Würmer auf einem Wasserfeld so "versinken" sie und werden aus dem Spiel entfernt. Ebenso Kisten. Wasserfelder können nicht zerstört werden und sind durch ein 'W' symbolisiert.

#### Luft (' ')

Würmer können sich durch Luftfelder bewegen. Stehen Würmer auf einem Luftfeld so "fallen" sie auf das darunter liegende Feld. Ebenso Kisten. Luft wird in der Karte durch ein Leerzeichen ' ' im map-file (in welchem das Spielfeld definiert ist)  als 'A' dargestellt. 

### Kiste ('#')

Kisten beinhalten eine zufällige Waffe (außer Pistole). Bei deren aufsammeln bekommt der aktuelle Wurm +1 Munition für eine zufällige Waffe. Die Kiste verschwindet beim Aufsammeln oder wenn sie ins Wasser fällt. Kisten können auf anderen Kisten liegen. Kisten können nicht fliegen, sollte sich unter der Kiste keine Erde mehr befinden fällt sie. Wenn die Kiste auf einen Wurm fällt, bekommt der Wurm die Kiste als hätte er sie aufgesammelt. Kisten können durch Waffen (außer Baseballschläger) zerstört werden. Die Kiste (Chest) wird mit einer Raute "#" symbolisiert.

### Wurm ('~'/'*')

Bei einem "Wurmfeld" handelt es sich um ein Luftfeld, auf dem sich ein Wurm befindet. Ein Wurm ist die grundlegende Spielfigur. Jeder Wurm kann sich in zwei Richtungen (links und rechts) bewegen und danach Aktionen ausführen. Würmer können sich nicht durch Würmer bewegen, aber auf Würmer stehen und auf Würmer oder Erdfelder klettern, welche sich maximal auf gleicher Höhe wie sie selbst befinden. Würmer haben verschiedene Waffen mit entsprechender Munition. Jeder Wurm beginnt mit 100 HP (Lebenspunkte). Wenn sie attackiert werden oder fallen, verlieren sie HP. Sobald ihre Lebenspunkte auf 0 fallen, oder sie aus anderen Gründen sterben, werden sie aus dem Spiel entfernt. Zur Unterscheidung werden die Würmer von Spieler 1 mit '~' (Tilde) symbolisiert und von Spieler 2 mit '*' 


## Konfigurations Dateien
Das Spiel wird zentral über eine Initialisierungsdatei (*config.ini*) konfiguriert, welche beim Programmstart als Kommandozeilenargument an das Programm übergeben wird. Aus der Initialisierungsdatei werden neben den allgemeinen Konfigurationen, die Pfade für die Mapdatei (*map.txt*) und der Datei mit den Namen der Würmer (*worm_names.txt*) geladen. Alle Konfigurationsdateien, der Code der Klassen Random (Erzeugen der zufällen Wurmnamen und Positionen der Würmer und Kisten) und INIReader (Lesen der Initialisierungsdatei) sowie die **CMakeLists.txt** zum compilieren des Projektes über Cmake sind im aktuellen Repository zu finden.

### Beispiel für eine gültige Initialisierungsdatei
<pre>
[general]
PROMT=>
MAP=../assets/map.txt
WORM_NAMES=../assets/worm_names.txt

[player]
NUM_PLAYER=2
NUM_WORMS=3
PLAYER0=~
PLAYER1=*
</pre>

### Beispiel für eine gültige Mapdatei

<pre>#SWORMS
#this is a comment

# Size in WIDTHxHEIGHT
SIZE: 40 11

MAP:
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAEAAAAAEEAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAEEEAAAEEEEAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAEEEEEEEEEEEEAAAAAAAAAAAAAAAAAAA
AAAAEAAAEEEEEEEEEEEEEEAAAAAAAAAAAAAAAAAA
AAAEEAAEEEEEEEEEEEEEEEEAAAAAAAAAAAAAAAAA
AAEEEAEEEEEEEEEEEEEEEEEEAAAAAAAAAAAAAAAA
AEEEEEEEEEEEEEEEEEEEEEEEEAAAAAAAAAAAAAAA
WEEEEEEEEEEEEEEEEEEEEEEEEEWWWWWWWWWWWWWW
</pre>

Die Datei muss immer mit der Magic Value #SWORMS beginnen, der letzte Eintrag muss die Karte (MAP) sein.

Leere Zeilen sind zu ignorieren. Zeilen, die mit dem Raute-Symbol beginnen, enthalten einen Kommentar und sind ebenfalls zu ignorieren.

Die Felder SIZE und MAP müssen genau einmal vorkommen und in Upper-Case geschrieben sein. Zwischen den einzelnen Elementen der MAP darf kein Leerzeichen sein. Diese Elemente repräsentieren den Typ des Feldes und es dürfen nur die Feldtypen "Earth", "Water" und "Air" vorkommen, wobei Air durch 'A' in der Konfigurationsdatei repräsentiert wird. In der obersten Zeile darf nur Luft sein.

Wird eine fehlerhafte Zeile eingelesen, so soll das Einlesen des Files abgebrochen und das Spiel mit der entsprechenden Fehlermeldung beendet werden (siehe Fehlermeldungen).

Zum Laden und erstellen des Spieles mit zugehöriger Map bietet sich das [Builder Pattern](https://en.wikipedia.org/wiki/Builder_pattern) an. Würmer und Kisten können sinnvoll über eine einfache Version des [Factory Pattern](https://en.wikipedia.org/wiki/Factory_method_pattern) erzeugt werden, müssen dies aber nicht.


# Waffen

Waffen haben unterschiedliche Eigenschaften in Bezug auf Anzahl an Munition, Schussrichtung, Schadensausmaß und -radius. Würmer können auch Würmer des eigenen Teams angreifen (friendly fire) und sich selbst verletzen! Erdfelder und Kisten, welche sich im Schadensradius befinden, werden zerstört (Ausnahme: Baseballschläger).

#### Pistole

*   Name: gun
*   Munition: unendlich
*   Schaden: 25
*   Schussrichtung: eine Gerade, je nach gewählter Richtung.
*   Schadensradius: das erste getroffene Ziel. 1 Feld.

#### Raketenwerfer

*   Name: bazooka
*   Munition: 1
*   Schaden: 40
*   Schussrichtung: eine Gerade, je nach gewählter Richtung.
*   Schadensradius: das erste getroffene Ziel. Ein Kreuz ab dem Einschlagspunkt ([4er Nachbarschaft](https://de.wikipedia.org/wiki/Nachbarschaft_(Bildverarbeitung)#Vierer-Nachbarschaft)). Schaden bekommen der Einschlagspunkt und je 1 Feld daüber und daunter sowie links und rechts davon.

#### Teleporter

*   Name: teleporter
*   Munition: 1
*   Der aktuelle Wurm teleportiert sich zu einer gewählten Position (falls möglich). Beachten Sie, dass der Wurm auch hier beim Fallen Schaden erleidet.

#### Flammenwerfer

*   Name: blowtorch
*   Munition: 1
*   Schaden: 35
*   Schussrichtung: eine Gerade, je nach gewählter Richtung
*   Schadensradius: eine Gerade von 5 Felder nach der Position des aktuellen Wurmes. Die Waffe schießt durch 5 Felder durch, auf alle diese Felder wird der Schaden gegebenenfalls angewendet.

#### Baseballschläger

*   Name: melee
*   Munition: 1
*   Schaden: 50
*   Schussrichtung: ein Kreis rund um den aktuellen Wurm
*   Schadensradius: ein Kreis rund um den aktuellen Wurm. 1 Feld in allen Richtungen ([8er Nachbarschaft](https://de.wikipedia.org/wiki/Nachbarschaft_(Bildverarbeitung)#Achter-Nachbarschaft)). Der Baseballschläger attackiert nur Würmer, er kann NICHT Erde oder Kisten zerstören!

#### Luftangriff

*   Name: airstrike
*   Munition: 1
*   Schaden: 20
*   Schussrichtung: eine Gerade nach unten, je nach gewählter Spalte
*   Schadensradius: das erste getroffene Ziel. 1 Feld.

# Benutzereingabe

Für die Umsetzung der Benutzereingaben bietet sich das [Command Pattern](https://en.wikipedia.org/wiki/Command_pattern) an.

## Eingabeaufforderung

Die Eingabeaufforderung muss in einer Endlosschleife den Standardprompt (aus der Initialisierungsdatei)

<pre>> </pre>

ausgeben und das Programm wartet auf die Eingabe eines der definierten Befehle. Zwischen Standardprompt und Eingabe der Befehle sowie Parameter können ein oder mehrere Leerzeichen vorkommen. Die Eingabe der Befehle sowie deren Parameter erfolgen case insensitive. Wird ein ungültiger Befehl eingegeben, wird eine der folgenden Fehlermeldungen ausgegeben und es wird wieder auf den nächsten Befehl gewartet.

*   Wird kein Befehl (nur Enter gedrückt) eigegeben, so soll die Schleife erneut beginnen (erneute Ausgabe des Standardprompts)
*   Wird der quit-Befehl erkannt, so soll sich das Programm ohne weitere Ausgaben mit mit Rückgabewert 0 beenden.
*   Wird ein unbekannter Befehl eingegeben, so soll folgende Fehlermeldung ausgegeben werden:

<pre>[ERROR] unknown command!\n</pre>

*   Ist der Parameter für den aufrufenden Befehl ungültig (z.B. Buchstabe statt Zahl oder ungültige Koordinate), soll folgende Fehlermeldung ausgegeben werden:

<pre>[ERROR] invalid parameter!\n</pre>

*   Würde ein Befehl den Regeln des Spielablaufs widersprechen (z.B. zwei mal move Befehl hintereinander), soll folgende Fehlermeldung ausgegeben werden:

<pre>[ERROR] command currently not allowed!\n</pre>

*   Wird eine Waffe ausgewählt für welche keine Munition mehr vorhanden ist, soll folgende Fehlermeldung ausgegeben werden:

<pre>[ERROR] no ammunition\n</pre>

*   Wird beim Aktivieren des Teleporters ein ungültiges Ziel ausgewählt (z.B. in Erde, Wurm oder Wasser), soll folgende Fehlermeldung ausgegeben werden:

<pre>[ERROR] invalid target!\n</pre>

## Befehle

### move [left/right] [0..3]

Parameter:

*   left/right: entweder "l" oder "r" je nach Richtung in welche der Wurm gehen soll
*   0..3: Anzahl an Schritten, die der Wurm ausführen soll

Bewegt den Wurm um die Anzahl an Schritten nach links oder rechts.

*   Bewegungsregeln:
    *   Der Wurm kann auf ein benachbartes Erdfeld oder Wurm klettern, wenn es sich maximal auf gleicher Höhe wie der Wurm befindet und darüber ein Luftfeld liegt.
    *   Der Wurm kann nur klettern, wenn sich über dem Wurm Luft oder ein anderer Wurm befindet.

Sollten nicht alle Schritte möglich sein, werden alle Schritte bis zum ungültigen Schritt durchgeführt. Sobald der Wurm an einem Schritt ankommt, den er nicht ausführen kann, soll folgender Hinweis ausgegeben werden (nur 1 Mal):

<pre>[WARNING] can't move further\n</pre>

Nach dem move Befehl wird das aktuelle Spielfeld ausgegeben. Würmer können nun auch außerhalb der map gehen bzw. fallen (siehe Todesursachen).

### choose [weapon]

Parameter:

*   weapon: eine der folgenden Waffen: "gun", "bazooka", "teleporter", "blowtorch", "melee", "airstrike"

Sollte keine Munition für die entsprechende Waffe vorhanden sein, soll die entsprechende Fehlermeldung ausgegeben werden. Sollte keine Waffe ausgewählt werden, benutzt der Wurm standardmäßig die Pistole. Nach der Auswahl soll die Waffe und ihre Munition ausgegeben werden. Beispielausgabe:

<pre>> choose teleporter\n
Chose weapon teleporter Ammunition: 2\n
</pre>

### action [direction]

Parameter:

*   direction: eine der folgenden Richtungen: "l", "r", "d", "u", "ld", "rd", "lu", "ru". Diese stehen entsprechen für links, rechts, unten, oben, links unten, rechts unten, links oben und rechts oben.

Schießt mit Pistole, Raketenwerfer oder Flammenwerfer in die entsprechende Richtung.

### action [col] [row]

Parameter:

*   col: die Spalte
*   row: die Zeile

Teleportiert an die entsprechende Koordinate.

### action [col]

Parameter:

*   col: die Spalte

Führt den Luftangriff an der entsprechenden Koordinate aus.

### action

aktiviert den Baseballschläger.

### action idle

der Wurm tut nichts und setzt die Runde aus.

### map

Ausgabe des aktuellen Spielfeldes umrandet mit Koordinaten. Die Spaltenkoordinaten laufen jeweils von 0 bis 9 und die Zeilenkoordinaten von 0 bis Höhe des Spielfeldes. Jedes Field wird durch das entsprechende Zeichen dargestellt. Somit werden z.B. Luftelemente als Leerzeichen dargestellt. 

Beispielausgabe: Beachten Sie die Leerzeichen vor den einstelligen Zeilenkoordinaten und das Leerzeichen in der linken oberen und unteren Ecke. In der rechten oberen und unteren Ecke befindet sich nur ein Newline.

<pre>Current Map:\n
  0123456789012345678901234567890123456789\n
 0                                         0\n
 1                                         1\n
 2                                         2\n
 3           E*    EE                      3\n
 4          EEE   EEEE                     4\n
 5         EEEEEEEEEEEE~                   5\n
 6   *E   EEEEEEEEEEEEEE#                  6\n
 7   EE  EEEEEEEEEEEEEEEE                  7\n
 8  EEE EEEEEEEEEEEEEEEEEE                 8\n
 9 EEEEEEEEEEEEEEEEEEEEEEEE                9\n
10WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW10\n
  0123456789012345678901234567890123456789\n
</pre>

### state

*   Gibt den aktuellen Spielstatus aus.
    *   Welcher Spieler mit welchem Wurm am Zug ist.
    *   Welche Waffen der aktuelle Wurm hat. Die Waffen werden in der Reihenfolge ausgegeben wie in Kategorie "Waffen" aufgelistet. Beachten Sie das * am Ende der Waffe, dies kennzeichnet die aktuell ausgewählte Waffe (mittels choose Befehl).
    *   Wieviel Leben die noch vorhandenen Würmer beider Spieler haben und an welcher Koordinate sie liegen. Mit * und ~ wird nochmal die Teamzugehörigkeit gekennzeichnet.

Beispielausgabe:

<pre>current player: 1\n
current worm: Spookster (3) \n
\n
weapons of current worm:\n
  gun (ammunition: inf) *\n
  bazooka (ammunition: 1)\n
  teleport (ammunition: 1)\n
  blowtorch (ammunition: 1)\n
  melee (ammunition: 1)\n
  airstrike (ammunition: 1)\n

worms of player 1\n
  Spookster (3) 100 HP (5, 21) ~\n
worms of player 2\n
  Fat Agnus (4) 100 HP (3, 12) *\n
  Phil (5) 100 HP (6, 3) *\n
</pre>

Beispielausgabe des zweiten Spielers nach einigen Runden, in welchen er den Flammenwerfer verbraucht hat, um dem Gegner Schaden zuzufügen, einige Kisten aufgesammelt hat und zur Zeit den Teleporter ausgewählt hat:

<pre>current player: 2\n
current worm: Fat Agnus (4) \n
\n
weapons of current worm:\n
  gun (ammunition: inf)\n
  bazooka (ammunition: 1)\n
  teleport (ammunition: 2) *\n
  melee (ammunition: 2)\n
  airstrike (ammunition: 3)\n
\n
worms of player 1\n
  Spookster (3) 65 HP (6, 22) ~\n
worms of player 2\n
  Fat Agnus (4) 100 HP (2, 18) *\n
  Phil (5) 100 HP (6, 3) *\n
</pre>

### help

Dieser Befehl soll folgende Meldung ausgeben:

<pre>Available Commands:\n
  move [left/right] [0..3]\n
    Move your worm.\n
  choose [weapon]\n
    Select your weapon.\n
  action [l/r/d/u/ld/rd/lu/ru]\n
    Shoots current weapon.\n
    Activates blowtorch.\n
  action\n
    Activates melee attack.\n
  action [row] [col]\n
    Teleports to coordinate.\n
  action [col]\n
    Airstrike.\n
  action idle\n
    Do nothing.\n
  quit\n
    End the game.\n
  help\n
    Display this help.\n
  state\n
    Print the current game state.\n
</pre>

### quit

Beendet das Spiel ohne weitere Ausgabe mit Rückgabewert 0.

# Regeln und Spielablauf

## Schwerkraft

Die Schwerkraft ist allgegenwärtig und beeinflusst **zu jedem Zeitpunkt** die Würmer und Kisten (Erdfelder und Wasserfelder nicht).

*   Sollte sich unter dem Wurm Luft befinden, fällt der Wurm so lange nach unten, bis sich unter ihm kein Luftfeld mehr befindet. Das gilt natürlich auch, wenn sich unter dem Wurm ein Wurm bewegt/stirbt oder unter dem Wurm ein Erdfeld zerstört wird. Gleiches gilt für Kisten.
*   Sollte sich unter dem Wurm Wasser befinden, so "ertrinkt" er und wird aus dem Spiel entfernt. Kisten, die ins Wasser fallen, werden ebenfalls aus dem Spiel entfernt.
*   Sollte der Wurm mehr als ein Feld fallen, so verliert er pro zusätzlichem Feld 10 HP. Es folgt eine Ausgabe mit dem Namen des Wurmes, seiner ID und der Höhe des Schadens. Kisten erleiden beim Fallen keinen Schaden.

Beispielausgabe für einen Wurm der nach rechts gegangen ist und dann drei Felder fiel:

<pre>> move r 1\n
Phil (5) took 20hp fall damage\n
</pre>

## Spielbeginn

Die Würmer werden zufällig nacheinander erstellt. Drei für Spieler 1, dann drei für Spieler 2\. Diese Würmer haben eine ID (1-6), eine Teamzugehörigkeit (~/*), einen zufälligen Namen und von jeder Waffe 1 Munition (außer gun). Die Position der Erstellung des Wurm erfolgt zufällig in der ersten Zeile, danach fällt der Wurm hinunter. Hier bekommt er noch **keinen** Sturzschaden. Es kann jedoch vorkommen, dass der Wurm ins Wasser fällt, hierbei erscheint die entsprechende Todesmeldung (siehe Spielablauf). Für jeden Wurm wird dessen Name, ID und Position der Erstellung ausgegeben. Beispielausgabe (beachten Sie, dass hier 3 Würmer über Wasser erstellt wurden):

<pre>spawning Fishface (1) at (0, 34)
Fishface (1) drowned.
spawning Brain (2) at (0, 26)
Brain (2) drowned.
spawning Clive (3) at (0, 6)
spawning Black Panther (4) at (0, 36)
Black Panther (4) drowned.
spawning Ainsley (5) at (0, 24)
spawning Chuck Norris (6) at (0, 21)
</pre>

Für die zufällige Erstellung der Würmer und Kisten erhalten Sie von eine Random Klasse, welche die entsprechenden Werte liefert. Diese **muss** verwendet werden und **darf nur einmal** initialisiert werden, dies ist für das automatisierte Testen Ihrer Abgabe notwendig.  

### Wahl der Wurmnamen und Wurmposition

Wie bereits beschrieben werden zuerst drei Würmer für Spieler 1, dann drei Würmer für Spieler 2 generiert (Spieler 1 hat bekommt also ID 1..3, Spieler 2 bekommt ID 4..6).

Für jeden Wurm (aufsteigend nach den IDs gereiht) müssen folgende Aktionen durchgeführt werden. Zuerst muss der Wurmname mit Random::getWormName() generiert werden. Danach wird die Spalte des Wurms mit Random::getRandomInt(0, board_width_ - 1) generiert. Sollte es nicht möglich sein, den Wurm dort zu platzieren (da der Platz von einem anderem Wurm besetzt ist), muss eine neue Position generiert werden. Dies geschieht so lange, bis der Wurm erfolgreich platziert wurde.

Diese Reihenfolge der Operationen **muss** eingehalten werden, da sich sonst Ihre Zufallszahlen von jenen der Referenzlösung unterscheiden.

## Spielablauf

Das Spiel läuft rundenbasiert, Spieler 1 und Spieler 2 wechseln sich ab. Nach jeder Runde wird zyklisch der Wurm des Spielers gewechselt. Erste Runde: Es startet Spieler 1\. Die aktuelle map wird ausgegeben mit der Information, welcher Spieler mit welchem Wurm an der Reihe ist.

<pre>Current Map:
  0123456789012345678901234567890123456789
 0                                         0
 1                                         1
 2                                         2
 3           E     EE                      3
 4          EEE   EEEE                     4
 5         EEEEEEEEEEEE*                   5
 6    E   EEEEEEEEEEEEEE                   6
 7   EE ~EEEEEEEEEEEEEEEE                  7
 8  EEE EEEEEEEEEEEEEEEEEE*                8
 9 EEEEEEEEEEEEEEEEEEEEEEEE                9
10WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW10
  0123456789012345678901234567890123456789
Player 1 Worm Clive (3) at (7, 6) ready
</pre>

Danach können die Befehle beliebig oft und in beliebiger Reihenfolge eingegeben werden, mit folgender Ausnahme:

*   move kann nur einmal eingegeben werden (ebenso action).
*   der Spielzug wird nach dem action Befehl, oder wenn der eigene Wurm durch move einen Schaden erlitten hat beendet.

### Einsammeln der Kisten

Am Ende jeder Runde wird eine Kiste mit einer zufälligen Waffe (außer Pistole) erzeugt. Die Position der Erstellung der Kiste erfolgt auch hier zufällig in der ersten Zeile (Genaueres siehe unten). Der Inhalt (welche Waffe sich in der Kiste befindet) der Kiste wird zufällig mit 1-4 (alle Waffen außer gun) bestimmt, wobei die Reihenfolge der Kategorie Waffen zu entnehmen ist, beginnend mit dem Raketenwerfer. Es befindet sich immer eine Munitionseinheit in der Kiste. Die Pistole kann sich nicht in Kisten befinden, da sie ohnehin unendlich Munition besitzt. Danach fällt die Kiste hinunter. Es kann vorkommen dass die Kiste direkt ins Wasser fällt und so nie erscheint. Ebenso, dass die Kiste über einen Wurm erstellt wird und er sie sofort bekommt. Sobald ein Wurm eine Kiste aufgesammelt hat, kommt eine Meldung welche Waffe er bekommen hat und die Kiste verschwindet. Die Ammunition der aufgehobenen Waffe wird dabei um 1 erhöht. Ein Wurm kann auch mehrere Kisten in einer Runde aufsammeln. Beispielausgabe für einen Wurm welcher eine Kiste bekommt die auf ihn runter fällt:

<pre>Current Map:
  0123456789012345678901234567890123456789
 0                                         0
 1                                         1
 2                  #                      2
 3           E    #EE                      3
 4          E  ~  EE*                      4
 5    #   ~EEE EEEEEEEE                    5
 6   #E   EEEEEEEEEEEEEE                   6
 7   EE #EEEEEEEEEEEEEEEE                  7
 8 #EEE#EEEEEEEEEEEEEEEEEE                 8
 9 EEEEEEEEEEEEEEEEEEEEEEEE                9
10WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW10
  0123456789012345678901234567890123456789
Player 2 Worm Druss (6) at (4, 18) ready
> action u
Shot hit Earth at position (3, 18)
Druss (6) picked up 1 of teleport
Current Map:
  0123456789012345678901234567890123456789
 0                                         0
 1                                         1
 2                                         2
 3           E    #E                       3
 4          E  ~  EE* #                    4
 5    #   ~EEE EEEEEEEE                    5
 6   #E   EEEEEEEEEEEEEE                   6
 7   EE #EEEEEEEEEEEEEEEE                  7
 8 #EEE#EEEEEEEEEEEEEEEEEE                 8
 9 EEEEEEEEEEEEEEEEEEEEEEEE                9
10WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW10
  0123456789012345678901234567890123456789
Player 1 Worm Samson (1) at (5, 8) ready
> 
</pre>

#### Wahl der Kistenposition und Inhalte

Wie bei Würmern wird eine zufällige Spalte bestimmt (mit Random::getRandomIn(0, board_width - 1)). Direkt danach wird immer ein Integer für den Inhalt generiert (mit Random::getRandomIn(1, NUMBER_OF_WEAPONS - 1), wobei NUMBER_OF_WEAPONS == 5).

Sollte der Platz für eine Kiste nicht frei sein, so wird diese (mitsamt ihrem Inhalt) verworfen. Gleiches geschieht, wenn die Kiste im Wasser versinkt.

Es werden also immer genau zwei Zufallszahlen generiert. Es ist explizit nicht erlaubt, die Zufallszahlen erst beim Aufheben der Kiste zu generieren.

### Feuern der Waffen

Nachdem action aufgerufen wurde, verringert sich die entsprechende Munition um 1 und es wird angezeigt, welche Kartenelemente durch welchen Waffentyp Schaden bekommen haben. **Danach** erfolgen die Auswirkungen der Schwerkraft. Schaden wird hierbei in folgender Reihenfolge verteilt (Ebenso Ausgabe dadurch auftretender Fallschaden):

*   (1.) Nach Entfernung vom Schadensursprung (Flammenwerfer) / Einschlagspunkt (Raketenwerfer) (also immer erster Einschlagpunkt zuerst)
*   (2.) Bei gleicher Entfernung nach der Richtung: oben vor rechts vor unten vor links (i.e.: zuerst oben, danach im Uhrzeigersinn).

Schadensausgabe:

*   Pistole, Raketenwerfer, Luftangriff: Shot hit [Earth/Chest/Worm] at position [Koordinate]
*   Flammenwerfer: Torch hit [Earth/Chest/Worm] at position [Koordinate]
*   Baseballschläger: Attack hit Worm at position [Koordinate]

Beispielausgabe, bei der ein Wurm mit dem Raketenwerfer schießt.

<pre>Current Map:
  0123456789012345678901234567890123456789
 0                                         0
 1                                         1
 2           *                             2
 3           E    ~EE                      3
 4         #EEE#  EEEE                     4
 5         EEEEEEEEEEEE~                   5
 6    E  #EEEEEEEEEEEEEE                   6
 7   EE  EEEEEEEEEEEEEEEE                  7
 8 #EEE EEEEEEEEEEEEEEEEEE                 8
 9 EEEEEEEEEEEEEEEEEEEEEEEE                9
10WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW10
  0123456789012345678901234567890123456789
Player 1 Worm Korby (3) at (3, 16) ready
> choose bazooka
Chose weapon bazooka Ammunition: 1
> action l
Shot hit Earth at position (3, 11)
Shot hit Worm at position (2, 11)
Razz (5) took 40hp damage
Shot hit Earth at position (4, 11)
Razz (5) took 10hp fall damage
</pre>

Sollten Schüsse von der Pistole, Bazooka oder Luftangriff in die Leere gehen (also Rand der Map) kommt folgende Meldung:

<pre>Shot missed...\n
</pre>

Nach action ist die Runde beendet und es folgt die nächste Runde mit dem nächsten Spieler.

### Todesursachen und deren Ausgabe

Sobald die Lebenspunkte eines Wurms auf 0 fallen, sterben sie und werden aus dem Spiel entfernt. Würmer können sich auch selbst verletzen! Es folgt eine Ausgabe mit Name und ID des Wurms und die Todesursache. Beispielausgabe:

*   durch ertrinken

<pre>Chilli (1) drowned.\n
</pre>

*   durch fallen auf Erde oder anderen Wurm

<pre>Malone (2) fell into his death.\n
</pre>

*   durch fallen aus der Map

<pre>Pinkie (5) fell out of the map.\n
</pre>

*   durch Waffen

<pre>Bob (4) died.\n
</pre>

Die Ausgabe der Todesursache erfolgt, sobald ein Wurm gestorben ist. (Daher würde ein durch Waffen zerstörter Wurm nicht durch einen darauffolgenden Sturz wieder sterben) Beispielausgabe:

<pre>Current Map:
  0123456789012345678901234567890123456789
 0                                         0
 1                                         1
 2                  #                      2
 3           E*    EE*                     3
 4          EEE~  EEEE                     4
 5    #   ~EEEEEEEEEEEE                    5
 6   #E   EEEEEEEEEEEEEE                   6
 7   EE  EEEEEEEEEEEEEEEE                  7
 8 #EEE#EEEEEEEEEEEEEEEEEE                 8
 9 EEEEEEEEEEEEEEEEEEEEEEEE                9
10WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW10
  0123456789012345678901234567890123456789
Player 1 Worm Viking (2) at (4, 13) ready
> choose bazooka
Chose weapon bazooka Ammunition: 1
> action l
Shot hit Earth at position (4, 12)
Shot hit Worm at position (3, 12)
Mr. Lardtree (4) died.
Shot hit Worm at position (4, 13)
Viking (2) took 40hp damage
Shot hit Earth at position (5, 12)
Shot hit Earth at position (4, 11)
</pre>

## Spielende

Sollte am Anfang der Runde von einem Spieler keiner der Würmer mehr am Leben sein, vom gegnerischen Spieler aber schon, gewinnt der Spieler mit lebenden Würmern. Es folgt die Ausgabe welcher Spieler gewonnen hat (1\. oder 2.):

<pre>END: Player 1 win!\n</pre>

Sollten am Anfang der Runde von keinem Spieler lebende Würmer vorhanden sein (z.B. beide fallen ins Wasser oder verletzen sich selbst), ist das Spiel mit unentschieden zu beenden. Es folgt folgende Ausgabe:

<pre>END: Draw\n</pre>

Das Spiel beendet sich mit Rückgabewert 0.

Beispielausgabe, bei welcher der letzte Wurm eines Spielers (durch den Schläger) stirbt:

<pre>> action 
Attack hit Worm at position (4, 12)
Bob (4) died.
Attack hit Worm at position (3, 11)
Sporty (6) took 50hp damage
Current Map:
  0123456789012345678901234567890123456789
 0                                         0
 1                                         1
 2                                         2
 3           *     EE#                     3
 4          EE*   EEEE                     4
 5   #     EEEEEEEEEEEE                    5
 6   #E   EEEEEEEEEEEEEE#                  6
 7   EE  EEEEEEEEEEEEEEEE#                 7
 8 #EEE EEEEEEEEEEEEEEEEEE                 8
 9 EEEEEEEEEEEEEEEEEEEEEEEE                9
10WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW10
  0123456789012345678901234567890123456789
END: Player 2 win!
</pre>

## Fehlermeldungen mit Rückgabewerten

*   Wird eine ungültige Anzahl an Parametern eingelesen:
    *   Das Spiel beendet sich in diesem Fall mit Rückgabewert -1.
    *   Ausgabe:

        <pre>[ERROR] usage: ./swworms <config-file>\n</pre>
        
*   Wird eine fehlerhafte Konfiguration oder Map eingelesen:
    *   Das Spiel beendet sich in diesem Fall mit Rückgabewert -2.
    *   Ausgabe:

        <pre>[ERROR] invalid config file!\n</pre>


# Erlaubte Bibliotheken

*   alle Bibliotheken der C++ Standard Library

# Referenzen

Die Übung basiert auf der Übung der UE [Softwareentwicklung Praktikum](https://tube.tugraz.at/paella/ui/browse.html?series=bd9f22ba-97d4-4835-865d-2a80b08da9a3)
der TU Graz, gehalten im Sommer Semester 2019 von Prof. Frank Kappe und Dr. Christian Safran. Sie wurde von Dr. Christian Safran konzeptioniert, der mir die Aufgabenstellung auch freundlicherweise zur Verfügung gestellt hat. Vielen Dank.   