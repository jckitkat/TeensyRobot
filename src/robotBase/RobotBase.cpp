#include "RobotBase.h"
#include <TeensyThreads.h>

#include "device/Encoders/AMT10VEncoder/AMT10VEncoder.h"

[[noreturn]] void updateEncoders() {
    while (true) {
        if (robot.encoders == nullptr) {
            Serial.println("no encoders found");
            threads.yield();
        }

        for (int i = 0; i < robot.encoderCount; i++) {

            switch (encoderType type = robot.encoderTypes[i]) {
                case AMT10V: {
                    readAMT10VEncoder(static_cast<AMT10VEncoder_t *>(robot.encoders[i]));
                    break;
                }
                    // Add cases for other encoder types as needed
                default:
                    break;
            }
        }
        threads.yield();
    }
}

void initRobot(int loopTimeMs) {
    robot.loopTimeMs = loopTimeMs;
    threads.setSliceMillis(loopTimeMs);
    threads.addThread(updateEncoders);
}

void registerEncoder(void *encoder, encoderType type) {
    Serial.printf("registering encoder of type %d\n", type);
    robot.encoderCount++;

    Serial.printf("sizeof encoders: %d\n", sizeof(robot.encoders));
    if (robot.encoders == nullptr) {
        robot.encoders = static_cast<void **>(malloc(robot.encoderCount * sizeof(void *)));
        robot.encoderTypes = (encoderType *)malloc(robot.encoderCount * sizeof(encoderType));
    } else {
        robot.encoderTypes = (encoderType *)realloc(robot.encoderTypes, sizeof(encoderType) * (robot.encoderCount));
        robot.encoders = static_cast<void **>(realloc(robot.encoders, sizeof(void *) * robot.encoderCount));
    }

    Serial.printf("sizeof encoders: %d\n", sizeof(robot.encoders));
    robot.encoders[robot.encoderCount - 1] = encoder;
    robot.encoderTypes[robot.encoderCount - 1] = type;
}