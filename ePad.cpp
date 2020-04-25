#include "ePad.hpp"
#include <Arduino.h>
#include <CD74HC4067.hpp>
#include <MIDIUSB.h>

/*
 * Default constructor.
 * @warning Use the 'setupPad' function 
 *          to set a code and channel values.
 */
ePad::ePad()
{ 
  this->code = 0; 
  this->channel = 0; 
  this->preassure = 0; 
  this->hitTime = 0; 
}

/**
 * Set values for pad.
 * @param note    Note number
 * @param channel Channel number
 * @return None
 */
void ePad::setupPad(byte note, byte channel)
{ 
	this->code = note; 
	this->channel = channel; 
}

/**
 * @brief Is pad was hit.
 * 
 * @description
 * If pad was hit with force greather than threeshold and after delay time
 * measured values will be assigned to object fields.
 * 
 * @param  mux Pointer to multiplekser structure.
 * @param  threeshold Impact threshold. 
 * @param  afterTouchDelay Minimal delay betwen impacts.   
 * @retval true  Pad was hit.
 *         false Pad wasn't hit.
 */
bool ePad::wasHit(struct Mux16 * mux, unsigned int threeshold, unsigned int afterTouchDelay) {
    selectChannel(mux, this->channel);
    unsigned long actualTime = millis();
    if (actualTime > this->hitTime + afterTouchDelay) {
        unsigned int force = analogRead(mux->SIG); 
        if (force > threeshold) {
            this->preassure = map(force, 0, 1024, 0, 127);
            this->hitTime = actualTime;
            return true;
        }
        else {
          return false;
        }
    }
    else {
        return false;
    }
}

/**
 * Get hit force value. 
 * 
 * @return Mapped last impact force value.
 */
unsigned int ePad::getPreassure(void) {
    return this->preassure;
}

/**
 * Send MIDI Note On command with values assigned to pad object.
 */
void ePad::sendMidiNoteOn(void)
{ /**
    NOTE: Number 0 here = 1 in FL Studio! 
  */
  midiEventPacket_t noteOn = {0x09, 0x90 | (uint8_t)this->channel, (uint8_t)this->code, (uint8_t)this->getPreassure()}; 
  MidiUSB.sendMIDI(noteOn);
  MidiUSB.flush();
}
