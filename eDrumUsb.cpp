#include "eDrumUsb.hpp"

///< TODO pinout.h
unsigned int muxEnablePin = A3;
unsigned int muxSigPin = A0;
unsigned int muxS0Pin = 10;
unsigned int muxS1Pin = 16;
unsigned int muxS2Pin = 14;
unsigned int muxS3Pin = A2;
const unsigned int DEBUG = 6;
unsigned int NOTE = 64;


eDrum::eDrum()
{
  this->mux16.EN = muxEnablePin; 
  this->mux16.SIG = muxSigPin;
  this->mux16.bitS[0] = muxS0Pin;
  this->mux16.bitS[1] = muxS1Pin;
  this->mux16.bitS[2] = muxS2Pin;
  this->mux16.bitS[3] = muxS3Pin;

  pinoutSetup(&(this->mux16));
  enableChip(&(this->mux16));
  this->numberOfPads = setupPads(&mux16);

  this->threeshold = 250;
  this->afterTouchDelay = 50;
}

/**
 * 
 */
static size_t checkNumberOfConnectedPads(Mux16 * mux)
{           
  unsigned int i;                                                     String log = "Pads connected to channel: ";
  size_t numberOfPads = 0;

  for (i = 0; i < DEBUG; i++) {    ///< TODO: 16
    selectChannel(mux, i);
    if (digitalRead(mux->SIG)) {                                      log += i;
      numberOfPads++;                                                 log += ',';                           
    }
  }                                                                   Serial.println(log); 
  return numberOfPads;                                                log = "Connected pads: " + numberOfPads; Serial.println(log);                                  
}

bool eDrum::setupPads(Mux16 * mux)
{ 
  this->numberOfPads = DEBUG;     ////TODO:<< !!!checkNumberOfConnectedPads(mux);
  this->drums = new ePad[this->numberOfPads];
                                                                       String log = "Pads setup: "; 
  if (this->drums == nullptr) {                                        log += " Problem with memory allocation... :/";
    return false;
  } else {                                                             log += "OK :)";    
    unsigned int i; 
    for (i = 0; i < this->numberOfPads; i++) {   ///<<< TODO DEBUG
      this->drums[i].setupPad(NOTE, i); 
    }
  }                                                                    Serial.print(log);
  return true;
}

void eDrum::pollingAllPads(void)
{
  unsigned int i;
  ePad * pad;
  for (i = 0; i < this->numberOfPads; i++) {
    pad = &drums[i];
    if (pad->wasHit(&mux16, threeshold, afterTouchDelay)) {           
      pad->sendMidiNoteOn();
    }
  }
}

eDrum::~eDrum()  ///< TODO: disable Mux, LCD Bye
{
  disableChip(&mux16);
}
