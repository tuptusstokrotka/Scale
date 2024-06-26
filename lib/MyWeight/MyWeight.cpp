#include "MyWeight.h"

MyWeight::MyWeight() {}

MyWeight::~MyWeight(){}

void MyWeight::Init(){
    // Out off GND pins, just ignore or use GND
    pinMode(17, OUTPUT);
    digitalWrite(17, LOW );
    // Out off VCC pins, just ignore or use VCC
    pinMode(11, OUTPUT);
    digitalWrite(11, HIGH);

    // OLED init
    myOled.Init();

    // RGB bootup animation
    myLED.Init();

    // Scale begin
    myScale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    // Scale calibrate
    Calibrate();

}

void MyWeight::Calibrate(){
    // dummy hardcode test value
    myScale.set_scale(0.802);

    // Set offset on init
    offset = myScale.get_value(5);
}

void MyWeight::Measure(){
    /* NOT HOLDING LAST VALUE */
    if(!hold){
        /* Get fresh reading */
        adc_reading = myScale.get_value(2);

        /* PARSING, CONVERTING, OFFSETING */
        adc_reading = constrain(adc_reading - offset, -10000000, 1241214); // This should limit in range [-1200, 1500]g

        /* CHECK IF VALUE HAS CHANGED */
        if(converted != adc_reading / myScale.get_scale()){
            converted = adc_reading / myScale.get_scale();          // This should be grams or whatever
            refresh = true;
        }
    }

    /* PRESENT CHANGES ON DISPLAY */
    Showcase();
}

void MyWeight::Zero(){
    offset = myScale.get_value(1);
}

void MyWeight::Hold(){
    hold = !hold;
    refresh = true;    // Force display udpate
}

void MyWeight::Showcase(){
    /* NOTHING TO UPDATE */
    if(!refresh)
        return;

    /* CLEAR */
    myOled.clearDisplay();

    /* HOLD */
    if(hold)
        myOled.SmallText("HOLD",4);

    /* SET STRING */
    String temp="";
    if(converted/1000 > 1000){
        temp = String(converted/1000000);
        temp+= "Kg";
    }
    else{
        temp = String(converted/1000);
        temp.remove(temp.length()-3);
        temp+= "g";
    }

    /* UPDATE OLED */
    myOled.BigText(temp);
    myOled.display();

    /* RGB STRIP */
    myLED.Range(converted/1000, hold);
}