#pragma once
#include "hardwareDescription/hardwareDescription.h"
#include "device/encoderType.h"

struct DCMotor {
    descriptor hardwareDescriptor;
    String name;
    void* encoder; // Pointer to encoder structure (if applicable)
    encoderType encoderType;
};

DCMotor initDCMotor(String name, uint8_t pin, encoderType encType = NO_ENCODER);