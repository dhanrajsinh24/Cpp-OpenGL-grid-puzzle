#include <iostream>

#include "GameWindow.h"

GameWindow::GameWindow(int width, int height, int gridSize)
    : width(width), height(height) 
{
    // Calculate cell sizes based on gridSize
    cell_width = static_cast<float>(width) / gridSize;
    cell_height = static_cast<float>(height) / gridSize;

    std::cout << "cell width: " << cell_width << ", cell height: " << cell_height << std::endl;
}
