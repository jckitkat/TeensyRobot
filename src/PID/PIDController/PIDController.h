#pragma once

struct PIDController {
    float kp;
    float ki;
    float kd;
    float previousError;
    float integral;
    float setpoint;
    unsigned long lastTime;
    // bool continuousOutput;
    // float minimumOutput;
    // float maximumOutput;
    float (*calculate)(PIDController*, float currentValue);
};