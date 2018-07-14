#pragma once

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <assert.h>
#include <iostream>
#include <vector>

#include "shader.h"

// Provides some helper methods for dealing with frame buffers. Child classes
// should initialize frame buffers.


class FrameBuffer {
protected:
    GLuint fboHandle;
    GLuint texHandle;
    FrameBuffer(int w, int h);
public:
    const int width;
    const int height;
    //void end_render_to();
    //void pass_as_uniform();
    virtual GLuint get_fbo_handle();
    virtual GLuint get_tex_handle();
    
    // For testing. Warning: binds this framebuffer, and does not unbind.
    // Assumes RGBA format. Not tested on types other than floats.
    std::vector<float> read_pixel(int x, int y); 
    // Not yet working
    virtual void write_pixel(int x, int y, unsigned int pixel); 
    // Copies this frame buffer to the frame buffer with handle other_fb. Note:
    // Assumes the two frame buffers are the same size. Only copies colors.
    virtual void copy_to(FrameBuffer& other);
    virtual void bind();
    
    virtual void write_to_tga_file(const std::string& filename);
};
