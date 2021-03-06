#ifndef SRC_RENDERING_FRAME_BUFFER_FRAME_BUFFER_H
#define SRC_RENDERING_FRAME_BUFFER_FRAME_BUFFER_H

#include <GL/glew.h>

#include <vector>
#include <string>


// Provides some helper methods for dealing with frame buffers. Child classes
// should initialize frame buffers.

class FrameBuffer {
protected:
    int width;
    int height;
    GLuint fboHandle;
    GLuint texHandle;
    FrameBuffer(int w, int h);
public:
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
    virtual void copy_to(FrameBuffer& other, int this_x, int this_y, int this_w, int this_h, int other_x, int other_y, int other_w, int other_h);
    
    virtual void write_to(std::vector<float>& vec);
    virtual void write_to_tga_file(const std::string& filename);
    
    virtual int get_width() {
        return width;
    }
    virtual int get_height() {
        return height;
    }
    
    virtual bool is_in_bounds(int x, int y);
    
    virtual ~FrameBuffer();
};

#endif
