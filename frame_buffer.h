#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <iostream>

#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

class FrameBuffer {
    GLuint fboHandle;
    GLuint rboHandle;
    GLuint texHandle;
public:
    FrameBuffer(int width, int height);
    void draw_stuff();
    void begin_render_to();
    void end_render_to();
    void pass_as_uniform();
    GLuint get_fbo_handle();
    GLuint get_tex_handle();
};

#endif
