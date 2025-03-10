#include "Engine.h"

unsigned int Engine::maxFPS;
int Engine::frameCount = 0, Engine::currentTime, Engine::previousTime, Engine::fps;
float Engine::r, Engine::g, Engine::b;
State Engine::state = Title;
Camera* Engine::camera;

Engine::~Engine() {
    glutDestroyWindow(glutGetWindow());
}

Engine::Engine(int width, int height, bool fullscreen) : width(width), height(height), fullscreen(fullscreen) {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    //FreeConsole();
    glutInitWindowSize(width, height);

    glutCreateWindow("Tanks 3D");

    if (fullscreen) {
        glutFullScreen();
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, update, 0);
    previousTime = glutGet(GLUT_ELAPSED_TIME);

    setBackgroundColor(0.5f, 0.7f, 0.5f);
    setMaxFPS(60);
    run();
}

void Engine::setBackgroundColor(float red, float green, float blue) {
    r = red;
    g = green;
    b = blue;
    glClearColor(r, g, b, 1.0f);
}

void Engine::setMaxFPS(unsigned int FPS) {
    maxFPS = FPS;
}

void Engine::run(void){
    glutMainLoop();
}

void Engine::update(int value) {
    calculateFPS();
    int targetMillis = 1000 / maxFPS;
    int elapsedMillis = glutGet(GLUT_ELAPSED_TIME) - previousTime;
    int remainingMillis = targetMillis - elapsedMillis;

    if (state == Play) {
        if (player1Pos.lifes <= 0 || player2Pos.lifes <= 0) {
            delete camera;
            camera = NULL;
            state = Win;
            Mouse::choose = Win;
        }
        float angleRad1 = glm::radians(player1Pos.angle);
        glm::vec2 direction1(cos(angleRad1), sin(angleRad1));
        glm::vec2 newPosition1(player1Pos.x, player1Pos.y);
        float angleRad2 = glm::radians(player2Pos.angle);
        glm::vec2 direction2(cos(angleRad2), sin(angleRad2));
        glm::vec2 newPosition2(player2Pos.x, player2Pos.y);

        if (player1Pos.up) {
            newPosition1 += direction1 * 0.05f;
        }
        if (player1Pos.down) {
            newPosition1 -= direction1 * 0.05f;
        }

        if (player1Pos.left) {
            player1Pos.angle += 2.0f;
        }

        if (player1Pos.right) {
            player1Pos.angle -= 2.0f;
        }

        if (player2Pos.up) {
            newPosition2 += direction2 * 0.05f;
        }

        if (player2Pos.down) {
            newPosition2 -= direction2 * 0.05f;
        }

        if (player2Pos.left) {
            player2Pos.angle += 2.0f;
        }

        if (player2Pos.right) {
            player2Pos.angle -= 2.0f;
        }
        for (int i = 0; i < 3; i++) {
            if (player1Pos.bullets[i].isAlive) {
                float radianAngle = glm::radians(player1Pos.bullets[i].angle);
                player1Pos.bullets[i].x += player1Pos.bullets[i].speed * cos(radianAngle);
                player1Pos.bullets[i].y += player1Pos.bullets[i].speed * sin(radianAngle);
            }
        }
        for (int i = 0; i < 3; i++) {
            if (player2Pos.bullets[i].isAlive) {
                float radianAngle = glm::radians(player2Pos.bullets[i].angle);
                player2Pos.bullets[i].x += player2Pos.bullets[i].speed * cos(radianAngle);
                player2Pos.bullets[i].y += player2Pos.bullets[i].speed * sin(radianAngle);
            }
        }
        player1Pos.newPosition = newPosition1;
        player2Pos.newPosition = newPosition2;
    }

    glutPostRedisplay();
    glutTimerFunc(1000 / maxFPS, update, 0);
}

void Engine::render(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    switch (state) {
    case Title: {
        state = MMenu;
        }
        break;
    case MMenu: {
        if (camera == NULL) {
            glLoadIdentity();
            camera = new Camera;
            camera->setPosition(0.0f, 0.0f, 5.0f);
            camera->setLookAt(0.0f, 0.0f, 0.0f);
            camera->setUpVector(0.0f, 1.0f, 0.0f);
            camera->update();
            glutMouseFunc(Mouse::mouseMenuClick);
            glutPassiveMotionFunc(Mouse::mouseMotion);
            glutKeyboardFunc(NULL);
            glutKeyboardUpFunc(NULL);
        }

        MainMenu main;
        main.render();
        state = Mouse::getChoose();

        if (state == Play) {
            delete camera;
            camera = NULL;
        }
        }
        break;
    case Play: {
        if (camera == NULL) {
            glLoadIdentity();
            camera = new Camera;
            camera->setPosition(5.0f, -5.0f, 14.0f);
            camera->setLookAt(5.0f, -5.0f, 0.0f);
            camera->setUpVector(0.0f, 1.0f, 0.0f);
            camera->update();
            glutMouseFunc(NULL);
            glutPassiveMotionFunc(NULL);
            glutKeyboardFunc(Keyboard::keyPressed);
            glutKeyboardUpFunc(Keyboard::keyReleased);
        }

        Game play;

        }
        break;
    case Win: {
        if (camera == NULL) {
            glLoadIdentity();
            camera = new Camera;
            camera->setPosition(0.0f, 0.0f, 5.0f);
            camera->setLookAt(0.0f, 0.0f, 0.0f);
            camera->setUpVector(0.0f, 1.0f, 0.0f);
            camera->update();
            glutMouseFunc(Mouse::mouseWinClick);
            glutPassiveMotionFunc(Mouse::mouseMotion);
        }

        WinMenu winM;
        bool wonFirst;
        if (player1Pos.lifes <= 0 && player2Pos.lifes <= 0)
            state = MMenu;
        else if (player1Pos.lifes <= 0) {
            winM.render(false);
            state = Mouse::getChoose();
        }
        else if (player2Pos.lifes <= 0) {
            winM.render(true);
            state = Mouse::getChoose();
        }
        else
            std::cout << "Error - who did win?" << std::endl;

        if (state == MMenu) {
            player1Pos.lifes = player2Pos.lifes = 3;
            delete camera;
            camera = NULL;
            Mouse::choose = MMenu;
        }
        }
        break;
    case Settings: {
        state = Mouse::getChoose();
        }
        break;
    case Exit: {
        glutLeaveMainLoop();
        }
        break;
    }
    
    glutSwapBuffers();
}

void Engine::reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, static_cast<float>(width) / height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void Engine::calculateFPS(void) {
    frameCount++;
    currentTime = glutGet(GLUT_ELAPSED_TIME);

    if (currentTime - previousTime > 1000) {
        fps = static_cast<int>(frameCount * 1000.0 / (currentTime - previousTime));
        std::cout << "FPS: " << fps << std::endl;

        frameCount = 0;
        previousTime = currentTime;
    }
}