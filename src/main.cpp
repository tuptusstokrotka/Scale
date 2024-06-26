#include "MyWeight.h"
#include "MyButton.h"

MyWeight Waga;
MyButton Button;

void setup() {
  Serial.begin(9600);

  Button.Init();
  Waga.Init();
}

void loop() {
  switch(Button.Read()){
    default:
    case RELEASE:{
      break;
    }
    case PRESS:{
      Waga.Hold();    // Stop reading until pressed again
      break;
    }
    case HOLD:{
      Waga.Zero();    // Tare weight
      break;
    }
  }

  Waga.Measure();
}