// define how the pins are going to be used
#include <Wire.h>                                                               // Global for amplifier
#define MAX9744_I2CADDR 0x4B

const uint8_t PinSDA = 0;                                                        // I2C data
const uint8_t PinSCL = 2;                                                        // I2C clock
const uint8_t PinEncoderA = 3;                                                   // set this to the pin connected to encoder-A
const uint8_t PinEncoderB = 4;                                                   // set this to the pin connected to encoder-B

// define constants
const uint8_t KnobGain = 1;                                                      // increase this to make volume change quicker
uint8_t position = 0;// initial knob position (volume)
int8_t thevol = 0;

/**
 * Setup()
 * This runs once after reset.
 */
void setup() 
{ 
   pinMode(PinEncoderA, INPUT);                                                  // set the encoder pins as inputs
   pinMode(PinEncoderB, INPUT);                                                  // .
   
   attachInterrupt(digitalPinToInterrupt(PinEncoderA), IsrEncoderA, CHANGE) ;    // connect encoder pins to interrupt service routines
   attachInterrupt(digitalPinToInterrupt(PinEncoderB), IsrEncoderB, CHANGE) ;    //  .
}


/**
 * loop()_
 * This gets called over and over by the arduino library
 */
void loop() 
{
   static uint8_t lastPosition = 0;
   if (lastPosition != position)
   {
      // put the i2c code here to set the volume to "position"
      lastPosition = position;                                                   // only write to i2c if the volume changed.   
   }
}

/**
 * IsrEncoderA()
 * This gets called on every changing edge of encoder A
 */
void IsrEncoderA(void)
{
   if (digitalRead(PinEncoderB) == digitalRead(PinEncoderA))                    // If pins are same, turning CCW
   {
      position = position - KnobGain;   // CCW motion of the knob
      Serial.println("down A");
   }
   else
   {
       position = position + KnobGain;    // CW motion of the knob
       Serial.println("up A"); 
   }
}

/**
 * IsrEncoderB()
 * This gets called on every changing edge of encoder B
 */
void IsrEncoderB(void)
{
     if (digitalRead(PinEncoderA) == digitalRead(PinEncoderB))                 // If pins are same, turning CW
   {
      position = position + KnobGain;     // CW motion of the knob
      Serial.println("up B");
   }
   else
   {
       position = position - KnobGain;    // CCW motion of the knob
       Serial.println("down B");
   }
}
