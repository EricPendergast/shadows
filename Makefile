SOURCEDIR = src/

CPPFILES = $(shell find $(SOURCEDIR) -type f -name "*.cpp")
HFILES = $(shell find $(SOURCEDIR) -type f -name "*.h")
DIRECTORIES = $(shell find $(SOURCEDIR) -type d)

OFILES= $(CPPFILES:%.cpp=%.o)
# Dependency files
DFILES = $(CPPFILES:%.cpp=%.d)
	
#GLFLAGS = -lglut -lGL -lGLU -lGLEW
GLFLAGS = -lglut -lOpenGL -lGLU -lGLEW
DIRSFLAGS = $(addprefix -I, $(DIRECTORIES))
CXXFLAGS = -std=c++17 -Wconversion -Wall -Wextra -Woverloaded-virtual -pedantic -g3 -DRUNTESTS $(GLFLAGS) $(DIRSFLAGS)

GDB = gdb -ex='set confirm on' -ex=run -ex=bt -ex=quit -quiet

test: compile
	optirun ./run_game run_tests

renderdoc: compile
	/opt/renderdoc_1.0/bin/renderdoccmd capture run_game
	
all: $(OFILES) compile
	@#Requires opengl 3, glsl 4.5.
	optirun $(GDB) ./run_game
	
compile: $(OFILES)
	@echo "$(DIRSFLAGS)" | tr " " "\n" > .include_dirs
	g++ $(OFILES) $(CXXFLAGS) -o run_game
	
-include $(DFILES)

%.d: %.cpp
	@$(CPP) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) >$@
	
.PHONY: clean
clean:
	find . -type f -name '*.o' -delete
	find . -type f -name '*.d' -delete
