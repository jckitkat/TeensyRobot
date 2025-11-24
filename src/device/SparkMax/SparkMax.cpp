//
// Created by jc on 11/24/25.
//

#include "SparkMax.h"

SparkMax initServo(uint8_t signalPin, void* encoder, encoderType encType) {
    SparkMax sparkMax;
    descriptor descriptor;
    descriptor.pins = (uint8_t*)malloc(sizeof(uint8_t) * 1);
    descriptor.currentPinModes = (uint8_t*)malloc(sizeof(uint8_t) * 1);

    descriptor.pins[0] = signalPin;
    descriptor.currentPinModes[0] = OUTPUT;

    pinMode(descriptor.pins[0], OUTPUT);
    sparkMax.hardwareDescriptor = descriptor;
    sparkMax.setControl = setControl;

    sparkMax.encoder = encoder;
    sparkMax.encType = encType;

    return sparkMax;
}

void setControl(SparkMax *sparkMax, float control) {
    analogWrite(sparkMax->hardwareDescriptor.pins[0], (int)(control * 255.0));
}
