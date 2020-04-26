#include "eDrumUsb.hpp"
#include "eDrumPinout.hpp"

/**
 * Default constructor.
 */
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
  setupPads(&(this->mux16));

  this->threeshold = THREESHOLD;
  this->afterTouchDelay = AFTER_TOUCH_DELAY;
}

/**
 * Count connected ePads.
 * 
 * @return Number of connected ePads.
 */
static size_t checkNumberOfConnectedPads(Mux16 * mux)
{           
  unsigned int i;                                                    // String log = "Pads connected to channel: ";
  size_t numberOfPads = 0;

  for (i = 0; i < 16; i++) {
    selectChannel(mux, i);
    if (digitalRead(mux->SIG)) {                                     // log += i;
      numberOfPads++;                                                // log += ',';                           
    }
  }                                                                  // Serial.println(log); 
  return numberOfPads;                                               // log = "Connected pads: " + numberOfPads; Serial.println(log);                                  
}

/**
 * Set initial values to connected ePads.
 * 
 * @param mux Pointer to multiplekser structure.
 */
bool eDrum::setupPads(Mux16 * mux)
{ 
  this->numberOfPads = DEBUG;     ////TODO:<< !!!checkNumberOfConnectedPads(mux);
  this->drums = new ePad[this->numberOfPads];
                                                                      // String log = "Pads setup: "; 
  if (this->drums == nullptr) {                                       // log += " Problem with memory allocation... :/";
    return false;
  } else {                                                            // log += "OK :)";    
    unsigned int i; 
    for (i = 0; i < this->numberOfPads; i++) {
      this->drums[i].setupPad(NOTE, i); 
    }
  }                                                                   // Serial.print(log);
  return true;
}

/**
 * Checking if any drum pad was hit.
 * If pad was hit MIDI 'Note On' command is send. 
 */
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

/**
 * Default destruktor.
 */
eDrum::~eDrum()  
{
  /* TODO: disable Mux, LCD Bye */
  disableChip(&mux16);
}
