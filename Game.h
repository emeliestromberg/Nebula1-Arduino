#ifndef Game_h
#define Game_h
#include <Arduino.h>
#include <CapacitiveSensor.h>
#include <Servo.h>
#include "LightSensor.h"
#include "Display.h"

class Game {

public:

enum GameState{
  WAITING,
  READY,
  PLAYING,
  GAME_OVER
};

  // Constructor
  Game();

  // Main functions
  void begin();
  void update();

private:

// USED FOR LIGHTS
const int ledPin1 = 12;


// USED FOR TOUCH SENSOR
int threshold1 = 100;
CapacitiveSensor capSensor;
int hitCounter = -1;
bool wasTouched = false;
unsigned long prevTimeLEDs = millis();

// USED FOR MOTORS
Servo continousServo;

// USED FOR TIMER
unsigned long startTime;
int finalTime;
int totalPenatlyTime = 0;
int wipTimerButtonPin = 7;

// USED FOR GAME CONTROL            //this needs implementing
bool ufoInAir = false;
//const int startButtonPin = 7;
bool startButtonWasPressed = false;
const int lightSensorPinA = A0;
const int lightSensorPinB = A1;
const int lightThreshold = 1000;

// LIGHT SENSORS
LightSensor lightsensor;

// DISPLAY
Display controlDisplay;
Display highScoreDisplay;

GameState gamestate = WAITING;

// SCORE
const int currentPlayerScore;



};

#endif
