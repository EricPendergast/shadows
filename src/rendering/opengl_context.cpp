#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

#include "opengl_context.h"
#include "raii.h"

namespace OpenGLContext {
    namespace {
        // A frame buffer which represents the screen. This is a singleton class.
        class DefaultFrameBuffer : public FrameBuffer {
        public:
            // TODO: Figure out width and height
            DefaultFrameBuffer() : FrameBuffer(1000, 1000) {
                fboHandle = 0;
                texHandle = -1;
            }

            int get_width() override {
                return glutGet(GLUT_WINDOW_WIDTH);
            }

            int get_height() override {
                return glutGet(GLUT_WINDOW_HEIGHT);
            }
        };
    }
    
    void reshape(int width, int height);
    void key_up(unsigned char key, int x, int y);
    void key_down(unsigned char key, int x, int y);
    void mouse_move(int x, int y);
    void display(void);
    void do_nothing(void);
    
    const std::unique_ptr<FrameBuffer> screen = std::make_unique<DefaultFrameBuffer>();
    std::unique_ptr<GameManagerInterface> manager(nullptr);
    
    void init_context(int argc,  char** argv) {
        glutInit(&argc, argv);
        glutInitContextVersion(4, 0);
        glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
        glutInitContextProfile(GLUT_CORE_PROFILE);
        glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA); 
        glutInitWindowSize(800, 800);
        glutInitWindowPosition(100,100);
        glutCreateWindow("Shadows");
        glutDisplayFunc(do_nothing);
        glutIdleFunc(display);
        glutReshapeFunc(reshape);
        glutKeyboardFunc(key_down);
        glutKeyboardUpFunc(key_up);
        glutMotionFunc(mouse_move);

        //std::cout << "HELLO " << glGetString(GL_VERSION) << std::endl;
        
        auto glew_init_result = glewInit();
        if(glewInit() != GLEW_OK) {
            std::cout << "ERROR: " << glewGetErrorString(glew_init_result) << std::endl;
            exit(1);
        }
        
        glEnable(GL_TEXTURE_2D);
        set_raii_defaults();
    }

    void reshape(int width, int height) {
        manager->screen_width = width;
        manager->screen_height = height;
        WithViewport::set_default(0, 0, width, height);
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
        glClear(GL_COLOR_BUFFER_BIT);
        
        manager->display();
        
        glutSwapBuffers();
    }
    
    void do_nothing(void) {
        
    }
    
    void start_running(void) {
        glutMainLoop();
    }
}
