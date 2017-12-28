#include "light.h"

using namespace std;

Light::Light(void): projection(resolution), light_shader("shaders/light.vert", "shaders/light.frag"), background_shader("shaders/shadow_background.vert", "shaders/shadow_background.frag") {}

void Light::fill_frame_buffer(World& world) {
    glEnable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, get_tex_handle());
    glBindFramebuffer(GL_FRAMEBUFFER, projection.get_fbo_handle());
    

    glClearColor(10000000, 10000000, 10000000, 1);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    // TODO: Translate with x and y
    //glTranslatef(0, 0, 0);
    glUseProgram(light_shader.get_handle());
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    glViewport(0,0, projection.width, 1);
    world.draw();
    //glLoadIdentity();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glBegin(GL_LINES);
    //glVertex2f(250, 250);
    //glVertex2f(250, 300);
    //glEnd();
    
    glPopMatrix();
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
}

void Light::draw_light(int screen_width, int screen_height) {
    glBindTexture(GL_TEXTURE_2D, get_tex_handle());
    
    glUseProgram(background_shader.get_handle());
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f((GLfloat)screen_width,0);
    glVertex2f((GLfloat)screen_width,(GLfloat)screen_height);
    glVertex2f(0,(GLfloat)screen_height);
    glEnd();
    
    //GLint dims[2];
    //glGetIntegerv(GL_MAX_VIEWPORT_DIMS, dims);
    //cout << "Dims " << dims[0] << " " << dims[1] << endl;
}

GLuint Light::get_tex_handle() {
    return projection.get_tex_handle();
}
