#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>


#pragma once

// A Drawer instance is responsible for 
class Drawer {
public:
    virtual void draw() = 0;
};
