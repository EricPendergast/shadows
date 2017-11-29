#include "light.h"


Light::Light(void): projection(500,1), shader("shaders/light.vert", "shaders/light.frag") {
}

void Light::fill_frame_buffer() {
    //printFramebufferInfo(projection.get_fbo_handle());
    //printFramebufferInfo(0);
    glBindFramebuffer(GL_FRAMEBUFFER, projection.get_fbo_handle());

    glClearColor(1, .5, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    
    
    // TODO: Translate with x and y
    glTranslatef(0, 0, 0);
    glUseProgram(shader.get_handle());
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glLoadIdentity();
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(-.5, 0);
    glVertex2f(-1, 0);
    glEnd();
    
    float pix[4];
    glReadPixels(50, 0, 1, 1, GL_RGBA, GL_FLOAT, &pix);
    std::cout << "HERE " << pix[0] << std::endl;
    
    glPopMatrix();
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint Light::get_tex_handle() {
    return projection.get_tex_handle();
}
