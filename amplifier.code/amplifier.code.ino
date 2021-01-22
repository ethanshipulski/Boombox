#include <Wire.h>

#define MAX9744_I2CADDR 0x4B

int8_t thevol = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("MAX9744 demo");
  Wire.begin();
  
  if (! setvolume(thevol)) {
    Serial.println("Failed to set volume, MAX9744 not found!");
    while (1);
  }
}


boolean setvolume(int8_t v) {
  // cant be higher than 63 or lower than 0
  if (v > 63) v = 63;
  if (v < 0) v = 0;
  
  Serial.print("Setting volume to ");
  Serial.println(v);
  Wire.beginTransmission(MAX9744_I2CADDR);
  Wire.write(v);
  if (Wire.endTransmission() == 0) 
    return true;
  else
    return false;
}

void loop() {
  if (! Serial.available()) return;
  

  char c = Serial.read();
  
  // increase
  if (c == '+') {
    thevol++;
  }
  // decrease
  else if (c == '-') {
    thevol--;
  }
  // ignore anything else
  else 
    return;
    
  if (thevol > 63) thevol = 63;
  if (thevol < 0) thevol = 0;

  setvolume(thevol);
}
