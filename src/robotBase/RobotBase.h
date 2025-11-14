#pragma once
#include "hardwareDescription/hardwareDescription.h"
#include "device/DCMotor/DCMotor.h"
#include "device/AMT10VEncoder/AMT10VEncoder.h"
#include "device/encoderType.h"

inline struct RobotBase {
    void** encoders = nullptr;
    encoderType* encoderTypes = nullptr;
    size_t encoderCount = 0;
    int loopTimeMs = 10;
} robot;

void initRobot(int loopTimeMs);

void registerEncoder(void* encoder, encoderType type);