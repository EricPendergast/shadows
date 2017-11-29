#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <algorithm>

#include "shader.h"
#include "frame_buffer.h"
#include "printer.h"
#include "light.h"

void display(void);
void reshape (int, int);
void key_down(unsigned char key, int x, int y);
void key_up(unsigned char key, int x, int y);

ShaderProgram* shad;
FrameBuffer* frame_buffer;
Light* light;
// Applying various settings to glut, as well as assigning functions
void init(int argc,  char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA); 
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Shadows");
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key_down);
    glutKeyboardUpFunc(key_up);
    
    if(glewInit() != GLEW_OK) {
        std::cout << "GLEW bad" << std::endl;
        exit(1);
    }
    
    glEnable(GL_TEXTURE_2D);
    
}

void reshape(int width, int height) {
    glLoadIdentity();
    glViewport(0,0, width, height);
    gluOrtho2D(0, 500, 0, 500);
    glScalef(1, -1, 1);
    glTranslatef(0, -(GLfloat)500, 0);

    // Switch back to the model view matrix, so that we can start drawing
    // shapes correctly
    glMatrixMode(GL_MODELVIEW);
} 

GLfloat counter = 0;
void key_up(unsigned char key, int x, int y) {  
    (void)x;
    (void)y;
    (void)key;
    //std::cout << "UP" << key << std::endl;
}  
  
void key_down(unsigned char key, int x, int y) {  
    (void)x;
    (void)y;
    counter += 10;
    //std::cout << "DOWN" << std::endl;
    if (key == 0x001b) //Escape key
        exit(0);
}

void draw_world(void) {
    
    light->fill_frame_buffer();
    
    glUseProgram(shad->get_handle());
    //glBindTexture(GL_TEXTURE_2D, frame_buffer->get_tex_handle());
    glBindTexture(GL_TEXTURE_2D, light->get_tex_handle());
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_QUADS);
    glVertex2f(counter, 0);
    glVertex2f(125, 375);
    glVertex2f(375, 375);
    glVertex2f(375, 125);
    glEnd();
}

void display(void) {
    glClearColor(1.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    draw_world();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    
    init(argc, argv);
    
    ShaderProgram shader("shaders/main.vert", "shaders/main.frag");
    shad = &shader;
    
    
    FrameBuffer fb(500, 500);
    frame_buffer = &fb;
    fb.draw_stuff();
    
    
    Light l;
    light = &l;
    
    //glBindFramebuffer(GL_FRAMEBUFFER, fb.get_fbo_handle());
    //int pix;
    //glReadPixels(1,1, 1,1, GL_GREEN, GL_INT, &pix);
    //pix = 0x00FFFF00;
    //glRasterPos2i(48,56);
    //glDrawPixels(1,1, GL_RGB, GL_INT, &pix);
    //std::cout << "HERE " << std::hex << pix << std::endl;
    
    printFramebufferInfo(fb.get_fbo_handle());
    glutMainLoop();
}
