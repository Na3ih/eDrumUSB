/**
 * TODO:
 */

#include <CD74HC4067.hpp>

const static unsigned int S0  = 10;
const static unsigned int S1  = 16;
const static unsigned int S2  = 14;
const static unsigned int S3  = A2;
const static unsigned int EN  = 15;
const static unsigned int SIG = A0;

Mux16 testMux;

void setup()
{
   pinoutSetup(&testMux);
   Serial.begin(115200);
}

void loop()
{
    int val;
    String line;
   
    for (byte i = 0; i < 16; i++) {
        val = readValue(&testMux, i);
        line = "Chan";
        line += i;
        line += " = ";
        line += val;
        Serial.println(line); 
    }

    delay(5000);
}