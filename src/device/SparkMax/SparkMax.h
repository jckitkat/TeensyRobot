# pragma once
#include "device/encoderType.h"
#include "hardwareDescription/hardwareDescription.h"

struct SparkMax {
    descriptor hardwareDescriptor;
    void* encoder; // Pointer to encoder structure (if applicable)
    encoderType encType;
    void (*setControl)(SparkMax*, float control);
};

SparkMax initServo(uint8_t signalPin, void* encoder, encoderType encType);

void setControl(SparkMax* sparkMax, float control);
