#include "Engine.h"

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    
    Engine engine(1280, 720, false);
    
    return 0;
}