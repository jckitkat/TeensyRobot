//
// Created by jc on 11/24/25.
//

#include "Servo.h"

SparkMax initServo(uint8_t signalPin, ServoType type) {
    SparkMax servo;
    descriptor descriptor;
    descriptor.pins = (uint8_t*)malloc(sizeof(uint8_t) * 1);
    descriptor.currentPinModes = (uint8_t*)malloc(sizeof(uint8_t) * 1);

    descriptor.pins[0] = signalPin;
    descriptor.currentPinModes[0] = OUTPUT;

    pinMode(descriptor.pins[0], OUTPUT);
    servo.hardwareDescriptor = descriptor;
    servo.type = type;
    servo.setControl = setControl;

    return servo;
}

void setServoAngle(SparkMax *servo, float angle) {
    analogWrite(servo->hardwareDescriptor.pins[0], (int)(angle / 180.0 * 255.0));
}

void setServoSpeed(SparkMax *servo, float speed) {
    analogWrite(servo->hardwareDescriptor.pins[0], (int)((speed + 1.0) / 2.0 * 255.0));
}

void setControl(SparkMax *servo, float control) {
    switch (servo->type) {
        case CONTINUOUS:
            setServoSpeed(servo, control);
            break;
        case STANDARD:
            setServoAngle(servo, control);
            break;
        default:
            break;
    }
}
