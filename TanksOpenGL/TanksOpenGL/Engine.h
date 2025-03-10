#pragma once

#include "Camera.h"
#include "MainMenu.h"
#include "WinMenu.h"
#include "Game.h"

class Engine {
public:
	~Engine();
	Engine(int width, int height, bool fullscreen);
private:
	int width, height;
	bool fullscreen;

	static float r, g, b;
	static unsigned int maxFPS;
	static int frameCount;
	static int currentTime, previousTime;
	static int fps;
	static State state;
	static Camera* camera;

	void setBackgroundColor(float red, float green, float blue);
	void setMaxFPS(unsigned int FPS);
	void run(void);

	static void update(int value);
	static void render(void);
	static void reshape(int width, int height);
	static void calculateFPS(void);
};