english version below!

# Mega Projekt: Binäre Anzeige der Uhzeit mit LEDS
Die Idee war schon länger vorhanden und nachdem es dieses spezielle Ding nicht zu kaufen gibt: Hab ich da was gemacht
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
- 17 3-mm-LEDS wie diese :https://www.amazon.de/gp/product/B01BTYHOMC/
- PCB nach EAGLE-Plan
- ESP32 https://www.amazon.de/gp/product/B0DGG865GM/
- 2kOhm widerstand als Bremswiderstand für die LED am gigitalen Ausgang

---
---
# Mega Project: Binary Display of Time with LEDs
The idea had been around for a while, and since this special thing couldn’t be bought, I decided to make one myself.

### TODO: Add image here
## General:
The entire project is based on an ESP32 (e.g. [this one](https://www.amazon.de/dp/B0DGG865GM)), which has 16 PWM-capable outputs. This is almost enough to display the time:

Minutes and seconds each require 6 bits (0…63)
The hour display needs 5 bits (0…31). This means that one LED must be connected with a fixed resistor, and all others can be dimmable. Not so bad, let’s do it that way. Now that the basic idea is in place, let’s move on to the implementation.

## Electronics
The admittedly very simple circuit diagram for the device is written in [Autodesk EAGLE](http://eagle.autodesk.com/eagle/software-versions/50). The software is, as far as I can see, free, but requires registration. To get started, I strongly recommend a tutorial like this: https://www.youtube.com/watch?v=1AXwjZoyNno 
This will help you understand the logic and tool usage quite well.

I used the plan to create gerber files (CNC files for the boards) and ordered them from [PCBway](https://www.pcbway.com/). The instructions [hier](https://www.pcbway.com/helpcenter/generate_gerber/Generate_Gerber_files_in_Eagle.html) worked very well for me.

### TODO: Add image here.

## CAD / Housing
As you can easily recognize, the front panel is a Lego building plate, 10x6 studs. The studs (⌀ 4.9 mm) are drilled with a 3.3mm drill bit. This allows the 3mm LEDs to fit snugly. The first prototype with a 3mm large hole did fit nicely, but the LEDs don’t handle the forces of being placed well. The board uses the Lego grid size of 8 mm. This allows the LEDs on the board to fit cleanly into the holes. The housing itself is constructed in [FreeCAD](https://www.freecad.org/) and then printed at home.

## Software
The software is written in the [Arduino-IDE](https://www.arduino.cc/en/software). I’ll try to gather the necessary libraries below. The ESP provides a Wi-Fi access point. In this network, the ESP serves the webpage that sets the clock. The control is realized via HTTP requests (POST). Especially the http-request part on the backend was strongly supported by AI, namely the one included in [Brave](https://brave.com/).
I programmed the ASCII table, and the clock can display all letters, numbers, and a few special characters with its 3x5 large display field.

---
## Parts List
- 17 3mm LEDs like these: https://www.amazon.de/gp/product/B01BTYHOMC/
- PCB according to EAGLE plan
- ESP32: https://www.amazon.de/gp/product/B0DGG865GM/
- 2kOhm resistor as a braking resistor for the LED at the digital output
