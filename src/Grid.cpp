#include <iostream>
#include <algorithm>

#include "Grid.h"

Grid::Grid() {
    // 2d matrix (row, column) -> Top to bottom, Left to right
    level_color = {
        {Color::Purple, Color::Orange, Color::Orange, Color::Blue,   Color::Green,  Color::Green,  Color::Green, Color::Beige},
        {Color::Purple, Color::Purple, Color::Orange, Color::Blue,   Color::Blue,   Color::Green,  Color::Green, Color::Beige},
        {Color::Red,    Color::Purple, Color::Purple, Color::Purple, Color::Purple, Color::Green,  Color::Green, Color::Beige},
        {Color::Red,    Color::Red,    Color::Purple, Color::Purple, Color::Purple, Color::Purple, Color::Green, Color::Beige},
        {Color::Yellow, Color::Yellow, Color::Purple, Color::Purple, Color::Purple, Color::Purple, Color::Green, Color::Purple},
        {Color::Gray,   Color::Yellow, Color::Purple, Color::Purple, Color::Purple, Color::Purple, Color::Purple, Color::Purple},
        {Color::Gray,   Color::Gray,   Color::Gray,   Color::Purple, Color::Purple, Color::Purple, Color::Purple, Color::Purple},
        {Color::Gray,   Color::Gray,   Color::Gray,   Color::Gray,   Color::Gray,   Color::Purple, Color::Purple, Color::Purple}
    };

    // Fill the 2D vector using indices
    for (int i = 0; i < grid_size; ++i) {
        std::vector<Cell> row;
        for (int j = 0; j < grid_size; ++j) {
            row.emplace_back(i, j, level_color[i][j]);
        }
        cells.push_back(row);
    }
}

void Grid::draw() {
    drawCells();
    drawGridLines();
}

void Grid::drawGridLines() {
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(1.5);
    
    // Enable line smoothing for better quality if supported
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); 
    
    glBegin(GL_LINES);
    for (int i = 0; i <= grid_size; ++i) {
        glVertex2f(i, 0);
        glVertex2f(i, grid_size);
        glVertex2f(0, i);
        glVertex2f(grid_size, i);
    }
    glEnd();
}

void Grid::drawCells() {
    for (auto& row : cells) {
        for (auto& cell : row) {
            cell.draw();
        }
    } 
}

void Grid::setCell(int row, int col) {
    if(getCellState(row, col) == CellState::CROWN) {
        deleteCrownIndice(row, col);
    }
    cells[row][col].setNextState();
    if(getCellState(row, col) == CellState::CROWN) {
        addCrownIndice(row, col);
    }
}

CellState Grid::getCellState(int row, int col) const {
    return cells[row][col].getState();
}

Color Grid::getCellColor(int row, int col) const {
    return cells[row][col].getColor();
}

std::vector<std::pair<int, int>> Grid::getCrownIndices() {
    return crownIndices;
}

bool Grid::allCrownsPlaced() {
    return crownIndices.size() == grid_size;
}

void Grid::addCrownIndice(int row, int col) {
    crownIndices.push_back({row, col});
}

void Grid::deleteCrownIndice(int row, int col) {
    auto item = std::find(crownIndices.begin(), crownIndices.end(), std::make_pair(row, col));
    if(item != crownIndices.end()) {
        crownIndices.erase(item);
    }
}
