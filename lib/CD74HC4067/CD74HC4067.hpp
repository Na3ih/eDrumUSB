/**
 *  The file provides the functions needed for handling with a 16-channel analog multiplexer (CD74HC4067 chip).
 * 
 *  Chip pinout:
 *      - SIG : Multiplekser output.
 *              Analog value measured at specify channel.
 *  
 *      - EN  : Enable pin. 
 *              State LOW:  chip enable, 
 *                    HIGH: chip disable.
 *  
 *      - S0-4: Channel select.
 *              Digital inputs (S0 - Least Significant Bit).
 */

#pragma once
#include <stdint.h>

/**
 * Multiplekser structure.
 * Contain board pinout used to handle with the module.
 * @warning For chip pinout look the file header. 
 */
struct Mux16
{
  unsigned int bitS[4]; 
  unsigned int EN;
  unsigned int SIG;
};

/**
 * Setup the specify pins.
 * @warning This function should be called into main setup() function.
 * 
 * @param mux Multiplekser structure.
 */
void pinoutSetup(struct Mux16 * mux);

/**
 * Chip enable.
 * 
 * @param mux Multiplekser structure.
 */
void enableChip(struct Mux16 * mux);

/**
 * Chip disable.
 * 
 * @param mux Multiplekser structure.
 */
void disableChip(struct Mux16 * mux);

/**
 * Channel selection.
 * 
 * @param mux Multiplekser structure.
 * @param channel Channel number.
 */
void selectChannel(struct Mux16 * mux, uint8_t channel);

/**
 * Reading value from specify channel;
 * 
 * @param mux Multiplekser structure.
 * @param channel Channel number.
 * @return Analog value measured at specify channel.
 */ 
unsigned int readValue(struct Mux16 * mux, uint8_t channel);
