#pragma once
#include <gl/freeglut.h>

class Camera {
public:
    void setPosition(float x, float y, float z);
    void setLookAt(float x, float y, float z);
    void setUpVector(float x, float y, float z);
    void update(void);

private:
    float posX, posY, posZ;
    float lookX, lookY, lookZ;
    float upX, upY, upZ;
};