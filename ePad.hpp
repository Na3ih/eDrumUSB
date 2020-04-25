#pragma once
#include <Arduino.h>

class ePad
{
	private:
		//const unsigned int inputPinNumber; ///< 
        //const unsigned int ledPinNumber;
		bool hit; ///< is pad was hit?
		byte code; ///< note number
		byte channel; ///< channel number
		unsigned int preassure; ///< hit force
        unsigned long hitTime; ///< millis() 
	public:
        ePad() {
            Serial.println("ePad Created");
        }
		ePad(byte pin, byte code, byte channel);
		void setupPad(byte code, byte channel);
        bool wasHit(struct Mux16 * mux, unsigned int threeshold, unsigned int afterTouchDelay);
        //bool wasHit(const unsigned int analogPin, unsigned int threeshold, unsigned int afterTouchDelay);
		unsigned int getPreassure(void);	///< 
        void sendMidiNoteOn(void);
		void clearPad(void);
};
