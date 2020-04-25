#pragma once

#include <Arduino.h>
#include "ePad.hpp"
#include <CD74HC4067.hpp>

/**
 * TODO:
 * 1. Konstruktor dla eDrum (jeden z mux, drugi dla analogPin?)
 * 4. Enkoder 
 * 5. Tests
 * 6. Doxygen
 * 7.LCD 
*/

/**
 * !!! Podlaczac do nieparzystych piezo, a do parzystych "czujnik". 
 */
  
class eDrum
{
    unsigned int threeshold;
    unsigned int afterTouchDelay;
    Mux16 mux16;
    size_t numberOfPads;
    ePad * drums; // wskaznik na tablice bebnaw
    bool setupPads(Mux16 * mux);
    
    public:
    eDrum();
    void pollingAllPads(void);
    //void noteOn(byte channel, byte pitch, byte velocity);
    void refresh(void);
    ~eDrum();  //disable Mux, LCD Bye
};
