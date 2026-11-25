#include "LightSensor.h"
#include "Arduino.h"

LightSensor::LightSensor(int pinA, int pinB, int limit){
  sensorPinA = pinA;
  sensorPinB = pinB;
  lightThreshold = limit;

  startSensor = -1;
  finishSensor = -1;
}

bool LightSensor::ufoIsOnPlatform() {

  // Läs av båda ljussensorerna
  int lightA = analogRead(sensorPinA);
  int lightB = analogRead(sensorPinB);


  // UFO:t står på platta A
  if (lightA < lightThreshold &&
      lightB >= lightThreshold) {

    startSensor = sensorPinA;
    finishSensor = sensorPinB;

    // Spelet är redo att börja
    return true;
  }


  // UFO:t står på platta B
  else if (lightB < lightThreshold &&
           lightA >= lightThreshold) {

    startSensor = sensorPinB;
    finishSensor = sensorPinA;

    // Spelet är redo att börja
    return true;
  }


  // Ingen tydlig startposition hittades
  else {
    return false;
  }
}


//bool LightSensor::ufoHasLifted() {
  
//  if(startSensor > lightThreshold){
//    return true;                              //gamla ufoHasLifted-funktionen som claude tyckte var fel
//  }
//  return false;
//}

bool LightSensor::ufoHasLifted() {
  if(startSensor == -1){
    return false;                                // ingen startplattform vald än
  }
  return analogRead(startSensor) >= lightThreshold;
}

bool LightSensor::isFinishReached() {

  if(finishSensor == -1){
    return false;
  }

    int finishValue = analogRead(finishSensor);

    return finishValue < lightThreshold;
}

int LightSensor::getStartSensor() {
    return startSensor;
}


int LightSensor::getFinishSensor() {
    return finishSensor;
}
