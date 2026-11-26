#include "Arduino.h"
#include "Display.h"


Display::Display(int adress)
    : lcd(adress, 16, 2){
}

  // FUNCTIONS

void Display::initiateDisplay(){
  lcd.init();
  lcd.backlight();
}

void Display::timer() {
  
  if (timerFinished) {
      return;
    }

  // Start the timer
  if (!timerRunning) {
    startTime = millis();
    lcd.clear();
    timerRunning = true;
    lcd.clear();
  }

  // Update timer
  if (timerRunning) {

    elapsedTime = (millis() - startTime) / 1000;

    lcd.setCursor(0, 0);
    lcd.print("Time: ");

    lcd.setCursor(6, 0);
    lcd.print(elapsedTime);
    lcd.print(" sec");
  }
}

  // STOP THE TIMER
void Display::stopTimer(){
  if (timerRunning && !timerFinished) {
    elapsedTime = (millis() - startTime) / 1000;
    playerTime = elapsedTime;

    timerRunning = false;
    timerFinished = true;
  }
}

unsigned long Display::getPlayerTime(){
  return playerTime;
}

void Display::resetTimer(){
  timerRunning = false;
  timerFinished = false;
  elapsedTime = 0;
  playerTime = 0;
}

void Display::printTimePenalty(int timePenalty){
  lcd.setCursor(0, 1);
  lcd.print("Penalty: ");
  lcd.setCursor(9, 1);
  lcd.print(timePenalty);
  lcd.setCursor(11, 1);
  lcd.print("sec");
}

void Display::printHighScore(int highScore){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Fastest time:");
  lcd.setCursor(0, 1);
  lcd.print(highScore);
  lcd.setCursor(4, 1);
  lcd.print(" sec");
}


  // MESSAGES

void Display::pressButtonMessage() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press button");
  lcd.setCursor(0, 1);
  lcd.print("to start");
}

void Display::ufoNotOnPlatformMessage(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Please place UFO");
  lcd.setCursor(0, 1);
  lcd.print("on a platform :)");
}

void Display::liftUfoToStartMessage(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Lift UFO");
  lcd.setCursor(0, 1);
  lcd.print("to start");
}

void Display::PlayerScoreMessage(int currentPlayerScore){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Your time: ");
  lcd.setCursor(0, 1);
  lcd.print(currentPlayerScore);
  lcd.setCursor(4, 1);
  lcd.print("sec");
}

void Display::thanksForPlayingMessage(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Thank you for");
  lcd.setCursor(0, 1);
  lcd.print("playing!<3 :)");
}

void Display::newHighScoreMessage(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("You set a new");
  lcd.setCursor(0, 1);
  lcd.print("high score!<3 :)");
}
