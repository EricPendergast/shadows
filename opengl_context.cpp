#include "opengl_context.h"

namespace OpenGLContext {
    GameManagerInterface* manager;
    
    void init_context(int argc,  char** argv) {
        glutInit(&argc, argv);
        glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA); 
        manager->screen_width = render_width;
        manager->screen_height = render_height;
        glutInitWindowSize(manager->screen_width, manager->screen_height);
        glutInitWindowPosition(100,100);
        glutCreateWindow("Shadows");
        glutIdleFunc(display);
        glutReshapeFunc(reshape);
        glutKeyboardFunc(key_down);
        glutKeyboardUpFunc(key_up);
        glutMotionFunc(mouse_move);
        
        if(glewInit() != GLEW_OK) {
            std::cout << "GLEW bad" << std::endl;
            exit(1);
        }
        
        glEnable(GL_TEXTURE_2D);
    }

    void reshape(int width, int height) {
        glMatrixMode(GL_MODELVIEW);
        manager->screen_width = width;
        manager->screen_height = height;
        glLoadIdentity();
        glViewport(0,0, width, height);
        gluOrtho2D(0, render_width, 0, render_height);
        glScalef(1, -1, 1);
        glTranslatef(0, -(GLfloat)render_height, 0);
    } 


    void key_up(unsigned char key, int x, int y) {  
        manager->key_up(key, x, y);
    }

    void key_down(unsigned char key, int x, int y) {  
        manager->key_down(key, x, y);
        if (key == 0x001b) //Escape key
            exit(0);
    }

    void mouse_move(int x, int y) {
        manager->mouse_move(x, y);
    }

    void display(void) {
        glClearColor(1.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        manager->display();
        
        glutSwapBuffers();
    }
    
    void start_running(void) {
        glutMainLoop();
    }

}
