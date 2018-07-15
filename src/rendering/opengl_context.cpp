#include "opengl_context.h"

namespace OpenGLContext {
    namespace {
        // A frame buffer which represents the screen. This is a singleton class.
        class DefaultFrameBuffer : public FrameBuffer {
        public:
            // TODO: Figure out width and height
            DefaultFrameBuffer() : FrameBuffer(500, 500) {
                fboHandle = 0;
                texHandle = -1;
            }
            
            void set_width(int w) {
                width = w;
            }
            
            void set_height(int h) {
                height = h;
            }
        };
    }
    
    void reshape(int width, int height);
    void key_up(unsigned char key, int x, int y);
    void key_down(unsigned char key, int x, int y);
    void mouse_move(int x, int y);
    void display(void);
    
    FrameBuffer * const screen = new DefaultFrameBuffer();
    GameManagerInterface* manager;
    
    void init_context(int argc,  char** argv) {
        glutInit(&argc, argv);
        glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA); 
        glutInitWindowSize(screen->get_width(), screen->get_height());
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
        gluOrtho2D(0, screen->get_width(), 0, screen->get_height());
        glScalef(1, -1, 1);
        glTranslatef(0, -(GLfloat)screen->get_width(), 0);
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