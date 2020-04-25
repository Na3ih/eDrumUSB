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
 * TODO: !!! Zrobic drugi mux do wykrywania wpietyych jackow i funkcje do zapamietania numerow
 */
  
class eDrum
{
    unsigned int threeshold; ///< Impact threshold. 
    unsigned int afterTouchDelay; ///< Minimal delay betwen impacts. 
    Mux16 mux16; ///< CD74HC4067 multuiplekser structure.
    size_t numberOfPads; ///< Number of connected ePads.
    ePad * drums; ///< Pointer to ePads table;
    
    /**
     * Set initial values to connected ePads.
     */
    bool setupPads(Mux16 * mux);   
    
    public:
    /**
     * Default constructor.
     */
    eDrum();
    
    /**
     * Checking if any drum pad was hit.
     */
    void pollingAllPads(void);

    /*
     * Object destructor.  
     */
    ~eDrum();
};
