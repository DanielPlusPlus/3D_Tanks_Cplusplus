#include "Keyboard.h"

char Keyboard::key;

void Keyboard::keyPressed(unsigned char key, int x, int y) {
    switch (key) {
    case 'a':
        player1Pos.left = true;
        break;
    case 'd':
        player1Pos.right = true;
        break;
    case 'w':
        player1Pos.up = true;
        break;
    case 's':
        player1Pos.down = true;
        break;
    case 'f':
        for (int i = 0; i < 3; i++) {
            if (!player1Pos.bullets[i].isAlive) {
                player1Pos.bullets[i].isAlive = true;
                break;
            }
        }
        break;
    case 'j':
        player2Pos.left = true;
        break;
    case 'l':
        player2Pos.right = true;
        break;
    case 'i':
        player2Pos.up = true;
        break;
    case 'k':
        player2Pos.down = true;
        break;
    case 'h':
        for (int i = 0; i < 3; i++) {
            if (!player2Pos.bullets[i].isAlive) {
                player2Pos.bullets[i].isAlive = true;
                break;
            }
        }
        break;
    case 27:
        player1Pos.lifes = 0;
        player2Pos.lifes = 0;
        player1Pos.x = 1.25f;
        player1Pos.y = -1.25f;
        player1Pos.angle = 0.0f;
        player2Pos.x = 8.25f;
        player2Pos.y = -8.25f;
        player2Pos.angle = 180.0f;
        for (int i = 0; i < 3; i++) {
            player1Pos.bullets[i].isAlive = false;
            player2Pos.bullets[i].isAlive = false;
        }
        break;
    }
}

void Keyboard::keyReleased(unsigned char key, int x, int y) {
    switch (key) {
    case 'a':
        player1Pos.left = false;
        break;
    case 'd':
        player1Pos.right = false;
        break;
    case 'w':
        player1Pos.up = false;
        break;
    case 's':
        player1Pos.down = false;
        break;
    case 'j':
        player2Pos.left = false;
        break;
    case 'l':
        player2Pos.right = false;
        break;
    case 'i':
        player2Pos.up = false;
        break;
    case 'k':
        player2Pos.down = false;
        break;
    }
}

char Keyboard::getKey(void) {
    return key;
}

void Keyboard::clean(void) {
    key = ' ';
}