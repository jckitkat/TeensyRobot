#include "DCMotor.h"

DCMotor initDCMotor(String name, uint8_t enablePin, uint8_t PWMPin1, uint8_t PWMPin2, void* encoder, encoderType encType) {
    DCMotor motor;
    descriptor descriptor;
    descriptor.pins = (uint8_t*)malloc(sizeof(uint8_t) * 3);
    descriptor.currentPinModes = (uint8_t*)malloc(sizeof(uint8_t) * 3);

    descriptor.pins[DCMotor_PWM_Pin1] = PWMPin1;
    descriptor.pins[DCMotor_PWM_Pin2] = PWMPin2;
    descriptor.pins[DCMotor_Enable_Pin] = enablePin;

    descriptor.currentPinModes[DCMotor_PWM_Pin1] = OUTPUT;
    descriptor.currentPinModes[DCMotor_PWM_Pin2] = OUTPUT;
    descriptor.currentPinModes[DCMotor_Enable_Pin] = OUTPUT;

    pinMode(PWMPin1, OUTPUT);
    pinMode(PWMPin2, OUTPUT);
    pinMode(enablePin, OUTPUT);

    motor.encoder = encoder;
    motor.encType = encType;

    motor.hardwareDescriptor = descriptor;
    motor.name = name;
    motor.setSpeed = setSpeed;

    return motor;
}

void setSpeed(DCMotor* motor, float speed) {
    Serial.printf("setSpeed: %d\n", (int)(speed * 255));
    if (speed > 0 && speed <= 1) {
        analogWrite(motor->hardwareDescriptor.pins[DCMotor_Enable_Pin], (int)(speed * 255.0));
        digitalWrite(motor->hardwareDescriptor.pins[DCMotor_PWM_Pin1], HIGH);
        digitalWrite(motor->hardwareDescriptor.pins[DCMotor_PWM_Pin2], LOW);
    } else if (speed < 0 && speed >= -1) {
        analogWrite(motor->hardwareDescriptor.pins[DCMotor_Enable_Pin], (int)(speed * -255.0));
        digitalWrite(motor->hardwareDescriptor.pins[DCMotor_PWM_Pin1], LOW);
        digitalWrite(motor->hardwareDescriptor.pins[DCMotor_PWM_Pin2], HIGH);
    } else {
        analogWrite(motor->hardwareDescriptor.pins[DCMotor_Enable_Pin], 0);
        digitalWrite(motor->hardwareDescriptor.pins[DCMotor_PWM_Pin1], LOW);
        digitalWrite(motor->hardwareDescriptor.pins[DCMotor_PWM_Pin2], LOW);
    }
}
