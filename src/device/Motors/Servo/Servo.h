# pragma once
#include "hardwareDescription/hardwareDescription.h"

enum ServoType {
    CONTINUOUS,
    STANDARD,
};

struct SparkMax {
    descriptor hardwareDescriptor;
    ServoType type;
    void (*setControl)(SparkMax*, float control);
};

SparkMax initServo(uint8_t signalPin, ServoType type);

void setServoAngle(SparkMax* servo, float angle);

void setServoSpeed(SparkMax* servo, float speed);

void setControl(SparkMax* servo, float control);