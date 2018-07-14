#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "opengl_context.h"
#include "player.h"

class GameManager: public OpenGLContext::GameManagerInterface {
public:
    ShaderProgram main_shader;
    BasicBuffer casted_shadows;
    
    Light light;
    World world;
    Player player;
    
    bool move_left = false, move_right = false;
    bool jump = false;
    
    double last_update_time = -1;
    
    GameManager();
    // This function is used for updating as well.
    virtual void display(void);
    virtual void mouse_move(int x, int y);
    virtual void key_up(unsigned char key, int x, int y);
    virtual void key_down(unsigned char key, int x, int y);
};

#endif
