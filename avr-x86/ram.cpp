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

/*
    Note on avr-x86's RAM:
    A few KB is not enough for our emulator. So ram.cpp will create a
    virutal RAM on the SD card, read and write from it and send to the emulator.

    Virtual RAM file is located in 'avr-x86/ram.bin'
*/

#include "ram.h"

char filepath[80]; // Virtual disk filepath

void ramload(){
    while(pf_open(fileinput())) fileinput();
    
    Serial.print(F("Loading disk image"));

    int ramloc = 0;
    uint8_t buf[RAM_BUFFER];

    if (pf_open(filepath)); // Open disk image file
    
    while (1) {
        if (pf_lseek(ramloc)); // Change the cusor

        // Read disk image
        UINT nr;
        if (pf_read(buf, RAM_BUFFER, &nr)); // Read disk image
        if (nr == 0) break; // Break at the end of file

        // Write to vram
        if (pf_open("avr-x86/ram.bin")); // Open ram image file
        if (pf_lseek(ramloc)); // Change the cusor
        if (pf_write(buf, RAM_BUFFER, &nr)); // Write ram image
        pf_write(0, 0, &nr); // End of writing

        ramloc = ramloc + RAM_BUFFER; // Increase ramloc

        Serial.print(F("."));
    }

    Serial.println(F(". Done!"));
}

byte ramread(uint32_t addr){
    uint8_t buf;
    
    if (pf_open("avr-x86/ram.bin")); // Open ram image file
    UINT nr;
    if (pf_lseek(addr)); // Change the cusor
    if (pf_read(buf, 1, &nr)); // Read disk image

    return buf; // Return the buffer
}

void ramwrite(uint32_t addr, byte value){
    if (pf_open("avr-x86/ram.bin")); // Open ram image file
    UINT nr;
    if (pf_lseek(addr)); // Change the cusor
    if (pf_write(value, 1, &nr)); // Write ram image
    pf_write(0, 0, &nr); // End of writing
}

/* fileinput() - Ask for virtual disk file to boot from */
char* fileinput(){
    Serial.print(F("Please enter virtual disk file to boot: "));
    
    while(Serial.available() == 0); // Wait until Serial input
    
    String tmpstring;
    while(Serial.available() > 0){
        // Read the char
        int incomingByte = Serial.read(); //Read the character ASCII number to the incomingByte varrible
        
        if(incomingByte == 13 | incomingByte == 10) break;
        else{
            tmpstring = String(tmpstring + char(incomingByte));
        }
    }
    
    tmpstring.toCharArray(filepath, sizeof(tmpstring)); // Convert the filepath to char array
}
