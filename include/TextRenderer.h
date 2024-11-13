#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <iostream>
#include <string>

#include <GL/freeglut.h>

class TextRenderer {
public:
    TextRenderer();

    // Draws centered text with a specified message
    void drawCenteredText(const std::string &text, int windowWidth, int windowHeight);

    // Calculates length of a text in pixels
    int getTextLength(const std::string &str);

private:
    void drawText(float x, float y, const std::string& text);
    
    // Setups new ortho projection to render texts
    void setupOrthographicProjection(int windowWidth, int windowHeight);

    //Restores previous projection to draw other elements
    void restoreProjection();
};

#endif // TEXT_RENDERER_H
