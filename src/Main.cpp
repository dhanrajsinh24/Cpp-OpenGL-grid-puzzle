#include <iostream>
#include <GL/freeglut.h>

#include "Game.h"
#include "GameWindow.h"

// Using define to check the platform. Planning to port the game to Windows and Android
#if defined(_WIN32)
    #define PLATFORM_WINDOWS
#elif defined(__ANDROID__)
    #define PLATFORM_ANDROID
#else
    #define PLATFORM_UNKNOWN
#endif

Game game;
Grid grid;
GameWindow window(600, 600, grid.grid_size); // Initializing window with 600x600 dimentions

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    game.draw(window.width, window.height);
    glutSwapBuffers();
    glFlush();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    //X and Y starts at top
    gluOrtho2D(0, grid.grid_size, grid.grid_size, 0);
    
    glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) {
    if(game.is_game_won) return;

    #ifdef PLATFORM_WINDOWS
    // Handling left mouse button input
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        std::cout << "Mouse click- X: " << x << "Y: " << y << std::endl;
        
        // Converting mouse click pixel positions to cell indices
        int cell_x = x / window.cell_width;
        int cell_y = (window.height - y) / window.cell_height;

        // Matching row and columns with the current ortho projections
        int row = grid.grid_size - 1 - cell_y;
        int col = cell_x;

        // When the mouse click is around the right side edge, cell_x might be out of bounds!
        // Ensure cell_x and cell_y are within valid range
        if (row >= 0 && row < grid.grid_size && col >= 0 && col < grid.grid_size) {
            game.makeMove(row, col);
        } else {
            std::cout << "Click out of bounds!" << std::endl;
        }

        glutPostRedisplay();
    }
    #endif
}

void input() {
    glutMouseFunc(mouse);
}

void render() 
{
    glClearColor(0, 0, 0, 1);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
}

void initWindow(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(window.width, window.height);
    glutCreateWindow("Queens Game");
}

void DebugPlatform() {
    #ifdef PLATFORM_WINDOWS
        std::cout << "Running on Windows" << std::endl;
        // Windows-specific initialization or functionality
    #elif defined(PLATFORM_ANDROID)
        std::cout << "Running on Android" << std::endl;
        // Android-specific initialization or functionality
    #else
        std::cout << "Unknown platform" << std::endl;
        // Handle unknown platform
    #endif
}

int main(int argc, char** argv) {
    DebugPlatform();

    initWindow(argc, argv);
    input();
    render();

    return 0;
}
