#pragma once
#include "hardwareDescription/hardwareDescription.h"
#include "device/encoderType.h"

#define DCMotor_PWM_Pin1 0
#define DCMotor_PWM_Pin2 1
#define DMMotor_Enable_Pin 2

// Structure to represent a basic DC Motor controlled with an H-Bridge
struct DCMotor {
    descriptor hardwareDescriptor;
    String name;
    void* encoder; // Pointer to encoder structure (if applicable)
    encoderType encType;
    void (*setSpeed)(DCMotor*, int speed);
};

DCMotor initDCMotor(String name, uint8_t PWMPin, uint8_t directionPin, encoderType encType);

void setSpeed(DCMotor* motor, int speed);