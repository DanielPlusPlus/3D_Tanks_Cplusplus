#pragma once
#include <vector>
#include "Tile.h"
#include "Tank.h"
#include "Bullet.h"

class Level {
protected:
	Tile blocks[10][10];
	Tank player1Tank, player2Tank;
	Bullet player1Bullets[3];
	Bullet player2Bullets[3];
	virtual void setLevel(void) = 0;
	virtual void checkCollision(glm::vec2 newPosition, bool firstTank) = 0;
	virtual void checkBullet(bool firstTank) = 0;
	virtual void resetPositions(void) = 0;
public:
	virtual void render(void) = 0;
};