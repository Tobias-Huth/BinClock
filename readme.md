# Mega Projekt: Binäre Anzeige der Uhzeit mit LEDS
Die Idee was schon länger vorhanden und nachdem es dieses spezielle Ding nicht zu kaufen gibt: Hab ich da was gemacht

## TODO: Bild hin

## Allgemein:
Das ganze Projekt hat einen ESP32 (z.B [dieser](https://www.amazon.de/dp/B0DGG865GM)) als Kern. Der ESP hat 16 PWM-fähige Ausgänge. Das reicht fast, um die Uhrzeit anzuzeigen:
Minuten und Sekunden benötigen jeweils 6 Bit (0..63)
Die Stundenanzeige braucht 5 Bit (0..31). 
Das heißt, eine LED muss mit einem Widerstand fest beschalten werden, alle anderen können dimmbar sein. gar nicht so schlecht, machen wir so.
Nachdem diese Grundidee vorhanden ist, nun zur Umsetzung.

## Elektronik

Der zugegeben wirklich einfache Schaltplan für das Gerät ist in [Autodesk EAGLE](http://eagle.autodesk.com/eagle/software-versions/50) geschrieben. Die Software ist, soweit ich sehen kann, frei, nur eine Anmeldung ist nötig.
Um selbst was zu machen, empfehle ich dringend ein Tutorial wie dieses:
https://www.youtube.com/watch?v=1AXwjZoyNno
Damit versteht man die Bedienlogik und die Logik des Tools ganz gut.

Den Plan habe ich dann genutzt, um gerber-files (CNC-Dateien für die Platinen) herzustellen und bei [PCBway](https://www.pcbway.com/) zu bestellen. Die Anleitung [hier](https://www.pcbway.com/helpcenter/generate_gerber/Generate_Gerber_files_in_Eagle.html) hat bei mir sehr gut funktioniert.

TODO: Bild hier rein.

## CAD / Gehäuse
Wie man unschwer erkennen kann, ist die Frontplatte eine Lego Bauplatte, 10x6 Noppen. Die Noppen ( ⌀ 4.9 mm) sind mit einem Bohrer 3,3mm ausgebohrt. So passen die 3mm-LEDs locker. Der erste Prototyp mit 3mm goßem Loch hat zwar schön geklemmt, die LEDs vertragen aber die Kräfte beim Aufsetzen nicht gut.
Die Platine benutzt das Lego-Rastermaß 8 mm. So passen die LEDs auf der Paltine sauber in die Löcher.
Das Gehäuse selbst ist in [FreeCAD](https://www.freecad.org/) konstruiert und dann gedruckt.

## Software
Die Software ist in [Arduino-IDE](https://www.arduino.cc/en/software) geschrieben. Die notwendigen Bibliotheken versuche ich weiter unten zusammenzutragen.
Der ESP stellt einen WLAN-Access-Point zu Verfügung. In diesem Netz serviert der ESP die Webseite, mit der die Uhr gestellt wird. Die Steuerung wird über http-request (POST) realisiert.
Die in [Brave](https://brave.com/) enthaltene KI hat mir wirklich gut geholfen, den Teil der Verarbeitung der http-requests im Backend einfach zu implementieren.
Ich hab die ASCII-Tabelle abprogrammiert, die Uhr kann mit ihrem 3x5 großen Anzeigefeld alle Buchstaben, Ziffern und ein paar Sonderzeichen darstellen.

---

## Stückliste
17 3-mm-LEDS wie diese :https://www.amazon.de/gp/product/B01BTYHOMC/
PCB nach EAGLE-Plan
ESP32 https://www.amazon.de/gp/product/B0DGG865GM/
2kOhm widerstand als Bremswiderstand für die LED am gigitalen Ausgang