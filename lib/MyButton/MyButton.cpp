#include "MyButton.h"

MyButton::MyButton(){}

MyButton::~MyButton(){}

void MyButton::Init(){
    pinMode(BTN_S  , INPUT);

    // Out off GND pins, just ignore or use GND
    pinMode(BTN_GND, OUTPUT);
    digitalWrite(BTN_GND, LOW );

    // Out off VCC pins, just ignore or use VCC
    pinMode(BTN_VCC, OUTPUT);
    digitalWrite(BTN_VCC, HIGH);
}

int MyButton::Read(){
    /* BUTTON RELEASED */
    if(digitalRead(BTN_S) == LOW){                     // BUTTON RELEASED
        last_State = LOW;                              // UPDATE LASTSTATE
        return RELEASE;
    }

    /* BUTTON PRESSED && LASTSTATE PRESSED */
    if(last_State == HIGH){                              // BUTTON HAS NOT BEEN RELEASED YET
        return -1;                                      // SKIP ITERATION
    }

    /* BUTTON PRESSED && LASTSTATE RELEASED */
    last_State = HIGH;                                   // BUTTON JUST PRESSED AND HAS BEEN RELEASED

    /* BUTTON HOLD */
    unsigned long holding_Time = millis();              // COUNT HOLDING TIME
    while(digitalRead(BTN_S) != LOW){                  // WAIT UNTIL RELEASED
        if(millis() - holding_Time > HOLD_MS)           // BREAK AFTER 400ms
            return HOLD;                                // HOLDING A BUTTON C:
    }
    /* BUTTON PRESS */
    return PRESS;                                       // JUST A PRESS :C
}
