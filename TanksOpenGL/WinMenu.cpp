#include "WinMenu.h"

void WinMenu::render(bool wonFirst) {
	Button winButton(-1.15f, -0.2f, 2.3f, 0.5f);
	if(wonFirst)
		winButton.loadTexture("textures/player1Wins.png");
	else
		winButton.loadTexture("textures/player2Wins.png");
	winButton.render();
}
