#ifndef MYRGB_H
#define MYRGB_H

#pragma once

#include "Adafruit_NeoPixel.h"

#define PIN        3
#define NUMPIXELS 16

class MyRGB : public Adafruit_NeoPixel{
private:
public:
    MyRGB();
    ~MyRGB();

    void Init();

    void Range(float grams, bool hold);
};

#endif