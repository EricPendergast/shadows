#include "frame_buffer.h"

FrameBuffer::FrameBuffer(int w, int h) : width(w), height(h) {}

GLuint FrameBuffer::get_fbo_handle() {
    return fboHandle;
}

GLuint FrameBuffer::get_tex_handle() {
    return texHandle;
}

std::vector<float> FrameBuffer::read_pixel(int x, int y) {
    bind();
    GLfloat pixel[4];
    glReadPixels(x,y, 1,1, GL_RGBA, GL_FLOAT, pixel);
    
    return std::vector<float>(pixel, pixel+4);
}

void FrameBuffer::write_pixel(int x, int y, unsigned int pixel) {
    bind();
    GLubyte byte_arr[4];
    for (int i = 3; i >= 0; i--) {
        byte_arr[i] = (char)(pixel & 0xff);
        pixel >>= 8;
    }
    
    glRasterPos2i(x,y);
    glDrawPixels(1,1, GL_RGBA, GL_UNSIGNED_BYTE, byte_arr);
}

void FrameBuffer::copy_to(FrameBuffer& other) {
    glBlitNamedFramebuffer(
            get_fbo_handle(), other.get_fbo_handle(), 
            0,0, width, height,
            0,0, width, height,
            GL_COLOR_BUFFER_BIT,
            GL_NEAREST);
}

void FrameBuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, get_fbo_handle());
}

void FrameBuffer::write_to_tga_file(const std::string& filename) {
    bind();
    
    FILE* out = std::fopen(filename.c_str(), "wb");
    char* pixel_data = new char[3*width*height];
    short TGAhead[] = { 0, 2, 0, 0, 0, 0, (short)width, (short)height, 24 };

    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, pixel_data);

    fwrite(&TGAhead, sizeof(TGAhead), 1, out);
    fwrite(pixel_data, 3*width*height, 1, out);
    fclose(out);

    delete[] pixel_data;
}








