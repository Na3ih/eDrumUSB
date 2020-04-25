#include "ePad.hpp"
#include <Arduino.h>
#include <CD74HC4067.hpp>
#include <MIDIUSB.h>

/**
* eDrum class constructor.
* @param pin	 Arduino pin attached to pad number (for preassure detection should be analog pin)
* @param code	 MIDI code (note) number
* @param channel MIDI channel number
*/
ePad::ePad(byte pin, byte code, byte channel)
{
	//this->pinNumber = pin;
	this->code = code;
	this->channel = channel;
	//pinMode(INPUT, this->pinNumber);	///< return?
	
	Serial.println("Create Object ...");
	Serial.print("Attached to pin ");
	//Serial.println(this->pinNumber);
	Serial.print("MIDI code: ");
	Serial.print(this->code);
	Serial.print("MIDI channel: ");
	Serial.println(this->channel);
	Serial.print("Created");
}

void ePad::setupPad(byte note, byte channel)
{
    this->hit = false; 
	this->code = note; 
	this->channel = channel; 
	this->preassure = 0; 
    this->hitTime = 0; 
}

bool ePad::wasHit(struct Mux16 * mux, unsigned int threeshold, unsigned int afterTouchDelay) {
    selectChannel(mux, this->channel);
    unsigned long actualTime = millis();
    if (actualTime > this->hitTime + afterTouchDelay) { ///<<TODO hit
        unsigned int force = analogRead(mux->SIG); 
        if (force > threeshold) {
            this->preassure = map(force, 0, 1024, 0, 127);
            this->hitTime = actualTime;
           // digitalWrite(this->ledPinNumber, HIGH);   ///< TODO LCD?
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

unsigned int ePad::getPreassure(void) {
    return this->preassure;
}

void ePad::sendMidiNoteOn(void)
{
  midiEventPacket_t noteOn = {0x09, 0x90 | (uint8_t)this->channel, (uint8_t)this->code, (uint8_t)this->getPreassure()}; ///< NOTE: numer 0 tu = 1 w FLu
  MidiUSB.sendMIDI(noteOn);
  MidiUSB.flush();
}

void ePad::clearPad(void) {
    this->preassure = 0;
    this->hit = false;
}
