#include "Game.h"
#include "Arduino.h"



Game::Game() 
:   controlDisplay(wipTimerButtonPin, 0x27),
    highScoreDisplay(wipTimerButtonPin, 0x3F),      // ändra vilken port den andra displayen går in på
    capSensor(4, 2),
    lightsensor(lightSensorPinA, lightSensorPinB, lightThreshold) {
}

void Game::begin() {

  // DEKLARERA PINS OCH OBJEKT
  pinMode(ledPin1, OUTPUT);
  //pinMode(startButtonPin, INPUT);
  continousServo.attach(9);
  Serial.begin(9600);
  controlDisplay.initiateDisplay();

  // TIMER
  startTime = millis();

}


void Game::update() {
  // SIFFROR VI MÄTER
  unsigned long currentTime = millis();
  long sensorValue = capSensor.capacitiveSensor(30);
  //highScoreDisplay.showHighScore();

  switch(gamestate){

    case WAITING:
      controlDisplay.welcomeMessage();
      //gamestate = READY;

    if(lightsensor.chooseStartSensor()){
      Serial.println("Lift UFO to start!");
      gamestate = READY;
    }
      break;

    case READY:
      //if startsensor threshold
      gamestate = PLAYING;
      break;

    
    case PLAYING:
      controlDisplay.timerDisplay();
      hitCounter = 0;

        // TOUCH SENSOR. CONTROLS LIGHTS, NR OF HITS
      if(currentTime - prevTimeLEDs > 300){           // vi checkar för nudd varje 0,3 sekunder

        if(sensorValue > threshold1){                 // if nuddar gamewire
            digitalWrite(ledPin1, HIGH);

            if(wasTouched == false){                  // if det är en ny touch
              hitCounter++;                           // allt det här ska göras varje gång oavsett antal hits
              totalPenatlyTime += 5;
              wasTouched = true;
              Serial.print(" Number of hits: ");
              Serial.println(hitCounter);
              Serial.print(" Time penalty: ");
              Serial.print(totalPenatlyTime);
              Serial.println(" sec");
            }
        } 
        
        else{                                   // vi nuddar inte gamewire
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

      break;


  }
}
