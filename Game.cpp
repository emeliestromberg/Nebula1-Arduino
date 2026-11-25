#include "Game.h"
#include "Arduino.h"



Game::Game() 
:   controlDisplay(0x27),
    highScoreDisplay(0x3F),      // ändra vilken port den andra displayen går in på
    capSensor(4, 2),
    lightsensor(lightSensorPinA, lightSensorPinB, lightThreshold) {
}

void Game::begin() {

  // DEKLARERA PINS OCH OBJEKT
  pinMode(ledPin1, OUTPUT);
  pinMode(startButtonPin, INPUT_PULLUP);
  continousServo.attach(9);
  continousServo.write(servoIsStill);
  controlDisplay.initiateDisplay();
  Serial.begin(9600);
  hitCounter = 0;
}


void Game::update() {
  // SIFFROR VI MÄTER
  unsigned long currentTime = millis();
  long ufoTouchSensorValue = capSensor.capacitiveSensor(50);
  Serial.println(ufoTouchSensorValue);                //så vi ser vad touch-sensorvärdet är
  //Serial.println(analogRead(lightSensorPinA));                               //så vi ser vad ljus-ensorvärdet är
  //highScoreDisplay.printFastestTime(highScore);

  switch(gamestate){

    case WAIT_FOR_START_BUTTON:
      buttonState = digitalRead(startButtonPin);
      controlDisplay.pressButtonMessage();

      // Detect a new button press and reset game
      if (buttonState == LOW && lastButtonState == HIGH) {
        controlDisplay.resetTimer();
        hitCounter = 0;
        wasTouched = false;
        gamestate = CHECK_UFO_ON_PLATFORM;
        delay(50); // Simple button debounce
      }

      lastButtonState = buttonState;

    break;


    case CHECK_UFO_ON_PLATFORM:

      if(lightsensor.ufoIsOnPlatform()){
        gamestate = READY;
      }
      else{
        controlDisplay.ufoNotOnPlatformMessage();
        //delay(5000);                                      // test code, delete later
        //gamestate = READY;                                // test code, delete later
      }

      break;

    case READY:
    controlDisplay.liftUfoToStartMessage();
    //delay(2000);                                          // test code, delete later
   // gamestate = PLAYING;                                  // test code, delete later

      if(lightsensor.ufoHasLifted()){
        gamestate = PLAYING;
      }

      break;

    
    case PLAYING:
      controlDisplay.timer();

      if(lightsensor.isFinishReached()){
        gamestate = GAME_OVER;
        break;
      }

        // TOUCH SENSOR. CONTROLS LIGHTS, NR OF HITS
      if(currentTime - prevTimeLEDs > 200){                           // vi checkar för nudd varje 0,2 sekunder

        if(ufoTouchSensorValue < ufoTouchSensorThreshold){            // if nuddar gamewire , testar åt med < om det inte funkar
            digitalWrite(ledPin1, HIGH);

            if(wasTouched == false){                                   // if det är en ny touch
              hitCounter++;                                            // allt det här ska göras varje gång oavsett antal hits
              wasTouched = true;
              controlDisplay.printTimePenalty(hitCounter * 5);
            }
        } 
        
        else{                                                       // vi nuddar inte gamewire
            digitalWrite(ledPin1, LOW);
            wasTouched = false;
        } 
        prevTimeLEDs = currentTime;
      }

        // WHAT HAPPENS AT EVERY HIT
        if(hitCounter >= 4){
          continousServo.write(100);
          // light up led strip at random
          // play sounds at random
          gamestate = GAME_OVER;                          // test code, delete later
        
        }
        else if(hitCounter == 0){
          continousServo.write(92);
        }
        else if(hitCounter == 1){
          continousServo.write(94);
        }
        else if(hitCounter == 2){
          continousServo.write(96);
        }
        else if(hitCounter == 3){
          continousServo.write(98);
        } 

      break;

    case GAME_OVER:
      // STOP EVERYTHING
      controlDisplay.stopTimer();
      continousServo.write(servoIsStill);
      digitalWrite(ledPin1, LOW);

      // PRINT MESSAGES ON DISPLAY
      currentPlayerScore = controlDisplay.getPlayerTime() + hitCounter * 5;
      controlDisplay.PlayerScoreMessage(currentPlayerScore);
      delay(5000);

      if(currentPlayerScore < highScore){
        highScore = currentPlayerScore;
        controlDisplay.newHighScoreMessage();
        delay(5000);
      }
      else{
        controlDisplay.thanksForPlayingMessage();
        delay(5000);
      }

      // RESET GAME FOR NEW PLAYER
      gamestate = WAIT_FOR_START_BUTTON;

      break;


  }
}
