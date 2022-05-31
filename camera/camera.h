#ifndef OPENGL_GAME_CAMERA_H
#define OPENGL_GAME_CAMERA_H
#include <GLFW/glfw3.h>
#include "../constants.h"
#include "cmath"

struct CameraSpeed {
    float horizontal;
    float vertical;
    float zoom;
};

struct CameraAngle {
    float horizontal;
    float vertical;
    float zoom;
};

CameraSpeed initCameraSpeed();
CameraAngle initCameraAngle();
CameraSpeed changeCameraSpeedOnPress(int key, struct CameraSpeed cameraSpeed);
CameraSpeed changeCameraSpeedOnRelease(int key, struct CameraSpeed cameraSpeed);
CameraAngle changeCameraAngle(struct CameraAngle cameraAngle, struct CameraSpeed cameraSpeed, double elapsedTime);

#endif