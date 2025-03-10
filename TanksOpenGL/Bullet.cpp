#include "Bullet.h"

void Bullet::render(void) {
    float radius = 0.05f;
    int sectors = 16;
    int stacks = 16;
    float x, y, z, xy, lengthInv = 1.0f / radius;

    float sectorStep = 2 * M_PI / sectors;
    float stackStep = M_PI / stacks;
    float sectorAngle, stackAngle;

    sphereVert.clear();
    sphereNorm.clear();
    sphereCols.clear();
    sphereInd.clear();

    for (int i = 0; i <= stacks; i++) {
        stackAngle = M_PI / 2 - i * stackStep;
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);

        for (int j = 0; j <= sectors; j++) {
            sectorAngle = j * sectorStep;

            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);
            sphereVert.push_back(x);
            sphereVert.push_back(y);
            sphereVert.push_back(z);

            sphereNorm.push_back(x * lengthInv);
            sphereNorm.push_back(y * lengthInv);
            sphereNorm.push_back(z * lengthInv);

            float heightColor = (float)i / (float)stacks;
            float brownColor = 0.647f;
            float blackColor = 0.0f;
            float r = (1.0f - heightColor) * blackColor + heightColor * brownColor;
            float g = (1.0f - heightColor) * blackColor + heightColor * brownColor * 0.5f;
            float b = (1.0f - heightColor) * blackColor + heightColor * brownColor * 0.25f;

            sphereCols.push_back(r);
            sphereCols.push_back(g);
            sphereCols.push_back(b);
        }
    }

    unsigned int k1, k2;
    for (int i = 0; i < stacks; i++) {
        k1 = i * (sectors + 1);
        k2 = k1 + sectors + 1;

        for (int j = 0; j < sectors; j++, k1++, k2++) {
            if (i != 0) {
                sphereInd.push_back(k1);
                sphereInd.push_back(k2);
                sphereInd.push_back(k1 + 1);
            }

            if (i != (stacks - 1)) {
                sphereInd.push_back(k1 + 1);
                sphereInd.push_back(k2);
                sphereInd.push_back(k2 + 1);
            }
        }
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, sphereVert.data());
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, sphereNorm.data());
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, sphereCols.data());

    glPushMatrix();
    glMultMatrixf(&transformationMatrix[0][0]);
    glDrawElements(GL_TRIANGLES, GLsizei(sphereInd.size()), GL_UNSIGNED_INT, sphereInd.data());
    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    return;
}

void Bullet::translate(const glm::vec3& translation) {
    transformationMatrix = glm::translate(transformationMatrix, translation);
    return;
}

void Bullet::rotate(float angle, const glm::vec3& axis) {
    transformationMatrix = glm::rotate(transformationMatrix, glm::radians(angle), axis);
    return;
}

void Bullet::scale(const glm::vec3& scaling) {
    transformationMatrix = glm::scale(transformationMatrix, scaling);
    return;
}
