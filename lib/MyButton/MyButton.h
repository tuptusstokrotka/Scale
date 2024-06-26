#ifndef MYBUTTON_H
#define MYBUTTON_H
#pragma once

#include "Arduino.h"

#define BTN_S       9
#define BTN_GND     7
#define BTN_VCC     5

#define HOLD_MS     400
#define HOLD        2
#define PRESS       1
#define RELEASE     0

class MyButton{
private:
    bool last_State = LOW;               // Last Switch state

public:
    MyButton();
    ~MyButton();

    void Init();

    /**
     * @brief Check if button is pressed, holding or released
     * @return + HOLD (2)
     * @return + PRESS (1)
     * @return + RELEASE (0)
     */
    int Read();
};

#endif