#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

class GameWindow {
public:
    GameWindow(int width, int height, int gridSize);

    int width;
    int height;
    float cell_width;
    float cell_height;
};

#endif // GAME_WINDOW_H
