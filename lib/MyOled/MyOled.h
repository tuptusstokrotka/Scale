#ifndef MYOLED_H
#define MYOLED_H

#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// Change these if you're using a different OLED display
#define OLED_WIDTH 128
#define OLED_HEIGHT 128

#pragma once

class MyOled : public Adafruit_SH1107 {
private:

public:
    MyOled();
    ~MyOled();

    void Init();

    void SmallText(String text, int y_pos = 0);

    void BigText(String text, int y_pos = 0);

    void Text(String text, int y_pos = 0);

    void Clear();
};

#endif