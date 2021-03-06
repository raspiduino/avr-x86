/*
    avr-x86 - x86 emulator running on AVR Arduino!
    Copyright (C) 2021 @raspiduino

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

/* ------------------------ Include libraries ------------------------ */
/* Fake86 */
#include "cpu.h"

/* ------------------------ setup() function ------------------------- */
void setup() {
    Serial.begin(9600); // Open serial port with baud 9600 bps
    
    /*  Display welcome messages  */
    Serial.println(F("avr-x86 - Copyright (C) 2021 @raspiduino"));
    Serial.println(F("Github repo: https://github.com/raspiduino/avr-x86"));
    Serial.println(F("Under GPL-v3"));

    /* Init SD card */
    sdinit();
    
    /* Copy data from virtual disk to virtual ram */
    ramload();

    /* Init the fake86 */
    Serial.print(F("Init Fake86"));
    init86();
    Serial.println(F(". Done! Starting emulator..."));
}

/* ------------------------ loop() function -------------------------- */
void loop() {
    exec86(100); // Execute fake86
}
