#pragma once
#include <Arduino.h>

struct descriptor{
    uint8_t* pins;
    uint8_t* currentPinModes;
};