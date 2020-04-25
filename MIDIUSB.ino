/**
 * Main function realized MIDI eDrum functionality.
 * 
 * Project use a Arduino board with native USB capabilities (Arduino Micro in this case).\ 
 * Code is based on MIDIUSB library (by gurbrinder grewal).
 * 
 * ePads are connected to 16 channels multiplekser with CD74HC4067 chip. 
 */
#include <Arduino.h>
#include "eDrumUsb.hpp"

void setup() {
}

eDrum drumset;
void loop() {
 drumset.pollingAllPads();
}
