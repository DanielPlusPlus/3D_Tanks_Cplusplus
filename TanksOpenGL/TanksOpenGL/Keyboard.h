#pragma once
#include "Positions.h"

class Keyboard {
private:
	static char key;
public:
	static void keyPressed(unsigned char key, int x, int y);
	static void keyReleased(unsigned char key, int x, int y);
	static char getKey(void);
	static void clean(void);
};