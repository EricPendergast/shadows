#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include "opengl_context.h"


class GameManager: public OpenGLContext::GameManagerInterface {
public:
    ShaderProgram* main_shader;
    Light* light;
    World* world;
    BasicBuffer* casted_shadows;
    
    virtual void display(void);
    virtual void mouse_move(int x, int y);
    ~GameManager();
    virtual void init_after_opengl_context();
    
};
#endif
