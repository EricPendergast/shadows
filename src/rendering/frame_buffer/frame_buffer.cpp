#include "frame_buffer.h"
#include "shader.h"
#include "raii.h"

#include <iostream>
#include <fstream>
#include <assert.h>
#include <array>

//#include <CImg.h>

FrameBuffer::FrameBuffer(int w, int h) : width(w), height(h) {}

GLuint FrameBuffer::get_fbo_handle() {
    return fboHandle;
}

GLuint FrameBuffer::get_tex_handle() {
    return texHandle;
}

std::vector<float> FrameBuffer::read_pixel(int x, int y) {
    WithBindFramebuffer w(this);
    GLfloat pixel[4];
    glReadnPixels(x,y, 1,1, GL_RGBA, GL_FLOAT, 4*sizeof(pixel[0]), pixel);
    
    return std::vector<float>(pixel, pixel+4);
}

void FrameBuffer::write_pixel(int x, int y, unsigned int pixel) {
    WithBindFramebuffer w(this);
    GLubyte byte_arr[4];
    for (int i = 3; i >= 0; i--) {
        byte_arr[i] = (char)(pixel & 0xff);
        pixel >>= 8;
    }
    
    glRasterPos2i(x,y);
    glDrawPixels(1,1, GL_RGBA, GL_UNSIGNED_BYTE, byte_arr);
}

void FrameBuffer::copy_to(FrameBuffer& other) {
    copy_to(other, 0,0, width, height, 0,0, other.get_width(),other.get_height());
}

void FrameBuffer::copy_to(FrameBuffer& other, int this_x, int this_y, int this_w, int this_h, int other_x, int other_y, int other_w, int other_h) {
    //assert(this->is_in_bounds(this_x, this_y));
    //assert(this->is_in_bounds(this_x+this_w-1, this_y+this_h-1));
    //assert(other.is_in_bounds(other_x, other_y));
    //assert(other.is_in_bounds(other_x+other_w-1, other_y+other_h-1));

    {
        WithScissorTestEnabled s(true);
        WithBindFramebuffer b(&other);
        glScissor(other_x, other_y, other_w, other_h);
        WithClearColor c(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
    glBlitNamedFramebuffer(
            get_fbo_handle(), other.get_fbo_handle(), 
            this_x, this_y, this_x+this_w, this_y+this_h,
            other_x, other_y, other_x+other_w, other_y+other_h,
            GL_COLOR_BUFFER_BIT,
            GL_NEAREST);
}

void FrameBuffer::write_to(std::vector<float>& vec) {
    WithBindFramebuffer w(this);
    vec.resize(4*get_width()*get_height(), 0);
    
    glGetError();
    glReadnPixels(0, 0, get_width(), get_height(), GL_RGBA, GL_FLOAT, 4*get_width()*get_height()*(int)sizeof(float), &vec[0]);
    assert(glGetError() == 0);
}

// WARNING: BUG: Might break if dimensions are not powers of two
void FrameBuffer::write_to_tga_file(const std::string& filename) {
    (void)filename;
    //glGetError();
    //bind();
    //glReadBuffer(GL_COLOR_ATTACHMENT0);
    //
    //std::ofstream out(filename);
    ////char* pixel_data = new char[3*width*height];
    //std::array<char, 18> TGAhead = {    0,
    //                                    2, 
    //                                    0, 
    //                                    0, 0, 0, 0, 0
    //                                    (short)width, (short)height, 24 };
    //std::vector<char> pixel_data(3*get_width()*get_height());
    //
    //glReadnPixels(0, 0, get_width(), get_height(), GL_BGR, GL_UNSIGNED_BYTE, 3*get_width()*get_height(), &pixel_data.front());
    //
    //out.write((char const*)&TGAhead, sizeof(TGAhead[0])*sizeof(TGAhead));
    //out.write(&pixel_data.front(), pixel_data.size());
    //out.close();
    //assert(glGetError() == 0);
}

bool FrameBuffer::is_in_bounds(int x, int y) {
    return x >= 0 && x < get_width() && y >= 0 && y < get_height();
}

FrameBuffer::~FrameBuffer() {
    glDeleteFramebuffers(1, &fboHandle);
}
