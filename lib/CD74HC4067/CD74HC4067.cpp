#include <CD74HC4067.hpp>
#include <Arduino.h>

/**
 * Setup the specify pins.
 * @warning This function should be called into main setup() function.
 * 
 * @param mux Multiplekser structure.
 */
void pinoutSetup(struct Mux16 * mux)
{
    pinMode(mux->bitS[0], OUTPUT);
    pinMode(mux->bitS[1], OUTPUT);
    pinMode(mux->bitS[2], OUTPUT);
    pinMode(mux->bitS[3], OUTPUT);
    pinMode(mux->EN, OUTPUT);
    pinMode(mux->SIG, INPUT);
}

/**
 * Chip enable.
 * 
 * @param mux Multiplekser structure.
 */
void enableChip(struct Mux16 * mux)
{
    digitalWrite(mux->EN, LOW);
}

/**
 * Chip disable.
 * 
 * @param mux Multiplekser structure.
 */
void disableChip(struct Mux16 * mux)
{
    digitalWrite(mux->EN, HIGH);
}

/**
 * Channel selection.
 * 
 * @param mux Multiplekser structure.
 * @param channel Channel number.
 */
void selectChannel(struct Mux16 * mux, uint8_t channel)
{
	byte j = 0;
    for (byte i = 1; i <= 8; i *= 2) {
    if (channel & i) {
		//Serial.print(j++); Serial.println(" = 1");
      digitalWrite(mux->bitS[j++], HIGH);  
    } else {
		//Serial.print(j++); Serial.println(" = 0");
      digitalWrite(mux->bitS[j++], LOW);
    }
   }
}

/**
 * Reading value from specify channel;
 * 
 * @param mux Multiplekser structure.
 * @param channel Channel number.
 * @return Analog value measured at specify channel.
 */ 
unsigned int readValue(struct Mux16 * mux, uint8_t channel)
{
    selectChannel(mux, channel);
    delay(5);
    return analogRead(mux->SIG);
}