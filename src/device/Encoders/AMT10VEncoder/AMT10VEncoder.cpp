#include "AMT10VEncoder.h"

#include <TeensyThreads.h>

#include "robotBase/RobotBase.h"

AMT10VEncoder initAMT10VEncoder(uint8_t pinA, uint8_t pinB, uint8_t pinX, AMT10VResolution resolution, double gearRatio) {
    AMT10VEncoder encoder;
    descriptor descriptor;
    descriptor.pins = (uint8_t*)malloc(sizeof(uint8_t) * 3);
    descriptor.currentPinModes = (uint8_t*)malloc(sizeof(uint8_t) * 3);

    descriptor.pins[AMT10V_A_Pin] = pinA;
    descriptor.pins[AMT10V_B_Pin] = pinB;
    descriptor.pins[AMT10V_X_Pin] = pinX;

    descriptor.currentPinModes[AMT10V_A_Pin] = INPUT_PULLDOWN;
    descriptor.currentPinModes[AMT10V_B_Pin] = INPUT_PULLDOWN;
    descriptor.currentPinModes[AMT10V_X_Pin] = INPUT_PULLDOWN;

    pinMode(pinA, INPUT_PULLDOWN);
    pinMode(pinB, INPUT_PULLDOWN);
    pinMode(pinX, INPUT_PULLDOWN);

    encoder.resolution = resolution;
    encoder.gearRatio = gearRatio;
    encoder.tickCount = 0;
    encoder.indexCount = 0;
    encoder.readEncoder = readAMT10VEncoder;
    encoder.getDegrees = getDegrees;

    encoder.hardwareDescriptor = descriptor;

    return encoder;
}

void readAMT10VEncoder(AMT10VEncoder* encoder) {
    int tickA = digitalRead(encoder->hardwareDescriptor.pins[AMT10V_A_Pin]);
    int tickB = digitalRead(encoder->hardwareDescriptor.pins[AMT10V_B_Pin]);
    int index = digitalRead(encoder->hardwareDescriptor.pins[AMT10V_X_Pin]);

    // Serial.printf("TickA: %d, TickB: %d, Index: %d\n", tickA, tickB, index);

    if (tickA != encoder->prevTick) {
        if (tickA != tickB) {
            encoder->tickCount += tickA;
            encoder->prevTick = tickA;
        } else {
            encoder->tickCount -= tickA;
            encoder->prevTick = tickA;
        }
    }

    if (index != encoder->prevIndex) {
        if (encoder->tickCount > 0) {
            encoder->indexCount = encoder->indexCount + index;
            encoder->prevIndex = index;
        } else {
            encoder->indexCount = encoder->indexCount - index;
            encoder->prevIndex = index;
        }
        encoder->tickCount = 0;
    }
}

double getDegrees(AMT10VEncoder_t *encoder) {
    int tickCount = encoder->tickCount + (encoder->indexCount * encoder->resolution);
    double revolutions = ((double)tickCount / encoder->resolution) / encoder->gearRatio;

    double radians = revolutions * 2 * PI;

    double degrees = radians * (180/PI);

    return degrees;
}
