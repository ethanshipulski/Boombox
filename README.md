# Boombox
# This is where Ethan is going to keep his notes.

1.23:
Updated knob test code to include more inclusive logic in subroutines.
Added serial printing in subroutines to track position up or down
Wired board so encoder uses 3V VI2C off of trinket with pullup resistors
Ran code on trinket, serial monitor showed repeating pattern of messages, didn't respond to turning knob at all

I think I'm either doing too much in the subroutines, or comparing the A and B pins too quickly after one
has changed. Does the change happen instantly, or does the value take time to settle?
I also think using 3V off the trinket I2C voltage could be a problem

1.24:
Tried to change where to print and using falling mode on interrupt pin. Still erratic behavior. Doesn't 
change with the knob, only changes when I touch the wires