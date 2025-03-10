#include "MainMenu.h"

void MainMenu::render(void) {
	GLdouble x = Mouse::getX();
	GLdouble y = Mouse::getY();

	Button titleButton(-2.3f, 0.7f, 4.6f, 1.0f);
	titleButton.loadTexture("textures/title.png");
	titleButton.render();

	Button playButton(-1.15f, -0.2f, 2.3f, 0.5f);
	if (x >= -1.15f && x <= -1.15f + 2.3f &&
		y >= -0.2f && y <= -0.2f + 0.5f) {
		playButton.loadTexture("textures/playClick.png");
	}
	else {
		playButton.loadTexture("textures/play.png");
	}
	
	Button menuButton(-1.15f, -0.8f, 2.3f, 0.5f);
	if (x >= -1.15f && x <= -1.15f + 2.3f &&
		y >= -0.8f && y <= -0.8f + 0.5f) {
		menuButton.loadTexture("textures/settingsClick.png");
	}
	else {
		menuButton.loadTexture("textures/settings.png");
	}

	Button exitButton(-1.15f, -1.4f, 2.3f, 0.5f);
	if (x >= -1.15f && x <= -1.15f + 2.3f &&
		y >= -1.4f && y <= -1.4f + 0.5f) {
		exitButton.loadTexture("textures/exitClick.png");
	}
	else {
		exitButton.loadTexture("textures/exit.png");
	}

	playButton.render();
	menuButton.render();
	exitButton.render();
}
