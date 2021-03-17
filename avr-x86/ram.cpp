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

    Virtual RAM file is located in RAM_FILE macro path
    Default is 'RAM.BIN'
*/

#include "ram.h"

#ifdef BOOT_PROMPT
char filepath[80]; // Virtual disk filepath
#endif
#ifndef BOOT_PROMPT
char filepath[] = BOOT_FILE;
#endif

void ramload(){
    #ifdef BOOT_PROMPT
    fileinput();
    while(pf_open(filepath)){
        Serial.print(F("Error opening "));
        Serial.println(filepath);
        fileinput();
    }
    #endif
    #ifndef BOOT_PROMPT
    pf_open(filepath); // Open disk image file
    #endif
    
    Serial.print(F("Loading disk image"));

    #ifndef ONE_USE
    int ramloc = 0;
    uint8_t buf[RAM_BUFFER];
    
    while (1) {
        pf_lseek(ramloc); // Change the cusor

        // Read disk image
        UINT nr1;
        pf_read(buf, RAM_BUFFER, &nr1); // Read disk image
        if (nr1 == 0) break; // Break at the end of file

        //Serial.write(buf, nr1); // For debug only

        // Write to vram
        UINT nr2;
        pf_open(RAM_FILE); // Open ram image file
        pf_lseek(ramloc); // Change the cusor
        pf_write(buf, nr1, &nr2); // Write ram image
        pf_write(0, 0, &nr2); // End of writing

        ramloc = ramloc + RAM_BUFFER; // Increase ramloc

        delay(200);

        pf_open(filepath);

        Serial.print(F("."));
    }

    Serial.println(F(". Done!"));
    #endif
}

#ifdef ONE_USE
byte ramread(uint32_t addr){
    uint8_t buf[1];
    
    pf_open(filepath); // Open ram image file
    UINT nr;
    pf_lseek(int(addr)); // Change the cusor
    pf_read(buf, 1, &nr); // Read disk image
    return buf[0]; // Return the buffer
}

void ramwrite(uint32_t addr, byte value){
    Serial.println(value);
    uint8_t buf[1];
    buf[0] = value;
    pf_open(filepath); // Open ram image file
    UINT nr;
    pf_lseek(int(addr)); // Change the cusor
    pf_write(buf, 1, &nr); // Write ram image
    Serial.write(buf, nr);
    Serial.println(nr);
    pf_write(0, 0, &nr); // End of writing
}
#endif
#ifndef ONE_USE
byte ramread(uint32_t addr){
    uint8_t buf[1];
    
    pf_open(RAM_FILE); // Open ram image file
    UINT nr;
    pf_lseek(addr); // Change the cusor
    pf_read(buf, 1, &nr); // Read disk image

    return buf[0]; // Return the buffer
}

void ramwrite(uint32_t addr, byte value){
    byte buf[1];
    buf[0] = value;
    pf_open(RAM_FILE); // Open ram image file
    UINT nr;
    pf_lseek(addr); // Change the cusor
    pf_write(buf, 1, &nr); // Write ram image
    pf_write(0, 0, &nr); // End of writing
}
#endif

/* fileinput() - Ask for virtual disk file to boot from */
#ifdef BOOT_PROMPT
void fileinput(){
    Serial.print(F("$ "));
    
    //while(Serial.available() == 0); // Wait until Serial input
    
    String tmpstring;
    while (1){
        if(Serial.available() > 0){
            // Read the char
            int incomingByte = Serial.read(); //Read the character ASCII number to the incomingByte varrible
            
            if(incomingByte == 10 | incomingByte == 13) break;
            else{
                tmpstring = String(tmpstring + char(incomingByte));
            }
        }
    }
    
    tmpstring.toCharArray(filepath, tmpstring.length()+1); // Convert the filepath to char array
    Serial.println(filepath);
}
#endif
