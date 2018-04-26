#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <assert.h>
#include <iostream>
#include <vector>


// Provides some helper methods for dealing with frame buffers. Child classes
// should initialize frame buffers.

class FrameBuffer {
protected:
    GLuint fboHandle;
    GLuint rboHandle;
    GLuint texHandle;
    FrameBuffer(int w, int h);
public:
    const int width;
    const int height;
    //void end_render_to();
    //void pass_as_uniform();
    GLuint get_fbo_handle();
    GLuint get_tex_handle();
    // For testing
    // Warning: binds this framebuffer
    int read_pixel(int x, int y); 
    void write_pixel(int x, int y, unsigned int pixel); 
    void bind();
};

class DepthBuffer : public FrameBuffer {
public:
    DepthBuffer(int w);
};

class BasicBuffer : public FrameBuffer {
public:
    BasicBuffer(int w, int h);
};

#endif
