#include "AMT10VEncoder.h"

#include "robotBase/RobotBase.h"

AMT10VEncoder initAMT10VEncoder(uint8_t pinA, uint8_t pinB, uint8_t pinX, AMT10VResolution resolution) {
    AMT10VEncoder encoder;
    descriptor descriptor;
    descriptor.pins = (uint8_t*)malloc(sizeof(uint8_t) * 3);
    descriptor.currentPinModes = (uint8_t*)malloc(sizeof(uint8_t) * 3);

    descriptor.pins[AMT10V_A_Pin] = pinA;
    descriptor.pins[AMT10V_B_Pin] = pinB;
    descriptor.pins[AMT10V_X_Pin] = pinX;

    descriptor.currentPinModes[AMT10V_A_Pin] = INPUT;
    descriptor.currentPinModes[AMT10V_B_Pin] = INPUT;
    descriptor.currentPinModes[AMT10V_X_Pin] = INPUT;

    pinMode(pinA, INPUT);
    pinMode(pinB, INPUT);
    pinMode(pinX, INPUT);

    encoder.resolution = resolution;
    encoder.tickCount = 0;
    encoder.indexCount = 0;
    encoder.readEncoder = readAMT10VEncoder;

    encoder.hardwareDescriptor = descriptor;

    registerEncoder(&encoder, AMT10V);

    return encoder;
}

void readAMT10VEncoder(AMT10VEncoder* encoder) {
    int tickA = digitalRead(encoder->hardwareDescriptor.pins[AMT10V_A_Pin]);
    int tickB = digitalRead(encoder->hardwareDescriptor.pins[AMT10V_B_Pin]);
    int index = digitalRead(encoder->hardwareDescriptor.pins[AMT10V_X_Pin]);

    if (tickA != encoder->prevTick) {
        if (tickA != tickB) {
            encoder->tickCount++;
            encoder->prevTick = tickA;
        } else {
            encoder->tickCount--;
            encoder->prevTick = tickB;
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
