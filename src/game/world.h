#ifndef SRC_GAME_WORLD_H
#define SRC_GAME_WORLD_H

#include "drawer.h"
#include "vbo.h"

#include <glm/glm.hpp>


// This class is in charge of managing the position of blocks or various
// objects in the background of the world.
class World : Drawable {
    VBO vbo;
public:
    World();
    void draw();
    static glm::mat4 get_world_to_screen(float screen_x, float screen_y, float screen_width, float screen_height);
};

#endif
