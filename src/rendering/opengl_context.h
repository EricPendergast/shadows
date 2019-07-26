#ifndef OPENGL_CONTEXT_H
#define OPENGL_CONTEXT_H

#include "frame_buffer.h"
#include <memory>

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
    
    extern const std::unique_ptr<FrameBuffer> screen;
    extern std::unique_ptr<GameManagerInterface> manager;
    
    void init_context(int argc,  char** argv);
    void start_running(void);
}

#endif
