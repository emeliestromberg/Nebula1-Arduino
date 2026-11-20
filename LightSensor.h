#ifndef LightSensor_h
#define LightSensor_h
#include "Arduino.h"


class LightSensor{

  private:
    int sensorPinA;
    int sensorPinB;
    int lightThreshold;

    int startSensor;
    int finishSensor;

    unsigned long currentTime = millis();

  public:
    LightSensor(int pinA, int pinB, int limit);

    bool chooseStartSensor();
    
    bool ufoHasLifted();

    bool isFinishReached();

    int getStartSensor();

    int getFinishSensor();

};

#endif



