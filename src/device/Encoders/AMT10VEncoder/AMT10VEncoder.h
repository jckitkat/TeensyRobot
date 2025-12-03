#pragma once

#include "hardwareDescription/hardwareDescription.h"

#define AMT10V_A_Pin 0
#define AMT10V_B_Pin 1
#define AMT10V_X_Pin 2

enum AMT10VResolution {
    AMT10V_48 = 48,
    AMT10V_96 = 96,
    AMT10V_100 = 100,
    AMT10V_125 = 125,
    AMT10V_192 = 192,
    AMT10V_200 = 200,
    AMT10V_250 = 250,
    AMT10V_256 = 256,
    AMT10V_384 = 384,
    AMT10V_400 = 400,
    AMT10V_500 = 500,
    AMT10V_512 = 512,
    AMT10V_800 = 800,
    AMT10V_1000 = 1000,
    AMT10V_1024 = 1024,
    AMT10V_2048 = 2048,
};

// Structure to represent the AMT10V encoder
typedef struct AMT10VEncoder {
    descriptor hardwareDescriptor;
    AMT10VResolution resolution;
    // gear ratio from input to the encoder to the output of the mechanism
    double gearRatio;
    int tickCount;
    int indexCount;
    void (*readEncoder)(AMT10VEncoder*);
    double (*getDegrees)(AMT10VEncoder*);
    int prevTick;
    int prevIndex;
} AMT10VEncoder_t;

AMT10VEncoder_t initAMT10VEncoder(uint8_t pinA, uint8_t pinB, uint8_t pinX, AMT10VResolution resolution, double gearRatio);

void readAMT10VEncoder(AMT10VEncoder_t* encoder);

double getDegrees(AMT10VEncoder_t* encoder);