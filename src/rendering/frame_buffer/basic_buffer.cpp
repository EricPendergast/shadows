#include "raii.h"
#include "basic_buffer.h"
#include <iostream>

bool is_power_of_two(int a) {
    return a && ((a & (a-1)) == 0);
}

BasicBuffer::BasicBuffer(int w, int h): FrameBuffer(w,h) {
    assert(w != 0 && h != 0);
    if (!is_power_of_two(w) && !is_power_of_two(h)) {
        std::cout << "Warning: texture with dimensions not a power of two: " << w << "x" << h << std::endl;
    }
    // create a texture object
    glGenTextures(1, &texHandle);
    glBindTexture(GL_TEXTURE_2D, texHandle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glGenFramebuffers(1, &fboHandle);

    WithBindFramebuffer b(this);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texHandle, 0);
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer error" << std::endl;
        exit(1);
    }
}
