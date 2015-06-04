#include <ArduinoJson.h>

#include <VirtualShield.h>
#include <Graphics.h>
#include <Colors.h>

#include "RGBGrid.h"

const int gridcolumns = 16;
const int gridrows = 12;

struct _Character {
    unsigned int offsetX, offsetY, width, height;
    bool dots[gridcolumns][gridrows];
};

VirtualShield shield;
Graphics screen = Graphics(shield);

RGBGrid strip = RGBGrid(gridcolumns, gridrows);

String hex = "0123456789ABCDEF";

void doChar(char* pack, unsigned int length, struct _Character *chr) {

    chr->offsetX = hex.indexOf(pack[1]);
    chr->offsetY = hex.indexOf(pack[2]);
    chr->width = hex.indexOf(pack[3]);
    chr->height = hex.indexOf(pack[4]);

    unsigned int wordIndex = 0;
    unsigned int row = 0;
    unsigned int value = 0;
    unsigned int index = 0;
    unsigned int column = 0;
    unsigned int xcolumn = 0;
    for (unsigned int i = 5; i < length; i++)
    {
        unsigned int bitValue = hex.indexOf(pack[i]);
        Serial.print("...");
        Serial.print(bitValue);
        row = 0;
        for (unsigned int xrow = 0; xrow<4; xrow++) {
            chr->dots[column][row] = (bitValue & 0x0001) == 0x0001;
            bitValue = bitValue >> 1;
            Serial.print(",");
            Serial.print(bitValue);
            if (++row >= gridrows) {
                ++column;
                break;
            }
        }
    }
}

void refresh(ShieldEvent* shieldEvent)
{
    //drawGrid();
    struct _Character chr;
    Serial.print("!");
    doChar("!0389081060C50340340C50060081", 29, &chr);
    
    for (unsigned int col = 0; col < chr.height; col++) {
      for (unsigned int row = 0; row < chr.width; row++) {
         unsigned int val = 0;
         if (chr.dots[col][row]) {
           val = 255;
         }
         strip.setPixel(col, row, ARGB(val,val,val)); 
      }
    }
/*
    for (int col=0; col<gridcolumns; col++) {
      for (int row=0;row<gridrows; row++) {
        strip.setPixel(col,row,ARGB(255,255,255));
        strip.ShiftAllPixels();
        delay(100);
      }
    }
*/    
    strip.ShiftAllPixels();
}

void setup()
{
    //shield.setOnRefresh(refresh);
    strip.begin();
    //shield.begin();
    refresh(0);
}


void loop()
{
    //shield.checkSensors();
}
