#ifndef CELL_H
#define CELL_H

#include <GL/freeglut.h>

enum CellState { EMPTY, CROSS, CROWN };

// Number of colors should be exactly as grid_size
enum class Color {
    Red,
    Orange,
    Yellow,
    Green,
    Blue,
    Purple,
    Beige,
    Gray
};

class Cell {
private:
    CellState state;
    int x, y;
    Color color;

public:
    Cell(int row, int col, Color color);
    Cell();
    
    void setState(CellState newState);
    CellState getState() const;
    Color getColor() const;
    void setNextState();
    void setColor();
    void draw();
    void drawQuad();
    void drawCross();
    void drawCrown();
};

#endif // CELL_H
