#ifndef OPENGL_CONTEXT_H
#define OPENGL_CONTEXT_H

#include <GL/glew.h>
#include <GL/freeglut.h>
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
#include "world.h"

namespace OpenGLContext {
    // A class which encapsulates GLUT. Should contain most of game logic.
    class GameManagerInterface {
    public:
        // These functions are all implemented and do nothing because it is
        // convenient for the inheriting classes.
        virtual void display(){}
        virtual void mouse_move(int x, int y){(void)x; (void)y;}
        virtual void key_up(unsigned char key, int x, int y){(void)key; (void)x; (void)y;}
        virtual void key_down(unsigned char key, int x, int y){(void)key; (void)x; (void)y;}
        // These are for changing the aspect ratio.
        int screen_width;
        int screen_height;
        
        virtual ~GameManagerInterface(){};
    };
    
    extern GameManagerInterface* manager;
    
    extern FrameBuffer * const screen;
    
    void init_context(int argc,  char** argv);
    void start_running(void);
}

#endif
