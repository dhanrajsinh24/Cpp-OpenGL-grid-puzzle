#include <iostream>

#include "Game.h"

Game::Game() {}

void Game::makeMove(int row, int col)
{
    grid.setCell(row, col);

    std::cout << "Cell X: " << row << ", Cell Y: " << col << std::endl;

    if(hasAnyViolationWithCrown()) { // row, col)
        std::cout << "Rule violation!!" << std::endl;
    }
    else if (isGameWon()) {
        std::cout << "Game won: " << is_game_won << std::endl;
        // TODO: If we want to reset the grid and start playing again?
        // resetGame();

        //TODO: Reseting other setup
    }
}

bool Game::isGameWon() {
    is_game_won = grid.allCrownsPlaced();
    return is_game_won;
}

bool Game::hasDiagonalMatch(int row, int col) {
    if (grid.getCellState(row, col) != CellState::CROWN) 
        return false;

    // Top-left diagonal
    if (row > 0 && col > 0 && grid.getCellState(row - 1, col - 1) == CellState::CROWN)
        return true;
    // Top-right diagonal
    if (row > 0 && col < 2 && grid.getCellState(row - 1, col + 1) == CellState::CROWN)
        return true;
    // Bottom-left diagonal
    if (row < 2 && col > 0 && grid.getCellState(row + 1, col - 1) == CellState::CROWN)
        return true;
    // Bottom-right diagonal
    if (row < 2 && col < 2 && grid.getCellState(row + 1, col + 1) == CellState::CROWN)
        return true;

    return false;
}

bool Game::hasNoMoreThanOneCrownInRowAndColumn(int row, int col) {
    if (grid.getCellState(row, col) != CellState::CROWN) 
        return true;
    
    //Row check
    for (int c = 0; c < grid.grid_size; ++c) {
        //Skip the current column
        if(c == col) continue;
        if (grid.getCellState(row, c) == CellState::CROWN)
            return false;
    }

    //Column check
    for (int r = 0; r < grid.grid_size; ++r) {
        //Skip the current column
        if(r == row) continue;
        if (grid.getCellState(r, col) == CellState::CROWN)
            return false;
    }

    return true;
}

bool Game::hasOnlyOneInThatColor(int row, int col) {

    if (grid.getCellState(row, col) != CellState::CROWN) 
        return true;
    
    // Identify the color of the specified cell
    Color targetColor = grid.getCellColor(row, col);

    for (int r = 0; r < grid.grid_size; ++r) {
        for (int c = 0; c < grid.grid_size; ++c) {
            //Skip the current cell
            if(r == row && c == col) continue;
            if (grid.getCellColor(r, c) == targetColor && grid.getCellState(r, c) == CellState::CROWN)
                return false;
        }
    }

    // Return true if there's exactly one "CROWN" in that color
    return true;
}

bool Game::hasRuleViolation(int row, int col) {
    bool diagonalMatch = hasDiagonalMatch(row, col);
    bool onlyOneInRowAndCol = hasNoMoreThanOneCrownInRowAndColumn(row, col);
    bool onlyOneInColor = hasOnlyOneInThatColor(row, col);

    // Print the results
    std::cout << "Diagonal Match: " << diagonalMatch << std::endl;
    std::cout << "Only One In Row And Column: " << onlyOneInRowAndCol << std::endl;
    std::cout << "Only One In That Color: " << onlyOneInColor << std::endl;

    // Return the overall result
    return diagonalMatch || !onlyOneInRowAndCol || !onlyOneInColor;
}

bool Game::hasAnyViolationWithCrown() {
    const std::vector<std::pair<int, int>>& indices = grid.getCrownIndices();
    for (const auto& pair : indices) {
        int row = pair.first;
        int col = pair.second;

        has_rule_violation = hasRuleViolation(row, col);
        if(has_rule_violation) return true;
    }
    return false;
}


void Game::resetGame() {
    *this = Game();
}

void Game::draw(int width, int height) {
    grid.draw();

    if (is_game_won) {
        textRenderer.drawCenteredText("Game Won!", width, height);
    }

    if (has_rule_violation) {
        textRenderer.drawCenteredText("Rule Violated!", width, height);
    }
}
