#include "LevelCity.h"

void LevelCity::render(void) {
    setLevel();
    checkCollision(player1Pos.newPosition, true);
    checkCollision(player2Pos.newPosition, false);

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) {
            blocks[i][j].render();
        }
    player1Tank.render();
    player2Tank.render();
    checkBullet(true);
    checkBullet(false);
    for (int i = 0; i < 3; i++) {
        if (player1Pos.bullets[i].isAlive) {
            player1Bullets[i].render();
        }
        if (player2Pos.bullets[i].isAlive) {
            player2Bullets[i].render();
        }
    }
    return;
}

void LevelCity::setLevel(void) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) {
            blocks[i][j] = Tile();
            blocks[i][j].translate(glm::vec3(float(j), float(i)*(-1), 0.0f));
        }
    for (int i = 0; i < 10; i++) {
        blocks[0][i].translate(glm::vec3(0.0f, 0.0f, 1.0f));
        blocks[9][i].translate(glm::vec3(0.0f, 0.0f, 1.0f));
    }
    for (int i = 1; i < 9; i++) {
        blocks[i][0].translate(glm::vec3(0.0f, 0.0f, 1.0f));
        blocks[i][9].translate(glm::vec3(0.0f, 0.0f, 1.0f));
    }
    blocks[1][8].translate(glm::vec3(0.0f, 0.0f, 1.0f));
    blocks[2][2].translate(glm::vec3(0.0f, 0.0f, 1.0f));
    blocks[2][3].translate(glm::vec3(0.0f, 0.0f, 1.0f));
    blocks[2][6].translate(glm::vec3(0.0f, 0.0f, 1.0f));
    blocks[3][8].translate(glm::vec3(0.0f, 0.0f, 1.0f));
    blocks[4][2].translate(glm::vec3(0.0f, 0.0f, 1.0f));
    blocks[4][3].translate(glm::vec3(0.0f, 0.0f, 1.0f));
    blocks[4][5].translate(glm::vec3(0.0f, 0.0f, 1.0f));
    blocks[5][5].translate(glm::vec3(0.0f, 0.0f, 1.0f));
    blocks[6][1].translate(glm::vec3(0.0f, 0.0f, 1.0f));
    blocks[6][2].translate(glm::vec3(0.0f, 0.0f, 1.0f));
    blocks[7][2].translate(glm::vec3(0.0f, 0.0f, 1.0f));
    blocks[7][4].translate(glm::vec3(0.0f, 0.0f, 1.0f));
    blocks[7][5].translate(glm::vec3(0.0f, 0.0f, 1.0f));
    blocks[7][7].translate(glm::vec3(0.0f, 0.0f, 1.0f));
    player1Tank = Tank();
    player2Tank = Tank();
    Bullet bullet;
    bullet.translate(glm::vec3(0.25f, -0.25f, 0.35f));
    for (int i = 0; i < 3; i++) {
        if (player1Pos.bullets[i].isAlive) {
            player1Bullets[i] = bullet;
        }
        if (player2Pos.bullets[i].isAlive) {
            player2Bullets[i] = bullet;
        }
    }
    return;
}

