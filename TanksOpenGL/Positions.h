#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct BulletPos {
	bool isAlive;
	float x, y;
	float speed;
	float angle;
	int bounceCount;
};

struct Player1Pos {
	float x, y;
	float angle;
	bool up;
	bool down;
	bool left;
	bool right;
	glm::vec2 newPosition;
	BulletPos bullets[3];
	short lifes;
};
struct Player2Pos {
	float x, y;
	float angle;
	bool up;
	bool down;
	bool left;
	bool right;
	glm::vec2 newPosition;
	BulletPos bullets[3];
	short lifes;
};

extern Player1Pos player1Pos;
extern Player2Pos player2Pos;