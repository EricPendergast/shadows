SOURCES = $(wildcard *.cpp)
CXXFLAGS = -std=c++17 -Wconversion -Wall -Wextra -pedantic -g3
GLFLAGS = -lglut -lGL -lGLU -lGLEW
OBJECTS	= $(SOURCES:%.cpp=%.o)
test:all
all: $(OBJECTS)
	g++ $(OBJECTS) $(GLFLAGS) $(CXXFLAGS) -o run_game
	@#Requires opengl 3, glsl 4.5. Optirun may not be needed on some computers.
	optirun ./run_game
	
%.o: %.cpp *.h
	$(CXX) $(CXXFLAGS) $(GLFLAGS) -c $*.cpp
