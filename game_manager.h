#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include "opengl_context.h"


class GameManager: public OpenGLContext::GameManagerInterface {
public:
    ShaderProgram* shad;
    //FrameBuffer frame_buffer;
    Light* light;
    World* world;
    int screen_width;
    int screen_height;
    
    virtual void display(void);
    virtual void mouse_move(int x, int y);
    ~GameManager();
    virtual void init_after_opengl_context();
    
};
#endif
