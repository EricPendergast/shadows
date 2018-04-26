#ifndef OPENGL_CONTEXT_H
#define OPENGL_CONTEXT_H

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
#include "world.h"

namespace OpenGLContext {
    const int render_width = 500;
    const int render_height = 500;
    // A class which encapsulates GLUT. Should contain most of game logic.
    class GameManagerInterface {
    public:
        virtual void display(){}
        virtual void mouse_move(int x, int y){}
        // Should be called after the opengl context exists. Could do things
        // such as initializing shaders, frame buffers, VBOs, etc.
        virtual void init_after_opengl_context(){}
        int screen_width;
        int screen_height;
        
        // TODO: This is probably a good idea:
        //virtual ~GameManagerInterface()=0;
    };
    extern GameManagerInterface* manager;
    
    
    void init_context(int argc,  char** argv);
    void reshape(int width, int height);
    void key_up(unsigned char key, int x, int y);
    void key_down(unsigned char key, int x, int y);
    void mouse_move(int x, int y);
    void draw_world(void);
    void display(void);
    void start_running(void);
}

#endif
