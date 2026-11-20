#ifndef Display_h
#define Display_h
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>


class Display {

  private:
    int buttonPin;
    LiquidCrystal_I2C lcd;

  public:

    Display(int buttonPin, int adress);

    void initiateDisplay();

    void welcomeMessage();

    void loopDisplay();

    void showHighScore();


};

#endif
