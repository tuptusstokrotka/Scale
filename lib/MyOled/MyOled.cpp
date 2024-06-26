#include "MyOled.h"

MyOled::MyOled() : Adafruit_SH1107(OLED_WIDTH, OLED_HEIGHT, &Wire){}

MyOled::~MyOled(){}

void MyOled::Init(){
    // Inicjalizacja wyświetlacza OLED
    if(!begin(0x3C, true)) {
        Serial.println(F("SH1107 not found"));
        while(1);
    }
    setTextColor(SH110X_WHITE);

    // splash
    display();
    delay(200);
    clearDisplay();

    SmallText("CALIBRATE");
    display();
}

void MyOled::SmallText(String text, int y_pos){
    // SMALL TEXT
    setTextSize(2);
    // Print to OLED
    Text(text, y_pos);
}

void MyOled::BigText(String text, int y_pos){
    // DEFAULT SIZE
    setTextSize(3);
    // Print to OLED
    Text(text, y_pos);
}

void MyOled::Text(String text, int y_pos){
    // CENTER TEXT
    int16_t _x, _y;
    uint16_t textWidth, textHeight;
    getTextBounds(text, 0, 0, &_x, &_y, &textWidth, &textHeight);

    // SEND BUFFER STRING TO THE OLED
    int16_t x = (OLED_WIDTH  - textWidth)  / 2;
    int16_t y = (OLED_HEIGHT - textHeight) / 2;

    y_pos != 0 ? setCursor(x, y_pos) : setCursor(x, y);
    print(text);
}

void MyOled::Clear(){
    clearDisplay();
}
