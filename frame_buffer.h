#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <iostream>

#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

class FrameBuffer {
protected:
    GLuint fboHandle;
    GLuint rboHandle;
    GLuint texHandle;
public:
    const int width;
    const int height;
    FrameBuffer(int w, int h);
    void draw_stuff();
    void begin_render_to();
    void end_render_to();
    //void pass_as_uniform();
    GLuint get_fbo_handle();
    GLuint get_tex_handle();
};

class DepthBuffer : public FrameBuffer {
public:
    DepthBuffer(int w, int h);
};

#endif
