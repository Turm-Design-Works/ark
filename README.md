# ark*~
**MIDI Controller with Rotaly Encoders** for Algorhythmic Composition / Experimental Sound Artists.  
We use Seeed Xiao as core, and ATmega328P-PU ×2 AVR chips as functional part.

ark*~  is **Open Source** hardware and software.

![IMG_7801](https://github.com/Turm-Design-Works/ark/assets/75283624/064a1bd0-33da-4259-b255-d205b1ef2da7)

# LICENSES
- firmware and PCB :  [**MIT**](https://github.com/Turm-Design-Works/ark/blob/main/LICENSE)  
Copyright (C) 2023 Turm Design Works LLC.

- arduino MIDIUSB Library :  [**LGPL2.1**](https://github.com/arduino-libraries/MIDIUSB/blob/master/LICENSE.txt)  
Copyright (C) 1991, 1999 Free Software Foundation, Inc.
> ark*~ is using MIDIUSB library as it is. You don't need to modify MIDIUSB.h library,  
> just only install and calling.

# How to install

**first of all...**

- Download and install `Arduio IDE`.  
- Install `MIDIUSB library` from library manager of Arduino IDE.  

**Seeeduino Xiao SAMD21**

- Setup `Seeed SAMD boards` ver.`1.8.3` from board manager of Arduino IDE.

- Upload ark-main sketch to seeeduino xiao.

**ATmega328P-PU ×2**

- Burn `Arduino bootloader` to 2 chips.

- Upload ark-ATmega328P_U2 and U3 sketch.
