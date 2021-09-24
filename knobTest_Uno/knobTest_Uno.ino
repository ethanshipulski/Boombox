// define how the pins are going to be used
#include <Wire.h>                                                                // Global for amplifier
#define MAX9744_I2CADDR 0x4B

// Forward declarations
void IsrEncoderA(void);
void IsrEncoderB(void);

const uint8_t PinSDA = A4;                                                        // I2C data
const uint8_t PinSCL = A5;                                                        // I2C clock
const uint8_t PinEncoderA = 2;                                                   // set this to the pin connected to encoder-A
const uint8_t PinEncoderB = 3;                                                   // set this to the pin connected to encoder-B

// define constants
const uint8_t KnobGain = 4;                                                      // increase this to make volume change quicker
uint8_t position = 0;                                                            // initial knob position (volume)
bool debounceb = true;
bool debouncea = true;
const uint32_t waitTime = 2;
uint32_t timea = 0;                                                              // Inital assignment of these 2 variables
uint32_t timeb = 0;
static uint8_t lastPosition = 0;

/**
 * Setup()
 * This runs once after reset.
 */
void setup() 
{
   Serial.begin(9600);
   Serial.println("READY");
   Wire.begin();

   pinMode(PinEncoderA, INPUT_PULLUP);                                            // set the encoder pins as inputs
   pinMode(PinEncoderB, INPUT_PULLUP);                                            // .
                                                                                 
                                                                                 // connect encoder pins to interrupt service routines
   attachInterrupt(digitalPinToInterrupt(PinEncoderB), IsrEncoderB, RISING) ;
   attachInterrupt(digitalPinToInterrupt(PinEncoderA), IsrEncoderA, RISING) ;    //  .

  
}


/**
 * loop()_
 * This gets called over and over by the arduino library
 */
void loop() 
{

   if (lastPosition != position)
   {                                                                      // put the i2c code here to set the volume to "position"
        Wire.beginTransmission(MAX9744_I2CADDR);
        Wire.write(position/4);
        Wire.endTransmission();
      
      lastPosition = position;                                                   // only write to i2c if the volume changed.   
      Serial.println(position/4);


   }
    if (debouncea == false)                                                       // end of subroutine, grab a timestamp
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
         if ((timeElapsedB - timeb) >= waitTime)
         {
              debounceb = true;
         }
    }   
    
}

/**
 * IsrEncoderB()
 * This gets called on every RISING edge of encoder B
 */
 void IsrEncoderA(void)
{
    if (debouncea == true)
    {
        if (digitalRead(PinEncoderB) == 0)                 // If B is low, turning CW
        {
            if (position <= 255)                           // Only increment if volume is under 255
              {
            position = position + KnobGain;                // CW motion of the knob
              }
        }
        else
         {
            if (position >= 0)                              // Only decrement if the volume is over 0
              {
             position = position - KnobGain;                // CCW motion of the knob    
              }
         }
         debouncea = false;
         timeb = millis();
    }
}

    
void IsrEncoderB(void)
{
    if (debounceb == true)
    {
        if (digitalRead(PinEncoderA) == 1)                 // If A is high, turning CW
        {
            if (position <= 255)                           // Only increment if volume is under 255
              {
            position = position + KnobGain;                // CW motion of the knob
              }
        }
        else
         {
            if (position >= 0)                              // Only decrement if the volume is over 0
              {
             position = position - KnobGain;                // CCW motion of the knob    
              }
         }
         debounceb = false;
         timeb = millis();
    }
}
