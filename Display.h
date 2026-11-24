#ifndef Display_h
#define Display_h
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>


class Display {

  private:
    LiquidCrystal_I2C lcd;
    
    unsigned long startTime = 0;
    unsigned long elapsedTime = 0;
    long playerTime = 0;

    bool timerRunning = false;
    bool timerFinished = false;


  public:

    // CONSTRUCTOR FOR CREATING DISPLAY OBJECT
    Display(int adress);

    // FUNCTIONS
    void timer();
    
    void stopTimer();

    void initiateDisplay();

    unsigned long getPlayerTime();

    void resetTimer();

    void printTimePenalty(int timePenalty);

    void printHighScore(int highScore);


    // MESSAGES
    void pressButtonMessage();

    void ufoNotOnPlatformMessage();

    void liftUfoToStartMessage();

    void PlayerScoreMessage(int currentPlayerScore);

    void newHighScoreMessage();

    void thanksForPlayingMessage();
};

#endif
