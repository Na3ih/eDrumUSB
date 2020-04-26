/**
 * Main function realized MIDI eDrum functionality.
 * 
 * Project use a Arduino board with native USB capabilities (Arduino Micro in this case). 
 * Code is based on MIDIUSB library (by gurbrinder grewal).
 * 
 * Board is recognized by the PC as MIDI device what allows communication with software 
 * like Fruity Loops Studio.
 *
 * 
 */
#include <Arduino.h>
#include "eDrumUsb.hpp"

void setup() {
}

eDrum drumset;
void loop() {
 drumset.pollingAllPads();
}
