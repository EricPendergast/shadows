CXXFLAGS = -std=c++17 -Wconversion -Wall -Werror -Wextra -pedantic
GLFLAGS = -lglut -lGL -lGLU -lGLEW
test:all
all:
	g++ main.cpp shader.cpp frame_buffer.cpp printer.cpp light.cpp $(GLFLAGS) $(CXXFLAGS) -g3 -o run_game
	./run_game
