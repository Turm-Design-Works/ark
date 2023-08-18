# ark*~
**MIDI Controller with Rotaly Encoders** for Algorhythmic Composition / Experimental Sound Artists.  
We use seeeduino xiao as core, and 2 ATmega328P-PU chips as functional part.

ark*~  is open source hardware and software.

![IMG_7801](https://github.com/Turm-Design-Works/ark/assets/75283624/064a1bd0-33da-4259-b255-d205b1ef2da7)

# LICENSES
・firmware and PCB :  **MIT**  ( [Turm Design Works LLC.](https://turmdesignworks.com) )

・arduino MIDIUSB Library :  **LGPL2.1**  ( https://github.com/arduino-libraries/MIDIUSB/ ) 

# How to install

first of all...

- Download and install `Arduio IDE`.  
- Install `MIDIUSB library` from library manager of Arduino IDE.  
> ark*~ **is using MIDIUSB library as it is, You don't need to modify library code.**

Seeeduino Xiao SAMD21

- Setup Seeed SAMD boards `1.8.3` from board manager of Arduino IDE.

- Upload ark-main sketch to seeeduino xiao.

ATmega328P-PU *2

- Burn arduino bootloader to chips.

- Upload ark-ATmega328P_U2 and U3 sketch.
