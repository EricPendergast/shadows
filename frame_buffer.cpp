#include "frame_buffer.h"

FrameBuffer::FrameBuffer(int width, int height) {
    // create a texture object
    glGenTextures(1, &texHandle);
    glBindTexture(GL_TEXTURE_2D, texHandle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    
    
    glGenFramebuffers(1, &fboHandle);
    glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);
    
    // attach a texture to FBO color attachement point
    //glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texHandle, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texHandle, 0);
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer error" << std::endl;
        exit(1);
    }
        
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::draw_stuff() {
    // set the rendering destination to the frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);

    glClearColor(.5, (GLclampf).5, .5, 1.);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw a rotating teapot at the origin
    //glPushMatrix();
    //glRotatef(45*0.5f, 1, 0, 0);
    //glRotatef(45, 0, 1, 0);
    //glRotatef(45*0.7f, 0, 0, 1);
    //glTranslatef(0, -1.575f, 0);
    //drawTeapot();
    //glPopMatrix();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //glBindTexture(GL_TEXTURE_2D, texHandle);
    // TODO: Does this need to be here?
    //glGenerateMipmap(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, 0);
}

//void FrameBuffer::begin_render_to() {
//    glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);
//}

GLuint FrameBuffer::get_fbo_handle() {
    return fboHandle;
}

GLuint FrameBuffer::get_tex_handle() {
    return texHandle;
}
