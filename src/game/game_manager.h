#include <vector>

#include "opengl_context.h"
#include "player.h"
#include "basic_buffer.h"

#pragma once

class GameManager: public OpenGLContext::GameManagerInterface {
    ShaderProgram main_shader;
    BasicBuffer casted_shadows;
    
    Light light;
    World world;
    Player player;
    
    std::vector<bool> keys;
public:
    double last_update_time = -1;
    
    GameManager();
    // This function is used for updating as well.
    virtual void display(void);
    virtual void mouse_move(int x, int y);
    virtual void key_up(unsigned char key, int x, int y);
    virtual void key_down(unsigned char key, int x, int y);
};
