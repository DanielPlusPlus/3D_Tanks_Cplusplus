#pragma once

#include <gl/freeglut.h>
#include "TransformInterface.h"
#include <vector>
#include <math.h>

class Bullet : public TransformInterface {
private:
    float M_PI = 3.15f;
    std::vector<float> sphereVert;
    std::vector<float> sphereNorm;
    std::vector<float> sphereCols;
    std::vector<unsigned int> sphereInd;
    glm::mat4 transformationMatrix = glm::mat4(1.0f);
public:
    void render(void);
    void translate(const glm::vec3& translation);
    void rotate(float angle, const glm::vec3& axis);
    void scale(const glm::vec3& scaling);
};