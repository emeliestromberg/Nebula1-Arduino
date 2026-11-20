#include "Arduino.h"
#include "Display.h"


Display::Display(int pin, int adress)
    : buttonPin (pin), lcd(adress, 16, 2){
}


void Display::initiateDisplay(){
  lcd.init();
  lcd.backlight();

  pinMode(buttonPin, INPUT_PULLUP);
}

void Display::welcomeMessage() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press button");
  lcd.setCursor(0, 1);
  lcd.print("to start");
}

void Display::loopDisplay() {
  static unsigned long startTime = 0;
  static unsigned long elapsedTime = 0;

  static int timerMode = 0;

  static int buttonState;
  static int lastButtonState = HIGH;
  buttonState = digitalRead(buttonPin);

  // Detect a new button press
  if (buttonState == LOW && lastButtonState == HIGH) {

    timerMode++;

    if (timerMode == 1) {
      startTime = millis();
      lcd.clear();
    }

    else if (timerMode == 2) {
      timerMode = 0;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Press button");
      lcd.setCursor(0, 1);
      lcd.print("to start");
    }

    delay(50); // Simple button debounce
  }

  lastButtonState = buttonState;

  // Timer is running
  if (timerMode == 1) {

    elapsedTime = (millis() - startTime) / 1000;

    lcd.setCursor(0, 0);
    lcd.print("Time: ");

    lcd.setCursor(6, 0);
    lcd.print(elapsedTime);
    lcd.print("     ");
  }
}

void Display::showHighScore(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("HighScore");
  lcd.setCursor(0, 1);
  lcd.print("1 million bre");
}
