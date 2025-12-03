#pragma once
#include "hardwareDescription/hardwareDescription.h"
#include "device/Encoders/encoderType.h"

#define DCMotor_PWM_Pin1 0
#define DCMotor_PWM_Pin2 1
#define DCMotor_Enable_Pin 2

// Structure to represent a basic DC Motor controlled with an H-Bridge
struct DCMotor {
    descriptor hardwareDescriptor;
    String name;
    void* encoder; // Pointer to encoder structure (if applicable)
    encoderType encType;
    void (*setSpeed)(DCMotor*, float speed);
};

DCMotor initDCMotor(String name, uint8_t enablePin, uint8_t PWMPin1, uint8_t PWMPin2, void* encoder, encoderType encType);

void setSpeed(DCMotor* motor, float speed);