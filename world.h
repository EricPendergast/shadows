#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include "shader.h"

#ifndef WORLD_H
#define WORLD_H

class World {
    ShaderProgram shader;
public:
    World();
    void draw();
    void render_with_shader();
};

#endif
