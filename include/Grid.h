#ifndef GRID_H
#define GRID_H

#include <vector>

#include "Cell.h"


class Grid {
private:
    std::vector<std::vector<Cell>> cells;
    std::vector<std::vector<Color>> level_color; // All level colors stored in standard 2d array format
    std::vector<std::pair<int, int>> crownIndices; // Stores all current indices (row, col) of crowns in the grid

    void addCrownIndice(int row, int col);
    void deleteCrownIndice(int row, int col);

public:
    int grid_size = 8; // 8x8 grid
    
    Grid();
    void setCell(int x, int y);
    CellState getCellState(int row, int col) const;
    Color getCellColor(int row, int col) const;
    std::vector<std::pair<int, int>> getCrownIndices();
    bool allCrownsPlaced(); // Checks if all required crowns are placed successfully in the grid
    void draw();
    void drawGridLines();
    void drawCells();
};

#endif // GRID_H
