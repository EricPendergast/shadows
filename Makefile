SOURCES = $(wildcard *.cpp)
CXXFLAGS = -std=c++17 -Wconversion -Wall -Wextra -pedantic -g3 -DRUNTESTS
GLFLAGS = -lglut -lGL -lGLU -lGLEW
OBJECTS	= $(SOURCES:%.cpp=%.o)
test: compile
	optirun ./run_game run_tests

renderdoc: compile
	/opt/renderdoc_1.0/bin/renderdoccmd capture run_game
	
all: $(OBJECTS) compile
	@#Requires opengl 3, glsl 4.5.
	optirun ./run_game
	
compile: $(OBJECTS)
	g++ $(OBJECTS) $(GLFLAGS) $(CXXFLAGS)  -o run_game 
	
%.o: %.cpp *.h Makefile
	$(CXX) $(CXXFLAGS) $(GLFLAGS) -c $*.cpp
