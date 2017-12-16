#include "light.h"

using namespace std;

Light::Light(void): projection(resolution,1), shader("shaders/light.vert", "shaders/light.frag") {}

void Light::fill_frame_buffer(World& world) {
    //printFramebufferInfo(projection.get_fbo_handle());
    //printFramebufferInfo(0);
    glBindFramebuffer(GL_FRAMEBUFFER, projection.get_fbo_handle());
    

    glClearColor(1, .5, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    // TODO: Translate with x and y
    //glTranslatef(0, 0, 0);
    glUseProgram(shader.get_handle());
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glLineWidth(2);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    glViewport(0,0, projection.width, projection.height);
    world.draw();
    //glLoadIdentity();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glBegin(GL_LINES);
    //glVertex2f(250, 250);
    //glVertex2f(250, 300);
    //glEnd();
    
    glPopMatrix();
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Light::draw_light(int screen_width, int screen_height) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f((GLfloat)screen_width,0);
    glVertex2f((GLfloat)screen_width,(GLfloat)screen_height);
    glVertex2f(0,(GLfloat)screen_height);
    glEnd();
}

GLuint Light::get_tex_handle() {
    return projection.get_tex_handle();
}
