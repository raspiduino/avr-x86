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
/* PetitFS */
#include <PetitFS.h>
#include <PetitSerial.h>

/* Fake86 */
#include "cpu.h"

/* ------------ Varriables, macros, objects and functions ------------ */
/* Instances of classes */
// Use PetitSerial instead of normal Serial (compatibility reason)
//PetitSerial PS;
//#define Serial PS

FATFS fs; // Create a filesystem object

/* Functions */
void errorHalt(char* msg);
char* fileinput();

/* ------------------------ setup() function ------------------------- */
void setup() {
    Serial.begin(9600); // Open serial port with baud 9600 bps
    
    /*  Display welcome messages  */
    Serial.println(F("avr-x86 - Copyright (C) 2021 @raspiduino"));
    Serial.println(F("Github repo: https://github.com/raspiduino/avr-x86"));
    Serial.println(F("This program comes with ABSOLUTELY NO WARRANTY."));
    Serial.println(F("This is free software, and you are welcome to redistribute it under certain conditions. See GPL-v3 license"));

    /* Init the SD card */
    if (pf_mount(&fs)) errorHalt("pf_mount"); // Mount filesystem
    
    /* Ask for virtual disk file to boot from */
    while(pf_open(fileinput())) fileinput();

    /* Init the fake86 */
    init86();
    
    /* Read data from the virtual disk file and run fake86 to emulate it */
    
}

/* ------------------------ loop() function -------------------------- */
void loop() {
    
}

/* --------------------------- Functions ----------------------------- */
/* errorHalt() - Function to raise error */
void errorHalt(char* msg){
    Serial.print("Error: ");
    Serial.println(msg);
    while(1);
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
    
    char filepath[80];
    tmpstring.toCharArray(filepath, sizeof(tmpstring)); // Convert the filepath to char array
    return filepath;
}
