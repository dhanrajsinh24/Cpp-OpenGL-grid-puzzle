#ifndef GAME_H
#define GAME_H

#include <iostream>

#include "Grid.h"
#include "TextRenderer.h"

// Game class to setup a grid based game Queens (LinkedIn)
class Game {
public:
    Grid grid;
    bool is_game_won;
    bool has_rule_violation;

    Game();

    void makeMove(int row, int col); //Take appropriate actions on specific cell
    bool isGameWon();

    // Rule checking based on Queens LinkedIn game - https://www.linkedin.com/help/linkedin/answer/a6269510/
    bool hasDiagonalMatch(int row, int col);
    bool hasNoMoreThanOneCrownInRowAndColumn(int row, int col);
    bool hasOnlyOneInThatColor(int row, int col);

    bool hasRuleViolation(int row, int col);
    bool hasAnyViolationWithCrown(); // Returns true if any rule violation observed
    void resetGame();
    void draw(int width, int height);

private:
    TextRenderer textRenderer;
};

#endif // GAME_H
