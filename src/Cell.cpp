#include <iostream>

#include "Cell.h"


Cell::Cell(int row, int col, Color color) : x(row), y(col), color(color), state(CellState::EMPTY) {}

Cell::Cell() {}

void Cell::setState(CellState newState) {
    state = newState;
}

CellState Cell::getState() const {
    return state;
}

Color Cell::getColor() const {
    return color;
}

void Cell::setNextState() {
    int value = state;
    value++;
    if(value == 3) value = 0;
    state = static_cast<CellState>(value);
}

void Cell::setColor() {
    switch (color) {
        case Color::Purple:
            glColor3f(0.75f, 0.65f, 0.85f);
            break;
        case Color::Orange:
            glColor3f(1.0f, 0.75f, 0.4f);
            break;
        case Color::Blue:
            glColor3f(0.4f, 0.7f, 1.0f);
            break;
        case Color::Green:
            glColor3f(0.5f, 0.9f, 0.6f);
            break;
        case Color::Beige:
            glColor3f(0.98f, 0.98f, 0.92f);
            break;
        case Color::Red:
            glColor3f(1.0f, 0.5f, 0.5f);
            break;
        case Color::Yellow:
            glColor3f(1.0f, 1.0f, 0.6f);
            break;
        case Color::Gray:
            glColor3f(0.7f, 0.7f, 0.7f);
            break;
    }
}

void Cell::draw() {
    drawQuad();

    if (state == CellState::CROSS) {
        drawCross();

    } else if (state == CellState::CROWN) {
        drawCrown();
    }
}

void Cell::drawQuad() {
    setColor();
    glBegin(GL_QUADS); // Start drawing a rectangle

    glVertex2f(y + 0.01, x + 0.99); // Top-left corner
    glVertex2f(y + 0.99, x + 0.99); // Top-right corner
    glVertex2f(y + 0.99, x + 0.01); // Bottom-right corner
    glVertex2f(y + 0.01, x + 0.01); // Bottom-left corner

    glEnd();
}

void Cell::drawCross() {
    glColor3f(0, 0, 0); // Set color to black

    glBegin(GL_LINES);
    glVertex2f(y + 0.45, x + 0.55); // Top-left corner
    glVertex2f(y + 0.55, x + 0.45); // Top-right corner
    glVertex2f(y + 0.55, x + 0.55); // Bottom-right corner
    glVertex2f(y + 0.45, x + 0.45); // Bottom-left corner
    glEnd();
}

void Cell::drawCrown() {
    glColor3f(0, 0, 0); // Set color to black for the crown

    glBegin(GL_TRIANGLES);

    // Left triangle of the crown
    glVertex2f(y + 0.2, x + 0.6); // Bottom-left corner of the left triangle
    glVertex2f(y + 0.3, x + 0.2); // Top of the left triangle
    glVertex2f(y + 0.4, x + 0.6); // Bottom-right corner of the left triangle

    // Middle triangle of the crown
    glVertex2f(y + 0.4, x + 0.6); // Bottom-left corner of the middle triangle
    glVertex2f(y + 0.5, x + 0.1); // Top of the middle triangle
    glVertex2f(y + 0.6, x + 0.6); // Bottom-right corner of the middle triangle

    // Right triangle of the crown
    glVertex2f(y + 0.6, x + 0.6); // Bottom-left corner of the right triangle
    glVertex2f(y + 0.7, x + 0.2); // Top of the right triangle
    glVertex2f(y + 0.8, x + 0.6); // Bottom-right corner of the right triangle

    glEnd();

    // Base of the crown
    glBegin(GL_QUADS);
    glVertex2f(y + 0.2, x + 0.6); // Bottom-left corner of the base
    glVertex2f(y + 0.8, x + 0.6); // Bottom-right corner of the base
    glVertex2f(y + 0.8, x + 0.7); // Top-right corner of the base
    glVertex2f(y + 0.2, x + 0.7); // Top-left corner of the base

    glEnd();
}

