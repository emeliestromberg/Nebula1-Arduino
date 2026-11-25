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
  WAIT_FOR_START_BUTTON,
  CHECK_UFO_ON_PLATFORM,
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
int ufoTouchSensorThreshold = 20;
CapacitiveSensor capSensor;
int hitCounter;
bool wasTouched = false;
unsigned long prevTimeLEDs = millis();

// USED FOR MOTORS
Servo continousServo;
int servoIsStill = 86;

// USED FOR GAME CONTROL            //this needs implementing
int startButtonPin = 7;
int buttonState;
int lastButtonState = HIGH;
bool ufoInAir = false;
bool startButtonWasPressed = false;
const int lightSensorPinA = A0;
const int lightSensorPinB = A1;
const int lightThreshold = 800;               

// LIGHT SENSORS
LightSensor lightsensor;

// DISPLAY
Display controlDisplay;
Display highScoreDisplay;

// PLAYER SCORE¨
int currentPlayerScore;
int highScore = 10;

GameState gamestate = WAIT_FOR_START_BUTTON;



};

#endif
