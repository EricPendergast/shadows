#include "drawer.h"
#include "vbo.h"

#include <glm/glm.hpp>

#pragma once

// This class is in charge of managing the position of blocks or various
// objects in the background of the world.
class World : Drawable {
    VBO vbo;
public:
    World();
    void draw(Drawer* drawer) const;
    void draw();
    static glm::mat4 get_world_to_screen(float screen_x, float screen_y, float screen_width, float screen_height);
};
