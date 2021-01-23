// define how the pins are going to be used
const uint8_t PinSDA = 0;                                                       // I2C data
const uint8_t PinSCL = 2;                                                       // I2C clock
const uint8_t PinEncoderA = 1;                                                   // set this to the pin connected to encoder-A
const uint8_t PinEncoderB = 3;                                                   // set this to the pin connected to encoder-B

// define constants
const uint8_t KnobGain = 1;                                                      // increase this to make volume chsnge quicker
uint8_t position = 0;                                                            // initial knob position (volume)

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
 * This gets called over and over by the arduino librsry
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
 * This gets called on every chsnging edge of encoder A
 */
void IsrEncoderA(void)
{
   if (digitalRead(PinEncoderB) == 0)
   {
      position = position - KnobGain;     // CCW motion of the knob
   }
   else
   {
       position = position + KnobGain;    // CW motion of the knob
   }
}

/**
 * IsrEncoderB()
 * This gets called on every chsnging edge of encoder B
 */
void IsrEncoderB(void)
{
     if (digitalRead(PinEncoderA) == 0)
   {
      position = position - KnobGain;     // CCW motion of the knob
   }
   else
   {
       position = position + KnobGain;    // CW motion of the knob
   }
}
