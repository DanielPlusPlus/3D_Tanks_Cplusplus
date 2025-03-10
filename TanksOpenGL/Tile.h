#pragma once

#include <gl/freeglut.h>
#include <iostream>
#include "TransformInterface.h"

class Tile : public TransformInterface {
private:
    glm::mat4 transformationMatrix = glm::mat4(1.0f);
    float cubeVert[24] = {
        0.0f, -1.0f, 0.0f, //lewy dolny przed
        0.0f, 0.0f, 0.0f, //lewy gorny przed 
        1.0f, -1.0f, 0.0f, //prawy dolny przed
        1.0f, 0.0f, 0.0f, //prawy gorny przed
        0.0f, -1.0f, -1.0f, //lewy za przed
        0.0f, 0.0f, -1.0f, //lewy za przed 
        1.0f, -1.0f, -1.0f, //prawy za przed
        1.0f, 0.0f, -1.0f, //prawy za przed
    };

    float cubeNorm[24] = {
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f
    };

    float cubeCols[24] = {
        1.0f, 0.3f, 0.3f,
        1.0f, 0.3f, 0.3f,
        1.0f, 1.0f, 0.3f,
        1.0f, 0.3f, 0.3f,
        1.0f, 0.3f, 0.3f,
        1.0f, 1.0f, 0.3f,
        1.0f, 0.3f, 0.3f,
        1.0f, 0.3f, 0.3f
    };

    unsigned char cubeInd[36] = {
        0, 1, 2,
        2, 1, 3,
        4, 5, 6,
        6, 5, 7,
        0, 1, 5,
        0, 5, 4,
        2, 3, 7,
        2, 7, 6,
        0, 4, 6,
        0, 6, 2,
        1, 5, 7,
        1, 7, 3
    };
    bool higher = false;
public:
    void render(void);
    void translate(const glm::vec3& translation) override;
    void rotate(float angle, const glm::vec3& axis) override;
    void scale(const glm::vec3& scale) override;
    bool isColliding(float x, float y);
    bool isHigher(void);
};