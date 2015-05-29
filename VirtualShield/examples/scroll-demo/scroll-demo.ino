#include <ArduinoJson.h>

#include <VirtualShield.h>
#include <Graphics.h>
#include <Colors.h>

#include "RGBGrid.h"

VirtualShield shield;
Graphics screen = Graphics(shield);

const int gridcolumns = 16;
const int gridrows = 12;

RGBGrid strip = RGBGrid(gridcolumns, gridrows);

String hex = "0123456789ABCDEF";

void doChar(char* pack, UINT length) {
    int offsetX = hex.indexOf(pack[2]);
    screen.printAt(3, offsetX);

    for (int i = 0; i < length; i++)
    {

    }
}

void refresh(ShieldEvent* shieldEvent)
{
    //drawGrid();
    doChar("!0389081060C50340340C50060081", 29);
}

void setup()
{
    shield.setOnRefresh(refresh);
    strip.begin();
    shield.begin();
}


void loop()
{
    shield.checkSensors();
}
