SOURCES = $(wildcard *.cpp)
CXXFLAGS = -std=c++17 -Wconversion -Wall -Werror -Wextra -pedantic
GLFLAGS = -lglut -lGL -lGLU -lGLEW
OBJECTS	= $(SOURCES:%.cpp=%.o)
test:all
all: $(OBJECTS)
	g++ $(OBJECTS) $(GLFLAGS) $(CXXFLAGS) -g3 -o run_game
	./run_game
	
%.o: %.cpp *.h
	$(CXX) $(CXXFLAGS) $(GLFLAGS) -c $*.cpp
