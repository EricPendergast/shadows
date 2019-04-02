#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include "world.h"

World::World() : vbo({
        450, 300, 0, 1,
        400, 300, 0, 1,
        400, 350, 0, 1,
        450, 350, 0, 1,
        0,   500, 0, 1,
        400, 500, 0, 1,
        400, 490, 0, 1,
        0,   490, 0, 1 }) {
}

void World::draw() {
    vbo.draw();
}

glm::mat4 World::get_world_to_screen(float screen_x, float screen_y, float screen_width, float screen_height) {
    assert(screen_x == 0 && screen_y == 0);
    auto transform = glm::scale(glm::vec3(2.0f/screen_width, -2.0f/(float)screen_height, 1.0f));
    return glm::translate(glm::vec3(-1,1,0)) * transform;
}
