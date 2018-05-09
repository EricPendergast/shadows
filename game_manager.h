#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "opengl_context.h"
#include "player.h"


class GameManager: public OpenGLContext::GameManagerInterface {
public:
    ShaderProgram* main_shader;
    Light* light;
    World* world;
    BasicBuffer* casted_shadows;
    
    Player player;
    
    bool move_left = false, move_right = false;
    
    virtual void display(void);
    virtual void mouse_move(int x, int y);
    virtual void key_up(unsigned char key, int x, int y);
    virtual void key_down(unsigned char key, int x, int y);
    ~GameManager();
    // TODO: With some reorganization, this function can be put in the
    // constructor.
    virtual void init_after_opengl_context();
    
    
};
#endif
