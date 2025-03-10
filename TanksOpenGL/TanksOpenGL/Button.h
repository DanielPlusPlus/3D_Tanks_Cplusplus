#pragma once

#include <iostream>
#include <gl/freeglut.h>

class Button {
public:
	Button(float x, float y, float width, float height);
	~Button(void);
	void loadTexture(const char* filename);
	void render(void);
private:
	float x, y, width, height;
	GLuint textureID;
};
