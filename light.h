#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include "frame_buffer.h"
#include "shader.h"
#include "printer.h"

#ifndef LIGHT_H
#define LIGHT_H

// 
class Light {
    int resolution = 500;
    FrameBuffer projection;
    ShaderProgram shader;
    int x,y;

public:
    Light(void);
    void fill_frame_buffer();
    GLuint get_tex_handle();
};

#endif
