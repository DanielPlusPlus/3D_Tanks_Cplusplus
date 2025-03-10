#pragma once
#include <iostream>
#include <gl/freeglut.h>
#include "State.h"

class Mouse {
private:
    static GLint viewport[4];
    static GLdouble modelview[16];
    static GLdouble projection[16];
    static GLfloat winX, winY, winZ;
    static GLdouble posX, posY, posZ;
public:
    static State choose;
	static void mouseMenuClick(int button, int state, int x, int y);
    static void mouseWinClick(int button, int state, int x, int y);
    static void mouseMotion(int x, int y);
    static GLdouble getX(void);
    static GLdouble getY(void);
    static State getChoose(void);
};