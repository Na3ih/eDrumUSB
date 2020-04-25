/**
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
