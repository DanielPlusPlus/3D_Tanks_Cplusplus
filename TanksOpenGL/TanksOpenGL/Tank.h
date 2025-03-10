#pragma once

#include <gl/freeglut.h>
#include "TransformInterface.h"
#include "Keyboard.h"

class Tank : public TransformInterface {
private:
    glm::mat4 transformationMatrix = glm::mat4(1.0f);
    float truckVert[24] = {
        0.0f, -0.5f, 0.0f, //lewy dolny przed
        0.0f, 0.0f, 0.0f, //lewy gorny przed 
        0.5f, -0.5f, 0.0f, //prawy dolny przed
        0.5f, 0.0f, 0.0f, //prawy gorny przed
        0.0f, -0.5f, -0.3f, //lewy dolny za
        0.0f, 0.0f, -0.3f, //lewy gorny za
        0.5f, -0.5f, -0.3f, //prawy dolny za
        0.5f, 0.0f, -0.3f, //prawy gorny za
    };

    float truckNorm[24] = {
        0.0f, 0.0f, 0.5f,
        0.0f, 0.0f, 0.5f,
        0.0f, 0.0f, 0.5f,
        0.0f, 0.0f, 0.5f,
        0.0f, 0.0f, -0.5f,
        0.0f, 0.0f, -0.5f,
        0.0f, 0.0f, -0.5f,
        0.0f, 0.0f, -0.5f
    };

    float truckCols[24] = {
        0.0f, 0.3f, 0.3f,
        0.0f, 0.3f, 0.3f,
        0.0f, 1.0f, 0.3f,
        0.0f, 0.3f, 0.3f,
        0.0f, 0.3f, 0.3f,
        0.0f, 1.0f, 0.3f,
        0.0f, 0.3f, 0.3f,
        0.0f, 0.3f, 0.3f
    };

    unsigned char truckInd[36] = {
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

    float hullVert[24] = {
        0.0f, -0.3f, 0.0f, //lewy dolny przed
        0.0f, 0.0f, 0.0f, //lewy gorny przed 
        0.3f, -0.3f, 0.0f, //prawy dolny przed
        0.3f, 0.0f, 0.0f, //prawy gorny przed
        0.0f, -0.3f, 0.2f, //lewy dolny za
        0.0f, 0.0f, 0.2f, //lewy gorny za
        0.3f, -0.3f, 0.2f, //prawy dolny za
        0.3f, 0.0f, 0.2f, //prawy gorny za
    };

    float hullNorm[24] = {
        0.0f, 0.0f, 0.5f,
        0.0f, 0.0f, 0.5f,
        0.0f, 0.0f, 0.5f,
        0.0f, 0.0f, 0.5f,
        0.0f, 0.0f, -0.5f,
        0.0f, 0.0f, -0.5f,
        0.0f, 0.0f, -0.5f,
        0.0f, 0.0f, -0.5f
    };

    float hullCols[24] = {
        0.0f, 0.3f, 0.3f,
        0.0f, 0.3f, 0.3f,
        0.0f, 1.0f, 0.3f,
        0.0f, 0.3f, 0.3f,
        0.0f, 0.3f, 0.3f,
        0.0f, 1.0f, 0.3f,
        0.0f, 0.3f, 0.3f,
        0.0f, 0.3f, 0.3f
    };

    unsigned char hullInd[36] = {
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
    float gunVert[24] = {
        0.0f, -0.1f, 0.0f, //lewy dolny przed
        0.0f, 0.0f, 0.0f, //lewy gorny przed 
        0.3f, -0.1f, 0.0f, //prawy dolny przed
        0.3f, 0.0f, 0.0f, //prawy gorny przed
        0.0f, -0.1f, 0.1f, //lewy dolny za
        0.0f, 0.0f, 0.1f, //lewy gorny za
        0.3f, -0.1f, 0.1f, //prawy dolny za
        0.3f, 0.0f, 0.1f, //prawy gorny za
    };

    float gunNorm[24] = {
        0.0f, 0.0f, 0.5f,
        0.0f, 0.0f, 0.5f,
        0.0f, 0.0f, 0.5f,
        0.0f, 0.0f, 0.5f,
        0.0f, 0.0f, -0.5f,
        0.0f, 0.0f, -0.5f,
        0.0f, 0.0f, -0.5f,
        0.0f, 0.0f, -0.5f
    };

    float gunCols[24] = {
        0.0f, 0.3f, 0.3f,
        0.0f, 0.3f, 0.3f,
        0.0f, 1.0f, 0.3f,
        0.0f, 0.3f, 0.3f,
        0.0f, 0.3f, 0.3f,
        0.0f, 1.0f, 0.3f,
        0.0f, 0.3f, 0.3f,
        0.0f, 0.3f, 0.3f
    };

    unsigned char gunInd[36] = {
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
public:
    void render(void);
    void translate(const glm::vec3& translation) override;
    void rotate(float angle, const glm::vec3& axis) override;
    void scale(const glm::vec3& scale) override;
};