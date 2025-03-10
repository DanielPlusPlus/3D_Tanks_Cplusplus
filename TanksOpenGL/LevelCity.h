#pragma once
#include "Level.h"
#include "Bullet.h"

class LevelCity : public Level {
private:
	void setLevel(void) override;
	void checkCollision(glm::vec2 newPosition, bool firstTank) override;
	void checkBullet(bool firstTank) override;
	void resetPositions(void) override;
public:
	void render(void) override;
};