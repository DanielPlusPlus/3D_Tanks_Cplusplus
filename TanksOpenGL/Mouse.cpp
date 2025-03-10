#include "Mouse.h"

GLint Mouse::viewport[4];
GLdouble Mouse::modelview[16];
GLdouble Mouse::projection[16];
GLfloat Mouse::winX, Mouse::winY, Mouse::winZ;
GLdouble Mouse::posX, Mouse::posY, Mouse::posZ;
State Mouse::choose = MMenu;

void Mouse::mouseMenuClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
        glGetDoublev(GL_PROJECTION_MATRIX, projection);
        glGetIntegerv(GL_VIEWPORT, viewport);
        winX = (float)x;
        winY = (float)viewport[3] - (float)y;
        glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
        gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
        if (posX >= -1.15f && posX <= -1.15f + 2.3f &&
            posY >= -0.2f && posY <= -0.2f + 0.5f) {
            choose = Play;
        }
        else if (posX >= -1.15f && posX <= -1.15f + 2.3f &&
            posY >= -0.8f && posY <= -0.8f + 0.5f) {
            choose = Settings;
        }
        else if (posX >= -1.15f && posX <= -1.15f + 2.3f &&
            posY >= -1.4f && posY <= -1.4f + 0.5f) {
            choose = Exit;
        }
        else {
            std::cout << "Cord: X: " << posX << std::endl;
            std::cout << "Cord: Y: " << posY << std::endl;
            std::cout << "Cord: Z: " << posZ << std::endl;
            unsigned char pixelColor[3];
            glReadPixels(x, int(winY), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixelColor);
            std::cout << "Pixel color: (" << (int)pixelColor[0] << ", " << (int)pixelColor[1] << ", " << (int)pixelColor[2] << ")" << std::endl;
            choose = MMenu;
        }
    }
    return;
}

void Mouse::mouseWinClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        choose = MMenu;
    }
    return;
}

void Mouse::mouseMotion(int x, int y) {
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
    return;
}

GLdouble Mouse::getX(void) {
    return posX;
}

GLdouble Mouse::getY(void) {
    return posY;
}

State Mouse::getChoose(void) {
    return choose;
}
