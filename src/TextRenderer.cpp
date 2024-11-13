#include "TextRenderer.h"

TextRenderer::TextRenderer() {}

void TextRenderer::drawCenteredText(const std::string& text, int windowWidth, int windowHeight) {
    int width = windowWidth;
    int height = windowHeight / 2.0;
    float centerX = (width - getTextLength(text)) / 2.0;

    // Red colored text
    glColor3f(1, 0, 0);

    // Set up 2D projection
    setupOrthographicProjection(windowWidth, windowHeight);

    // Use drawText to position and render the text
    drawText(centerX, height, text);

    // Restore the previous projection
    restoreProjection();
}

int TextRenderer::getTextLength(const std::string &str) {
    int width = 0;
    for (char c : str) {
        width += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
    return width;
}

void TextRenderer::drawText(float x, float y, const std::string& text) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}

void TextRenderer::setupOrthographicProjection(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, height, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void TextRenderer::restoreProjection() {
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
