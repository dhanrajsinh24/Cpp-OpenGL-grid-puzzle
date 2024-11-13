# Works for MinGW on Windows only.
CXX = g++
CXXFLAGS = -I./include -lfreeglut -lopengl32 -lglu32
SOURCES = src/Main.cpp src/GameWindow.cpp src/Game.cpp src/Grid.cpp src/Cell.cpp src/TextRenderer.cpp
TARGET = build/Queens_Game

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(SOURCES) $(CXXFLAGS) -o $(TARGET)

clean:
	@if exist build\Queens_Game del build\Queens_Game
