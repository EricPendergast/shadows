#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include "shader.h"

#ifndef WORLD_H
#define WORLD_H

// This class is in charge of managing the position of blocks or various
// objects in the background of the world.
class World {
public:
    World();
    void draw();
};

#endif
