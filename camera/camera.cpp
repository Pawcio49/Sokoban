#include "camera.h"

CameraSpeed initCameraSpeed(){
    struct CameraSpeed cameraSpeed;
    cameraSpeed.horizontal = 0;
    cameraSpeed.vertical = 0;
    cameraSpeed.zoom = 0;
    return cameraSpeed;
}

CameraAngle initCameraAngle(){
    struct CameraAngle cameraAngle;
    cameraAngle.horizontal = 0;
    cameraAngle.vertical = 0;
    cameraAngle.zoom = STARTING_CAMERA_ZOOM;
    return cameraAngle;
}

CameraSpeed changeCameraSpeedOnPress(int key, struct CameraSpeed cameraSpeed){
    if (key == GLFW_KEY_A)
        cameraSpeed.horizontal = -CAMERA_ROTATE_SPEED;
    else if (key == GLFW_KEY_D)
        cameraSpeed.horizontal = CAMERA_ROTATE_SPEED;
    
    if (key == GLFW_KEY_W)
        cameraSpeed.vertical = -CAMERA_ROTATE_SPEED;
    else if (key == GLFW_KEY_S)
        cameraSpeed.vertical = CAMERA_ROTATE_SPEED;

    if (key == GLFW_KEY_Q)
        cameraSpeed.zoom = -CAMERA_ZOOM_SPEED;
    else if (key == GLFW_KEY_E)
        cameraSpeed.zoom = CAMERA_ZOOM_SPEED;

    return cameraSpeed;
}

CameraSpeed changeCameraSpeedOnRelease(int key, struct CameraSpeed cameraSpeed){
    if (key == GLFW_KEY_A || key == GLFW_KEY_D)
        cameraSpeed.horizontal = 0;
    if (key == GLFW_KEY_W || key == GLFW_KEY_S)
        cameraSpeed.vertical = 0;
    if (key == GLFW_KEY_Q || key == GLFW_KEY_E)
        cameraSpeed.zoom = 0;

    return cameraSpeed;
}

CameraAngle changeCameraAngle(struct CameraAngle cameraAngle, struct CameraSpeed cameraSpeed, double elapsedTime){
    cameraAngle.horizontal += cameraSpeed.horizontal * elapsedTime;
    if(cameraAngle.horizontal > RIGHT_ANGLE) {
        cameraAngle.horizontal = RIGHT_ANGLE;
    } else if(cameraAngle.horizontal < -RIGHT_ANGLE) {
        cameraAngle.horizontal = -RIGHT_ANGLE;
    }

    cameraAngle.vertical += cameraSpeed.vertical * elapsedTime;
    if(cameraAngle.vertical > RIGHT_ANGLE) {
        cameraAngle.vertical = RIGHT_ANGLE;
    } else if(cameraAngle.vertical < -RIGHT_ANGLE) {
        cameraAngle.vertical = -RIGHT_ANGLE;
    }

    cameraAngle.zoom += cameraSpeed.zoom * elapsedTime;
    if(cameraAngle.zoom < ceil((MAX_MAP_SIZE+1)*sqrt(2))){
        cameraAngle.zoom = ceil((MAX_MAP_SIZE+1)*sqrt(2));
    }
    return cameraAngle;
}