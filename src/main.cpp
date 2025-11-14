#include "robotBase/RobotBase.h"
#include <TeensyThreads.h>

static DCMotor motor;
static AMT10VEncoder encoder;

void setup() {
// write your initialization code here
    Serial.begin(9600);

    encoder = initAMT10VEncoder(0, 1, 2, AMT10V_2048);
    registerEncoder(&encoder, AMT10V);
    motor = initDCMotor("motor", 10, 11, 12, &encoder, AMT10V);

    initRobot(10);

    motor.setSpeed(&motor, -0.3);
}

void loop() {
    Serial.println(encoder.tickCount);
    threads.delay(100);
}
