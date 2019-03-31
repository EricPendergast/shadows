#include <vector>

#include "basic_buffer.h"
#include "collision_map.h"
#include "opengl_context.h"
#include "player.h"

#pragma once

class GameManager: public OpenGLContext::GameManagerInterface {
    ShaderProgram main_shader;
    CollisionMap collision_map;
    
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
