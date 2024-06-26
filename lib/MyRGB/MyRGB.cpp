#include "MyRGB.h"

MyRGB::MyRGB() : Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800){}

MyRGB::~MyRGB(){}

void MyRGB::Init(){
  begin();
  clear();
  setBrightness(100);
  show();

  for(int i = 0; i< NUMPIXELS; i++){
    setPixelColor(i, Color(255, 255, 255));
    show();
    delay(50);
  }
}

void MyRGB::Range(float grams, bool hold){
  uint32_t color;
  static uint8_t range=0;
  clear();

  /* Set color */
  if(hold == true)
    color = Color(255, 100, 0);
  else if(grams < 0)
    color = Color(255, 0, 0);
  else
    color = Color(0, 255, 0);

  /* Set pixel num and direction*/
  if(grams < 0){
    range = (uint8_t)map(grams, 0,-200, 0,NUMPIXELS);
    for(int i = 0; i< range; i++)
      setPixelColor(NUMPIXELS-i, color);
  }
  else{
    range = (uint8_t)map(grams, 0, 200, 0,NUMPIXELS);
    for(int i = 0; i< range; i++)
      setPixelColor(i, color);
  }

  show();
}