void LevelCity::checkCollision(glm::vec2 newPosition, bool firstTank) {
    int minX = std::max(0, static_cast<int>(newPosition.x - 0.5f));
    int maxX = std::min(9, static_cast<int>(newPosition.x + 0.5f));
    int minY = std::max(0, static_cast<int>(-newPosition.y - 0.5f));
    int maxY = std::min(9, static_cast<int>(-newPosition.y + 0.5f));

    bool collisionDetected = false;
    for (int i = minY; i <= maxY && !collisionDetected; i++) {
        for (int j = minX; j <= maxX && !collisionDetected; j++) {
            if (blocks[i][j].isHigher()) {
                if (blocks[i][j].isColliding(newPosition.x, newPosition.y) ||
                    blocks[i][j].isColliding(newPosition.x + 0.5f, newPosition.y) ||
                    blocks[i][j].isColliding(newPosition.x, newPosition.y - 0.5f) ||
                    blocks[i][j].isColliding(newPosition.x + 0.5f, newPosition.y - 0.5f)) {
                    collisionDetected = true;
                }
            }
        }
    }

    if (firstTank) {
        glm::vec2 player2Center(player2Pos.x + 0.25f, player2Pos.y - 0.25f);
        glm::vec2 player1Center(newPosition.x + 0.25f, newPosition.y - 0.25f);
        if (glm::distance(player1Center, player2Center) < 0.5f) {
            collisionDetected = true;
        }
    }
    else {
        glm::vec2 player1Center(player1Pos.x + 0.25f, player1Pos.y - 0.25f);
        glm::vec2 player2Center(newPosition.x + 0.25f, newPosition.y - 0.25f);
        if (glm::distance(player2Center, player1Center) < 0.5f) {
            collisionDetected = true;
        }
    }

    if (!collisionDetected) {
        if (firstTank) {
            player1Pos.x = newPosition.x;
            player1Pos.y = newPosition.y;
            player1Tank.translate(glm::vec3(player1Pos.x, player1Pos.y, 0.3f));
            player1Tank.rotate(player1Pos.angle, glm::vec3(0.0f, 0.0f, 1.0f));
        }
        else {
            player2Pos.x = newPosition.x;
            player2Pos.y = newPosition.y;
            player2Tank.translate(glm::vec3(player2Pos.x, player2Pos.y, 0.3f));
            player2Tank.rotate(player2Pos.angle, glm::vec3(0.0f, 0.0f, 1.0f));
        }
    }
    else {
        if (firstTank) {
            player1Tank.translate(glm::vec3(player1Pos.x, player1Pos.y, 0.3f));
            player1Tank.rotate(player1Pos.angle, glm::vec3(0.0f, 0.0f, 1.0f));
        }
        else {
            player2Tank.translate(glm::vec3(player2Pos.x, player2Pos.y, 0.3f));
            player2Tank.rotate(player2Pos.angle, glm::vec3(0.0f, 0.0f, 1.0f));
        }
    }
    return;
}

