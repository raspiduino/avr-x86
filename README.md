# avr-x86
## What is this?
*AVR-x86* is a 8086+ emulator running on AVR Arduino. This project is originally forked from https://github.com/corax89/Arduino_8086_emulator
![Proteus simulation](https://user-images.githubusercontent.com/68118236/112129528-1415f400-8bfa-11eb-93f2-7bdf84fe7214.png)
<br> As you can see in the image, AVR-x86 is running [*Brainfuck*](https://en.wikipedia.org/wiki/Brainfuck) written in 8086 assembly,

## How?
AVR-x86 is based on [*Fake86*](http://fake86.rubbermallet.org/)'s core, ported to AVR by *corax89*. In the original version, binary is stored in a RAM array, then boot up and execute it. But AVR-x86 load the binary stored in a SD card to a *virtual RAM file* on the SD card. So you can have more RAM for the emulator than the AVR hardware's. That also means AVR-x86 can execute larger binary file!

## Why?
For fun. It just a toy.

From [dmitry.gr](http://dmitry.gr/?r=05.Projects&proj=07.%20Linux%20on%208bit):
> It is common to see newbies asking in microcontroller forums if they can run Linux on their puny little 8-bit micro. The results are usually laughter.

## Todo
- Write an bootloader for floppy disk files on SD card, not just executing one file at a time.
- Reduce the sketch file
- Boot more things
- ...

If you have any ideas, you can open an issue and tell me!

## Some other projects releated to this
- [Linux on 8-bit AVR by *Dmitry.GR*](http://dmitry.gr/?r=05.Projects&proj=07.%20Linux%20on%208bit)
- [CP/M on an AVR by *Spritesmods.com*](https://spritesmods.com/?art=avrcpm)
- [Launch .COM file on Arduino by *corax89* (the repo where this repo forked)](https://github.com/corax89/Arduino_8086_emulator)
- [8086 emulator on Arduino DUE by *miker00lz*](https://forum.arduino.cc/index.php?topic=605391.0)
- [8086 emulator on ESP8266 (include video)](https://www.hackster.io/janost/ibm-pc-xt-emulator-on-an-esp8266-42abcc)

# Configs
There are configs macro inside *config.h*. You can follow the instructions in that file.
<br>Notes: You can enable more feature if you has more flash and RAM, but for Arduino UNO, you can only enable `ONE_USE` for now (autoload the file when boot, no bootprompt!).
