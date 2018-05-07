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
    GLuint get_fbo_handle();
    GLuint get_tex_handle();
    
    // For testing. Warning: binds this framebuffer, and does not unbind.
    // Assumes RGBA format. Not tested on types other than floats.
    std::vector<float> read_pixel(int x, int y); 
    // Not yet working
    void write_pixel(int x, int y, unsigned int pixel); 
    void bind();
};

// Intended to be used as a shadow buffer which is a square around a
// point. Contains a frame buffer with given width and height 4. Uses a
// renderbuffer for depth testing, and writes depth values to its texture, to
// be read by a shader at a later point.
class DepthBoxBuffer : public FrameBuffer {
public:
    // These constants specify which row corresponds to each side of the
    // square.
    // Note: These are the same values as defined in light_box.vert
    static const int UP = 0;
    static const int DOWN = 1;
    static const int RIGHT = 2;
    static const int LEFT = 3;
    static const std::vector<float> DEFAULT_DEPTH;
    
    ShaderProgram projection_shader;
    
    DepthBoxBuffer(int width);
    // To be called before drawing. Enables the projection shader.
    void begin_draw(int row);
    // Prepares depth and color buffers for rendering
    void clear();
    ShaderProgram* shader();
private:
    // Sets the viewport to only render to the specified row.
    void set_render_row(int row);
};

// A FrameBuffer which is as simple as possible. No depth testing, or anything
// fancy.
class BasicBuffer : public FrameBuffer {
public:
    BasicBuffer(int w, int h);
};

#endif
