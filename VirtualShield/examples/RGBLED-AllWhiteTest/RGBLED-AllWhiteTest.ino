

#include "RGBStrip.h"

const int gridcolumns = 8;
const int gridrows = 6;

RGBStrip strip = RGBStrip();

void setup()
{
  strip.begin();
  strip.setAll(127,127,127);
  
}

void loop()
{
}		 
