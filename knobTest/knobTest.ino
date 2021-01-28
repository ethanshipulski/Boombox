// define how the pins are going to be used
#include <Wire.h>                                                                // Global for amplifier
#define MAX9744_I2CADDR 0x4B

const uint8_t PinSDA = 0;                                                        // I2C data
const uint8_t PinSCL = 2;                                                        // I2C clock
const uint8_t PinEncoderA = 3;                                                   // set this to the pin connected to encoder-A
const uint8_t PinEncoderB = 4;                                                   // set this to the pin connected to encoder-B

// define constants
const uint8_t KnobGain = 1;                                                      // increase this to make volume change quicker
uint8_t position = 0;// initial knob position (volume)
int8_t thevol = 0;
bool debouncea = true;
bool debounceb = true;
const uint32_t waitTime = 5;
uint32_t timea = 0;                                                              // Inital assignment of these 2 variables
uint32_t timeb = 0;

/**
 * Setup()
 * This runs once after reset.
 */
void setup() 
{ 
   pinMode(PinEncoderA, INPUT_PULLUP);                                                  // set the encoder pins as inputs
   pinMode(PinEncoderB, INPUT_PULLUP);                                                  // .
   
   attachInterrupt(digitalPinToInterrupt(PinEncoderA), IsrEncoderA, FALLING) ;    // connect encoder pins to interrupt service routines
   attachInterrupt(digitalPinToInterrupt(PinEncoderB), IsrEncoderB, FALLING) ;    //  .
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
      Serial.println(position/4);
    }  
    
    if (debouncea == false)                                                       // Debounce a wait waitime until 
    { 
        uint32_t timeElapsedA = millis();
        if ((timeElapsedA - timea) >= waitTime)
        {
             debouncea = true;
        }
    }
  
    if (debounceb == false)                                                       // end of subroutine, grab a timestamp
    { 
         uint32_t timeElapsedB = millis();
         if ((millis() - timeb) >= waitTime)
         {
              debounceb = true;
         }
    }   
}

/**
 * IsrEncoderA()
 * This gets called on every changing edge of encoder A
 */
void IsrEncoderA(void)
{ 
    if (debouncea == true)
    {
        if (digitalRead(PinEncoderB) == 0)                    // If pins are same, turning CCW
        {
             position = position - KnobGain;   // CCW motion of the knob
        }
        else
        {
           position = position + KnobGain;    // CW motion of the knob
        }
        debouncea = false;
        timea = millis();
    }
}

/**
 * IsrEncoderB()
 * This gets called on every changing edge of encoder B
 */
void IsrEncoderB(void)
{ 
    if (debounceb == true)
    {
        if (digitalRead(PinEncoderA) == 0)                 // If pins are same, turning CW
        {
            position = position + KnobGain;     // CW motion of the knob
        }
        else
         {
             position = position - KnobGain;    // CCW motion of the knob    
         }
         debounceb = false;
         timeb = millis();
    }
}
