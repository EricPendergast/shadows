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


void FrameBuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, get_fbo_handle());
}


const std::vector<float> DepthBoxBuffer::DEFAULT_DEPTH({1000000, 0, 0, 1});

// Using the color buffer as a depth buffer. 
DepthBoxBuffer::DepthBoxBuffer(int w) : FrameBuffer(w, 4), projection_shader("shaders/light_box.vert", "shaders/light_box.frag") {
    // create a texture object
    glGenTextures(1, &texHandle);
    glBindTexture(GL_TEXTURE_2D, texHandle);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // alternate setting
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glGenFramebuffers(1, &fboHandle);
    glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);
    
    // Uses a depth render buffer so that closest fragment gets rendered for
    // each pixel. The depth value ultimately gets stored in the color buffer
    // so that it can be accessed by a texture sample in a shader.
    GLuint depthrenderbuffer;
    glGenRenderbuffers(1, &depthrenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texHandle, 0);
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer error" << std::endl;
        exit(1);
    }
        
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    // TODO: Do we need to bind the shader?
    //glUniform1i(shader()->get_uniform("UP"), UP);
    //glUniform1i(shader()->get_uniform("DOWN"), DOWN);
    //glUniform1i(shader()->get_uniform("RIGHT"), RIGHT);
    //glUniform1i(shader()->get_uniform("LEFT"), LEFT);
}

void DepthBoxBuffer::begin_draw(int row) {
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    projection_shader.use();
    set_render_row(row);
    glUniform1i(shader()->get_uniform("side"), row);
}

void DepthBoxBuffer::clear() {
    // Setting the default depth to far away
    glClearColor(DEFAULT_DEPTH[0], DEFAULT_DEPTH[1], DEFAULT_DEPTH[2], DEFAULT_DEPTH[3]);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

ShaderProgram* DepthBoxBuffer::shader() {
    return &projection_shader;
}

void DepthBoxBuffer::set_render_row(int row) {
    assert(row >= 0 && row < 4);
    
    glViewport(0, row, width, 1);
}



BasicBuffer::BasicBuffer(int w, int h): FrameBuffer(w,h) {
    // create a texture object
    glGenTextures(1, &texHandle);
    glBindTexture(GL_TEXTURE_2D, texHandle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glGenFramebuffers(1, &fboHandle);
    glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texHandle, 0);
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer error" << std::endl;
        exit(1);
    }
        
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
}
