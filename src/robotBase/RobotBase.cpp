#include "RobotBase.h"
#include <TeensyThreads.h>

void updateEncoders() {
    if (robot.encoders == nullptr) {
        threads.yield();
    }

    for (size_t i = 0; i < robot.encoderCount; i++) {
        encoderType type = robot.encoderTypes[i];
        void* encoder = robot.encoders[i];

        switch (type) {
            case AMT10V: {
                static_cast<AMT10VEncoder *>(encoder)->readEncoder((AMT10VEncoder *)encoder);
                break;
            }
            // Add cases for other encoder types as needed
            default:
                break;
        }
    }
    threads.yield();
}

void initRobot(int loopTimeMs) {
    robot.loopTimeMs = loopTimeMs;
    threads.setSliceMillis(loopTimeMs);
    threads.addThread(updateEncoders);
}

void registerEncoder(void *encoder, encoderType type) {
    robot.encoderCount++;
    if (robot.encoders == nullptr) {
        robot.encoders = (void **)malloc(sizeof(void *));
        robot.encoderTypes = (encoderType *)malloc(sizeof(encoderType));
    } else {
        robot.encoderTypes = (encoderType *)realloc(robot.encoderTypes, sizeof(encoderType) * (robot.encoderCount));
        robot.encoders = (void **)realloc(robot.encoders, sizeof(void *) * (robot.encoderCount));
    }

    robot.encoders[robot.encoderCount - 1] = encoder;
    robot.encoderTypes[robot.encoderCount - 1] = type;
}