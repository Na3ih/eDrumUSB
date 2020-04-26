#pragma once
#include <Arduino.h>

/**
 * Class represent a single electronic pad (piezoelectric transducer)
 * connected to 16 channels multiplekser with CD74HC4067 chip.
 * 
 * 
 */
class ePad
{
	private:
		byte code; ///< Note number.

    /**
     *  @warning: Channel is a value for both the MIDI channel 
     *  and the multiplexer channel connected to.
     */
		byte channel; ///< Channel number.
		unsigned int preassure; ///< Hit force value(mapped).
    unsigned long hitTime; ///< Last hit time (millis()). 
	public: 
    /*
     * Default constructor.
     * @warning Use the 'setupPad' function 
     *          to set a code and channel values.
     */
    ePad();

    /**    
     * Set values for pad.    
     */
		void setupPad(byte code, byte channel);  
    
    /**
     * Is pad was hit.
     */
    bool wasHit(struct Mux16 * mux, unsigned int threeshold, unsigned int afterTouchDelay);

    /**
     * Get hit force value. 
     */
		unsigned int getPreassure(void);	
   
    /**
    * Send MIDI 'Note On' command with values assigned to pad object.
    */
    void sendMidiNoteOn(void);
};
