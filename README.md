QuizCandyDispenser
===================

Welcome to the Quiz Based Educational 3D Printed Candy Dispenser
![preview alt_text](https://raw.githubusercontent.com/FrYakaTKoP/QuizCandyDispenser/master/doc/preview.jpg)


History and About
-------------
The Project was born in a [**Discord Group**](https://discordapp.com/invite/KWpvRSs) Fan Group of the famous 3D Print Youtuber [**Choas Drucker**](https://www.youtube.com/user/ufgBishob).  Please check out his [**Channel**](https://www.youtube.com/user/ufgBishob) on youtube. 

The Initial Idea is a Candy Dispenser where you have to solve a question or similar, to get the Candy. The Hardware shall be mostly 3d printed or easy to source hardware. Like the very common RAMPS with lcd kit as the mainboard or the 9g hobby servo as actuator. 

Project Status
-----------

Still pretty early phase of the project.  Inital Target is a to fix the "to Buy" Hardware, draw schematics and write a initial Hardware test program.

License
----
*todo: add License information and credits here*

Credits
----
Lofwyr: Mechanical Design  
waschbaerbauch75: Testing and Pictures  
FrY:  Electronics and Firmware  

BOM: Bill Of Material
-------------

{Warning Pre Alpha not ready}

- 3D Printed Parts:
**thingiverse** *TODO: add link here*
- Ardunio/Genuino Mega2560
- 5V USB Power supply
- Arduino Mega compatible USB lead
- 1x RAMPS v1.4 
- 1x RepRapDiscount_Full_Graphic_Smart_Controller
incl. cables and ramps adapter
- 4x Mechanical endstops (eg.: https://www.thingiverse.com/thing:762 or https://www.banggood.com/5Pcs-RAMPS-1_4-Endstop-Switch-For-RepRap-Mendel-3D-Printer-With-70cm-Cable-p-1054555.html?rmmds=search&cur_warehouse=CN or https://www.amazon.de/Rokoo-Mechanisches-Endstop-Schalter-Modul-Endstop-3D-Drucker/dp/B075FQD5NW/ref=sr_1_7?ie=UTF8&qid=1512333714&sr=8-7&keywords=ramps+endstop)
- 9g Hobby RC Servo (Hextronik HXT-900 https://hobbyking.com/de_de/hxt900-micro-servo-1-6kg-0-12sec-9g.html or similar)
- Window (still unclear most likely a 100x150 photo frame) *TODO: Add dimension *


Electrical Connections / Schematic
-------------

![electronics alt_text](https://raw.githubusercontent.com/FrYakaTKoP/QuizCandyDispenser/master/doc/electronics.jpg)
Thanks to **waschbaerbauch75** for taking pictures

- Plug the Ramps board to the arduino mega
- connect Servo to SER1 Servo output also put a jumper between 5V and Vcc (header left of the reset switch)
  refer to this picture:  
![servo_pin alt_text](https://raw.githubusercontent.com/FrYakaTKoP/QuizCandyDispenser/master/doc/servo_pin.png)
Thanks to **waschbaerbauch75** for taking pictures

- connect Input Button A to Xmin endstop
- connect Input Button B to Xmax endstop
- connect Input Button C to Ymin endstop
- connect Input Button D to Ymax endstop
- plugin the lcd adapter
- connect lcd cables
- plug in the Arduino to USB to power it
- it should work now (you need to flash the firmware and *prepare sd card first*, if not done allready)



Software
---

*sorry not ready, documentation will come soon*

Libs:
u8glib by oliver (Arduino Library Manager)
VarSpeedServo (https://github.com/netlabtoolkit/VarSpeedServo) -> follow installation guide of the lib *TODO: Add more instructions*


