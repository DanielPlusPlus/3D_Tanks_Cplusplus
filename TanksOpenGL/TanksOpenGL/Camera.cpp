#include "Camera.h"

void Camera::setPosition(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
}

void Camera::setLookAt(float x, float y, float z) {
    lookX = x;
    lookY = y;
    lookZ = z;
}

void Camera::setUpVector(float x, float y, float z) {
    upX = x;
    upY = y;
    upZ = z;
}

void Camera::update(void) {
    gluLookAt(posX, posY, posZ, lookX, lookY, lookZ, upX, upY, upZ);
}