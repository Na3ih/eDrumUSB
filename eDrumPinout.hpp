#pragma once

/**
 * eDrum multiplekser pinout.
 */
const unsigned int muxEnablePin = A3;
const unsigned int muxSigPin = A0;
const unsigned int muxS0Pin = 10;
const unsigned int muxS1Pin = 16;
const unsigned int muxS2Pin = 14;
const unsigned int muxS3Pin = A2;

/**
 * Default values used in project.
 */
const unsigned int NOTE = 64; ///<  MIDI note number.
const unsigned int AFTER_TOUCH_DELAY = 50; ///< Minimal delay betwen impacts. 
const unsigned int THREESHOLD = 250; ///< Impact threeshold.

const unsigned int DEBUG = 6; ///< TODO: usunac DEBUG