void LevelCity::checkBullet(bool firstTank) {
    for (int i = 0; i < 3; i++) {
        if (firstTank) {
            if (player1Pos.bullets[i].isAlive) {
                int bulletMinX = std::max(0, static_cast<int>(player1Pos.bullets[i].x - 0.5f));
                int bulletMaxX = std::min(9, static_cast<int>(player1Pos.bullets[i].x + 0.5f));
                int bulletMinY = std::max(0, static_cast<int>(-player1Pos.bullets[i].y - 0.5f));
                int bulletMaxY = std::min(9, static_cast<int>(-player1Pos.bullets[i].y + 0.5f));

                for (int row = bulletMinY; row <= bulletMaxY; row++) {
                    for (int col = bulletMinX; col <= bulletMaxX; col++) {
                        if (blocks[row][col].isHigher()) {
                            if (blocks[row][col].isColliding(player1Pos.bullets[i].x, player1Pos.bullets[i].y) ||
                                blocks[row][col].isColliding(player1Pos.bullets[i].x + 0.25f, player1Pos.bullets[i].y) ||
                                blocks[row][col].isColliding(player1Pos.bullets[i].x, player1Pos.bullets[i].y - 0.25f) ||
                                blocks[row][col].isColliding(player1Pos.bullets[i].x + 0.25f, player1Pos.bullets[i].y - 0.25f)) {
                                player1Pos.bullets[i].speed = player1Pos.bullets[i].speed * (-1);
                                player1Pos.bullets[i].angle += 45.0f;
                                player1Pos.bullets[i].bounceCount++;
                                if (player1Pos.bullets[i].bounceCount >= 6) {
                                    player1Pos.bullets[i].isAlive = false;
                                    player1Pos.bullets[i].bounceCount = 0;
                                    if (player1Pos.bullets[i].speed < 0) {
                                        player1Pos.bullets[i].speed = abs(player1Pos.bullets[i].speed);
                                    }
                                }
                                break;
                            }
                        }
                    }
                    glm::vec2 player2Center(player2Pos.x + 0.25f, player2Pos.y - 0.25f);
                    glm::vec2 bulletCenter(player1Pos.bullets[i].x + 0.025f, player1Pos.bullets[i].y - 0.025f);
                    if (glm::distance(bulletCenter, player2Center) < 0.5f) { //Tutaj co sie dzieje jak bullet czolgu numer 1 dotnie czolgu numer 2
                        player1Pos.bullets[i].isAlive = false;
                        player1Pos.bullets[i].bounceCount = 0;
                        resetPositions();
                        player2Pos.lifes--;
                    }
                    if (!player1Pos.bullets[i].isAlive) break;
                }
                player1Bullets[i].translate(glm::vec3(player1Pos.bullets[i].x, player1Pos.bullets[i].y, 0.0f));
            }
            else {
                player1Pos.bullets[i].x = player1Pos.x;
                player1Pos.bullets[i].y = player1Pos.y;
                player1Pos.bullets[i].angle = player1Pos.angle;
            }
        }
        else {
            if (player2Pos.bullets[i].isAlive) {
                int bulletMinX = std::max(0, static_cast<int>(player2Pos.bullets[i].x - 0.5f));
                int bulletMaxX = std::min(9, static_cast<int>(player2Pos.bullets[i].x + 0.5f));
                int bulletMinY = std::max(0, static_cast<int>(-player2Pos.bullets[i].y - 0.5f));
                int bulletMaxY = std::min(9, static_cast<int>(-player2Pos.bullets[i].y + 0.5f));

                for (int row = bulletMinY; row <= bulletMaxY; row++) {
                    for (int col = bulletMinX; col <= bulletMaxX; col++) {
                        if (blocks[row][col].isHigher()) {
                            if (blocks[row][col].isColliding(player2Pos.bullets[i].x, player2Pos.bullets[i].y) ||
                                blocks[row][col].isColliding(player2Pos.bullets[i].x + 0.25f, player2Pos.bullets[i].y) ||
                                blocks[row][col].isColliding(player2Pos.bullets[i].x, player2Pos.bullets[i].y - 0.25f) ||
                                blocks[row][col].isColliding(player2Pos.bullets[i].x + 0.25f, player2Pos.bullets[i].y - 0.25f)) {
                                player2Pos.bullets[i].speed = player2Pos.bullets[i].speed * (-1);
                                player2Pos.bullets[i].angle += 45.0f;
                                player2Pos.bullets[i].bounceCount++;
                                if (player2Pos.bullets[i].bounceCount >= 6) {
                                    player2Pos.bullets[i].isAlive = false;
                                    player2Pos.bullets[i].bounceCount = 0;
                                    if (player2Pos.bullets[i].speed < 0) {
                                        player2Pos.bullets[i].speed = abs(player2Pos.bullets[i].speed);
                                    }
                                }
                                break;
                            }
                        }
                    }
                    glm::vec2 player1Center(player1Pos.x + 0.25f, player1Pos.y - 0.25f);
                    glm::vec2 bulletCenter(player2Pos.bullets[i].x + 0.025f, player2Pos.bullets[i].y - 0.025f);
                    if (glm::distance(bulletCenter, player1Center) < 0.5f) { //Tutaj co sie dzieje jak bullet czolgu numer 2 dotnie czolgu numer 1
                        player2Pos.bullets[i].isAlive = false;
                        player2Pos.bullets[i].bounceCount = 0;
                        player1Pos.lifes--;
                        resetPositions();
                    }
                    if (!player2Pos.bullets[i].isAlive) break;
                }
                player2Bullets[i].translate(glm::vec3(player2Pos.bullets[i].x, player2Pos.bullets[i].y, 0.0f));
            }
            else {
                player2Pos.bullets[i].x = player2Pos.x;
                player2Pos.bullets[i].y = player2Pos.y;
                player2Pos.bullets[i].angle = player2Pos.angle;
            }
        }
    }
}

void LevelCity::resetPositions(void) {
    player1Pos.x =  1.25f;
    player1Pos.y = -1.25f;
    player1Pos.angle = 0.0f;
    player2Pos.x = 8.25f;
    player2Pos.y = -8.25f;
    player2Pos.angle = 180.0f;
    for (int i = 0; i < 3; i++) {
        player1Pos.bullets[i].isAlive = false;
        player1Pos.bullets[i].speed = abs(player2Pos.bullets[i].speed);
        player2Pos.bullets[i].isAlive = false;
        player2Pos.bullets[i].speed = abs(player2Pos.bullets[i].speed);
    }
    return;
}
