#include <M5Stack.h>
#include "HX711.h"

// HX711
HX711 myScale;
#define LOADCELL_DOUT_PIN 16    // was 2
#define LOADCELL_SCK_PIN  17    // was 3

long  adc_reading = 0;      // ADC reading
float converted   = 0;      // ADC converted by scale factor
long  offset      = 0;      // Offset when tare
bool  refresh     = false;  // True if new data to showcase
bool  hold        = false;  // True if hold the weight measurement

uint8_t calib_step = 10;
float calib_weight = 5.6;


void Center(String source, int y_offset = -1){
    int str_len = source.length();

    int font_X = M5.Lcd.textsize * 6;
    int font_Y = M5.Lcd.textsize * 8;

    int _x = (M5.Lcd.width()  - str_len * font_X)/2;
    int _y = (M5.Lcd.height() - font_Y)/2;

    if(y_offset != -1)
        M5.Lcd.setCursor(_x, y_offset);
    else
        M5.Lcd.setCursor(_x, _y);
}

void Calibrate(){
    static long zero;
    static long five;

    switch (calib_step){
        case 0:{
            // get the zero
            zero = myScale.read_average(5);
            calib_step += 5;  // goto 5zł
            break;
        }
        case 5:{
            // get the 5zł
            five = myScale.read_average(5);
            calib_step += 5;  // finish
            break;
        }
        default:
            calib_step = 0;
            break;
    }


    if(calib_step > 5){
        long dx = five - zero;
        float scale = dx / calib_weight;    // weight of the 5zł

        myScale.set_scale(scale);
        offset = zero;
    }
}

void Zero(){
    offset = myScale.get_value(1);
}

void Measure(){
    /* Get fresh reading */
    adc_reading = myScale.get_value(2);

    /* PARSING, CONVERTING, OFFSETING */
    adc_reading = constrain(adc_reading - offset, -1000000, 1200000); // This should limit in range [-1250, 1500]g

    /* CHECK IF VALUE HAS CHANGED */
    if(converted != adc_reading / myScale.get_scale()){
        converted = adc_reading / myScale.get_scale();          // This should be grams or whatever
        refresh = true;
    }
}

void ButtonUpdate(){
    //Buttons
    if (M5.BtnA.wasPressed()) {
        Zero();
    }

    if(M5.BtnB.wasPressed() && M5.BtnC.wasPressed()){
        Calibrate();
    }
    if (M5.BtnB.wasPressed()) {
        calib_weight -= 0.1;
        refresh = true;
    }
    else if (M5.BtnB.pressedFor(700)) {
        calib_weight -= 5;
        refresh = true;
    }

    if (M5.BtnC.wasPressed()) {
        calib_weight += 0.1;
        refresh = true;
    }
    else if (M5.BtnC.pressedFor(700)) {
        calib_weight += 5;
        refresh = true;
    }
}

void setup() {
    Serial.begin(115200);

    M5.begin();        // Init M5Core.
    M5.Power.begin();  // Init Power module.
    delay(500);

    M5.Lcd.setTextColor(WHITE);

    myScale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    myScale.set_scale(800);
    offset = myScale.read();
}

void loop() {
    M5.update();

    Measure();

    ButtonUpdate();

    //Screen
    if(refresh){
        refresh = false;

        M5.Lcd.fillScreen(TFT_BLACK);

        M5.Lcd.setTextSize(7);
        String grams = String(converted);
        grams[grams.length()-1] = 'g';
        Center(grams);
        M5.Lcd.print(grams);


        M5.Lcd.setTextSize(2);
        switch (calib_step){
            case 0:{
                // get the zero
                Center("Calibrate: 0g", 10);
                M5.Lcd.print("Calibrate: 0g");
                break;
            }
            case 5:{
                // get the 5zł
                String text = "Calibrate:" + String(calib_weight);
                text[text.length()-1] = 'g';
                Center(text, 10);
                M5.Lcd.print(text);
                break;
            }
        }

        M5.Lcd.setCursor(43,190);
        M5.Lcd.print("ZERO");

        M5.Lcd.setCursor(155,190);
        M5.Lcd.print("CALIBRATE");

        M5.Lcd.setCursor(157,220);
        M5.Lcd.print("-");
        M5.Lcd.setCursor(250,220);
        M5.Lcd.print("+");
    }
}