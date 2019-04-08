#ifndef SRC_GAME_GAME_MANAGER_H
#define SRC_GAME_GAME_MANAGER_H

#include <vector>

#include "basic_buffer.h"
#include "collision_map.h"
#include "opengl_context.h"
#include "player.h"
#include "light.h"
#include "world.h"
#include "vbo.h"
#include "level.h"


class GameManager: public OpenGLContext::GameManagerInterface {
    Level level;
    
    std::vector<bool> keys;
public:
    double last_update_time = -1;
    
    GameManager();
    // This function is used for updating as well.
    void display(void) override;
    void mouse_move(int x, int y) override;
    void key_up(unsigned char key, int x, int y) override;
    void key_down(unsigned char key, int x, int y) override;
};

#endif
