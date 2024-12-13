# Mega Project: Binary Display of Time with LEDs
The idea had been around for a while, and since this special thing couldn’t be bought, I decided to make one myself.

### TODO: Add image here
## General:
The entire project is based on an ESP32, which has 16 PWM-capable outputs. This is almost enough to display the time:

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
17 3mm LEDs like these: https://www.amazon.de/gp/product/B01BTYHOMC/
PCB according to EAGLE plan
ESP32: https://www.amazon.de/gp/product/B0DGG865GM/
2kOhm resistor as a braking resistor for the LED at the digital output