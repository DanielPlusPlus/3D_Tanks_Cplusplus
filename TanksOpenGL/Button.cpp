#include "Button.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Button::Button(float x, float y, float width, float height) : x(x), y(y), width(width), height(height), textureID(0) {}

Button::~Button(void) {
    if (textureID != 0) {
        glDeleteTextures(1, &textureID);
    }
}

void Button::loadTexture(const char* filename) {
    int texWidth, texHeight, texChannels;
    unsigned char* texData = stbi_load(filename, &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    if (texData) {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
        stbi_image_free(texData);
    }
    else {
        std::cout << "Button texture error" << std::endl;
    }
}

void Button::render(void) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width, y);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width, y + height);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y + height);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}